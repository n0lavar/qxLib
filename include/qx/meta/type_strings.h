/**

    @file      type_strings.h
    @brief     Contains qx::type_strings class
    @details   ~
    @author    Khrapov
    @date      24.09.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <array>
#include <string_view>

namespace qx
{

/**

    @class   type_strings
    @brief   The class allows you to get strings with information about the type,
             including its full name, name without template parameters
             and a list of template parameters separately
    @details Strings are COMPILER IMPLEMENTATION DEPENDENT but can be used for a human readable output
    @tparam  T - type to get information for
    @author  Khrapov
    @date    24.09.2022

**/
template<class T>
class type_strings
{
private:
    static constexpr char             lambdaMarker[] = "lambda";
    static constexpr std::string_view create_full_signature();
    static constexpr size_t           get_num_template_parameters();
    static constexpr std::string_view create_signature();
    static constexpr std::string_view create_name();
    using template_parameters_container = std::array<std::string_view, get_num_template_parameters()>;
    static constexpr template_parameters_container create_template_parameters();

    static constexpr auto m_kSignature          = create_signature();
    static constexpr auto m_kName               = create_name();
    static constexpr auto m_kTemplateParameters = create_template_parameters();

public:
    /**
        @brief  Get type signature (full name with template parameters)
        @retval  - type signature
    **/
    static constexpr std::string_view get_signature();

    /**
        @brief  Get type name (short name without template parameters)
        @retval  - type name
    **/
    static constexpr std::string_view get_name();

    /**
        @brief  Get type template parameters
        @retval  - template parameters
    **/
    static constexpr template_parameters_container get_template_parameters();
};

} // namespace qx

#include <qx/meta/type_strings.inl>
