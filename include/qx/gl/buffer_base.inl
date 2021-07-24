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
//!\fn                    qx::buffer_base::~buffer_base
//
//!\brief  buffer_base object destructor
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline buffer_base::~buffer_base(void)
{
    Delete();
}

//==============================================================================
//!\fn                      qx::buffer_base::Generate
//
//!\brief  Generate buffer object name
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void buffer_base::Generate()
{
    glGenBuffers(1, &m_nBuffer);
}

//==============================================================================
//!\fn                       qx::buffer_base::Delete
//
//!\brief  Delete named buffer object
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void buffer_base::Delete()
{
    if (m_nBuffer != std::numeric_limits<GLuint>::max())
    {
        glDeleteBuffers(1, &m_nBuffer);
        m_nBuffer = std::numeric_limits<GLuint>::max();
    }
}

//==============================================================================
//!\fn                        qx::buffer_base::Bind
//
//!\brief  Bind a named buffer object
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void buffer_base::Bind() const
{
    glBindBuffer(GetBufferType(), m_nBuffer);
}

//==============================================================================
//!\fn                       qx::buffer_base::Unbind
//
//!\brief  Unbind a named buffer object
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void buffer_base::Unbind() const
{
    glBindBuffer(GetBufferType(), 0);
}

//==============================================================================
//!\fn                     qx::buffer_base::MemBarrier
//
//!\brief  Defines a barrier ordering memory transactions
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void buffer_base::MemBarrier()
{
    glMemoryBarrier(GetBarrierBit());
}

//==============================================================================
//!\fn                       qx::buffer_base::Update
//
//!\brief  Update the whole buffer
//!\param  nSize  - data size
//!\param  pData  - data pointer
//!\param  eUsage - the expected usage pattern of the data store
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void buffer_base::Update(GLsizeiptr nSize, const void* pData, GLenum eUsage)
{
    glBufferData(GetBufferType(), nSize, pData, eUsage);
}

//==============================================================================
//!\fn                       qx::buffer_base::UpdatePart
//
//!\brief  Update buffer part
//!\param  nOffset - offset from the buffer beginning
//!\param  nSize   - data size
//!\param  pData   - data pointer
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void buffer_base::UpdatePart(GLintptr nOffset, GLsizeiptr nSize, const void* pData)
{
    glBufferSubData(GetBufferType(), nOffset, nSize, pData);
}

}
