//============================================================================
//
//!\file                       ubo.h
//
//!\brief       Uniform buffer object class
//!\details     ~
//
//!\author      Khrapov
//!\date        9.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <qx/gl/buffer_base.h>

namespace qx::gl
{

//============================================================================
//
//!\class                       ubo
//
//!\brief   Uniform buffer object
//!\details UBO can be used to share uniforms between different shader programs,
//          as well as quickly change between sets of uniforms for the same program object
//
//!\author  Khrapov
//!\date    9.01.2020
//
//============================================================================
class ubo : public buffer_base
{
public:
            ubo             (void) = default;
            ubo             (GLsizeiptr szUBO,
                             GLuint     nBindingPoint);
    void    Init            (GLsizeiptr szUBO,
                             GLuint     nBindingPoint);

protected:
    virtual GLenum      GetBufferType   (void) const override { return GL_UNIFORM_BUFFER;       }
    virtual GLbitfield  GetBarrierBit   (void) const override { return GL_UNIFORM_BARRIER_BIT;  }   // not shure
};

}

#include <qx/gl/ubo.inl>
