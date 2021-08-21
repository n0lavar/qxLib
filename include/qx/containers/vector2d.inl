/**

    @file      vector2d.inl
    @author    Khrapov
    @date      17.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class T>
inline vector2d<T>::vector2d(vector2d&& other) noexcept
{
    assign(std::move(other));
}

template<class T>
inline vector2d<T>::vector2d(const vector2d& other)
{
    assign(other);
}

template<class T>
inline vector2d<T>::vector2d(
    size_type     rows,
    size_type     cols,
    const_pointer pData)
{
    assign(rows, cols, pData);
}

template<class T>
inline vector2d<T>::vector2d(
    size_type       rows,
    size_type       cols,
    const_reference data)
{
    assign(rows, cols, data);
}

template<class T>
inline vector2d<T>::~vector2d(void)
{
    free();
}

template<class T>
inline const typename vector2d<T>::vector2d& vector2d<T>::operator=(
    vector2d&& other) noexcept
{
    assign(std::move(other));
    return *this;
}

template<class T>
inline const typename vector2d<T>::vector2d& vector2d<T>::operator=(
    const vector2d& other)
{
    assign(other);
    return *this;
}

template<class T>
inline void vector2d<T>::assign(vector2d&& other) noexcept
{
    std::swap(m_pData, other.m_pData);
    std::swap(m_nRows, other.m_nRows);
    std::swap(m_nCols, other.m_nCols);
    std::swap(m_nAllocatedSize, other.m_nAllocatedSize);
}

template<class T>
inline void vector2d<T>::assign(const vector2d& other)
{
    if (other.m_pData != m_pData)
        assign(other.rows(), other.cols(), other.m_pData);
}

template<class T>
inline void vector2d<T>::assign(
    size_type     rows,
    size_type     cols,
    const_pointer pData)
{
    if (resize(rows, cols) && pData)
        std::memcpy(m_pData, pData, rows * cols * sizeof(T));
}

template<class T>
inline void vector2d<T>::assign(
    size_type       rows,
    size_type       cols,
    const_reference data)
{
    if (resize(rows, cols))
        fill(data);
}

template<class T>
inline bool vector2d<T>::reserve(size_type nElements)
{
    bool bRet = false;

    if (nElements > m_nAllocatedSize)
    {
        if (void* pMem = std::realloc(m_pData, nElements * sizeof(T)))
        {
            m_pData          = static_cast<T*>(pMem);
            m_nAllocatedSize = nElements;
            bRet             = true;
        }
    }

    return bRet;
}

template<class T>
inline bool vector2d<T>::resize(size_type rows, size_type cols)
{
    bool bRet = false;

    if (rows > 0 && cols > 0)
    {
        const size_type nSizeRequired = rows * cols;

        if (nSizeRequired > m_nAllocatedSize)
            bRet = reserve(nSizeRequired);
        else
            bRet = true;

        if (bRet)
        {
            auto itFirst = iterator(this, rows * cols);
            auto itLast  = iterator(this, m_nRows * m_nCols);
            destruct(itFirst, itLast);

            m_nRows = rows;
            m_nCols = cols;
        }
    }

    return bRet;
}

template<class T>
inline bool vector2d<T>::resize(
    size_type       rows,
    size_type       cols,
    const_reference data)
{
    const bool bRet = resize(rows, cols);

    if (bRet)
        fill(data);

    return bRet;
}

template<class T>
inline void vector2d<T>::free(void)
{
    clear();
    std::free(m_pData);
    m_pData          = nullptr;
    m_nAllocatedSize = 0;
}

template<class T>
inline void vector2d<T>::fill(const_reference elem)
{
    value_type temp = elem;
    std::fill(begin(), end(), temp);
}

template<class T>
inline typename vector2d<T>::pointer vector2d<T>::operator[](
    size_type nRow) noexcept
{
    return m_pData + nRow * m_nCols;
}

template<class T>
inline typename vector2d<T>::const_pointer vector2d<T>::operator[](
    size_type nRow) const noexcept
{
    return m_pData + nRow * m_nCols;
}

template<class T>
inline const T& vector2d<T>::get(size_type nRow, size_type nCol) const noexcept
{
    return (*this)[nRow][nCol];
}

template<class T>
inline void vector2d<T>::set(
    size_type       nRow,
    size_type       nCol,
    const_reference data) noexcept
{
    (*this)[nRow][nCol] = data;
}

template<class T>
inline typename vector2d<T>::size_type vector2d<T>::rows(void) const noexcept
{
    return m_nRows;
}

template<class T>
inline typename vector2d<T>::size_type vector2d<T>::cols(void) const noexcept
{
    return m_nCols;
}

template<class T>
inline typename vector2d<T>::size_type vector2d<T>::size_x(void) const noexcept
{
    return m_nRows;
}

template<class T>
inline typename vector2d<T>::size_type vector2d<T>::size_y(void) const noexcept
{
    return m_nCols;
}

template<class T>
inline typename vector2d<T>::size_type vector2d<T>::capacity(
    void) const noexcept
{
    return m_nAllocatedSize;
}

/**
    @brief  Get number of elements in whole vector2d
    @retval - num of elements (cols * rows)
**/
template<class T>
inline typename vector2d<T>::size_type vector2d<T>::size(void) const noexcept
{
    return size_x() * size_y();
}

/**
    @brief  Get first element pointer
    @retval - first element pointer
**/
template<class T>
inline typename vector2d<T>::pointer vector2d<T>::data(void) noexcept
{
    return m_pData;
}

/**
    @brief  Get element at nIndex pos
    @param  nIndex - continuous vector index
    @retval        - element
**/
template<class T>
inline typename vector2d<T>::reference vector2d<T>::at(
    size_type nIndex) noexcept
{
    return m_pData[nIndex];
}

/**
    @brief Clear vector (do not free memory)
**/
template<class T>
inline void vector2d<T>::clear(void) noexcept
{
    if (m_pData)
        destruct(begin(), end());

    m_nRows = 0;
    m_nCols = 0;
}

} // namespace qx
