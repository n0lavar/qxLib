//==============================================================================
//
//!\file                          texture.h
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        23.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/typedefs.h>
#include <qx/gl/ibuffer.h>

namespace qx::gl
{

//==============================================================================
//
//!\class                          texture
//
//!\brief   OpenGL texture
//!\details ~
//
//!\author  Khrapov
//!\date    23.01.2020
//
//==============================================================================
class texture : public IBuffer
{
public:

    QX_NONCOPYBLE(texture)

                    texture             (void) = default;
                    ~texture            (void);

    virtual void    Generate            (void)          override;
    virtual void    Delete              (void)          override;
    virtual void    Bind                (void) const    override;
    virtual void    Unbind              (void) const    override;
    virtual GLuint  GetBufferName       (void) const    override;
            GLsizei GetWidth            (void) const;
            GLsizei GetHeight           (void) const;

            void    SetTarget           (GLenum         eTarget);
            void    Specify2DTexImage   (GLint          level,
                                         GLint          internalformat,
                                         GLsizei        width,
                                         GLsizei        height,
                                         GLenum         format,
                                         GLenum         type,
                                         const void*    pData   = nullptr,
                                         GLenum         eTarget = -1);
            void    Specify2DMultisample(GLsizei        nSamples,
  	                                     GLenum         eInternalformat,
  	                                     GLsizei        nWidth,
  	                                     GLsizei        nHeight,
  	                                     GLboolean      bFixedsamplelocations);
            void    GenerateMipmap      (void);

    template<typename T>
            void    SetParameter        (GLenum         target,
                                         T              value);

private:

    GLuint  m_nTexture          = UINT_EMPTY_VALUE;
    GLenum  m_eTextureTarget    = GL_TEXTURE_2D;
    GLsizei m_nWidth            = 0;
    GLsizei m_nHeight           = 0;
};

inline GLuint  texture::GetBufferName (void) const { return m_nTexture; }
inline GLsizei texture::GetWidth      (void) const { return m_nWidth;   }
inline GLsizei texture::GetHeight     (void) const { return m_nHeight;  }

}

#include <qx/gl/texture.inl>