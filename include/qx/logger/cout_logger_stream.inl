/**

    @file      cout_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline cout_logger_stream::cout_logger_stream(
    bool bUseColors,
    bool bDisableStdioSync,
    bool bUntieCin)
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
    }
}

inline void cout_logger_stream::process_output(
    std::string_view svMessage,
    const log_unit&  logUnit,
    log_level        eLogLevel)
{
    std::string_view svColor;
    switch (eLogLevel)
    {
    case log_level::errors:
        svColor = auto_terminal_color::yellow;
        break;

    case log_level::asserts:
        svColor = auto_terminal_color::red;
        break;
    }

    if (!svColor.empty() && m_bUsingColors)
    {
        auto_terminal_color atc(svColor);
        std::cout << svMessage;
    }
    else
    {
        std::cout << svMessage;
    }
}

inline void cout_logger_stream::set_using_colors(bool bUsingColors) noexcept
{
    m_bUsingColors = bUsingColors;
}

} // namespace qx
