//============================================================================
//
//!\file                      ssbo_arrayed.inl
//
//!\brief       Contains ssbo_arrayed class
//!\details     ~
//
//!\author      Khrapov
//!\date        18.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================

namespace qx::gl
{

constexpr GLuint SSBO_HEADER_SIZE = 32;
static_assert(SSBO_HEADER_SIZE % 16 == 0);

//============================================================================
//!\fn                         ssbo_arrayed<T>::ssbo_arrayed
//
//!\brief  ssbo_arrayed object constructor
//!\param  nBindingPoint - buffer binding point from the shader
//!\param  nMaxObjects   - num of objects in the buffer
//!\author Khrapov
//!\date   9.01.2020
//============================================================================
template<typename T>
ssbo_arrayed<T>::ssbo_arrayed(GLuint nBindingPoint, size_t nMaxObjects)
{
    Init(nBindingPoint, nMaxObjects);
}

//============================================================================
//!\fn                          ssbo_arrayed<T>::Init
//
//!\brief  Init SSBO
//!\param  nBindingPoint - buffer binding point from the shader
//!\param  nMaxObjects   - num of objects in the buffer
//!\author Khrapov
//!\date   9.01.2020
//============================================================================
template<typename T>
void ssbo_arrayed<T>::Init(GLuint nBindingPoint, size_t nMaxObjects)
{
    ssbo::Init(nBindingPoint, SSBO_HEADER_SIZE + nMaxObjects * sizeof(T));

    m_Indexes.resize(nMaxObjects, UINT_EMPTY_VALUE);
    m_ArrayFirstFree = 0;

    UpdatePart(0, SSBO_HEADER_SIZE, &m_ArrayFirstFree);
}

//============================================================================
//!\fn                       ssbo_arrayed<T>::AddElement
//
//!\brief  Add element to SSBO vector
//!\param  pData - data pointer
//!\retval       - object index if succesfull, otherwise UINT_EMPTY_VALUE
//!\author Khrapov
//!\date   12.01.2020
//============================================================================
template<typename T>
size_t ssbo_arrayed<T>::AddElement(const T * pData)
{
    size_t nRet = UINT_EMPTY_VALUE;

    CHECK(m_ArrayFirstFree < m_Indexes.size())
    {
        nRet = std::find(m_Indexes.cbegin(),
                         m_Indexes.cend(),
                         UINT_EMPTY_VALUE) - m_Indexes.cbegin();

        m_Indexes[nRet] = static_cast<GLuint>(m_ArrayFirstFree);
        UpdateElem(m_ArrayFirstFree, pData);
        m_ArrayFirstFree++;
    }

    return nRet;
}

//============================================================================
//!\fn                       ssbo_arrayed<T>::UpdateElem
//
//!\brief  Update information in SSBO
//!\param  nElement - number of element in buffer
//!\param  pData    - data pointer
//!\author Khrapov
//!\date   9.01.2020
//============================================================================
template<typename T>
void ssbo_arrayed<T>::UpdateElem(size_t nIndex, const T * pData)
{
    UpdatePart(static_cast<GLintptr>(SSBO_HEADER_SIZE + static_cast<size_t>(m_Indexes[nIndex]) * sizeof(T)),
               sizeof(T),
               pData);
}

//============================================================================
//!\fn                       ssbo_arrayed<T>::RemoveElem
//
//!\brief  Remove element brom SSBO array
//!\param  nIndex - element index
//!\author Khrapov
//!\date   9.01.2020
//============================================================================
template<typename T>
void ssbo_arrayed<T>::RemoveElem(size_t nIndex)
{
    ASSERT(0);
    CHECK(m_Indexes[nIndex] != UINT_EMPTY_VALUE)
    {
        //if ()
        {
            glCopyBufferSubData(GetBufferName(),
                                GetBufferName(),
                                SSBO_HEADER_SIZE + (m_ArrayFirstFree - 1) * sizeof(T),
                                SSBO_HEADER_SIZE + static_cast<size_t>(m_Indexes[nIndex]) * sizeof(T),
                                sizeof(T));

            auto it = std::find(m_Indexes.begin(), m_Indexes.end(), m_ArrayFirstFree);
            *it = m_Indexes[nIndex];
        }
        m_Indexes[nIndex] = UINT_EMPTY_VALUE;
        m_ArrayFirstFree--;
    }
}

//============================================================================
//!\fn                        ssbo_arrayed<T>::SetIndex
//
//!\brief  Set array index
//!\param  nIndex - index
//!\author Khrapov
//!\date   18.01.2020
//============================================================================
template<typename T>
void ssbo_arrayed<T>::SetIndex(size_t nIndex)
{
    CHECK(m_Indexes[nIndex] != UINT_EMPTY_VALUE)
        UpdatePart(0, sizeof(GLuint), &(m_Indexes[nIndex]));
}

}