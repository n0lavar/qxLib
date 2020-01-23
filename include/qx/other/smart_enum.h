//============================================================================
//
//!\file                         smart_enum.h
//
//!\brief       Smart enum macro definition
//!\details     Smart macro allows you to use ToString(), FromString() and increment
//              functions. "namespace name" is used to make possible
//              same names of enum values in one scope.
//              Note that the numbering of objects begins with first_elem + 1
//
//!\author      Khrapov
//!\date        16.10.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <vector>
#include <unordered_map>
#include <qxstring.h>

#define SMART_ENUM(name, first_elem, ...)                                                                               \
    namespace name                                                                                                      \
    {                                                                                                                   \
        enum name##_t                                                                                                   \
        {                                                                                                               \
            first      = first_elem,                                                                                    \
            defaut_val = first,                                                                                         \
            __VA_ARGS__,                                                                                                \
            last                                                                                                        \
        };                                                                                                              \
    }                                                                                                                   \
                                                                                                                        \
    const char* ToString(name::name##_t value, cstr defaultStr = "default");                                            \
    namespace smart_enum_detail                                                                                         \
    {                                                                                                                   \
        static const std::vector<qx::string> name##ToStringMap = qx::string::split(qx::string(#__VA_ARGS__), ',');      \
        inline std::unordered_map<qx::string, name::name##_t> name##ToFromStringMap()                                   \
        {                                                                                                               \
            std::vector<name::name##_t> args;                                                                           \
            for (int i = name::first + 1; i < name::last; i++)                                                          \
                args.push_back(static_cast<name::name##_t>(i));                                                         \
                                                                                                                        \
            std::unordered_map<qx::string, name::name##_t> m;                                                           \
            for(size_t i = 0; i < args.size(); i++)                                                                     \
                m[ToString(args[i])] = args[i];                                                                         \
                                                                                                                        \
            return m;                                                                                                   \
        };                                                                                                              \
        static const std::unordered_map<qx::string, name::name##_t> name##FromStringMap = name##ToFromStringMap();      \
    }                                                                                                                   \
                                                                                                                        \
    inline const char* ToString(name::name##_t value, cstr defaultStr)                                                  \
    {                                                                                                                   \
        size_t ind = static_cast<size_t>(value) - static_cast<size_t>(name::first) - 1u;                                \
        return ind < smart_enum_detail::name##ToStringMap.size()                                                        \
            ? smart_enum_detail::name##ToStringMap[ind].data()                                                          \
            : defaultStr;                                                                                               \
    };                                                                                                                  \
                                                                                                                        \
    inline name::name##_t FromString(cstr value, name::name##_t defaultValue = name::name##_t::defaut_val)              \
    {                                                                                                                   \
        auto   it  = smart_enum_detail::name##FromStringMap.find(qx::string(value));                                    \
        return it == smart_enum_detail::name##FromStringMap.end() ? defaultValue : it->second;                          \
    }                                                                                                                   \
                                                                                                                        \
    /* also returns "last" value as end flag */                                                                         \
    /* note that these operators are defined in enum scope */                                                           \
                                                                                                                        \
    /* postfix */                                                                                                       \
    inline name::name##_t operator++ (name::name##_t & d)                                                               \
    {                                                                                                                   \
        d = static_cast<name::name##_t>((static_cast<int>(d) + 1) % (name::last + 1));                                  \
        return d;                                                                                                       \
    }                                                                                                                   \
                                                                                                                        \
    /* prefix */                                                                                                        \
    inline name::name##_t operator++ (name::name##_t & d, int)                                                          \
    {                                                                                                                   \
        name::name##_t tmp(d);                                                                                          \
        ++d;                                                                                                            \
        return tmp;                                                                                                     \
    }