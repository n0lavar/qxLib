#include "continuous_vector.h"
//============================================================================
//
//!\file                    continuous_vector.inl
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        17.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================

//============================================================================
//!\fn                       vector2d<T>::assign
//
//!\brief  
//!\param  other - 
//!\retval       - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
void vector2d<T>::assign(vector2d&& other) noexcept
{
    std::swap(m_pData, other.m_pData);
    std::swap(m_nRows, other.m_nRows);
    std::swap(m_nCols, other.m_nCols);
}

//============================================================================
//!\fn                       vector2d<T>::assign
//
//!\brief  
//!\param  other - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
void vector2d<T>::assign(const vector2d& other)
{
    assign(other.rows(), other.cols(), other.m_pData);
}

//============================================================================
//!\fn                         vector2d<T>::assign
//
//!\brief  
//!\param  rows  - 
//!\param  cols  - 
//!\param  pData - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
void vector2d<T>::assign(size_type rows, size_type cols, const_pointer pData)
{
    if (resize(rows, cols) && pData)
        memcpy(m_pData, pData, rows * cols);
}

//============================================================================
//!\fn                       vector2d<T>::assign
//
//!\brief  
//!\param  rows - 
//!\param  cols - 
//!\param  data - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
void vector2d<T>::assign(size_type rows, size_type cols, const_reference data)
{
    if (resize(rows, cols))
        fill(data);
}

//============================================================================
//!\fn                       vector2d<T>::resize
//
//!\brief  
//!\param  rows - 
//!\param  cols - 
//!\retval      - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
bool vector2d<T>::resize(size_type rows, size_type cols)
{
    bool bRet = false;

    if (rows > 0 && cols > 0)
    {
        if (cols != m_nCols)
        {
            clear();

            m_pData = new T[rows * cols];
            m_nRows = rows;
            m_nCols = cols;

            bRet = true;
        }
        else
            bRet = resize(rows);
    }

    return bRet;
}

//============================================================================
//!\fn                       vector2d<T>::resize
//
//!\brief  
//!\param  rows - 
//!\retval      - 
//!\author Khrapov
//!\date   20.02.2020
//============================================================================
template<class T>
bool vector2d<T>::resize(size_type rows)
{
    return false;
}

//============================================================================
//!\fn                        vector2d<T>::fill
//
//!\brief  
//!\param  elem - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
void vector2d<T>::fill(const_reference elem)
{
    for (size_type i = 0; i < size_x(); i++)
        for (size_type j = 0; j < size_y(); j++)
            (*this)[i][j] = elem;
}

//============================================================================
//!\fn                     vector2d<T>::operator[]
//
//!\brief  
//!\param  nRow - 
//!\retval      - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
typename vector2d<T>::row& vector2d<T>::operator[](size_type nRow)
{
    size_type nInd = nRow *= m_nCols;
    ASSERT(nInd < m_nRows * m_nCols);
    return *reinterpret_cast<row*>(m_pData + nInd);
}

//============================================================================
//!\fn                     vector2d<T>::operator[]
//
//!\brief  
//!\param  nRow - 
//!\retval      - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
const typename vector2d<T>::row& vector2d<T>::operator[](size_type nRow) const
{
    return operator[](nRow);
}

//============================================================================
//!\fn                         vector2d<T>::get
//
//!\brief  
//!\param  nRow - 
//!\param  nCol - 
//!\retval      - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
const T& vector2d<T>::get(size_type nRow, size_type nCol) const
{
    return (*this)[nRow][nCol];
}

//============================================================================
//!\fn                        vector2d<T>::clear
//
//!\brief  
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
void vector2d<T>::clear(void)
{
    SAFE_DELETE(m_pData);
    m_nRows = 0;
    m_nCols = 0;
}

//============================================================================
//!\fn                         vector2d<T>::set
//
//!\brief  
//!\param  nRow - 
//!\param  nCol - 
//!\param  data - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
void vector2d<T>::set(size_type nRow, size_type nCol, const_reference data)
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
typename vector2d<T>::reference vector2d<T>::at(size_type ind)
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
typename vector2d<T>::size_type vector2d<T>::size(void) const
{ 
    return size_x() * size_y(); 
}

//============================================================================
//!\fn                        vector2d<T>::data
//
//!\brief  
//!\retval  - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
typename vector2d<T>::pointer vector2d<T>::data()
{
    return m_pData;
}
template<class T>
typename vector2d<T>::const_pointer vector2d<T>::data() const
{
    return m_pData;
}