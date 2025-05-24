/**

    @file      buffer_base.h
    @author    Khrapov
    @date      19.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/ibuffer.h>
#include <qx/typedefs.h>

namespace qx
{

/**

    @class   buffer_base
    @brief   Base OpenGL buffer object class
    @author  Khrapov
    @date    10.07.2020

**/
class buffer_base : public IBuffer
{
public:
    virtual ~buffer_base();

    QX_DECL_IBUFFER

    /**
        @brief Defines a barrier ordering memory transactions
    **/
    virtual void MemBarrier();

    /**
        @brief Allocate memory for the buffer
        @param nSize  - data size
        @param pData  - data pointer
        @param eUsage - the expected usage pattern of the data store
    **/
    virtual void Allocate(GLsizeiptr nSize, const void* pData = nullptr, GLenum eUsage = GL_DYNAMIC_DRAW);

    /**
        @brief Update buffer
        @param pData   - data pointer
        @param nSize   - data size
        @param nOffset - offset from the buffer beginning
    **/
    virtual void Update(const void* pData, GLsizeiptr nSize, GLintptr nOffset = 0);

protected:
    /**
        @brief  Get buffer type
        @retval - buffer type
    **/
    virtual GLenum GetBufferType() const = 0;

    /**
        @brief  Get buffer type barrier bit
        @retval - buffer type barrier bit
    **/
    virtual GLbitfield GetBarrierBit() const = 0;

private:
    GLuint m_nBuffer = std::numeric_limits<GLuint>::max();
};

#define QX_DECL_BUFFER_BASE                            \
    virtual GLenum     GetBufferType() const override; \
    virtual GLbitfield GetBarrierBit() const override;

} // namespace qx

#include <qx/gl/buffer_base.inl>
