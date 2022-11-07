/**

    @file      cout_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline cout_logger_stream::cout_logger_stream(bool bUseColors, bool bDisableStdioSync, bool bUntieCin)
    : m_bUsingColors(bUseColors)
{
    if (bDisableStdioSync)
    {
        // Optimization
        // Don't synchronize to the standard C streams after each input/output operation
        std::ios_base::sync_with_stdio(false);
    }

    if (bUntieCin)
    {
        // This unties cin from cout.
        // Tied streams ensure that one stream is flushed automatically
        // before each I/O operation on the other stream
        std::cin.tie(nullptr);
        std::wcin.tie(nullptr);
    }
}

inline void cout_logger_stream::do_log(std::string_view svMessage, const log_unit& logUnit, log_level eLogLevel)
{
    log_cout(svMessage, logUnit, eLogLevel);
}

inline void cout_logger_stream::do_log(std::wstring_view svMessage, const log_unit& logUnit, log_level eLogLevel)
{
    log_cout(svMessage, logUnit, eLogLevel);
}

inline void cout_logger_stream::set_using_colors(bool bUsingColors) noexcept
{
    m_bUsingColors = bUsingColors;
}

template<class char_type>
inline std::basic_ostream<char_type>& cout_logger_stream::get_cout() noexcept
{
    if constexpr (std::is_same_v<char_type, char>)
        return std::cout;
    else
        return std::wcout;
}

template<class char_type>
inline void cout_logger_stream::log_cout(
    std::basic_string_view<char_type> svMessage,
    const log_unit&                   logUnit,
    log_level                         eLogLevel)
{
    if (m_bUsingColors)
    {
        std::string_view svColor;
        switch (eLogLevel)
        {
        case log_level::warning:
            svColor = auto_terminal_color::yellow_bold;
            break;

        case log_level::error:
            svColor = auto_terminal_color::yellow;
            break;

        case log_level::critical:
            svColor = auto_terminal_color::red;
            break;
        }

        auto_terminal_color atc(svColor);
        get_cout<char_type>() << svMessage;
    }
    else
    {
        get_cout<char_type>() << svMessage;
    }
}


} // namespace qx
