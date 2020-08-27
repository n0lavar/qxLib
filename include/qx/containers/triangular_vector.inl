//==============================================================================
//
//!\file                     triangular_vector.inl
//
//!\brief       Contains triangular_vector class
//!\details     ~
//
//!\author      Khrapov
//!\date        23.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                   triangular_vector<T>::assign
//
//!\brief  Assigns new contents to the vector, moving from other vector
//!\param  other - other vector
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline void triangular_vector<T>::assign(this_type&& other) noexcept
{
    std::swap(m_pData, other.m_pData);
    std::swap(m_nSideSize, other.m_nSideSize);
    std::swap(m_nSize, other.m_nSize);
    std::swap(m_nAllocatedSize, other.m_nAllocatedSize);
}

//==============================================================================
//!\fn                   triangular_vector<T>::assign
//
//!\brief  Assigns new contents to the vector, copying from other vector
//!\param  other - other vector
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline void triangular_vector<T>::assign(const this_type& other)
{
    if (other.m_pData != m_pData && resize(other.size_side()))
        std::memcpy(m_pData, other.m_pData, size() * sizeof(T));
}

//==============================================================================
//!\fn                   triangular_vector<T>::assign
//
//!\brief  Assigns new contents to the vector, creating new vector with size size and filling value
//!\param  nSideSize - triangular vector side size
//!\param  data      - data to fill
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline void triangular_vector<T>::assign(size_type nSideSize, const_reference data)
{
    resize(nSideSize, data);
}

//==============================================================================
//!\fn                  triangular_vector<T>::reserve
//
//!\brief  Reserve memory for vector
//!\param  nSideSize - triangular vector side size
//!\retval           - true if reserved
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline bool triangular_vector<T>::reserve(size_type nSideSize)
{
    bool bRet = false;

    size_type nNewElements = getVectorSize(nSideSize);
    if (nNewElements > m_nAllocatedSize)
    {
        if (void* pMem = std::realloc(m_pData, nNewElements * sizeof(T)))
        {
            m_pData = static_cast<T*>(pMem);
            m_nAllocatedSize = nNewElements;
            bRet = true;
        }
    }
    else
        bRet = true;

    return bRet;
}

//==============================================================================
//!\fn                   triangular_vector<T>::resize
//
//!\brief  Resize triangular vector without filling with new value
//!\param  nSideSize - triangular vector side size
//!\retval           - true if resized
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline bool triangular_vector<T>::resize(size_type nSideSize)
{
    bool bRet = false;

    if (nSideSize > 0 && reserve(nSideSize))
    {
        auto itFirst = iterator(this, m_nSize);

        m_nSideSize = nSideSize;
        m_nSize = getVectorSize(nSideSize);

        auto itLast = iterator(this, m_nSize);
        destruct(itFirst, itLast);

        bRet = true;
    }

    return bRet;
}

//==============================================================================
//!\fn                   triangular_vector<T>::resize
//
//!\brief  Resize triangular vector with filling with new value
//!\param  nSideSize - triangular vector side size
//!\param  data      - value to fill
//!\retval           - true if resized
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline bool triangular_vector<T>::resize(size_type nSideSize, const_reference data)
{
    bool bRet = resize(nSideSize);

    if (bRet)
        fill(data);

    return bRet;
}

//==============================================================================
//!\fn                    triangular_vector<T>::free
//
//!\brief  Clear vector and free memory
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline void triangular_vector<T>::free(void)
{
    clear();
    std::free(m_pData);
    m_pData = nullptr;
    m_nAllocatedSize = 0;
}

//==============================================================================
//!\fn                    triangular_vector<T>::fill
//
//!\brief  Fill vector with value
//!\param  data - value to fill
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline void triangular_vector<T>::fill(const_reference data)
{
    value_type temp = data;
    std::fill(begin(), end(), temp);
}

//==============================================================================
//!\fn                    triangular_vector<T>::get
//
//!\brief  Get value on position
//!\param  nRow - row num
//!\param  nCol - column num
//!\retval      - vector value
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline typename triangular_vector<T>::const_reference triangular_vector<T>::get(size_type nRow, size_type nCol) const noexcept
{
    return m_pData[getIndex(nRow, nCol)];
}

//==============================================================================
//!\fn                    triangular_vector<T>::set
//
//!\brief  Set value on position
//!\param  nRow - row num
//!\param  nCol - column num
//!\param  data - value to set
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline void triangular_vector<T>::set(size_type nRow, size_type nCol, const_reference data) noexcept
{
    m_pData[getIndex(nRow, nCol)] = data;
}

//==============================================================================
//!\fn                  triangular_vector<T>::getIndex
//
//!\brief  Convert row and column numbers to continuous vector index
//!\param  nRow - row number
//!\param  nCol - column number
//!\retval      - continuous vector index
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline typename triangular_vector<T>::size_type triangular_vector<T>::getIndex(size_type nRow, size_type nCol) const noexcept
{
    if (nRow >= nCol)
        return (nRow * nRow + nRow) / 2 + nCol;
    else
        return (nCol * nCol + nCol) / 2 + nRow;
}

//==============================================================================
//!\fn               triangular_vector<T>::getVectorSize
//
//!\brief  Get continuous vector size 
//!\param  nSideSize - triangular vector side size
//!\retval           - continuous vector size
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline typename triangular_vector<T>::size_type triangular_vector<T>::getVectorSize(size_type nSideSize) const noexcept
{
    return (nSideSize * nSideSize + nSideSize) / 2;
}

//==============================================================================
//!\fn                    triangular_vector<T>::size
//
//!\brief  Get triangular vector size
//!\retval  - number of elements in triangular vector (without duplication)
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline typename triangular_vector<T>::size_type triangular_vector<T>::size(void) const
{
    return m_nSize;
}

//==============================================================================
//!\fn                    triangular_vector<T>::data
//
//!\brief  Get raw data pointer
//!\retval  - data pointer
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline typename triangular_vector<T>::pointer triangular_vector<T>::data()
{
    return m_pData;
}

//==============================================================================
//!\fn                     triangular_vector<T>::at
//
//!\brief  Get element in continuous vector at index 
//!\param  ind - continuous vector index
//!\retval     - value
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline typename triangular_vector<T>::reference triangular_vector<T>::at(size_type ind)
{
    return m_pData[ind];
}

//==============================================================================
//!\fn                   triangular_vector<T>::clear
//
//!\brief  Clear triangular vector
//!\author Khrapov
//!\date   1.03.2020
//==============================================================================
template<class T>
inline void triangular_vector<T>::clear(void)
{
    if (m_pData)
        destruct(begin(), end());

    m_nSideSize = 0;
    m_nSize     = 0;
}

}