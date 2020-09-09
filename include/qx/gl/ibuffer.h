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

/*
    define "name" and "copyble_name" buffer classes

    since we want to use the advantages of RAII to encapsulate OpenGL generate and delete functions,
    and we want to create copies of the buffer to be inserted into the render queue,
    we need two different classes: the regular one, which controls the lifetime of the object and cannot be copied,
    and the copies class with an empty Delete method

    "name" is storage non-copyble class with enabled Delete() method (and destructor),
    should be used as unique or shared pointer

    "copyble_name" can be used as copy of "name" class, it won't be destructed
*/
#define QX_DEFINE_BUFFER_CLASSES(name)                                                              \
class name : public base_ ## name<false>                                                            \
{                                                                                                   \
public:                                                                                             \
                        name                (void)                              = default;          \
                        name                (name&&)                noexcept    = default;          \
    name&               operator=           (name&&)                noexcept    = default;          \
                        name                (const name&)                       = delete;           \
    name&               operator=           (const name&)                       = delete;           \
};                                                                                                  \
                                                                                                    \
class copyble_ ## name : public base_ ## name<true>                                                 \
{                                                                                                   \
public:                                                                                             \
                        copyble_ ## name    (void)                              = default;          \
                        copyble_ ## name    (copyble_ ## name&&)     noexcept   = default;          \
    copyble_ ## name&   operator=           (copyble_ ## name&&)     noexcept   = default;          \
                        copyble_ ## name    (const copyble_ ## name&)           = default;          \
    copyble_ ## name&   operator=           (const copyble_ ## name&)           = default;          \
                                                                                                    \
                        copyble_ ## name    (const name& other) { Assign(other); }                  \
    copyble_ ## name&   operator=           (const name& other) { Assign(other); return *this; }    \
};

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
