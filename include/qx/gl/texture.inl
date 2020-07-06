//==============================================================================
//
//!\file                         texture.inl
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        23.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx::gl
{

//==============================================================================
//!\fn                        texture::~texture
//
//!\brief  texture object destructor
//!\author Khrapov
//!\date   15.04.2020
//==============================================================================
inline texture::~texture(void)
{
    Delete();
}

//==============================================================================
//!\fn                        texture::Generate
//
//!\brief  Generate texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void texture::Generate(void)
{
    if (m_nTexture == UINT_EMPTY_VALUE)
        glGenTextures(1, &m_nTexture);
}

//==============================================================================
//!\fn                         texture::Delete
//
//!\brief  Delete texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void texture::Delete(void)
{
    if (m_nTexture != UINT_EMPTY_VALUE)
    {
        // also sets m_nTexture to 0
        glDeleteTextures(1, &m_nTexture);
    }
}

//==============================================================================
//!\fn                         texture::Bind
//
//!\brief  Bind texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void texture::Bind(void) const
{
    glBindTexture(m_eTextureTarget, m_nTexture);
}

//==============================================================================
//!\fn                         texture::Unbind
//
//!\brief  Unbind texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void texture::Unbind(void) const
{
    glBindTexture(m_eTextureTarget, 0);
}

//==============================================================================
//!\fn                         texture::SetTarget
//
//!\brief  Set texture target
//!\param  eTarget - target texture 
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void texture::SetTarget(GLenum eTarget)
{
    m_eTextureTarget = eTarget;
}

//==============================================================================
//!\fn                          texture::Specify2DTexImage
//
//!\brief   Specify a two-dimensional texture image
//!\details https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
//!\param   level          - level-of-detail number.
//!\param   internalformat - number of color components in the texture
//!\param   width          - width of the texture image
//!\param   height         - height of the texture image
//!\param   format         - format of the pixel data
//!\param   type           - data type of the pixel data
//!\param   pData          - pointer to the image data in memory
//!\param   eTarget        - non-default target. -1 value will use m_eTextureTarget
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void texture::Specify2DTexImage(GLint         level, 
                                       GLint         internalformat, 
                                       GLsizei       width, 
                                       GLsizei       height, 
                                       GLenum        format,
                                       GLenum        type, 
                                       const void  * pData,
                                       GLenum        eTarget)
{
    glTexImage2D(eTarget != -1 ? eTarget : m_eTextureTarget, 
                 level,
                 internalformat,
                 width,
                 height,
                 0,
                 format,
                 type,
                 pData);

    m_nWidth  = width;
    m_nHeight = height;
}

//==============================================================================
//!\fn                        texture::Specify2DMultisample
//
//!\brief  Establish parameters of a multisample texture's image
//!\param  nSamples              - level-of-detail number.
//!\param  eInternalformat       - number of color components in the texture
//!\param  nWidth                - width of the texture image
//!\param  nHeight               - height of the texture image
//!\param  bFixedsamplelocations - format of the pixel data
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
inline void texture::Specify2DMultisample(GLsizei        nSamples,
                                          GLenum         eInternalformat,
                                          GLsizei        nWidth,
                                          GLsizei        nHeight,
                                          GLboolean      bFixedsamplelocations)
{
    glTexImage2DMultisample(m_eTextureTarget, nSamples, GL_RGB, nWidth, nHeight, GL_TRUE);

    m_nWidth  = nWidth;
    m_nHeight = nHeight;
}
//==============================================================================
//!\fn                     texture::GenerateMipmap
//
//!\brief  Generate mipmap for texture
//!\author Khrapov
//!\date   15.04.2020
//==============================================================================
inline void texture::GenerateMipmap(void)
{
    glGenerateMipmap(m_eTextureTarget);
}

template<>
inline void texture::SetParameter(GLenum target, GLfloat value)
{
    glTextureParameterf(m_nTexture, target, value);
}

template<>
inline void texture::SetParameter(GLenum target, GLint value)
{
    glTextureParameteri(m_nTexture, target, value);
}

template<>
inline void texture::SetParameter(GLenum target, const GLfloat* value)
{
    glTextureParameterfv(m_nTexture, target, value);
}

template<>
inline void texture::SetParameter(GLenum target, const GLint* value)
{
    glTextureParameterIiv(m_nTexture, target, value);
}

template<>
inline void texture::SetParameter(GLenum target, const GLuint* value)
{
    glTextureParameterIuiv(m_nTexture, target, value);
}

}