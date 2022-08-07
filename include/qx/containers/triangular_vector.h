/**

    @file      triangular_vector.h
    @brief     Contains qx::triangular_vector class
    @author    Khrapov
    @date      23.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/container.h>
#include <qx/containers/utils.h>

#include <cstring>

namespace qx
{

/**

    @class   triangular_vector
    @brief   Triangular vector class
    @details Only elements with nRow >= nCols are stored
             data storage example:
                 x 0 0 0     vec[r][c] = r >= c => vec[r][c]
                 x x 0 0                 r < c  => vec[c][r]
                 x x x 0
                 x x x x
    @tparam  T - value type
    @author  Khrapov
    @date    23.02.2020

**/
template<class T>
class triangular_vector
{
public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;
    using size_type       = size_t;

    QX_IMPL_CONTAINER(triangular_vector)

public:
    triangular_vector() = default;

    /**
        @brief triangular_vector object constructor
        @param other - triangular_vector rvalue ref
    **/
    triangular_vector(triangular_vector&& other) noexcept;

    /**
        @brief triangular_vector object constructor
        @param other - other triangular_vector
    **/
    triangular_vector(const triangular_vector& other);

    /**
        @brief triangular_vector object constructor
        @param nSideSize - matrix side size
    **/
    triangular_vector(size_type nSideSize);

    /**
        @brief triangular_vector object constructor
        @param nSideSize - matrix side size
        @param data      - data to fill
    **/
    triangular_vector(size_type nSideSize, const_reference data);

    /**
        @brief triangular_vector object destructor
    **/
    ~triangular_vector();

    /**
        @brief  operator=
        @param  other - triangular_vector rvalue ref
        @retval       - this object reference
    **/
    const triangular_vector& operator=(triangular_vector&& other) noexcept;

    /**
        @brief  operator=
        @param  other - other triangular_vector
        @retval       - this object reference
    **/
    const triangular_vector& operator=(const triangular_vector& other);

    /**
        @brief Assigns new contents to the vector, moving from other vector
        @param other - triangular_vector rvalue ref
    **/
    void assign(triangular_vector&& other) noexcept;

    /**
        @brief Assigns new contents to the vector, copying from other vector
        @param other - other triangular_vector
    **/
    void assign(const triangular_vector& other);

    /**
        @brief Assigns new contents to the vector, creating new vector with size size and filling value
        @param nSideSize - matrix side size
        @param data      - data to fill
    **/
    void assign(size_type nSideSize, const_reference data);

    /**
        @brief  Reserve memory for vector
        @param  nSideSize - new matrix side size
        @retval           - true if reserved
    **/
    bool reserve(size_type nSideSize);

    /**
        @brief  Resize triangular vector without filling with new value
        @param  nSideSize - new matrix side size
        @retval           - true if resized
    **/
    bool resize(size_type nSideSize);

    /**
        @brief  Resize triangular vector with filling with new value
        @param  nSideSize - new matrix side size
        @param  data      - data to fill
        @retval           - true if resized
    **/
    bool resize(size_type nSideSize, const_reference data);

    /**
        @brief Fill vector with value
        @param data - value to fill
    **/
    void fill(const_reference data);

    /**
        @brief  Get value on position
        @param  nRow - row num
        @param  nCol - column num
        @retval      - vector value
    **/
    const_reference get(size_type nRow, size_type nCol) const noexcept;

    /**
        @brief Set value on position
        @param nRow - row num 
        @param nCol - column num 
        @param data - value to set 
    **/
    void set(size_type nRow, size_type nCol, const_reference data) noexcept;

    /**
        @brief  Get matrix side size
        @retval - matrix side size
    **/
    size_type size_side() const noexcept;

    /**
        @brief  Get capacity
        @retval - capacity
    **/
    size_type capacity() const noexcept;

    /**
        @brief Clear vector and free memory
    **/
    void free();

private:
    /**
        @brief  Convert row and column numbers to continuous vector index
        @param  nRow - row number
        @param  nCol - column number
        @retval      - continuous vector index
    **/
    static size_type _get_index(size_type nRow, size_type nCol) noexcept;

    /**
        @brief  Get continuous vector size
        @param  nSideSize - matrix side size
        @retval           - continuous vector size
    **/
    static size_type _get_vector_size(size_type nSideSize) noexcept;

private:
    pointer   m_pData          = nullptr;
    size_type m_nSideSize      = 0;
    size_type m_nSize          = 0;
    size_type m_nAllocatedSize = 0;
};

} // namespace qx

#include <qx/containers/triangular_vector.inl>
