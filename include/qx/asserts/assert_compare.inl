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
    while (!svExpression.empty() && (svExpression.front() == QXT(' ') || svExpression.front() == QXT('\t')))
        svExpression.remove_prefix(1);

    while (!svExpression.empty() && (svExpression.back() == QXT(' ') || svExpression.back() == QXT('\t')))
        svExpression.remove_suffix(1);

    return svExpression;
}

constexpr std::pair<string_view, string_view> split_assert_arguments(string_view svCondition) noexcept
{
    const size_t nArgsBegin = svCondition.find(QXT('('));
    if (nArgsBegin == string_view::npos)
        return {};

    i32    nDepth    = 0;
    size_t nCommaPos = string_view::npos;
    size_t nArgsEnd  = string_view::npos;

    for (size_t nPos = nArgsBegin + 1; nPos < svCondition.size(); ++nPos)
    {
        switch (svCondition[nPos])
        {
        case QXT('('):
        case QXT('['):
        case QXT('{'):
            ++nDepth;
            break;

        case QXT(')'):
            if (nDepth == 0)
            {
                nArgsEnd = nPos;
                nPos     = svCondition.size();
            }
            else
                --nDepth;
            break;

        case QXT(']'):
        case QXT('}'):
            --nDepth;
            break;

        case QXT(','):
            if (nDepth == 0 && nCommaPos == string_view::npos)
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

template<bool bCanHaveName, class T>
inline string make_assert_operand_string(string_view svExpression, const T& value) noexcept
{
    if constexpr (bCanHaveName)
    {
        string sResult;
        sResult.append(svExpression);
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

template<class condition_t>
inline string_view get_assert_condition_string(string_view svCondition, const condition_t&) noexcept
{
    return svCondition;
}

template<class left_t, class right_t, class operation_t>
inline string get_assert_condition_string(
    string_view                                            svCondition,
    const assert_comparison<left_t, right_t, operation_t>& condition) noexcept
{
    return condition.make_assert_condition_string(svCondition);
}

} // namespace details

template<class left_t, class right_t, class operation_t>
constexpr assert_comparison<left_t, right_t, operation_t>::assert_comparison(left_t&& left, right_t&& right) noexcept(
    std::is_nothrow_constructible_v<left_t, left_t&&> && std::is_nothrow_constructible_v<right_t, right_t&&>)
    : m_Left(std::forward<left_t>(left))
    , m_Right(std::forward<right_t>(right))
{
}

template<class left_t, class right_t, class operation_t>
constexpr bool assert_comparison<left_t, right_t, operation_t>::result() const
    noexcept(noexcept(operation_t {}(left(), right())))
{
    return operation_t {}(left(), right());
}

template<class left_t, class right_t, class operation_t>
constexpr assert_comparison<left_t, right_t, operation_t>::operator bool() const noexcept(noexcept(result()))
{
    return result();
}

template<class left_t, class right_t, class operation_t>
constexpr const auto& assert_comparison<left_t, right_t, operation_t>::left() const noexcept
{
    return m_Left;
}

template<class left_t, class right_t, class operation_t>
constexpr const auto& assert_comparison<left_t, right_t, operation_t>::right() const noexcept
{
    return m_Right;
}

template<class left_t, class right_t, class operation_t>
inline string assert_comparison<left_t, right_t, operation_t>::make_assert_condition_string(
    string_view svCondition) const noexcept
{
    const auto [svLeftExpression, svRightExpression] = details::split_assert_arguments(svCondition);

    return string::static_format(
        QXT("Condition failed: {} {} {}"),
        details::make_assert_operand_string<std::is_lvalue_reference_v<left_t>>(
            svLeftExpression,
            left()),
        details::assert_operation_symbol<operation_t>::symbol(),
        details::make_assert_operand_string<std::is_lvalue_reference_v<right_t>>(
            svRightExpression,
            right()));
}

template<class left_t, class right_t>
constexpr auto assert_equal(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::equal_to<>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return assert_comparison<left_t, right_t, std::equal_to<>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_not_equal(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::not_equal_to<>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return assert_comparison<left_t, right_t, std::not_equal_to<>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_less(left_t&& left, right_t&& right) noexcept(
    noexcept(assert_comparison<left_t, right_t, std::less<>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return assert_comparison<left_t, right_t, std::less<>>(std::forward<left_t>(left), std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_less_equal(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::less_equal<>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return assert_comparison<left_t, right_t, std::less_equal<>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_greater(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::greater<>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return assert_comparison<left_t, right_t, std::greater<>>(std::forward<left_t>(left), std::forward<right_t>(right));
}

template<class left_t, class right_t>
constexpr auto assert_greater_equal(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::greater_equal<>>(std::forward<left_t>(left), std::forward<right_t>(right))))
{
    return assert_comparison<left_t, right_t, std::greater_equal<>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right));
}

template<class left_t, class right_t, class operation_t>
constexpr bool predicates::validator<assert_comparison<left_t, right_t, operation_t>>::is_valid(
    const assert_comparison<left_t, right_t, operation_t>& value) noexcept(noexcept(value.result()))
{
    return value.result();
}

} // namespace qx
