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

#include <qx/logger_worker.h>
#include <regex>

template <
    const char sLogsFolder[],
    const char sLogsFile[],
    const char sUnit[],
    const char sTraceFile[],
    const char sTag[]
>
struct LoggerTraits
{
    constexpr static auto GetLogsFolder() { return sLogsFolder; }
    constexpr static auto GetLogsFile()   { return sLogsFile;   }
    constexpr static auto GetUnit()       { return sUnit;       }
    constexpr static auto GetTraceFile()  { return sTraceFile;  }
    constexpr static const char* GetTag() { return qx::meta::strlen(sTag) == 0 ? nullptr : sTag; }
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

constexpr const char TRACE_TAG_NULLPTR[] = "";
constexpr const char TRACE_TAG_TAG1[]    = "tag1";
constexpr const char TRACE_TAG_TAG2[]    = "tag2";

using Implementations = ::testing::Types
<
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_NULLPTR>,

    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_FILE,    TRACE_FILE_H, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_FUNC,    TRACE_FILE_H, TRACE_TAG_NULLPTR>,

    LoggerTraits<LOGS_FOLDER_LOGS, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_KEKW, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_NULLPTR>,

    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_CPP, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_INL, TRACE_TAG_NULLPTR>,

    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_TAG1>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_TAG2>
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
        std::filesystem::remove(m_sLogFilePath.data());

        auto configure_logger = [](std::unique_ptr<qx::logger>& pLogger)
        {
            pLogger->set_logs_folder(Traits::GetLogsFolder());
            pLogger->deregister_unit(qx::logger::DEFAULT_UNIT);
            pLogger->register_unit(
                Traits::GetUnit(),
                { Traits::GetLogsFile(), qx::logger::level::none, qx::logger::level::info });

            if constexpr (Traits::GetTag() && qx::meta::strcmp(TRACE_TAG_TAG1, Traits::GetTag()) == 0)
            {
                pLogger->register_unit(
                    Traits::GetTag(),
                    {
                        Traits::GetLogsFile(),
                        qx::logger::level::none,
                        qx::logger::level::info,
                        [](qx::string         & sMsg,
                           qx::string         & sFormat,
                           qx::logger::level,
                           const char         * pszFormat,
                           const char         *,
                           const char         * pszTag,
                           const char         *,
                           const char         *,
                           int,
                           va_list              args)
                        {
                            sMsg.vsprintf(pszFormat, args);
                            qx::logger::format_time_string(sFormat);
                            sMsg = qx::string("[I][") + sFormat + "][" + pszTag + "] " + sMsg + '\n';
                        }
                    }
                );
            }
        };

        m_pLogger = std::make_unique<qx::logger>();
        configure_logger(m_pLogger);

        std::unique_ptr<qx::logger> pLogger = std::make_unique<qx::logger>();
        configure_logger(pLogger);
        m_pLoggerWorker = std::make_unique<qx::logger_worker>(std::move(pLogger));
        m_pLoggerWorker->set_check_period(std::chrono::minutes(1));
        m_pLoggerWorker->set_check_period(std::chrono::seconds(1));
        m_pLoggerWorker->set_check_period(std::chrono::microseconds(1));
        m_pLoggerWorker->set_check_period(std::chrono::microseconds(500));
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
            constexpr const char* pszDate   = "\\[\\d{2}-\\d{2}-\\d{4}_";
            constexpr const char* pszTime   = "\\d{2}-\\d{2}-\\d{2}\\]";

            auto CheckRegex = [
                &regex,
                &match
            ]
                (const qx::string& sMatch, const std::string& sText)
            {
                regex = std::regex(sMatch.data());
                EXPECT_TRUE(std::regex_search(sText, match, regex))
                    << "regex:           " << sMatch.data() << std::endl
                    << "line:            " << sText.data() << std::endl
                    << "logs folder:     " << Traits::GetLogsFolder() << std::endl
                    << "logs file:       " << Traits::GetLogsFile() << std::endl
                    << "logs unit:       " << Traits::GetUnit() << std::endl
                    << "logs trace file: " << Traits::GetTraceFile();
            };

