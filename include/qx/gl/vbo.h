//==============================================================================
//
//!\file                            vbo.h
//
//!\brief       Contains qx::base_vbo class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/gl/buffer_base.h>

namespace qx
{

//==============================================================================
//
//!\class                    qx::base_vbo
//
//!\brief   Base VBO class
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
class base_vbo : public buffer_base
{
public:

                        base_vbo     (void) = default;

protected:

    virtual GLenum      GetBufferType(void) const override;
    virtual GLbitfield  GetBarrierBit(void) const override;
};

inline GLenum base_vbo::GetBufferType(void) const
{
    return GL_ARRAY_BUFFER;
}
inline GLbitfield base_vbo::GetBarrierBit(void) const
{
    return GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT;
}

using vbo = base_vbo;

}
