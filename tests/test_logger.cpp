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

#include <filesystem>
#include <regex>

QX_PUSH_SUPPRESS_MSVC_WARNINGS(5233)

template<const wchar_t sLogsFile[], const char sUnit[], const char sTraceFile[], const char sCategory[]>
struct LoggerTraits
{
    constexpr static std::wstring_view GetLogsFile()
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
    constexpr static const char* GetCategory()
    {
        return sCategory[0] == '\0' ? nullptr : sCategory;
    }
};

constexpr wchar_t LOGS_FILE_DEFAULT[] = L"default";

constexpr char UNIT_DEFAULT[] = "default";
constexpr char UNIT_FILE[]    = "file.h";
constexpr char UNIT_FUNC[]    = "TestLoggerFunction";

constexpr char LOG_FILE_H[]   = "file.h";
constexpr char LOG_FILE_CPP[] = "file.cpp";
constexpr char LOG_FILE_INL[] = "file.inl";

constexpr char LOG_CATEGORY_NULLPTR[] = "";
constexpr char LOG_CATEGORY_TAG1[]    = "tag1";
constexpr char LOG_CATEGORY_TAG2[]    = "tag2";

using Implementations = ::testing::Types<
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_NULLPTR>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_FILE, LOG_FILE_H, LOG_CATEGORY_NULLPTR>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_FUNC, LOG_FILE_H, LOG_CATEGORY_NULLPTR>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_NULLPTR>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_NULLPTR>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_CPP, LOG_CATEGORY_NULLPTR>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_INL, LOG_CATEGORY_NULLPTR>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_TAG1>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_TAG2>>;

template<typename Traits>
class TestLogger : public ::testing::Test
{
protected:
    /* init protected members here */
    TestLogger()
    {
        m_sLogFilePath = Traits::GetLogsFile();
        m_sLogFilePath += L".log";
    }

