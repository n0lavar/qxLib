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
#include <qx/containers/container.h>

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

    // help class to provide correct vector2d[][] 
    class row
    {
                    row         (void)          = delete;
                    row         (const row&)    = delete;
                    row         (row&&)         = delete;

        const row&  operator=   (const row&)    = delete;
        const row&  operator=   (row&&)         = delete;

    public:
        T&          operator[]  (size_t x)       { return *(&m_First + x); }
        const T&    operator[]  (size_t x) const { return *(&m_First + x); }

    private:
        T m_First;
    };

    IMPL_CONTAINER(vector2d)

public:

                    vector2d    (void) { };
                    vector2d    (vector2d&&         other) noexcept { assign(std::move(other));     }
                    vector2d    (const vector2d&    other)          { assign(other);                }
                    vector2d    (size_type          rows,
                                 size_type          cols,
                                 const_pointer      pData = nullptr){ assign(rows, cols, pData);    }
                    vector2d    (size_type          rows,
                                 size_type          cols,
                                 const_reference    data)           { assign(rows, cols, data);     }

                    ~vector2d   (void)                              { clear();                      }

    void            assign      (vector2d&&         other) noexcept;
    void            assign      (const vector2d&    other);
    void            assign      (size_type          rows,
                                 size_type          cols,
                                 const_pointer      pData = nullptr);
    void            assign      (size_type          rows,
                                 size_type          cols,
                                 const_reference    data);

    bool            resize      (size_type          rows, 
                                 size_type          cols);
    bool            resize      (size_type          rows);
    void            fill        (const_reference    elem);
    row&            operator[]  (size_type          nRow);
    const row&      operator[]  (size_type          nRow) const;
    const_reference get         (size_type          nRow,
                                 size_type          nCol) const;

    void            set         (size_type          nRow,
                                 size_type          nCol,
                                 const_reference    data);

    size_type       cols        (void) const { return m_nCols;              }
    size_type       rows        (void) const { return m_nRows;              }
    size_type       size_x      (void) const { return rows();               }
    size_type       size_y      (void) const { return cols();               }

private:

    pointer     m_pData     = nullptr;
    size_type   m_nRows     = 0;
    size_type   m_nCols     = 0;
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
    printf("\n");

    for (size_t i = 0; i < v1.size_x(); i++)
    {
        for (size_t j = 0; j < v1.size_y(); j++)
        {
            v1[i][j] = (int)(i * j);
            printf("%d ", v1[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    v1.at(0);
    v1.data();

    for (auto it = v1.begin(); it != v1.end(); ++it)
    {
        (*it)++;
    }

    for (size_t i = 0; i < v1.size_x(); i++)
    {
        for (size_t j = 0; j < v1.size_y(); j++)
        {
            printf("%d ", v1[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    for (auto& val : v1)
    {
        val *= 2;
    }

    for (size_t i = 0; i < v1.size_x(); i++)
    {
        for (size_t j = 0; j < v1.size_y(); j++)
        {
            printf("%d ", v1[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

#endif

#include <qx/containers/continuous_vector.inl>
