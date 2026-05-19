/**

    @file      assert.gtest.cpp
    @author    Khrapov
    @date      29.10.2020
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

#define QX_DEBUG_BREAK() (void)0

#include <qx/asserts/asserts.h>
#include <qx/logger/cout_logger_stream.h>

#include <string>

//V_EXCLUDE_PATH *.gtest.cpp

QX_SET_FILE_CATEGORY(CatDefault);

QX_DEFINE_CATEGORY(CatAssertsTests, qx::color::white());

static_assert(qx::details::trim_assert_expression(QXT(" nValue\t")) == QXT("nValue"));
static_assert(qx::details::split_assert_arguments(QXT("qx::assert_equal(nValue, 42)")).first == QXT("nValue"));
static_assert(qx::details::split_assert_arguments(QXT("qx::assert_equal(nValue, 42)")).second == QXT("42"));

class assert_exit_tests_fixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        qx::get_logger().reset();
        qx::get_logger().add_stream(qx::cout_logger_stream());
    }

    void TearDown() override
    {
        qx::get_logger().reset();
    }
};

TEST_F(assert_exit_tests_fixture, assert)
{
#if QX_WITH_DEBUG_ASSERTS
    EXPECT_EXIT({ QX_ASSERT(0); }, ::testing::ExitedWithCode(0), "\\[0\\]");
    EXPECT_EXIT({ QX_ASSERT(0, ""); }, ::testing::ExitedWithCode(0), "\\[0\\]");
    EXPECT_EXIT({ QX_ASSERT_C(0, CatAssertsTests); }, ::testing::ExitedWithCode(0), "\\[0\\]");
    EXPECT_EXIT({ QX_ASSERT_C(0, CatAssertsTests, ""); }, ::testing::ExitedWithCode(0), "\\[0\\]");
    EXPECT_EXIT({ QX_ASSERT(QX_NO_ENTRY); }, ::testing::ExitedWithCode(0), "\\[\\!\"No entry\"\\]");
    EXPECT_EXIT({ QX_ASSERT(QX_NO_ENTRY, "{}", 42); }, ::testing::ExitedWithCode(0), "\\[\\!\"No entry\"\\] 42");
    EXPECT_EXIT({ QX_ASSERT_C(QX_NO_ENTRY, CatAssertsTests); }, ::testing::ExitedWithCode(0), "\\[\\!\"No entry\"\\]");
    EXPECT_EXIT(
        { QX_ASSERT_C(QX_NO_ENTRY, CatAssertsTests, "{}", 42); },
        ::testing::ExitedWithCode(0),
        "\\[\\!\"No entry\"\\] 42");
#else
    // must not crash, as it must expand to nothing
    QX_ASSERT(0);
    QX_ASSERT(0, "");
    QX_ASSERT_C(0, CatDeCatAssertsTestsfault);
    QX_ASSERT_C(0, CatAssertsTests, "");
    QX_ASSERT(QX_NO_ENTRY);
    QX_ASSERT(QX_NO_ENTRY, "{}", 42);
    QX_ASSERT_C(QX_NO_ENTRY, CatAssertsTests);
    QX_ASSERT_C(QX_NO_ENTRY, CatAssertsTests, "{}", 42);
#endif
}

TEST_F(assert_exit_tests_fixture, verify)
{
    EXPECT_EXIT({ QX_VERIFY(0); }, ::testing::ExitedWithCode(0), "\\[0\\]");
    EXPECT_EXIT({ QX_VERIFY(0, ""); }, ::testing::ExitedWithCode(0), "\\[0\\]");
    EXPECT_EXIT({ QX_VERIFY_C(0, CatAssertsTests); }, ::testing::ExitedWithCode(0), "\\[0\\]");
    EXPECT_EXIT({ QX_VERIFY_C(0, CatAssertsTests, ""); }, ::testing::ExitedWithCode(0), "\\[0\\]");
    EXPECT_EXIT({ QX_VERIFY(QX_NO_ENTRY); }, ::testing::ExitedWithCode(0), "\\[\\!\"No entry\"\\]");
    EXPECT_EXIT({ QX_VERIFY(QX_NO_ENTRY, "{}", 42); }, ::testing::ExitedWithCode(0), "\\[\\!\"No entry\"\\] 42");
    EXPECT_EXIT({ QX_VERIFY_C(QX_NO_ENTRY, CatAssertsTests); }, ::testing::ExitedWithCode(0), "\\[\\!\"No entry\"\\]");
    EXPECT_EXIT(
        { QX_VERIFY_C(QX_NO_ENTRY, CatAssertsTests, "{}", 42); },
        ::testing::ExitedWithCode(0),
        "\\[\\!\"No entry\"\\] 42");
}

QX_PUSH_SUPPRESS_MSVC_WARNINGS(4189 4390 4702);

static void foo()
{
}

#define TEST_QX_ASSERT_COMMON(macro_call) \
    macro_call;                           \
                                          \
    if (false)                            \
        macro_call;                       \
                                          \
    if (false)                            \
        macro_call;                       \
    else                                  \
        foo();                            \
                                          \
    if (false)                            \
        foo();                            \
    else                                  \
        macro_call;                       \
                                          \
    if (false)                            \
    {                                     \
        macro_call;                       \
        foo();                            \
    }                                     \
                                          \
    if (false)                            \
        foo();                            \
    else                                  \
    {                                     \
        macro_call;                       \
        foo();                            \
    }

#define TEST_QX_ASSERT_COMMON_LOOP(macro_call) \
    do                                         \
    {                                          \
        TEST_QX_ASSERT_COMMON(macro_call);     \
    } while (false)

TEST(qx_assert, assert_compilation)
{
    GTEST_SKIP();

    TEST_QX_ASSERT_COMMON(QX_ASSERT(false));
    TEST_QX_ASSERT_COMMON(QX_ASSERT(false, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_ASSERT_C(false, CatAssertsTests));
    TEST_QX_ASSERT_COMMON(QX_ASSERT_C(false, CatAssertsTests, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_ASSERT(QX_NO_ENTRY));
    TEST_QX_ASSERT_COMMON(QX_ASSERT(QX_NO_ENTRY, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_ASSERT_C(QX_NO_ENTRY, CatAssertsTests));
    TEST_QX_ASSERT_COMMON(QX_ASSERT_C(QX_NO_ENTRY, CatAssertsTests, "msg {}", 41));
}

TEST(qx_assert, verify_compilation)
{
    GTEST_SKIP();

    TEST_QX_ASSERT_COMMON(QX_VERIFY(false));
    TEST_QX_ASSERT_COMMON(QX_VERIFY(false, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_VERIFY_C(false, CatAssertsTests));
    TEST_QX_ASSERT_COMMON(QX_VERIFY_C(false, CatAssertsTests, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_VERIFY(QX_NO_ENTRY));
    TEST_QX_ASSERT_COMMON(QX_VERIFY(QX_NO_ENTRY, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_VERIFY_C(QX_NO_ENTRY, CatAssertsTests));
    TEST_QX_ASSERT_COMMON(QX_VERIFY_C(QX_NO_ENTRY, CatAssertsTests, "msg {}", 41));
}

TEST(qx_assert, ensure_compilation)
{
    GTEST_SKIP();

    TEST_QX_ASSERT_COMMON(QX_ENSURE(false));
    TEST_QX_ASSERT_COMMON(QX_ENSURE(false, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_ENSURE_C(false, CatAssertsTests));
    TEST_QX_ASSERT_COMMON(QX_ENSURE_C(false, CatAssertsTests, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_ENSURE(QX_NO_ENTRY));
    TEST_QX_ASSERT_COMMON(QX_ENSURE(QX_NO_ENTRY, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_ENSURE_C(QX_NO_ENTRY, CatAssertsTests));
    TEST_QX_ASSERT_COMMON(QX_ENSURE_C(QX_NO_ENTRY, CatAssertsTests, "msg {}", 41));
}

#define TEST_QX_ASSERT_BOOL(macro_call) \
    TEST_QX_ASSERT_COMMON(macro_call);  \
                                        \
    if (macro_call)                     \
        ;                               \
                                        \
    const bool QX_LINE_NAME(_) = macro_call

TEST(qx_assert, expect_compilation)
{
    GTEST_SKIP();

    TEST_QX_ASSERT_BOOL(QX_EXPECT(false));
    TEST_QX_ASSERT_BOOL(QX_EXPECT(false, "msg {}", 41));
    TEST_QX_ASSERT_BOOL(QX_EXPECT_C(false, CatAssertsTests));
    TEST_QX_ASSERT_BOOL(QX_EXPECT_C(false, CatAssertsTests, "msg {}", 41));
    TEST_QX_ASSERT_BOOL(QX_EXPECT(QX_NO_ENTRY));
    TEST_QX_ASSERT_BOOL(QX_EXPECT(QX_NO_ENTRY, "msg {}", 41));
    TEST_QX_ASSERT_BOOL(QX_EXPECT_C(QX_NO_ENTRY, CatAssertsTests));
    TEST_QX_ASSERT_BOOL(QX_EXPECT_C(QX_NO_ENTRY, CatAssertsTests, "msg {}", 41));

    TEST_QX_ASSERT_COMMON_LOOP(QX_EXPECT_CONTINUE(false));
    TEST_QX_ASSERT_COMMON_LOOP(QX_EXPECT_CONTINUE(false, "msg {}", 41));
    TEST_QX_ASSERT_COMMON_LOOP(QX_EXPECT_CONTINUE_C(false, CatAssertsTests));
    TEST_QX_ASSERT_COMMON_LOOP(QX_EXPECT_CONTINUE_C(false, CatAssertsTests, "msg {}", 41));

    TEST_QX_ASSERT_COMMON_LOOP(QX_EXPECT_BREAK(false));
    TEST_QX_ASSERT_COMMON_LOOP(QX_EXPECT_BREAK(false, "msg {}", 41));
    TEST_QX_ASSERT_COMMON_LOOP(QX_EXPECT_BREAK_C(false, CatAssertsTests));
    TEST_QX_ASSERT_COMMON_LOOP(QX_EXPECT_BREAK_C(false, CatAssertsTests, "msg {}", 41));

    TEST_QX_ASSERT_COMMON(QX_EXPECT_RETURN(false));
    TEST_QX_ASSERT_COMMON(QX_EXPECT_RETURN(false, "msg {}", 41));
    TEST_QX_ASSERT_COMMON(QX_EXPECT_RETURN_C(false, CatAssertsTests));
    TEST_QX_ASSERT_COMMON(QX_EXPECT_RETURN_C(false, CatAssertsTests, "msg {}", 41));

    auto Check = []() -> int
    {
        TEST_QX_ASSERT_COMMON(QX_EXPECT_RETURN_T(false, 1));
        TEST_QX_ASSERT_COMMON(QX_EXPECT_RETURN_T(false, 1, "msg {}", 41));
        TEST_QX_ASSERT_COMMON(QX_EXPECT_RETURN_CT(false, CatAssertsTests, 1));
        TEST_QX_ASSERT_COMMON(QX_EXPECT_RETURN_CT(false, CatAssertsTests, 1, "msg {}", 41));
    };
}

QX_POP_SUPPRESS_WARNINGS();

class assert_callback_tests_fixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        auto config        = qx::asserts_manager::get_instance().get_config();
        config.onAssertion = [this](
                                 qx::string_view     svCondition,
                                 const qx::category& category,
                                 qx::assert_type     eAssertType,
                                 qx::string_view     svUserMessage,
                                 qx::string_view     svFunction,
                                 qx::string_view     svFile,
                                 i32                 nLine)
        {
            EXPECT_EQ(svCondition, m_svExpectedCondition);
            EXPECT_EQ(*m_pExpectedCategory, category);
            EXPECT_EQ(m_eExpectedAssertType, eAssertType);
            EXPECT_EQ(m_svExpectedUserMessage, svUserMessage);
            EXPECT_EQ(m_sExpectedFunction, svFunction);
            EXPECT_EQ(m_svExpectedFile, svFile);
            EXPECT_EQ(m_nExpectedLine, nLine);

            m_bHit = true;
        };
        config.onExit = nullptr;

        qx::asserts_manager::get_instance().set_config(std::move(config));
    }

    void TearDown() override
    {
        EXPECT_TRUE(m_bHit || !QX_WITH_DEBUG_ASSERTS);

        qx::asserts_manager::get_instance().set_config(qx::asserts_manager::config());
    }

protected:
    qx::string_view     m_svExpectedCondition;
    const qx::category* m_pExpectedCategory   = nullptr;
    qx::assert_type     m_eExpectedAssertType = qx::assert_type::assert;
    qx::string_view     m_svExpectedUserMessage;
    qx::string          m_sExpectedFunction;
    qx::string_view     m_svExpectedFile;
    i32                 m_nExpectedLine = 0;

private:
    bool m_bHit = false;
};

#define TEST_ON_ASSERTION(macro_call, condition, category, assert_type, user_message) \
    TEST_F(assert_callback_tests_fixture, QX_LINE_NAME(test_on_assertion_))           \
    {                                                                                 \
        this->m_svExpectedCondition   = QXT(QX_STRINGIFY(condition));                 \
        this->m_pExpectedCategory     = &category;                                    \
        this->m_eExpectedAssertType   = assert_type;                                  \
        this->m_svExpectedUserMessage = QXT(user_message);                            \
        this->m_sExpectedFunction     = qx::to_string(__FUNCTION__);                  \
        this->m_svExpectedFile        = QXT(__FILE__);                                \
        this->m_nExpectedLine         = QX_LINE;                                      \
                                                                                      \
        macro_call;                                                                   \
    }

#define TEST_ON_ASSERTION_LOOP(macro_call, condition, category, assert_type, user_message) \
    TEST_F(assert_callback_tests_fixture, QX_LINE_NAME(test_on_assertion_))                \
    {                                                                                      \
        this->m_svExpectedCondition   = QXT(QX_STRINGIFY(condition));                      \
        this->m_pExpectedCategory     = &category;                                         \
        this->m_eExpectedAssertType   = assert_type;                                       \
        this->m_svExpectedUserMessage = QXT(user_message);                                 \
        this->m_sExpectedFunction     = qx::to_string(__FUNCTION__);                       \
        this->m_svExpectedFile        = QXT(__FILE__);                                     \
        this->m_nExpectedLine         = QX_LINE;                                           \
                                                                                           \
        do                                                                                 \
        {                                                                                  \
            macro_call;                                                                    \
        } while (false);                                                                   \
    }

#define TEST_ON_ASSERTION_RETURN(macro_call, condition, category, assert_type, user_message) \
    TEST_F(assert_callback_tests_fixture, QX_LINE_NAME(test_on_assertion_))                  \
    {                                                                                        \
        auto Check = [this]() -> int                                                         \
        {                                                                                    \
            this->m_svExpectedCondition   = QXT(QX_STRINGIFY(condition));                    \
            this->m_pExpectedCategory     = &category;                                       \
            this->m_eExpectedAssertType   = assert_type;                                     \
            this->m_svExpectedUserMessage = QXT(user_message);                               \
            this->m_sExpectedFunction     = qx::to_string(__FUNCTION__);                     \
            this->m_svExpectedFile        = QXT(__FILE__);                                   \
            this->m_nExpectedLine         = QX_LINE;                                         \
                                                                                             \
            macro_call;                                                                      \
            return 0;                                                                        \
        };                                                                                   \
        Check();                                                                             \
    }

// clang-format off
TEST_ON_ASSERTION(QX_ASSERT(false),                                                      false,       CatDefault,      qx::assert_type::assert, "");
TEST_ON_ASSERTION(QX_ASSERT(false, "msg {}", 41),                                        false,       CatDefault,      qx::assert_type::assert, "msg 41");
TEST_ON_ASSERTION(QX_ASSERT_C(false, CatAssertsTests),                                   false,       CatAssertsTests, qx::assert_type::assert, "");
TEST_ON_ASSERTION(QX_ASSERT_C(false, CatAssertsTests, "msg {}", 41),                     false,       CatAssertsTests, qx::assert_type::assert, "msg 41");
TEST_ON_ASSERTION(QX_ASSERT(QX_NO_ENTRY),                                                QX_NO_ENTRY, CatDefault,      qx::assert_type::assert, "");
TEST_ON_ASSERTION(QX_ASSERT(QX_NO_ENTRY, "msg {}", 41),                                  QX_NO_ENTRY, CatDefault,      qx::assert_type::assert, "msg 41");
TEST_ON_ASSERTION(QX_ASSERT_C(QX_NO_ENTRY, CatAssertsTests),                             QX_NO_ENTRY, CatAssertsTests, qx::assert_type::assert, "");
TEST_ON_ASSERTION(QX_ASSERT_C(QX_NO_ENTRY, CatAssertsTests, "msg {}", 41),               QX_NO_ENTRY, CatAssertsTests, qx::assert_type::assert, "msg 41");
                                                                                         
TEST_ON_ASSERTION(QX_VERIFY(false),                                                      false,       CatDefault,      qx::assert_type::verify, "");
TEST_ON_ASSERTION(QX_VERIFY(false, "msg {}", 41),                                        false,       CatDefault,      qx::assert_type::verify, "msg 41");
TEST_ON_ASSERTION(QX_VERIFY_C(false, CatAssertsTests),                                   false,       CatAssertsTests, qx::assert_type::verify, "");
TEST_ON_ASSERTION(QX_VERIFY_C(false, CatAssertsTests, "msg {}", 41),                     false,       CatAssertsTests, qx::assert_type::verify, "msg 41");
TEST_ON_ASSERTION(QX_VERIFY(QX_NO_ENTRY),                                                QX_NO_ENTRY, CatDefault,      qx::assert_type::verify, "");
TEST_ON_ASSERTION(QX_VERIFY(QX_NO_ENTRY, "msg {}", 41),                                  QX_NO_ENTRY, CatDefault,      qx::assert_type::verify, "msg 41");
TEST_ON_ASSERTION(QX_VERIFY_C(QX_NO_ENTRY, CatAssertsTests),                             QX_NO_ENTRY, CatAssertsTests, qx::assert_type::verify, "");
TEST_ON_ASSERTION(QX_VERIFY_C(QX_NO_ENTRY, CatAssertsTests, "msg {}", 41),               QX_NO_ENTRY, CatAssertsTests, qx::assert_type::verify, "msg 41");
                                                                                         
TEST_ON_ASSERTION(QX_ENSURE(false),                                                      false,       CatDefault,      qx::assert_type::ensure, "");
TEST_ON_ASSERTION(QX_ENSURE(false, "msg {}", 41),                                        false,       CatDefault,      qx::assert_type::ensure, "msg 41");
TEST_ON_ASSERTION(QX_ENSURE_C(false, CatAssertsTests),                                   false,       CatAssertsTests, qx::assert_type::ensure, "");
TEST_ON_ASSERTION(QX_ENSURE_C(false, CatAssertsTests, "msg {}", 41),                     false,       CatAssertsTests, qx::assert_type::ensure, "msg 41");
TEST_ON_ASSERTION(QX_ENSURE(QX_NO_ENTRY),                                                QX_NO_ENTRY, CatDefault,      qx::assert_type::ensure, "");
TEST_ON_ASSERTION(QX_ENSURE(QX_NO_ENTRY, "msg {}", 41),                                  QX_NO_ENTRY, CatDefault,      qx::assert_type::ensure, "msg 41");
TEST_ON_ASSERTION(QX_ENSURE_C(QX_NO_ENTRY, CatAssertsTests),                             QX_NO_ENTRY, CatAssertsTests, qx::assert_type::ensure, "");
TEST_ON_ASSERTION(QX_ENSURE_C(QX_NO_ENTRY, CatAssertsTests, "msg {}", 41),               QX_NO_ENTRY, CatAssertsTests, qx::assert_type::ensure, "msg 41");
                                                                                         
TEST_ON_ASSERTION_LOOP(QX_EXPECT_CONTINUE(false),                                        false,       CatDefault,      qx::assert_type::expect, "");
TEST_ON_ASSERTION_LOOP(QX_EXPECT_CONTINUE(false, "msg {}", 41),                          false,       CatDefault,      qx::assert_type::expect, "msg 41");
TEST_ON_ASSERTION_LOOP(QX_EXPECT_CONTINUE_C(false, CatAssertsTests),                     false,       CatAssertsTests, qx::assert_type::expect, "");
TEST_ON_ASSERTION_LOOP(QX_EXPECT_CONTINUE_C(false, CatAssertsTests, "msg {}", 41),       false,       CatAssertsTests, qx::assert_type::expect, "msg 41");
                                                                                         
TEST_ON_ASSERTION_LOOP(QX_EXPECT_BREAK(false),                                           false,       CatDefault,      qx::assert_type::expect, "");
TEST_ON_ASSERTION_LOOP(QX_EXPECT_BREAK(false, "msg {}", 41),                             false,       CatDefault,      qx::assert_type::expect, "msg 41");
TEST_ON_ASSERTION_LOOP(QX_EXPECT_BREAK_C(false, CatAssertsTests),                        false,       CatAssertsTests, qx::assert_type::expect, "");
TEST_ON_ASSERTION_LOOP(QX_EXPECT_BREAK_C(false, CatAssertsTests, "msg {}", 41),          false,       CatAssertsTests, qx::assert_type::expect, "msg 41");
                                                                                         
TEST_ON_ASSERTION(QX_EXPECT_RETURN(false),                                               false,       CatDefault,      qx::assert_type::expect, "");
TEST_ON_ASSERTION(QX_EXPECT_RETURN(false, "msg {}", 41),                                 false,       CatDefault,      qx::assert_type::expect, "msg 41");
TEST_ON_ASSERTION(QX_EXPECT_RETURN_C(false, CatAssertsTests),                            false,       CatAssertsTests, qx::assert_type::expect, "");
TEST_ON_ASSERTION(QX_EXPECT_RETURN_C(false, CatAssertsTests, "msg {}", 41),              false,       CatAssertsTests, qx::assert_type::expect, "msg 41");
                                                                                         
TEST_ON_ASSERTION_RETURN(QX_EXPECT_RETURN_T(false, 1),                                   false,       CatDefault,      qx::assert_type::expect, "");
TEST_ON_ASSERTION_RETURN(QX_EXPECT_RETURN_T(false, 1, "msg {}", 41),                     false,       CatDefault,      qx::assert_type::expect, "msg 41");
TEST_ON_ASSERTION_RETURN(QX_EXPECT_RETURN_CT(false, CatAssertsTests, 1),                 false,       CatAssertsTests, qx::assert_type::expect, "");
TEST_ON_ASSERTION_RETURN(QX_EXPECT_RETURN_CT(false, CatAssertsTests, 1, "msg {}", 41),   false,       CatAssertsTests, qx::assert_type::expect, "msg 41");
// clang-format on

class assert_compare_tests_fixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        auto config          = qx::asserts_manager::get_instance().get_config();
        config.bLogAssertion = false;
        config.onAssertion   = [this](
                                 qx::string_view svCondition,
                                 const qx::category&,
                                 qx::assert_type,
                                 qx::string_view,
                                 qx::string_view,
                                 qx::string_view,
                                 i32)
        {
            m_sCondition = svCondition;
        };

        qx::asserts_manager::get_instance().set_config(std::move(config));
    }

    void TearDown() override
    {
        qx::asserts_manager::get_instance().set_config(qx::asserts_manager::config());
    }

    void expect_condition(qx::string_view svExpectedCondition)
    {
        EXPECT_EQ(m_sCondition, svExpectedCondition);
    }

private:
    qx::string m_sCondition;
};

TEST_F(assert_compare_tests_fixture, lvalue_rvalue)
{
    constexpr int nValue = 41;

    EXPECT_FALSE(QX_EXPECT(qx::assert_equal(nValue, 42)));
    expect_condition(QXT("Condition failed: nValue [41] == 42"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_not_equal(nValue, 41)));
    expect_condition(QXT("Condition failed: nValue [41] != 41"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less(nValue, 40)));
    expect_condition(QXT("Condition failed: nValue [41] < 40"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less_equal(nValue, 40)));
    expect_condition(QXT("Condition failed: nValue [41] <= 40"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater(nValue, 42)));
    expect_condition(QXT("Condition failed: nValue [41] > 42"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater_equal(nValue, 42)));
    expect_condition(QXT("Condition failed: nValue [41] >= 42"));
}

TEST_F(assert_compare_tests_fixture, lvalue_lvalue)
{
    constexpr int nValue = 41;
    constexpr int nOther = 42;
    constexpr int nSame  = 41;

    EXPECT_FALSE(QX_EXPECT(qx::assert_equal(nValue, nOther)));
    expect_condition(QXT("Condition failed: nValue [41] == nOther [42]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_not_equal(nValue, nSame)));
    expect_condition(QXT("Condition failed: nValue [41] != nSame [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less(nOther, nValue)));
    expect_condition(QXT("Condition failed: nOther [42] < nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less_equal(nOther, nValue)));
    expect_condition(QXT("Condition failed: nOther [42] <= nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater(nValue, nOther)));
    expect_condition(QXT("Condition failed: nValue [41] > nOther [42]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater_equal(nValue, nOther)));
    expect_condition(QXT("Condition failed: nValue [41] >= nOther [42]"));
}

TEST_F(assert_compare_tests_fixture, rvalue_lvalue)
{
    constexpr int nValue = 41;

    EXPECT_FALSE(QX_EXPECT(qx::assert_equal(42, nValue)));
    expect_condition(QXT("Condition failed: 42 == nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_not_equal(41, nValue)));
    expect_condition(QXT("Condition failed: 41 != nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less(42, nValue)));
    expect_condition(QXT("Condition failed: 42 < nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less_equal(42, nValue)));
    expect_condition(QXT("Condition failed: 42 <= nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater(40, nValue)));
    expect_condition(QXT("Condition failed: 40 > nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater_equal(40, nValue)));
    expect_condition(QXT("Condition failed: 40 >= nValue [41]"));
}

TEST_F(assert_compare_tests_fixture, rvalue_rvalue)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_equal(41, 42)));
    expect_condition(QXT("Condition failed: 41 == 42"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_not_equal(41, 41)));
    expect_condition(QXT("Condition failed: 41 != 41"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less(41, 40)));
    expect_condition(QXT("Condition failed: 41 < 40"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less_equal(41, 40)));
    expect_condition(QXT("Condition failed: 41 <= 40"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater(41, 42)));
    expect_condition(QXT("Condition failed: 41 > 42"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater_equal(41, 42)));
    expect_condition(QXT("Condition failed: 41 >= 42"));
}

TEST_F(assert_compare_tests_fixture, string_lvalue_rvalue)
{
    const qx::string sValue = QXT("b");

    EXPECT_FALSE(QX_EXPECT(qx::assert_equal(sValue, qx::string(QXT("c")))));
    expect_condition(QXT("Condition failed: sValue [b] == c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_not_equal(sValue, qx::string(QXT("b")))));
    expect_condition(QXT("Condition failed: sValue [b] != b"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less(sValue, qx::string(QXT("a")))));
    expect_condition(QXT("Condition failed: sValue [b] < a"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less_equal(sValue, qx::string(QXT("a")))));
    expect_condition(QXT("Condition failed: sValue [b] <= a"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater(sValue, qx::string(QXT("c")))));
    expect_condition(QXT("Condition failed: sValue [b] > c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater_equal(sValue, qx::string(QXT("c")))));
    expect_condition(QXT("Condition failed: sValue [b] >= c"));
}

TEST_F(assert_compare_tests_fixture, string_lvalue_lvalue)
{
    const qx::string sValue = QXT("b");
    const qx::string sOther = QXT("c");
    const qx::string sSame  = QXT("b");
    const qx::string sLess  = QXT("a");

    EXPECT_FALSE(QX_EXPECT(qx::assert_equal(sValue, sOther)));
    expect_condition(QXT("Condition failed: sValue [b] == sOther [c]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_not_equal(sValue, sSame)));
    expect_condition(QXT("Condition failed: sValue [b] != sSame [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less(sValue, sLess)));
    expect_condition(QXT("Condition failed: sValue [b] < sLess [a]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less_equal(sValue, sLess)));
    expect_condition(QXT("Condition failed: sValue [b] <= sLess [a]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater(sValue, sOther)));
    expect_condition(QXT("Condition failed: sValue [b] > sOther [c]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater_equal(sValue, sOther)));
    expect_condition(QXT("Condition failed: sValue [b] >= sOther [c]"));
}

TEST_F(assert_compare_tests_fixture, string_rvalue_lvalue)
{
    const qx::string sValue = QXT("b");

    EXPECT_FALSE(QX_EXPECT(qx::assert_equal(qx::string(QXT("c")), sValue)));
    expect_condition(QXT("Condition failed: c == sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_not_equal(qx::string(QXT("b")), sValue)));
    expect_condition(QXT("Condition failed: b != sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less(qx::string(QXT("c")), sValue)));
    expect_condition(QXT("Condition failed: c < sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less_equal(qx::string(QXT("c")), sValue)));
    expect_condition(QXT("Condition failed: c <= sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater(qx::string(QXT("a")), sValue)));
    expect_condition(QXT("Condition failed: a > sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater_equal(qx::string(QXT("a")), sValue)));
    expect_condition(QXT("Condition failed: a >= sValue [b]"));
}

TEST_F(assert_compare_tests_fixture, string_rvalue_rvalue)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_equal(qx::string(QXT("b")), qx::string(QXT("c")))));
    expect_condition(QXT("Condition failed: b == c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_not_equal(qx::string(QXT("b")), qx::string(QXT("b")))));
    expect_condition(QXT("Condition failed: b != b"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less(qx::string(QXT("b")), qx::string(QXT("a")))));
    expect_condition(QXT("Condition failed: b < a"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_less_equal(qx::string(QXT("b")), qx::string(QXT("a")))));
    expect_condition(QXT("Condition failed: b <= a"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater(qx::string(QXT("b")), qx::string(QXT("c")))));
    expect_condition(QXT("Condition failed: b > c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_greater_equal(qx::string(QXT("b")), qx::string(QXT("c")))));
    expect_condition(QXT("Condition failed: b >= c"));
}
