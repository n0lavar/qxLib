//============================================================================
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
//============================================================================
#pragma once

#include <qx/other/typedefs.h>
#include <qx/gl/iBuffer.h>

namespace qx::gl
{

//============================================================================
//
//!\class                          texture
//
//!\brief   OpenGL texture
//!\details ~
//
//!\author  Khrapov
//!\date    23.01.2020
//
//============================================================================
class texture : iBuffer
{
public:
                    texture         (void) = default;
                    ~texture        (void);
            void    Init            (GLenum         target,
                                     GLint          level,
                                     GLint          internalformat,
                                     GLsizei        width,
                                     GLsizei        height,
                                     GLenum         format,
                                     GLenum         type,
                                     const void   * data    = nullptr);

    virtual void    Generate        (void)          override;
    virtual void    Delete          (void)          override;
    virtual void    Bind            (void) const    override;
    virtual void    Unbind          (void) const    override;
    virtual GLuint  GetBufferName   (void) const    override;

            GLsizei GetWidth        (void) const;
            GLsizei GetHeight       (void) const;

    template<typename T>
            void    SetParameter    (GLenum         target,
                                     T              value);

private:
    GLuint  m_nTexture      = UINT_EMPTY_VALUE;
    GLenum  m_eTextureType  = GL_TEXTURE_2D;
    GLsizei m_nWidth        = 0;
    GLsizei m_nHeight       = 0;
};

inline GLuint   texture::GetBufferName  (void) const { return m_nTexture;   }
inline GLsizei  texture::GetWidth       (void) const { return m_nWidth;     }
inline GLsizei  texture::GetHeight      (void) const { return m_nHeight;    }

}

#include <qx/gl/texture.inl>