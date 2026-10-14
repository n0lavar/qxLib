/**

    @file      base_iterator.h
    @author    Khrapov
    @date      2.12.2023
    @copyright (c) Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/meta/concepts.h>

#include <iterator>
#include <ranges>

namespace qx
{

/**

    @class   base_iterator
    @brief   Base contiguous iterator with a container pointer and an index
    @tparam  container_t - container satisfying std::ranges::contiguous_range concept
    @author  Khrapov
    @date    2.12.2023

**/
template<class container_t>
/* requires std::ranges::contiguous_range<container_t> */
class base_iterator
{
public:
    template<class container_t_, class derived_t_>
    friend class base_forward_iterator;

    template<class container_t_, class derived_t_>
    friend class base_reverse_iterator;

    using difference_type = typename container_t::difference_type;
    using size_type       = typename container_t::size_type;
    using value_type      = typename container_t::value_type;
    using pointer         = typename container_t::pointer;
    using const_pointer   = typename container_t::const_pointer;
    using reference       = typename container_t::reference;
    using const_reference = typename container_t::const_reference;

    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr base_iterator() noexcept = default;
    constexpr base_iterator(container_t* pContainer, size_type nIndex) noexcept
        : m_nIndex(nIndex)
        , m_pContainer(pContainer)
    {
    }
    constexpr operator void*() noexcept;

protected:
    constexpr void           shift(difference_type nShift) noexcept;
    constexpr decltype(auto) get(difference_type nShift = 0) const noexcept;
    constexpr size_type      get_index() const noexcept;

private:
    size_type    m_nIndex     = 0u;
    container_t* m_pContainer = nullptr;
};

/**

    @class   base_forward_iterator
    @brief   Basic contiguous forward iterator, meaning that incrementing an iterator will lead it moving forward
    @tparam  container_t - container satisfying std::ranges::contiguous_range concept
    @tparam  derived_t   - derived iterator type
    @author  Khrapov
    @date    2.12.2023

**/
template<class container_t, class derived_t>
class base_forward_iterator : public base_iterator<container_t>
{
    using super_type           = base_iterator<container_t>;
    using decayed_derived_type = std::decay_t<derived_t>;

public:
    using super_type::super_type;

    template<class iterator_t>
        requires derived_from_template_c<iterator_t, base_iterator>
    constexpr typename super_type::difference_type operator-(const iterator_t& r) const noexcept;
    constexpr bool                                 operator<(const base_forward_iterator& r) const noexcept;
    constexpr bool                                 operator<=(const base_forward_iterator& r) const noexcept;
    constexpr bool                                 operator>(const base_forward_iterator& r) const noexcept;
    constexpr bool                                 operator>=(const base_forward_iterator& r) const noexcept;
    constexpr bool                                 operator!=(const base_forward_iterator& r) const noexcept;
    constexpr bool                                 operator==(const base_forward_iterator& r) const noexcept;
    constexpr decayed_derived_type&                operator++() noexcept;
    constexpr decayed_derived_type&                operator--() noexcept;
    [[nodiscard]] constexpr decayed_derived_type   operator++(int) noexcept;
    [[nodiscard]] constexpr decayed_derived_type   operator--(int) noexcept;
    constexpr decayed_derived_type&                operator+=(typename super_type::difference_type n) noexcept;
    constexpr decayed_derived_type&                operator-=(typename super_type::difference_type n) noexcept;
    constexpr decayed_derived_type                 operator+(typename super_type::difference_type n) const noexcept;
    constexpr decayed_derived_type                 operator-(typename super_type::difference_type n) const noexcept;
};

template<class iterator_t>
    requires derived_from_template_c<iterator_t, base_forward_iterator>
constexpr iterator_t operator+(typename iterator_t::size_type n, iterator_t it) noexcept;

/**

    @class   base_reverse_iterator
    @brief   Basic contiguous reverse iterator, meaning that incrementing an iterator will lead it moving backward
    @tparam  container_t - container satisfying std::ranges::contiguous_range concept
    @tparam  derived_t   - derived iterator type
    @author  Khrapov
    @date    2.12.2023

**/
template<class container_t, class derived_t>
class base_reverse_iterator : public base_iterator<container_t>
{
    using super_type           = base_iterator<container_t>;
    using decayed_derived_type = std::decay_t<derived_t>;

public:
    using super_type::super_type;

    template<class iterator_t>
        requires derived_from_template_c<iterator_t, base_iterator>
    constexpr typename super_type::difference_type operator-(const iterator_t& r) const noexcept;
    // + 1 is necessary, as `m_nIndex = -1 (aka size_type::max)`
    // may be used as end (past-the-last) element
    constexpr bool                               operator<(const base_reverse_iterator& r) const noexcept;
    constexpr bool                               operator<=(const base_reverse_iterator& r) const noexcept;
    constexpr bool                               operator>(const base_reverse_iterator& r) const noexcept;
    constexpr bool                               operator>=(const base_reverse_iterator& r) const noexcept;
    constexpr bool                               operator!=(const base_reverse_iterator& r) const noexcept;
    constexpr bool                               operator==(const base_reverse_iterator& r) const noexcept;
    constexpr decayed_derived_type&              operator++() noexcept;
    constexpr decayed_derived_type&              operator--() noexcept;
    [[nodiscard]] constexpr decayed_derived_type operator++(int) noexcept;
    [[nodiscard]] constexpr decayed_derived_type operator--(int) noexcept;
    constexpr decayed_derived_type&              operator+=(typename super_type::difference_type n) noexcept;
    constexpr decayed_derived_type&              operator-=(typename super_type::difference_type n) noexcept;
    constexpr decayed_derived_type               operator+(typename super_type::difference_type n) const noexcept;
    constexpr decayed_derived_type               operator-(typename super_type::difference_type n) const noexcept;
};

template<class iterator_t>
    requires derived_from_template_c<iterator_t, base_reverse_iterator>
constexpr iterator_t operator+(typename iterator_t::size_type n, iterator_t it) noexcept;

} // namespace qx

#include <qx/patterns/contiguous_iterator/base_iterator.inl>