            auto CheckStringCommon = [
                &sFormat,
                &sFile,
                &ifs,
                &sLine,
                &CheckRegex,
                &pszDate,
                &pszTime
            ]
                (const char* pszStringStarting, const char* pszStringEnding)
            {
                sFile.sprintf("\\[%s::", Traits::GetTraceFile());
                constexpr const char* pszFunc = "(.*?)"; // compiler-dependent
                constexpr const char* pszLine = "\\(\\d+\\)\\]";

                sFormat.sprintf(
                    "%s%s%s%s%s%s%s",
                    pszStringStarting,
                    pszDate,
                    pszTime,
                    sFile.data(),
                    pszFunc,
                    pszLine,
                    pszStringEnding);

                ifs.getline(sLine.data(), static_cast<std::streamsize>(sLine.size()));
                CheckRegex(sFormat, sLine);
            };

            auto CheckStringTag = [
                &sFormat,
                &ifs,
                &sLine,
                &CheckRegex,
                &pszInfo,
                &pszDate,
                &pszTime
            ]
                (const char* pszStringEnding)
            {
                sFormat.sprintf(
                    "%s%s%s\\[%s\\]%s",
                    pszInfo,
                    pszDate,
                    pszTime,
                    Traits::GetTag(),
                    pszStringEnding);

                ifs.getline(sLine.data(), static_cast<std::streamsize>(sLine.size()));
                CheckRegex(sFormat, sLine);
            };

            CheckStringCommon(pszInfo,    " Start test");

            CheckStringCommon(pszInfo,    " 1.000000");
            CheckStringCommon(pszInfo,    " 1.000000 1");
            CheckStringCommon(pszInfo,    " 1.000000 2");
            CheckStringCommon(pszInfo,    " 1.000000 3");
            CheckStringCommon(pszInfo,    " 1.000000 4");
            CheckStringCommon(pszInfo,    " 1.000000 5");

            CheckStringCommon(pszError,   " 1.000000 1");
            CheckStringCommon(pszError,   " 1.000000 2");
            CheckStringCommon(pszError,   " 1.000000 3");
            CheckStringCommon(pszError,   " 1.000000 4");
            CheckStringCommon(pszError,   " 1.000000 5");

            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 1");
            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 2");
            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 3");
            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 4");
            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 5");

            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 1 three");
            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 2 three");
            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 3 three");
            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 4 three");
            CheckStringCommon(pszAssert,  "\\[false\\] 1.000000 5 three");

            if constexpr (Traits::GetTag() && qx::meta::strcmp(TRACE_TAG_TAG1, Traits::GetTag()) == 0)
            {
                CheckStringTag(" 1.000000");
                CheckStringTag(" 1.000000 1");
                CheckStringTag(" 1.000000 2");
                CheckStringTag(" 1.000000 3");
                CheckStringTag(" 1.000000 4");
                CheckStringTag(" 1.000000 5");
            }
            else
            {
                CheckStringCommon(pszInfo, " 1.000000");
                CheckStringCommon(pszInfo, " 1.000000 1");
                CheckStringCommon(pszInfo, " 1.000000 2");
                CheckStringCommon(pszInfo, " 1.000000 3");
                CheckStringCommon(pszInfo, " 1.000000 4");
                CheckStringCommon(pszInfo, " 1.000000 5");
            }

            CheckStringCommon(pszInfo,    " End test");

            ifs.close();

            std::error_code ec;
            EXPECT_TRUE(std::filesystem::remove(m_sLogFilePath.data(), ec)) << ec.message().data();
        }
        else
            EXPECT_FALSE(std::filesystem::exists(m_sLogFilePath.data()));

        m_bFunction = false;
    }

protected:

    std::unique_ptr<qx::logger>         m_pLogger;
    std::unique_ptr<qx::logger_worker>  m_pLoggerWorker;
    bool                                m_bFunction     = false;
    qx::string                          m_sLogFilePath;
};

