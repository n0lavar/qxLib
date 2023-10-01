/**

    @file      flags.inl
    @author    Khrapov
    @date      29.09.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<enumeration_c enum_t>
flags<enum_t>::flags(enum_t eFlag) noexcept : m_EnumFlags(underlying_type(eFlag))
{
}

template<enumeration_c enum_t>
template<class... args_t>
    requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
flags<enum_t>::flags(args_t... flags) noexcept
{
    add(flags...);
}

template <enumeration_c enum_t>
flags<enum_t>& flags<enum_t>::operator=(enum_t eFlag) noexcept
{
	m_EnumFlags = underlying_type(eFlag);
	return *this;
}

template <enumeration_c enum_t>
auto flags<enum_t>::operator<=>(enum_t eFlag) const noexcept
{
	return underlying_type(m_EnumFlags) <=> underlying_type(eFlag);
}

template <enumeration_c enum_t>
template <class ... args_t> requires (sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
void flags<enum_t>::add(args_t... flags) noexcept
{
	((m_EnumFlags |= underlying_type(flags)), ...);
}

template <enumeration_c enum_t>
template <class ... args_t> requires (sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
void flags<enum_t>::remove(args_t... flags) noexcept
{
	((m_EnumFlags &= ~underlying_type(flags)), ...);
}

template <enumeration_c enum_t>
bool flags<enum_t>::contains(enum_t eFlag) const noexcept
{
	return m_EnumFlags & underlying_type(eFlag);
}

template <enumeration_c enum_t>
template <class ... args_t> requires (sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
bool flags<enum_t>::contains_all(args_t... flags) const noexcept
{
	return (contains(flags) && ...);
}

template <enumeration_c enum_t>
template <class ... args_t> requires (sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
bool flags<enum_t>::contains_any(args_t... flags) const noexcept
{
	return (contains(flags) || ...);
}

} // namespace qx
