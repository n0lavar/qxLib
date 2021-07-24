//==============================================================================
//
//!\file                            ebo.h
//
//!\brief       Contains qx::base_ebo class
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
//!\class                    qx::base_ebo
//
//!\brief   Base EBO class
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
class base_ebo : public buffer_base
{
protected:

    virtual GLenum      GetBufferType(void) const override;
    virtual GLbitfield  GetBarrierBit(void) const override;
};

inline GLenum base_ebo::GetBufferType(void) const
{
    return GL_ELEMENT_ARRAY_BUFFER;
}
inline GLbitfield base_ebo::GetBarrierBit(void) const
{
    return GL_ELEMENT_ARRAY_BARRIER_BIT;
}

using ebo = base_ebo;

}
