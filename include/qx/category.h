/**

    @file      category.h
    @brief     Contains category class
    @details   ~
    @author    Khrapov
    @date      5.12.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/render/color.h>

/**
    @brief Define a category
    @param name - category name
    @param ...  - optional category description and color
**/
#define QX_DEFINE_CATEGORY(name, ...) constexpr qx::category name(#name, ##__VA_ARGS__);

namespace qx
{

/**

    @class   category
    @brief   A category is a class that identifies a particular piece of code.
             This code can be located in different files, but united by one functionality.
             Objects of this class can be used in logging, asserts and profiling.
    @author  Khrapov
    @date    5.12.2022

**/
class category
{
    static constexpr auto kDefaultColor = color::white();

public:
    /**
        @brief  category object constructor
        @param  pszName        - category name. For ex. CatRendering or CatWidgets
        @param  pszDescription - category description
        @param  color          - color to be used if supported
    **/
    constexpr explicit category(
        const char*  pszName,
        const char*  pszDescription = nullptr,
        const color& color          = kDefaultColor) noexcept;

    /**
        @brief  Get category name
        @retval  -category  name
    **/
    constexpr const char* get_name() const noexcept;

    /**
        @brief  Get category description
        @retval  - category description
    **/
    constexpr const char* get_description() const noexcept;

    /**
        @brief  Get category color
        @retval  - category color
    **/
    constexpr const color& get_color() const noexcept;

private:
    const char* const m_pszName        = nullptr;
    const char* const m_pszDescription = nullptr;
    const color       m_Color          = kDefaultColor;
};

constexpr category::category(const char* pszName, const char* pszDescription, const color& color) noexcept
    : m_pszName(pszName)
    , m_pszDescription(pszDescription)
    , m_Color(color)
{
}

constexpr const char* category::get_name() const noexcept
{
    return m_pszName;
}

constexpr const char* category::get_description() const noexcept
{
    return m_pszDescription;
}

constexpr const color& category::get_color() const noexcept
{
    return m_Color;
}

} // namespace qx
