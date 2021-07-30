//==============================================================================
//
//!\file                      cout_logger_stream.inl
//
//!\brief       Contains qx::cout_logger_stream class
//!\details     ~
//
//!\author      Khrapov
//!\date        30.07.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn             qx::cout_logger_stream::process_output
//
//!\brief  Output to std::cout
//!\param  svMessage - message string
//!\param  logUnit   - log unit info
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void cout_logger_stream::process_output(
    std::string_view    svMessage,
    log_unit            logUnit)
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

}
