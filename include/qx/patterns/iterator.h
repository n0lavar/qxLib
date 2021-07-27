//==============================================================================
//
//!\file                         iterator.h
//
//!\brief       Contains random access iterator classes
//!\details     ~
//
//!\author      Khrapov
//!\date        27.07.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <iterator>

namespace qx
{

template <class C>
class const_iterator;

//==============================================================================
//
//!\class                   qx::iterator<C>
//
//!\brief   Non-const random access iterator type
//!\details Use it for range-based loops and std algorithms
//          C have to provide at(size_t)
//
//!\author  Khrapov
//!\date    27.07.2019
//
//==============================================================================
template <class C>
class iterator
{
    friend class const_iterator<C>;

public:

    using value_type        = typename C::value_type;
    using pointer           = typename C::pointer;
    using reference         = typename C::reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::random_access_iterator_tag;

public:

    constexpr iterator (void) noexcept = default;
    constexpr iterator (C* c, size_type i) noexcept
        : m_nIndex(i)
        , m_pCollection(c)
    {
    }
    [[nodiscard]] constexpr reference operator*(void) noexcept
    {
        return (*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr pointer operator->(void) noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr reference operator[](size_type i) noexcept
    {
        return (*m_pCollection).at(m_nIndex + i);
    }
    constexpr iterator& operator++(void) noexcept
    {
        ++m_nIndex;
        return *this;
    }
    constexpr iterator& operator--(void) noexcept
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
    constexpr iterator & operator+=(size_type n) noexcept
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
    constexpr difference_type operator-(iterator  const& r) const noexcept
    {
        return static_cast<difference_type>(m_nIndex - r.m_nIndex);
    }
    constexpr bool operator<(iterator const & r) const noexcept
    {
        return m_nIndex < r.m_nIndex;
    }
    constexpr bool operator<=(iterator const & r) const noexcept
    {
        return m_nIndex <= r.m_nIndex;
    }
    constexpr bool operator>(iterator const & r) const noexcept
    {
        return m_nIndex > r.m_nIndex;
    }
    constexpr bool operator>=(iterator const & r) const noexcept
    {
        return m_nIndex >= r.m_nIndex;
    }
    constexpr bool operator!=(const iterator & r) const noexcept
    {
        return m_nIndex != r.m_nIndex;
    }
    constexpr bool operator==(const iterator & r) const noexcept
    {
        return m_nIndex == r.m_nIndex;
    }
    constexpr operator void*(void) noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }

private:

    size_type   m_nIndex        = 0u;
    C*          m_pCollection   = nullptr;
};

//==============================================================================
//
//!\class               qx::const_iterator<C>
//
//!\brief   Const random access iterator type
//!\details Use it for range-based loops and std algorithms
//          C have to provide at(size_t)
//
//!\author  Khrapov
//!\date    19.03.2020
//
//==============================================================================
template <class C>
class const_iterator
{
public:

    using value_type        = typename C::value_type;
    using pointer           = typename C::const_pointer;
    using reference         = typename C::const_reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::random_access_iterator_tag;

public:

    constexpr const_iterator (void) noexcept = default;
    constexpr const_iterator (const C* c, size_type i) noexcept
        : m_nIndex(i)
        , m_pCollection(c)
    {
    }
    constexpr const_iterator (const iterator<C>& it) noexcept
        : m_nIndex(it.m_nIndex)
        , m_pCollection(it.m_pCollection)
    {
    }
    [[nodiscard]] constexpr reference operator*(void) noexcept
    {
        return (*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr pointer operator->(void) noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr reference operator[](size_type m) noexcept
    {
        return (*m_pCollection).at(m_nIndex + m);
    }
    constexpr const_iterator& operator++(void) noexcept
    {
        ++m_nIndex;
        return *this;
    }
    constexpr const_iterator& operator--(void) noexcept
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
    constexpr bool operator<(const_iterator const & r) const noexcept
    {
        return m_nIndex < r.m_nIndex;
    }
    constexpr bool operator<=(const_iterator const & r) const noexcept
    {
        return m_nIndex <= r.m_nIndex;
    }
    constexpr bool operator>(const_iterator const & r) const noexcept
    {
        return m_nIndex > r.m_nIndex;
    }
    constexpr bool operator>=(const_iterator const & r) const noexcept
    {
        return m_nIndex >= r.m_nIndex;
    }
    constexpr bool operator!=(const const_iterator & r) const noexcept
    {
        return m_nIndex != r.m_nIndex;
    }
    constexpr bool operator==(const const_iterator & r) const noexcept
    {
        return m_nIndex == r.m_nIndex;
    }
    constexpr operator const void*(void) const noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }

private:

    size_type   m_nIndex        = 0u;
    const C*    m_pCollection   = nullptr;
};


template <class C>
class const_reverse_iterator;

//==============================================================================
//
//!\class                   qx::reverse_iterator<C>
//
//!\brief   Non-const random access reverse iterator type
//!\details Use it for range-based loops and std algorithms
//          C have to provide at(size_t)
//
//!\author  Khrapov
//!\date    27.07.2019
//
//==============================================================================
template <class C>
class reverse_iterator
{
    friend class const_reverse_iterator<C>;

public:

