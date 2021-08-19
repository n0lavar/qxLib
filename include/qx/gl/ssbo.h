/**

    @file      ssbo.h
    @brief     Contains qx::base_ssbo class
    @author    Khrapov
    @date      9.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/buffer_binding_point_base.h>

namespace qx
{

/**

    @class   qx::base_ssbo

    @brief   Base SSBO class
    @details ~

    @author  Khrapov
    @date    18.01.2020

**/
class base_ssbo : public buffer_binding_point_base
{
public:
    /**
        @brief base_ssbo object constructor
    **/
    base_ssbo(void) = default;

    /**
        @brief  Get max SSBO size
        @retval - max SSBO size
    **/
    GLint GetMaxSize(void) const;

protected:
    QX_DECL_BUFFER_BASE
};

using ssbo = base_ssbo;

} // namespace qx

#include <qx/gl/ssbo.inl>
