/**

    @file      category.h
    @brief     Contains category class
    @details   ~
    @author    Khrapov
    @date      5.12.2022
    @copyright � Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_utils.h>
#include <qx/macros/common.h>
#include <qx/render/color.h>

/**
    @brief Define a category
    @param name - category name
    @param ...  - optional category color and description
**/
#define QX_DEFINE_CATEGORY(name, ...) constexpr qx::category name(#name, ##__VA_ARGS__)

/**
    @brief Define file category
           You can access this value via QX_FILE_CATEGORY()
           This category will not be exported via #include
    @param _category - category to use in this file
**/
#define QX_DEFINE_FILE_CATEGORY(_category)                                                                    \
    template<>                                                                                                \
    constexpr const qx::category& qx::details::get_file_category<qx::djb2a_hash(QX_SHORT_FILE, 0)>() noexcept \
    {                                                                                                         \
        return _category;                                                                                     \
    }

/**
    @brief Get category defined in QX_DEFINE_FILE_CATEGORY
           If there is none, CatDefault will be used
**/
#define QX_FILE_CATEGORY() qx::details::get_file_category<qx::djb2a_hash(QX_SHORT_FILE, 0)>()

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
        @param  categoryColor  - color to be used if supported
        @param  pszDescription - category description
    **/
    constexpr explicit category(
        const char*  pszName,
        const color& categoryColor  = kDefaultColor,
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

} // namespace qx

#include <qx/category.inl>