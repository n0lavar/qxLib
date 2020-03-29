//============================================================================
//
//!\file                           vector2d.h
//
//!\brief       Contains vector2d class
//!\details     ~
//
//!\author      Khrapov
//!\date        17.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <cstring>

#include <qx/containers/container.h>
#include <qx/other/useful_funcs.h>

namespace qx
{

//============================================================================
//
//!\class                        vector2d<T>
//
//!\brief   Continuous 2d vector
//!\details Stores in memory like one big array and makes container cache friendly
//
//!\author  Khrapov
//!\date    21.02.2020
//
//============================================================================
template<class T>
class vector2d
{
public:

    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;

    IMPL_CONTAINER(vector2d)

public:

                    vector2d    (void) = default;
                    vector2d    (vector2d&&         other) noexcept { assign(std::move(other));     }
                    vector2d    (const vector2d&    other)          { assign(other);                }
                    vector2d    (size_type          rows,
                                 size_type          cols,
                                 const_pointer      pData = nullptr){ assign(rows, cols, pData);    }
                    vector2d    (size_type          rows,
                                 size_type          cols,
                                 const_reference    data)           { assign(rows, cols, data);     }

                    ~vector2d   (void)                              { free();                       }

    const vector2d& operator=   (vector2d&&         other) noexcept { assign(std::move(other)); return *this; }
    const vector2d& operator=   (const vector2d&    other)          { assign(other); return *this;  }

    void            assign      (vector2d&&         other) noexcept;
    void            assign      (const vector2d&    other);
    void            assign      (size_type          rows,
                                 size_type          cols,
                                 const_pointer      pData = nullptr);
    void            assign      (size_type          rows,
                                 size_type          cols,
                                 const_reference    data);

    bool            reserve     (size_type          nElements);
    bool            resize      (size_type          rows,
                                 size_type          cols);
    bool            resize      (size_type          rows, 
                                 size_type          cols,
                                 const_reference    data);
    void            fill        (const_reference    elem);
    pointer         operator[]  (size_type          nRow)       noexcept;
    const_pointer   operator[]  (size_type          nRow) const noexcept;
    const_reference get         (size_type          nRow,
                                 size_type          nCol) const noexcept;

    void            set         (size_type          nRow,
                                 size_type          nCol,
                                 const_reference    data)       noexcept;

    size_type       rows        (void) const noexcept { return m_nRows;             }
    size_type       cols        (void) const noexcept { return m_nCols;             }
    size_type       size_x      (void) const noexcept { return m_nRows;             }
    size_type       size_y      (void) const noexcept { return m_nCols;             }
    size_type       capacity    (void) const noexcept { return m_nAllocatedSize;    }

private:

    void            free        (void);

private:

    pointer     m_pData             = nullptr;
    size_type   m_nRows             = 0;
    size_type   m_nCols             = 0;
    size_type   m_nAllocatedSize    = 0;
};

}

#include <qx/containers/vector2d.inl>
