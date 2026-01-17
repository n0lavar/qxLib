/**

    @file      logger.gtest.cpp
    @brief     Tests for qx::logger
    @author    Khrapov
    @date      27.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *logger.gtest.cpp

#include <qx/logger/logger.h>

#include <qx/logger/cout_logger_stream.h>
#include <qx/logger/debugger_logger_stream.h>
#include <qx/logger/file_logger_stream_fopen.h>
#include <qx/logger/file_logger_stream_mapping.h>
#include <qx/logger/file_logger_stream_ofstream.h>

#include <filesystem>
#include <regex>

static_assert(qx::log_acceptable_args_c<int>);
static_assert(qx::log_acceptable_args_c<float>);
static_assert(qx::log_acceptable_args_c<int, float>);

using allowed_type = qx::char_type;
static_assert(qx::log_acceptable_args_c<allowed_type>);
static_assert(qx::log_acceptable_args_c<const allowed_type>);
static_assert(qx::log_acceptable_args_c<allowed_type*>);
static_assert(qx::log_acceptable_args_c<const allowed_type*>);
static_assert(qx::log_acceptable_args_c<allowed_type[10]>);
static_assert(qx::log_acceptable_args_c<const allowed_type[10]>);

static_assert(qx::log_acceptable_args_c<int, float, allowed_type>);
static_assert(qx::log_acceptable_args_c<int, float, const allowed_type>);
static_assert(qx::log_acceptable_args_c<int, float, allowed_type*>);
static_assert(qx::log_acceptable_args_c<int, float, const allowed_type*>);
static_assert(qx::log_acceptable_args_c<int, float, allowed_type[10]>);
static_assert(qx::log_acceptable_args_c<int, float, const allowed_type[10]>);

using forbidden_type = std::tuple_element_t<0, qx::forbidden_char_types>;
static_assert(!qx::log_acceptable_args_c<forbidden_type>);
static_assert(!qx::log_acceptable_args_c<const forbidden_type>);
static_assert(!qx::log_acceptable_args_c<forbidden_type*>);
static_assert(!qx::log_acceptable_args_c<const forbidden_type*>);
static_assert(!qx::log_acceptable_args_c<forbidden_type[10]>);
static_assert(!qx::log_acceptable_args_c<const forbidden_type[10]>);

static_assert(!qx::log_acceptable_args_c<int, float, forbidden_type>);
static_assert(!qx::log_acceptable_args_c<int, float, const forbidden_type>);
static_assert(!qx::log_acceptable_args_c<int, float, forbidden_type*>);
static_assert(!qx::log_acceptable_args_c<int, float, const forbidden_type*>);
static_assert(!qx::log_acceptable_args_c<int, float, forbidden_type[10]>);
static_assert(!qx::log_acceptable_args_c<int, float, const forbidden_type[10]>);

static_assert(qx::sbo_poly_fittable_types_v<
              qx::logger::logger_sbo,
              qx::cout_logger_stream,
              qx::file_logger_stream_ofstream,
              qx::file_logger_stream_fopen,
              qx::file_logger_stream_mapping,
              qx::debugger_logger_stream>);

QX_PUSH_SUPPRESS_MSVC_WARNINGS(4866 5233);

template<
    const qx::char_type sLogsFile[],
    const qx::char_type sUnit[],
    const qx::char_type sTraceFile[],
    const qx::char_type sCategory[]>
struct LoggerTraits
{
    constexpr static qx::string_view GetLogsFile()
    {
        return sLogsFile;
    }
    constexpr static qx::string_view GetUnit()
    {
        return sUnit;
    }
    constexpr static const qx::char_type* GetTraceFile()
    {
        return sTraceFile;
    }
    constexpr static qx::string_view GetCategory()
    {
        return sCategory;
    }
};

constexpr qx::char_type LOGS_FILE_DEFAULT[] = QXT("default");

constexpr qx::char_type UNIT_DEFAULT[] = QXT("default");
constexpr qx::char_type UNIT_FILE[]    = QXT("file.h");
constexpr qx::char_type UNIT_FUNC[]    = QXT("TestLoggerFunction");

constexpr qx::char_type LOG_FILE_H[]   = QXT("file.h");
constexpr qx::char_type LOG_FILE_CPP[] = QXT("file.cpp");
constexpr qx::char_type LOG_FILE_INL[] = QXT("file.inl");

constexpr qx::char_type LOG_CATEGORY_DEFAULT[] = QXT("CatDefault");
constexpr qx::char_type LOG_CATEGORY_TAG1[]    = QXT("tag1");
constexpr qx::char_type LOG_CATEGORY_TAG2[]    = QXT("tag2");

using implementations_type = ::testing::Types<
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_DEFAULT>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_FILE, LOG_FILE_H, LOG_CATEGORY_DEFAULT>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_FUNC, LOG_FILE_H, LOG_CATEGORY_DEFAULT>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_DEFAULT>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_DEFAULT>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_CPP, LOG_CATEGORY_DEFAULT>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_INL, LOG_CATEGORY_DEFAULT>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_TAG1>,
    LoggerTraits<LOGS_FILE_DEFAULT, UNIT_DEFAULT, LOG_FILE_H, LOG_CATEGORY_TAG2>>;


template<class traits_t>
class TestLogger : public ::testing::Test
{
protected:
    /* init protected members here */
    TestLogger()
    {
        m_sLogFilePath = traits_t::GetLogsFile();
        m_sLogFilePath += QXT(".log");
    }

    /* called before every test */
    virtual void SetUp() override
    {
        std::filesystem::remove(m_sLogFilePath.data());
        m_pLogger = std::make_unique<qx::logger>();

        qx::cout_logger_stream consoleLoggerStream;
        //consoleLoggerStream.deregister_unit(qx::base_logger_stream::svDefaultUnit);
        //consoleLoggerStream.register_unit(traits_t::GetUnit(), { qx::verbosity::log });

        qx::file_logger_stream_ofstream fileLoggerStream(
            { { .bProtectLog = true, .eMinFlushVerbosity = qx::verbosity::very_verbose },
              qx::log_file_policy::clear_then_uppend,
              traits_t::GetLogsFile() });
        //fileLoggerStream.deregister_unit(qx::base_logger_stream::svDefaultUnit);
        //fileLoggerStream.register_unit(traits_t::GetUnit(), { qx::verbosity::log });

        qx::debugger_logger_stream debugLoggerStream;
        //debugLoggerStream.deregister_unit(qx::base_logger_stream::svDefaultUnit);
        //debugLoggerStream.register_unit(traits_t::GetUnit(), { qx::verbosity::log });

        m_pLogger->add_stream(std::move(consoleLoggerStream));
        m_pLogger->add_stream(std::move(fileLoggerStream));
        m_pLogger->add_stream(std::move(debugLoggerStream));
    }

    /* called after every test */
    virtual void TearDown() override
    {
        if (traits_t::GetUnit() == UNIT_DEFAULT
            || traits_t::GetUnit() == UNIT_FILE && traits_t::GetUnit() == traits_t::GetTraceFile()
            || traits_t::GetUnit() == UNIT_FUNC && m_bFunction)
        {
            const std::filesystem::path        path(m_sLogFilePath.c_str());
            std::basic_ifstream<qx::char_type> ifs(path);

            std::basic_string<qx::char_type>              sLine(512, QXT('\0'));
            std::match_results<qx::string::const_pointer> match;
            std::basic_string<qx::char_type>              sFormat;
            std::basic_regex<qx::char_type>               regex;
            std::basic_string<qx::char_type>              sFile;

            constexpr const qx::char_type* pszInfo    = QXT("   ");
            constexpr const qx::char_type* pszWarning = QXT("\\[W\\]");
            constexpr const qx::char_type* pszError   = QXT("\\[E\\]");
            constexpr const qx::char_type* pszAssert  = QXT("\\[C\\]");
            constexpr const qx::char_type* pszDate    = QXT("\\[\\d{2}.\\d{2}.\\d{4}_");
            constexpr const qx::char_type* pszTime    = QXT("\\d{2}:\\d{2}:\\d{2}\\]");

            auto check_regex = [&regex, &match](const qx::string& sMatch, const qx::string& sText)
            {
                regex = std::basic_regex(sMatch.data());
                EXPECT_TRUE(std::regex_search(std::basic_string(sText.c_str()).c_str(), match, regex))
                    << "regex:           " << qx::to_cstring(sMatch).c_str() << std::endl
                    << "line:            " << qx::to_cstring(sText).c_str() << std::endl
                    << "logs unit:       " << qx::to_cstring(traits_t::GetUnit()).c_str() << std::endl
                    << "logs trace file: " << qx::to_cstring(traits_t::GetTraceFile()).c_str();
            };

            auto check_string = [&sFormat, &sFile, &ifs, &sLine, &check_regex](
                                    const qx::char_type* pszStringStarting,
                                    const qx::char_type* pszStringEnding,
                                    qx::string_view      svCategory = LOG_CATEGORY_DEFAULT)
            {
                sFile.clear();
                sFile += QXT("\\[");
                sFile += svCategory;
                sFile += QXT("\\]");
                sFile += QXT("\\[");
                sFile += traits_t::GetTraceFile();
                sFile += QXT("::");

                constexpr const qx::char_type* pszFunc = QXT("(.*?)"); // compiler-dependent
                constexpr const qx::char_type* pszLine = QXT("::\\d+\\]");

                sFormat.clear();
                sFormat += pszStringStarting;
                sFormat += pszDate;
                sFormat += pszTime;
                sFormat += sFile;
                sFormat += pszFunc;
                sFormat += pszLine;
                sFormat += pszStringEnding;

                ifs.getline(sLine.data(), static_cast<std::streamsize>(sLine.size()));

                check_regex(sFormat, sLine);
            };

            check_string(pszInfo, QXT(" Start test"));

            check_string(pszInfo, QXT(" 1.2"));
            check_string(pszInfo, QXT(" 1.2 1"));
            check_string(pszInfo, QXT(" 1.2 2"));
            check_string(pszInfo, QXT(" 1.2 3"));
            check_string(pszInfo, QXT(" 1.2 4"));
            check_string(pszInfo, QXT(" 1.2 5"));

            check_string(pszWarning, QXT(" 1.2"));
            check_string(pszWarning, QXT(" 1.2 1"));
            check_string(pszWarning, QXT(" 1.2 2"));
            check_string(pszWarning, QXT(" 1.2 3"));
            check_string(pszWarning, QXT(" 1.2 4"));
            check_string(pszWarning, QXT(" 1.2 5"));

            check_string(pszError, QXT(" 1.2 1"));
            check_string(pszError, QXT(" 1.2 2"));
            check_string(pszError, QXT(" 1.2 3"));
            check_string(pszError, QXT(" 1.2 4"));
            check_string(pszError, QXT(" 1.2 5"));

            check_string(pszAssert, QXT(" \\[false\\] 1.2 1"));
            check_string(pszAssert, QXT(" \\[false\\] 1.2 2"));
            check_string(pszAssert, QXT(" \\[false\\] 1.2 3"));
            check_string(pszAssert, QXT(" \\[false\\] 1.2 4"));
            check_string(pszAssert, QXT(" \\[false\\] 1.2 5"));

            check_string(pszAssert, QXT(" \\[false\\] 1.2 1 three"));
            check_string(pszAssert, QXT(" \\[false\\] 1.2 2 three"));
            check_string(pszAssert, QXT(" \\[false\\] 1.2 3 three"));
            check_string(pszAssert, QXT(" \\[false\\] 1.2 4 three"));
            check_string(pszAssert, QXT(" \\[false\\] 1.2 5 three"));

            check_string(pszInfo, QXT(" 1.2"), traits_t::GetCategory());
            check_string(pszInfo, QXT(" 1.2 1"), traits_t::GetCategory());
            check_string(pszInfo, QXT(" 1.2 2"), traits_t::GetCategory());
            check_string(pszInfo, QXT(" 1.2 3"), traits_t::GetCategory());
            check_string(pszInfo, QXT(" 1.2 4"), traits_t::GetCategory());
            check_string(pszInfo, QXT(" 1.2 5"), traits_t::GetCategory());

            check_string(pszInfo, QXT(" End test"));

            ifs.close();
        }

        m_bFunction = false;
    }

