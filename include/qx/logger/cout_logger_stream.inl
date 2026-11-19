/**

    @file      cout_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline cout_logger_stream::cout_logger_stream(std::optional<config> optStreamConfig) noexcept
    : base_standard_streams_stream(optStreamConfig ? *optStreamConfig : config())
{
    const config streamConfig = optStreamConfig ? *optStreamConfig : config();

    if (streamConfig.bDisableStdioSync)
    {
        std::ios_base::sync_with_stdio(false);
    }

    if (streamConfig.bUntieCin)
    {
        std::cout.tie(nullptr);
        std::cerr.tie(nullptr);
    }
}

inline void cout_logger_stream::do_flush()
{
    std::cout << std::flush;
    std::cerr << std::flush;
}

inline void cout_logger_stream::cout_colorized(verbosity eVerbosity, string_view svMessage, const color& rangeColor)
{
    check_previous_message(eVerbosity);

    std::ostream&      outputStream = !is_error(eVerbosity) ? std::cout : std::cerr;
    const cstring_view svUtf8       = to_utf8(svMessage);
    outputStream << terminal_color::font(rangeColor);
    outputStream.write(svUtf8.data(), static_cast<std::streamsize>(svUtf8.size()));
    outputStream << terminal_color::reset();
}

inline void cout_logger_stream::cout_common(verbosity eVerbosity, string_view svMessage)
{
    check_previous_message(eVerbosity);

    std::ostream&      outputStream = !is_error(eVerbosity) ? std::cout : std::cerr;
    const cstring_view svUtf8       = to_utf8(svMessage);
    outputStream.write(svUtf8.data(), static_cast<std::streamsize>(svUtf8.size()));
}

} // namespace qx
