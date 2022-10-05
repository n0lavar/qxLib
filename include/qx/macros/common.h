/**

    @file      common.h
    @brief     Useful macros
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

/**
    @def     QX_EMPTY_MACRO
    @brief   Placeholder for disabled macros
    @details Has no effect and work correctly with "if else"
**/
#define QX_EMPTY_MACRO ((void*)0)

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
#define QX_LINE_NAME(prefix)          _QX_JOIN(prefix, __LINE__)
#define _QX_JOIN(symbol1, symbol2)    _QX_DO_JOIN(symbol1, symbol2)
#define _QX_DO_JOIN(symbol1, symbol2) symbol1##symbol2

namespace qx::detail
{

constexpr const char* last_slash(const char* str)
{
    const char* pszLastSlash = str;
    while (str && *str != '\0')
    {
        if (*str == '\\' || *str == '/')
            pszLastSlash = str;

        str++;
    }
    return pszLastSlash + 1;
}

} // namespace qx::detail

/**
    @def   QX_SHORT_FILE
    @brief Cuts full absolute path to the file name only
           ex: "C:\folder1\foler2\file.h"  =>  "file.h"
**/
#define QX_SHORT_FILE qx::detail::last_slash(__FILE__)

/**
    @def   QX_SINGLE_ARGUMENT
    @brief Let macro param containing commas work fine
           "#define FOO(type, name) type name"
           FOO(QX_SINGLE_ARGUMENT(std::map<int, int>), map_var);
    @param ... - param containing commas
**/
#define QX_SINGLE_ARGUMENT(...) __VA_ARGS__

/**
    @brief Macro for generating "enum class"-like class or struct with additional data/methods
    @note  Default value is one corresponds to 0
    @param TypeName - class/struct name
    @param ...      - enum values
**/
#define QX_ENUM_CLASS(TypeName, ...)                                               \
public:                                                                            \
    enum TypeName##Internal { __VA_ARGS__ };                                       \
                                                                                   \
    TypeName##Internal _eInternal = static_cast<TypeName##Internal>(0);            \
                                                                                   \
    TypeName() noexcept = default;                                                 \
                                                                                   \
    TypeName(const TypeName##Internal& eInternal) noexcept : _eInternal(eInternal) \
    {                                                                              \
    }                                                                              \
                                                                                   \
    TypeName& operator=(const TypeName##Internal& eInternal) noexcept              \
    {                                                                              \
        _eInternal = eInternal;                                                    \
        return *this;                                                              \
    }                                                                              \
                                                                                   \
    bool operator==(const TypeName##Internal& eInternal) const noexcept            \
    {                                                                              \
        return _eInternal == eInternal;                                            \
    }                                                                              \
                                                                                   \
    bool operator!=(const TypeName##Internal& eInternal) const noexcept            \
    {                                                                              \
        return _eInternal != eInternal;                                            \
    }                                                                              \
                                                                                   \
    bool operator<(const TypeName##Internal& eInternal) const noexcept             \
    {                                                                              \
        return _eInternal < eInternal;                                             \
    }                                                                              \
                                                                                   \
    bool operator<=(const TypeName##Internal& eInternal) const noexcept            \
    {                                                                              \
        return _eInternal <= eInternal;                                            \
    }                                                                              \
                                                                                   \
    bool operator>(const TypeName##Internal& eInternal) const noexcept             \
    {                                                                              \
        return _eInternal > eInternal;                                             \
    }                                                                              \
                                                                                   \
    bool operator>=(const TypeName##Internal& eInternal) const noexcept            \
    {                                                                              \
        return _eInternal >= eInternal;                                            \
    }                                                                              \
                                                                                   \
    operator TypeName##Internal() const noexcept                                   \
    {                                                                              \
        return _eInternal;                                                         \
    }
