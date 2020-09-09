//==============================================================================
//
//!\file                            vbo.h
//
//!\brief       Vertex buffer object classes: vbo and copyble_vbo
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
//!\class                    qx::base_vbo<COPYBLE>
//
//!\brief   Base VBO class. Use vbo or copyble_vbo
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
template<bool COPYBLE>
class base_vbo : public buffer_base<COPYBLE>
{
public:

                        base_vbo     (void) = default;

protected:

    virtual GLenum      GetBufferType(void) const override { return GL_ARRAY_BUFFER; }
    virtual GLbitfield  GetBarrierBit(void) const override { return GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT; }
};

QX_DEFINE_BUFFER_CLASSES(vbo)

}
