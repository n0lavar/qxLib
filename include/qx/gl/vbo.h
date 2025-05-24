/**

    @file      vbo.h
    @author    Khrapov
    @date      19.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/buffer_base.h>

namespace qx
{

/**

    @class   base_vbo
    @brief   Base VBO class
    @author  Khrapov
    @date    10.07.2020

**/
class base_vbo : public buffer_base
{
public:
    base_vbo() = default;

protected:
    QX_DECL_BUFFER_BASE
};

using vbo = base_vbo;

} // namespace qx

#include <qx/gl/vbo.inl>
