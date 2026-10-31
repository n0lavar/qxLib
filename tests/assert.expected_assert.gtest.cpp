/**

    @file      assert.expected_assert.gtest.cpp
    @author    Khrapov
    @date      31.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

#include <qx/asserts/expected_assert.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <gtest/gtest-spi.h>
QX_POP_SUPPRESS_WARNINGS();

#include <cstdlib>
#include <thread>

QX_DEFINE_CATEGORY(CatOtherExpectedAssert, qx::color::white());

/**

    @class  scoped_disable_gtest_break
    @brief  Temporarily disable Google Test breaks for an intentionally reported failure.
    @author Khrapov
    @date   31.10.2026

**/
class scoped_disable_gtest_break
{
public:
    scoped_disable_gtest_break();
    ~scoped_disable_gtest_break();

private:
    bool m_bPrevious;
};

inline scoped_disable_gtest_break::scoped_disable_gtest_break() : m_bPrevious(GTEST_FLAG_GET(break_on_failure))
{
    GTEST_FLAG_SET(break_on_failure, false);
}

inline scoped_disable_gtest_break::~scoped_disable_gtest_break()
{
    GTEST_FLAG_SET(break_on_failure, m_bPrevious);
}

TEST(expected_assert_tests, restores_gtest_break_setting)
{
    const bool bPrevious = GTEST_FLAG_GET(break_on_failure);
    {
        scoped_disable_gtest_break disableBreak;
        EXPECT_FALSE(GTEST_FLAG_GET(break_on_failure));
    }
    EXPECT_EQ(GTEST_FLAG_GET(break_on_failure), bPrevious);
}

TEST(expected_assert_tests, matches_type_and_message_and_forwards_other_assertions)
{
    qx::asserts_manager&              manager        = qx::asserts_manager::get_instance();
    const qx::asserts_manager::config previousConfig = manager.get_config();
    qx::asserts_manager::config       config         = previousConfig;
    size_t                            nForwarded     = 0;
    config.bLogAssertion                             = false;
    config.onAssertion                               = [&nForwarded](
                             qx::string_view,
                             const qx::category&,
                             qx::assert_type,
                             qx::string_view,
                             qx::string_view,
                             qx::string_view,
                             i32)
    {
        ++nForwarded;
    };
    manager.set_config(std::move(config));
    {
        qx::expected_assert expected = qx::expected_assert_builder()
                                           .condition(QXT("false"))
                                           .message(QXT("value [0-9]+"), true)
                                           .count(2)
                                           .type(qx::assert_type::expect)
                                           .build();
        QX_EXPECT(false, "value {}", 42);

        const bool bCondition = false;
#undef QX_DEBUG_BREAK
#define QX_DEBUG_BREAK() (void)0
        QX_EXPECT(false, "other");
        QX_EXPECT(bCondition, "value {}", 42);
#undef QX_DEBUG_BREAK
#define QX_DEBUG_BREAK() _QX_DEBUG_BREAK()

        QX_EXPECT(false, "value {}", 13);
#if QX_WITH_DEBUG_ASSERTS
    #undef QX_DEBUG_BREAK
    #define QX_DEBUG_BREAK() (void)0
        QX_ENSURE(false, "value {}", 99);
    #undef QX_DEBUG_BREAK
    #define QX_DEBUG_BREAK() _QX_DEBUG_BREAK()
#endif
    }
    manager.set_config(previousConfig);
    EXPECT_EQ(nForwarded, 2 + (QX_WITH_DEBUG_ASSERTS ? 1 : 0));
}

TEST(expected_assert_tests, supports_simultaneous_expectations)
{
    qx::expected_assert first = qx::expected_assert_builder()
                                    .condition(QXT("false"))
                                    .message(QXT("first"))
                                    .count(2)
                                    .type(qx::assert_type::expect)
                                    .build();
    qx::expected_assert second = qx::expected_assert_builder()
                                     .condition(QXT("false"))
                                     .message(QXT("second"))
                                     .type(qx::assert_type::expect)
                                     .build();
    QX_EXPECT(false, "first");
    QX_EXPECT(false, "second");
    QX_EXPECT(false, "first");
}

TEST(expected_assert_tests, reports_missing_and_excess_assertions)
{
    EXPECT_NONFATAL_FAILURE(
        {
            scoped_disable_gtest_break disableBreak;
            qx::expected_assert        expected = qx::expected_assert_builder().message(QXT("missing")).build();
        },
        "Expected 1 matching assertions, got 0");
    EXPECT_NONFATAL_FAILURE(
        {
            scoped_disable_gtest_break disableBreak;
            qx::expected_assert        expected = qx::expected_assert_builder().message(QXT("extra")).build();
            QX_EXPECT(false, "extra");
            QX_EXPECT(false, "extra");
        },
        "Expected 1 matching assertions, got 2");
}

