/**

    @file      layered_configs_manager.h
    @author    Khrapov
    @date      12.05.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/algo/contains.h>
#include <qx/algo/sort.h>
#include <qx/logger/logger.h>
#include <qx/patterns/singleton.h>

#include <any>
#include <unordered_map>

namespace qx
{

namespace details
{

struct layered_config_variable_data
{
    cstring_view svEnvName;
    cstring_view svFullCommandLineName;
    cstring_view svShortCommandLineName;

    cstring_view svGroupName;
    cstring_view svDescription;
    bool         bRequired = false;

    std::optional<std::any> (*pStringToT)(cstring_view svData);
    cstring (*pTToString)(const std::any& data);
    cstring_view svTypeName;
};

} // namespace details

/**

    @class   layered_configs_manager
    @brief   A singleton that manages layered configuration variables
    @details Doesn't support multithreading
    @author  Khrapov
    @date    17.05.2026

**/
class layered_configs_manager final : public singleton<layered_configs_manager>
{
    template<class T>
    friend class layered_config_variable_builder;

public:
    /**
        @brief Set app description. It will be shown in help message.
        @param sAppDescription - app description
    **/
    void set_app_description(cstring sAppDescription) noexcept;

    /**
        @brief   Set command line arguments.
        @details Should be called once at the beginning of the app before the first parse().
        @param   argc - number of command line arguments
        @param   argv - array of command line arguments
    **/
    void set_args(int argc, char* argv[]) noexcept;

    /**
        @brief   Show help message if "--help" or "-h" argument is present in command line arguments.
        @details Should be called after set_args().
        @retval  - true if help message was shown. usually the app should exit after that
    **/
    bool show_help() const noexcept;

    /**
        @brief   Parse command line arguments, environment variables, and default values.
        @details Should be called after set_args() and before get()/set() of any variable.
        @retval  - true all required variables are present and have valid values
    **/
    bool parse() noexcept;

    /**
        @brief  Get variable value by runtime name.
        @tparam T             - type of variable
        @param  svRuntimeName - runtime name of variable
        @retval               - optional with variable value if it is present, has valid value and correct type
    **/
    template<class T>
    std::optional<T> get(cstring_view svRuntimeName) const noexcept;

    /**
        @brief  Set variable value by runtime name. Only set if the variable type matches.
        @tparam T             - type of variable
        @param  svRuntimeName - runtime name of variable
        @param  value         - new variable value
        @retval               - true if the value was set successfully
    **/
    template<class T>
    bool set(cstring_view svRuntimeName, T value) noexcept;

    /**
        @brief Clear all variables and command line arguments. You should call parse() after that to set variables again.
    **/
    void reset() noexcept;

private:
    /**
        @brief  Add a variable to the manager. Called from variable builders
        @tparam T             - type of variable
        @param  svRuntimeName - runtime name of variable
        @param  data          - information about variable
        @param  defaultValue  - default variable value
    **/
    template<class T>
    void add_variable(
        cstring_view                                 svRuntimeName,
        const details::layered_config_variable_data& data,
        T                                            defaultValue) noexcept;

private:
    cstring                m_sAppDescription;
    std::span<char* const> m_Args;

    std::unordered_map<cstring_view, details::layered_config_variable_data> m_VariableData;
    std::unordered_map<cstring_view, std::any>                              m_DefaultVariables;
    std::unordered_map<cstring_view, std::any>                              m_Variables;
};

} // namespace qx

#include <qx/layered_config/layered_configs_manager.inl>
