//============================================================================
//
//!\file                            ebo.h
//
//!\brief       
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
//!\class                            ebo
//
//!\brief   
//!\details ~
//
//!\author  Khrapov
//!\date    19.01.2020
//
//============================================================================
class ebo : public buffer_base
{
protected:
    virtual GLenum      GetBufferType(void) const override { return GL_ELEMENT_ARRAY_BUFFER; }
    virtual GLbitfield  GetBarrierBit(void) const override { return GL_ELEMENT_ARRAY_BARRIER_BIT; }
};

}