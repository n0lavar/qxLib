//==============================================================================
//
//!\file                       ubo.h
//
//!\brief       Contains qx::base_ubo class
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
//!\class                    qx::base_ubo
//
//!\brief   Base UBO class
//!\details UBO can be used to share uniforms between different shader programs,
//          as well as quickly change between sets of uniforms for the same program object
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
class base_ubo : public buffer_binding_point_base
{
public:

            base_ubo        (void) = default;

    GLint   GetMaxSize      (void)  const;

protected:

    virtual GLenum      GetBufferType   (void) const override;
    virtual GLbitfield  GetBarrierBit   (void) const override;

private:

    GLuint m_nBindingPoint = std::numeric_limits<GLuint>::max();
};

inline GLenum base_ubo::GetBufferType(void) const
{
    return GL_UNIFORM_BUFFER;
}
inline GLbitfield base_ubo::GetBarrierBit(void) const
{
    return GL_UNIFORM_BARRIER_BIT;
}

using ubo = base_ubo;

}

#include <qx/gl/ubo.inl>
