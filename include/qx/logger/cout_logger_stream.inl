/**

    @file      cout_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void cout_logger_stream::process_output(
    std::string_view svMessage,
    log_unit         logUnit)
{
    std::string_view svColor;
    switch (logUnit.pUnitInfo->eUnitLevel)
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
