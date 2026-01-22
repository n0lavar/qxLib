/**

    @file      fwrite_logger_stream.inl
    @author    Khrapov
    @date      18.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline fwrite_logger_stream::fwrite_logger_stream(const config& streamConfig)
    : base_standard_streams_stream(streamConfig)
{
}

inline void fwrite_logger_stream::do_flush()
{
    fflush(stdout);
    fflush(stderr);
}

inline void fwrite_logger_stream::cout_colorized(verbosity eVerbosity, string_view svMessage, const color& rangeColor)
{
    check_previous_message(eVerbosity);

    FILE* output = !is_error(eVerbosity) ? stdout : stderr;
    terminal_color::font(rangeColor).write(output);
    fwrite(svMessage.data(), sizeof(char_type), svMessage.size(), output);
    terminal_color::reset().write(output);
}

inline void fwrite_logger_stream::cout_common(verbosity eVerbosity, string_view svMessage)
{
    check_previous_message(eVerbosity);

    FILE* output = !is_error(eVerbosity) ? stdout : stderr;
    fwrite(svMessage.data(), sizeof(char_type), svMessage.size(), output);
}

} // namespace qx
