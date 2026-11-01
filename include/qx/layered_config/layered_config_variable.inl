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
    std::expected<T, layered_configs_manager::get_error> value =
        layered_configs_manager::get_instance().get<T>(m_svRuntimeName);
    return value ? *value : m_DefaultValue;
}

template<class T>
constexpr std::expected<void, layered_configs_manager::set_error> layered_config_variable<T>::set(T value) noexcept
{
    return layered_configs_manager::get_instance().set(m_svRuntimeName, std::move(value));
}

template<class T>
consteval layered_config_variable_builder<T>::layered_config_variable_builder(
    string_view svRuntimeName,
    T           defaultValue) noexcept
    : m_svRuntimeName(svRuntimeName)
    , m_DefaultValue(std::move(defaultValue))
{
    m_Data.pStringToT = [](string_view svData) -> std::optional<std::any>
    {
        if constexpr (std::is_same_v<T, string_view>)
        {
            return string(svData);
        }
        else
        {
            // todo get rid of an allocation
            string sData = svData;

            std::optional<T> optResult = sData.to<T>();
            if (!optResult)
                return std::nullopt;

            return std::move(*optResult);
        }
    };
    m_Data.pTToString = [](const std::any& data) -> string
    {
        return convert_to_string<typename details::layered_config_variable_type<T>::type, char_type>(
            std::any_cast<const typename details::layered_config_variable_type<T>::type&>(data));
    };
    m_Data.svTypeName = []() -> string_view
    {
        if constexpr (std::is_same_v<T, string_view>)
        {
            return QXT("string");
        }
        else
        {
            return type_strings<T, char_type>::get_signature();
        }
    }();
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::env(string_view svEnvName) noexcept
{
    m_Data.svEnvName = svEnvName;
    return *this;
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::command_line(
    string_view svFullName,
    string_view svShortName)
{
    m_Data.svFullCommandLineName = svFullName;
    if (!m_Data.svFullCommandLineName.starts_with(QXT("--")))
        throw QXT("Full command line name must start with --");

    m_Data.svShortCommandLineName = svShortName;
    if (!m_Data.svShortCommandLineName.empty() && !m_Data.svShortCommandLineName.starts_with(QXT("-")))
        throw QXT("Short command line name must start with -");

    return *this;
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::group(string_view svGroupName) noexcept
{
    m_Data.svGroupName = svGroupName;
    return *this;
}

template<class T>
consteval layered_config_variable_builder<T> layered_config_variable_builder<T>::description(
    string_view svDescription) noexcept
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
