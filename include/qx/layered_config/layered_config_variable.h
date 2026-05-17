/**

    @file      layered_config_variable.h
    @author    Khrapov
    @date      12.05.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/containers/string/format.h>
#include <qx/layered_config/layered_configs_manager.h>
#include <qx/meta/type_strings.h>

namespace qx
{

/**

    @class   layered_config_variable
    @brief   A configuration variable that can be set from different layers
             (default value, environment variable, command line argument, runtime get()/set()).
    @details Supposed to be created using layered_config_variable_builder and stored as a global variable or constant
             (in case you don't want to change it at runtime).
    @tparam  T - variable type
    @author  Khrapov
    @date    17.05.2026

**/
template<class T>
class layered_config_variable
{
    template<class U>
    friend class layered_config_variable_builder;

public:
    /**
        @brief  Get variable value.
                If the variable is not set in any layer or has invalid value, the default value will be returned.
        @retval  - variable value
    **/
    constexpr T get() const noexcept;

    /**
        @brief Set variable value at runtime. It will override value from all other layers.
        @param value - variable value
    **/
    constexpr void set(T value) noexcept;

private:
    constexpr layered_config_variable() noexcept = default;

private:
    T            m_DefaultValue;
    cstring_view m_svRuntimeName;
};

/**

    @class   layered_config_variable_builder
    @brief   A builder for creating layered_config_variable instances.
    @tparam  T - variable type
    @author  Khrapov
    @date    17.05.2026

**/
template<class T>
class layered_config_variable_builder
{
public:
    /**
        @brief layered_config_variable_builder object constructor
        @param svRuntimeName - runtime name of variable
        @param defaultValue  - a value to be used if the variable is not set in any layer or has invalid value
    **/
    consteval layered_config_variable_builder(cstring_view svRuntimeName, T defaultValue = {}) noexcept;

    /**
        @brief  Add environment variable layer with specified name
        @param  svEnvName - name of environment variable
    **/
    consteval layered_config_variable_builder env(cstring_view svEnvName) noexcept;

    /**
        @brief  Add command line argument layer with specified full and short names.
                Full name should start with "--", short name should start with "-" or be empty.
        @param  svFullName  - full name of command line argument
        @param  svShortName - short name of command line argument
    **/
    consteval layered_config_variable_builder command_line(
        cstring_view svFullName,
        cstring_view svShortName = {}) noexcept;

    /**
        @brief   Set the group name for the variable.
        @details Variables with the same group name can be displayed together in help messages.
        @param   svGroupName - group name
    **/
    consteval layered_config_variable_builder group(cstring_view svGroupName) noexcept;

    /**
        @brief   Set the description for the variable.
        @details This description will be shown in help messages.
        @param   svDescription - description of the variable
    **/
    consteval layered_config_variable_builder description(cstring_view svDescription) noexcept;

    /**
        @brief Mark variable as required. If a required variable is not set in any layer or has invalid value,
               layered_configs_manager::parse() will log errors and return false.
    **/
    consteval layered_config_variable_builder required() noexcept;

    /**
        @brief  Finalize building layered_config_variable instance and add it to layered_configs_manager.
        @retval  - built layered_config_variable instance
    **/
    layered_config_variable<T> build() noexcept;

private:
    details::layered_config_variable_data m_Data;
    cstring_view                          m_svRuntimeName;
    T                                     m_DefaultValue;
};

} // namespace qx

#include <qx/layered_config/layered_config_variable.inl>
