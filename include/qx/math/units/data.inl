/**

    @file      data.inl
    @author    Khrapov
    @date      13.08.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

template<qx::arithmetic_c T>
class qx::convert<T, qx::units::data> : public units::details::base_converter<T, units::data>
{
public:
    using units::details::base_converter<T, units::data>::base_converter;

    constexpr unit<T, units::data> to(units::data eTo) const noexcept;
};

template<class char_t>
struct std::formatter<qx::units::data, char_t> : qx::basic_formatter<char_t>
{
    template<class format_context_type_t>
    constexpr auto format(qx::units::data eData, format_context_type_t& ctx) const noexcept;
};

namespace qx::units::details
{

constexpr bool is_binary(data eDataSize) noexcept
{
    return eDataSize < data::_last_binary;
}

template<class T>
constexpr i64 to_bits(data eFrom, T value) noexcept
{
    if (is_binary(eFrom))
    {
        return static_cast<i64>(static_cast<double>(value) * pow(2, static_cast<int>(eFrom)));
    }
    else
    {
        return static_cast<i64>(
            8.f * static_cast<double>(value) * pow(10, static_cast<int>(eFrom) - static_cast<int>(data::_last_binary)));
    }
}

template<class T>
constexpr T from_bits(i64 bits, data eTo) noexcept
{
    if (is_binary(eTo))
    {
        return static_cast<T>(static_cast<double>(bits) / pow(2, static_cast<int>(eTo)));
    }
    else
    {
        return static_cast<T>(
            static_cast<double>(bits) / pow(10, static_cast<int>(eTo) - static_cast<int>(data::_last_binary)) / 8.f);
    }
}

template<arithmetic_c T>
struct unit_normalizer<T, data>
{
    static constexpr unit<T, data> normalize(unit<T, data> unit) noexcept;
};

template<class char_t>
struct unit_suffixes<data, char_t>
{
    static constexpr auto get() noexcept
    {
        using pair_type = std::pair<data, basic_string_view<char_t>>;
        return std::array { pair_type { data::bits, QX_STR_PREFIX(char_t, "b") },
                            pair_type { data::nibbles, QX_STR_PREFIX(char_t, "nib") },
                            pair_type { data::bytes, QX_STR_PREFIX(char_t, "B") },
                            pair_type { data::kibibytes, QX_STR_PREFIX(char_t, "KiB") },
                            pair_type { data::mebibytes, QX_STR_PREFIX(char_t, "MiB") },
                            pair_type { data::gibibytes, QX_STR_PREFIX(char_t, "GiB") },
                            pair_type { data::tebibytes, QX_STR_PREFIX(char_t, "TiB") },
                            pair_type { data::pebibytes, QX_STR_PREFIX(char_t, "PiB") },
                            pair_type { data::kilobytes, QX_STR_PREFIX(char_t, "kB") },
                            pair_type { data::megabytes, QX_STR_PREFIX(char_t, "MB") },
                            pair_type { data::gigabytes, QX_STR_PREFIX(char_t, "GB") },
                            pair_type { data::terabytes, QX_STR_PREFIX(char_t, "TB") },
                            pair_type { data::petabytes, QX_STR_PREFIX(char_t, "PB") } };
    }
};

} // namespace qx::units::details

template<qx::arithmetic_c T>
constexpr qx::unit<T, qx::units::data> qx::convert<T, qx::units::data>::to(units::data eTo) const noexcept
{
    if (this->m_From.type == eTo)
        return { this->m_From.value, eTo };

    const i64 bits = units::details::to_bits(this->m_From.type, this->m_From.value);
    return { units::details::from_bits<T>(bits, eTo), eTo };
}

template<class char_t>
template<class format_context_type_t>
constexpr auto std::formatter<qx::units::data, char_t>::format(qx::units::data eData, format_context_type_t& ctx)
    const noexcept
{
    auto out = ctx.out();

    const auto& suffixes = qx::units::details::unit_suffixes<qx::units::data, char_t>::get();

    auto itName = std::ranges::find_if(
        suffixes,
        [eData](const std::pair<qx::units::data, qx::basic_string_view<char_t>>& pair)
        {
            return pair.first == eData;
        });
    if (itName != suffixes.end())
        out = std::format_to(out, QX_STR_PREFIX(char_t, "{}"), itName->second);

    return out;
}

template<qx::arithmetic_c T>
constexpr qx::unit<T, qx::units::data> qx::units::details::unit_normalizer<T, qx::units::data>::normalize(
    unit<T, data> unit) noexcept
{
    const i64 nBits    = details::to_bits(unit.type, unit.value);
    const f64 fAbsBits = static_cast<f64>(abs(nBits));

    data eTo = data::pebibytes;
    if (fAbsBits <= pow(2, 3))
    {
        eTo = data::bits;
    }
    else if (fAbsBits <= pow(2, 13))
    {
        eTo = data::bytes;
    }
    else if (fAbsBits <= pow(2, 23))
    {
        eTo = data::kibibytes;
    }
    else if (fAbsBits <= pow(2, 33))
    {
        eTo = data::mebibytes;
    }
    else if (fAbsBits <= pow(2, 43))
    {
        eTo = data::gibibytes;
    }
    else if (fAbsBits <= pow(2, 53))
    {
        eTo = data::tebibytes;
    }

    return convert(unit).to(eTo);
}
