/**

    @file      assert.assert_compare.gtest.cpp
    @author    Khrapov
    @date      31.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

#define QX_DEBUG_BREAK() (void)0

#include <qx/asserts/asserts.h>

#include <array>
#include <sstream>
#include <string>
#include <utility>

class assert_compare_tests_fixture : public ::testing::Test
{
protected:
    void SetUp() override;

    void TearDown() override;

    void expect_condition(qx::string_view svExpectedCondition);

private:
    qx::string m_sCondition;
};

inline void assert_compare_tests_fixture::SetUp()
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

inline void assert_compare_tests_fixture::TearDown()
{
    qx::asserts_manager::get_instance().set_config(qx::asserts_manager::config());
}

inline void assert_compare_tests_fixture::expect_condition(qx::string_view svExpectedCondition)
{
    EXPECT_EQ(m_sCondition, svExpectedCondition);
}

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
    constexpr auto format(assert_compare_state eState, context_t& ctx) const -> decltype(ctx.out())
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
