//==============================================================================
//
//!\file                          texture.h
//
//!\brief       OpenGL textures classes: texture and copyble_texture
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

#include <memory>

namespace qx
{

//==============================================================================
//
//!\class                    base_texture<COPYBLE>
//
//!\brief   Base texture class. Use texture or copyble_texture
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
template<bool COPYBLE>
class base_texture : public IBuffer
{
public:

    friend class base_texture;

                    base_texture        (void) = default;
    virtual         ~base_texture       (void);

    virtual void    Generate            (void)          override;
    virtual void    Delete              (void)          override;
    virtual void    Bind                (void) const    override;
    virtual void    Unbind              (void) const    override;
    virtual GLuint  GetBufferName       (void) const    override;
    virtual bool    IsGenerated         (void) const    override;

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

protected:

    template<class Derived>
            void    Assign              (const Derived& other);

private:

    GLuint  m_nTexture          = UINT_EMPTY_VALUE;
    GLenum  m_eTextureTarget    = GL_TEXTURE_2D;
    GLsizei m_nWidth            = 0;
    GLsizei m_nHeight           = 0;
};

template<bool COPYBLE>
inline GLuint  base_texture<COPYBLE>::GetBufferName (void) const { return m_nTexture; }
template<bool COPYBLE>
inline bool    base_texture<COPYBLE>::IsGenerated   (void) const { return m_nTexture != UINT_EMPTY_VALUE; };
template<bool COPYBLE>
inline GLsizei base_texture<COPYBLE>::GetWidth      (void) const { return m_nWidth;   }
template<bool COPYBLE>
inline GLsizei base_texture<COPYBLE>::GetHeight     (void) const { return m_nHeight;  }

QX_DEFINE_BUFFER_CLASSES(texture)

using ptr_texture = std::unique_ptr<texture>;

}


#include <qx/gl/texture.inl>
