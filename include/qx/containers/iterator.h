//============================================================================
//
//!\file                         iterator.h
//
//!\brief       Contains iterator class
//!\details     ~
//
//!\author      Khrapov
//!\date        27.07.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <xutility>

namespace qx
{

//============================================================================
//
//!\class                     iterator<C>
//
//!\brief   Iterator type
//!\details Use it for range-based loops and std algorithms
//          C have to provide at(size_t)
//
//!\author  Khrapov
//!\date    27.07.2019
//
//============================================================================
template <class C>
class iterator
{
public:

    using value_type        = typename C::value_type;
    using pointer           = typename C::pointer;
    using reference         = typename C::reference;
    using difference_type   = typename C::difference_type;
    using size_type         = typename C::size_type;
    using iterator_category = typename std::forward_iterator_tag;

public:
                    iterator   (void) = default;
                    iterator   (C* c, size_type i) : m_pCollection(c), m_nIndex(i) { }

    // Default Copy/Move are fine.
    // Default Destructor is fine.

    reference       operator*   (void)                          { return (*m_pCollection).at(m_nIndex);     }
    const reference operator*   (void)                  const   { return (*m_pCollection).at(m_nIndex);     }
    pointer         operator->  (void)                          { return &((*m_pCollection).at(m_nIndex));  }
    const pointer   operator->  (void)                  const   { return &((*m_pCollection).at(m_nIndex));  }
    reference       operator[]  (size_type m)                   { return (*m_pCollection).at(m_nIndex + m); }
    const reference operator[]  (size_type m)           const   { return (*m_pCollection).at(m_nIndex + m); }


    iterator      & operator++  (void)                          { ++m_nIndex; return *this;                 }
    iterator      & operator--  (void)                          { --m_nIndex; return *this;                 }
    iterator        operator++  (int)                           { iterator r(*this); ++m_nIndex; return r;  }
    iterator        operator--  (int)                           { iterator r(*this); --m_nIndex; return r;  }
                  
    iterator      & operator+=  (size_type n)                   { m_nIndex += n; return *this;              }
    iterator      & operator-=  (size_type n)                   { m_nIndex -= n; return *this;              }
                  
    iterator        operator+   (size_type n)           const   { iterator r(*this); return r += n;         }
    iterator        operator-   (size_type n)           const   { iterator r(*this); return r -= n;         }

    difference_type operator-   (iterator  const& r)    const   { return m_nIndex - r.m_nIndex;             }

    // Note: comparing iterator from different containers
    //       is undefined behavior so we don't need to check
    //       if they are the same container.
    bool            operator<   (iterator const & r)    const   { return m_nIndex <  r.m_nIndex;            }
    bool            operator<=  (iterator const & r)    const   { return m_nIndex <= r.m_nIndex;            }
    bool            operator>   (iterator const & r)    const   { return m_nIndex >  r.m_nIndex;            }
    bool            operator>=  (iterator const & r)    const   { return m_nIndex >= r.m_nIndex;            }
    bool            operator!=  (const iterator & r)    const   { return m_nIndex != r.m_nIndex;            }
    bool            operator==  (const iterator & r)    const   { return m_nIndex == r.m_nIndex;            }

    operator void*              (void)                          { return &(m_pCollection.at(m_nIndex));     }

private:
    size_type       m_nIndex        = 0u;
    C             * m_pCollection   = nullptr;
};

}
