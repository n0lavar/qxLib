/**

    @file      vector2d.h
    @brief     Contains qx::vector2d class
    @author    Khrapov
    @date      17.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/container.h>
#include <qx/useful_funcs.h>

#include <cstring>

namespace qx
{

/**

    @class   vector2d
    @brief   Continuous 2d vector
    @details Stores in memory like one big array and makes container cache friendly
    @tparam  T - value type
    @author  Khrapov
    @date    18.08.2021

**/
template<class T>
class vector2d
{
public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;
    using size_type       = size_t;

    QX_IMPL_CONTAINER(vector2d)

public:
    vector2d() = default;

    /**
        @brief vector2d object constructor
        @param other - other vector rvalue ref
    **/
    vector2d(vector2d&& other) noexcept;

    /**
        @brief vector2d object constructor
        @param other - other vector
    **/
    vector2d(const vector2d& other);

    /**
        @brief vector2d object constructor
        @param rows  - num of rows in new vector
        @param cols  - num of cols in new vector
        @param pData - data to copy, may be nullptr
    **/
    vector2d(size_type rows, size_type cols, const_pointer pData = nullptr);

    /**
        @brief vector2d object constructor
        @param rows - num of rows in new vector
        @param cols - num of cols in new vector
        @param data - element to fill in every vector cell
    **/
    vector2d(size_type rows, size_type cols, const_reference data);

    /**
        @brief vector2d object destructor
    **/
    ~vector2d();

    /**
        @brief  operator=
        @param  other - other vector rvalue ref
        @retval       - this object reference
    **/
    const vector2d& operator=(vector2d&& other) noexcept;

    /**
        @brief  operator=
        @param  other - another vector
        @retval       - this object reference
    **/
    const vector2d& operator=(const vector2d& other);

    /**
        @brief Assign by moving from other vector
        @param other - other vector rvalue ref
    **/
    void assign(vector2d&& other) noexcept;

    /**
        @brief Assign by copying another vector
        @param other - another vector
    **/
    void assign(const vector2d& other);

    /**
        @brief   Assign by size and data pointer
        @details Data is being copied from pData with size rows * cols
        @param   rows  - num of rows in new vector
        @param   cols  - num of cols in new vector 
        @param   pData - data to copy, may be nullptr 
    **/
    void assign(size_type rows, size_type cols, const_pointer pData = nullptr);

    /**
        @brief Assign by size and fill element
        @param rows - num of rows in new vector
        @param cols - num of cols in new vector
        @param data - element to fill in every vector cell
    **/
    void assign(size_type rows, size_type cols, const_reference data);

    /**
        @brief  Reserve vector size
        @param  nElements - num elements
        @retval           - true if reserved successfully
    **/
    bool reserve(size_type nElements);

    /**
        @brief  Resize vector
        @param  rows - num of rows
        @param  cols - num of cols
        @retval      - true if resized successfully
    **/
    bool resize(size_type rows, size_type cols);

    /**
        @brief   Resize vector
        @details If new size is bigger, new elements are not constructed
                 If new size is smaller, truncated elements are destructed
                 If ols cols != new cols, elements are moving from one col to another
        @param   rows - num of rows in new vector
        @param   cols - num of cols in new vector
        @param   data - data to fill
        @retval       - true if resized successfully
    **/
    bool resize(size_type rows, size_type cols, const_reference data);

    /**
        @brief Clear vector and free memory
    **/
    void free();

    /**
        @brief Fill vector with element
        @param elem - element for filling
    **/
    void fill(const_reference elem);

    /**
        @brief  operator[]
        @param  nRow - row number
        @retval      - row
    **/
    pointer operator[](size_type nRow) noexcept;

    /**
        @brief  operator[]
        @param  nRow - row number
        @retval      - row
    **/
    const_pointer operator[](size_type nRow) const noexcept;

    /**
        @brief  Get element
        @param  nRow - row number
        @param  nCol - col number
        @retval      - element
    **/
    const_reference get(size_type nRow, size_type nCol) const noexcept;

    /**
        @brief Set element
        @param nRow - row number
        @param nCol - col number
        @param data - element
    **/
    void set(size_type nRow, size_type nCol, const_reference data) noexcept;

    /**
        @brief  Get num of rows in vector
        @retval - num of rows in vector
    **/
    size_type rows() const noexcept;

    /**
        @brief  Get num of cols in vector
        @retval - num of cols in vector
    **/
    size_type cols() const noexcept;

    /**
        @brief  Get num of rows in vector
        @retval - num of rows in vector
    **/
    size_type size_x() const noexcept;

    /**
        @brief  Get num of cols in vector
        @retval - num of cols in vector
    **/
    size_type size_y() const noexcept;

    /**
        @brief  Get allocated size
        @retval - allocated size
    **/
    size_type capacity() const noexcept;

private:
    pointer   m_pData          = nullptr;
    size_type m_nRows          = 0;
    size_type m_nCols          = 0;
    size_type m_nAllocatedSize = 0;
};

} // namespace qx

#include <qx/containers/vector2d.inl>
