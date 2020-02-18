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
//!\fn                      vector2d<T>::vector2d
//
//!\brief  vector2d object constructor
//!\param  rows  - 
//!\param  cols  - 
//!\param  pData - 
//!\author Khrapov
//!\date   19.02.2020
//============================================================================
template<class T>
inline vector2d<T>::vector2d(size_t rows, size_t cols, const T* pData)
{
    assign(rows, cols, pData);
}

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
inline void vector2d<T>::assign(vector2d&& other) noexcept
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
inline void vector2d<T>::assign(const vector2d& other)
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
inline void vector2d<T>::assign(size_t rows, size_t cols, const T* pData)
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
inline void vector2d<T>::assign(size_t rows, size_t cols, const T& data)
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
inline bool vector2d<T>::resize(size_t rows, size_t cols)
{
    if (rows > 0 && cols > 0)
    {
        clear();

        m_pData = new T[rows * cols];
        m_nRows = rows;
        m_nCols = cols;

        return true;
    }

    return false
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
inline void vector2d<T>::fill(const T& elem)
{
    for (size_t i = 0; i < size_x(); i++)
        for (size_t j = 0; j < size_y(); j++)
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
inline typename vector2d<T>::row& vector2d<T>::operator[](size_t nRow)
{
    int nInd = nRow *= m_nCols;
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
inline const typename vector2d<T>::row& vector2d<T>::operator[](size_t nRow) const
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
inline const T& vector2d<T>::get(size_t nRow, size_t nCol) const
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
inline void vector2d<T>::clear(void)
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
inline void vector2d<T>::set(size_t nRow, size_t nCol, const T& data)
{
    (*this)[nRow][nCol] = data;
}
