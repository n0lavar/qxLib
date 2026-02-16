/**

    @file      logger.gtest.cpp
    @author    Khrapov
    @date      19.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

#define QX_DEBUG_BREAK() (void)0

#include <qx/logger/logger.h>

#include <qx/logger/cout_logger_stream.h>
#include <qx/logger/debugger_logger_stream.h>
#include <qx/logger/file_logger_stream_fopen.h>
#include <qx/logger/file_logger_stream_mapping.h>
#include <qx/logger/file_logger_stream_ofstream.h>
#include <qx/logger/fwrite_logger_stream.h>
#include <qx/macros/asserts/asserts.h>
#include <qx/macros/asserts/error_context.h>
#include <qx/macros/asserts/error_context_stream.h>

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

//V_EXCLUDE_PATH *.gtest.cpp

QX_DEFINE_CATEGORY(CatLoggerTest);
QX_DEFINE_CATEGORY(CatLoggerTestLogVerbosity);
QX_DEFINE_CATEGORY(CatLoggerTestFileWide);
QX_DEFINE_CATEGORY(CatErrorContextTest);
QX_SET_FILE_CATEGORY(CatLoggerTestFileWide);

static_assert(qx::sbo_poly_fittable_types_v<
              qx::logger::logger_sbo,
              qx::cout_logger_stream,
              qx::file_logger_stream_fopen,
              qx::file_logger_stream_mapping,
              qx::file_logger_stream_ofstream,
              qx::fwrite_logger_stream,
              qx::debugger_logger_stream,
              qx::error_context_stream>);

constexpr qx::string_view k_svLogFileName = QXT("logger_output_test.log");

QX_CALL_BEFORE_MAIN = []()
{
    if (std::filesystem::exists(k_svLogFileName))
        std::filesystem::remove(k_svLogFileName);
};

namespace traits
{

struct base_traits
{
    static constexpr bool bResetTestOnStart = true;

    static qx::string get_color_regex(bool bOptional = false)
    {
        return {};
    }
};

struct base_file : base_traits
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

struct base_cout : base_traits
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
            qx::cout_logger_stream(qx::cout_logger_stream::config { {}, false, false }));
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
            qx::fwrite_logger_stream(qx::fwrite_logger_stream::config()));
    }
};

struct cout_colors : base_cout
{
    static qx::string get_color_regex(bool bOptional = false)
    {
        return qx::string(QXT("(\x1B(?:[@-Z\\-_]|\\[[0-?]*[ -\\/]*[@-~]))")) + (bOptional ? QXT("?") : QXT(""));
    }

    static void set_up()
    {
        // On POSIX, cout outputs always use char
#if !QX_WIN
        s_bCharOutput = true;
#endif

        base_cout::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(
            qx::cout_logger_stream(qx::cout_logger_stream::config { { .bUseColors = true }, false, false }));
    }
};

struct fwrite_colors : base_cout
{
    static qx::string get_color_regex(bool bOptional = false)
    {
#if QX_WIN
        return qx::string(QXT("(\x1B(?:[@-Z\\-_]|\\[[0-?]*[ -\\/]*[@-~]))")) + (bOptional ? QXT("?") : QXT(""));
#else
        // linux (?) doesn't capture colors in fwrite stream
        return {};
#endif
    }

    static void set_up()
    {
#if !QX_WIN
        s_bCharOutput = false;
#endif

        base_cout::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(
            qx::fwrite_logger_stream(qx::fwrite_logger_stream::config({ .bUseColors = true })));
    }
};

struct default_constructed : base_cout
{
    static constexpr bool bResetTestOnStart = false;

    static void set_up()
    {
#if !QX_WIN
        s_bCharOutput = false;
#endif

        base_cout::set_up();
        // default constructed logger should have fwrite_logger_stream inside and be ready to be used
    }
};

} // namespace traits

using implementations_type = ::testing::Types<
    traits::default_constructed,
    traits::ostream_default_buffer,
    traits::ostream,
    traits::fopen_default_buffer,
    traits::fopen,
    traits::mapping_default_initial_size,
    traits::mapping,
    traits::cout,
    traits::fwrite,
    traits::cout_colors,
    traits::fwrite_colors>;

template<class traits_t>
class logger_output_test : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        if constexpr (traits_t::bResetTestOnStart)
            qx::get_logger().reset();

        qx::get_logger().register_category(CatLoggerTestFileWide, { .eRuntimeVerbosity = qx::verbosity::detailed });
        traits_t::set_up();
    }

    virtual void TearDown() override
    {
        qx::get_logger().flush();

        const qx::string             sContent = traits_t::get_content();
        std::vector<qx::string_view> lines    = sContent.split(QXT('\n'));
        for (qx::string_view& svLine : lines)
            if (svLine.ends_with(QXT('\r')))
                svLine.remove_suffix(1);

        m_CheckContent(lines);

        traits_t::tear_down();
    }

protected:
    static void check_line(
        qx::string_view     svLine,
        qx::verbosity       eVerbosity,
        const qx::category& category,
        qx::string_view     svMessage,
        bool                bOptionalColor = false)
    {
        qx::string sPattern = traits_t::get_color_regex(bOptionalColor); // line color

        // verbosity
        switch (eVerbosity)
        {
        case qx::verbosity::detailed:
            sPattern += QXT("\\[D\\]");
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
            sPattern += traits_t::get_color_regex(bOptionalColor); // reset
            sPattern += traits_t::get_color_regex(bOptionalColor); // category color
            sPattern += category.get_name();
            sPattern += traits_t::get_color_regex(bOptionalColor); // reset
            sPattern += traits_t::get_color_regex(bOptionalColor); // line color
            sPattern += QXT("\\]");
        }

        // message
        sPattern += QXT(" ");
        sPattern += svMessage;
        sPattern += traits_t::get_color_regex(true); // reset (can be absent in multiline log messages)

        std::match_results<qx::string::const_pointer> match;
        auto                                          regex = std::basic_regex(sPattern.data());
        EXPECT_TRUE(std::regex_search(std::basic_string(svLine).c_str(), match, regex))
            << "regex: " << qx::to_cstring(sPattern) << std::endl
            << "line:  " << qx::to_cstring(svLine) << std::endl;
    }

protected:
    std::function<void(std::span<const qx::string_view> lines)> m_CheckContent;
};

TYPED_TEST_SUITE(logger_output_test, implementations_type);

TYPED_TEST(logger_output_test, categories)
{
    // file category
    QX_LOG(qx::verbosity::log, "Categories check 1");

    // manual category
    QX_LOG_C(CatLoggerTest, qx::verbosity::log, "Categories check 2");

    // manual default category ([CatDefault] must not appear)
    QX_LOG_C(CatDefault, qx::verbosity::log, "Categories check 3");

    this->m_CheckContent = [](std::span<const qx::string_view> lines)
    {
        auto it = lines.begin();

        TestFixture::check_line(*it++, qx::verbosity::log, CatLoggerTestFileWide, QXT("Categories check 1"));
        TestFixture::check_line(*it++, qx::verbosity::log, CatLoggerTest, QXT("Categories check 2"));
        TestFixture::check_line(*it++, qx::verbosity::log, CatDefault, QXT("Categories check 3"));

        EXPECT_EQ(it, lines.end());
    };
}

TYPED_TEST(logger_output_test, verbosity)
{
    qx::get_logger().register_category(CatLoggerTestLogVerbosity, { .eRuntimeVerbosity = qx::verbosity::log });

    QX_LOG(qx::verbosity::detailed, "Verbosity check 1");
    QX_LOG(qx::verbosity::verbose, "Verbosity check 2");
    QX_LOG(qx::verbosity::log, "Verbosity check 3");
    QX_LOG(qx::verbosity::important, "Verbosity check 4");
    QX_LOG(qx::verbosity::warning, "Verbosity check 5");
    QX_LOG(qx::verbosity::error, "Verbosity check 6");
    QX_LOG(qx::verbosity::critical, "Verbosity check 7");

    QX_LOG_C(CatLoggerTestLogVerbosity, qx::verbosity::detailed, "Verbosity check 8");
    QX_LOG_C(CatLoggerTestLogVerbosity, qx::verbosity::verbose, "Verbosity check 9");
    QX_LOG_C(CatLoggerTestLogVerbosity, qx::verbosity::log, "Verbosity check 10");
    QX_LOG_C(CatLoggerTestLogVerbosity, qx::verbosity::important, "Verbosity check 11");
    QX_LOG_C(CatLoggerTestLogVerbosity, qx::verbosity::warning, "Verbosity check 12");
    QX_LOG_C(CatLoggerTestLogVerbosity, qx::verbosity::error, "Verbosity check 13");
    QX_LOG_C(CatLoggerTestLogVerbosity, qx::verbosity::critical, "Verbosity check 14");

    this->m_CheckContent = [](std::span<const qx::string_view> lines)
    {
        auto it = lines.begin();

        TestFixture::check_line(*it++, qx::verbosity::detailed, CatLoggerTestFileWide, QXT("Verbosity check 1"));
        TestFixture::check_line(*it++, qx::verbosity::verbose, CatLoggerTestFileWide, QXT("Verbosity check 2"));
        TestFixture::check_line(*it++, qx::verbosity::log, CatLoggerTestFileWide, QXT("Verbosity check 3"));
        TestFixture::check_line(*it++, qx::verbosity::important, CatLoggerTestFileWide, QXT("Verbosity check 4"));
        TestFixture::check_line(*it++, qx::verbosity::warning, CatLoggerTestFileWide, QXT("Verbosity check 5"));
        TestFixture::check_line(*it++, qx::verbosity::error, CatLoggerTestFileWide, QXT("Verbosity check 6"));
        TestFixture::check_line(*it++, qx::verbosity::critical, CatLoggerTestFileWide, QXT("Verbosity check 7"));

        TestFixture::check_line(*it++, qx::verbosity::log, CatLoggerTestLogVerbosity, QXT("Verbosity check 10"));
        TestFixture::check_line(*it++, qx::verbosity::important, CatLoggerTestLogVerbosity, QXT("Verbosity check 11"));
        TestFixture::check_line(*it++, qx::verbosity::warning, CatLoggerTestLogVerbosity, QXT("Verbosity check 12"));
        TestFixture::check_line(*it++, qx::verbosity::error, CatLoggerTestLogVerbosity, QXT("Verbosity check 13"));
        TestFixture::check_line(*it++, qx::verbosity::critical, CatLoggerTestLogVerbosity, QXT("Verbosity check 14"));

        EXPECT_EQ(it, lines.end());
    };
}

TYPED_TEST(logger_output_test, formatting)
{
    QX_LOG(qx::verbosity::log, "Hello {}", QXT("world"));
    QX_LOG(qx::verbosity::log, "The {} is {}", QXT("answer"), 42);

    this->m_CheckContent = [](std::span<const qx::string_view> lines)
    {
        auto it = lines.begin();

        TestFixture::check_line(*it++, qx::verbosity::log, CatLoggerTestFileWide, QXT("Hello world"));
        TestFixture::check_line(*it++, qx::verbosity::log, CatLoggerTestFileWide, QXT("The answer is 42"));

        EXPECT_EQ(it, lines.end());
    };
}

TYPED_TEST(logger_output_test, error_context)
{
    auto& logger = qx::get_logger();
    logger.add_stream(qx::error_context_stream());
    logger.register_category(CatErrorContextTest, { .eRuntimeVerbosity = qx::verbosity::log });

    qx::error_context _(qx::verbosity::detailed);

    QX_LOG_C(CatErrorContextTest, qx::verbosity::detailed, "Check 1");
    QX_LOG_C(CatErrorContextTest, qx::verbosity::verbose, "Check 2");
    QX_LOG_C(CatErrorContextTest, qx::verbosity::log, "Check 3");
    QX_LOG_C(CatErrorContextTest, qx::verbosity::important, "Check 4");
    QX_LOG_C(CatErrorContextTest, qx::verbosity::warning, "Check 5");
    QX_LOG_C(CatErrorContextTest, qx::verbosity::error, "Check 6");
    QX_LOG_C(CatErrorContextTest, qx::verbosity::critical, "Check 7");

    QX_EXPECT_C(false, CatErrorContextTest);

    this->m_CheckContent = [](std::span<const qx::string_view> lines)
    {
        auto it = lines.begin();

        TestFixture::check_line(*it++, qx::verbosity::log, CatErrorContextTest, QXT("Check 3"));
        TestFixture::check_line(*it++, qx::verbosity::important, CatErrorContextTest, QXT("Check 4"));
        TestFixture::check_line(*it++, qx::verbosity::warning, CatErrorContextTest, QXT("Check 5"));
        TestFixture::check_line(*it++, qx::verbosity::error, CatErrorContextTest, QXT("Check 6"));
        TestFixture::check_line(*it++, qx::verbosity::critical, CatErrorContextTest, QXT("Check 7"));
        TestFixture::check_line(*it++, qx::verbosity::error, CatErrorContextTest, QXT("\\[false\\] "));
        TestFixture::check_line(*it++, qx::verbosity::log, CatDefault, QXT(""));
        EXPECT_EQ(*it++, QXT("Error context start"));
        TestFixture::check_line(*it++, qx::verbosity::detailed, CatErrorContextTest, QXT("Check 1"), true);
        TestFixture::check_line(*it++, qx::verbosity::verbose, CatErrorContextTest, QXT("Check 2"), true);
        TestFixture::check_line(*it++, qx::verbosity::log, CatErrorContextTest, QXT("Check 3"), true);
        TestFixture::check_line(*it++, qx::verbosity::important, CatErrorContextTest, QXT("Check 4"), true);
        TestFixture::check_line(*it++, qx::verbosity::warning, CatErrorContextTest, QXT("Check 5"), true);
        TestFixture::check_line(*it++, qx::verbosity::error, CatErrorContextTest, QXT("Check 6"), true);
        TestFixture::check_line(*it++, qx::verbosity::critical, CatErrorContextTest, QXT("Check 7"), true);
        TestFixture::check_line(*it++, qx::verbosity::error, CatErrorContextTest, QXT("\\[false\\] "), true);
        EXPECT_TRUE((it++)->starts_with(QXT("Error context end"))); // could have a color mark at the end

        EXPECT_EQ(it, lines.end());
    };
}

TEST(logger_test, streams)
{
    auto& logger = qx::get_logger();
    logger.reset();

    qx::cout_logger_stream* pStream = logger.get_stream<qx::cout_logger_stream>();
    EXPECT_FALSE(pStream);

    logger.add_stream(qx::cout_logger_stream());
    pStream = logger.get_stream<qx::cout_logger_stream>();
    EXPECT_TRUE(pStream);

    logger.add_stream(qx::cout_logger_stream());
    pStream = logger.get_stream<qx::cout_logger_stream>();
    EXPECT_TRUE(pStream);
    auto streams = logger.get_streams<qx::cout_logger_stream>();
    EXPECT_EQ(std::distance(streams.begin(), streams.end()), 2);

    logger.remove_streams<qx::fwrite_logger_stream>();
    pStream = logger.get_stream<qx::cout_logger_stream>();
    EXPECT_TRUE(pStream);
    streams = logger.get_streams<qx::cout_logger_stream>();
    EXPECT_EQ(std::distance(streams.begin(), streams.end()), 2);

    logger.remove_streams<qx::cout_logger_stream>();
    pStream = logger.get_stream<qx::cout_logger_stream>();
    EXPECT_FALSE(pStream);
    streams = logger.get_streams<qx::cout_logger_stream>();
    EXPECT_EQ(std::distance(streams.begin(), streams.end()), 0);
}

TEST(logger_test, terminal_colors)
{
    // just output all the colors so we can visually see that it works
    // (and improve tests coverage)
    qx::terminal_color::test_colors();
}
