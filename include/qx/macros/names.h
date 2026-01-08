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
#define QX_LINE_NAME(prefix) QX_JOIN(prefix, __LINE__)

/**
    @brief A helper to avoid duplication when converting c libs constants to string literals
    @param name - c constant
    @code
    static const char* GlfwErrorCodeToString(int nErrorCode)
    {
        switch (nErrorCode)
        {
            QX_C_CONSTANT_CASE(GLFW_NO_ERROR);
            QX_C_CONSTANT_CASE(GLFW_NOT_INITIALIZED);
            QX_C_CONSTANT_CASE(GLFW_NO_CURRENT_CONTEXT);
            QX_C_CONSTANT_CASE(GLFW_INVALID_ENUM);
            QX_C_CONSTANT_CASE(GLFW_INVALID_VALUE);
            QX_C_CONSTANT_CASE(GLFW_OUT_OF_MEMORY);
            QX_C_CONSTANT_CASE(GLFW_API_UNAVAILABLE);
            QX_C_CONSTANT_CASE(GLFW_VERSION_UNAVAILABLE);
            QX_C_CONSTANT_CASE(GLFW_PLATFORM_ERROR);
            QX_C_CONSTANT_CASE(GLFW_FORMAT_UNAVAILABLE);
            QX_C_CONSTANT_CASE(GLFW_NO_WINDOW_CONTEXT);
        }

        return "GLFW_UNKNOWN_ERROR";
    }
    @endcode
**/
#define QX_C_CONSTANT_CASE(name) \
    case name:                   \
        return #name

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
    ((void)sizeof(&className::methodName), QX_STRINGIFY(className) "::" QX_STRINGIFY(methodName))
