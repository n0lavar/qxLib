/**

    @file      rbo.inl
    @brief     Contains qx::base_rbo class implementation
    @author    Khrapov
    @date      20.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline qx::base_rbo::~base_rbo(void)
{
    if (m_nBuffer != std::numeric_limits<GLuint>::max())
    {
        glDeleteRenderbuffers(1, &m_nBuffer);
        m_nBuffer = std::numeric_limits<GLuint>::max();
    }
}

inline void base_rbo::Init(
    size_t nWidth,
    size_t nHeight,
    GLenum eInternalFormat,
    GLenum eAttachment,
    size_t nMultiSamples)
{
    m_nWidth          = nWidth;
    m_nHeight         = nHeight;
    m_eInternalFormat = eInternalFormat;
    m_eAttachmentType = eAttachment;

    // use a single renderbuffer object for both a depth and stencil buffer.
    if (nMultiSamples > 0)
    {
        glRenderbufferStorageMultisample(
            GL_RENDERBUFFER,
            static_cast<GLsizei>(nMultiSamples),
            eInternalFormat,
            static_cast<GLsizei>(nWidth),
            static_cast<GLsizei>(nHeight));
    }
    else
    {
        glRenderbufferStorage(
            GL_RENDERBUFFER,
            eInternalFormat,
            static_cast<GLsizei>(nWidth),
            static_cast<GLsizei>(nHeight));
    }
}

inline void base_rbo::Generate(void)
{
    glGenRenderbuffers(1, &m_nBuffer);
}

inline void base_rbo::Bind(void) const
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_nBuffer);
}

inline void base_rbo::Unbind(void) const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

inline GLuint base_rbo::GetBufferName(void) const
{
    return m_nBuffer;
}

inline bool base_rbo::IsGenerated(void) const
{
    return m_nBuffer != std::numeric_limits<GLuint>::max();
}

inline size_t base_rbo::GetWidth(void) const
{
    return m_nWidth;
}

inline size_t base_rbo::GetHeight(void) const
{
    return m_nHeight;
}

inline GLenum base_rbo::GetInternalFormat(void) const
{
    return m_eInternalFormat;
}

inline GLenum base_rbo::GetAttachmentType(void) const
{
    return m_eAttachmentType;
}


} // namespace qx
