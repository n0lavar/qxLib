/**

    @file      type_strings.h
    @author    Khrapov
    @date      24.09.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_literal.h>
#include <qx/containers/string/string_utils.h>
#include <qx/containers/string/string_view.h>
#include <qx/macros/config.h>

#include <array>
#include <span>

namespace qx
{

/**

    @class   type_strings
    @brief   The class allows you to get strings with information about the type,
             including its full name, name without template parameters
             and a list of template parameters separately
    @details Strings are COMPILER IMPLEMENTATION DEPENDENT but can be used for a human readable output
    @tparam  T      - type to get information for
    @tparam  char_t - char type to use
    @author  Khrapov
    @date    24.09.2022

**/
template<class T, class char_t = char_type>
class type_strings
{
    using string_view_type = basic_string_view<char_t>;

private:
    static constexpr string_view_type lambdaMarker = QX_STR_PREFIX(char_t, "lambda");
    static constexpr string_view_type create_full_signature();
    static constexpr string_view_type create_signature();
    static constexpr size_t           get_num_template_parameters();

public:
    /**
        @brief  Get type signature (full name with template parameters)
        @retval  - type signature
    **/
    static constexpr string_view_type get_signature();

    /**
        @brief  Get type name (short name without template parameters)
        @retval  - type name
    **/
    static constexpr string_view_type get_name();

    /**
        @brief  Get type template parameters
        @retval  - template parameters
    **/
    static constexpr auto get_template_parameters();
};

} // namespace qx

#include <qx/meta/type_strings.inl>
