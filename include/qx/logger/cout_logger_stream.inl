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
        std::ios_base::sync_with_stdio(false);
    }

    if (streamConfig.bUntieCin)
    {
        std::wcin.tie(nullptr);
        std::wcout.tie(nullptr);
    }
}

inline void cout_logger_stream::do_flush()
{
    details::get_cout<char_type>::get() << std::flush;
    details::get_cerr<char_type>::get() << std::flush;
}

inline void cout_logger_stream::cout_colorized(verbosity eVerbosity, string_view svMessage, const color& rangeColor)
{
    auto& outputStream =
        eVerbosity < verbosity::error ? details::get_cout<char_type>::get() : details::get_cerr<char_type>::get();
    outputStream << terminal_color::font(rangeColor) << svMessage << terminal_color::reset();
}

inline void cout_logger_stream::cout_common(verbosity eVerbosity, string_view svMessage)
{
    auto& outputStream =
        eVerbosity < verbosity::error ? details::get_cout<char_type>::get() : details::get_cerr<char_type>::get();
    outputStream << svMessage;
}

} // namespace qx
