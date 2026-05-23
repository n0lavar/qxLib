/**

    @file      assert_compare.inl
    @author    Khrapov
    @date      19.05.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

namespace details
{

template<class operation_t>
struct assert_operation_symbol;

template<>
struct assert_operation_symbol<std::equal_to<>>
{
    static constexpr string_view symbol() noexcept
    {
        return QXT("==");
    }
};

template<>
struct assert_operation_symbol<std::not_equal_to<>>
{
    static constexpr string_view symbol() noexcept
    {
        return QXT("!=");
    }
};

template<>
struct assert_operation_symbol<std::less<>>
{
    static constexpr string_view symbol() noexcept
    {
        return QXT("<");
    }
};

template<>
struct assert_operation_symbol<std::less_equal<>>
{
    static constexpr string_view symbol() noexcept
    {
        return QXT("<=");
    }
};

template<>
struct assert_operation_symbol<std::greater<>>
{
    static constexpr string_view symbol() noexcept
    {
        return QXT(">");
    }
};

template<>
struct assert_operation_symbol<std::greater_equal<>>
{
    static constexpr string_view symbol() noexcept
    {
        return QXT(">=");
    }
};

constexpr string_view trim_assert_expression(string_view svExpression) noexcept
{
    while (!svExpression.empty()
           && (svExpression.front() == QXT(' ') || svExpression.front() == QXT('\t')
               || svExpression.front() == QXT('\r') || svExpression.front() == QXT('\n')))
    {
        svExpression.remove_prefix(1);
    }

    while (!svExpression.empty()
           && (svExpression.back() == QXT(' ') || svExpression.back() == QXT('\t') || svExpression.back() == QXT('\r')
               || svExpression.back() == QXT('\n')))
    {
        svExpression.remove_suffix(1);
    }

    return svExpression;
}

constexpr bool is_space(char_type ch) noexcept
{
    return ch == QXT(' ') || ch == QXT('\t') || ch == QXT('\r') || ch == QXT('\n');
}

constexpr bool is_char(char_type ch) noexcept
{
    return ch == QXT('_') || ch >= QXT('0') && ch <= QXT('9') || ch >= QXT('a') && ch <= QXT('z')
           || ch >= QXT('A') && ch <= QXT('Z');
}

constexpr bool is_identifier_first_char(char_type ch) noexcept
{
    return ch == QXT('_') || ch >= QXT('a') && ch <= QXT('z') || ch >= QXT('A') && ch <= QXT('Z');
}

constexpr bool is_literal(string_view svExpression) noexcept
{
    if (svExpression.empty())
        return false;

    if (svExpression == QXT("true") || svExpression == QXT("false") || svExpression == QXT("nullptr"))
        return true;

    const char_type chFirst = svExpression.front();
    if (chFirst == QXT('"') || chFirst == QXT('\''))
        return true;

    if (chFirst >= QXT('0') && chFirst <= QXT('9'))
        return true;

    return (chFirst == QXT('+') || chFirst == QXT('-')) && svExpression.size() > 1 && svExpression[1] >= QXT('0')
           && svExpression[1] <= QXT('9');
}

constexpr bool is_temporary_value(string_view svExpression) noexcept
{
    if (svExpression.starts_with(QXT("static_cast<")) || svExpression.starts_with(QXT("const_cast<"))
        || svExpression.starts_with(QXT("dynamic_cast<")) || svExpression.starts_with(QXT("reinterpret_cast<")))
    {
        return false;
    }

    bool   bQualified = false;
    size_t nPos       = 0;
    while (nPos < svExpression.size() && is_char(svExpression[nPos]))
        ++nPos;

    while (nPos + 1 < svExpression.size() && svExpression[nPos] == QXT(':') && svExpression[nPos + 1] == QXT(':'))
    {
        bQualified = true;
        nPos += 2;
        while (nPos < svExpression.size() && is_char(svExpression[nPos]))
            ++nPos;
    }

    if (nPos < svExpression.size() && svExpression[nPos] == QXT('<'))
    {
        i32 nAngleDepth = 1;
        ++nPos;

        while (nPos < svExpression.size() && nAngleDepth > 0)
        {
            if (svExpression[nPos] == QXT('<'))
                ++nAngleDepth;
            else if (svExpression[nPos] == QXT('>'))
                --nAngleDepth;

            ++nPos;
        }
    }

    return bQualified && nPos < svExpression.size() && svExpression[nPos] == QXT('(');
}

constexpr bool is_qualified_value(string_view svExpression) noexcept
{
    size_t nPos = 0;
    if (svExpression.size() > 1 && svExpression[0] == QXT(':') && svExpression[1] == QXT(':'))
        nPos = 2;

    bool bQualified = nPos != 0;
    while (nPos < svExpression.size())
    {
        if (!is_identifier_first_char(svExpression[nPos]))
            return false;

        while (nPos < svExpression.size() && is_char(svExpression[nPos]))
            ++nPos;

        if (nPos < svExpression.size() && svExpression[nPos] == QXT('<'))
        {
            i32 nAngleDepth = 1;
            ++nPos;

            while (nPos < svExpression.size() && nAngleDepth > 0)
            {
                if (svExpression[nPos] == QXT('<'))
                    ++nAngleDepth;
                else if (svExpression[nPos] == QXT('>'))
                    --nAngleDepth;

                ++nPos;
            }

            if (nAngleDepth != 0)
                return false;
        }

        if (nPos == svExpression.size())
            return bQualified;

        if (nPos + 1 >= svExpression.size() || svExpression[nPos] != QXT(':') || svExpression[nPos + 1] != QXT(':'))
        {
            return false;
        }

        bQualified = true;
        nPos += 2;
    }

    return false;
}

constexpr bool should_show_assert_expression_for_rvalue(string_view svExpression) noexcept
{
    return !is_literal(svExpression) && !is_temporary_value(svExpression) && !is_qualified_value(svExpression);
}

constexpr bool is_identifier_open_angle_char(char_type ch) noexcept
{
    return ch == QXT('_') || ch >= QXT('a') && ch <= QXT('z') || ch >= QXT('A') && ch <= QXT('Z');
}

constexpr bool is_open_angle(string_view svExpression, size_t nPos) noexcept
{
    if (nPos == 0)
        return false;

    const char_type chPrev = svExpression[nPos - 1];
    return is_identifier_open_angle_char(chPrev) || chPrev == QXT(':') || chPrev == QXT('>') || chPrev == QXT('&')
           || chPrev == QXT('*');
}

constexpr bool is_close_angle(string_view svExpression, size_t nPos) noexcept
{
    if (nPos + 1 >= svExpression.size())
        return true;

    const char_type chNext = svExpression[nPos + 1];
    return is_space(chNext) || chNext == QXT('(') || chNext == QXT(')') || chNext == QXT(',') || chNext == QXT(':')
           || chNext == QXT('&') || chNext == QXT('*') || chNext == QXT('>') || chNext == QXT('{')
           || chNext == QXT('.');
}

constexpr std::pair<string_view, string_view> split_assert_arguments(string_view svCondition) noexcept
{
    const size_t nArgsBegin = svCondition.find(QXT('('));
    if (nArgsBegin == string_view::npos)
        return {};

    i32    nParenDepth   = 0;
    i32    nBracketDepth = 0;
    i32    nBraceDepth   = 0;
    i32    nAngleDepth   = 0;
    size_t nCommaPos     = string_view::npos;
    size_t nArgsEnd      = string_view::npos;
    bool   bInString     = false;
    bool   bInChar       = false;
    bool   bEscaped      = false;

    for (size_t nPos = nArgsBegin + 1; nPos < svCondition.size(); ++nPos)
    {
        if (bInString || bInChar)
        {
            if (bEscaped)
            {
                bEscaped = false;
            }
            else if (svCondition[nPos] == QXT('\\'))
            {
                bEscaped = true;
            }
            else if (bInString && svCondition[nPos] == QXT('"'))
            {
                bInString = false;
            }
            else if (bInChar && svCondition[nPos] == QXT('\''))
            {
                bInChar = false;
            }

            continue;
        }

        switch (svCondition[nPos])
        {
        case QXT('"'):
            bInString = true;
            break;

        case QXT('\''):
            bInChar = true;
            break;

        case QXT('('):
            ++nParenDepth;
            break;

        case QXT(')'):
            if (nParenDepth == 0 && nBracketDepth == 0 && nBraceDepth == 0 && nAngleDepth == 0)
            {
                nArgsEnd = nPos;
                nPos     = svCondition.size();
            }
            else
            {
                --nParenDepth;
            }
            break;

        case QXT('['):
            ++nBracketDepth;
            break;

        case QXT(']'):
            --nBracketDepth;
            break;

        case QXT('{'):
            ++nBraceDepth;
            break;

        case QXT('}'):
            --nBraceDepth;
            break;

        case QXT('<'):
            if (is_open_angle(svCondition, nPos))
                ++nAngleDepth;
            break;

        case QXT('>'):
            if (nAngleDepth > 0 && is_close_angle(svCondition, nPos))
                --nAngleDepth;
            break;

        case QXT(','):
            if (nParenDepth == 0 && nBracketDepth == 0 && nBraceDepth == 0 && nAngleDepth == 0
                && nCommaPos == string_view::npos)
                nCommaPos = nPos;
            break;
        }
    }

    if (nCommaPos == string_view::npos || nArgsEnd == string_view::npos)
        return {};

    return { trim_assert_expression(svCondition.substr(nArgsBegin + 1, nCommaPos - nArgsBegin - 1)),
             trim_assert_expression(svCondition.substr(nCommaPos + 1, nArgsEnd - nCommaPos - 1)) };
}

template<class T>
inline string assert_value_to_string(const T& value) noexcept
{
    if constexpr (std::is_convertible_v<const T&, string_view>)
        return string(value);
    else
        return qx::convert_to_string(value);
}

inline void append_assert_expression(string& sResult, string_view svExpression) noexcept
{
    bool bPreviousWasSpace = false;

    for (const char_type ch : svExpression)
    {
        if (is_space(ch))
        {
            bPreviousWasSpace = !sResult.empty();
        }
        else
        {
            if (bPreviousWasSpace)
            {
                sResult.append(QXT(' '));
                bPreviousWasSpace = false;
            }

            sResult.append(ch);
        }
    }
}

template<bool bCanHaveName, class T>
inline string make_assert_operand_string(string_view svExpression, const T& value) noexcept
{
    if constexpr (bCanHaveName)
    {
        string sResult;
        append_assert_expression(sResult, svExpression);
        sResult.append(QXT(" ["));
        sResult.append(assert_value_to_string(value));
        sResult.append(QXT("]"));
        return sResult;
    }
    else
    {
        return assert_value_to_string(value);
    }
}

template<string_literal svCondition, class condition_t>
constexpr string_view get_assert_condition_string(const condition_t&) noexcept
{
    return svCondition.view();
}

template<
    string_literal svCondition,
    class left_t,
    class right_t,
    class operation_t,
    bool bLeftIsLvalue,
    bool bRightIsLvalue>
inline string get_assert_condition_string(
    const assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>& condition) noexcept
{
    constexpr auto split             = split_assert_arguments(svCondition.view());
    constexpr auto svLeftExpression  = split.first;
    constexpr auto svRightExpression = split.second;

    return qx::format(
        QXT("{} {} {}"),
        make_assert_operand_string < bLeftIsLvalue
            || should_show_assert_expression_for_rvalue(svLeftExpression) > (svLeftExpression, condition.left()),
        assert_operation_symbol<operation_t>::symbol(),
        make_assert_operand_string < bRightIsLvalue
            || should_show_assert_expression_for_rvalue(svRightExpression) > (svRightExpression, condition.right()));
}

template<class left_t, class right_t, class operation_t, bool bLeftIsLvalue, bool bRightIsLvalue>
constexpr assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>::
    assert_comparison(left_t&& left, right_t&& right) noexcept(
        std::is_nothrow_constructible_v<left_t, left_t&&> && std::is_nothrow_constructible_v<right_t, right_t&&>)
    : m_Left(std::forward<left_t>(left))
    , m_Right(std::forward<right_t>(right))
{
}

template<class left_t, class right_t, class operation_t, bool bLeftIsLvalue, bool bRightIsLvalue>
constexpr bool assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>::result() const
    noexcept(noexcept(operation_t {}(left(), right())))
{
    return operation_t {}(left(), right());
}

template<class left_t, class right_t, class operation_t, bool bLeftIsLvalue, bool bRightIsLvalue>
constexpr assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>::operator bool() const
    noexcept(noexcept(result()))
{
    return result();
}

template<class left_t, class right_t, class operation_t, bool bLeftIsLvalue, bool bRightIsLvalue>
constexpr const auto& assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>::left()
    const noexcept
{
    return m_Left;
}

template<class left_t, class right_t, class operation_t, bool bLeftIsLvalue, bool bRightIsLvalue>
constexpr const auto& assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>::right()
    const noexcept
{
    return m_Right;
}

} // namespace details

template<class left_t, class right_t, class operation_t, bool bLeftIsLvalue, bool bRightIsLvalue>
constexpr bool predicates::
    validator<details::assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>>::is_valid(
        const details::assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>&
            value) noexcept(noexcept(value.result()))
{
    return value.result();
}

template<class left_t, class right_t>
constexpr auto assert_eq(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
             left_t,
             right_t,
             std::equal_to<>,
             std::is_lvalue_reference_v<left_t>,
             std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return details::assert_comparison<
        left_t,
        right_t,
        std::equal_to<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_ne(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
             left_t,
             right_t,
             std::not_equal_to<>,
             std::is_lvalue_reference_v<left_t>,
             std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return details::assert_comparison<
        left_t,
        right_t,
        std::not_equal_to<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_lt(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
             left_t,
             right_t,
             std::less<>,
             std::is_lvalue_reference_v<left_t>,
             std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return details::assert_comparison<
        left_t,
        right_t,
        std::less<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_le(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
             left_t,
             right_t,
             std::less_equal<>,
             std::is_lvalue_reference_v<left_t>,
             std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return details::assert_comparison<
        left_t,
        right_t,
        std::less_equal<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_gt(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
             left_t,
             right_t,
             std::greater<>,
             std::is_lvalue_reference_v<left_t>,
             std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return details::assert_comparison<
        left_t,
        right_t,
        std::greater<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_ge(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
             left_t,
             right_t,
             std::greater_equal<>,
             std::is_lvalue_reference_v<left_t>,
             std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return details::assert_comparison<
        left_t,
        right_t,
        std::greater_equal<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(std::forward<left_t>(left), std::forward<right_t>(right));
}

} // namespace qx
