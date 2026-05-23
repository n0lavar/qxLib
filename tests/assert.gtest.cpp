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

#include <array>
#include <sstream>
#include <string>
#include <utility>

//V_EXCLUDE_PATH *.gtest.cpp

QX_SET_FILE_CATEGORY(CatDefault);

QX_DEFINE_CATEGORY(CatAssertsTests, qx::color::white());

static_assert(qx::details::trim_assert_expression(QXT(" nValue\t")) == QXT("nValue"));
static_assert(qx::details::split_assert_arguments(QXT("qx::assert_eq(nValue, 42)")).first == QXT("nValue"));
static_assert(qx::details::split_assert_arguments(QXT("qx::assert_eq(nValue, 42)")).second == QXT("42"));
static_assert(qx::details::split_assert_arguments(QXT("qx::assert_eq(foo(a, b), 42)")).first == QXT("foo(a, b)"));
static_assert(
    qx::details::split_assert_arguments(QXT("qx::assert_eq(value<std::pair<int, int>>(), 42)")).first
    == QXT("value<std::pair<int, int>>()"));
static_assert(
    qx::details::split_assert_arguments(QXT("qx::assert_eq(values[index(a, b)], 42)")).first
    == QXT("values[index(a, b)]"));
static_assert(qx::details::split_assert_arguments(QXT("qx::assert_eq(\"a, b\", 42)")).first == QXT("\"a, b\""));
static_assert(qx::details::split_assert_arguments(QXT("qx::assert_eq(',', 42)")).first == QXT("','"));
static_assert(qx::details::split_assert_arguments(QXT("qx::assert_eq((a, b), 42)")).first == QXT("(a, b)"));

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

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(nValue, 42)));
    expect_condition(QXT("nValue [41] == 42"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ne(nValue, 41)));
    expect_condition(QXT("nValue [41] != 41"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(nValue, 40)));
    expect_condition(QXT("nValue [41] < 40"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_le(nValue, 40)));
    expect_condition(QXT("nValue [41] <= 40"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_gt(nValue, 42)));
    expect_condition(QXT("nValue [41] > 42"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(nValue, 42)));
    expect_condition(QXT("nValue [41] >= 42"));
}

TEST_F(assert_compare_tests_fixture, lvalue_lvalue)
{
    constexpr int nValue = 41;
    constexpr int nOther = 42;
    constexpr int nSame  = 41;

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(nValue, nOther)));
    expect_condition(QXT("nValue [41] == nOther [42]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ne(nValue, nSame)));
    expect_condition(QXT("nValue [41] != nSame [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(nOther, nValue)));
    expect_condition(QXT("nOther [42] < nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_le(nOther, nValue)));
    expect_condition(QXT("nOther [42] <= nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_gt(nValue, nOther)));
    expect_condition(QXT("nValue [41] > nOther [42]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(nValue, nOther)));
    expect_condition(QXT("nValue [41] >= nOther [42]"));
}

TEST_F(assert_compare_tests_fixture, rvalue_lvalue)
{
    constexpr int nValue = 41;

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(42, nValue)));
    expect_condition(QXT("42 == nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ne(41, nValue)));
    expect_condition(QXT("41 != nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(42, nValue)));
    expect_condition(QXT("42 < nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_le(42, nValue)));
    expect_condition(QXT("42 <= nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_gt(40, nValue)));
    expect_condition(QXT("40 > nValue [41]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(40, nValue)));
    expect_condition(QXT("40 >= nValue [41]"));
}

TEST_F(assert_compare_tests_fixture, rvalue_rvalue)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(41, 42)));
    expect_condition(QXT("41 == 42"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ne(41, 41)));
    expect_condition(QXT("41 != 41"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(41, 40)));
    expect_condition(QXT("41 < 40"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_le(41, 40)));
    expect_condition(QXT("41 <= 40"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_gt(41, 42)));
    expect_condition(QXT("41 > 42"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(41, 42)));
    expect_condition(QXT("41 >= 42"));
}

constexpr int assert_compare_add(int nLeft, int nRight) noexcept
{
    return nLeft + nRight;
}

template<class T>
constexpr int assert_compare_value() noexcept
{
    return 42;
}

constexpr size_t assert_compare_index(size_t nLeft, size_t nRight) noexcept
{
    return nLeft + nRight;
}

template<class char_t>
constexpr int assert_compare_length(const char_t* pszValue) noexcept
{
    int nLength = 0;
    while (pszValue[nLength])
        ++nLength;
    return nLength;
}

template<class char_t>
constexpr int assert_compare_char(char_t chValue) noexcept
{
    return chValue == ',' ? 42 : 0;
}

TEST_F(assert_compare_tests_fixture, parser_function_call)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(assert_compare_add(20, 22), 43)));
    expect_condition(QXT("assert_compare_add(20, 22) [42] == 43"));
}

TEST_F(assert_compare_tests_fixture, parser_template_id)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(assert_compare_value<std::pair<int, int>>(), 43)));
    expect_condition(QXT("assert_compare_value<std::pair<int, int>>() [42] == 43"));
}

TEST_F(assert_compare_tests_fixture, parser_subscript)
{
    constexpr std::array<int, 2> values = { 0, 42 };

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(values[assert_compare_index(0, 1)], 43)));
    expect_condition(QXT("values[assert_compare_index(0, 1)] [42] == 43"));
}

TEST_F(assert_compare_tests_fixture, parser_string_literal)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(assert_compare_length("a, b"), 5)));
    expect_condition(QXT("assert_compare_length(\"a, b\") [4] == 5"));
}

TEST_F(assert_compare_tests_fixture, parser_char_literal)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(assert_compare_char(','), 43)));
    expect_condition(QXT("assert_compare_char(',') [42] == 43"));
}

