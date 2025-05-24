/**

    @file      ibuffer.h
    @author    Khrapov
    @date      22.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <glew.h>

namespace qx
{

/**

    @class   IBuffer
    @brief   OpenGL buffer interface
    @author  Khrapov
    @date    22.01.2020

**/
class IBuffer
{
public:
    virtual ~IBuffer() = default;

    /**
        @brief Generate buffer object
    **/
    virtual void Generate() = 0;

    /**
        @brief Bind a named buffer object
    **/
    virtual void Bind() const = 0;

    /**
        @brief Unbind a named buffer object
    **/
    virtual void Unbind() const = 0;

    /**
        @brief  Get the object's name - the reference to the object
        @retval - the object's name
    **/
    virtual GLuint GetBufferName() const = 0;

    /**
        @brief  Is this buffer generated
        @retval - true is generated
    **/
    virtual bool IsGenerated() const = 0;
};

#define QX_DECL_IBUFFER                            \
    virtual void   Generate() override;            \
    virtual void   Bind() const override;          \
    virtual void   Unbind() const override;        \
    virtual GLuint GetBufferName() const override; \
    virtual bool   IsGenerated() const override;

} // namespace qx
