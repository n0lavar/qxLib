/**

    @file      base.inl
    @author    Khrapov
    @date      13.08.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<arithmetic_c T, unit_enum_c unit_t>
convert(T, unit_t) -> convert<T, unit_t>;

template<arithmetic_c T, unit_enum_c unit_t>
convert(unit<T, unit_t>) -> convert<T, unit_t>;

namespace units::details
{

template<arithmetic_c T, unit_enum_c unit_t>
class base_converter
{
public:
    constexpr base_converter(unit<T, unit_t> from) noexcept;
    constexpr base_converter(T value, unit_t eFrom) noexcept;

protected:
    unit<T, unit_t> m_From;
};

template<unit_enum_c unit_t, class char_t>
struct unit_formatter : basic_formatter<char_t>
{
    template<class format_context_type_t>
    constexpr auto format(unit_t eData, format_context_type_t& ctx) const noexcept;
};

} // namespace units::details

} // namespace qx

template<qx::arithmetic_c T, qx::unit_enum_c unit_t, class char_t>
struct std::formatter<qx::unit<T, unit_t>, char_t>
{
    template<class format_parse_context_t>
    constexpr auto parse(format_parse_context_t& context) noexcept;

    template<class format_context_type_t>
    constexpr auto format(const qx::unit<T, unit_t>& unit, format_context_type_t& ctx) const noexcept;

private:
    std::formatter<T, char_t> valueFormatter;
};

template<qx::arithmetic_c T, qx::unit_enum_c unit_t>
constexpr qx::unit<T, unit_t>::operator T() const noexcept
{
    return value;
}

template<qx::arithmetic_c T, qx::unit_enum_c unit_t>
constexpr bool qx::unit<T, unit_t>::operator==(const unit<T, unit_t>& other) const noexcept
{
    if (type != other.type)
        return false;

    if constexpr (std::is_floating_point_v<T>)
        return float_compare(value, other.value);
    else
        return value == other.value;
}

template<qx::arithmetic_c T, qx::unit_enum_c unit_t>
constexpr qx::units::details::base_converter<T, unit_t>::base_converter(unit<T, unit_t> from) noexcept : m_From(from)
{
}

template<qx::arithmetic_c T, qx::unit_enum_c unit_t>
constexpr qx::units::details::base_converter<T, unit_t>::base_converter(T value, unit_t eFrom) noexcept
    : m_From({ value, eFrom })
{
}

template<qx::arithmetic_c T, qx::unit_enum_c unit_t>
constexpr qx::unit<T, unit_t> qx::normalize_unit(unit<T, unit_t> unit) noexcept
{
    return units::traits<unit_t>::template normalize<T>(unit);
}

template<qx::arithmetic_c T, qx::unit_enum_c unit_t>
constexpr qx::unit<T, unit_t> qx::normalize_unit(T value, unit_t eInitialType) noexcept
{
    return qx::normalize_unit(unit { value, eInitialType });
}

template<qx::arithmetic_c T, qx::unit_enum_c unit_t, class char_t>
std::optional<qx::unit<T, unit_t>> qx::unit_from_string(basic_string_view<char_t> svValue) noexcept
{
    auto remove_suffix = [](basic_string_view<char_t> svValue,
                            auto                      predicate) -> std::optional<basic_string_view<char_t>>
    {
        size_t nToErase = predicate(svValue);
        if (nToErase == 0)
            return std::nullopt;

        svValue.remove_suffix(nToErase);
        return svValue;
    };

    auto trim_right = [&remove_suffix](basic_string_view<char_t> svValue)
    {
        while (std::optional<basic_string_view<char_t>> svErased = remove_suffix(
                   svValue,
                   [](basic_string_view<char_t> svValue)
                   {
                       size_t nToErase = 0;
                       while (string_traits::traits<char_t>::is_space(svValue[nToErase]))
                       {
                           ++nToErase;
                       }

                       return nToErase;
                   }))
        {
            svValue = *svErased;
        }

        return svValue;
    };

    svValue = trim_right(svValue);

    const auto&           suffixes = units::traits<unit_t>::template get_suffixes<char_t>();
    auto                  itSuffix = suffixes.begin();
    std::optional<unit_t> optUnitType;
    std::optional<T>      optValue;
    while ((!optUnitType || !optValue) && itSuffix != suffixes.end())
    {
        auto optValueCandidate = remove_suffix(
            svValue,
            [&optUnitType, &itSuffix, &suffixes](basic_string_view<char_t> svValue) -> size_t
            {
                itSuffix = std::find_if(
                    itSuffix,
                    suffixes.end(),
                    [svValue](const std::pair<unit_t, basic_string_view<char_t>>& suffix)
                    {
                        return svValue.ends_with(suffix.second);
                    });

                if (itSuffix != suffixes.end())
                {
                    optUnitType = itSuffix->first;
                    return itSuffix->second.size();
                }
                else
                {
                    return 0;
                }
            });

        if (!optUnitType)
            continue;

        if (!optValueCandidate)
            continue;

        *optValueCandidate = trim_right(*optValueCandidate);

        // todo we can make it constexpr and get rid of a possible allocation
        basic_string<char_t> sValue = *optValueCandidate;
        optValue                    = sValue.template to<T>();
        ++itSuffix;
    }

    if (!optValue || !optUnitType)
        return std::nullopt;

    return unit(*optValue, *optUnitType);
}

template<qx::arithmetic_c T, qx::unit_enum_c unit_t, class char_t>
std::optional<qx::unit<T, unit_t>> qx::unit_from_string(const char_t* pszValue) noexcept
{
    return unit_from_string<T, unit_t, char_t>(basic_string_view<char_t>(pszValue));
}


template<qx::unit_enum_c unit_t, class char_t>
constexpr std::optional<qx::basic_string_view<char_t>> qx::get_unit_suffix(unit_t eUnit) noexcept
{
    const auto& suffixes = units::traits<unit_t>::template get_suffixes<char_t>();
    auto        itSuffix = std::ranges::find_if(
        suffixes,
        [eUnit](const std::pair<unit_t, basic_string_view<char_t>>& pair)
        {
            return pair.first == eUnit;
        });
    if (itSuffix != suffixes.end())
        return itSuffix->second;
    else
        return std::nullopt;
}

template<qx::arithmetic_c T, qx::unit_enum_c unit_t, class char_t>
template<class format_parse_context_t>
constexpr auto std::formatter<qx::unit<T, unit_t>, char_t>::parse(format_parse_context_t& context) noexcept
{
    return valueFormatter.parse(context);
}


template<qx::arithmetic_c T, qx::unit_enum_c unit_t, class char_t>
template<class format_context_type_t>
constexpr auto std::formatter<qx::unit<T, unit_t>, char_t>::format(
    const qx::unit<T, unit_t>& unit,
    format_context_type_t&     ctx) const noexcept
{
    auto outIt = valueFormatter.format(unit.value, ctx);
    return std::format_to(outIt, QX_STR_PREFIX(char_t, "{}"), unit.type);
}

template<qx::unit_enum_c unit_t, class char_t>
template<class format_context_type_t>
constexpr auto qx::units::details::unit_formatter<unit_t, char_t>::format(unit_t eUnit, format_context_type_t& ctx)
    const noexcept
{
    auto out = ctx.out();

    if (std::optional<basic_string_view<char_t>> optSuffix = get_unit_suffix<unit_t, char_t>(eUnit))
        out = std::format_to(out, QX_STR_PREFIX(char_t, "{}"), *optSuffix);

    return out;
}
