//============================================================================
//
//!\file                     continuous_vector.h
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        17.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <qx/other/useful_funcs.h>

template<class T>
class vector2d
{
public:

    class row
    {
        row()           = delete;
        row(const row&) = delete;
        row(row&&)      = delete;

    public:
        T&       operator[] (size_t x)          { return *(&m_First + x); }
        const T& operator[] (size_t x) const    { return *(&m_First + x); }

    private:
        T m_First;
    };

public:

                vector2d    (void) { };
                vector2d    (vector2d&&         other) noexcept { assign(std::move(other);      }
                vector2d    (const vector2d&    other)          { assign(other);                }
                vector2d    (size_t             rows, 
                             size_t             cols,
                             const T          * pData = nullptr){ assign(rows, cols, pData);    }
                vector2d    (size_t             rows, 
                             size_t             cols,
                             const T          & data)           { assign(rows, cols, data);     }

                ~vector2d   (void)                              { clear();                      }

    void        assign      (vector2d&&         other) noexcept;
    void        assign      (const vector2d&    other);
    void        assign      (size_t             rows,
                             size_t             cols,
                             const T          * pData = nullptr);
    void        assign      (size_t             rows,
                             size_t             cols,
                             const T          & data);


    bool        resize      (size_t             rows, 
                             size_t             cols);
    void        fill        (const T&           elem);
    row&        operator[]  (size_t             nRow);
    const row&  operator[]  (size_t             nRow) const;
    const T&    get         (size_t             nRow,
                             size_t             nCol) const;

    void        clear       (void);
    void        set         (size_t             nRow,
                             size_t             nCol,
                             const T          & data);

    size_t      cols        (void) const { return m_nCols;              }
    size_t      rows        (void) const { return m_nRows;              }
    size_t      size_x      (void) const { return rows();               }
    size_t      size_y      (void) const { return cols();               }
    size_t      size        (void) const { return size_x() * size_y();  }
    bool        empty       (void) const { return size() == 0;          }

private:

    T*      m_pData     = nullptr;
    size_t  m_nRows     = 0;
    size_t  m_nCols     = 0;
};

#if 1
#include <vector>

void test_vector2d()
{
    vector2d<int> v1;
    v1.resize(5, 2);
    v1.fill(3);

    for (size_t i = 0; i < v1.size_x(); i++)
    {
        for (size_t j = 0; j < v1.size_y(); j++)
        {
            printf("%d ", v1[i][j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < v1.size_x(); i++)
    {
        for (size_t j = 0; j < v1.size_y(); j++)
        {
            v1[i][j] = i * j;
            printf("%d ", v1[i][j]);
        }
        printf("\n");
    }
}

#include <qx/containers/continuous_vector.inl>

#endif