//==============================================================================
//
//!\file                         texture.inl
//
//!\brief       OpenGL textures classes: texture and copyble_texture
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
//!\fn              qx::base_texture<COPYBLE>::~base_texture
//
//!\brief  base_texture object destructor
//!\author Khrapov
//!\date   10.07.2020
//==============================================================================
template<bool COPYBLE>
inline base_texture<COPYBLE>::~base_texture(void)
{
    Delete();
}

//==============================================================================
//!\fn                qx::base_texture<COPYBLE>::Generate
//
//!\brief  Generate texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_texture<COPYBLE>::Generate(void)
{
    if (m_nTexture == std::numeric_limits<GLuint>::max())
        glGenTextures(1, &m_nTexture);
}

//==============================================================================
//!\fn                 qx::base_texture<COPYBLE>::Delete
//
//!\brief  Delete texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_texture<COPYBLE>::Delete(void)
{
    if constexpr (!COPYBLE)
    {
        if (m_nTexture != std::numeric_limits<GLuint>::max())
        {
            glDeleteTextures(1, &m_nTexture);
            m_nTexture = std::numeric_limits<GLuint>::max();
        }
    }
}

//==============================================================================
//!\fn                  qx::base_texture<COPYBLE>::Bind
//
//!\brief  Bind texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_texture<COPYBLE>::Bind(void) const
{
    glBindTexture(m_eTextureTarget, m_nTexture);
}

//==============================================================================
//!\fn                 qx::base_texture<COPYBLE>::Unbind
//
//!\brief  Unbind texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_texture<COPYBLE>::Unbind(void) const
{
    glBindTexture(m_eTextureTarget, 0);
}

//==============================================================================
//!\fn                qx::base_texture<COPYBLE>::SetTarget
//
//!\brief  Set texture target
//!\param  eTarget - target texture
//!\author Khrapov
//!\date   23.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_texture<COPYBLE>::SetTarget(GLenum eTarget)
{
    m_eTextureTarget = eTarget;
}

//==============================================================================
//!\fn            qx::base_texture<COPYBLE>::Specify2DTexImage
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
//!\author  Khrapov
//!\date    23.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_texture<COPYBLE>::Specify2DTexImage(
    GLint         level,
    GLint         internalformat,
    GLsizei       width,
    GLsizei       height,
    GLenum        format,
    GLenum        type,
    const void  * pData,
    GLenum        eTarget)
{
    glTexImage2D(
        eTarget != -1 ? eTarget : m_eTextureTarget,
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
//!\fn          qx::base_texture<COPYBLE>::Specify2DMultisample
//
//!\brief  Establish parameters of a multisample texture's image
//!\param  nSamples              - level-of-detail number.
//!\param  eInternalformat       - number of color components in the texture
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
template<bool COPYBLE>
inline void base_texture<COPYBLE>::Specify2DMultisample(
    GLsizei        nSamples,
    GLenum         eInternalformat,
    GLsizei        nWidth,
    GLsizei        nHeight,
    GLboolean      bFixedSampleLocations)
{
    glTexImage2DMultisample(
        m_eTextureTarget,
        nSamples,
        eInternalformat,
        nWidth,
        nHeight,
        bFixedSampleLocations);

    m_nWidth  = nWidth;
    m_nHeight = nHeight;
}

//==============================================================================
//!\fn             qx::base_texture<COPYBLE>::GenerateMipmap
//
//!\brief  Generate mipmap for texture
//!\author Khrapov
//!\date   15.04.2020
//==============================================================================
template<bool COPYBLE>
inline void base_texture<COPYBLE>::GenerateMipmap(void)
{
    glGenerateMipmap(m_eTextureTarget);
}

template<bool COPYBLE>
inline void base_texture<COPYBLE>::SetParameter(GLenum target, GLfloat value)
{
    glTextureParameterf(m_nTexture, target, value);
}

template<bool COPYBLE>
inline void base_texture<COPYBLE>::SetParameter(GLenum target, GLint value)
{
    glTextureParameteri(m_nTexture, target, value);
}

template<bool COPYBLE>
inline void base_texture<COPYBLE>::SetParameter(GLenum target, const GLfloat* value)
{
    glTextureParameterfv(m_nTexture, target, value);
}

template<bool COPYBLE>
inline void base_texture<COPYBLE>::SetParameter(GLenum target, const GLint* value)
{
    glTextureParameterIiv(m_nTexture, target, value);
}

template<bool COPYBLE>
inline void base_texture<COPYBLE>::SetParameter(GLenum target, const GLuint* value)
{
    glTextureParameterIuiv(m_nTexture, target, value);
}

//==============================================================================
//!\fn             qx::base_texture<COPYBLE>::Assign<COPYBLE>
//
//!\brief  Assing by derived class
//!\param  other - derived class instance
//!\author Khrapov
//!\date   10.07.2020
//==============================================================================
template<bool COPYBLE>
template<class Derived>
void base_texture<COPYBLE>::Assign(const Derived& other)
{
    m_nTexture       = other.m_nTexture;
    m_eTextureTarget = other.m_eTextureTarget;
    m_nWidth         = other.m_nWidth;
    m_nHeight        = other.m_nHeight;
}

}
