//==============================================================================
//
//!\file                           ssbo.h
//
//!\brief       Contains qx::base_ssbo class
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
//!\class                 qx::base_ssbo
//
//!\brief   Base SSBO class
//!\details ~
//
//!\author  Khrapov
//!\date    18.01.2020
//
//==============================================================================
class base_ssbo : public buffer_binding_point_base
{
public:

                base_ssbo   (void) = default;

        GLint   GetMaxSize  (void) const;

protected:

    virtual GLenum      GetBufferType   (void) const override;
    virtual GLbitfield  GetBarrierBit   (void) const override;
};

inline GLenum base_ssbo::GetBufferType(void) const
{
    return GL_SHADER_STORAGE_BUFFER;
}
inline GLbitfield base_ssbo::GetBarrierBit(void) const
{
    return GL_SHADER_STORAGE_BARRIER_BIT;
}

using ssbo = base_ssbo;

}

#include <qx/gl/ssbo.inl>
