//==============================================================================
//
//!\file                           ssbo.h
//
//!\brief       Shader storage buffer object classes: ssbo and copyble_ssbo
//!\details     ~
//
//!\author      Khrapov
//!\date        9.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/gl/buffer_base.h>

namespace qx
{

//==============================================================================
//
//!\class                 qx::base_ssbo<COPYBLE>
//
//!\brief   Base SSBO class. Use rbo or copyble_rbo
//!\details ~
//
//!\author  Khrapov
//!\date    18.01.2020
//
//==============================================================================
template<bool COPYBLE>
class base_ssbo : public buffer_base<COPYBLE>
{
public:

                        base_ssbo       (void) = default;
    virtual void        Init            (GLuint             nBindingPoint,
                                         GLsizeiptr         nSize,
                                         const void       * pData = nullptr);

protected:

    virtual GLenum      GetBufferType   (void) const override { return GL_SHADER_STORAGE_BUFFER;        }
    virtual GLbitfield  GetBarrierBit   (void) const override { return GL_SHADER_STORAGE_BARRIER_BIT;   }
};

QX_DEFINE_BUFFER_CLASSES(ssbo)

}

#include <qx/gl/ssbo.inl>
