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
#include <qx/gl/iBuffer.h>

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

            void    SetTarget           (GLenum         eTarget);
            void    Specify2DTexImage   (GLint          level,
                                         GLint          internalformat,
                                         GLsizei        width,
                                         GLsizei        height,
                                         GLenum         format,
                                         GLenum         type,
                                         const void*    pData   = nullptr,
                                         GLenum         eTarget = -1);
            void    GenerateMipmap      (void);

    template<typename T>
            void    SetParameter    (GLenum         target,
                                     T              value);

private:

    GLuint  m_nTexture          = UINT_EMPTY_VALUE;
    GLenum  m_eTextureTarget    = GL_TEXTURE_2D;
};

inline GLuint   texture::GetBufferName  (void) const { return m_nTexture;   }

}

#include <qx/gl/texture.inl>