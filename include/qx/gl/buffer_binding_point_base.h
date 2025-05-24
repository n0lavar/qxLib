/**

    @file      buffer_binding_point_base.h
    @author    Khrapov
    @date      10.07.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/buffer_base.h>

namespace qx
{

/**

    @class   buffer_binding_point_base
    @brief   Base class for buffers with binding points
    @author  Khrapov
    @date    10.07.2020

**/
class buffer_binding_point_base : public buffer_base
{
public:
    /**
        @brief Bind a buffer object to an indexed buffer target from shader
        @param nIndex - index
    **/
    virtual void BindBase(GLuint nIndex);
};

} // namespace qx

#include <qx/gl/buffer_binding_point_base.inl>
