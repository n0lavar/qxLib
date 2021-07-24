//==============================================================================
//
//!\file                         texture.inl
//
//!\brief       Contains qx::base_texture class
//!\details     ~
//
//!\author      Khrapov
//!\date        23.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                   qx::base_texture::~base_texture
//
//!\brief  base_texture object destructor
//!\author Khrapov
//!\date   10.07.2020
//==============================================================================
inline base_texture::~base_texture(void)
{
    Delete();
}

//==============================================================================
//!\fn                     qx::base_texture::Generate
//
//!\brief  Generate texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void base_texture::Generate(void)
{
    if (m_nTexture == std::numeric_limits<GLuint>::max())
        glGenTextures(1, &m_nTexture);
}

//==============================================================================
//!\fn                      qx::base_texture::Delete
//
//!\brief  Delete texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void base_texture::Delete(void)
{
    if (m_nTexture != std::numeric_limits<GLuint>::max())
    {
        glDeleteTextures(1, &m_nTexture);
        m_nTexture = std::numeric_limits<GLuint>::max();
    }
}

//==============================================================================
//!\fn                       qx::base_texture::Bind
//
//!\brief  Bind texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void base_texture::Bind(void) const
{
    glBindTexture(m_eTextureTarget, m_nTexture);
}

//==============================================================================
//!\fn                      qx::base_texture::Unbind
//
//!\brief  Unbind texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void base_texture::Unbind(void) const
{
    glBindTexture(m_eTextureTarget, 0);
}

//==============================================================================
//!\fn                     qx::base_texture::SetTarget
//
//!\brief  Set texture target
//!\param  eTarget - target texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void base_texture::SetTarget(GLenum eTarget)
{
    m_eTextureTarget = eTarget;
}

//==============================================================================
//!\fn                 qx::base_texture::Specify2DTexImage
//
//!\brief   Specify a two-dimensional texture image
//!\details https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
//!\param   nLevel          - level-of-detail number.
//!\param   eInternalFormat - number of color components in the texture
//!\param   nWidth          - width of the texture image
//!\param   nHeight         - height of the texture image
//!\param   eFormat         - format of the pixel data
//!\param   eType           - data type of the pixel data
//!\param   pData           - pointer to the image data in memory
//!\param   eTarget         - non-default target. -1 value will use m_eTextureTarget
//!\author  Khrapov
//!\date    23.01.2020
//==============================================================================
inline void base_texture::Specify2DTexImage(
    GLint           nLevel,
    GLenum          eInternalFormat,
    GLsizei         nWidth,
    GLsizei         nHeight,
    GLenum          eFormat,
    GLenum          eType,
    const void    * pData,
    GLenum          eTarget)
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

//==============================================================================
//!\fn               qx::base_texture::Specify2DMultisample
//
//!\brief  Establish parameters of a multisample texture's image
//!\param  nSamples              - level-of-detail number.
//!\param  eInternalFormat       - number of color components in the texture
//!\param  nWidth                - width of the texture image
//!\param  nHeight               - height of the texture image
//!\param  bFixedSampleLocations - specifies whether the image will use identical
//!                                sample locations and the same number of samples
//!                                for all texels in the image, and the sample
//!                                locations will not depend on the internal
//!                                format or size of the image
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void base_texture::Specify2DMultisample(
    GLsizei        nSamples,
    GLenum         eInternalFormat,
    GLsizei        nWidth,
    GLsizei        nHeight,
    GLboolean      bFixedSampleLocations)
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

//==============================================================================
//!\fn                  qx::base_texture::GenerateMipmap
//
//!\brief  Generate mipmap for texture
//!\author Khrapov
//!\date   15.04.2020
//==============================================================================
inline void base_texture::GenerateMipmap(void)
{
    glGenerateMipmap(m_eTextureTarget);
}

inline void base_texture::SetParameter(GLenum target, GLfloat value)
{
    glTextureParameterf(m_nTexture, target, value);
}

inline void base_texture::SetParameter(GLenum target, GLint value)
{
    glTextureParameteri(m_nTexture, target, value);
}

inline void base_texture::SetParameter(GLenum target, const GLfloat* value)
{
    glTextureParameterfv(m_nTexture, target, value);
}

inline void base_texture::SetParameter(GLenum target, const GLint* value)
{
    glTextureParameterIiv(m_nTexture, target, value);
}

inline void base_texture::SetParameter(GLenum target, const GLuint* value)
{
    glTextureParameterIuiv(m_nTexture, target, value);
}

}
