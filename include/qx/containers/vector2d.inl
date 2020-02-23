//============================================================================
//
//!\file                        vector2d.inl
//
//!\brief       Contains vector2d class class
//!\details     ~
//
//!\author      Khrapov
//!\date        17.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================

namespace qx
{

//============================================================================
//!\fn                       vector2d<T>::assign
//
//!\brief  Assign by moving other vector
//!\param  other - other vector
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::assign(vector2d&& other) noexcept
{
    std::swap(m_pData, other.m_pData);
    std::swap(m_nRows, other.m_nRows);
    std::swap(m_nCols, other.m_nCols);
    std::swap(m_nAllocatedSize, other.m_nAllocatedSize);
}

//============================================================================
//!\fn                       vector2d<T>::assign
//
//!\brief  Assign by copying another vector
//!\param  other - another vector
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::assign(const vector2d& other)
{
    assign(other.rows(), other.cols(), other.m_pData);
}

//============================================================================
//!\fn                         vector2d<T>::assign
//
//!\brief   Assign by size and data pointer
//!\details Data is being copyed from pData with size rows * cols
//!\param   rows  - num of rows in new vector
//!\param   cols  - num of cols in new vector
//!\param   pData - data to copy, may be nullptr
//!\author  Khrapov
//!\date    19.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::assign(size_type rows, size_type cols, const_pointer pData)
{
    if (resize(rows, cols) && pData)
        std::memcpy(m_pData, pData, rows * cols * sizeof(T));
}

//============================================================================
//!\fn                       vector2d<T>::assign
//
//!\brief  Assign by size and fill element
//!\param  rows - num of rows in new vector
//!\param  cols - num of cols in new vector
//!\param  data - element to fill in every vector cell
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::assign(size_type rows, size_type cols, const_reference data)
{
    if (resize(rows, cols))
        fill(data);
}

//============================================================================
//!\fn                       vector2d<T>::resize
//
//!\brief   Resize vector
//!\details If new size is bigger, new elements are not constructed
//          If new size is smalled, truncated elements are destructed
//          If ols cols != new cols, elements are moving from one col to another
//!\param   rows - num of rows in new vector
//!\param   cols - num of cols in new vector
//!\retval       - true if resized successfully
//!\author  Khrapov
//!\date    19.02.2020
//============================================================================
template<class T>
inline bool vector2d<T>::resize(size_type rows, size_type cols)
{
    bool bRet = false;

    if (rows > 0 && cols > 0)
    {
        size_type nBytesRequired = rows * cols * sizeof(T);

        if (nBytesRequired > m_nAllocatedSize)
        {
            void* pMem = std::realloc(m_pData, nBytesRequired);

            if (pMem)
            {
                m_pData = static_cast<T*>(pMem);
                m_nAllocatedSize = nBytesRequired;
                bRet = true;
            }
        }
        else
            bRet = true;

        if (bRet)
        {
            clear_elements(iterator(this, rows * cols), 
                           iterator(this, m_nRows * m_nCols));

            m_nRows = rows;
            m_nCols = cols;
        }
    }

    return bRet;
}

//============================================================================
//!\fn                        vector2d<T>::free
//
//!\brief  Clear string and free memory
//!\author Khrapov
//!\date   21.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::free(void)
{
    clear(); 
    std::free(m_pData);
}

//============================================================================
//!\fn                        vector2d<T>::fill
//
//!\brief  Fill vector with element
//!\param  elem - element for filling
//!\todo   optimize. for some reason vector<vector> is 3 times better
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::fill(const_reference elem) noexcept
{
    std::fill(begin(), end(), elem);
}

//============================================================================
//!\fn                     vector2d<T>::operator[]
//
//!\brief  Get row
//!\param  nRow - row number
//!\retval      - row
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline typename vector2d<T>::pointer vector2d<T>::operator[](size_type nRow) noexcept
{
    return m_pData + nRow * m_nCols;
}

//============================================================================
//!\fn                     vector2d<T>::operator[]
//
//!\brief  Get row
//!\param  nRow - row number
//!\retval      - const row
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline typename vector2d<T>::const_pointer vector2d<T>::operator[](size_type nRow) const noexcept
{
    return m_pData + nRow * m_nCols;
}

//============================================================================
//!\fn                         vector2d<T>::get
//
//!\brief  Get element
//!\param  nRow - row number
//!\param  nCol - col number
//!\retval      - element
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline const T& vector2d<T>::get(size_type nRow, size_type nCol) const noexcept
{
    return (*this)[nRow][nCol];
}

//============================================================================
//!\fn                        vector2d<T>::clear
//
//!\brief  Clear vector (do not free memory)
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::clear(void)
{
    if (m_pData)
        clear_elements(begin(), end());

    m_nRows = 0;
    m_nCols = 0;
}

//============================================================================
//!\fn                         vector2d<T>::set
//
//!\brief  Set elemtnt
//!\param  nRow - row number
//!\param  nCol - col number
//!\param  data - element
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::set(size_type nRow, size_type nCol, const_reference data) noexcept
{
    (*this)[nRow][nCol] = data;
}

//============================================================================
//!\fn                         vector2d<T>::at
//
//!\brief  Get element at ind pos
//!\param  ind - pos
//!\retval     - element
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline typename vector2d<T>::reference vector2d<T>::at(size_type ind)
{ 
    return m_pData[ind]; 
}

//============================================================================
//!\fn                        vector2d<T>::size
//
//!\brief  Get number of elements in whole vector2d
//!\retval  - num of elements (cols * rows)
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline typename vector2d<T>::size_type vector2d<T>::size(void) const
{ 
    return size_x() * size_y(); 
}

//============================================================================
//!\fn                        vector2d<T>::data
//
//!\brief  Get first element pointer
//!\retval  - first element pointer
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline typename vector2d<T>::pointer vector2d<T>::data()
{
    return m_pData;
}
template<class T>
inline typename vector2d<T>::const_pointer vector2d<T>::data() const
{
    return m_pData;
}

//============================================================================
//!\fn                   vector2d<T>::clear_elements
//
//!\brief  Destruct elements
//!\param  start - start element iterator
//!\param  end   - end element iterator
//!\author Khrapov
//!\date   21.02.2020
//============================================================================
template<class T>
inline void vector2d<T>::clear_elements(iterator start, iterator end)
{
    if constexpr (!std::is_fundamental<T>::value)
    {
        for (auto it = start; it < end; ++it)
            static_cast<value_type>((*it)).~T();
    }
}

}
