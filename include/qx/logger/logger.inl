/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class char_t>
inline void logger::log(
    log_level       eLogLevel,
    const char_t*   pszFormat,
    const category& category,
    const char*     pszFile,
    const char*     pszFunction,
    int             nLine,
    ...)
{
    if (eLogLevel == log_level::none)
        return;

    va_list args;
    va_start(args, nLine);

    do_log(eLogLevel, pszFormat, category, pszFile, pszFunction, nLine, args);

    va_end(args);
}

template<class char_t>
inline void logger::log(
    log_level                   eLogLevel,
    const basic_string<char_t>& sFormat,
    const category&             category,
    const char*                 pszFile,
    const char*                 pszFunction,
    int                         nLine,
    ...)
{
    va_list args;
    va_start(args, nLine);

    do_log(eLogLevel, sFormat.c_str(), category, pszFile, pszFunction, nLine, args);

    va_end(args);
}

template<class char_t>
inline void logger::do_log(
    log_level       eLogLevel,
    const char_t*   pszFormat,
    const category& category,
    const char*     pszFile,
    const char*     pszFunction,
    int             nLine,
    va_list         args)
{
    va_list argsCopy;
    va_copy(argsCopy, args);

    for (const auto& stream : m_Streams)
        stream->log(eLogLevel, pszFormat, category, pszFile, pszFunction, nLine, argsCopy);

    va_end(argsCopy);
}

inline void logger::flush()
{
    for (const auto& stream : m_Streams)
        stream->flush();
}

inline void logger::add_stream(std::unique_ptr<base_logger_stream> pStream) noexcept
{
    m_Streams.push_back(std::move(pStream));
}

inline void logger::reset() noexcept
{
    m_Streams.clear();
}

} // namespace qx
