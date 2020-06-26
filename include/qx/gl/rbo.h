//==============================================================================
//
//!\file                            rbo.h
//
//!\brief       Contains rbo class
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

namespace qx::gl
{

//==============================================================================
//
//!\class                            rbo
//
//!\brief   Render buffer object class
//!\details ~
//
//!\author  Khrapov
//!\date    20.01.2020
//
//==============================================================================
class rbo : IBuffer
{
public:

    QX_NONCOPYBLE(rbo)

            rbo                     (void) = default;

    void    Init                    (GLsizei    nWidth,
                                     GLsizei    nHeight,
                                     size_t     nMultisamples = 0);

    virtual void    Generate        (void)          override;
    virtual void    Delete          (void)          override;
    virtual void    Bind            (void) const    override;
    virtual void    Unbind          (void) const    override;
    virtual GLuint  GetBufferName   (void) const    override;

private:

    GLuint m_nBuffer = UINT_EMPTY_VALUE;
};

inline GLuint rbo::GetBufferName(void) const { return m_nBuffer; }

}

#include <qx/gl/rbo.inl>