static void run_expected_fatal_assert(qx::assert_type eExpectedType)
{
    qx::asserts_manager::config config = qx::asserts_manager::get_instance().get_config();
    config.onAssertion                 = [](qx::string_view,
                            const qx::category&,
                            qx::assert_type,
                            qx::string_view,
                            qx::string_view,
                            qx::string_view,
                            i32)
    {
        std::exit(77);
    };
    config.onExit = [eExpectedType](const qx::category&, qx::assert_type eType)
    {
        std::exit(eType == eExpectedType ? 42 : 78);
    };
    qx::asserts_manager::get_instance().set_config(std::move(config));
    qx::expected_assert expected = qx::expected_assert_builder()
                                       .condition(QXT("false"))
                                       .message(QXT("expected fatal"))
                                       .type(eExpectedType)
                                       .build();
    if (eExpectedType == qx::assert_type::verify)
    {
        QX_VERIFY(false, "expected fatal");
    }
    else
    {
        QX_ASSERT(false, "expected fatal");
    }
    std::exit(99);
}

TEST(expected_assert_tests, matched_verify_calls_fatal_exit)
{
    EXPECT_EXIT(run_expected_fatal_assert(qx::assert_type::verify), ::testing::ExitedWithCode(42), "");
}

#if QX_WITH_DEBUG_ASSERTS
TEST(expected_assert_tests, matched_assert_calls_fatal_exit)
{
    EXPECT_EXIT(run_expected_fatal_assert(qx::assert_type::assert), ::testing::ExitedWithCode(42), "");
}
#endif

TEST(expected_assert_tests, counts_matches_from_multiple_threads)
{
    constexpr size_t    nThreads = 4;
    constexpr size_t    nCalls   = 100;
    qx::expected_assert expected =
        qx::expected_assert_builder().message(QXT("parallel")).count(nThreads * nCalls).build();
    std::vector<std::thread> threads;
    for (size_t i = 0; i < nThreads; ++i)
    {
        threads.emplace_back(
            []
            {
                for (size_t j = 0; j < nCalls; ++j)
                    QX_EXPECT(false, "parallel");
            });
    }
    for (std::thread& thread : threads)
        thread.join();
}

// These tests deliberately send non-matching assertions through the normal callback.
#undef QX_DEBUG_BREAK
#define QX_DEBUG_BREAK() (void)0
static void trigger_expected_assert_test()
{
    QX_EXPECT_C(false, CatOtherExpectedAssert, "message.");
}
#undef QX_DEBUG_BREAK
#define QX_DEBUG_BREAK() _QX_DEBUG_BREAK()

TEST(expected_assert_tests, matches_all_selected_fields)
{
    qx::asserts_manager&              manager        = qx::asserts_manager::get_instance();
    const qx::asserts_manager::config previousConfig = manager.get_config();
    qx::asserts_manager::config       config         = previousConfig;
    size_t                            nForwarded     = 0;
    qx::string                        sFunction;
    qx::string                        sFile;
    i32                               nLine = 0;
    config.bLogAssertion                    = false;
    config.onAssertion                      = [&](qx::string_view,
                             const qx::category&,
                             qx::assert_type,
                             qx::string_view,
                             qx::string_view svFunction,
                             qx::string_view svFile,
                             i32             nAssertLine)
    {
        ++nForwarded;
        sFunction = svFunction;
        sFile     = svFile;
        nLine     = nAssertLine;
    };
    manager.set_config(std::move(config));
    trigger_expected_assert_test();

    size_t     nExpectedForwarded = 1;
    const auto CheckMismatch      = [&](qx::expected_assert_builder builder)
    {
        {
            qx::expected_assert expected = builder.count(0).build();
            trigger_expected_assert_test();
        }
        EXPECT_EQ(nForwarded, ++nExpectedForwarded);
    };
    CheckMismatch(qx::expected_assert_builder().condition(QXT("true")));
    CheckMismatch(qx::expected_assert_builder().category(CatDefault));
    CheckMismatch(qx::expected_assert_builder().type(qx::assert_type::ensure));
    CheckMismatch(qx::expected_assert_builder().message(QXT("wrong")));
    CheckMismatch(qx::expected_assert_builder().function(QXT("wrong")));
    CheckMismatch(qx::expected_assert_builder().file(QXT("wrong")));
    CheckMismatch(qx::expected_assert_builder().line(nLine + 1));


    {
        qx::expected_assert expected = qx::expected_assert_builder()
                                           .condition(QXT("fals[e]"), true)
                                           .category(CatOtherExpectedAssert)
                                           .type(qx::assert_type::expect)
                                           .message(QXT("message[.]"), true)
                                           .function(QXT("trigger_expected_assert_test"), true)
                                           .file(QXT("assert[.]expected_assert[.]gtest[.]cpp$"), true)
                                           .line(nLine)
                                           .build();
        trigger_expected_assert_test();
    }
    EXPECT_EQ(nForwarded, nExpectedForwarded);
    manager.set_config(previousConfig);
}

