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
    constexpr static const qx::char_type* GetCategory()
    {
        return sCategory[0] == QX_TEXT('\0') ? nullptr : sCategory;
    }
};

constexpr qx::char_type LOGS_FILE_DEFAULT[] = QX_TEXT("default");

constexpr qx::char_type UNIT_DEFAULT[] = QX_TEXT("default");
constexpr qx::char_type UNIT_FILE[]    = QX_TEXT("file.h");
constexpr qx::char_type UNIT_FUNC[]    = QX_TEXT("TestLoggerFunction");

constexpr qx::char_type LOG_FILE_H[]   = QX_TEXT("file.h");
constexpr qx::char_type LOG_FILE_CPP[] = QX_TEXT("file.cpp");
constexpr qx::char_type LOG_FILE_INL[] = QX_TEXT("file.inl");

constexpr qx::char_type LOG_CATEGORY_NULLPTR[] = QX_TEXT("");
constexpr qx::char_type LOG_CATEGORY_TAG1[]    = QX_TEXT("tag1");
constexpr qx::char_type LOG_CATEGORY_TAG2[]    = QX_TEXT("tag2");

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

template<class traits_t>
class TestLogger : public ::testing::Test
{
protected:
    /* init protected members here */
    TestLogger()
    {
        m_sLogFilePath = traits_t::GetLogsFile();
        m_sLogFilePath += QX_TEXT(".log");
    }

    /* called before every test */
    virtual void SetUp() override
    {
        std::filesystem::remove(m_sLogFilePath.data());
        m_pLogger = std::make_unique<qx::logger>();

        auto pConsoleLoggerStream = std::make_unique<qx::cout_logger_stream>();
        pConsoleLoggerStream->deregister_unit(qx::base_logger_stream::k_svDefaultUnit);
        pConsoleLoggerStream->register_unit(traits_t::GetUnit(), { qx::log_level::none });

        auto pFileLoggerStream = std::make_unique<qx::file_logger_stream>(
            true,
            qx::log_file_policy::clear_then_uppend,
            traits_t::GetLogsFile());
        pFileLoggerStream->deregister_unit(qx::base_logger_stream::k_svDefaultUnit);
        pFileLoggerStream->register_unit(traits_t::GetUnit(), { qx::log_level::log });

        if constexpr (traits_t::GetCategory() == LOG_CATEGORY_TAG1)
        {
            pFileLoggerStream->register_unit(
                traits_t::GetCategory(),
                { qx::log_level::log,
                  [](qx::logger_buffer& buffers,
                     qx::log_level,
                     const qx::category& category,
                     qx::string_view     svFormat,
                     qx::string_view,
                     qx::string_view,
                     int,
                     va_list args)
                  {
                      buffers.sMessage.vsprintf(qx::string(svFormat).c_str(), args);
                      qx::base_logger_stream::format_time_string(buffers.sFormat, QX_TEXT('.'), QX_TEXT(':'));
                      buffers.sMessage = qx::string(QX_TEXT("   [")) + buffers.sFormat + QX_TEXT("][")
                                         + category.get_name() + QX_TEXT("] ") + buffers.sMessage + QX_TEXT('\n');
                  } });
        }

        m_pLogger->add_stream(std::move(pConsoleLoggerStream));
        m_pLogger->add_stream(std::move(pFileLoggerStream));
    }

