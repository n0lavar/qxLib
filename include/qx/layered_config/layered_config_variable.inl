/**

    @file      layered_config_variable.inl
    @author    Khrapov
    @date      12.05.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

template<class T>
constexpr T layered_config_variable<T>::get() const noexcept
{
    std::optional<T> optValue = layered_configs_manager::get_instance().get<T>(m_svRuntimeName);
    return optValue ? *optValue : m_DefaultValue;
}

template<class T>
constexpr void layered_config_variable<T>::set(T value) noexcept
{
    layered_configs_manager::get_instance().set(m_svRuntimeName, std::move(value));
}

template<class T>
consteval layered_config_variable_builder<T>::layered_config_variable_builder(
    cstring_view svRuntimeName,
    T            defaultValue) noexcept
{
    m_svRuntimeName   = svRuntimeName;
    m_DefaultValue    = std::move(defaultValue);
    m_Data.pStringToT = [](cstring_view svData) -> std::optional<std::any>
    {
        if constexpr (std::is_same_v<T, cstring_view>)
        {
            return cstring(svData);
        }
        else
        {
            // todo get rid of an allocation
            cstring sData = svData;

            std::optional<T> optResult = sData.to<T>();
            if (!optResult)
                return std::nullopt;

            return std::move(*optResult);
        }
    };
    m_Data.pTToString = [](const std::any& data) -> cstring
    {
        return convert_to_string<T, char>(std::any_cast<T>(data));
    };
    m_Data.svTypeName = []() -> cstring_view
    {
        if constexpr (std::is_same_v<T, cstring_view>)
        {
            return "string";
        }
        else
        {
            return type_strings<T, char>::get_signature();
        }
    }();
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::env(cstring_view svEnvName) noexcept
{
    m_Data.svEnvName = svEnvName;
    return *this;
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::command_line(
    cstring_view svFullName,
    cstring_view svShortName) noexcept
{
    m_Data.svFullCommandLineName = svFullName;
    if (!m_Data.svFullCommandLineName.starts_with("--"))
        throw "Full command line name must start with --";

    m_Data.svShortCommandLineName = svShortName;
    if (!m_Data.svShortCommandLineName.empty() && !m_Data.svShortCommandLineName.starts_with("-"))
        throw "Short command line name must start with -";

    return *this;
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::group(
    cstring_view svGroupName) noexcept
{
    m_Data.svGroupName = svGroupName;
    return *this;
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::description(
    cstring_view svDescription) noexcept
{
    m_Data.svDescription = svDescription;
    return *this;
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::required() noexcept
{
    m_Data.bRequired = true;
    return *this;
}

template<class T>
layered_config_variable<T> layered_config_variable_builder<T>::build() noexcept
{
    layered_config_variable<T> layeredConfigVariable;
    layeredConfigVariable.m_DefaultValue  = m_DefaultValue;
    layeredConfigVariable.m_svRuntimeName = m_svRuntimeName;

    layered_configs_manager::get_instance().add_variable(m_svRuntimeName, std::move(m_Data), std::move(m_DefaultValue));

    return layeredConfigVariable;
}

} // namespace qx
