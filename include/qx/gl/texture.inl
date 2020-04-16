#include "texture.h"
//============================================================================
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
//============================================================================

namespace qx::gl
{

//============================================================================
//!\fn                        texture::~texture
//
//!\brief  texture object destructor
//!\author Khrapov
//!\date   15.04.2020
//============================================================================
inline texture::~texture(void)
{
    Delete();
}

//============================================================================
//!\fn                          texture::Init
//
//!\brief   Specify a two-dimensional texture image
//!\details https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
//!\param   target         - target texture 
//!\param   level          - level-of-detail number.
//!\param   internalformat - number of color components in the texture
//!\param   width          - width of the texture image
//!\param   height         - height of the texture image
//!\param   format         - format of the pixel data
//!\param   type           - data type of the pixel data
//!\param   data           - pointer to the image data in memory
//!\author Khrapov
//!\date   23.01.2020
//============================================================================
inline void texture::Init(GLenum        target, 
                          GLint         level, 
                          GLint         internalformat, 
                          GLsizei       width, 
                          GLsizei       height, 
                          GLenum        format,
                          GLenum        type, 
                          const void  * data)
{
    Generate();
    Bind();
    glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);

    m_eTextureType  = target;
    m_nWidth        = width;
    m_nHeight       = height;
}

//============================================================================
//!\fn                        texture::Generate
//
//!\brief  Generate texture
//!\author Khrapov
//!\date   23.01.2020
//============================================================================
inline void texture::Generate(void)
{
    if (m_nTexture == UINT_EMPTY_VALUE)
        glGenTextures(1, &m_nTexture);
}

//============================================================================
//!\fn                         texture::Delete
//
//!\brief  Delete texture
//!\author Khrapov
//!\date   23.01.2020
//============================================================================
inline void texture::Delete(void)
{
    if (m_nTexture != UINT_EMPTY_VALUE)
    {
        // also sets m_nTexture to 0
        glDeleteTextures(1, &m_nTexture);
        m_nWidth  = 0;
        m_nHeight = 0;
    }
}

//============================================================================
//!\fn                         texture::Bind
//
//!\brief  Bind texture
//!\author Khrapov
//!\date   23.01.2020
//============================================================================
inline void texture::Bind(void) const
{
    glBindTexture(m_eTextureType, m_nTexture);
}

//============================================================================
//!\fn                         texture::Unbind
//
//!\brief  Unbind texture
//!\author Khrapov
//!\date   23.01.2020
//============================================================================
inline void texture::Unbind(void) const
{
    glBindTexture(m_eTextureType, 0);
}

//============================================================================
//!\fn                     texture::GenerateMipmap
//
//!\brief  Generate mipmap for texture
//!\author Khrapov
//!\date   15.04.2020
//============================================================================
inline void texture::GenerateMipmap(void)
{
    glGenerateMipmap(m_eTextureType);
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