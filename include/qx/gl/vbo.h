//============================================================================
//
//!\file                            vbo.h
//
//!\brief       Contains vbo class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <buffer_base.h>

namespace qx::gl
{

//============================================================================
//
//!\class                            vbo
//
//!\brief   Vertex buffer object class
//!\details ~
//
//!\author  Khrapov
//!\date    19.01.2020
//
//============================================================================
class vbo : public buffer_base
{
protected:
    virtual GLenum      GetBufferType(void) const override { return GL_ARRAY_BUFFER; }
    virtual GLbitfield  GetBarrierBit(void) const override { return GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT; }
};

}