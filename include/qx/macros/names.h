/**

    @file      names.h
    @author    Khrapov
    @date      24.07.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/macros/common.h>

/**
    @def   QX_STRINGIFY
    @brief Macro can be used to turn any text in your code into a string,
           but only the exact text between the parentheses
           There are no variable dereferencing or macro substitutions or any other sort of thing done.
    @param name - name to convert to the string
**/
#define QX_STRINGIFY(name) #name

/**
    @def   QX_LINE_NAME
    @brief Do magic! Creates a unique name using the line number
    @param prefix - name prefix
**/
#define QX_LINE_NAME(prefix) _QX_JOIN(prefix, __LINE__)

/**
    @brief Get a method name (without className::), while statically verifying that the method exists
    @param className  - class name
    @param methodName - method name
**/
#define QX_METHOD_NAME(className, methodName) \
    ((void)sizeof(&className::methodName), QX_STRINGIFY(methodName)))

/**
    @brief Get a full method name (className::methodName), while statically verifying that the method exists
    @param className  - class name
    @param methodName - method name
**/
#define QX_FULL_METHOD_NAME(className, methodName) \
    ((void)sizeof(&className::methodName), QX_STRINGIFY(className) "::" QX_STRINGIFY(methodName)))
