/**

    @file      triangular_vector.inl
    @brief     Contains qx::triangular_vector class implementation
    @author    Khrapov
    @date      23.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class T>
inline triangular_vector<T>::triangular_vector(
    triangular_vector&& other) noexcept
{
    assign(std::move(other));
}

template<class T>
inline triangular_vector<T>::triangular_vector(const triangular_vector& other)
{
    assign(other);
}

template<class T>
inline triangular_vector<T>::triangular_vector(size_type nSideSize)
{
    resize(nSideSize);
}

template<class T>
inline triangular_vector<T>::triangular_vector(
    size_type       nSideSize,
    const_reference data)
{
    assign(nSideSize, data);
}

template<class T>
inline triangular_vector<T>::~triangular_vector(void)
{
    free();
}

template<class T>
inline const typename triangular_vector<T>::triangular_vector&
    triangular_vector<T>::operator=(triangular_vector&& other) noexcept
{
    assign(std::move(other));
    return *this;
}

template<class T>
inline const typename triangular_vector<T>::triangular_vector&
    triangular_vector<T>::operator=(const triangular_vector& other)
{
    assign(other);
    return *this;
}

template<class T>
inline void triangular_vector<T>::assign(triangular_vector&& other) noexcept
{
    std::swap(m_pData, other.m_pData);
    std::swap(m_nSideSize, other.m_nSideSize);
    std::swap(m_nSize, other.m_nSize);
    std::swap(m_nAllocatedSize, other.m_nAllocatedSize);
}

template<class T>
inline void triangular_vector<T>::assign(const triangular_vector& other)
{
    if (other.m_pData != m_pData && resize(other.size_side()))
        std::memcpy(m_pData, other.m_pData, size() * sizeof(T));
}

template<class T>
inline void triangular_vector<T>::assign(
    size_type       nSideSize,
    const_reference data)
{
    resize(nSideSize, data);
}

template<class T>
inline bool triangular_vector<T>::reserve(size_type nSideSize)
{
    bool bRet = false;

    const size_type nNewElements = _get_vector_size(nSideSize);
    if (nNewElements > m_nAllocatedSize)
    {
        if (void* pMem = std::realloc(m_pData, nNewElements * sizeof(T)))
        {
            m_pData          = static_cast<T*>(pMem);
            m_nAllocatedSize = nNewElements;
            bRet             = true;
        }
    }
    else
        bRet = true;

    return bRet;
}

template<class T>
inline bool triangular_vector<T>::resize(size_type nSideSize)
{
    bool bRet = false;

    if (nSideSize > 0 && reserve(nSideSize))
    {
        auto itFirst = iterator(this, m_nSize);

        m_nSideSize = nSideSize;
        m_nSize     = _get_vector_size(nSideSize);

        auto itLast = iterator(this, m_nSize);
        destruct(itFirst, itLast);

        bRet = true;
    }

    return bRet;
}

template<class T>
inline bool triangular_vector<T>::resize(
    size_type       nSideSize,
    const_reference data)
{
    bool bRet = resize(nSideSize);

    if (bRet)
        fill(data);

    return bRet;
}

template<class T>
inline void triangular_vector<T>::fill(const_reference data)
{
    value_type temp = data;
    std::fill(begin(), end(), temp);
}

template<class T>
inline typename triangular_vector<T>::const_reference triangular_vector<T>::get(
    size_type nRow,
    size_type nCol) const noexcept
{
    return m_pData[_get_index(nRow, nCol)];
}

template<class T>
inline void triangular_vector<T>::set(
    size_type       nRow,
    size_type       nCol,
    const_reference data) noexcept
{
    m_pData[_get_index(nRow, nCol)] = data;
}

template<class T>
inline typename triangular_vector<T>::size_type triangular_vector<T>::size_side(
    void) const noexcept
{
    return m_nSideSize;
}

template<class T>
inline typename triangular_vector<T>::size_type triangular_vector<T>::capacity(
    void) const noexcept
{
    return m_nAllocatedSize;
}

template<class T>
inline void triangular_vector<T>::free(void)
{
    clear();
    std::free(m_pData);
    m_pData          = nullptr;
    m_nAllocatedSize = 0;
}

template<class T>
inline typename triangular_vector<T>::size_type triangular_vector<
    T>::_get_index(size_type nRow, size_type nCol) noexcept
{
    if (nRow >= nCol)
        return (nRow * nRow + nRow) / 2 + nCol;
    else
        return (nCol * nCol + nCol) / 2 + nRow;
}

template<class T>
inline typename triangular_vector<T>::size_type triangular_vector<
    T>::_get_vector_size(size_type nSideSize) noexcept
{
    return (nSideSize * nSideSize + nSideSize) / 2;
}

/**
    @brief  Get triangular vector size
    @retval - number of elements in triangular vector (without duplication)
**/
template<class T>
inline typename triangular_vector<T>::size_type triangular_vector<T>::size(
    void) const noexcept
{
    return m_nSize;
}

/**
    @brief  Get raw data pointer
    @retval - data pointer
**/
template<class T>
inline typename triangular_vector<T>::pointer triangular_vector<T>::data(
    void) noexcept
{
    return m_pData;
}

/**
    @brief  Get element in continuous vector at index
    @param  nIndex - continuous vector index
    @retval        - value
**/
template<class T>
inline typename triangular_vector<T>::reference triangular_vector<T>::at(
    size_type nIndex) noexcept
{
    return m_pData[nIndex];
}

/**
    @brief Clear triangular vector
**/
template<class T>
inline void triangular_vector<T>::clear(void) noexcept
{
    if (m_pData)
        destruct(begin(), end());

    m_nSideSize = 0;
    m_nSize     = 0;
}

} // namespace qx
