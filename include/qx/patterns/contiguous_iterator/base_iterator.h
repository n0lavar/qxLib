/**

    @file      base_iterator.h
    @author    Khrapov
    @date      2.12.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

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
    @details ~
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
    constexpr operator void*() noexcept
    {
        return &(*m_pContainer).at(m_nIndex);
    }

protected:
    void shift(difference_type nShift) noexcept
    {
        m_nIndex += nShift;
    }
    auto&& get(difference_type nShift = 0) const noexcept
    {
        return (*m_pContainer).at(m_nIndex + nShift);
    }
    size_type get_index() const noexcept
    {
        return m_nIndex;
    }

private:
    size_type    m_nIndex     = 0u;
    container_t* m_pContainer = nullptr;
};

/**

    @class   base_forward_iterator
    @brief   Basic contiguous forward iterator, meaning that incrementing an iterator will lead it moving forward
    @details ~
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
    constexpr typename super_type::difference_type operator-(const iterator_t& r) const noexcept
    {
        return static_cast<typename super_type::difference_type>(super_type::get_index() - r.get_index());
    }
    constexpr bool operator<(const base_forward_iterator& r) const noexcept
    {
        return super_type::get_index() < r.get_index();
    }
    constexpr bool operator<=(const base_forward_iterator& r) const noexcept
    {
        return super_type::get_index() <= r.get_index();
    }
    constexpr bool operator>(const base_forward_iterator& r) const noexcept
    {
        return super_type::get_index() > r.get_index();
    }
    constexpr bool operator>=(const base_forward_iterator& r) const noexcept
    {
        return super_type::get_index() >= r.get_index();
    }
    constexpr bool operator!=(const base_forward_iterator& r) const noexcept
    {
        return super_type::get_index() != r.get_index();
    }
    constexpr bool operator==(const base_forward_iterator& r) const noexcept
    {
        return super_type::get_index() == r.get_index();
    }
    constexpr decayed_derived_type& operator++() noexcept
    {
        super_type::shift(1);
        return static_cast<decayed_derived_type&>(*this);
    }
    constexpr decayed_derived_type& operator--() noexcept
    {
        super_type::shift(-1);
        return static_cast<decayed_derived_type&>(*this);
    }
    [[nodiscard]] constexpr decayed_derived_type operator++(int) noexcept
    {
        decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
        super_type::shift(1);
        return r;
    }
    [[nodiscard]] constexpr decayed_derived_type operator--(int) noexcept
    {
        decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
        super_type::shift(-1);
        return r;
    }
    constexpr decayed_derived_type& operator+=(typename super_type::difference_type n) noexcept
    {
        super_type::shift(n);
        return static_cast<decayed_derived_type&>(*this);
    }
    constexpr decayed_derived_type& operator-=(typename super_type::difference_type n) noexcept
    {
        super_type::shift(-n);
        return static_cast<decayed_derived_type&>(*this);
    }
    constexpr decayed_derived_type operator+(typename super_type::difference_type n) const noexcept
    {
        decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
        return r += n;
    }
    constexpr decayed_derived_type operator-(typename super_type::difference_type n) const noexcept
    {
        decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
        return r -= n;
    }
};

template<class iterator_t>
    requires derived_from_template_c<iterator_t, base_forward_iterator>
constexpr iterator_t operator+(typename iterator_t::size_type n, iterator_t it) noexcept
{
    return it += n;
}

/**

    @class   base_reverse_iterator
    @brief   Basic contiguous reverse iterator, meaning that incrementing an iterator will lead it moving backward
    @details ~
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
    constexpr typename super_type::difference_type operator-(const iterator_t& r) const noexcept
    {
        return static_cast<typename super_type::difference_type>(r.get_index() - super_type::get_index());
    }
    // + 1 is necessary, as `m_nIndex = -1 (aka size_type::max)`
    // may be used as end (past-the-last) element
    constexpr bool operator<(const base_reverse_iterator& r) const noexcept
    {
        return super_type::get_index() + 1 > r.get_index() + 1;
    }
    constexpr bool operator<=(const base_reverse_iterator& r) const noexcept
    {
        return super_type::get_index() + 1 >= r.get_index() + 1;
    }
    constexpr bool operator>(const base_reverse_iterator& r) const noexcept
    {
        return super_type::get_index() + 1 < r.get_index() + 1;
    }
    constexpr bool operator>=(const base_reverse_iterator& r) const noexcept
    {
        return super_type::get_index() + 1 <= r.get_index() + 1;
    }
    constexpr bool operator!=(const base_reverse_iterator& r) const noexcept
    {
        return super_type::get_index() + 1 != r.get_index() + 1;
    }
    constexpr bool operator==(const base_reverse_iterator& r) const noexcept
    {
        return super_type::get_index() + 1 == r.get_index() + 1;
    }
    constexpr decayed_derived_type& operator++() noexcept
    {
        super_type::shift(-1);
        return static_cast<decayed_derived_type&>(*this);
    }
    constexpr decayed_derived_type& operator--() noexcept
    {
        super_type::shift(1);
        return static_cast<decayed_derived_type&>(*this);
    }
    [[nodiscard]] constexpr decayed_derived_type operator++(int) noexcept
    {
        decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
        super_type::shift(-1);
        return r;
    }
    [[nodiscard]] constexpr decayed_derived_type operator--(int) noexcept
    {
        decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
        super_type::shift(1);
        return r;
    }
    constexpr decayed_derived_type& operator+=(typename super_type::difference_type n) noexcept
    {
        super_type::shift(-n);
        return static_cast<decayed_derived_type&>(*this);
    }
    constexpr decayed_derived_type& operator-=(typename super_type::difference_type n) noexcept
    {
        super_type::shift(n);
        return static_cast<decayed_derived_type&>(*this);
    }
    constexpr decayed_derived_type operator+(typename super_type::difference_type n) const noexcept
    {
        decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
        return r += n;
    }
    constexpr decayed_derived_type operator-(typename super_type::difference_type n) const noexcept
    {
        decayed_derived_type r(static_cast<const decayed_derived_type&>(*this));
        return r -= n;
    }
};

template<class iterator_t>
    requires derived_from_template_c<iterator_t, base_reverse_iterator>
constexpr iterator_t operator+(typename iterator_t::size_type n, iterator_t it) noexcept
{
    return it += n;
}

} // namespace qx
