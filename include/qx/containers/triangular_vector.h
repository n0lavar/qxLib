//==============================================================================
//
//!\file                      triangular_vector.h
//
//!\brief       Contains triangular_vector class
//!\details     ~
//
//!\author      Khrapov
//!\date        23.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <cstring>

#include <qx/containers/container.h>
#include <qx/other/useful_funcs.h>

namespace qx
{

//==============================================================================
//
//!\class                    triangular_vector<T>
//
//!\brief   Triangular vector class. Only elements with nRow >= nCols are stored.
//!\details data storage example:
//              x 0 0 0     vec[r][c] = r >= c => vec[r][c]
//              x x 0 0                 r < c  => vec[c][r]
//              x x x 0
//              x x x x
//
//!\author  Khrapov
//!\date    23.02.2020
//
//==============================================================================
template<class T>
class triangular_vector //-V690 bug: PVS can't see "using this_type = triangular_vector"
{
public:

    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;
    using this_type         = triangular_vector;

    IMPL_CONTAINER(triangular_vector)

public:

                        triangular_vector   (void) = default;
                        triangular_vector   (this_type&&        other) noexcept     { assign(std::move(other));                 }
                        triangular_vector   (const this_type&   other)              { assign(other);                            }
                        triangular_vector   (size_type          nSideSize)          { resize(nSideSize);                        }
                        triangular_vector   (size_type          nSideSize, 
                                             const_reference    data)               { assign(nSideSize, data);                  }

                        ~triangular_vector  (void)                                  { free();                                   }

    const this_type&    operator=           (this_type&&        other) noexcept     { assign(std::move(other)); return *this;   }
    const this_type&    operator=           (const this_type&   other)              { assign(other);            return *this;   }

    void                assign              (this_type&&        other)          noexcept;
    void                assign              (const this_type&   other);
    void                assign              (size_type          nSideSize, 
                                             const_reference    data);

    bool                reserve             (size_type          nSideSize);
    bool                resize              (size_type          nSideSize);
    bool                resize              (size_type          nSideSize,
                                             const_reference    data);

    void                fill                (const_reference    data);
    const_reference     get                 (size_type          nRow,
                                             size_type          nCol)   const   noexcept;

    void                set                 (size_type          nRow,
                                             size_type          nCol,
                                             const_reference    data)           noexcept;

    size_type           size_side           (void)                      const   noexcept { return m_nSideSize;      }
    size_type           capacity            (void)                      const   noexcept { return m_nAllocatedSize; }
    void                free                (void);

private:

    size_type           getIndex            (size_type          nRow,
                                             size_type          nCol)   const   noexcept;
    size_type           getVectorSize       (size_type          nSideSize) const noexcept;

private:

    pointer     m_pData             = nullptr;
    size_type   m_nSideSize         = 0;
    size_type   m_nSize             = 0;
    size_type   m_nAllocatedSize    = 0;
};

}

#include <qx/containers/triangular_vector.inl>
