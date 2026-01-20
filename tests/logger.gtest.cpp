/**

    @file      logger.gtest.cpp
    @author    Khrapov
    @date      19.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *logger.gtest.cpp

#include <qx/logger/logger.h>

#include <qx/logger/cout_logger_stream.h>
#include <qx/logger/file_logger_stream_fopen.h>
#include <qx/logger/file_logger_stream_mapping.h>
#include <qx/logger/file_logger_stream_ofstream.h>
#include <qx/logger/fwrite_logger_stream.h>

#include <filesystem>
#include <regex>

#if QX_WIN
    #include <fcntl.h>
    #include <io.h>
    #define __dup    _dup
    #define __dup2   _dup2
    #define __close  _close
    #define __read   _read
    #define __pipe   _pipe
    #define __fileno _fileno
#else
    #include <fcntl.h>
    #include <unistd.h>
    #define __dup    dup
    #define __dup2   dup2
    #define __close  close
    #define __read   read
    #define __fileno fileno
#endif

QX_DEFINE_CATEGORY(CatLoggerTest);
QX_DEFINE_CATEGORY(CatLoggerTestFileWide);
QX_SET_FILE_CATEGORY(CatLoggerTestFileWide);

constexpr qx::string_view k_svLogFileName = QXT("logger_test.log");

namespace traits
{

struct base_file
{
    static void set_up()
    {
        EXPECT_FALSE(std::filesystem::exists(k_svLogFileName));
    }

    static qx::string get_content()
    {
        qx::logger_singleton::get_instance().get_logger().flush();
        qx::logger_singleton::get_instance().get_logger().reset();

        EXPECT_TRUE(std::filesystem::exists(k_svLogFileName));

        const std::filesystem::path        path(k_svLogFileName);
        std::basic_ifstream<qx::char_type> file(path, std::ios::binary);

        if constexpr (std::is_same_v<qx::char_type, wchar_t>)
        {
            QX_DISABLE_MSVC_WARNINGS(4996);
            file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<qx::char_type, 0x10ffff, std::little_endian>));
            QX_RESTORE_MSVC_WARNINGS(4996);
        }

        return { std::istreambuf_iterator<qx::char_type>(file), std::istreambuf_iterator<qx::char_type>() };
    }

    static void tear_down()
    {
        std::filesystem::remove(k_svLogFileName);
    }
};

struct ostream_default_buffer : base_file
{
    static void set_up()
    {
        base_file::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_ofstream(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName },
            qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
    }
};

struct ostream : base_file
{
    static void set_up()
    {
        base_file::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_ofstream(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName }));
    }
};

struct fopen_default_buffer : base_file
{
    static void set_up()
    {
        base_file::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_fopen(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName },
            qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
    }
};

struct fopen : base_file
{
    static void set_up()
    {
        base_file::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_fopen(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName }));
    }
};

struct mapping_default_initial_size : base_file
{
    static void set_up()
    {
        base_file::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_mapping(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName },
            qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
    }
};

struct mapping : base_file
{
    static void set_up()
    {
        base_file::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_mapping(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName }));
    }
};

struct base_cout
{
    // Saved original file descriptors for stdout/stderr
    static inline int s_nOldOutDescriptor = -1;
    static inline int s_nOldErrDescriptor = -1;

    static inline int s_nReadPipe  = -1;
    static inline int s_nWritePipe = -1;

#if QX_WIN
    // Previous text modes (used when wchar_t is active)
    static inline int s_nOldOutMode = -1;
    static inline int s_nOldErrMode = -1;
#else
    static inline bool s_bCharOutput = false;
#endif

    // Redirect stdout and stderr into a single pipe
    static void set_up()
    {
        std::fflush(stdout);
        std::fflush(stderr);

        // Save original stdout/stderr descriptors
        s_nOldOutDescriptor = __dup(__fileno(stdout));
        ASSERT_GE(s_nOldOutDescriptor, 0);
        s_nOldErrDescriptor = __dup(__fileno(stderr));
        ASSERT_GE(s_nOldErrDescriptor, 0);

        int fds[2];
#if QX_WIN
        // Create binary pipe (no CR/LF or encoding conversion)
        ASSERT_EQ(__pipe(fds, 1 << 16, _O_BINARY), 0);
#else
        // Create POSIX pipe
        ASSERT_EQ(::pipe(fds), 0);
#endif
        s_nReadPipe  = fds[0];
        s_nWritePipe = fds[1];

        // Redirect both stdout and stderr to the same pipe
#if QX_WIN
        ASSERT_EQ(__dup2(s_nWritePipe, __fileno(stdout)), 0);
        ASSERT_EQ(__dup2(s_nWritePipe, __fileno(stderr)), 0);
#else
        ASSERT_NE(__dup2(s_nWritePipe, STDOUT_FILENO), -1);
        ASSERT_NE(__dup2(s_nWritePipe, STDERR_FILENO), -1);
#endif

#if QX_WIN
        // If wchar_t is used, switch CRT to UTF-16 text mode
        if constexpr (std::is_same_v<qx::char_type, wchar_t>)
        {
            s_nOldOutMode = _setmode(__fileno(stdout), _O_U16TEXT);
            s_nOldErrMode = _setmode(__fileno(stderr), _O_U16TEXT);
        }
#endif
    }

    // Restore stdout/stderr and return captured output
    static qx::string get_content()
    {
#if QX_WIN
        // Restore previous text mode if wchar_t was used
        if constexpr (std::is_same_v<qx::char_type, wchar_t>)
        {
            if (s_nOldOutMode != -1)
                _setmode(__fileno(stdout), s_nOldOutMode);
            if (s_nOldErrMode != -1)
                _setmode(__fileno(stderr), s_nOldErrMode);
        }
#endif

        // Restore original stdout/stderr
        __dup2(s_nOldOutDescriptor, __fileno(stdout));
        __dup2(s_nOldErrDescriptor, __fileno(stderr));
        __close(s_nOldOutDescriptor);
        s_nOldOutDescriptor = -1;
        __close(s_nOldErrDescriptor);
        s_nOldErrDescriptor = -1;

        // Close write end so read end receives EOF
        __close(s_nWritePipe);
        s_nWritePipe = -1;

        // Read all captured bytes
        qx::string             sContent;
        std::array<char, 1024> buffer;
        while (true)
        {
            int n = __read(s_nReadPipe, buffer.data(), static_cast<unsigned int>(buffer.size()));
            if (n > 0)
            {
#if QX_WIN
                QX_PUSH_SUPPRESS_MSVC_WARNINGS(4244);
                if constexpr (std::is_same_v<qx::char_type, char>)
                {
                    sContent.append(buffer.data(), buffer.data() + n);
                }
                else
                {
                    for (int i = 0; i < n; i += sizeof(qx::char_type))
                        sContent.push_back(*reinterpret_cast<qx::char_type*>(&buffer[i]));
                }
                QX_POP_SUPPRESS_WARNINGS();
#else
                if (s_bCharOutput)
                {
                    for (int i = 0; i < n; ++i)
                        sContent.append(static_cast<qx::char_type>(buffer[i]));
                }
                else
                {
                    for (int i = 0; i < n; i += sizeof(qx::char_type))
                        sContent.push_back(*reinterpret_cast<qx::char_type*>(&buffer[i]));
                }
#endif
            }
            else
            {
                break;
            }
        }

        __close(s_nReadPipe);
        s_nReadPipe = -1;

        return sContent;
    }

    static void tear_down()
    {
    }
};
struct cout : base_cout
{
    static void set_up()
    {
        // On POSIX, cout outputs always use char
#if !QX_WIN
        s_bCharOutput = true;
#endif

        base_cout::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(
            qx::cout_logger_stream(qx::cout_logger_stream::config { { .bUseColors = false }, false, false }));
    }
};

struct fwrite : base_cout
{
    static void set_up()
    {
#if !QX_WIN
        s_bCharOutput = false;
#endif

        base_cout::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(
            qx::fwrite_logger_stream(qx::fwrite_logger_stream::config { .bUseColors = false }));
    }
};

} // namespace traits

using implementations_type = ::testing::Types<
    traits::ostream_default_buffer,
    traits::ostream,
    traits::fopen_default_buffer,
    traits::fopen,
    traits::mapping_default_initial_size,
    traits::mapping,
    traits::cout,
    traits::fwrite>;

template<class traits_t>
class logger_test : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        qx::logger_singleton::get_instance().get_logger().reset();
        traits_t::set_up();
    }
    virtual void TearDown() override
    {
        qx::get_logger().flush();

        const qx::string                   sContent = traits_t::get_content();
        const std::vector<qx::string_view> lines    = sContent.split(QXT('\n'));
        auto                               it       = lines.begin();

        check_line(*it++, qx::verbosity::log, CatLoggerTestFileWide, QXT("Hello world"));
        check_line(*it++, qx::verbosity::log, CatLoggerTestFileWide, QXT("Hello world"));
        check_line(*it++, qx::verbosity::log, CatLoggerTestFileWide, QXT("The answer is 42"));

        check_line(*it++, qx::verbosity::log, CatLoggerTest, QXT("Hello world"));
        check_line(*it++, qx::verbosity::log, CatLoggerTest, QXT("Hello world"));
        check_line(*it++, qx::verbosity::log, CatLoggerTest, QXT("The answer is 42"));

        check_line(*it++, qx::verbosity::log, CatDefault, QXT("Hello world"));
        check_line(*it++, qx::verbosity::log, CatDefault, QXT("Hello world"));
        check_line(*it++, qx::verbosity::log, CatDefault, QXT("The answer is 42"));

        EXPECT_EQ(it, lines.end());

        traits_t::tear_down();
    }

private:
    static void check_line(
        qx::string_view     svLine,
        qx::verbosity       eVerbosity,
        const qx::category& category,
        qx::string_view     svMessage)
    {
        qx::string sPattern;

        // verbosity
        switch (eVerbosity)
        {
        case qx::verbosity::very_verbose:
            sPattern += QXT("\\[VV\\]");
            break;

        case qx::verbosity::verbose:
            sPattern += QXT("\\[V\\]");
            break;

        case qx::verbosity::log:
            sPattern += QXT("   ");
            break;

        case qx::verbosity::important:
            sPattern += QXT("\\[I\\]");
            break;

        case qx::verbosity::warning:
            sPattern += QXT("\\[W\\]");
            break;

        case qx::verbosity::error:
            sPattern += QXT("\\[E\\]");
            break;

        case qx::verbosity::critical:
            sPattern += QXT("\\[C\\]");
            break;

        case qx::verbosity::none:
            sPattern += QXT("   ");
            break;
        }

        // date + time
        sPattern += QXT("\\[\\d{2}.\\d{2}.\\d{4}_\\d{2}:\\d{2}:\\d{2}\\]");

        // category
        if (category != CatDefault)
        {
            sPattern += QXT("\\[");
            sPattern += category.get_name();
            sPattern += QXT("\\]");
        }

        // message
        sPattern += QXT(" ");
        sPattern += svMessage;

        std::match_results<qx::string::const_pointer> match;
        auto                                          regex = std::basic_regex(sPattern.data());
        EXPECT_TRUE(std::regex_search(std::basic_string(svLine).c_str(), match, regex))
            << "regex: " << qx::to_cstring(sPattern) << std::endl
            << "line:  " << qx::to_cstring(svLine) << std::endl;
    }
};

TYPED_TEST_SUITE(logger_test, implementations_type);

TYPED_TEST(logger_test, main)
{
    // file category
    QX_LOG(qx::verbosity::log, "Hello world");
    QX_LOG(qx::verbosity::log, "Hello {}", QXT("world"));
    QX_LOG(qx::verbosity::log, "The {} is {}", QXT("answer"), 42);

    // manual category
    QX_LOG_C(CatLoggerTest, qx::verbosity::log, "Hello world");
    QX_LOG_C(CatLoggerTest, qx::verbosity::log, "Hello {}", QXT("world"));
    QX_LOG_C(CatLoggerTest, qx::verbosity::log, "The {} is {}", QXT("answer"), 42);

    // manual default category ([CatDefault] must not appear)
    QX_LOG_C(CatDefault, qx::verbosity::log, "Hello world");
    QX_LOG_C(CatDefault, qx::verbosity::log, "Hello {}", QXT("world"));
    QX_LOG_C(CatDefault, qx::verbosity::log, "The {} is {}", QXT("answer"), 42);
}