protected:
    std::unique_ptr<qx::logger> m_pLogger;
    bool                        m_bFunction = false;
    qx::string                  m_sLogFilePath;
};

TYPED_TEST_SUITE(TestLogger, implementations_type);

#define TEST_LOG(traceFile, format, ...)                           \
    myLogger.log(                                                  \
        CatDefault,                                                \
        qx::verbosity::log,                                        \
        traceFile,                                                 \
        qx::convert_string_literal<qx::char_type, __FUNCTION__>(), \
        __LINE__,                                                  \
        qx::string::static_format(QXT(format), ##__VA_ARGS__))

#define TEST_LOG_WARNING(traceFile, format, ...)                   \
    myLogger.log(                                                  \
        CatDefault,                                                \
        qx::verbosity::warning,                                    \
        traceFile,                                                 \
        qx::convert_string_literal<qx::char_type, __FUNCTION__>(), \
        __LINE__,                                                  \
        qx::string::static_format(QXT(format), ##__VA_ARGS__))

#define TEST_LOG_CATEGORY(traceFile, _category, format, ...)       \
    myLogger.log(                                                  \
        qx::category { _category },                                \
        qx::verbosity::log,                                        \
        traceFile,                                                 \
        qx::convert_string_literal<qx::char_type, __FUNCTION__>(), \
        __LINE__,                                                  \
        qx::string::static_format(QXT(format), ##__VA_ARGS__))

#define TEST_LOG_ERROR(traceFile, format, ...)                     \
    myLogger.log(                                                  \
        CatDefault,                                                \
        qx::verbosity::error,                                      \
        traceFile,                                                 \
        qx::convert_string_literal<qx::char_type, __FUNCTION__>(), \
        __LINE__,                                                  \
        qx::string::static_format(QXT(format), ##__VA_ARGS__))

#define TEST_LOG_ASSERT(traceFile, expr, format, ...)              \
    myLogger.log(                                                  \
        CatDefault,                                                \
        qx::verbosity::critical,                                   \
        traceFile,                                                 \
        qx::convert_string_literal<qx::char_type, __FUNCTION__>(), \
        __LINE__,                                                  \
        qx::string::static_format(QXT("[{}] ") QXT(format), QXT(#expr), ##__VA_ARGS__))

#define TEST_LOGGER(traceFile, _category)                                 \
    TEST_LOG(traceFile, "Start test");                                    \
                                                                          \
    TEST_LOG(traceFile, "{}", 1.2f);                                      \
    TEST_LOG(traceFile, "{} {}", 1.2f, 1);                                \
    TEST_LOG(traceFile, "{} {}", 1.2f, 2);                                \
    TEST_LOG(traceFile, "{} {}", 1.2f, 3);                                \
    TEST_LOG(traceFile, "{} {}", 1.2f, 4);                                \
    TEST_LOG(traceFile, "{} {}", 1.2f, 5);                                \
                                                                          \
    TEST_LOG_WARNING(traceFile, "{}", 1.2f);                              \
    TEST_LOG_WARNING(traceFile, "{} {}", 1.2f, 1);                        \
    TEST_LOG_WARNING(traceFile, "{} {}", 1.2f, 2);                        \
    TEST_LOG_WARNING(traceFile, "{} {}", 1.2f, 3);                        \
    TEST_LOG_WARNING(traceFile, "{} {}", 1.2f, 4);                        \
    TEST_LOG_WARNING(traceFile, "{} {}", 1.2f, 5);                        \
                                                                          \
    TEST_LOG_ERROR(traceFile, "{} {}", 1.2f, 1);                          \
    TEST_LOG_ERROR(traceFile, "{} {}", 1.2f, 2);                          \
    TEST_LOG_ERROR(traceFile, "{} {}", 1.2f, 3);                          \
    TEST_LOG_ERROR(traceFile, "{} {}", 1.2f, 4);                          \
    TEST_LOG_ERROR(traceFile, "{} {}", 1.2f, 5);                          \
                                                                          \
    TEST_LOG_ASSERT(traceFile, false, "{} {}", 1.2f, 1);                  \
    TEST_LOG_ASSERT(traceFile, false, "{} {}", 1.2f, 2);                  \
    TEST_LOG_ASSERT(traceFile, false, "{} {}", 1.2f, 3);                  \
    TEST_LOG_ASSERT(traceFile, false, "{} {}", 1.2f, 4);                  \
    TEST_LOG_ASSERT(traceFile, false, "{} {}", 1.2f, 5);                  \
                                                                          \
    TEST_LOG_ASSERT(traceFile, false, "{} {} {}", 1.2f, 1, QXT("three")); \
    TEST_LOG_ASSERT(traceFile, false, "{} {} {}", 1.2f, 2, QXT("three")); \
    TEST_LOG_ASSERT(traceFile, false, "{} {} {}", 1.2f, 3, QXT("three")); \
    TEST_LOG_ASSERT(traceFile, false, "{} {} {}", 1.2f, 4, QXT("three")); \
    TEST_LOG_ASSERT(traceFile, false, "{} {} {}", 1.2f, 5, QXT("three")); \
                                                                          \
    TEST_LOG_CATEGORY(traceFile, _category, "{}", 1.2f);                  \
    TEST_LOG_CATEGORY(traceFile, _category, "{} {}", 1.2f, 1);            \
    TEST_LOG_CATEGORY(traceFile, _category, "{} {}", 1.2f, 2);            \
    TEST_LOG_CATEGORY(traceFile, _category, "{} {}", 1.2f, 3);            \
    TEST_LOG_CATEGORY(traceFile, _category, "{} {}", 1.2f, 4);            \
    TEST_LOG_CATEGORY(traceFile, _category, "{} {}", 1.2f, 5);            \
                                                                          \
    TEST_LOG(traceFile, "End test\n");

void TestLoggerFunction(qx::logger& myLogger, const qx::char_type* pszTraceFile, qx::string_view svCategory)
{
    TEST_LOGGER(pszTraceFile, svCategory);
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

QX_POP_SUPPRESS_WARNINGS();
