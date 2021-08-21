/**

    @file      texture.inl
    @author    Khrapov
    @date      23.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_texture::~base_texture(void)
{
    if (m_nTexture != std::numeric_limits<GLuint>::max())
    {
        glDeleteTextures(1, &m_nTexture);
        m_nTexture = std::numeric_limits<GLuint>::max();
    }
}

inline void base_texture::Generate(void)
{
    if (m_nTexture == std::numeric_limits<GLuint>::max())
        glGenTextures(1, &m_nTexture);
}

inline void base_texture::Bind(void) const
{
    glBindTexture(m_eTextureTarget, m_nTexture);
}

inline void base_texture::Unbind(void) const
{
    glBindTexture(m_eTextureTarget, 0);
}

inline GLuint base_texture::GetBufferName(void) const
{
    return m_nTexture;
}

inline bool base_texture::IsGenerated(void) const
{
    return m_nTexture != std::numeric_limits<GLuint>::max();
};

inline GLenum base_texture::GetTarget(void) const
{
    return m_eTextureTarget;
}

inline GLenum base_texture::GetInternalFormat(void) const
{
    return m_eInternalFormat;
}

inline GLsizei base_texture::GetWidth(void) const
{
    return m_nWidth;
}

inline GLsizei base_texture::GetHeight(void) const
{
    return m_nHeight;
}

inline void base_texture::SetTarget(GLenum eTarget)
{
    m_eTextureTarget = eTarget;
}

inline void base_texture::Specify2DTexImage(
    GLint       nLevel,
    GLenum      eInternalFormat,
    GLsizei     nWidth,
    GLsizei     nHeight,
    GLenum      eFormat,
    GLenum      eType,
    const void* pData,
    GLenum      eTarget)
{
    glTexImage2D(
        eTarget != -1 ? eTarget : m_eTextureTarget,
        nLevel,
        eInternalFormat,
        nWidth,
        nHeight,
        0,
        eFormat,
        eType,
        pData);

    m_nWidth          = nWidth;
    m_nHeight         = nHeight;
    m_eInternalFormat = eInternalFormat;
}

inline void base_texture::Specify2DMultisample(
    GLsizei   nSamples,
    GLenum    eInternalFormat,
    GLsizei   nWidth,
    GLsizei   nHeight,
    GLboolean bFixedSampleLocations)
{
    glTexImage2DMultisample(
        m_eTextureTarget,
        nSamples,
        eInternalFormat,
        nWidth,
        nHeight,
        bFixedSampleLocations);

    m_nWidth          = nWidth;
    m_nHeight         = nHeight;
    m_eInternalFormat = eInternalFormat;
}

inline void base_texture::GenerateMipmap(void)
{
    glGenerateMipmap(m_eTextureTarget);
}

inline void base_texture::SetParameter(GLenum eName, GLfloat value)
{
    glTextureParameterf(m_nTexture, eName, value);
}

inline void base_texture::SetParameter(GLenum eName, GLint value)
{
    glTextureParameteri(m_nTexture, eName, value);
}

inline void base_texture::SetParameter(GLenum eName, const GLfloat* value)
{
    glTextureParameterfv(m_nTexture, eName, value);
}

inline void base_texture::SetParameter(GLenum eName, const GLint* value)
{
    glTextureParameterIiv(m_nTexture, eName, value);
}

inline void base_texture::SetParameter(GLenum eName, const GLuint* value)
{
    glTextureParameterIuiv(m_nTexture, eName, value);
}

} // namespace qx
