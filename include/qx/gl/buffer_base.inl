//==============================================================================
//
//!\file                    buffer_base.inl
//
//!\brief       Contains buffer_base class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                 buffer_base<COPYBLE>::~buffer_base
//
//!\brief  buffer_base object destructor
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline buffer_base<COPYBLE>::~buffer_base(void)
{
    Delete();
}

//==============================================================================
//!\fn                   buffer_base<COPYBLE>::Generate
//
//!\brief  Generate buffer object name
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_base<COPYBLE>::Generate()
{
    glGenBuffers(1, &m_nBuffer);
}

//==============================================================================
//!\fn                    buffer_base<COPYBLE>::Delete
//
//!\brief  Delete named buffer object
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_base<COPYBLE>::Delete()
{
    if constexpr (!COPYBLE)
    {
        if (m_nBuffer != UINT_EMPTY_VALUE)
        {
            glDeleteBuffers(1, &m_nBuffer);
            m_nBuffer = UINT_EMPTY_VALUE;
        }
    }
}

//==============================================================================
//!\fn                     buffer_base<COPYBLE>::Bind
//
//!\brief  Bind a named buffer object
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_base<COPYBLE>::Bind() const
{
    glBindBuffer(GetBufferType(), m_nBuffer);
}

//==============================================================================
//!\fn                    buffer_base<COPYBLE>::Unbind
//
//!\brief  Unbind a named buffer object
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_base<COPYBLE>::Unbind() const
{
    glBindBuffer(GetBufferType(), 0);
}

//==============================================================================
//!\fn                   buffer_base<COPYBLE>::BindBase
//
//!\brief  Bind a buffer object to an indexed buffer target from shader
//!\param  nIndex - index
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_base<COPYBLE>::BindBase(GLuint nIndex)
{
    glBindBufferBase(GetBufferType(), nIndex, m_nBuffer);
}

//==============================================================================
//!\fn                  buffer_base<COPYBLE>::MemBarrier
//
//!\brief  Defines a barrier ordering memory transactions
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_base<COPYBLE>::MemBarrier()
{
    glMemoryBarrier(GetBarrierBit());
}

//==============================================================================
//!\fn                    buffer_base<COPYBLE>::Update
//
//!\brief  Update the whole buffer
//!\param  nSize  - data size
//!\param  pData  - data pointer
//!\param  eUsage - the expected usage pattern of the data store
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_base<COPYBLE>::Update(GLsizeiptr nSize, const void* pData, GLenum eUsage)
{
    glBufferData(GetBufferType(), nSize, pData, eUsage);
}

//==============================================================================
//!\fn                  buffer_base<COPYBLE>::UpdatePart
//
//!\brief  Update buffer part
//!\param  nOffset - offset from the buffer beginning
//!\param  nSize   - data size
//!\param  pData   - data pointer
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_base<COPYBLE>::UpdatePart(GLintptr nOffset, GLsizeiptr nSize, const void* pData)
{
    glBufferSubData(GetBufferType(), nOffset, nSize, pData);
}

}
