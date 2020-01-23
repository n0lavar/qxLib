//============================================================================
//
//!\file                       noncopyble.h
//
//!\brief       Contains noncopyble class
//!\details     ~
//
//!\author      Khrapov
//!\date        16.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

namespace qx
{

//============================================================================
//
//!\class                       noncopyble
//
//!\brief   Forbid object copy and move
//!\details Used for pretty all opengl classes
//
//!\author  Khrapov
//!\date    16.01.2020
//
//============================================================================
class noncopyble
{
protected:
                        noncopyble  (void)                  = default;
                        ~noncopyble (void)                  = default;
                        noncopyble  (noncopyble&&)          = default;
          noncopyble&   operator=   (noncopyble&&)          = default;

                        noncopyble  (const noncopyble&)     = delete;
    const noncopyble&   operator=   (const noncopyble&)     = delete;
};

}