    using value_type        = typename C::value_type;
    using pointer           = typename C::pointer;
    using reference         = typename C::reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::random_access_iterator_tag;

public:

    constexpr reverse_iterator (void) noexcept = default;
    constexpr reverse_iterator (C* c, size_type i) noexcept
        : m_nIndex(i)
        , m_pCollection(c)
    {
    }
    [[nodiscard]] constexpr reference operator*(void) noexcept
    {
        return (*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr pointer operator->(void) noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr reference operator[](size_type m) noexcept
    {
        return (*m_pCollection).at(m_nIndex + m);
    }
    constexpr reverse_iterator& operator++(void) noexcept
    {
        --m_nIndex;
        return *this;
    }
    constexpr reverse_iterator& operator--(void) noexcept
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
    constexpr difference_type operator-(reverse_iterator const& r) const noexcept
    {
        return static_cast<difference_type>(r.m_nIndex - m_nIndex);
    }
    // + 1 is necessary, as `m_nIndex = -1 (aka size_type::max)`
    // may be used as end (past-the-last) element
    constexpr bool operator<(reverse_iterator const & r) const noexcept
    {
        return m_nIndex + 1 > r.m_nIndex + 1;
    }
    constexpr bool operator<=(reverse_iterator const & r) const noexcept
    {
        return m_nIndex + 1 >= r.m_nIndex + 1;
    }
    constexpr bool operator>(reverse_iterator const & r) const noexcept
    {
        return m_nIndex + 1 < r.m_nIndex + 1;
    }
    constexpr bool operator>=(reverse_iterator const & r) const noexcept
    {
        return m_nIndex + 1 <= r.m_nIndex + 1;
    }
    constexpr bool operator!=(const reverse_iterator & r) const noexcept
    {
        return m_nIndex + 1 != r.m_nIndex + 1;
    }
    constexpr bool operator==(const reverse_iterator & r) const noexcept
    {
        return m_nIndex + 1 == r.m_nIndex + 1;
    }
    constexpr operator void*(void) noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }

private:

    size_type   m_nIndex        = 0u;
    C*          m_pCollection   = nullptr;
};

//==============================================================================
//
//!\class               qx::const_reverse_iterator<C>
//
//!\brief   Const reverse random access iterator type
//!\details Use it for range-based loops and std algorithms
//          C have to provide at(size_t)
//
//!\author  Khrapov
//!\date    19.03.2020
//
//==============================================================================
template <class C>
class const_reverse_iterator
{
public:

    using value_type        = typename C::value_type;
    using pointer           = typename C::const_pointer;
    using reference         = typename C::const_reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = std::random_access_iterator_tag;

public:

    constexpr const_reverse_iterator (void) noexcept = default;
    constexpr const_reverse_iterator (const C* c, size_type i) noexcept
        : m_nIndex(i)
        , m_pCollection(c)
    {
    }
    constexpr const_reverse_iterator (const reverse_iterator<C>& it) noexcept
        : m_nIndex(it.m_nIndex)
        , m_pCollection(it.m_pCollection)
    {
    }
    [[nodiscard]] constexpr reference operator*(void) noexcept
    {
        return (*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr pointer operator->(void) noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }
    [[nodiscard]] constexpr reference operator[](size_type m) noexcept
    {
        return (*m_pCollection).at(m_nIndex + m);
    }
    constexpr const_reverse_iterator& operator++(void) noexcept
    {
        --m_nIndex;
        return *this;
    }
    constexpr const_reverse_iterator& operator--(void) noexcept
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
    constexpr difference_type operator-(const_reverse_iterator const& r) const noexcept
    {
        return static_cast<difference_type>(r.m_nIndex - m_nIndex);
    }
    // + 1 is necessary, as `m_nIndex = -1 (aka size_type::max)`
    // may be used as end (past-the-last) element
    constexpr bool operator<(const_reverse_iterator const & r) const noexcept
    {
        return m_nIndex + 1 > r.m_nIndex + 1;
    }
    constexpr bool operator<=(const_reverse_iterator const & r) const noexcept
    {
        return m_nIndex + 1 >= r.m_nIndex + 1;
    }
    constexpr bool operator>(const_reverse_iterator const & r) const noexcept
    {
        return m_nIndex + 1 < r.m_nIndex + 1;
    }
    constexpr bool operator>=(const_reverse_iterator const & r) const noexcept
    {
        return m_nIndex + 1 <= r.m_nIndex + 1;
    }
    constexpr bool operator!=(const const_reverse_iterator & r) const noexcept
    {
        return m_nIndex + 1 != r.m_nIndex + 1;
    }
    constexpr bool operator==(const const_reverse_iterator & r) const noexcept
    {
        return m_nIndex + 1 == r.m_nIndex + 1;
    }
    constexpr operator const void*(void) const noexcept
    {
        return &(*m_pCollection).at(m_nIndex);
    }

private:

    size_type   m_nIndex        = 0u;
    const C*    m_pCollection   = nullptr;
};

}
