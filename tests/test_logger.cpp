/**

    @file      test_logger.cpp
    @brief     Tests for qx::logger
    @author    Khrapov
    @date      27.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_logger.cpp

#include <qx/logger/logger.h>

#include <qx/logger/cout_logger_stream.h>
#include <qx/logger/file_logger_stream.h>

#include <regex>

QX_PUSH_SUPPRESS_MSVC_WARNINGS(5233)

template<
    const char sLogsFolder[],
    const char sLogsFile[],
    const char sUnit[],
    const char sTraceFile[],
    const char sTag[]>
struct LoggerTraits
{
    constexpr static std::string_view GetLogsFolder()
    {
        return sLogsFolder;
    }
    constexpr static std::string_view GetLogsFile()
    {
        return sLogsFile;
    }
    constexpr static std::string_view GetUnit()
    {
        return sUnit;
    }
    constexpr static const char* GetTraceFile()
    {
        return sTraceFile;
    }
    constexpr static const char* GetTag()
    {
        return sTag[0] == '\0' ? nullptr : sTag;
    }
};

constexpr char LOGS_FOLDER_ROOT[] = "";
constexpr char LOGS_FOLDER_LOGS[] = "logs";
constexpr char LOGS_FOLDER_KEKW[] = "KEKW";

constexpr char LOGS_FILE_DEFAULT[] = "default.log";

constexpr char UNIT_DEFAULT[] = "default";
constexpr char UNIT_FILE[]    = "file.h";
constexpr char UNIT_FUNC[]    = "TestLoggerFunction";

constexpr char TRACE_FILE_H[]   = "file.h";
constexpr char TRACE_FILE_CPP[] = "file.cpp";
constexpr char TRACE_FILE_INL[] = "file.inl";

constexpr char TRACE_TAG_NULLPTR[] = "";
constexpr char TRACE_TAG_TAG1[]    = "tag1";
constexpr char TRACE_TAG_TAG2[]    = "tag2";

using Implementations = ::testing::Types<
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_FILE, TRACE_FILE_H, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_FUNC, TRACE_FILE_H, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_LOGS, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_KEKW, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_CPP, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_INL, TRACE_TAG_NULLPTR>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_TAG1>,
    LoggerTraits<LOGS_FOLDER_ROOT, LOGS_FILE_DEFAULT, UNIT_DEFAULT, TRACE_FILE_H, TRACE_TAG_TAG2>>;

template<typename Traits>
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
    virtual void SetUp() override
    {
        std::filesystem::remove(m_sLogFilePath.data());
        m_pLogger = std::make_unique<qx::logger>();

        auto pConsoleLoggerStream = std::make_unique<qx::cout_logger_stream>();
        pConsoleLoggerStream->deregister_unit(qx::base_logger_stream::k_svDefaultUnit);
        pConsoleLoggerStream->register_unit(Traits::GetUnit(), { qx::log_level::none });

        auto pFileLoggerStream = std::make_unique<qx::file_logger_stream>();
        pFileLoggerStream->set_logs_folder(Traits::GetLogsFolder());
        pFileLoggerStream->deregister_unit(qx::base_logger_stream::k_svDefaultUnit);
        pFileLoggerStream->register_unit(Traits::GetUnit(), { qx::log_level::log });
        pFileLoggerStream->register_file(Traits::GetUnit(), Traits::GetLogsFile());

        if constexpr (Traits::GetTag() == TRACE_TAG_TAG1)
        {
            pFileLoggerStream->register_unit(
                Traits::GetTag(),
                { qx::log_level::log,
                  [](qx::logger_buffers<char>& buffers,
                     qx::log_level,
                     const char*      pszFormat,
                     std::string_view svTag,
                     std::string_view,
                     std::string_view,
                     int,
                     va_list args)
                  {
                      buffers.sMessage.vsprintf(pszFormat, args);
                      qx::base_logger_stream::format_time_string(buffers.sFormat);
                      buffers.sMessage =
                          qx::string("   [") + buffers.sFormat + "][" + svTag + "] " + buffers.sMessage + '\n';
                  } });

            pFileLoggerStream->register_file(Traits::GetTag(), Traits::GetLogsFile());
        }

        m_pLogger->add_stream(std::move(pConsoleLoggerStream));
        m_pLogger->add_stream(std::move(pFileLoggerStream));
    }

    /* called after every test */
    virtual void TearDown() override
    {
        if (Traits::GetUnit() == UNIT_DEFAULT
            || Traits::GetUnit() == UNIT_FILE && Traits::GetUnit() == Traits::GetTraceFile()
            || Traits::GetUnit() == UNIT_FUNC && m_bFunction)
        {
            ASSERT_TRUE(std::filesystem::exists(m_sLogFilePath.data()));
            std::ifstream ifs(m_sLogFilePath.data());

            std::string sLine(512, '\0');
            std::smatch match;
            qx::string  sFormat;
            std::regex  regex;
            qx::string  sFile;

            constexpr const char* pszInfo    = "   ";
            constexpr const char* pszWarning = "\\[W\\]";
            constexpr const char* pszError   = "\\[E\\]";
            constexpr const char* pszAssert  = "\\[C\\]";
            constexpr const char* pszDate    = "\\[\\d{2}-\\d{2}-\\d{4}_";
            constexpr const char* pszTime    = "\\d{2}-\\d{2}-\\d{2}\\]";

            auto CheckRegex = [&regex, &match](const qx::string& sMatch, const std::string& sText)
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

            auto CheckStringCommon = [&sFormat, &sFile, &ifs, &sLine, &CheckRegex](
                                         const char* pszStringStarting,
                                         const char* pszStringEnding,
                                         bool        bTag = false)
            {
                sFile.sprintf(
                    "%s\\[%s::",
                    bTag && Traits::GetTag() ? qx::string::static_sprintf("\\[%s\\]", Traits::GetTag()).c_str() : "",
                    Traits::GetTraceFile());

                constexpr const char* pszFunc = "(.*?)"; // compiler-dependent
                constexpr const char* pszLine = "::\\d+\\]";

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

            auto CheckStringTag = [&sFormat, &ifs, &sLine, &CheckRegex](const char* pszStringEnding)
            {
                sFormat.sprintf("%s%s%s\\[%s\\]%s", pszInfo, pszDate, pszTime, Traits::GetTag(), pszStringEnding);
                ifs.getline(sLine.data(), static_cast<std::streamsize>(sLine.size()));
                CheckRegex(sFormat, sLine);
            };

            CheckStringCommon(pszInfo, " Start test");

            CheckStringCommon(pszInfo, " 1.000000");
            CheckStringCommon(pszInfo, " 1.000000 1");
            CheckStringCommon(pszInfo, " 1.000000 2");
            CheckStringCommon(pszInfo, " 1.000000 3");
            CheckStringCommon(pszInfo, " 1.000000 4");
            CheckStringCommon(pszInfo, " 1.000000 5");

            CheckStringCommon(pszWarning, " 1.000000");
            CheckStringCommon(pszWarning, " 1.000000 1");
            CheckStringCommon(pszWarning, " 1.000000 2");
            CheckStringCommon(pszWarning, " 1.000000 3");
            CheckStringCommon(pszWarning, " 1.000000 4");
            CheckStringCommon(pszWarning, " 1.000000 5");

            CheckStringCommon(pszError, " 1.000000 1");
            CheckStringCommon(pszError, " 1.000000 2");
            CheckStringCommon(pszError, " 1.000000 3");
            CheckStringCommon(pszError, " 1.000000 4");
            CheckStringCommon(pszError, " 1.000000 5");

            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 1");
            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 2");
            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 3");
            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 4");
            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 5");

            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 1 three");
            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 2 three");
            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 3 three");
            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 4 three");
            CheckStringCommon(pszAssert, " \\[false\\] 1.000000 5 three");

            if constexpr (TRACE_TAG_TAG1 == Traits::GetTag())
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
                CheckStringCommon(pszInfo, " 1.000000", true);
                CheckStringCommon(pszInfo, " 1.000000 1", true);
                CheckStringCommon(pszInfo, " 1.000000 2", true);
                CheckStringCommon(pszInfo, " 1.000000 3", true);
                CheckStringCommon(pszInfo, " 1.000000 4", true);
                CheckStringCommon(pszInfo, " 1.000000 5", true);
            }

            CheckStringCommon(pszInfo, " End test");

            ifs.close();

            std::error_code ec;
            EXPECT_TRUE(std::filesystem::remove(m_sLogFilePath.data(), ec)) << ec.message().data();
        }
        else
        {
            EXPECT_FALSE(std::filesystem::exists(m_sLogFilePath.data()));
        }

        m_bFunction = false;
    }

