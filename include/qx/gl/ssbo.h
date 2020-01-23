//============================================================================
//
//!\file                           ssbo.h
//
//!\brief       Contains ssbo class
//!\details     ~
//
//!\author      Khrapov
//!\date        9.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <buffer_base.h>

namespace qx::gl
{

//============================================================================
//
//!\class                           ssbo
//
//!\brief   Shader Storage Buffer Object class
//!\details ~
//
//!\author  Khrapov
//!\date    18.01.2020
//
//============================================================================
class ssbo : public buffer_base
{
public:
                        ssbo            (void) { }
                        ssbo            (GLuint             nBindingPoint, 
                                         GLsizeiptr         nSize, 
                                         const void       * pData = NULL);
    virtual void        Init            (GLuint             nBindingPoint, 
                                         GLsizeiptr         nSize, 
                                         const void       * pData = NULL);

protected:
    virtual GLenum      GetBufferType   (void) const override { return GL_SHADER_STORAGE_BUFFER;        }
    virtual GLbitfield  GetBarrierBit   (void) const override { return GL_SHADER_STORAGE_BARRIER_BIT;   }
};

}

#include <ssbo.inl>
