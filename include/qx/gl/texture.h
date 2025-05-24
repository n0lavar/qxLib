/**

    @file      texture.h
    @author    Khrapov
    @date      23.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/ibuffer.h>
#include <qx/typedefs.h>
#include <memory>

namespace qx
{

/**

    @class   base_texture
    @brief   Base texture class
    @author  Khrapov
    @date    10.07.2020

**/
class base_texture : public IBuffer
{
public:
    base_texture() = default;
    virtual ~base_texture();

    QX_DECL_IBUFFER

    /**
        @brief  Get texture target
        @retval - texture target
    **/
    GLenum GetTarget() const;

    /**
        @brief  Get texture internal format
        @retval - texture internal format
    **/
    GLenum GetInternalFormat() const;

    /**
        @brief  Get texture width
        @retval - texture width
    **/
    GLsizei GetWidth() const;

    /**
        @brief  Get texture height
        @retval - texture height
    **/
    GLsizei GetHeight() const;

    /**
        @brief Set texture target
        @param eTarget - target texture
    **/
    void SetTarget(GLenum eTarget);

    /**
        @brief   Specify a two-dimensional texture image
        @details https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
        @param   nLevel          - level-of-detail number. 
        @param   eInternalFormat - number of color components in the texture 
        @param   nWidth          - width of the texture image 
        @param   nHeight         - height of the texture image 
        @param   eFormat         - format of the pixel data 
        @param   eType           - data type of the pixel data 
        @param   pData           - pointer to the image data in memory 
        @param   eTarget         - non-default target. -1 value will use m_eTextureTarget 
    **/
    void Specify2DTexImage(
        GLint       nLevel,
        GLenum      eInternalFormat,
        GLsizei     nWidth,
        GLsizei     nHeight,
        GLenum      eFormat,
        GLenum      eType,
        const void* pData   = nullptr,
        GLenum      eTarget = -1);

    /**
        @brief Establish parameters of a multisample texture's image
        @param nSamples              - level-of-detail number. 
        @param eInternalFormat       - number of color components in the texture 
        @param nWidth                - width of the texture image 
        @param nHeight               - height of the texture image 
        @param bFixedSampleLocations - specifies whether the image will use identical
                                       sample locations and the same number of samples
                                       for all texels in the image, and the sample
                                       locations will not depend on the internal
                                       format or size of the image
    **/
    void Specify2DMultisample(
        GLsizei   nSamples,
        GLenum    eInternalFormat,
        GLsizei   nWidth,
        GLsizei   nHeight,
        GLboolean bFixedSampleLocations);

    /**
        @brief Generate mipmap for texture
    **/
    void GenerateMipmap();

    /**
        @brief Set texture parameter
        @param eName - the symbolic name of a single-valued texture parameter
        @param value - the value of eName
    **/
    void SetParameter(GLenum eName, GLfloat value);

    /**
        @brief Set texture parameter
        @param eName - the symbolic name of a single-valued texture parameter
        @param value - the value of eName
    **/
    void SetParameter(GLenum eName, GLint value);

    /**
        @brief Set texture parameter
        @param eName - the symbolic name of a single-valued texture parameter
        @param value - the value of eName
    **/
    void SetParameter(GLenum eName, const GLfloat* value);

    /**
        @brief Set texture parameter
        @param eName - the symbolic name of a single-valued texture parameter
        @param value - the value of eName
    **/
    void SetParameter(GLenum eName, const GLint* value);

    /**
        @brief Set texture parameter
        @param eName - the symbolic name of a single-valued texture parameter
        @param value - the value of eName
    **/
    void SetParameter(GLenum eName, const GLuint* value);

private:
    GLuint  m_nTexture        = std::numeric_limits<GLuint>::max();
    GLenum  m_eTextureTarget  = GL_TEXTURE_2D;
    GLenum  m_eInternalFormat = GL_RGBA;
    GLsizei m_nWidth          = 0;
    GLsizei m_nHeight         = 0;
};

using texture = base_texture;

} // namespace qx


#include <qx/gl/texture.inl>
