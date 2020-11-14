//==============================================================================
//
//!\file                         smart_enum.h
//
//!\brief       Smart enum macro definition
//!\details     Smart macro allows you to use to_string(), from_string()
//              and increment functions.
//
//!\author      Khrapov
//!\date        16.10.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/containers/string.h>

#include <unordered_map>

#define QX_SMART_ENUM(name, first_elem, ...)                                            \
class name                                                                              \
{                                                                                       \
public:                                                                                 \
    /* todo: enum class and using enum (C++ 20) */                                      \
    enum e                                                                              \
    {                                                                                   \
        first = (first_elem),                                                           \
        none  = (first_elem) - 1,                                                       \
        __VA_ARGS__,                                                                    \
        last,                                                                           \
        count = last,                                                                   \
    };                                                                                  \
                                                                                        \
    name(void) = default;                                                               \
    name(e value) : m_eValue(value) { }                                                 \
                                                                                        \
    bool operator==(const name& other) const { return m_eValue == other.m_eValue;   }   \
    bool operator==(const e&    other) const { return m_eValue == other;            }   \
    bool operator!=(const name& other) const { return !operator==(other.m_eValue);  }   \
    bool operator!=(const e&    other) const { return !operator==(other);           }   \
         operator e(void)              const { return m_eValue;                     }   \
                                                                                        \
    static const char* s_to_string(e value)                                             \
    {                                                                                   \
        static const std::vector<qx::string> enum_to_string = fill_enum_to_string();    \
        size_t ind = static_cast<size_t>(value) - static_cast<size_t>(e::first);        \
        return enum_to_string[ind].data();                                              \
    };                                                                                  \
                                                                                        \
    const char* to_string() const                                                       \
    {                                                                                   \
        return s_to_string(m_eValue);                                                   \
    };                                                                                  \
                                                                                        \
    static e s_from_string(const char* value)                                           \
    {                                                                                   \
        static const std::unordered_map<qx::string_hash, e> string_to_enum              \
            = fill_string_to_enum();                                                    \
                                                                                        \
        auto   it  = string_to_enum.find(value);                                        \
        return it != string_to_enum.end()                                               \
            ? it->second                                                                \
            : e::none;                                                                  \
    }                                                                                   \
                                                                                        \
    bool from_string(const char* value)                                                 \
    {                                                                                   \
        e val = s_from_string(value);                                                   \
        if (val != e::none)                                                             \
        {                                                                               \
            m_eValue = val;                                                             \
            return true;                                                                \
        }                                                                               \
        else                                                                            \
            return false;                                                               \
    }                                                                                   \
                                                                                        \
    /* postfix */                                                                       \
    /* also returns "last" value as end flag */                                         \
    e operator++ ()                                                                     \
    {                                                                                   \
        if (static_cast<int>(m_eValue) < static_cast<int>(e::last))                     \
            m_eValue = static_cast<e>((static_cast<int>(m_eValue) + 1));                \
        else                                                                            \
            m_eValue = e::first;                                                        \
                                                                                        \
        return m_eValue;                                                                \
    }                                                                                   \
                                                                                        \
    /* prefix */                                                                        \
    e operator++ (int)                                                                  \
    {                                                                                   \
        e tmp(m_eValue);                                                                \
        operator++();                                                                   \
        return tmp;                                                                     \
    }                                                                                   \
                                                                                        \
private:                                                                                \
                                                                                        \
    e m_eValue = e::none;                                                               \
                                                                                        \
    static std::unordered_map<qx::string_hash, e> fill_string_to_enum()                 \
    {                                                                                   \
        std::unordered_map<qx::string_hash, e> m;                                       \
        for (int i = static_cast<int>(e::first); i < static_cast<int>(e::last); i++)    \
            m[qx::string_hash(s_to_string(static_cast<e>(i)))] = static_cast<e>(i);     \
                                                                                        \
        return m;                                                                       \
    };                                                                                  \
                                                                                        \
    static std::vector<qx::string> fill_enum_to_string(void)                            \
    {                                                                                   \
        return qx::string(#__VA_ARGS__).split(", ");                                    \
    }                                                                                   \
};