TEST_F(assert_compare_tests_fixture, parser_comma_operator)
{
    constexpr int nValue = 42;

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq((assert_compare_add(0, 0), nValue), 43)));
    expect_condition(QXT("(assert_compare_add(0, 0), nValue) [42] == 43"));
}

TEST_F(assert_compare_tests_fixture, parser_brace_init)
{
    EXPECT_FALSE(
        QX_EXPECT(qx::assert_eq(std::pair<int, int> { 20, 22 }.first + std::pair<int, int> { 20, 22 }.second, 43)));
    expect_condition(QXT("std::pair<int, int> { 20, 22 }.first + std::pair<int, int> { 20, 22 }.second [42] == 43"));
}
TEST_F(assert_compare_tests_fixture, streamoff_expression)
{
    std::stringstream inputFile;
    inputFile.str("0123456789012345678901234567890123456789");
    inputFile.seekg(20);

    constexpr std::streamoff nRowSize  = 22;
    constexpr std::streamoff nFileSize = 43;

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(
        static_cast<std::streamoff>(inputFile.tellg()) + nRowSize,
        static_cast<std::streamoff>(nFileSize))));
    expect_condition(
        QXT("static_cast<std::streamoff>(inputFile.tellg()) + nRowSize [42] == "
            "static_cast<std::streamoff>(nFileSize) [43]"));
}

