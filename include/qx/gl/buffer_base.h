//============================================================================
//
//!\file                     buffer_base.h
//
//!\brief       Contains buffer_base class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <iBuffer.h>
#include <useful_macros.h>
#include <typedefs.h>

namespace qx::gl
{

//============================================================================
//
//!\class                     buffer_base
//
//!\brief   Base OpenGL buffer object class
//!\details ~
//
//!\author  Khrapov
//!\date    19.01.2020
//
//============================================================================
class buffer_base : iBuffer
{
public:
                        buffer_base         (void) { }
    virtual             ~buffer_base        (void);
    virtual void        Generate            (void)          override;
    virtual void        Delete              (void)          override;
    virtual void        Bind                (void) const    override;
    virtual void        Unbind              (void) const    override;
    virtual void        BindBase            (GLuint         nIndex);
    virtual void        MemBarrier          (void);

    virtual void        Update              (GLsizeiptr     nSize,
                                             const void   * pData,
                                             GLenum         eUsage = GL_DYNAMIC_DRAW);
    virtual void        UpdatePart          (GLintptr       nOffset,
                                             GLsizeiptr     nSize,
                                             const void   * pData);

protected:
    virtual GLenum      GetBufferType       (void) const = 0;
    virtual GLbitfield  GetBarrierBit       (void) const = 0;

    virtual GLuint      GetBufferName       (void) const    override;

private:
    GLuint m_nBuffer = UINT_EMPTY_VALUE;
};


inline GLuint buffer_base::GetBufferName(void) const { return m_nBuffer; }

}

#include <buffer_base.inl>
