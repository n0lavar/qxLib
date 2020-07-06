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
class fbo : public IBuffer
{
public:

    QX_NONCOPYBLE(fbo)

                            fbo             (void) = default;
    virtual                 ~fbo            (void);

    virtual void            Generate        (void)                                   override;
    virtual void            Delete          (void)                                   override;
    virtual void            Bind            (void)                          const    override;
    virtual void            Unbind          (void)                          const    override;
    virtual GLuint          GetBufferName   (void)                          const    override;

            void            Bind            (GLenum             target);
            void            AttachRBO       (const rbo        & rbo);
            void            AttachTexture   (GLenum             attachment,
                                             GLenum             texTarget,
                                             const texture    & texture);
            void            CheckStatus     (void)                          const;
    const qx::gl::texture & GetTexture      (void)                          const;

protected:

    qx::gl::texture       & GetTextureRef   (void);

private:

    GLuint          m_nBuffer   = UINT_EMPTY_VALUE;
    qx::gl::texture m_Texture;
};

inline GLuint                   fbo::GetBufferName  (void) const { return m_nBuffer; }
inline qx::gl::texture        & fbo::GetTextureRef  (void)       { return m_Texture; }
inline const qx::gl::texture  & fbo::GetTexture     (void) const { return m_Texture; }

}

#include <qx/gl/fbo.inl>
