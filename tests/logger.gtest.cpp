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
        EXPECT_TRUE(!std::filesystem::exists(k_svLogFileName));
    }

    static qx::string get_content()
    {
        qx::logger_singleton::get_instance().get_logger().flush();
        qx::logger_singleton::get_instance().get_logger().reset();

        EXPECT_TRUE(std::filesystem::exists(k_svLogFileName));
        std::basic_ifstream<qx::char_type> file(qx::string(k_svLogFileName).c_str());
        QX_DISABLE_MSVC_WARNINGS(4996);
        file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
        QX_RESTORE_MSVC_WARNINGS(4996);

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
    static inline int s_old_out = -1;
    static inline int s_old_err = -1;

#if QX_WIN
    // Windows uses two separate ints for pipe ends
    static inline int s_pipe_r = -1;
    static inline int s_pipe_w = -1;

    // Previous text modes (used when wchar_t is active)
    static inline int s_old_mode_out = -1;
    static inline int s_old_mode_err = -1;
#else
    // POSIX pipe: [0] = read end, [1] = write end
    static inline int s_pipefd[2] = { -1, -1 };
#endif

    static inline bool s_active = false;

    // Redirect stdout and stderr into a single pipe
    static void set_up()
    {
        if (s_active)
            throw std::runtime_error("base_cout capture already active");

        std::fflush(stdout);
        std::fflush(stderr);

        // Save original stdout/stderr descriptors
        s_old_out = __dup(__fileno(stdout));
        s_old_err = __dup(__fileno(stderr));
        if (s_old_out < 0 || s_old_err < 0)
            throw std::runtime_error("dup failed");

#if QX_WIN
        // Create binary pipe (no CR/LF or encoding conversion)
        int fds[2];
        if (__pipe(fds, 1 << 16, _O_BINARY) != 0)
            throw std::runtime_error("_pipe failed");

        s_pipe_r = fds[0];
        s_pipe_w = fds[1];

        // Redirect both stdout and stderr to the same pipe
        if (__dup2(s_pipe_w, __fileno(stdout)) != 0)
            throw std::runtime_error("dup2 stdout failed");
        if (__dup2(s_pipe_w, __fileno(stderr)) != 0)
            throw std::runtime_error("dup2 stderr failed");

        // If wchar_t is used, switch CRT to UTF-16 text mode
        if constexpr (std::is_same_v<qx::char_type, wchar_t>)
        {
            s_old_mode_out = _setmode(__fileno(stdout), _O_U16TEXT);
            s_old_mode_err = _setmode(__fileno(stderr), _O_U16TEXT);
        }
#else
        // Create POSIX pipe
        if (::pipe(s_pipefd) != 0)
            throw std::runtime_error("pipe failed");

        // Redirect both stdout and stderr to the same pipe
        if (__dup2(s_pipefd[1], STDOUT_FILENO) < 0)
            throw std::runtime_error("dup2 stdout failed");
        if (__dup2(s_pipefd[1], STDERR_FILENO) < 0)
            throw std::runtime_error("dup2 stderr failed");
#endif

        s_active = true;
    }

    // Restore stdout/stderr and return captured output
    static qx::string get_content()
    {
        if (!s_active)
            return {};

        std::fflush(stdout);
        std::fflush(stderr);

#if QX_WIN
        // Restore previous text mode if wchar_t was used
        if constexpr (std::is_same_v<qx::char_type, wchar_t>)
        {
            if (s_old_mode_out != -1)
                _setmode(__fileno(stdout), s_old_mode_out);
            if (s_old_mode_err != -1)
                _setmode(__fileno(stderr), s_old_mode_err);
        }

        // Restore original stdout/stderr
        __dup2(s_old_out, __fileno(stdout));
        __dup2(s_old_err, __fileno(stderr));
        __close(s_old_out);
        s_old_out = -1;
        __close(s_old_err);
        s_old_err = -1;

        // Close write end so read end receives EOF
        __close(s_pipe_w);
        s_pipe_w = -1;

        // Read all captured bytes
        qx::string bytes;
        bytes.reserve(4096);

        char buf[16 * 1024];
        while (true)
        {
            int n = __read(s_pipe_r, buf, (int)sizeof(buf));
            if (n > 0)
            {
                if constexpr (std::is_same_v<qx::char_type, char>)
                {
                    bytes.append(buf, buf + n);
                }
                else
                {
                    for (int i = 0; i < n; i += 2)
                    {
                        bytes.push_back(*reinterpret_cast<wchar_t*>(&buf[i]));
                    }
                }
            }
            else
            {
                break;
            }
        }

        __close(s_pipe_r);
        s_pipe_r = -1;
        s_active = false;

        // Convert to qx::string
        if constexpr (std::is_same_v<qx::char_type, char>)
        {
            return bytes;
        }
        else
        {
            // UTF-16 wchar_t stream (Windows + _O_U16TEXT)
            if (bytes.size() % sizeof(wchar_t) == 0)
            {
                const wchar_t* p = reinterpret_cast<const wchar_t*>(bytes.data());
                size_t         n = bytes.size() / sizeof(wchar_t);
                return qx::string(p, p + n);
            }

            // Fallback: byte-wise widening
            qx::string w;
            w.reserve(bytes.size());
            for (qx::char_type ch : bytes)
                w.push_back(ch);
            return w;
        }

#else
        // Restore original stdout/stderr
        __dup2(s_old_out, STDOUT_FILENO);
        __dup2(s_old_err, STDERR_FILENO);
        __close(s_old_out);
        s_old_out = -1;
        __close(s_old_err);
        s_old_err = -1;

        // Close write end to signal EOF
        __close(s_pipefd[1]);
        s_pipefd[1] = -1;

        // Read all captured bytes
        qx::string bytes;
        bytes.reserve(4096);

        char buf[16 * 1024];
        for (;;)
        {
            ssize_t n = __read(s_pipefd[0], buf, sizeof(buf));
            if (n > 0)
                bytes.append(buf, buf + (size_t)n);
            else
                break;
        }

        __close(s_pipefd[0]);
        s_pipefd[0] = -1;
        s_active    = false;

        if constexpr (std::is_same_v<qx::char_type, char>)
        {
            return bytes;
        }
        else
        {
            // On POSIX, wide output is usually already multibyte
            qx::string w;
            w.reserve(bytes.size());
            for (unsigned char ch : bytes)
                w.push_back((wchar_t)ch);
            return w;
        }
#endif
    }

    // Safety cleanup if a test exits early
    static void tear_down()
    {
        if (!s_active)
            return;

        std::fflush(stdout);
        std::fflush(stderr);

#if QX_WIN
        if constexpr (std::is_same_v<qx::char_type, wchar_t>)
        {
            if (s_old_mode_out != -1)
                _setmode(__fileno(stdout), s_old_mode_out);
            if (s_old_mode_err != -1)
                _setmode(__fileno(stderr), s_old_mode_err);
        }

        if (s_old_out != -1)
        {
            __dup2(s_old_out, __fileno(stdout));
            __close(s_old_out);
            s_old_out = -1;
        }

        if (s_old_err != -1)
        {
            __dup2(s_old_err, __fileno(stderr));
            __close(s_old_err);
            s_old_err = -1;
        }

        if (s_pipe_w != -1)
        {
            __close(s_pipe_w);
            s_pipe_w = -1;
        }
        if (s_pipe_r != -1)
        {
            __close(s_pipe_r);
            s_pipe_r = -1;
        }
#else
        if (s_old_out != -1)
        {
            __dup2(s_old_out, STDOUT_FILENO);
            __close(s_old_out);
            s_old_out = -1;
        }

        if (s_old_err != -1)
        {
            __dup2(s_old_err, STDERR_FILENO);
            __close(s_old_err);
            s_old_err = -1;
        }

        if (s_pipefd[1] != -1)
        {
            __close(s_pipefd[1]);
            s_pipefd[1] = -1;
        }
        if (s_pipefd[0] != -1)
        {
            __close(s_pipefd[0]);
            s_pipefd[0] = -1;
        }
#endif

        s_active = false;
    }
};
struct cout : base_cout
{
    static void set_up()
    {
        base_cout::set_up();
        qx::logger_singleton::get_instance().get_logger().add_stream(
            qx::cout_logger_stream(qx::cout_logger_stream::config { { .bUseColors = false } }));
    }
};

