/**

    @file      iterator.h
    @brief     Contains random access iterator classes
    @author    Khrapov
    @date      27.07.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <iterator>

namespace qx
{

template<class container_t>
class const_iterator;

/**

    @class   iterator
    @brief   Non-const random access iterator type
    @details Use it for range-based loops and std algorithms
             container_t have to provide at(size_t)
    @tparam  container_t - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class container_t>
class iterator
{
    friend class const_iterator<container_t>;

public:
    using value_type        = typename container_t::value_type;
    using pointer           = typename container_t::pointer;
    using reference         = typename container_t::reference;
    using difference_type   = typename container_t::difference_type;
    using size_type         = typename container_t::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr iterator() noexcept = default;
    constexpr iterator(container_t* c, size_type i) noexcept : m_nIndex(i), m_pCollection(c)
    {
    }
    [[nodiscard]] constexpr reference operator*() const noexcept
    {
        return (*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr pointer operator->() const noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr reference operator[](size_type i) const noexcept
    {
        return (*m_pCollection).at(m_nIndex + i);
    }
    constexpr iterator& operator++() noexcept
    {
        ++m_nIndex;
        return *this;
    }
    constexpr iterator& operator--() noexcept
    {
        --m_nIndex;
        return *this;
    }
    [[nodiscard]] constexpr iterator operator++(int) noexcept
    {
        iterator r(*this);
        ++m_nIndex;
        return r;
    }
    [[nodiscard]] constexpr iterator operator--(int) noexcept
    {
        iterator r(*this);
        --m_nIndex;
        return r;
    }
    constexpr iterator& operator+=(size_type n) noexcept
    {
        m_nIndex += n;
        return *this;
    }
    constexpr iterator& operator-=(size_type n) noexcept
    {
        m_nIndex -= n;
        return *this;
    }
    constexpr iterator operator+(size_type n) const noexcept
    {
        iterator r(*this);
        return r += n;
    }
    constexpr iterator operator-(size_type n) const noexcept
    {
        iterator r(*this);
        return r -= n;
    }
    constexpr difference_type operator-(const iterator& r) const noexcept
    {
        return static_cast<difference_type>(m_nIndex - r.m_nIndex);
    }
    constexpr bool operator<(const iterator& r) const noexcept
    {
        return m_nIndex < r.m_nIndex;
    }
    constexpr bool operator<=(const iterator& r) const noexcept
    {
        return m_nIndex <= r.m_nIndex;
    }
    constexpr bool operator>(const iterator& r) const noexcept
    {
        return m_nIndex > r.m_nIndex;
    }
    constexpr bool operator>=(const iterator& r) const noexcept
    {
        return m_nIndex >= r.m_nIndex;
    }
    constexpr bool operator!=(const iterator& r) const noexcept
    {
        return m_nIndex != r.m_nIndex;
    }
    constexpr bool operator==(const iterator& r) const noexcept
    {
        return m_nIndex == r.m_nIndex;
    }
    constexpr operator void*() noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }

protected:
    size_type    m_nIndex      = 0u;
    container_t* m_pCollection = nullptr;
};

template<class container_t>
constexpr iterator<container_t> operator+(
    typename iterator<container_t>::size_type n,
    iterator<container_t>                     it) noexcept
{
    return it += n;
}

/**

    @class   const_iterator
    @brief   Const random access iterator type
    @details Use it for range-based loops and std algorithms
             container_t have to provide at(size_t)
    @tparam  container_t - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class container_t>
class const_iterator
{
public:
    using value_type        = typename container_t::value_type;
    using pointer           = typename container_t::const_pointer;
    using reference         = typename container_t::const_reference;
    using difference_type   = typename container_t::difference_type;
    using size_type         = typename container_t::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr const_iterator() noexcept = default;
    constexpr const_iterator(const container_t* c, size_type i) noexcept : m_nIndex(i), m_pCollection(c)
    {
    }
    constexpr const_iterator(const iterator<container_t>& it) noexcept
        : m_nIndex(it.m_nIndex)
        , m_pCollection(it.m_pCollection)
    {
    }
    [[nodiscard]] constexpr reference operator*() const noexcept
    {
        return (*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr pointer operator->() const noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr reference operator[](size_type m) const noexcept
    {
        return (*m_pCollection).at(m_nIndex + m);
    }
    constexpr const_iterator& operator++() noexcept
    {
        ++m_nIndex;
        return *this;
    }
    constexpr const_iterator& operator--() noexcept
    {
        --m_nIndex;
        return *this;
    }
    [[nodiscard]] constexpr const_iterator operator++(int) noexcept
    {
        const_iterator r(*this);
        ++m_nIndex;
        return r;
    }
    [[nodiscard]] constexpr const_iterator operator--(int) noexcept
    {
        const_iterator r(*this);
        --m_nIndex;
        return r;
    }
    constexpr const_iterator& operator+=(size_type n) noexcept
    {
        m_nIndex += n;
        return *this;
    }
    constexpr const_iterator& operator-=(size_type n) noexcept
    {
        m_nIndex -= n;
        return *this;
    }
    constexpr const_iterator operator+(size_type n) const noexcept
    {
        const_iterator r(*this);
        return r += n;
    }
    constexpr const_iterator operator-(size_type n) const noexcept
    {
        const_iterator r(*this);
        return r -= n;
    }
    constexpr difference_type operator-(const_iterator const& r) const noexcept
    {
        return static_cast<difference_type>(m_nIndex - r.m_nIndex);
    }
    constexpr bool operator<(const const_iterator& r) const noexcept
    {
        return m_nIndex < r.m_nIndex;
    }
    constexpr bool operator<=(const const_iterator& r) const noexcept
    {
        return m_nIndex <= r.m_nIndex;
    }
    constexpr bool operator>(const const_iterator& r) const noexcept
    {
        return m_nIndex > r.m_nIndex;
    }
    constexpr bool operator>=(const const_iterator& r) const noexcept
    {
        return m_nIndex >= r.m_nIndex;
    }
    constexpr bool operator!=(const const_iterator& r) const noexcept
    {
        return m_nIndex != r.m_nIndex;
    }
    constexpr bool operator==(const const_iterator& r) const noexcept
    {
        return m_nIndex == r.m_nIndex;
    }
    constexpr operator const void*() const noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }

protected:
    size_type          m_nIndex      = 0u;
    const container_t* m_pCollection = nullptr;
};

template<class container_t>
constexpr const_iterator<container_t> operator+(
    typename const_iterator<container_t>::size_type n,
    const_iterator<container_t>                     it) noexcept
{
    return it += n;
}

template<class container_t>
class const_reverse_iterator;

/**

    @class   reverse_iterator
    @brief   Non-const random access reverse iterator type
    @details Use it for range-based loops and std algorithms
             container_t have to provide at(size_t)
    @tparam  container_t - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class container_t>
class reverse_iterator
{
    friend class const_reverse_iterator<container_t>;

public:
    using value_type        = typename container_t::value_type;
    using pointer           = typename container_t::pointer;
    using reference         = typename container_t::reference;
    using difference_type   = typename container_t::difference_type;
    using size_type         = typename container_t::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr reverse_iterator() noexcept = default;
    constexpr reverse_iterator(container_t* c, size_type i) noexcept : m_nIndex(i), m_pCollection(c)
    {
    }
    [[nodiscard]] constexpr reference operator*() const noexcept
    {
        return (*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr pointer operator->() const noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr reference operator[](size_type m) const noexcept
    {
        return (*m_pCollection).at(m_nIndex + m);
    }
    constexpr reverse_iterator& operator++() noexcept
    {
        --m_nIndex;
        return *this;
    }
    constexpr reverse_iterator& operator--() noexcept
    {
        ++m_nIndex;
        return *this;
    }
    [[nodiscard]] constexpr reverse_iterator operator++(int) noexcept
    {
        reverse_iterator r(*this);
        --m_nIndex;
        return r;
    }
    [[nodiscard]] constexpr reverse_iterator operator--(int) noexcept
    {
        reverse_iterator r(*this);
        ++m_nIndex;
        return r;
    }
    constexpr reverse_iterator& operator+=(size_type n) noexcept
    {
        m_nIndex -= n;
        return *this;
    }
    constexpr reverse_iterator& operator-=(size_type n) noexcept
    {
        m_nIndex += n;
        return *this;
    }
    constexpr reverse_iterator operator+(size_type n) const noexcept
    {
        reverse_iterator r(*this);
        return r -= n;
    }
    constexpr reverse_iterator operator-(size_type n) const noexcept
    {
        reverse_iterator r(*this);
        return r += n;
    }
    constexpr difference_type operator-(const reverse_iterator& r) const noexcept
    {
        return static_cast<difference_type>(r.m_nIndex - m_nIndex);
    }
    // + 1 is necessary, as `m_nIndex = -1 (aka size_type::max)`
    // may be used as end (past-the-last) element
    constexpr bool operator<(const reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 > r.m_nIndex + 1;
    }
    constexpr bool operator<=(const reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 >= r.m_nIndex + 1;
    }
    constexpr bool operator>(const reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 < r.m_nIndex + 1;
    }
    constexpr bool operator>=(const reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 <= r.m_nIndex + 1;
    }
    constexpr bool operator!=(const reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 != r.m_nIndex + 1;
    }
    constexpr bool operator==(const reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 == r.m_nIndex + 1;
    }
    constexpr operator void*() noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }

protected:
    size_type    m_nIndex      = 0u;
    container_t* m_pCollection = nullptr;
};

template<class container_t>
constexpr reverse_iterator<container_t> operator+(
    typename reverse_iterator<container_t>::size_type n,
    reverse_iterator<container_t>                     it) noexcept
{
    return it += n;
}

/**

    @class   const_reverse_iterator
    @brief   Const reverse random access iterator type
    @details Use it for range-based loops and std algorithms
             container_t have to provide at(size_t)
    @tparam  container_t - container type
    @author  Khrapov
    @date    19.03.2020

**/
template<class container_t>
class const_reverse_iterator
{
public:
    using value_type        = typename container_t::value_type;
    using pointer           = typename container_t::const_pointer;
    using reference         = typename container_t::const_reference;
    using difference_type   = typename container_t::difference_type;
    using size_type         = typename container_t::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr const_reverse_iterator() noexcept = default;
    constexpr const_reverse_iterator(const container_t* c, size_type i) noexcept : m_nIndex(i), m_pCollection(c)
    {
    }
    constexpr const_reverse_iterator(const reverse_iterator<container_t>& it) noexcept
        : m_nIndex(it.m_nIndex)
        , m_pCollection(it.m_pCollection)
    {
    }
    [[nodiscard]] constexpr reference operator*() const noexcept
    {
        return (*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr pointer operator->() const noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr reference operator[](size_type m) const noexcept
    {
        return (*m_pCollection).at(m_nIndex + m);
    }
    constexpr const_reverse_iterator& operator++() noexcept
    {
        --m_nIndex;
        return *this;
    }
    constexpr const_reverse_iterator& operator--() noexcept
    {
        ++m_nIndex;
        return *this;
    }
    [[nodiscard]] constexpr const_reverse_iterator operator++(int) noexcept
    {
        const_reverse_iterator r(*this);
        --m_nIndex;
        return r;
    }
    [[nodiscard]] constexpr const_reverse_iterator operator--(int) noexcept
    {
        const_reverse_iterator r(*this);
        ++m_nIndex;
        return r;
    }
    constexpr const_reverse_iterator& operator+=(size_type n) noexcept
    {
        m_nIndex -= n;
        return *this;
    }
    constexpr const_reverse_iterator& operator-=(size_type n) noexcept
    {
        m_nIndex += n;
        return *this;
    }
    constexpr const_reverse_iterator operator+(size_type n) const noexcept
    {
        const_reverse_iterator r(*this);
        return r -= n;
    }
    constexpr const_reverse_iterator operator-(size_type n) const noexcept
    {
        const_reverse_iterator r(*this);
        return r += n;
    }
    constexpr difference_type operator-(const const_reverse_iterator& r) const noexcept
    {
        return static_cast<difference_type>(r.m_nIndex - m_nIndex);
    }
    // + 1 is necessary, as `m_nIndex = -1 (aka size_type::max)`
    // may be used as end (past-the-last) element
    constexpr bool operator<(const const_reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 > r.m_nIndex + 1;
    }
    constexpr bool operator<=(const const_reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 >= r.m_nIndex + 1;
    }
    constexpr bool operator>(const const_reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 < r.m_nIndex + 1;
    }
    constexpr bool operator>=(const const_reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 <= r.m_nIndex + 1;
    }
    constexpr bool operator!=(const const_reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 != r.m_nIndex + 1;
    }
    constexpr bool operator==(const const_reverse_iterator& r) const noexcept
    {
        return m_nIndex + 1 == r.m_nIndex + 1;
    }
    constexpr operator const void*() const noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }

protected:
    size_type          m_nIndex      = 0u;
    const container_t* m_pCollection = nullptr;
};

template<class container_t>
constexpr const_reverse_iterator<container_t> operator+(
    typename const_reverse_iterator<container_t>::size_type n,
    const_reverse_iterator<container_t>                     it) noexcept
{
    return it += n;
}

/**

    @class   base_return_object_iterator
    @brief   This kind of iterator returns value and not reference in access methods
    @details ~
    @tparam  container_t     - container type
    @tparam  base_iterator_t - base iterator type
    @author  Khrapov
    @date    28.01.2023

**/
template<class container_t, class base_iterator_t>
class base_return_object_iterator : public base_iterator_t
{
public:
    using value_type        = typename container_t::value_type;
    using pointer           = typename container_t::const_pointer;
    using reference         = typename container_t::const_reference;
    using difference_type   = typename container_t::difference_type;
    using size_type         = typename container_t::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

    using base_iterator_t::BaseIterator;

    [[nodiscard]] constexpr value_type operator*() const noexcept
    {
        return (*base_iterator_t::m_pCollection).at(base_iterator_t::m_nIndex);
    }
    [[nodiscard]] constexpr value_type operator->() const noexcept
    {
        return (*base_iterator_t::m_pCollection).at(base_iterator_t::m_nIndex);
    }
    [[nodiscard]] constexpr value_type operator[](size_type m) const noexcept
    {
        return (*base_iterator_t::m_pCollection).at(base_iterator_t::m_nIndex + m);
    }
};

template<class container_t>
using return_object_iterator = base_return_object_iterator<container_t, iterator<container_t>>;

template<class container_t>
using const_return_object_iterator = base_return_object_iterator<container_t, const_iterator<container_t>>;

template<class container_t>
using reverse_return_object_iterator = base_return_object_iterator<container_t, reverse_iterator<container_t>>;

template<class container_t>
using const_reverse_return_object_iterator =
    base_return_object_iterator<container_t, const_return_object_iterator<container_t>>;

} // namespace qx
