//==============================================================================
//
//!\file                        test_logger.cpp
//
//!\brief       Tests for qx::logger
//!\details     ~
//
//!\author      Khrapov
//!\date        27.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_logger.cpp

#if QX_TEST_LOGGER

#include <qx/logger.h>
#include <gtest/gtest.h>
#include <regex>

template <
    const char sLogsFolder[],
    const char sLogsFile[],
    const char sUnit[],
    const char sTraceFile[]
>
struct LoggerTraits
{
    constexpr static auto GetLogsFolder() { return sLogsFolder; }
    constexpr static auto GetLogsFile()   { return sLogsFile;   }
    constexpr static auto GetUnit()       { return sUnit;       }
    constexpr static auto GetTraceFile()  { return sTraceFile;  }
};

constexpr const char LOGS_FOLDER_ROOT[]  = "";
constexpr const char LOGS_FOLDER_LOGS[]  = "logs";
constexpr const char LOGS_FOLDER_KEKW[]  = "KEKW";

constexpr const char LOGS_FILE_DEFAULT[] = "default.log";

constexpr const char UNIT_DEFAULT[]      = "default";
constexpr const char UNIT_FILE[]         = "file.h";
constexpr const char UNIT_FUNC[]         = "TestLoggerFunction";

constexpr const char TRACE_FILE_H[]      = "file.h";
constexpr const char TRACE_FILE_CPP[]    = "file.cpp";
constexpr const char TRACE_FILE_INL[]    = "file.inl";


using Implementations = ::testing::Types
<
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H>,

    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_FILE,    TRACE_FILE_H>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_FUNC,    TRACE_FILE_H>,

    LoggerTraits<LOGS_FOLDER_LOGS, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H>,
    LoggerTraits<LOGS_FOLDER_KEKW, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H>,

    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_CPP>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_INL>
>;


//==============================================================================
//
//!\class                      TestLogger<Traits>
//
//!\brief   Test class for logger
//!\details ~
//
//!\author  Khrapov
//!\date    6.10.2020
//
//==============================================================================
template <typename Traits>
class TestLogger : public ::testing::Test
{
protected:

    /* init protected members here */
    TestLogger()
    {
        m_sLogFilePath = Traits::GetLogsFolder();
        if (!m_sLogFilePath.empty())
        {
            m_sLogFilePath += '/';
            m_sLogFilePath += Traits::GetLogsFile();
        }
        else
            m_sLogFilePath = Traits::GetLogsFile();
    }

    /* called before every test */
    void SetUp()
    {
        std::error_code ec;
        std::filesystem::remove(m_sLogFilePath.data(), ec);

        m_Logger = qx::logger();
        m_Logger.set_logs_folder(Traits::GetLogsFolder());
        m_Logger.deregister_unit("default");
        m_Logger.register_unit(Traits::GetUnit(), { Traits::GetLogsFile(), qx::logger::level::none, qx::logger::level::info });
    }

    /* called after every test */
    void TearDown()
    {
        if (std::strcmp(Traits::GetUnit(), UNIT_DEFAULT) == 0
         || std::strcmp(Traits::GetUnit(), UNIT_FILE) == 0 && std::strcmp(Traits::GetUnit(), Traits::GetTraceFile()) == 0
         || std::strcmp(Traits::GetUnit(), UNIT_FUNC) == 0 && m_bFunction)
        {
            ASSERT_TRUE(std::filesystem::exists(m_sLogFilePath.data()));
            std::ifstream ifs(m_sLogFilePath.data());

            std::string sLine(512, '\0');
            std::smatch match;
            qx::string  sFormat;
            std::regex  regex;
            qx::string  sFile;

            constexpr const char* pszInfo   = "\\[I\\]";
            constexpr const char* pszError  = "\\[E\\]";
            constexpr const char* pszAssert = "\\[A\\]";

            auto CheckString = [
                &sFormat,
                &sFile,
                &regex,
                &ifs,
                &sLine,
                &match]
                (const char* pszStringStarting, const char* pszStringEnding)
            {
                constexpr const char* pszDate = "\\[\\d{2}-\\d{2}-\\d{4}_";
                constexpr const char* pszTime = "\\d{2}-\\d{2}-\\d{2}\\]";
                sFile.format("\\[%s::", Traits::GetTraceFile());
                constexpr const char* pszFunc = "(.*?)"; // compiler-dependent
                constexpr const char* pszLine = "\\(\\d+\\)\\]";

                sFormat.format(
                    "%s%s%s%s%s%s%s",
                    pszStringStarting,
                    pszDate,
                    pszTime,
                    sFile.data(),
                    pszFunc,
                    pszLine,
                    pszStringEnding);

                regex = std::regex(sFormat.data());
                ifs.getline(sLine.data(), sLine.size());
                EXPECT_TRUE(std::regex_search(sLine, match, regex))
                    << "regex:           " << sFormat.data()            << std::endl
                    << "line:            " << sLine.data()              << std::endl
                    << "logs folder:     " << Traits::GetLogsFolder()   << std::endl
                    << "logs file:       " << Traits::GetLogsFile()     << std::endl
                    << "logs unit:       " << Traits::GetUnit()         << std::endl
                    << "logs trace file: " << Traits::GetTraceFile();
            };

            CheckString(pszInfo,    " Start test");
            CheckString(pszInfo,    " 1.000000");
            CheckString(pszInfo,    " 1.000000 1");
            CheckString(pszInfo,    " 1.000000 2");
            CheckString(pszInfo,    " 1.000000 3");
            CheckString(pszInfo,    " 1.000000 4");
            CheckString(pszInfo,    " 1.000000 5");
            CheckString(pszError,   " 1.000000 1");
            CheckString(pszError,   " 1.000000 2");
            CheckString(pszError,   " 1.000000 3");
            CheckString(pszError,   " 1.000000 4");
            CheckString(pszError,   " 1.000000 5");
            CheckString(pszAssert,  "\\[false\\] 1.000000 1");
            CheckString(pszAssert,  "\\[false\\] 1.000000 2");
            CheckString(pszAssert,  "\\[false\\] 1.000000 3");
            CheckString(pszAssert,  "\\[false\\] 1.000000 4");
            CheckString(pszAssert,  "\\[false\\] 1.000000 5");
            CheckString(pszAssert,  "\\[false\\] 1.000000 1 three");
            CheckString(pszAssert,  "\\[false\\] 1.000000 2 three");
            CheckString(pszAssert,  "\\[false\\] 1.000000 3 three");
            CheckString(pszAssert,  "\\[false\\] 1.000000 4 three");
            CheckString(pszAssert,  "\\[false\\] 1.000000 5 three");
            CheckString(pszInfo,    " End test");

            ifs.close();

            std::error_code ec;
            EXPECT_TRUE(std::filesystem::remove(m_sLogFilePath.data(), ec)) << ec.message().data();
        }
        else
            EXPECT_FALSE(std::filesystem::exists(m_sLogFilePath.data()));

        m_bFunction = false;
    }

protected:

