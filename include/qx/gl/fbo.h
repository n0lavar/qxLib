//==============================================================================
//
//!\file                            fbo.h
//
//!\brief       Contains fbo class
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

namespace qx::gl
{

//==============================================================================
//
//!\class                            fbo
//
//!\brief   Frame buffer object class
//!\details ~
//
//!\author  Khrapov
//!\date    20.01.2020
//
//==============================================================================
class fbo : IBuffer
{
public:

    QX_NONCOPYBLE(fbo)

                    fbo             (void) = default;
    virtual         ~fbo            (void);

    virtual void    Generate        (void)                                   override;
    virtual void    Delete          (void)                                   override;
    virtual void    Bind            (void)                          const    override;
    virtual void    Unbind          (void)                          const    override;
    virtual GLuint  GetBufferName   (void)                          const    override;

            void    Bind            (GLenum             target);
            void    AttachRBO       (const rbo        & rbo);
            void    AttachTexture   (const texture    & texture,
                                     GLenum             texTarget);
            void    CheckStatus     (void)                          const;

private:

    GLuint  m_nBuffer   = UINT_EMPTY_VALUE;
};

inline GLuint fbo::GetBufferName(void) const { return m_nBuffer; }

}

#include <qx/gl/fbo.inl>
