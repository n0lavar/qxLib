/**

    @file      rbo.inl
    @author    Khrapov
    @date      20.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_rbo::~base_rbo()
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

inline void base_rbo::Generate()
{
    glGenRenderbuffers(1, &m_nBuffer);
}

inline void base_rbo::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_nBuffer);
}

inline void base_rbo::Unbind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

inline GLuint base_rbo::GetBufferName() const
{
    return m_nBuffer;
}

inline bool base_rbo::IsGenerated() const
{
    return m_nBuffer != std::numeric_limits<GLuint>::max();
}

inline size_t base_rbo::GetWidth() const
{
    return m_nWidth;
}

inline size_t base_rbo::GetHeight() const
{
    return m_nHeight;
}

inline GLenum base_rbo::GetInternalFormat() const
{
    return m_eInternalFormat;
}

inline GLenum base_rbo::GetAttachmentType() const
{
    return m_eAttachmentType;
}


} // namespace qx
