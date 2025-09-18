/**

    @file      base.inl
    @author    Khrapov
    @date      13.08.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx::units::details
{

template<arithmetic_c T, enumeration_c unit_t>
class base_converter
{
public:
    constexpr base_converter(unit<T, unit_t> from) noexcept;
    constexpr base_converter(T value, unit_t eFrom) noexcept;

protected:
    unit<T, unit_t> m_From;
};

template<arithmetic_c T, enumeration_c unit_t>
struct unit_normalizer;

template<enumeration_c unit_t, class char_t>
struct unit_suffixes;

} // namespace qx::units::details

template<qx::arithmetic_c T, qx::enumeration_c unit_t>
constexpr qx::unit<T, unit_t>::operator T() const noexcept
{
    return value;
}

template<qx::arithmetic_c T, qx::enumeration_c unit_t>
constexpr qx::units::details::base_converter<T, unit_t>::base_converter(unit<T, unit_t> from) noexcept : m_From(from)
{
}

template<qx::arithmetic_c T, qx::enumeration_c unit_t>
constexpr qx::units::details::base_converter<T, unit_t>::base_converter(T value, unit_t eFrom) noexcept
    : m_From({ value, eFrom })
{
}

template<qx::arithmetic_c T, qx::enumeration_c unit_t>
qx::unit<T, unit_t> qx::normalize_unit(unit<T, unit_t> unit) noexcept
{
    return units::details::unit_normalizer<T, unit_t>::normalize(unit);
}

template<qx::arithmetic_c T, qx::enumeration_c unit_t>
qx::unit<T, unit_t> qx::normalize_unit(T value, unit_t eInitialType) noexcept
{
    return qx::normalize_unit(unit { value, eInitialType });
}

template<qx::arithmetic_c T, qx::enumeration_c unit_t, class char_t>
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

    std::optional<unit_t> optUnitType;
    auto                  optNewValue = remove_suffix(
        svValue,
        [&optUnitType](basic_string_view<char_t> svValue) -> size_t
        {
            const auto& suffixes = units::details::unit_suffixes<unit_t, char_t>::get();
            const auto  it       = std::ranges::find_if(
                suffixes,
                [svValue](const std::pair<unit_t, basic_string_view<char_t>>& suffix)
                {
                    return svValue.ends_with(suffix.second);
                });

            if (it != suffixes.end())
            {
                optUnitType = it->first;
                return it->second.size();
            }
            else
            {
                return 0;
            }
        });
    if (!optUnitType)
        return std::nullopt;
    if (!optNewValue)
        return std::nullopt;
    svValue = *optNewValue;

    svValue = trim_right(svValue);

    // todo we can make it constexpr and get rid of a possible allocation
    basic_string<char_t> sValue   = svValue;
    std::optional<T>     optValue = sValue.template to<T>();
    if (!optValue)
        return std::nullopt;

    return unit(*optValue, *optUnitType);
}


template<qx::arithmetic_c T, qx::enumeration_c unit_t, class char_t>
template<class format_parse_context_t>
constexpr auto std::formatter<qx::unit<T, unit_t>, char_t>::parse(format_parse_context_t& context) noexcept
{
    return valueFormatter.parse(context);
}


template<qx::arithmetic_c T, qx::enumeration_c unit_t, class char_t>
template<class format_context_type_t>
constexpr auto std::formatter<qx::unit<T, unit_t>, char_t>::format(
    const qx::unit<T, unit_t>& unit,
    format_context_type_t&     ctx) const noexcept
{
    auto outIt = valueFormatter.format(unit.value, ctx);
    return std::format_to(outIt, QX_STR_PREFIX(char_t, "{}"), unit.type);
}
