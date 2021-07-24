//==============================================================================
//
//!\file                          texture.h
//
//!\brief       Contains qx::base_texture class
//!\details     ~
//
//!\author      Khrapov
//!\date        23.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <memory>
#include <qx/typedefs.h>
#include <qx/gl/ibuffer.h>

namespace qx
{

//==============================================================================
//
//!\class                  qx::base_texture
//
//!\brief   Base texture class
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
class base_texture : public IBuffer
{
public:

                    base_texture        (void) = default;
    virtual         ~base_texture       (void);

    virtual void    Generate            (void)          override;
    virtual void    Delete              (void)          override;
    virtual void    Bind                (void) const    override;
    virtual void    Unbind              (void) const    override;
    virtual GLuint  GetBufferName       (void) const    override;
    virtual bool    IsGenerated         (void) const    override;

            GLenum  GetTarget           (void) const;
            GLenum  GetInternalFormat   (void) const;
            GLsizei GetWidth            (void) const;
            GLsizei GetHeight           (void) const;

            void    SetTarget           (GLenum         eTarget);
            void    Specify2DTexImage   (GLint          nLevel,
                                         GLenum         eInternalFormat,
                                         GLsizei        nWidth,
                                         GLsizei        nHeight,
                                         GLenum         eFormat,
                                         GLenum         eType,
                                         const void*    pData   = nullptr,
                                         GLenum         eTarget = -1);
            void    Specify2DMultisample(GLsizei        nSamples,
                                         GLenum         eInternalFormat,
                                         GLsizei        nWidth,
                                         GLsizei        nHeight,
                                         GLboolean      bFixedSampleLocations);
            void    GenerateMipmap      (void);

            void    SetParameter        (GLenum         target,
                                         GLfloat        value);
            void    SetParameter        (GLenum         target,
                                         GLint          value);
            void    SetParameter        (GLenum         target,
                                         const GLfloat* value);
            void    SetParameter        (GLenum         target,
                                         const GLint  * value);
            void    SetParameter        (GLenum         target,
                                         const GLuint * value);

private:

    GLuint  m_nTexture          = std::numeric_limits<GLuint>::max();
    GLenum  m_eTextureTarget    = GL_TEXTURE_2D;
    GLenum  m_eInternalFormat   = GL_RGBA;
    GLsizei m_nWidth            = 0;
    GLsizei m_nHeight           = 0;
};

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

using texture = base_texture;

}


#include <qx/gl/texture.inl>