    /* called before every test */
    virtual void SetUp() override
    {
        std::filesystem::remove(m_sLogFilePath.data());
        m_pLogger = std::make_unique<qx::logger>();

        auto pConsoleLoggerStream = std::make_unique<qx::cout_logger_stream>();
        pConsoleLoggerStream->deregister_unit(qx::base_logger_stream::k_svDefaultUnit);
        pConsoleLoggerStream->register_unit(Traits::GetUnit(), { qx::log_level::none });

        auto pFileLoggerStream = std::make_unique<qx::file_logger_stream>(
            true,
            qx::log_file_policy::clear_then_uppend,
            Traits::GetLogsFile());
        pFileLoggerStream->deregister_unit(qx::base_logger_stream::k_svDefaultUnit);
        pFileLoggerStream->register_unit(Traits::GetUnit(), { qx::log_level::log });

        if constexpr (Traits::GetCategory() == LOG_CATEGORY_TAG1)
        {
            pFileLoggerStream->register_unit(
                Traits::GetCategory(),
                { qx::log_level::log,
                  [](qx::logger_buffer<char>& buffers,
                     qx::log_level,
                     const qx::category& category,
                     const char*         pszFormat,
                     const char*,
                     const char*,
                     int,
                     va_list args)
                  {
                      buffers.sMessage.vsprintf(pszFormat, args);
                      qx::base_logger_stream::format_time_string(buffers.sFormat, '.', ':');
                      buffers.sMessage = qx::string("   [") + buffers.sFormat + "][" + category.get_name() + "] "
                                         + buffers.sMessage + '\n';
                  } });
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
            constexpr const char* pszDate    = "\\[\\d{2}.\\d{2}.\\d{4}_";
            constexpr const char* pszTime    = "\\d{2}:\\d{2}:\\d{2}\\]";

            auto CheckRegex = [&regex, &match](const qx::string& sMatch, const std::string& sText)
            {
                regex = std::regex(sMatch.data());
                EXPECT_TRUE(std::regex_search(sText, match, regex))
                    << "regex:           " << sMatch.data() << std::endl
                    << "line:            " << sText.data() << std::endl
                    << "logs unit:       " << Traits::GetUnit() << std::endl
                    << "logs trace file: " << Traits::GetTraceFile();
            };

            auto CheckStringCommon = [&sFormat, &sFile, &ifs, &sLine, &CheckRegex](
                                         const char* pszStringStarting,
                                         const char* pszStringEnding,
                                         bool        bCategory = false)
            {
                sFile.sprintf(
                    "%s\\[%s::",
                    bCategory && Traits::GetCategory()
                        ? qx::string::static_sprintf("\\[%s\\]", Traits::GetCategory()).c_str()
                        : "",
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

            auto CheckStringCategory = [&sFormat, &ifs, &sLine, &CheckRegex](const char* pszStringEnding)
            {
                sFormat.sprintf("%s%s%s\\[%s\\]%s", pszInfo, pszDate, pszTime, Traits::GetCategory(), pszStringEnding);
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

            if constexpr (LOG_CATEGORY_TAG1 == Traits::GetCategory())
            {
                CheckStringCategory(" 1.000000");
                CheckStringCategory(" 1.000000 1");
                CheckStringCategory(" 1.000000 2");
                CheckStringCategory(" 1.000000 3");
                CheckStringCategory(" 1.000000 4");
                CheckStringCategory(" 1.000000 5");
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
        }

        m_bFunction = false;
    }

protected:
    std::unique_ptr<qx::logger> m_pLogger;
    bool                        m_bFunction = false;
    qx::wstring                 m_sLogFilePath;
};

TYPED_TEST_SUITE(TestLogger, Implementations);

#define TEST_LOG(traceFile, format, ...) \
    myLogger.log(qx::log_level::log, format, qx::category { nullptr }, traceFile, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define TEST_LOG_WARNING(traceFile, format, ...) \
    myLogger.log(                                \
        qx::log_level::warning,                  \
        format,                                  \
        qx::category { nullptr },                \
        traceFile,                               \
        __FUNCTION__,                            \
        __LINE__,                                \
        ##__VA_ARGS__)

#define TEST_LOG_CATEGORY(traceFile, _category, format, ...) \
    myLogger                                                 \
        .log(qx::log_level::log, format, qx::category { _category }, traceFile, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define TEST_LOG_ERROR(traceFile, format, ...) \
    myLogger                                   \
        .log(qx::log_level::error, format, qx::category { nullptr }, traceFile, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define TEST_LOG_ASSERT(traceFile, expr, format, ...) \
    myLogger.log(                                     \
        qx::log_level::critical,                      \
        "[%s] " format,                               \
        qx::category { nullptr },                     \
        traceFile,                                    \
        __FUNCTION__,                                 \
        __LINE__,                                     \
        #expr,                                        \
        ##__VA_ARGS__)

#define TEST_LOGGER(traceFile, _category)                           \
    TEST_LOG(traceFile, "Start test");                              \
                                                                    \
    TEST_LOG(traceFile, "%f", 1.f);                                 \
    TEST_LOG(traceFile, "%f %d", 1.f, 1);                           \
    TEST_LOG(traceFile, "%f %d", 1.f, 2);                           \
    TEST_LOG(traceFile, "%f %d", 1.f, 3);                           \
    TEST_LOG(traceFile, "%f %d", 1.f, 4);                           \
    TEST_LOG(traceFile, "%f %d", 1.f, 5);                           \
                                                                    \
    TEST_LOG_WARNING(traceFile, "%f", 1.f);                         \
    TEST_LOG_WARNING(traceFile, "%f %d", 1.f, 1);                   \
    TEST_LOG_WARNING(traceFile, "%f %d", 1.f, 2);                   \
    TEST_LOG_WARNING(traceFile, "%f %d", 1.f, 3);                   \
    TEST_LOG_WARNING(traceFile, "%f %d", 1.f, 4);                   \
    TEST_LOG_WARNING(traceFile, "%f %d", 1.f, 5);                   \
                                                                    \
    TEST_LOG_ERROR(traceFile, "%f %d", 1.f, 1);                     \
    TEST_LOG_ERROR(traceFile, "%f %d", 1.f, 2);                     \
    TEST_LOG_ERROR(traceFile, "%f %d", 1.f, 3);                     \
    TEST_LOG_ERROR(traceFile, "%f %d", 1.f, 4);                     \
    TEST_LOG_ERROR(traceFile, "%f %d", 1.f, 5);                     \
                                                                    \
    TEST_LOG_ASSERT(traceFile, false, "%f %d", 1.f, 1);             \
    TEST_LOG_ASSERT(traceFile, false, "%f %d", 1.f, 2);             \
    TEST_LOG_ASSERT(traceFile, false, "%f %d", 1.f, 3);             \
    TEST_LOG_ASSERT(traceFile, false, "%f %d", 1.f, 4);             \
    TEST_LOG_ASSERT(traceFile, false, "%f %d", 1.f, 5);             \
                                                                    \
    TEST_LOG_ASSERT(traceFile, false, "%f %d %s", 1.f, 1, "three"); \
    TEST_LOG_ASSERT(traceFile, false, "%f %d %s", 1.f, 2, "three"); \
    TEST_LOG_ASSERT(traceFile, false, "%f %d %s", 1.f, 3, "three"); \
    TEST_LOG_ASSERT(traceFile, false, "%f %d %s", 1.f, 4, "three"); \
    TEST_LOG_ASSERT(traceFile, false, "%f %d %s", 1.f, 5, "three"); \
                                                                    \
    TEST_LOG_CATEGORY(traceFile, _category, "%f", 1.f);             \
    TEST_LOG_CATEGORY(traceFile, _category, "%f %d", 1.f, 1);       \
    TEST_LOG_CATEGORY(traceFile, _category, "%f %d", 1.f, 2);       \
    TEST_LOG_CATEGORY(traceFile, _category, "%f %d", 1.f, 3);       \
    TEST_LOG_CATEGORY(traceFile, _category, "%f %d", 1.f, 4);       \
    TEST_LOG_CATEGORY(traceFile, _category, "%f %d", 1.f, 5);       \
                                                                    \
    TEST_LOG(traceFile, "End test\n");

void TestLoggerFunction(qx::logger& myLogger, const char* pszTraceFile, const char* pszCategory)
{
    TEST_LOGGER(pszTraceFile, pszCategory);
}

TYPED_TEST(TestLogger, logger_function)
{
    TestLoggerFunction(*TestFixture::m_pLogger, TypeParam::GetTraceFile(), TypeParam::GetCategory());
    TestFixture::m_bFunction = true;
}

TYPED_TEST(TestLogger, logger_method)
{
    auto& myLogger = *TestFixture::m_pLogger;
    TEST_LOGGER(TypeParam::GetTraceFile(), TypeParam::GetCategory());
}

TYPED_TEST(TestLogger, logger_lambda)
{
    auto TestLoggerLambda = [](auto& myLogger)
    {
        TEST_LOGGER(TypeParam::GetTraceFile(), TypeParam::GetCategory());
    };

    TestLoggerLambda(*TestFixture::m_pLogger);
}

QX_POP_SUPPRESS_WARNINGS
