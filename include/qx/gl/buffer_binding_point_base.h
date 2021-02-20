//==============================================================================
//
//!\file                  buffer_binding_point_base.h
//
//!\brief       Contains buffer_binding_point_base class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.02.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/gl/buffer_base.h>

namespace qx
{

//==============================================================================
//
//!\class          qx::buffer_binding_point_base<COPYBLE>
//
//!\brief   Base class for buffers with binding points
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================

template <bool COPYBLE>
class buffer_binding_point_base : public buffer_base<COPYBLE>
{
public:

    virtual void    BindBase    (GLuint         nIndex);
};

}

#include <qx/gl/buffer_binding_point_base.inl>