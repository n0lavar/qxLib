//==============================================================================
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
//==============================================================================
#pragma once

#include <qx/typedefs.h>
#include <qx/gl/buffer_classes.h>
#include <qx/gl/ibuffer.h>

namespace qx
{

//==============================================================================
//
//!\class                   qx::buffer_base<COPYBLE>
//
//!\brief   Base OpenGL buffer object class
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
template<bool COPYBLE>
class buffer_base : public IBuffer
{
public:

    friend class buffer_base;

    virtual             ~buffer_base        (void);
    virtual void        Generate            (void)          override;
    virtual void        Delete              (void)          override;
    virtual void        Bind                (void) const    override;
    virtual void        Unbind              (void) const    override;
    virtual GLuint      GetBufferName       (void) const    override;
    virtual bool        IsGenerated         (void) const    override;

    virtual void        MemBarrier          (void);

    virtual void        Update              (GLsizeiptr     nSize,
                                             const void   * pData,
                                             GLenum         eUsage = GL_DYNAMIC_DRAW);
    virtual void        UpdatePart          (GLintptr       nOffset,
                                             GLsizeiptr     nSize,
                                             const void   * pData);

protected:

    template<class Derived>
            void        Assign              (const Derived& other) { m_nBuffer = other.m_nBuffer; }
    virtual GLenum      GetBufferType       (void) const = 0;
    virtual GLbitfield  GetBarrierBit       (void) const = 0;

private:

    GLuint m_nBuffer = std::numeric_limits<GLuint>::max();
};

template<bool COPYBLE>
inline GLuint buffer_base<COPYBLE>::GetBufferName (void) const { return m_nBuffer; }
template<bool COPYBLE>
inline bool   buffer_base<COPYBLE>::IsGenerated   (void) const { return m_nBuffer != std::numeric_limits<GLuint>::max(); }

}

#include <qx/gl/buffer_base.inl>
