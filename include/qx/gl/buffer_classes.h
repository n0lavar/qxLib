//==============================================================================
//
//!\file                        buffer_classes.h
//
//!\brief       Contains QX_DEFINE_BUFFER_CLASSES macro
//!\details     ~
//
//!\author      Khrapov
//!\date        13.01.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

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