struct fwrite : base_cout
{
    static void set_up()
    {
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
            << "regex: " << qx::to_cstring(sPattern).c_str() << std::endl
            << "line:  " << qx::to_cstring(svLine).c_str() << std::endl;
    }
};

TYPED_TEST_SUITE(logger_test, implementations_type);

TYPED_TEST(logger_test, main)
{
    // file category
    QX_LOG(qx::verbosity::log, "Hello world");
    QX_LOG(qx::verbosity::log, "Hello {}", TEXT("world"));
    QX_LOG(qx::verbosity::log, "The {} is {}", TEXT("answer"), 42);

    // manual category
    QX_LOG_C(CatLoggerTest, qx::verbosity::log, "Hello world");
    QX_LOG_C(CatLoggerTest, qx::verbosity::log, "Hello {}", TEXT("world"));
    QX_LOG_C(CatLoggerTest, qx::verbosity::log, "The {} is {}", TEXT("answer"), 42);

    // manual default category ([CatDefault] must not appear)
    QX_LOG_C(CatDefault, qx::verbosity::log, "Hello world");
    QX_LOG_C(CatDefault, qx::verbosity::log, "Hello {}", TEXT("world"));
    QX_LOG_C(CatDefault, qx::verbosity::log, "The {} is {}", TEXT("answer"), 42);
}
