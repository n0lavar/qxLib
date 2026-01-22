/**

    @file      property.h
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

/**
    @brief Fast C#-like getter
    @param type - value type
    @param name - value name
**/
#define QX_GETTER(type, name)               \
    const type& get_##name() const noexcept \
    {                                       \
        return m_##name;                    \
    }

/**
    @def   QX_GETTER_REF
    @brief Fast C#-like ref getter
    @param type - value type
    @param name - value name
**/
#define QX_GETTER_REF(type, name) \
    type& get_##name() noexcept   \
    {                             \
        return m_##name;          \
    }
//-V:QX_GETTER_REF:1003

/**
    @brief Fast C#-like setter
    @param type - value type
    @param name - value name
**/
#define QX_SETTER(type, name)                 \
    void set_##name(const type& val) noexcept \
    {                                         \
        m_##name = val;                       \
    }

/**
    @brief A set of data member, getter and setter
    @param type - data type
    @param name - data name
    @param ...  - data default value
**/
#define QX_PROPERTY(type, name, ...) \
public:                              \
    QX_GETTER(type, name);           \
    QX_SETTER(type, name);           \
                                     \
private:                             \
    type m_##name = type(__VA_ARGS__)
