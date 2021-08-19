/**

    @file      buffer_base.h
    @brief     Contains qx::buffer_base class
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

    @class   qx::buffer_base

    @brief   Base OpenGL buffer object class
    @details ~

    @author  Khrapov
    @date    10.07.2020

**/
class buffer_base : public IBuffer
{
public:
    /**
        @brief buffer_base object destructor
    **/
    virtual ~buffer_base(void);

    QX_DECL_IBUFFER

    /**
        @brief Defines a barrier ordering memory transactions
    **/
    virtual void MemBarrier(void);

    /**
        @brief Update the whole buffer
        @param nSize  - data size
        @param pData  - data pointer
        @param eUsage - the expected usage pattern of the data store
    **/
    virtual void Update(
        GLsizeiptr  nSize,
        const void* pData,
        GLenum      eUsage = GL_DYNAMIC_DRAW);

    /**
        @brief Update buffer part
        @param nOffset - offset from the buffer beginning
        @param nSize   - data size
        @param pData   - data pointer
    **/
    virtual void UpdatePart(
        GLintptr    nOffset,
        GLsizeiptr  nSize,
        const void* pData);

protected:
    /**
        @brief  Get buffer type
        @retval - buffer type
    **/
    virtual GLenum GetBufferType(void) const = 0;

    /**
        @brief  Get buffer type barrier bit
        @retval - buffer type barrier bit
    **/
    virtual GLbitfield GetBarrierBit(void) const = 0;

private:
    GLuint m_nBuffer = std::numeric_limits<GLuint>::max();
};

#define QX_DECL_BUFFER_BASE                                \
    virtual GLenum     GetBufferType(void) const override; \
    virtual GLbitfield GetBarrierBit(void) const override;

} // namespace qx

#include <qx/gl/buffer_base.inl>