    /* called after every test */
    virtual void TearDown() override
    {
        if (traits_t::GetUnit() == UNIT_DEFAULT
            || traits_t::GetUnit() == UNIT_FILE && traits_t::GetUnit() == traits_t::GetTraceFile()
            || traits_t::GetUnit() == UNIT_FUNC && m_bFunction)
        {
            const std::filesystem::path path(m_sLogFilePath.c_str());
            std::ifstream               ifs(path);

            std::string                                   sLine(512, QX_TEXT('\0'));
            std::match_results<qx::string::const_pointer> match;
            qx::string                                    sFormat;
            std::basic_regex<qx::char_type>               regex;
            qx::string                                    sFile;

            constexpr const qx::char_type* pszInfo    = QX_TEXT("   ");
            constexpr const qx::char_type* pszWarning = QX_TEXT("\\[W\\]");
            constexpr const qx::char_type* pszError   = QX_TEXT("\\[E\\]");
            constexpr const qx::char_type* pszAssert  = QX_TEXT("\\[C\\]");
            constexpr const qx::char_type* pszDate    = QX_TEXT("\\[\\d{2}.\\d{2}.\\d{4}_");
            constexpr const qx::char_type* pszTime    = QX_TEXT("\\d{2}:\\d{2}:\\d{2}\\]");

            auto CheckRegex = [&regex, &match](const qx::string& sMatch, const qx::string& sText)
            {
                regex = std::basic_regex(sMatch.data());
                EXPECT_TRUE(std::regex_search(std::basic_string(sText.c_str()).c_str(), match, regex))
                    << "regex:           " << qx::to_cstring(sMatch).c_str() << std::endl
                    << "line:            " << qx::to_cstring(sText).c_str() << std::endl
                    << "logs unit:       " << qx::to_cstring(traits_t::GetUnit()).c_str() << std::endl
                    << "logs trace file: " << qx::to_cstring(traits_t::GetTraceFile()).c_str();
            };

            auto CheckStringCommon = [&sFormat, &sFile, &ifs, &sLine, &CheckRegex](
                                         const qx::char_type* pszStringStarting,
                                         const qx::char_type* pszStringEnding,
                                         bool                 bCategory = false)
            {
                sFile.clear();
                if (bCategory && traits_t::GetCategory())
                {
                    sFile += QX_TEXT("\\[");
                    sFile += traits_t::GetCategory();
                    sFile += QX_TEXT("\\]");
                }
                sFile += QX_TEXT("\\[");
                sFile += traits_t::GetTraceFile();
                sFile += QX_TEXT("::");

                constexpr const qx::char_type* pszFunc = QX_TEXT("(.*?)"); // compiler-dependent
                constexpr const qx::char_type* pszLine = QX_TEXT("::\\d+\\]");

                sFormat.clear();
                sFormat += pszStringStarting;
                sFormat += pszDate;
                sFormat += pszTime;
                sFormat += sFile;
                sFormat += pszFunc;
                sFormat += pszLine;
                sFormat += pszStringEnding;

                ifs.getline(sLine.data(), static_cast<std::streamsize>(sLine.size()));

                CheckRegex(sFormat, sLine);
            };

            auto CheckStringCategory = [&sFormat, &ifs, &sLine, &CheckRegex](const qx::char_type* pszStringEnding)
            {
                sFormat.clear();
                sFormat += pszInfo;
                sFormat += pszDate;
                sFormat += pszTime;
                sFormat += QX_TEXT("\\[");
                sFormat += traits_t::GetCategory();
                sFormat += QX_TEXT("\\]");
                sFormat += pszStringEnding;

                ifs.getline(sLine.data(), static_cast<std::streamsize>(sLine.size()));
                CheckRegex(sFormat, sLine);
            };

            CheckStringCommon(pszInfo, QX_TEXT(" Start test"));

            CheckStringCommon(pszInfo, QX_TEXT(" 1.000000"));
            CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 1"));
            CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 2"));
            CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 3"));
            CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 4"));
            CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 5"));

            CheckStringCommon(pszWarning, QX_TEXT(" 1.000000"));
            CheckStringCommon(pszWarning, QX_TEXT(" 1.000000 1"));
            CheckStringCommon(pszWarning, QX_TEXT(" 1.000000 2"));
            CheckStringCommon(pszWarning, QX_TEXT(" 1.000000 3"));
            CheckStringCommon(pszWarning, QX_TEXT(" 1.000000 4"));
            CheckStringCommon(pszWarning, QX_TEXT(" 1.000000 5"));

            CheckStringCommon(pszError, QX_TEXT(" 1.000000 1"));
            CheckStringCommon(pszError, QX_TEXT(" 1.000000 2"));
            CheckStringCommon(pszError, QX_TEXT(" 1.000000 3"));
            CheckStringCommon(pszError, QX_TEXT(" 1.000000 4"));
            CheckStringCommon(pszError, QX_TEXT(" 1.000000 5"));

            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 1"));
            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 2"));
            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 3"));
            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 4"));
            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 5"));

            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 1 three"));
            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 2 three"));
            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 3 three"));
            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 4 three"));
            CheckStringCommon(pszAssert, QX_TEXT(" \\[false\\] 1.000000 5 three"));

            if constexpr (LOG_CATEGORY_TAG1 == traits_t::GetCategory())
            {
                CheckStringCategory(QX_TEXT(" 1.000000"));
                CheckStringCategory(QX_TEXT(" 1.000000 1"));
                CheckStringCategory(QX_TEXT(" 1.000000 2"));
                CheckStringCategory(QX_TEXT(" 1.000000 3"));
                CheckStringCategory(QX_TEXT(" 1.000000 4"));
                CheckStringCategory(QX_TEXT(" 1.000000 5"));
            }
            else
            {
                CheckStringCommon(pszInfo, QX_TEXT(" 1.000000"), true);
                CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 1"), true);
                CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 2"), true);
                CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 3"), true);
                CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 4"), true);
                CheckStringCommon(pszInfo, QX_TEXT(" 1.000000 5"), true);
            }

            CheckStringCommon(pszInfo, QX_TEXT(" End test"));

            ifs.close();
        }

        m_bFunction = false;
    }

protected:
    std::unique_ptr<qx::logger> m_pLogger;
    bool                        m_bFunction = false;
    qx::string                  m_sLogFilePath;
};

