//==============================================================================
//
//!\file                            ebo.h
//
//!\brief       Elemnt buffer object classes: ebo and copyble_ebo
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
//!\class                      base_ebo<COPYBLE>
//
//!\brief   Base EBO class. Use ebo or copyble_ebo
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
template<bool COPYBLE>
class base_ebo : public buffer_base<COPYBLE>
{
protected:

    virtual GLenum      GetBufferType(void) const override { return GL_ELEMENT_ARRAY_BUFFER; }
    virtual GLbitfield  GetBarrierBit(void) const override { return GL_ELEMENT_ARRAY_BARRIER_BIT; }
};

QX_DEFINE_BUFFER_CLASSES(ebo)

}