    qx::logger      m_Logger;
    bool            m_bFunction     = false;
    qx::string      m_sLogFilePath;
};

TYPED_TEST_SUITE(TestLogger, Implementations);

#define TRACE(traceFile, format, ...)                               \
    myLogger.process_output(                                        \
        qx::logger::level::info,                                    \
        format,                                                     \
        nullptr,                                                    \
        traceFile,                                                  \
        __FUNCTION__,                                               \
        __LINE__,                                                   \
        nullptr,                                                    \
        ## __VA_ARGS__)

#define TRACE_ERROR(traceFile, format, ...)                         \
    myLogger.process_output(                                        \
        qx::logger::level::errors,                                  \
        format,                                                     \
        nullptr,                                                    \
        traceFile,                                                  \
        __FUNCTION__,                                               \
        __LINE__,                                                   \
        qx::logger::auto_terminal_color::yellow,                    \
        ## __VA_ARGS__)

#define TRACE_ASSERT(traceFile, expr, format, ...)                  \
    myLogger.process_output(                                        \
        qx::logger::level::asserts,                                 \
        format,                                                     \
        # expr,                                                     \
        traceFile,                                                  \
        __FUNCTION__,                                               \
        __LINE__,                                                   \
        qx::logger::auto_terminal_color::red,                       \
        ## __VA_ARGS__)

#define TEST_LOGGER(traceFile)                                      \
    TRACE(traceFile, "Start test");                                 \
                                                                    \
    TRACE(traceFile, "%f", 1.f);                                    \
    TRACE(traceFile, "%f %d", 1.f, 1);                              \
    TRACE(traceFile, "%f %d", 1.f, 2);                              \
    TRACE(traceFile, "%f %d", 1.f, 3);                              \
    TRACE(traceFile, "%f %d", 1.f, 4);                              \
    TRACE(traceFile, "%f %d", 1.f, 5);                              \
                                                                    \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 1);                        \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 2);                        \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 3);                        \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 4);                        \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 5);                        \
                                                                    \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 1);                \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 2);                \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 3);                \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 4);                \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 5);                \
                                                                    \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 1, "three");    \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 2, "three");    \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 3, "three");    \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 4, "three");    \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 5, "three");    \
                                                                    \
    TRACE(traceFile, "End test\n");

void TestLoggerFunction(qx::logger& myLogger, const char* pszTraceFile)
{
    TEST_LOGGER(pszTraceFile)
}

TYPED_TEST(TestLogger, function)
{
    TestLoggerFunction(TestFixture::m_Logger, TypeParam::GetTraceFile());
    TestFixture::m_bFunction = true;
}

TYPED_TEST(TestLogger, method)
{
    auto& myLogger = TestFixture::m_Logger;
    TEST_LOGGER(TypeParam::GetTraceFile())
}

TYPED_TEST(TestLogger, lambda)
{
    auto TestLoggerLambda = [](auto& myLogger)
    {
        TEST_LOGGER(TypeParam::GetTraceFile())
    };

    TestLoggerLambda(TestFixture::m_Logger);
}

#endif