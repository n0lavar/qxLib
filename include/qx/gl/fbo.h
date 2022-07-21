/**

    @file      fbo.h
    @brief     Contains qx::base_fbo class
    @author    Khrapov
    @date      20.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/rbo.h>
#include <qx/gl/texture.h>

namespace qx
{

/**

    @class   base_fbo
    @brief   Base FBO class
    @details ~
    @author  Khrapov
    @date    10.07.2020

**/
class base_fbo : public IBuffer
{
public:
    /**
        @brief base_fbo object destructor
    **/
    virtual ~base_fbo();

    QX_DECL_IBUFFER

    /**
        @brief Set target type
        @param target - GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER or GL_READ_FRAMEBUFFER
    **/
    void SetTarget(GLenum target);

    /**
        @brief Attach RBO th FRO
        @param rbo - render buffer object
    **/
    void AttachRBO(const base_rbo& rbo);

    /**
        @brief Attache a single face of a specific MIP level to FBO
        @param attachment   - attachment point of the framebuffer
        @param texture      - fbo texture
        @param nMipmapLevel - mipmap level of texture
    **/
    void AttachTexture2D(GLenum attachment, const base_texture& texture, GLint nMipmapLevel = 0);

    /**
        @brief Attache all cube map faces of a specific MIP level
               as an array of images (layered framebuffer)
        @param attachment   - attachment point of the framebuffer
        @param texture      - fbo texture
        @param nMipmapLevel - mipmap level of texture
    **/
    void AttachTexture(GLenum attachment, const base_texture& texture, GLint nMipmapLevel = 0);

    /**
        @brief  Check framebuffer status
        @retval - framebuffer error or empty if success  
    **/
    std::string_view CheckStatus() const;

private:
    GLuint m_nBuffer = std::numeric_limits<GLuint>::max();
    GLenum m_nTarget = GL_FRAMEBUFFER;
};

using fbo = base_fbo;

} // namespace qx

#include <qx/gl/fbo.inl>
