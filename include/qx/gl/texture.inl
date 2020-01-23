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
    m_eTextureType = target;
    Generate();
    Bind();
    glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
    // Unbind();
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
        glDeleteTextures(1, &m_nTexture);
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
//!\fn                         texture::Unbind
//
//!\brief  Render texture
//!\author Khrapov
//!\date   23.01.2020
//============================================================================
inline void texture::Render(void) const
{
    glActiveTexture(GL_TEXTURE0);
    Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Unbind();
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