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
    @param ...  - optional category color and description
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
        @param  color          - color to be used if supported
        @param  pszDescription - category description
    **/
    constexpr explicit category(
        const char*  pszName,
        const color& color          = kDefaultColor,
        const char*  pszDescription = nullptr) noexcept;

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
    const color       m_Color          = kDefaultColor;
    const char* const m_pszName        = nullptr;
    const char* const m_pszDescription = nullptr;
};

constexpr category::category(const char* pszName, const color& color, const char* pszDescription) noexcept
    : m_Color(color)
    , m_pszName(pszName)
    , m_pszDescription(pszDescription)
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
