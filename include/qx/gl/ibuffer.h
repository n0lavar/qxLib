/**

    @file      ibuffer.h
    @brief     Contains qx::IBuffer interface
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
    @details ~

    @author  Khrapov
    @date    22.01.2020

**/
class IBuffer
{
public:
    /**
        @brief IBuffer object destructor
    **/
    virtual ~IBuffer(void) = default;

    /**
        @brief Generate buffer object
    **/
    virtual void Generate(void) = 0;

    /**
        @brief Bind a named buffer object
    **/
    virtual void Bind(void) const = 0;

    /**
        @brief Unbind a named buffer object
    **/
    virtual void Unbind(void) const = 0;

    /**
        @brief  Get the object's name - the reference to the object
        @retval - the object's name
    **/
    virtual GLuint GetBufferName(void) const = 0;

    /**
        @brief  Is this buffer generated
        @retval - true is generated
    **/
    virtual bool IsGenerated(void) const = 0;
};

#define QX_DECL_IBUFFER                                \
    virtual void   Generate(void) override;            \
    virtual void   Bind(void) const override;          \
    virtual void   Unbind(void) const override;        \
    virtual GLuint GetBufferName(void) const override; \
    virtual bool   IsGenerated(void) const override;

} // namespace qx
