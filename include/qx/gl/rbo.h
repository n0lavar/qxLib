/**

    @file      rbo.h
    @author    Khrapov
    @date      20.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/ibuffer.h>
#include <qx/typedefs.h>

namespace qx
{

/**

    @class   base_rbo
    @brief   Base RBO class
    @details ~
    @author  Khrapov
    @date    10.07.2020

**/
class base_rbo : IBuffer
{
public:
    virtual ~base_rbo();

    /**
        @brief Init RBO with width and height
        @param nWidth          - width 
        @param nHeight         - height 
        @param eInternalFormat - internal format used for images 
        @param eAttachment     - attachment point of the framebuffer 
        @param nMultiSamples   - samples number, 0 - disable 
    **/
    void Init(size_t nWidth, size_t nHeight, GLenum eInternalFormat, GLenum eAttachment, size_t nMultiSamples = 0);

    QX_DECL_IBUFFER

    /**
        @brief  Get texture width
        @retval - texture width
    **/
    size_t GetWidth() const;

    /**
        @brief  Get texture height
        @retval - texture height
    **/
    size_t GetHeight() const;

    /**
        @brief  Get texture internal format
        @retval - texture internal format
    **/
    GLenum GetInternalFormat() const;

    /**
        @brief  Get attachment type
        @retval - attachment type
    **/
    GLenum GetAttachmentType() const;

private:
    GLuint m_nBuffer         = std::numeric_limits<GLuint>::max();
    GLenum m_eInternalFormat = 0;
    GLenum m_eAttachmentType = 0;
    size_t m_nWidth          = 0;
    size_t m_nHeight         = 0;
};

using rbo = base_rbo;

} // namespace qx

#include <qx/gl/rbo.inl>
