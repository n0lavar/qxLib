/**

    @file      expected_assert.h
    @author    Khrapov
    @date      31.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/asserts/asserts.h>
#include <qx/macros/suppress_warnings.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <gtest/gtest.h>
QX_POP_SUPPRESS_WARNINGS();

#include <atomic>
#include <optional>
#include <regex>

namespace qx
{

class expected_assert;

/**

    @class   expected_assert_builder
    @brief   Selects assertion properties and the number of expected occurrences.
    @details Only specified properties are matched. Strings match exactly unless regex search is enabled; a selected category
             must outlive the expectation. The default expected count is one.
    @author  Khrapov
    @date    31.10.2026

**/
class expected_assert_builder
{
    friend class expected_assert;

    class string_matcher
    {
    public:
        string_matcher(string_view svValue, bool bRegex);
        bool        matches(string_view svValue) const;
        string_view get_pattern() const;
        bool        is_regex() const;

    private:
        string                                     m_Value;
        std::optional<std::basic_regex<char_type>> m_Regex;
    };

public:
    /**
        @brief  Match the failed condition text.
        @param  svCondition - expected text or regex pattern
        @param  bRegex      - search using a regex instead of comparing the complete text
    **/
    [[nodiscard]] expected_assert_builder& condition(string_view svCondition, bool bRegex = false);

    /**
        @brief  Require the specified assertion category.
        @param  category - expected value
    **/
    [[nodiscard]] expected_assert_builder& category(const qx::category& category);

    /**
        @brief  Require the specified assertion type.
        @param  eType - expected value
    **/
    [[nodiscard]] expected_assert_builder& type(assert_type eType);

    /**
        @brief  Match the formatted user message.
        @param  svPattern - expected text or regex pattern
        @param  bRegex    - search using a regex instead of comparing the complete text
    **/
    [[nodiscard]] expected_assert_builder& message(string_view svPattern, bool bRegex = false);

    /**
        @brief  Match the function name.
        @param  svFunction - expected text or regex pattern
        @param  bRegex     - search using a regex instead of comparing the complete text
    **/
    [[nodiscard]] expected_assert_builder& function(string_view svFunction, bool bRegex = false);

    /**
        @brief  Match the source file name.
        @param  svFile - expected text or regex pattern
        @param  bRegex - search using a regex instead of comparing the complete text
    **/
    [[nodiscard]] expected_assert_builder& file(string_view svFile, bool bRegex = false);

    /**
        @brief  Require the exact source line number.
        @param  nLine - expected value
    **/
    [[nodiscard]] expected_assert_builder& line(i32 nLine);

    /**
        @brief  Require exactly this many matching assertions.
        @param  nCount - expected value
    **/
    [[nodiscard]] expected_assert_builder& count(size_t nCount);

    /**
        @brief  Start observing assertions using the selected criteria.
        @return - scoped expectation that reports a count mismatch on destruction
    **/
    [[nodiscard]] expected_assert build() const;

private:
    std::optional<string_matcher> m_Condition;
    const qx::category*           m_pCategory = nullptr;
    std::optional<assert_type>    m_Type;
    std::optional<string_matcher> m_Message;
    std::optional<string_matcher> m_Function;
    std::optional<string_matcher> m_File;
    std::optional<i32>            m_Line;
    size_t                        m_nCount = 1;
};

/**

    @class   expected_assert
    @brief   Counts assertions matching the criteria selected by expected_assert_builder.
    @details Matched assertions are consumed in registration order; other assertions follow normal handling.
             A matched QX_EXPECT or QX_ENSURE suppresses logging, the assertion callback and debug break;
             QX_EXPECT control-flow variants still perform their return, break or continue. QX_ENSURE and
             QX_ASSERT are disabled when QX_WITH_DEBUG_ASSERTS is false. A matched QX_ASSERT or QX_VERIFY
             also suppresses reporting and debug break, but still calls the fatal exit handler. With the default
             handler the process terminates without unwinding, so this object's destructor cannot report the count.
             Otherwise the destructor reports a Google Test failure if the observed count differs from the expected count.
    @author  Khrapov
    @date    31.10.2026

**/
class expected_assert
{
    friend class expected_assert_builder;

    QX_NONCOPYMOVABLE(expected_assert);

public:
    ~expected_assert();

private:
    explicit expected_assert(const expected_assert_builder& builder);

private:
    expected_assert_builder m_Builder;
    std::atomic_size_t      m_nActual = 0;
};

} // namespace qx

#include <qx/asserts/expected_assert.inl>