TEST(expected_assert_tests, ignores_unspecified_fields)
{
    qx::expected_assert expected = qx::expected_assert_builder().condition(QXT("false")).count(2).build();
    QX_EXPECT(false, "first");
#if QX_WITH_DEBUG_ASSERTS
    QX_ENSURE(false, "second");
#else
    QX_EXPECT(false, "second");
#endif
}

TEST(expected_assert_tests, strings_match_exactly_by_default)
{
    qx::asserts_manager&              manager        = qx::asserts_manager::get_instance();
    const qx::asserts_manager::config previousConfig = manager.get_config();
    qx::asserts_manager::config       config         = previousConfig;
    size_t                            nForwarded     = 0;
    qx::string                        sFunction;
    qx::string                        sFile;
    config.bLogAssertion = false;
    config.onAssertion   = [&](qx::string_view,
                             const qx::category&,
                             qx::assert_type,
                             qx::string_view,
                             qx::string_view svFunction,
                             qx::string_view svFile,
                             i32)
    {
        ++nForwarded;
        sFunction = svFunction;
        sFile     = svFile;
    };
    manager.set_config(std::move(config));
    trigger_expected_assert_test();

    size_t     nExpectedForwarded = 1;
    const auto CheckMismatch      = [&](qx::expected_assert_builder builder)
    {
        {
            qx::expected_assert expected = builder.count(0).build();
            trigger_expected_assert_test();
        }
        EXPECT_EQ(nForwarded, ++nExpectedForwarded);
    };
    CheckMismatch(qx::expected_assert_builder().condition(QXT("fals")));
    CheckMismatch(qx::expected_assert_builder().message(QXT("message")));
    CheckMismatch(qx::expected_assert_builder().function(QXT("prefix ") + sFunction));
    CheckMismatch(qx::expected_assert_builder().file(QXT("prefix ") + sFile));


    {
        qx::expected_assert expected = qx::expected_assert_builder()
                                           .condition(QXT("false"))
                                           .message(QXT("message."))
                                           .function(sFunction)
                                           .file(sFile)
                                           .build();
        trigger_expected_assert_test();
    }
    EXPECT_EQ(nForwarded, nExpectedForwarded);
    manager.set_config(previousConfig);
}

TEST(expected_assert_tests, reports_selected_expectation_details)
{
    ::testing::TestPartResultArray failures;
    {
        ::testing::ScopedFakeTestPartResultReporter reporter(
            ::testing::ScopedFakeTestPartResultReporter::INTERCEPT_ONLY_CURRENT_THREAD,
            &failures);
        {
            scoped_disable_gtest_break disableBreak;
            qx::expected_assert        expected = qx::expected_assert_builder()
                                               .condition(QXT("x > [0-9]+"), true)
                                               .category(CatOtherExpectedAssert)
                                               .type(qx::assert_type::expect)
                                               .message(QXT("bad value"))
                                               .function(QXT("test.*"), true)
                                               .file(QXT("file.cpp"))
                                               .line(42)
                                               .count(2)
                                               .build();
        }
    }

    ASSERT_EQ(failures.size(), 1);
    const std::string sReport = failures.GetTestPartResult(0).message();
    EXPECT_NE(sReport.find("Expected 2 matching assertions, got 0"), std::string::npos);
    EXPECT_NE(sReport.find("condition (regex): x > [0-9]+"), std::string::npos);
    EXPECT_NE(sReport.find("category: CatOtherExpectedAssert"), std::string::npos);
    EXPECT_NE(sReport.find("type: expect"), std::string::npos);
    EXPECT_NE(sReport.find("message: bad value"), std::string::npos);
    EXPECT_NE(sReport.find("function (regex): test.*"), std::string::npos);
    EXPECT_NE(sReport.find("file: file.cpp"), std::string::npos);
    EXPECT_NE(sReport.find("line: 42"), std::string::npos);
}

TEST(expected_assert_tests, omits_unspecified_expectation_details)
{
    ::testing::TestPartResultArray failures;
    {
        ::testing::ScopedFakeTestPartResultReporter reporter(
            ::testing::ScopedFakeTestPartResultReporter::INTERCEPT_ONLY_CURRENT_THREAD,
            &failures);
        {
            scoped_disable_gtest_break disableBreak;
            qx::expected_assert        expected = qx::expected_assert_builder().condition(QXT("false")).build();
        }
    }

    ASSERT_EQ(failures.size(), 1);
    const std::string sReport = failures.GetTestPartResult(0).message();
    EXPECT_NE(sReport.find("condition: false"), std::string::npos);
    EXPECT_EQ(sReport.find("category:"), std::string::npos);
    EXPECT_EQ(sReport.find("type:"), std::string::npos);
    EXPECT_EQ(sReport.find("message:"), std::string::npos);
    EXPECT_EQ(sReport.find("function:"), std::string::npos);
    EXPECT_EQ(sReport.find("file:"), std::string::npos);
    EXPECT_EQ(sReport.find("line:"), std::string::npos);
}
