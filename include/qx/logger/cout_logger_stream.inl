/**

    @file      cout_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline cout_logger_stream::cout_logger_stream(std::optional<config> optStreamConfig)
    : base_standard_streams_stream(optStreamConfig ? *optStreamConfig : config())
{
    const config streamConfig = optStreamConfig ? *optStreamConfig : config();

    if (streamConfig.bDisableStdioSync)
    {
        // Optimization
        // Don't synchronize to the standard C streams after each input/output operation
        std::ios_base::sync_with_stdio(false);
    }

    if (streamConfig.bUntieCin)
    {
        // This unties cin from cout.
        // Tied streams ensure that one stream is flushed automatically
        // before each I/O operation on the other stream
        std::wcin.tie(nullptr);
        std::wcout.tie(nullptr);
    }
}

inline void cout_logger_stream::do_flush()
{
    std::wcerr << std::flush;
    std::wcout << std::flush;
}

inline void cout_logger_stream::cout_colorized(verbosity eVerbosity, string_view svMessage, const color& rangeColor)
{
    std::wostream& outputStream = eVerbosity < verbosity::error ? std::wcout : std::wcerr;

    // possible allocation when qx::char_type != wchar_t
    auto sWideMessage = to_wstring(svMessage);

    outputStream << terminal_color::font(rangeColor) << sWideMessage << terminal_color::reset();
}

inline void cout_logger_stream::cout_common(verbosity eVerbosity, string_view svMessage)
{
    std::wostream& outputStream = eVerbosity < verbosity::error ? std::wcout : std::wcerr;

    // possible allocation when qx::char_type != wchar_t
    auto sWideMessage = to_wstring(svMessage);

    outputStream << sWideMessage;
}

} // namespace qx
