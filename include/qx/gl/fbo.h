//==============================================================================
//
//!\file                            fbo.h
//
//!\brief       Frame buffer object classes: fbo and copyble_fbo
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
//!\class                    qx::base_fbo<COPYBLE>
//
//!\brief   Base FBO class. Use fbo or copyble_fbo
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
template<bool COPYBLE>
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

            void            Bind            (GLenum             target);

    template<bool COPYBLE_RBO>
            void            AttachRBO       (const base_rbo<COPYBLE_RBO>& rbo);

    template<bool COPYBLE_TEXTURE>
            void            AttachTexture2D (GLenum             attachment,
                                             GLenum             texTarget,
                                             const base_texture<COPYBLE_TEXTURE>& texture);
    template<bool COPYBLE_TEXTURE>
            void            AttachTexture   (GLenum             attachment,
                                             const base_texture<COPYBLE_TEXTURE>& texture);
            void            CheckStatus     (void)                          const;

protected:

    template<class Derived>
            void            Assign          (const Derived    & other);

private:

    GLuint  m_nBuffer   = UINT_EMPTY_VALUE;
};

template<bool COPYBLE>
inline GLuint base_fbo<COPYBLE>::GetBufferName (void) const { return m_nBuffer; }
template<bool COPYBLE>
inline bool  base_fbo<COPYBLE>::IsGenerated (void) const { return m_nBuffer != UINT_EMPTY_VALUE; };
template<bool COPYBLE>
template<class Derived>
inline void  base_fbo<COPYBLE>::Assign(const Derived& other) { m_nBuffer = other.m_nBuffer; }

QX_DEFINE_BUFFER_CLASSES(fbo)

}

#include <qx/gl/fbo.inl>
