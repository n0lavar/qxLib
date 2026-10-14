/**

    @file      iterator.inl
    @author    Khrapov
    @date      14.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename iterator<container_t, derived_t>::super_type::reference iterator<
    container_t,
    derived_t>::operator*() const noexcept
{
    return super_type::get();
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename iterator<container_t, derived_t>::super_type::pointer iterator<
    container_t,
    derived_t>::operator->() const noexcept
{
    return &super_type::get();
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename iterator<container_t, derived_t>::super_type::reference iterator<
    container_t,
    derived_t>::operator[](typename super_type::size_type i) const noexcept
{
    return super_type::get(i);
}

template<class container_t, class derived_t>
constexpr const_iterator<container_t, derived_t>::const_iterator(const iterator<container_t>& it) noexcept
    : super_type(it.m_pContainer, it.m_nIndex)
{
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename const_iterator<container_t, derived_t>::super_type::const_reference const_iterator<
    container_t,
    derived_t>::operator*() const noexcept
{
    return super_type::get();
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename const_iterator<container_t, derived_t>::super_type::const_pointer const_iterator<
    container_t,
    derived_t>::operator->() const noexcept
{
    return &super_type::get();
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename const_iterator<container_t, derived_t>::super_type::const_reference const_iterator<
    container_t,
    derived_t>::operator[](typename super_type::size_type m) const noexcept
{
    return super_type::get(m);
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename reverse_iterator<container_t, derived_t>::super_type::reference reverse_iterator<
    container_t,
    derived_t>::operator*() const noexcept
{
    return super_type::get();
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename reverse_iterator<container_t, derived_t>::super_type::pointer reverse_iterator<
    container_t,
    derived_t>::operator->() const noexcept
{
    return &super_type::get();
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename reverse_iterator<container_t, derived_t>::super_type::reference reverse_iterator<
    container_t,
    derived_t>::operator[](typename super_type::size_type m) const noexcept
{
    return super_type::get(m);
}

template<class container_t, class derived_t>
constexpr const_reverse_iterator<container_t, derived_t>::const_reverse_iterator(
    const reverse_iterator<container_t>& it) noexcept
    : super_type(it.m_pContainer, it.m_nIndex)
{
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename const_reverse_iterator<container_t, derived_t>::super_type::const_reference
    const_reverse_iterator<container_t, derived_t>::operator*() const noexcept
{
    return super_type::get();
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename const_reverse_iterator<container_t, derived_t>::super_type::const_pointer
    const_reverse_iterator<container_t, derived_t>::operator->() const noexcept
{
    return &super_type::get();
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename const_reverse_iterator<container_t, derived_t>::super_type::const_reference
    const_reverse_iterator<container_t, derived_t>::operator[](typename super_type::size_type m) const noexcept
{
    return super_type::get(m);
}

} // namespace qx
