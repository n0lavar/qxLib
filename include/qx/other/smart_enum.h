//============================================================================
//
//!\file                         smart_enum.h
//
//!\brief       Smart enum macro definition
//!\details     Smart macro allows you to use ToString(), FromString() and increment
//              functions. 
//              Note that the numbering of objects begins with first_elem + 1
//
//!\author      Khrapov
//!\date        16.10.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <optional>
#include <unordered_map>
#include <qxstring.h>

#define SMART_ENUM(name, first_elem, ...)                                                                               \
    enum class name                                                                                                     \
    {                                                                                                                   \
        none = first_elem - 1,                                                                                          \
        first,                                                                                                          \
        __VA_ARGS__,                                                                                                    \
        last,                                                                                                           \
        count = last,                                                                                                   \
    };                                                                                                                  \
                                                                                                                        \
    std::optional<const char*> ToString(name value);                                                                    \
                                                                                                                        \
    template<typename T>                                                                                                \
    std::optional<T> FromString(cstr value);                                                                            \
                                                                                                                        \
    namespace smart_enum_detail                                                                                         \
    {                                                                                                                   \
        static const std::vector<qx::string> name##ToStringMap = qx::string::split(qx::string(#__VA_ARGS__), ", ");     \
        inline std::unordered_map<qx::string, name> name##ToFromStringMap()                                             \
        {                                                                                                               \
            std::vector<name> args;                                                                                     \
            for (int i = static_cast<int>(name::first) + 1; i < static_cast<int>(name::last); i++)                      \
                args.push_back(static_cast<name>(i));                                                                   \
                                                                                                                        \
            std::unordered_map<qx::string, name> m;                                                                     \
            for(size_t i = 0; i < args.size(); i++)                                                                     \
                m[ToString(args[i]).value()] = args[i];                                                                 \
                                                                                                                        \
            return m;                                                                                                   \
        };                                                                                                              \
        static const std::unordered_map<qx::string, name> name##FromStringMap = name##ToFromStringMap();                \
    }                                                                                                                   \
                                                                                                                        \
    inline std::optional<const char*> ToString(name value)                                                              \
    {                                                                                                                   \
        size_t ind = static_cast<size_t>(value) - static_cast<size_t>(name::first) - 1u;                                \
        return ind < smart_enum_detail::name##ToStringMap.size()                                                        \
            ? std::optional<const char*>(smart_enum_detail::name##ToStringMap[ind].data())                              \
            : std::nullopt;                                                                                             \
    };                                                                                                                  \
                                                                                                                        \
    template<>                                                                                                          \
    inline std::optional<name> FromString(cstr value)                                                                   \
    {                                                                                                                   \
        auto   it  = smart_enum_detail::name##FromStringMap.find(qx::string(value));                                    \
        return it != smart_enum_detail::name##FromStringMap.end()                                                       \
            ? std::optional<name>(it->second)                                                                           \
            : std::nullopt;                                                                                             \
    }                                                                                                                   \
                                                                                                                        \
    /* also returns "last" value as end flag */                                                                         \
    /* note that these operators are defined in enum scope */                                                           \
                                                                                                                        \
    /* postfix */                                                                                                       \
    inline name operator++ (name & d)                                                                                   \
    {                                                                                                                   \
        d = static_cast<name>((static_cast<int>(d) + 1) % (static_cast<int>(name::last) + 1));                          \
        return d;                                                                                                       \
    }                                                                                                                   \
                                                                                                                        \
    /* prefix */                                                                                                        \
    inline name operator++ (name & d, int)                                                                              \
    {                                                                                                                   \
        name tmp(d);                                                                                                    \
        ++d;                                                                                                            \
        return tmp;                                                                                                     \
    }