protected:
    std::unique_ptr<qx::logger> m_pLogger;
    bool                        m_bFunction = false;
    qx::string                  m_sLogFilePath;
};

TYPED_TEST_SUITE(TestLogger, Implementations);

#define TRACE(traceFile, format, ...) \
    myLogger.log(qx::log_level::log, format, qx::log_tag { nullptr }, traceFile, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define TRACE_WARNING(traceFile, format, ...) \
    myLogger.log(                             \
        qx::log_level::warning,               \
        format,                               \
        qx::log_tag { nullptr },              \
        traceFile,                            \
        __FUNCTION__,                         \
        __LINE__,                             \
        ##__VA_ARGS__)

#define TRACE_TAG(traceFile, tag, format, ...) \
    myLogger.log(qx::log_level::log, format, qx::log_tag { tag }, traceFile, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define TRACE_ERROR(traceFile, format, ...) \
    myLogger                                \
        .log(qx::log_level::error, format, qx::log_tag { nullptr }, traceFile, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define TRACE_ASSERT(traceFile, expr, format, ...) \
    myLogger.log(                                  \
        qx::log_level::critical,                   \
        "[%s] " format,                            \
        qx::log_tag { nullptr },                   \
        traceFile,                                 \
        __FUNCTION__,                              \
        __LINE__,                                  \
        #expr,                                     \
        ##__VA_ARGS__)

#define TEST_LOGGER(traceFile, tag)                              \
    TRACE(traceFile, "Start test");                              \
                                                                 \
    TRACE(traceFile, "%f", 1.f);                                 \
    TRACE(traceFile, "%f %d", 1.f, 1);                           \
    TRACE(traceFile, "%f %d", 1.f, 2);                           \
    TRACE(traceFile, "%f %d", 1.f, 3);                           \
    TRACE(traceFile, "%f %d", 1.f, 4);                           \
    TRACE(traceFile, "%f %d", 1.f, 5);                           \
                                                                 \
    TRACE_WARNING(traceFile, "%f", 1.f);                         \
    TRACE_WARNING(traceFile, "%f %d", 1.f, 1);                   \
    TRACE_WARNING(traceFile, "%f %d", 1.f, 2);                   \
    TRACE_WARNING(traceFile, "%f %d", 1.f, 3);                   \
    TRACE_WARNING(traceFile, "%f %d", 1.f, 4);                   \
    TRACE_WARNING(traceFile, "%f %d", 1.f, 5);                   \
                                                                 \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 1);                     \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 2);                     \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 3);                     \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 4);                     \
    TRACE_ERROR(traceFile, "%f %d", 1.f, 5);                     \
                                                                 \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 1);             \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 2);             \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 3);             \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 4);             \
    TRACE_ASSERT(traceFile, false, "%f %d", 1.f, 5);             \
                                                                 \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 1, "three"); \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 2, "three"); \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 3, "three"); \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 4, "three"); \
    TRACE_ASSERT(traceFile, false, "%f %d %s", 1.f, 5, "three"); \
                                                                 \
    TRACE_TAG(traceFile, tag, "%f", 1.f);                        \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 1);                  \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 2);                  \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 3);                  \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 4);                  \
    TRACE_TAG(traceFile, tag, "%f %d", 1.f, 5);                  \
                                                                 \
    TRACE(traceFile, "End test\n");

void TestLoggerFunction(qx::logger& myLogger, const char* pszTraceFile, const char* pszTag)
{
    TEST_LOGGER(pszTraceFile, pszTag);
}

TYPED_TEST(TestLogger, logger_function)
{
    TestLoggerFunction(*TestFixture::m_pLogger, TypeParam::GetTraceFile(), TypeParam::GetTag());
    TestFixture::m_bFunction = true;
}

TYPED_TEST(TestLogger, logger_method)
{
    auto& myLogger = *TestFixture::m_pLogger;
    TEST_LOGGER(TypeParam::GetTraceFile(), TypeParam::GetTag());
}

TYPED_TEST(TestLogger, logger_lambda)
{
    auto TestLoggerLambda = [](auto& myLogger)
    {
        TEST_LOGGER(TypeParam::GetTraceFile(), TypeParam::GetTag());
    };

    TestLoggerLambda(*TestFixture::m_pLogger);
}

QX_POP_SUPPRESS_WARNINGS
