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

#include <qx/other/logger.h>
#include <gtest/gtest.h>

#define TRACE(format, ...)              QX_TRACE_FROM(myLogger, format, ## __VA_ARGS__)
#define TRACE_ERROR(format, ...)        QX_TRACE_ERROR_FROM(myLogger, format, ## __VA_ARGS__)
#define TRACE_ASSERT(expr, format, ...) QX_TRACE_ASSERT_FROM(myLogger, expr, format, ## __VA_ARGS__)


template <
    // conditions
    qx::logger::policy  ePolicy,
    void                RegisterUnits(qx::logger&),
    const char          sFolder[],
    // check and reset
    void                TearDown(qx::logger&)
>
struct LoggerTraits
{
    constexpr static auto GetPolicy()            { return ePolicy;       }
    constexpr static auto GetRegisterUnitsFunc() { return RegisterUnits; }
    constexpr static auto GetFolder()            { return sFolder;       }
    constexpr static auto GetTearDownFunc()      { return TearDown;      }
};

//==============================================================================
//
//!\class                      TestLogger<Traits>
//
//!\brief
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
        m_Logger.set_logs_folder(Traits::GetFolder());
        m_Logger.set_log_policy(Traits::GetPolicy());
        Traits::GetRegisterUnitsFunc()(m_Logger);
    }

    /* called before every test */
    void SetUp()
    {
    }

    /* called after every test */
    void TearDown()
    {
        Traits::GetTearDownFunc()(m_Logger);
    }

protected:

    qx::logger m_Logger;
};


void RegisterUnits_void(qx::logger& logger)
{
}


constexpr const char FOLDER_1[] = "";
constexpr const char FOLDER_2[] = "logs";
constexpr const char FOLDER_3[] = "LOGS_F";


void TearDown_Suit1(qx::logger& logger)
{
    EXPECT_TRUE(std::filesystem::exists("default.log"));
    //std::remove("default.log");
}

using Suit1 = LoggerTraits<qx::logger::policy::append, RegisterUnits_void, FOLDER_1, TearDown_Suit1>;

using Implementations = ::testing::Types
<
    Suit1
>;

TYPED_TEST_SUITE(TestLogger, Implementations);

#define TEST_LOGGER                                     \
    TRACE("Start test");                                \
    TRACE("%f %d %s", 1.f, 2, "three");                 \
    TRACE_ERROR("%f %d %s", 1.f, 2, "three");           \
    TRACE_ASSERT(false, "%f %d %s", 1.f, 2, "three");   \
    TRACE("End test\n");

void TestLoggerFunction(qx::logger& myLogger)
{
    TEST_LOGGER
}

TYPED_TEST(TestLogger, function)
{
    TestLoggerFunction(TestFixture::m_Logger);
}

TYPED_TEST(TestLogger, method)
{
    auto& myLogger = TestFixture::m_Logger;
    TEST_LOGGER
}

TYPED_TEST(TestLogger, lambda)
{
    auto TestLoggerLambda = [](auto& myLogger)
    {
        TEST_LOGGER
    };

    TestLoggerLambda(TestFixture::m_Logger);
}

#endif