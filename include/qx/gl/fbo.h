//==============================================================================
//
//!\file                            fbo.h
//
//!\brief       Contains qx::base_fbo class
//!\details     ~
//
//!\author      Khrapov
//!\date        20.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/gl/rbo.h>
#include <qx/gl/texture.h>

namespace qx
{

//==============================================================================
//
//!\class                    qx::base_fbo
//
//!\brief   Base FBO class
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
class base_fbo : public IBuffer
{
public:

    friend class base_fbo;

    virtual                 ~base_fbo       (void);

    virtual void            Generate        (void)                                   override;
    virtual void            Delete          (void)                                   override;
    virtual void            Bind            (void)                          const    override;
    virtual void            Unbind          (void)                          const    override;
    virtual GLuint          GetBufferName   (void)                          const    override;
    virtual bool            IsGenerated     (void)                          const    override;

            void            SetTarget       (GLenum                 target);

            void            AttachRBO       (const base_rbo       & rbo);

            void            AttachTexture2D (GLenum                 attachment,
                                             const base_texture   & texture,
                                             GLint                  nMipmapLevel = 0);
            void            AttachTexture   (GLenum                 attachment,
                                             const base_texture   & texture,
                                             GLint                  nMipmapLevel = 0);
            void            CheckStatus     (void)                          const;

private:

    GLuint  m_nBuffer   = std::numeric_limits<GLuint>::max();
    GLenum  m_nTarget   = GL_FRAMEBUFFER;
};

inline GLuint base_fbo::GetBufferName(void) const
{
    return m_nBuffer;
}
inline bool base_fbo::IsGenerated(void) const
{
    return m_nBuffer != std::numeric_limits<GLuint>::max();
}

using fbo = base_fbo;

}

#include <qx/gl/fbo.inl>
