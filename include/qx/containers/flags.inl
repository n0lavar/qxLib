/**

    @file      flags.inl
    @author    Khrapov
    @date      29.09.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<enumeration_c enum_t>
constexpr void flags<enum_t>::reverse() noexcept
{
    m_EnumFlags = ~m_EnumFlags;
}

template<enumeration_c enum_t>
constexpr void flags<enum_t>::shift_left(size_t nShift) noexcept
{
    m_EnumFlags << nShift;
}

template<enumeration_c enum_t>
constexpr void flags<enum_t>::shift_right(size_t nShift) noexcept
{
    m_EnumFlags >> nShift;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator~() const noexcept
{
    flags result = *this;
    result.reverse();
    return result;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator<<=(size_t nShift) noexcept
{
    shift_left(nShift);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator>>=(size_t nShift) noexcept
{
    shift_right(nShift);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator<<(size_t nShift) const noexcept
{
    flags result = *this;
    result <<= nShift;
    return result;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator>>(size_t nShift) const noexcept
{
    flags result = *this;
    result >>= nShift;
    return result;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>::flags(enum_t eFlag) noexcept : m_EnumFlags(underlying_type(eFlag))
{
}

template<enumeration_c enum_t>
template<class... args_t>
    requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
constexpr flags<enum_t>::flags(args_t... flags) noexcept
{
    add(flags...);
}

template<enumeration_c enum_t>
template<class... args_t>
    requires(sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
constexpr void flags<enum_t>::add(args_t... flags) noexcept
{
    ((m_EnumFlags |= underlying_type(flags)), ...);
}

template<enumeration_c enum_t>
template<class... args_t>
    requires(sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
constexpr void flags<enum_t>::remove(args_t... flags) noexcept
{
    ((m_EnumFlags &= ~underlying_type(flags)), ...);
}

template<enumeration_c enum_t>
template<class... args_t>
    requires(sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
constexpr void flags<enum_t>::xor_(args_t... flags) noexcept
{
    ((m_EnumFlags ^= underlying_type(flags)), ...);
}

template<enumeration_c enum_t>
constexpr auto flags<enum_t>::operator<=>(enum_t eFlag) const noexcept
{
    return underlying_type(m_EnumFlags) <=> underlying_type(eFlag);
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator=(enum_t eFlag) noexcept
{
    m_EnumFlags = underlying_type(eFlag);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator|=(enum_t eFlag) noexcept
{
    add(eFlag);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator&=(enum_t eFlag) noexcept
{
    remove(eFlag);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator^=(enum_t eFlag) noexcept
{
    xor_(eFlag);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator|(enum_t eFlag) const noexcept
{
    flags result = *this;
    result |= eFlag;
    return result;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator&(enum_t eFlag) const noexcept
{
    flags result = *this;
    result &= eFlag;
    return result;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator^(enum_t eFlag) const noexcept
{
    flags result = *this;
    result ^= eFlag;
    return result;
}

template<enumeration_c enum_t>
constexpr void flags<enum_t>::add(flags flags_) noexcept
{
    m_EnumFlags |= flags_.m_EnumFlags;
}

template<enumeration_c enum_t>
constexpr void flags<enum_t>::remove(flags flags_) noexcept
{
    m_EnumFlags &= ~flags_.m_EnumFlags;
}

template<enumeration_c enum_t>
constexpr void flags<enum_t>::xor_(flags flags_) noexcept
{
    m_EnumFlags ^= flags_.m_EnumFlags;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator|=(flags flags_) noexcept
{
    add(flags_);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator&=(flags flags_) noexcept
{
    remove(flags_);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t>& flags<enum_t>::operator^=(flags flags_) noexcept
{
    xor_(flags_);
    return *this;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator|(flags flags_) const noexcept
{
    flags result = *this;
    result |= flags_;
    return result;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator&(flags flags_) const noexcept
{
    flags result = *this;
    result &= flags_;
    return result;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::operator^(flags flags_) const noexcept
{
    flags result = *this;
    result ^= flags_;
    return result;
}

template<enumeration_c enum_t>
constexpr bool flags<enum_t>::contains(enum_t eFlag) const noexcept
{
    return m_EnumFlags & underlying_type(eFlag);
}

template<enumeration_c enum_t>
template<class... args_t>
    requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
constexpr bool flags<enum_t>::contains_all(args_t... flags) const noexcept
{
    return (contains(flags) && ...);
}

template<enumeration_c enum_t>
constexpr bool flags<enum_t>::contains_all(flags other) const noexcept
{
    return (m_EnumFlags & other.m_EnumFlags) == other.m_EnumFlags;
}

template<enumeration_c enum_t>
template<class... args_t>
    requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
constexpr bool flags<enum_t>::contains_any(args_t... flags) const noexcept
{
    return (contains(flags) || ...);
}

template<enumeration_c enum_t>
constexpr bool flags<enum_t>::contains_any(flags other) const noexcept
{
    return (m_EnumFlags & other.m_EnumFlags) != 0;
}

template<enumeration_c enum_t>
constexpr typename flags<enum_t>::underlying_type flags<enum_t>::to_integer() const noexcept
{
    return m_EnumFlags;
}

template<enumeration_c enum_t>
constexpr flags<enum_t> flags<enum_t>::all_flags() noexcept
{
    flags flags;
    flags.m_EnumFlags = std::numeric_limits<underlying_type>::max();
    return flags;
}

} // namespace qx
