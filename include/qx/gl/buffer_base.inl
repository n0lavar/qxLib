/**

    @file      buffer_base.inl
    @brief     Contains qx::buffer_base class implementation
    @author    Khrapov
    @date      19.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline buffer_base::~buffer_base(void)
{
    if (m_nBuffer != std::numeric_limits<GLuint>::max())
    {
        glDeleteBuffers(1, &m_nBuffer);
        m_nBuffer = std::numeric_limits<GLuint>::max();
    }
}

inline void buffer_base::Generate()
{
    glGenBuffers(1, &m_nBuffer);
}

inline void buffer_base::Bind() const
{
    glBindBuffer(GetBufferType(), m_nBuffer);
}

inline void buffer_base::Unbind() const
{
    glBindBuffer(GetBufferType(), 0);
}

inline GLuint buffer_base::GetBufferName(void) const
{
    return m_nBuffer;
}

inline bool buffer_base::IsGenerated(void) const
{
    return m_nBuffer != std::numeric_limits<GLuint>::max();
}

inline void buffer_base::MemBarrier()
{
    glMemoryBarrier(GetBarrierBit());
}

inline void buffer_base::Update(
    GLsizeiptr  nSize,
    const void* pData,
    GLenum      eUsage)
{
    glBufferData(GetBufferType(), nSize, pData, eUsage);
}

inline void buffer_base::UpdatePart(
    GLintptr    nOffset,
    GLsizeiptr  nSize,
    const void* pData)
{
    glBufferSubData(GetBufferType(), nOffset, nSize, pData);
}

} // namespace qx