TYPED_TEST_SUITE(TestLogger, Implementations);

#define TEST_LOG(traceFile, format, ...) \
    myLogger.log(                        \
        qx::log_level::log,              \
        format,                          \
        qx::category { nullptr },        \
        traceFile,                       \
        qx::to_string(__FUNCTION__),     \
        __LINE__,                        \
        ##__VA_ARGS__)

#define TEST_LOG_WARNING(traceFile, format, ...) \
    myLogger.log(                                \
        qx::log_level::warning,                  \
        format,                                  \
        qx::category { nullptr },                \
        traceFile,                               \
        qx::to_string(__FUNCTION__),             \
        __LINE__,                                \
        ##__VA_ARGS__)

#define TEST_LOG_CATEGORY(traceFile, _category, format, ...) \
    myLogger.log(                                            \
        qx::log_level::log,                                  \
        format,                                              \
        qx::category { _category },                          \
        traceFile,                                           \
        qx::to_string(__FUNCTION__),                         \
        __LINE__,                                            \
        ##__VA_ARGS__)

#define TEST_LOG_ERROR(traceFile, format, ...) \
    myLogger.log(                              \
        qx::log_level::error,                  \
        format,                                \
        qx::category { nullptr },              \
        traceFile,                             \
        qx::to_string(__FUNCTION__),           \
        __LINE__,                              \
        ##__VA_ARGS__)

#define TEST_LOG_ASSERT(traceFile, expr, format, ...)                                                              \
    myLogger.log(                                                                                                  \
        qx::log_level::critical,                                                                                   \
        qx::string(QX_TEXT("[")) + qx::get_format_specifier<qx::char_type, const qx::char_type*>() + QX_TEXT("] ") \
            + format,                                                                                              \
        qx::category { nullptr },                                                                                  \
        traceFile,                                                                                                 \
        qx::to_string(__FUNCTION__),                                                                               \
        __LINE__,                                                                                                  \
        QX_TEXT(#expr),                                                                                            \
        ##__VA_ARGS__)

#define TEST_LOGGER(traceFile, _category)                                                          \
    TEST_LOG(traceFile, QX_TEXT("Start test"));                                                    \
                                                                                                   \
    TEST_LOG(traceFile, QX_TEXT("%f"), 1.f);                                                       \
    TEST_LOG(traceFile, QX_TEXT("%f %d"), 1.f, 1);                                                 \
    TEST_LOG(traceFile, QX_TEXT("%f %d"), 1.f, 2);                                                 \
    TEST_LOG(traceFile, QX_TEXT("%f %d"), 1.f, 3);                                                 \
    TEST_LOG(traceFile, QX_TEXT("%f %d"), 1.f, 4);                                                 \
    TEST_LOG(traceFile, QX_TEXT("%f %d"), 1.f, 5);                                                 \
                                                                                                   \
    TEST_LOG_WARNING(traceFile, QX_TEXT("%f"), 1.f);                                               \
    TEST_LOG_WARNING(traceFile, QX_TEXT("%f %d"), 1.f, 1);                                         \
    TEST_LOG_WARNING(traceFile, QX_TEXT("%f %d"), 1.f, 2);                                         \
    TEST_LOG_WARNING(traceFile, QX_TEXT("%f %d"), 1.f, 3);                                         \
    TEST_LOG_WARNING(traceFile, QX_TEXT("%f %d"), 1.f, 4);                                         \
    TEST_LOG_WARNING(traceFile, QX_TEXT("%f %d"), 1.f, 5);                                         \
                                                                                                   \
    TEST_LOG_ERROR(traceFile, QX_TEXT("%f %d"), 1.f, 1);                                           \
    TEST_LOG_ERROR(traceFile, QX_TEXT("%f %d"), 1.f, 2);                                           \
    TEST_LOG_ERROR(traceFile, QX_TEXT("%f %d"), 1.f, 3);                                           \
    TEST_LOG_ERROR(traceFile, QX_TEXT("%f %d"), 1.f, 4);                                           \
    TEST_LOG_ERROR(traceFile, QX_TEXT("%f %d"), 1.f, 5);                                           \
                                                                                                   \
    TEST_LOG_ASSERT(traceFile, false, QX_TEXT("%f %d"), 1.f, 1);                                   \
    TEST_LOG_ASSERT(traceFile, false, QX_TEXT("%f %d"), 1.f, 2);                                   \
    TEST_LOG_ASSERT(traceFile, false, QX_TEXT("%f %d"), 1.f, 3);                                   \
    TEST_LOG_ASSERT(traceFile, false, QX_TEXT("%f %d"), 1.f, 4);                                   \
    TEST_LOG_ASSERT(traceFile, false, QX_TEXT("%f %d"), 1.f, 5);                                   \
                                                                                                   \
    TEST_LOG_ASSERT(                                                                               \
        traceFile,                                                                                 \
        false,                                                                                     \
        qx::string(QX_TEXT("%f %d "))                                                              \
            + QX_SINGLE_ARGUMENT(qx::get_format_specifier<qx::char_type, const qx::char_type*>()), \
        1.f,                                                                                       \
        1,                                                                                         \
        QX_TEXT("three"));                                                                         \
    TEST_LOG_ASSERT(                                                                               \
        traceFile,                                                                                 \
        false,                                                                                     \
        qx::string(QX_TEXT("%f %d "))                                                              \
            + QX_SINGLE_ARGUMENT(qx::get_format_specifier<qx::char_type, const qx::char_type*>()), \
        1.f,                                                                                       \
        2,                                                                                         \
        QX_TEXT("three"));                                                                         \
    TEST_LOG_ASSERT(                                                                               \
        traceFile,                                                                                 \
        false,                                                                                     \
        qx::string(QX_TEXT("%f %d "))                                                              \
            + QX_SINGLE_ARGUMENT(qx::get_format_specifier<qx::char_type, const qx::char_type*>()), \
        1.f,                                                                                       \
        3,                                                                                         \
        QX_TEXT("three"));                                                                         \
    TEST_LOG_ASSERT(                                                                               \
        traceFile,                                                                                 \
        false,                                                                                     \
        qx::string(QX_TEXT("%f %d "))                                                              \
            + QX_SINGLE_ARGUMENT(qx::get_format_specifier<qx::char_type, const qx::char_type*>()), \
        1.f,                                                                                       \
        4,                                                                                         \
        QX_TEXT("three"));                                                                         \
    TEST_LOG_ASSERT(                                                                               \
        traceFile,                                                                                 \
        false,                                                                                     \
        qx::string(QX_TEXT("%f %d "))                                                              \
            + QX_SINGLE_ARGUMENT(qx::get_format_specifier<qx::char_type, const qx::char_type*>()), \
        1.f,                                                                                       \
        5,                                                                                         \
        QX_TEXT("three"));                                                                         \
                                                                                                   \
    TEST_LOG_CATEGORY(traceFile, _category, QX_TEXT("%f"), 1.f);                                   \
    TEST_LOG_CATEGORY(traceFile, _category, QX_TEXT("%f %d"), 1.f, 1);                             \
    TEST_LOG_CATEGORY(traceFile, _category, QX_TEXT("%f %d"), 1.f, 2);                             \
    TEST_LOG_CATEGORY(traceFile, _category, QX_TEXT("%f %d"), 1.f, 3);                             \
    TEST_LOG_CATEGORY(traceFile, _category, QX_TEXT("%f %d"), 1.f, 4);                             \
    TEST_LOG_CATEGORY(traceFile, _category, QX_TEXT("%f %d"), 1.f, 5);                             \
                                                                                                   \
    TEST_LOG(traceFile, QX_TEXT("End test\n"));

void TestLoggerFunction(qx::logger& myLogger, const qx::char_type* pszTraceFile, const qx::char_type* pszCategory)
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

QX_POP_SUPPRESS_WARNINGS();
