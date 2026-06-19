/**

    @file      category.h
    @author    Khrapov
    @date      5.12.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_hash.h>
#include <qx/containers/string/string_utils.h>
#include <qx/macros/common.h>
#include <qx/render/color.h>
#include <qx/verbosity.h>

#include <optional>

/**
    @brief Define a category
    @param name - category name
    @param ...  - optional category color
**/
#define QX_DEFINE_CATEGORY(name, ...) constexpr qx::category name = qx::category(QXT(#name), ##__VA_ARGS__)

/**
    @brief Set the file category
           You can access this value via QX_GET_FILE_CATEGORY()
           This category will not be exported via #include
    @param _category - category to use in this file
**/
#define QX_SET_FILE_CATEGORY(_category)                                 \
    template<>                                                          \
    struct qx::details::file_category<qx::djb2a_hash(QX_SHORT_FILE, 0)> \
    {                                                                   \
        static constexpr const qx::category& get() noexcept             \
        {                                                               \
            return _category;                                           \
        }                                                               \
    }

/**
    @brief Get category defined in QX_SET_FILE_CATEGORY
           If there is none, CatDefault will be used
**/
#define QX_GET_FILE_CATEGORY() qx::details::file_category<qx::djb2a_hash(QX_SHORT_FILE)>::get()

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
public:
    constexpr category()                           = default;
    constexpr category(const category&)            = default;
    constexpr category(category&&)                 = default;
    constexpr category& operator=(const category&) = default;
    constexpr category& operator=(category&&)      = default;

    constexpr bool operator==(const category&) const = default;

    /**
        @brief  category object constructor
        @param  svName           - category name. For ex. CatRendering or CatWidgets
        @param  optCategoryColor - color to be used if supported.
                                   If it isn't provided, a color generated from a name hash is used.
    **/
    constexpr explicit category(string_view svName, std::optional<color> optCategoryColor = std::nullopt) noexcept;

    /**
        @brief  Create new category from this one with custom verbosity
        @param  eVerbosity - category verbosity.
                User code will use this category with top priority and perform compile time checks if possible
        @retval            - new category
    **/
    constexpr category set_verbosity(verbosity eVerbosity) const noexcept;

    /**
        @brief  Get category name
        @retval - category name
    **/
    constexpr string_view get_name() const noexcept;

    /**
        @brief  Get category color
        @retval  - category color
    **/
    constexpr const color& get_color() const noexcept;

    /**
        @brief  Get category verbosity
        @retval  - category verbosity
                   User code will use this category with top priority and perform compile time checks if possible
    **/
    constexpr verbosity get_verbosity() const noexcept;

private:
    color       m_Color;
    string_view m_svName;
    verbosity   m_Verbosity = QX_CONF_COMPILE_TIME_VERBOSITY;
};

} // namespace qx

#include <qx/category.inl>

QX_DEFINE_CATEGORY(CatDefault, qx::color::white());

namespace qx::details
{

template<size_t nHash>
struct file_category
{
    static constexpr const category& get() noexcept
    {
        return CatDefault;
    }
};

} // namespace qx::details
