/**

    @file      base_iterator.inl
    @author    Khrapov
    @date      14.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

template<class container_t>
constexpr base_iterator<container_t>::operator void*() noexcept
{
    return &(*m_pContainer).at(m_nIndex);
}

template<class container_t>
constexpr void base_iterator<container_t>::shift(difference_type nShift) noexcept
{
    m_nIndex += nShift;
}

template<class container_t>
constexpr decltype(auto) base_iterator<container_t>::get(difference_type nShift) const noexcept
{
    return (*m_pContainer).at(m_nIndex + nShift);
}

template<class container_t>
constexpr typename base_iterator<container_t>::size_type base_iterator<container_t>::get_index() const noexcept
{
    return m_nIndex;
}

template<class container_t, class derived_t>
template<class iterator_t>
    requires derived_from_template_c<iterator_t, base_iterator>
constexpr typename base_forward_iterator<container_t, derived_t>::super_type::difference_type base_forward_iterator<
    container_t,
    derived_t>::operator-(const iterator_t& r) const noexcept
{
    return static_cast<typename super_type::difference_type>(super_type::get_index() - r.get_index());
}

template<class container_t, class derived_t>
constexpr bool base_forward_iterator<container_t, derived_t>::operator<(const base_forward_iterator& r) const noexcept
{
    return super_type::get_index() < r.get_index();
}

template<class container_t, class derived_t>
constexpr bool base_forward_iterator<container_t, derived_t>::operator<=(const base_forward_iterator& r) const noexcept
{
    return super_type::get_index() <= r.get_index();
}

template<class container_t, class derived_t>
constexpr bool base_forward_iterator<container_t, derived_t>::operator>(const base_forward_iterator& r) const noexcept
{
    return super_type::get_index() > r.get_index();
}

template<class container_t, class derived_t>
constexpr bool base_forward_iterator<container_t, derived_t>::operator>=(const base_forward_iterator& r) const noexcept
{
    return super_type::get_index() >= r.get_index();
}

template<class container_t, class derived_t>
constexpr bool base_forward_iterator<container_t, derived_t>::operator!=(const base_forward_iterator& r) const noexcept
{
    return super_type::get_index() != r.get_index();
}

template<class container_t, class derived_t>
constexpr bool base_forward_iterator<container_t, derived_t>::operator==(const base_forward_iterator& r) const noexcept
{
    return super_type::get_index() == r.get_index();
}

template<class container_t, class derived_t>
constexpr typename base_forward_iterator<container_t, derived_t>::decayed_derived_type& base_forward_iterator<
    container_t,
    derived_t>::operator++() noexcept
{
    super_type::shift(1);
    return static_cast<decayed_derived_type&>(*this);
}

template<class container_t, class derived_t>
constexpr typename base_forward_iterator<container_t, derived_t>::decayed_derived_type& base_forward_iterator<
    container_t,
    derived_t>::operator--() noexcept
{
    super_type::shift(-1);
    return static_cast<decayed_derived_type&>(*this);
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename base_forward_iterator<container_t, derived_t>::decayed_derived_type
    base_forward_iterator<container_t, derived_t>::operator++(int) noexcept
{
    decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
    super_type::shift(1);
    return r;
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename base_forward_iterator<container_t, derived_t>::decayed_derived_type
    base_forward_iterator<container_t, derived_t>::operator--(int) noexcept
{
    decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
    super_type::shift(-1);
    return r;
}

template<class container_t, class derived_t>
constexpr typename base_forward_iterator<container_t, derived_t>::decayed_derived_type& base_forward_iterator<
    container_t,
    derived_t>::operator+=(typename super_type::difference_type n) noexcept
{
    super_type::shift(n);
    return static_cast<decayed_derived_type&>(*this);
}

template<class container_t, class derived_t>
constexpr typename base_forward_iterator<container_t, derived_t>::decayed_derived_type& base_forward_iterator<
    container_t,
    derived_t>::operator-=(typename super_type::difference_type n) noexcept
{
    super_type::shift(-n);
    return static_cast<decayed_derived_type&>(*this);
}

template<class container_t, class derived_t>
constexpr typename base_forward_iterator<container_t, derived_t>::decayed_derived_type base_forward_iterator<
    container_t,
    derived_t>::operator+(typename super_type::difference_type n) const noexcept
{
    decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
    return r += n;
}

template<class container_t, class derived_t>
constexpr typename base_forward_iterator<container_t, derived_t>::decayed_derived_type base_forward_iterator<
    container_t,
    derived_t>::operator-(typename super_type::difference_type n) const noexcept
{
    decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
    return r -= n;
}

template<class iterator_t>
    requires derived_from_template_c<iterator_t, base_forward_iterator>
constexpr iterator_t operator+(typename iterator_t::size_type n, iterator_t it) noexcept
{
    return it += n;
}

template<class container_t, class derived_t>
template<class iterator_t>
    requires derived_from_template_c<iterator_t, base_iterator>
constexpr typename base_reverse_iterator<container_t, derived_t>::super_type::difference_type base_reverse_iterator<
    container_t,
    derived_t>::operator-(const iterator_t& r) const noexcept
{
    return static_cast<typename super_type::difference_type>(r.get_index() - super_type::get_index());
}

template<class container_t, class derived_t>
constexpr bool base_reverse_iterator<container_t, derived_t>::operator<(const base_reverse_iterator& r) const noexcept
{
    return super_type::get_index() + 1 > r.get_index() + 1;
}

template<class container_t, class derived_t>
constexpr bool base_reverse_iterator<container_t, derived_t>::operator<=(const base_reverse_iterator& r) const noexcept
{
    return super_type::get_index() + 1 >= r.get_index() + 1;
}

template<class container_t, class derived_t>
constexpr bool base_reverse_iterator<container_t, derived_t>::operator>(const base_reverse_iterator& r) const noexcept
{
    return super_type::get_index() + 1 < r.get_index() + 1;
}

template<class container_t, class derived_t>
constexpr bool base_reverse_iterator<container_t, derived_t>::operator>=(const base_reverse_iterator& r) const noexcept
{
    return super_type::get_index() + 1 <= r.get_index() + 1;
}

template<class container_t, class derived_t>
constexpr bool base_reverse_iterator<container_t, derived_t>::operator!=(const base_reverse_iterator& r) const noexcept
{
    return super_type::get_index() + 1 != r.get_index() + 1;
}

template<class container_t, class derived_t>
constexpr bool base_reverse_iterator<container_t, derived_t>::operator==(const base_reverse_iterator& r) const noexcept
{
    return super_type::get_index() + 1 == r.get_index() + 1;
}

template<class container_t, class derived_t>
constexpr typename base_reverse_iterator<container_t, derived_t>::decayed_derived_type& base_reverse_iterator<
    container_t,
    derived_t>::operator++() noexcept
{
    super_type::shift(-1);
    return static_cast<decayed_derived_type&>(*this);
}

template<class container_t, class derived_t>
constexpr typename base_reverse_iterator<container_t, derived_t>::decayed_derived_type& base_reverse_iterator<
    container_t,
    derived_t>::operator--() noexcept
{
    super_type::shift(1);
    return static_cast<decayed_derived_type&>(*this);
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename base_reverse_iterator<container_t, derived_t>::decayed_derived_type
    base_reverse_iterator<container_t, derived_t>::operator++(int) noexcept
{
    decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
    super_type::shift(-1);
    return r;
}

template<class container_t, class derived_t>
[[nodiscard]] constexpr typename base_reverse_iterator<container_t, derived_t>::decayed_derived_type
    base_reverse_iterator<container_t, derived_t>::operator--(int) noexcept
{
    decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
    super_type::shift(1);
    return r;
}

template<class container_t, class derived_t>
constexpr typename base_reverse_iterator<container_t, derived_t>::decayed_derived_type& base_reverse_iterator<
    container_t,
    derived_t>::operator+=(typename super_type::difference_type n) noexcept
{
    super_type::shift(-n);
    return static_cast<decayed_derived_type&>(*this);
}

template<class container_t, class derived_t>
constexpr typename base_reverse_iterator<container_t, derived_t>::decayed_derived_type& base_reverse_iterator<
    container_t,
    derived_t>::operator-=(typename super_type::difference_type n) noexcept
{
    super_type::shift(n);
    return static_cast<decayed_derived_type&>(*this);
}

template<class container_t, class derived_t>
constexpr typename base_reverse_iterator<container_t, derived_t>::decayed_derived_type base_reverse_iterator<
    container_t,
    derived_t>::operator+(typename super_type::difference_type n) const noexcept
{
    decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
    return r += n;
}

template<class container_t, class derived_t>
constexpr typename base_reverse_iterator<container_t, derived_t>::decayed_derived_type base_reverse_iterator<
    container_t,
    derived_t>::operator-(typename super_type::difference_type n) const noexcept
{
    decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
    return r -= n;
}

template<class iterator_t>
    requires derived_from_template_c<iterator_t, base_reverse_iterator>
constexpr iterator_t operator+(typename iterator_t::size_type n, iterator_t it) noexcept
{
    return it += n;
}

} // namespace qx
