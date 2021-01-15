//==============================================================================
//
//!\file                          ibuffer.h
//
//!\brief       Contains IBuffer interface
//!\details     ~
//
//!\author      Khrapov
//!\date        22.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <glew.h>

namespace qx
{

//==============================================================================
//
//!\class                        qx::IBuffer
//
//!\brief   OpenGL buffer interface
//!\details ~
//
//!\author  Khrapov
//!\date    22.01.2020
//
//==============================================================================
class IBuffer
{
public:
    virtual void    Generate        (void)          = 0;
    virtual void    Delete          (void)          = 0;
    virtual void    Bind            (void) const    = 0;
    virtual void    Unbind          (void) const    = 0;
    virtual GLuint  GetBufferName   (void) const    = 0;
    virtual bool    IsGenerated     (void) const    = 0;
};

}
