//============================================================================
//
//!\file                         smart_enum.h
//
//!\brief       Smart enum macro definition
//!\details     Smart macro allows you to use to_string(), from_string() 
//              and increment functions. 
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

#include <qx/containers/string.h>

// look for useful macros at the end of the file
#define _SMART_ENUM_IMPL(name, first_elem, ...)                                                                 \
class name                                                                                                      \
{                                                                                                               \
public:                                                                                                         \
    enum e                                                                                                      \
    {                                                                                                           \
        none = first_elem - 1,                                                                                  \
        first,                                                                                                  \
        __VA_ARGS__,                                                                                            \
        last,                                                                                                   \
        count = last,                                                                                           \
    };                                                                                                          \
                                                                                                                \
    name(void) = default;                                                                                       \
    name(e value) : m_eValue(value) { }                                                                         \
                                                                                                                \
    bool operator==(const name& other) const { return m_eValue == other.m_eValue;   }                           \
    bool operator==(const e&    other) const { return m_eValue == other;            }                           \
                                                                                                                \
    static const char* s_to_string(e value)                                                                     \
    {                                                                                                           \
        size_t ind = static_cast<size_t>(value) - static_cast<size_t>(name::first) - 1u;                        \
        return enum_to_string[ind].data();                                                                      \
    };                                                                                                          \
                                                                                                                \
    const char* to_string() const                                                                               \
    {                                                                                                           \
        return s_to_string(m_eValue);                                                                           \
    };                                                                                                          \
                                                                                                                \
    static std::optional<e> s_from_string(const char* value)                                                    \
    {                                                                                                           \
        auto   it  = string_to_enum.find(qx::string(value));                                                    \
        return it != string_to_enum.end()                                                                       \
            ? std::optional<e>(it->second)                                                                      \
            : std::nullopt;                                                                                     \
    }                                                                                                           \
                                                                                                                \
    bool from_string(const char* value)                                                                         \
    {                                                                                                           \
        std::optional<e> val = s_from_string(value);                                                            \
        if (val.has_value())                                                                                    \
        {                                                                                                       \
            m_eValue = val.value();                                                                             \
            return true;                                                                                        \
        }                                                                                                       \
        else                                                                                                    \
            return false;                                                                                       \
    }                                                                                                           \
                                                                                                                \
    /* also returns "last" value as end flag */                                                                 \
    /* note that these operators are defined in enum scope */                                                   \
                                                                                                                \
    /* postfix */                                                                                               \
    e operator++ ()                                                                                             \
    {                                                                                                           \
        m_eValue = static_cast<e>((static_cast<int>(m_eValue) + 1) % (static_cast<int>(name::last) + 1));       \
        return m_eValue;                                                                                        \
    }                                                                                                           \
                                                                                                                \
    /* prefix */                                                                                                \
    e operator++ (int)                                                                                          \
    {                                                                                                           \
        e tmp(m_eValue);                                                                                        \
        operator++();                                                                                           \
        return tmp;                                                                                             \
    }                                                                                                           \
                                                                                                                \
private:                                                                                                        \
                                                                                                                \
    e m_eValue = none;                                                                                          \
                                                                                                                \
    static std::unordered_map<qx::string, e> fill_string_to_enum()                                              \
    {                                                                                                           \
        std::vector<e> args;                                                                                    \
        for (int i = static_cast<int>(name::first) + 1; i < static_cast<int>(name::last); i++)                  \
            args.push_back(static_cast<e>(i));                                                                  \
                                                                                                                \
        std::unordered_map<qx::string, e> m;                                                                    \
        for (size_t i = 0; i < args.size(); i++)                                                                \
            m[s_to_string(args[i])] = args[i];                                                                  \
                                                                                                                \
        return m;                                                                                               \
    };                                                                                                          \
                                                                                                                \
    static std::vector<qx::string> fill_enum_to_string(void)                                                    \
    {                                                                                                           \
        return std::move(qx::string(#__VA_ARGS__).split(", "));                                                 \
    }

#define _SMART_ENUM_STORAGE                                                                                     \
    inline static const std::vector<qx::string> enum_to_string = fill_enum_to_string();                         \
    inline static const std::unordered_map<qx::string, e> string_to_enum = fill_string_to_enum();               \
};

#define _SMART_ENUM_HEADER_STORAGE                                                                              \
    static const std::vector<qx::string> enum_to_string;                                                        \
    static const std::unordered_map<qx::string, e> string_to_enum;                                              \
};

#define _SMART_ENUM_CPP_STORAGE(name, ...)                                                                      \
const std::vector<qx::string> name##::##enum_to_string = name::fill_enum_to_string();                           \
const std::unordered_map<qx::string, name::e> name::string_to_enum = name::fill_string_to_enum();

// smart enum may be used with inline maps, 
// but every header with definition included will produce its own maps instances
// use SMART_ENUM inside .cpp file or include .h file rarely
#define SMART_ENUM(name, first_elem, ...)               \
    _SMART_ENUM_IMPL(name, first_elem, __VA_ARGS__)     \
    _SMART_ENUM_STORAGE

// using SMART_ENUM_H inside .h file and SMART_ENUM_CPP inside .cpp file
// only one instance will be created 
#define SMART_ENUM_H(name, first_elem, ...)             \
    _SMART_ENUM_IMPL(name, first_elem, __VA_ARGS__)     \
    _SMART_ENUM_HEADER_STORAGE

#define SMART_ENUM_CPP(name)                            \
    _SMART_ENUM_CPP_STORAGE(name)