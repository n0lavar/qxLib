/**

    @file      layered_configs_manager.inl
    @author    Khrapov
    @date      12.05.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

namespace details
{

template<class T>
struct layered_config_variable_type
{
    using type = T;
};

template<>
struct layered_config_variable_type<string_view>
{
    using type = string;
};

} // namespace details

inline void layered_configs_manager::set_app_description(string sAppDescription) noexcept
{
    m_sAppDescription = std::move(sAppDescription);
}

inline void layered_configs_manager::set_args(int argc, char* argv[]) noexcept
{
    if (argc <= 0 || argv == nullptr)
    {
        m_Args.clear();
        return;
    }

    m_Args.clear();
    m_Args.reserve(static_cast<size_t>(argc));
    for (int i = 0; i < argc; ++i)
        m_Args.push_back(to_string(cstring_view(argv[i])));
}

inline bool layered_configs_manager::show_help() const noexcept
{
    if (!contains_if(
            m_Args,
            [](const string& sValue)
            {
                const string_view svValue = sValue;
                return svValue == QXT("--help") || svValue == QXT("-h");
            }))
    {
        return false;
    }

    struct data_with_runtime_name : details::layered_config_variable_data
    {
        string_view svRuntimeName;
    };

    std::map<string_view, std::vector<data_with_runtime_name>> groups;
    for (const auto& [svRuntimeName, data] : m_VariableData)
    {
        groups[data.svGroupName].emplace_back(data, svRuntimeName);
    }

    for (std::vector<data_with_runtime_name>& lines : groups | std::views::values)
    {
        sort(
            lines,
            [](const data_with_runtime_name& left, const data_with_runtime_name& right)
            {
                return left.bRequired > right.bRequired && left.svFullCommandLineName > right.svFullCommandLineName;
            });
    }

    string sHelp;
    if (!groups.empty())
    {
        constexpr string_view svRequired = QXT("required  ");

        size_t nMaxFullCommandLineNameLength  = 0;
        size_t nMaxShortCommandLineNameLength = 0;
        size_t nMaxTypeNameLength             = 0;
        size_t nMaxRequiredNameLength         = 0;
        for (const std::vector<data_with_runtime_name>& lines : groups | std::views::values)
        {
            for (const data_with_runtime_name& line : lines)
            {
                nMaxFullCommandLineNameLength =
                    std::max(nMaxFullCommandLineNameLength, line.svFullCommandLineName.size());
                nMaxShortCommandLineNameLength =
                    std::max(nMaxShortCommandLineNameLength, line.svShortCommandLineName.size());
                nMaxTypeNameLength     = std::max(nMaxTypeNameLength, line.svTypeName.size());
                nMaxRequiredNameLength = std::max(
                    nMaxRequiredNameLength,
                    line.bRequired ? svRequired.size() : line.pTToString(m_Variables.at(line.svRuntimeName)).size());
            }
        }

        sHelp.append_format(QXT("\n\nUsage: {} [options]\n"), m_Args[0]);
        sHelp += QXT("Using formats: [--key], [-k], [--key=value], [-k=value], [--key value], [-k value]\n\n");

        if (!m_sAppDescription.empty())
            sHelp.append_format(QXT("{}\n\n"), m_sAppDescription);

        for (const auto& [svGroupName, lines] : groups)
        {
            if (!svGroupName.empty())
                sHelp.append_format(QXT("{}:\n"), svGroupName);
            else
                sHelp += QXT("General options:\n");

            sHelp +=
                QXT("--------------------------------------------------------------------------------------------------"
                    "----------------------\n");

            for (const data_with_runtime_name& line : lines)
            {
                sHelp.append_format(
                    QXT("{:<{}}  {:<{}}  {:<{}}  {:<{}}{}\n"),
                    line.svFullCommandLineName,
                    nMaxFullCommandLineNameLength,
                    line.svShortCommandLineName,
                    nMaxShortCommandLineNameLength,
                    line.svTypeName,
                    nMaxTypeNameLength,
                    line.bRequired ? svRequired
                                   : string_view(line.pTToString(m_Variables.at(line.svRuntimeName)) + QXT("  ")),
                    nMaxRequiredNameLength,
                    line.svDescription);
            }

            sHelp += QXT("\n");
        }
    }
    else
    {
        sHelp += QXT("This app doesn't have any command line arguments.\n\n");
        if (!m_sAppDescription.empty())
            sHelp.append_format(QXT("{}\n\n"), m_sAppDescription);
    }

    QX_LOG(qx::verbosity::important, sHelp);

    return true;
}

inline bool layered_configs_manager::parse() noexcept
{
    std::unordered_map<string_view, std::any> variables;

    // read default variables
    for (const auto& [svRuntimeName, value] : m_DefaultVariables)
        if (!m_Variables.contains(svRuntimeName))
            variables[svRuntimeName] = value;

    // read envs
    for (const auto& [svRuntimeName, data] : m_VariableData)
    {
        if (const char* pszEnvValue = std::getenv(to_cstring(data.svEnvName).c_str()))
        {
            std::optional<std::any> optValue = data.pStringToT(to_string(pszEnvValue));
            if (!optValue)
                continue;

            variables[svRuntimeName] = std::move(*optValue);
        }
    }

    // read command lines args
    for (size_t i = 1; i < m_Args.size(); ++i)
    {
        const string_view svArgument = m_Args[i];

        bool        bShortKey = false;
        string_view svKey;
        string_view svValue;

        svKey = string_view(svArgument.begin(), svArgument.end());
        if (svArgument.starts_with(QXT("--")))
        {
            bShortKey = false;
        }
        else if (svArgument.starts_with(QXT("-")))
        {
            bShortKey = true;
        }
        else
        {
            QX_LOG(
                qx::verbosity::warning,
                "Invalid command argument format: {}. "
                "Use \"--key=value\", \"--key value\", \"-k value\", \"--key\", \"-k\" instead.",
                svArgument);
            continue;
        }

        // --key=value / -k=value
        if (const size_t nEqualPos = svKey.find('='); nEqualPos != string_view::npos)
        {
            svValue = string_view(svKey.begin() + nEqualPos + 1, svKey.end());
            svKey   = string_view(svKey.begin(), svKey.begin() + nEqualPos);
        }
        // --key value / -k value
        else if (i + 1 < m_Args.size())
        {
            const string_view svNextArgument = m_Args[i + 1];

            if (!svNextArgument.starts_with(QXT("-")))
            {
                svValue = svNextArgument;
                ++i;
            }
            else
            {
                // --key / -k
                svValue = QXT("true");
            }
        }
        // --key / -k
        else
        {
            svValue = QXT("true");
        }

        if (svKey.empty())
        {
            QX_LOG(qx::verbosity::warning, "Empty command argument key: {}.", svArgument);
            continue;
        }

        if (svValue.empty())
        {
            QX_LOG(qx::verbosity::warning, "Empty command argument value: {}.", svArgument);
            continue;
        }

        for (const auto& [svRuntimeName, data] : m_VariableData)
        {
            const bool bNameMatches =
                bShortKey && svKey == data.svShortCommandLineName || !bShortKey && svKey == data.svFullCommandLineName;
            if (!bNameMatches)
                continue;

            std::optional<std::any> optValue = data.pStringToT(svValue);
            if (!optValue)
                continue;

            variables[svRuntimeName] = std::move(*optValue);
            break;
        }
    }

    bool bAllRequiredVariablesPresent = true;
    for (const auto& [svRuntimeName, data] : m_VariableData)
    {
        if (data.bRequired && !variables.contains(svRuntimeName))
        {
            QX_LOG(qx::verbosity::error, "Required variable missing: {}.", data.svFullCommandLineName);
            bAllRequiredVariablesPresent = false;
        }
    }

    // override default and previous values
    for (const auto& [svRuntimeName, value] : variables)
        m_Variables[svRuntimeName] = value;

    return bAllRequiredVariablesPresent;
}

template<class T>
inline std::expected<T, layered_configs_manager::get_error> layered_configs_manager::get(
    string_view svRuntimeName) const noexcept
{
    const auto value = get(svRuntimeName);
    if (!value)
        return std::unexpected(value.error());

    const auto* pValue = std::any_cast<typename details::layered_config_variable_type<T>::type>(&value->get());
    if (!pValue)
        return std::unexpected(get_error::type_mismatch);

    return *pValue;
}

template<class T>
inline std::expected<void, layered_configs_manager::set_error> layered_configs_manager::set(
    string_view svRuntimeName,
    T           value) noexcept
{
    using stored_type = typename details::layered_config_variable_type<T>::type;
    return set(svRuntimeName, std::any(stored_type(std::move(value))));
}

inline std::expected<std::reference_wrapper<const std::any>, layered_configs_manager::get_error>
    layered_configs_manager::get(string_view svRuntimeName) const noexcept
{
    const auto itValue = m_Variables.find(svRuntimeName);
    if (itValue != m_Variables.end())
        return std::cref(itValue->second);

    const auto itDefault = m_DefaultVariables.find(svRuntimeName);
    if (itDefault == m_DefaultVariables.end())
        return std::unexpected(get_error::unknown_variable);

    return std::cref(itDefault->second);
}

inline std::expected<void, layered_configs_manager::set_error> layered_configs_manager::set(
    string_view svRuntimeName,
    std::any    value) noexcept
{
    const auto it = m_DefaultVariables.find(svRuntimeName);

    if (it == m_DefaultVariables.end())
        return std::unexpected(set_error::unknown_variable);

    if (it->second.type() != value.type())
        return std::unexpected(set_error::type_mismatch);

    m_Variables[it->first] = std::move(value);
    return {};
}

inline std::expected<string, layered_configs_manager::get_error> layered_configs_manager::get_string(
    string_view svRuntimeName) const noexcept
{
    const std::expected<std::reference_wrapper<const std::any>, get_error> value = get(svRuntimeName);
    if (!value)
        return std::unexpected(value.error());

    return m_VariableData.at(svRuntimeName).pTToString(value->get());
}

inline std::expected<void, layered_configs_manager::set_error> layered_configs_manager::set_string(
    string_view svRuntimeName,
    string_view svValue) noexcept
{
    const auto itData = m_VariableData.find(svRuntimeName);
    if (itData == m_VariableData.end())
        return std::unexpected(set_error::unknown_variable);

    auto optValue = itData->second.pStringToT(svValue);
    if (!optValue)
        return std::unexpected(set_error::invalid_value);

    return set(svRuntimeName, std::move(*optValue));
}

inline std::vector<layered_config_variable_info> layered_configs_manager::get_variables() const noexcept
{
    std::vector<layered_config_variable_info> variables;
    for (const auto& [svName, data] : m_VariableData)
        variables.emplace_back(svName, data.svDescription, data.svTypeName, data.svGroupName);

    std::ranges::sort(variables, {}, &layered_config_variable_info::svName);
    return variables;
}

inline void layered_configs_manager::reset() noexcept
{
    m_Variables.clear();
}

template<class T>
void layered_configs_manager::add_variable(
    string_view                                  svRuntimeName,
    const details::layered_config_variable_data& data,
    T                                            defaultValue) noexcept
{
    m_VariableData[svRuntimeName]     = data;
    m_DefaultVariables[svRuntimeName] = typename details::layered_config_variable_type<T>::type(defaultValue);
}

} // namespace qx
