//==============================================================================
//
//!\file                            rbo.h
//
//!\brief       Render buffer object classes: rbo and copyble_rbo
//!\details     ~
//
//!\author      Khrapov
//!\date        20.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/typedefs.h>
#include <qx/gl/ibuffer.h>

namespace qx
{

//==============================================================================
//
//!\class                    qx::base_rbo<COPYBLE>
//
//!\brief   Base RBO class. Use rbo or copyble_rbo
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
template<bool COPYBLE>
class base_rbo : IBuffer
{
public:

    friend class base_rbo;

            void    Init            (GLsizei    nWidth,
                                     GLsizei    nHeight,
                                     GLsizei    nMultisamples = 0);

    virtual void    Generate        (void)          override;
    virtual void    Delete          (void)          override;
    virtual void    Bind            (void) const    override;
    virtual void    Unbind          (void) const    override;
    virtual GLuint  GetBufferName   (void) const    override;
    virtual bool    IsGenerated     (void) const    override;

protected:

    template<class Derived>
            void    Assign          (const Derived& other);

private:

    GLuint m_nBuffer = UINT_EMPTY_VALUE;
};

template<bool COPYBLE>
inline GLuint base_rbo<COPYBLE>::GetBufferName (void) const { return m_nBuffer; }
template<bool COPYBLE>
inline bool   base_rbo<COPYBLE>::IsGenerated   (void) const { return m_nBuffer != UINT_EMPTY_VALUE; }
template<bool COPYBLE>
template<class Derived>
inline void    base_rbo<COPYBLE>::Assign(const Derived& other) { m_nBuffer = other.m_nBuffer; }

QX_DEFINE_BUFFER_CLASSES(rbo)

}

#include <qx/gl/rbo.inl>
