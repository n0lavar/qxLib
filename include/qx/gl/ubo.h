/**

    @file      ubo.h
    @brief     Contains qx::base_ubo class
    @author    Khrapov
    @date      9.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/buffer_binding_point_base.h>

namespace qx
{

/**

    @class   base_ubo
    @brief   Base UBO class
    @details UBO can be used to share uniforms between different shader programs,
             as well as quickly change between sets of uniforms for
             the same program object

    @author  Khrapov
    @date    10.07.2020

**/
class base_ubo : public buffer_binding_point_base
{
public:
    /**
        @brief base_ubo object constructor
    **/
    base_ubo(void) = default;

    /**
        @brief  Get max UBO size
        @retval - max UBO size
    **/
    GLint GetMaxSize(void) const;

protected:
    QX_DECL_BUFFER_BASE

private:
    GLuint m_nBindingPoint = std::numeric_limits<GLuint>::max();
};


using ubo = base_ubo;

} // namespace qx

#include <qx/gl/ubo.inl>
