//==============================================================================
//
//!\file                       ubo.h
//
//!\brief       Uniform buffer object classes: ubo and copyble_ubo
//!\details     ~
//
//!\author      Khrapov
//!\date        9.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/gl/buffer_binding_point_base.h>

namespace qx
{

//==============================================================================
//
//!\class                    qx::base_ubo<COPYBLE>
//
//!\brief   Base UBO class. Use ubo or copyble_ubo
//!\details UBO can be used to share uniforms between different shader programs,
//          as well as quickly change between sets of uniforms for the same program object
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
template<bool COPYBLE>
class base_ubo : public buffer_binding_point_base<COPYBLE>
{
public:

            base_ubo        (void) = default;

    GLint   GetMaxSize      (void)  const;

protected:

    virtual GLenum      GetBufferType   (void) const override { return GL_UNIFORM_BUFFER;       }
    virtual GLbitfield  GetBarrierBit   (void) const override { return GL_UNIFORM_BARRIER_BIT;  }

private:

    GLuint m_nBindingPoint = std::numeric_limits<GLuint>::max();
};

QX_DEFINE_BUFFER_CLASSES(ubo)

}

#include <qx/gl/ubo.inl>
