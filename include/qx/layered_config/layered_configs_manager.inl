/**

    @file      layered_configs_manager.inl
    @author    Khrapov
    @date      12.05.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

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
struct layered_config_variable_type<cstring_view>
{
    using type = cstring;
};

} // namespace details

inline void layered_configs_manager::set_app_description(cstring sAppDescription) noexcept
{
    m_sAppDescription = std::move(sAppDescription);
}

inline void layered_configs_manager::set_args(int argc, char* argv[]) noexcept
{
    m_Args = std::span(argv, argc);
}

inline bool layered_configs_manager::show_help() const noexcept
{
    if (!contains_if(
            m_Args,
            [](const char* const pszValue)
            {
                cstring_view svValue(pszValue);
                return svValue == "--help" || svValue == "-h";
            }))
    {
        return false;
    }

    struct data_with_runtime_name : details::layered_config_variable_data
    {
        cstring_view svRuntimeName;
    };

    std::map<cstring_view, std::vector<data_with_runtime_name>> groups;
    for (const auto& [svRuntimeName, data] : m_VariableData)
    {
        groups[data.svGroupName].push_back(data_with_runtime_name { { data }, svRuntimeName });
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

    cstring sHelp;
    if (!groups.empty())
    {
        constexpr cstring_view svRequired = "required  ";

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

        sHelp.append_format("\n\nUsage: {} [options]\n", m_Args[0]);
        sHelp += "Using formats: [--key], [-k], [--key=value], [-k=value], [--key value], [-k value]\n\n";

        if (!m_sAppDescription.empty())
            sHelp.append_format("{}\n\n", m_sAppDescription);

        for (const auto& [svGroupName, lines] : groups)
        {
            if (!svGroupName.empty())
                sHelp.append_format("{}:\n", svGroupName);
            else
                sHelp += "General options:\n";

            sHelp +=
                "------------------------------------------------------------------------------------------------------"
                "------------------\n";

            for (const data_with_runtime_name& line : lines)
            {
                sHelp.append_format(
                    "{:<{}}  {:<{}}  {:<{}}  {:<{}}{}\n",
                    line.svFullCommandLineName,
                    nMaxFullCommandLineNameLength,
                    line.svShortCommandLineName,
                    nMaxShortCommandLineNameLength,
                    line.svTypeName,
                    nMaxTypeNameLength,
                    line.bRequired ? svRequired
                                   : cstring_view(line.pTToString(m_Variables.at(line.svRuntimeName)) + "  "),
                    nMaxRequiredNameLength,
                    line.svDescription);
            }

            sHelp += "\n";
        }
    }
    else
    {
        sHelp += "This app doesn't have any command line arguments.\n\n";
        if (!m_sAppDescription.empty())
            sHelp.append_format("{}\n\n", m_sAppDescription);
    }

    QX_LOG(qx::verbosity::important, qx::to_string(sHelp));

    return true;
}

inline bool layered_configs_manager::parse() noexcept
{
    std::unordered_map<cstring_view, std::any> variables;

    // read default variables
    for (const auto& [svRuntimeName, value] : m_DefaultVariables)
        if (!m_Variables.contains(svRuntimeName))
            variables[svRuntimeName] = value;

    // read envs
    for (const auto& [svRuntimeName, data] : m_VariableData)
    {
        if (const char* pszEnvValue = std::getenv(cstring(data.svEnvName).c_str()))
        {
            std::optional<std::any> optValue = data.pStringToT(pszEnvValue);
            if (!optValue)
                continue;

            variables[svRuntimeName] = std::move(*optValue);
        }
    }

    // read command lines args
    for (size_t i = 1; i < m_Args.size(); ++i)
    {
        const cstring_view svArgument = m_Args[i];

        bool         bShortKey = false;
        cstring_view svKey;
        cstring_view svValue;

        svKey = cstring_view(svArgument.begin(), svArgument.end());
        if (svArgument.starts_with("--"))
        {
            bShortKey = false;
        }
        else if (svArgument.starts_with("-"))
        {
            bShortKey = true;
        }
        else
        {
            QX_LOG(
                qx::verbosity::warning,
                "Invalid command argument format: {}. "
                "Use \"--key=value\", \"--key value\", \"-k value\", \"--key\", \"-k\" instead.",
                qx::to_string(svArgument));
            continue;
        }

        // --key=value / -k=value
        if (const size_t nEqualPos = svKey.find('='); nEqualPos != cstring_view::npos)
        {
            svValue = cstring_view(svKey.begin() + nEqualPos + 1, svKey.end());
            svKey   = cstring_view(svKey.begin(), svKey.begin() + nEqualPos);
        }
        // --key value / -k value
        else if (i + 1 < m_Args.size())
        {
            const cstring_view svNextArgument = m_Args[i + 1];

            if (!svNextArgument.starts_with("-"))
            {
                svValue = svNextArgument;
                ++i;
            }
            else
            {
                // --key / -k
                svValue = "true";
            }
        }
        // --key / -k
        else
        {
            svValue = "true";
        }

        if (svKey.empty())
        {
            QX_LOG(qx::verbosity::warning, "Empty command argument key: {}.", qx::to_string(svArgument));
            continue;
        }

        if (svValue.empty())
        {
            QX_LOG(qx::verbosity::warning, "Empty command argument value: {}.", qx::to_string(svArgument));
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
            QX_LOG(qx::verbosity::error, "Required variable missing: {}.", qx::to_string(data.svFullCommandLineName));
            bAllRequiredVariablesPresent = false;
        }
    }

    // override default and previous values
    for (const auto& [svRuntimeName, value] : variables)
        m_Variables[svRuntimeName] = value;

    return bAllRequiredVariablesPresent;
}

template<class T>
inline std::optional<T> layered_configs_manager::get(cstring_view svRuntimeName) const noexcept
{
    auto it = m_Variables.find(svRuntimeName);
    if (it == m_Variables.end())
    {
        it = m_DefaultVariables.find(svRuntimeName);
        if (it == m_DefaultVariables.end())
            return std::nullopt;
    }

    const auto* pValue = std::any_cast<typename details::layered_config_variable_type<T>::type>(&it->second);
    if (!pValue)
        return std::nullopt;

    return *pValue;
}

template<class T>
inline bool layered_configs_manager::set(cstring_view svRuntimeName, T value) noexcept
{
    // set a value only if types match
    const auto it = m_DefaultVariables.find(svRuntimeName);
    if (it == m_DefaultVariables.end())
        return false;

    if (!std::any_cast<typename details::layered_config_variable_type<T>::type>(&it->second))
        return false;

    m_Variables[svRuntimeName] = typename details::layered_config_variable_type<T>::type(std::move(value));
    return true;
}

inline void layered_configs_manager::reset() noexcept
{
    m_Variables.clear();
}

template<class T>
void layered_configs_manager::add_variable(
    cstring_view                                 svRuntimeName,
    const details::layered_config_variable_data& data,
    T                                            defaultValue) noexcept
{
    m_VariableData[svRuntimeName]     = data;
    m_DefaultVariables[svRuntimeName] = typename details::layered_config_variable_type<T>::type(defaultValue);
}

} // namespace qx
