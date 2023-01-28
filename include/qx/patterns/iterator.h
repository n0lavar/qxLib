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

template<class C>
class const_iterator;

/**

    @class   iterator
    @brief   Non-const random access iterator type
    @details Use it for range-based loops and std algorithms
             C have to provide at(size_t)
    @tparam  C - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class C>
class iterator
{
    friend class const_iterator<C>;

public:
    using value_type        = typename C::value_type;
    using pointer           = typename C::pointer;
    using reference         = typename C::reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr iterator() noexcept = default;
    constexpr iterator(C* c, size_type i) noexcept : m_nIndex(i), m_pCollection(c)
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
    size_type m_nIndex      = 0u;
    C*        m_pCollection = nullptr;
};

template<class C>
constexpr iterator<C> operator+(typename iterator<C>::size_type n, iterator<C> it) noexcept
{
    return it += n;
}

/**

    @class   const_iterator
    @brief   Const random access iterator type
    @details Use it for range-based loops and std algorithms
             C have to provide at(size_t)
    @tparam  C - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class C>
class const_iterator
{
public:
    using value_type        = typename C::value_type;
    using pointer           = typename C::const_pointer;
    using reference         = typename C::const_reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr const_iterator() noexcept = default;
    constexpr const_iterator(const C* c, size_type i) noexcept : m_nIndex(i), m_pCollection(c)
    {
    }
    constexpr const_iterator(const iterator<C>& it) noexcept : m_nIndex(it.m_nIndex), m_pCollection(it.m_pCollection)
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
    size_type m_nIndex      = 0u;
    const C*  m_pCollection = nullptr;
};

template<class C>
constexpr const_iterator<C> operator+(typename const_iterator<C>::size_type n, const_iterator<C> it) noexcept
{
    return it += n;
}

template<class C>
class const_reverse_iterator;

/**

    @class   reverse_iterator
    @brief   Non-const random access reverse iterator type
    @details Use it for range-based loops and std algorithms
             C have to provide at(size_t)
    @tparam  C - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class C>
class reverse_iterator
{
    friend class const_reverse_iterator<C>;

public:
    using value_type        = typename C::value_type;
    using pointer           = typename C::pointer;
    using reference         = typename C::reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr reverse_iterator() noexcept = default;
    constexpr reverse_iterator(C* c, size_type i) noexcept : m_nIndex(i), m_pCollection(c)
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
    size_type m_nIndex      = 0u;
    C*        m_pCollection = nullptr;
};

template<class C>
constexpr reverse_iterator<C> operator+(typename reverse_iterator<C>::size_type n, reverse_iterator<C> it) noexcept
{
    return it += n;
}

/**

    @class   const_reverse_iterator
    @brief   Const reverse random access iterator type
    @details Use it for range-based loops and std algorithms
             C have to provide at(size_t)
    @tparam  C - container type
    @author  Khrapov
    @date    19.03.2020

**/
template<class C>
class const_reverse_iterator
{
public:
    using value_type        = typename C::value_type;
    using pointer           = typename C::const_pointer;
    using reference         = typename C::const_reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

public:
    constexpr const_reverse_iterator() noexcept = default;
    constexpr const_reverse_iterator(const C* c, size_type i) noexcept : m_nIndex(i), m_pCollection(c)
    {
    }
    constexpr const_reverse_iterator(const reverse_iterator<C>& it) noexcept
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
    size_type m_nIndex      = 0u;
    const C*  m_pCollection = nullptr;
};

template<class C>
constexpr const_reverse_iterator<C> operator+(
    typename const_reverse_iterator<C>::size_type n,
    const_reverse_iterator<C>                     it) noexcept
{
    return it += n;
}

/**

    @class   base_return_object_iterator
    @brief   This kind of iterator returns value and not reference in access methods
    @details ~
    @tparam  C            - container type
    @tparam  BaseIterator - base iterator type
    @author  Khrapov
    @date    28.01.2023

**/
template<class C, class BaseIterator>
class base_return_object_iterator : public BaseIterator
{
public:
    using value_type        = typename C::value_type;
    using pointer           = typename C::const_pointer;
    using reference         = typename C::const_reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::contiguous_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

    using BaseIterator::BaseIterator;

    [[nodiscard]] constexpr value_type operator*() const noexcept
    {
        return (*BaseIterator::m_pCollection).at(BaseIterator::m_nIndex);
    }
    [[nodiscard]] constexpr value_type operator->() const noexcept
    {
        return (*BaseIterator::m_pCollection).at(BaseIterator::m_nIndex);
    }
    [[nodiscard]] constexpr value_type operator[](size_type m) const noexcept
    {
        return (*BaseIterator::m_pCollection).at(BaseIterator::m_nIndex + m);
    }
};

template<class C>
using return_object_iterator = base_return_object_iterator<C, iterator<C>>;

template<class C>
using const_return_object_iterator = base_return_object_iterator<C, const_iterator<C>>;

template<class C>
using reverse_return_object_iterator = base_return_object_iterator<C, reverse_iterator<C>>;

template<class C>
using const_reverse_return_object_iterator = base_return_object_iterator<C, const_return_object_iterator<C>>;

} // namespace qx