TYPED_TEST_SUITE(TestLogger, Implementations);

#define TRACE(traceFile, format, ...)                               \
    myLogger.process_output(                                        \
        qx::logger::level::info,                                    \
        format,                                                     \
        nullptr,                                                    \
        nullptr,                                                    \
        traceFile,                                                  \
        __FUNCTION__,                                               \
        __LINE__,                                                   \
        std::string_view(),                                         \
        ## __VA_ARGS__)

#define TRACE_TAG(traceFile, tag, format, ...)                      \
    myLogger.process_output(                                        \
        qx::logger::level::info,                                    \
        format,                                                     \
        nullptr,                                                    \
        tag,                                                        \
        traceFile,                                                  \
        __FUNCTION__,                                               \
        __LINE__,                                                   \
        std::string_view(),                                         \
        ## __VA_ARGS__)

#define TRACE_ERROR(traceFile, format, ...)                         \
    myLogger.process_output(                                        \
        qx::logger::level::errors,                                  \
        format,                                                     \
        nullptr,                                                    \
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
        nullptr,                                                    \
        traceFile,                                                  \
        __FUNCTION__,                                               \
        __LINE__,                                                   \
        qx::logger::auto_terminal_color::red,                       \
        ## __VA_ARGS__)

#define TEST_LOGGER(traceFile, tag)                                 \
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
    TRACE_TAG(traceFile, tag, "%f", 1.f);                           \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 1);                     \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 2);                     \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 3);                     \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 4);                     \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 5);                     \
                                                                    \
    TRACE(traceFile, "End test\n");

//----------------------------------- logger -----------------------------------

void TestLoggerFunction(
    qx::logger& myLogger,
    const char* pszTraceFile,
    const char* pszTag)
{
    TEST_LOGGER(pszTraceFile, pszTag)
}

TYPED_TEST(TestLogger, logger_function)
{
    TestLoggerFunction(*TestFixture::m_pLogger, TypeParam::GetTraceFile(), TypeParam::GetTag());
    TestFixture::m_bFunction = true;
}

TYPED_TEST(TestLogger, logger_method)
{
    auto& myLogger = *TestFixture::m_pLogger;
    TEST_LOGGER(TypeParam::GetTraceFile(), TypeParam::GetTag())
}

TYPED_TEST(TestLogger, logger_lambda)
{
    auto TestLoggerLambda = [](auto& myLogger)
    {
        TEST_LOGGER(TypeParam::GetTraceFile(), TypeParam::GetTag())
    };

    TestLoggerLambda(*TestFixture::m_pLogger);
}

//-------------------------------- logger_worker -------------------------------

void TestLoggerFunction(
    qx::logger_worker& myLogger,
    const char       * pszTraceFile,
    const char       * pszTag)
{
    TEST_LOGGER(pszTraceFile, pszTag)
}

TYPED_TEST(TestLogger, logger_worker_function)
{
    TestFixture::m_pLoggerWorker->thread_start();
    TestLoggerFunction(*TestFixture::m_pLoggerWorker.get(), TypeParam::GetTraceFile(), TypeParam::GetTag());
    TestFixture::m_bFunction = true;
    TestFixture::m_pLoggerWorker->thread_terminate();
}

TYPED_TEST(TestLogger, logger_worker_method)
{
    TestFixture::m_pLoggerWorker->thread_start();
    auto& myLogger = *TestFixture::m_pLoggerWorker.get();
    TEST_LOGGER(TypeParam::GetTraceFile(), TypeParam::GetTag())
    TestFixture::m_pLoggerWorker->thread_terminate();
}

TYPED_TEST(TestLogger, logger_worker_lambda)
{
    TestFixture::m_pLoggerWorker->thread_start();
    auto TestLoggerWorkerLambda = [](auto& myLogger)
    {
        TEST_LOGGER(TypeParam::GetTraceFile(), TypeParam::GetTag())
    };
    TestLoggerWorkerLambda(*TestFixture::m_pLoggerWorker.get());
    TestFixture::m_pLoggerWorker->thread_terminate();
}


#endif