TEST_F(assert_compare_tests_fixture, string_lvalue_rvalue)
{
    const qx::string sValue = QXT("b");

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(sValue, qx::string(QXT("c")))));
    expect_condition(QXT("sValue [b] == c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ne(sValue, qx::string(QXT("b")))));
    expect_condition(QXT("sValue [b] != b"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(sValue, qx::string(QXT("a")))));
    expect_condition(QXT("sValue [b] < a"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_le(sValue, qx::string(QXT("a")))));
    expect_condition(QXT("sValue [b] <= a"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_gt(sValue, qx::string(QXT("c")))));
    expect_condition(QXT("sValue [b] > c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(sValue, qx::string(QXT("c")))));
    expect_condition(QXT("sValue [b] >= c"));
}

TEST_F(assert_compare_tests_fixture, string_lvalue_lvalue)
{
    const qx::string sValue = QXT("b");
    const qx::string sOther = QXT("c");
    const qx::string sSame  = QXT("b");
    const qx::string sLess  = QXT("a");

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(sValue, sOther)));
    expect_condition(QXT("sValue [b] == sOther [c]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ne(sValue, sSame)));
    expect_condition(QXT("sValue [b] != sSame [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(sValue, sLess)));
    expect_condition(QXT("sValue [b] < sLess [a]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_le(sValue, sLess)));
    expect_condition(QXT("sValue [b] <= sLess [a]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_gt(sValue, sOther)));
    expect_condition(QXT("sValue [b] > sOther [c]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(sValue, sOther)));
    expect_condition(QXT("sValue [b] >= sOther [c]"));
}

TEST_F(assert_compare_tests_fixture, string_rvalue_lvalue)
{
    const qx::string sValue = QXT("b");

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(qx::string(QXT("c")), sValue)));
    expect_condition(QXT("c == sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ne(qx::string(QXT("b")), sValue)));
    expect_condition(QXT("b != sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(qx::string(QXT("c")), sValue)));
    expect_condition(QXT("c < sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_le(qx::string(QXT("c")), sValue)));
    expect_condition(QXT("c <= sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_gt(qx::string(QXT("a")), sValue)));
    expect_condition(QXT("a > sValue [b]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(qx::string(QXT("a")), sValue)));
    expect_condition(QXT("a >= sValue [b]"));
}

TEST_F(assert_compare_tests_fixture, string_rvalue_rvalue)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(qx::string(QXT("b")), qx::string(QXT("c")))));
    expect_condition(QXT("b == c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ne(qx::string(QXT("b")), qx::string(QXT("b")))));
    expect_condition(QXT("b != b"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(qx::string(QXT("b")), qx::string(QXT("a")))));
    expect_condition(QXT("b < a"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_le(qx::string(QXT("b")), qx::string(QXT("a")))));
    expect_condition(QXT("b <= a"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_gt(qx::string(QXT("b")), qx::string(QXT("c")))));
    expect_condition(QXT("b > c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(qx::string(QXT("b")), qx::string(QXT("c")))));
    expect_condition(QXT("b >= c"));
}

TEST_F(assert_compare_tests_fixture, std_string)
{
    const std::basic_string<qx::char_type> sValue = QXT("b");
    const std::basic_string<qx::char_type> sOther = QXT("c");

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(sValue, sOther)));
    expect_condition(QXT("sValue [b] == sOther [c]"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_eq(sValue, std::basic_string<qx::char_type>(QXT("c")))));
    expect_condition(QXT("sValue [b] == c"));

    EXPECT_FALSE(QX_EXPECT(qx::assert_lt(sOther, sValue)));
    expect_condition(QXT("sOther [c] < sValue [b]"));
}

enum class assert_compare_state
{
    bounds_initialized,
    input_geometry_loaded
};

template<class char_t>
struct QX_FMT_NS::formatter<assert_compare_state, char_t> : qx::basic_formatter<char_t>
{
    template<class context_t>
    constexpr auto format(assert_compare_state eState, context_t& ctx) const
    {
        switch (eState)
        {
        case assert_compare_state::bounds_initialized:
            return QX_FMT_NS::format_to(
                ctx.out(),
                QX_STR_PREFIX(char_t, "{}"),
                QX_STR_PREFIX(char_t, "assert_compare_state::bounds_initialized"));

        case assert_compare_state::input_geometry_loaded:
            return QX_FMT_NS::format_to(
                ctx.out(),
                QX_STR_PREFIX(char_t, "{}"),
                QX_STR_PREFIX(char_t, "assert_compare_state::input_geometry_loaded"));
        }

        return ctx.out();
    }
};

constexpr assert_compare_state assert_compare_state_value() noexcept
{
    return assert_compare_state::bounds_initialized;
}

TEST_F(assert_compare_tests_fixture, enum_lvalue_rvalue)
{
    constexpr assert_compare_state eState = assert_compare_state::bounds_initialized;

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(eState, assert_compare_state::input_geometry_loaded)));
    expect_condition(
        QXT("eState [assert_compare_state::bounds_initialized] >= assert_compare_state::input_geometry_loaded"));
}

TEST_F(assert_compare_tests_fixture, enum_lvalue_lvalue)
{
    constexpr assert_compare_state eState = assert_compare_state::bounds_initialized;
    constexpr assert_compare_state eOther = assert_compare_state::input_geometry_loaded;

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(eState, eOther)));
    expect_condition(QXT(
        "eState [assert_compare_state::bounds_initialized] >= eOther [assert_compare_state::input_geometry_loaded]"));
}

TEST_F(assert_compare_tests_fixture, enum_rvalue_lvalue)
{
    constexpr assert_compare_state eState = assert_compare_state::input_geometry_loaded;

    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(assert_compare_state::bounds_initialized, eState)));
    expect_condition(
        QXT("assert_compare_state::bounds_initialized >= eState [assert_compare_state::input_geometry_loaded]"));
}

TEST_F(assert_compare_tests_fixture, enum_rvalue_rvalue)
{
    EXPECT_FALSE(QX_EXPECT(
        qx::assert_ge(assert_compare_state::bounds_initialized, assert_compare_state::input_geometry_loaded)));
    expect_condition(QXT("assert_compare_state::bounds_initialized >= assert_compare_state::input_geometry_loaded"));
}

TEST_F(assert_compare_tests_fixture, enum_rvalue_expression)
{
    EXPECT_FALSE(QX_EXPECT(qx::assert_ge(assert_compare_state_value(), assert_compare_state::input_geometry_loaded)));
    expect_condition(
        QXT("assert_compare_state_value() [assert_compare_state::bounds_initialized] >= "
            "assert_compare_state::input_geometry_loaded"));
}
