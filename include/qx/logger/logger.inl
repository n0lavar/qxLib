/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class char_type>
inline void logger::log(
    log_level        eLogLevel,
    const char_type* pszFormat,
    log_tag          tag,
    const char*      pszFile,
    const char*      pszFunction,
    int              nLine,
    ...)
{
    if (eLogLevel == log_level::none)
        return;

    va_list args;
    va_start(args, nLine);

    do_log(eLogLevel, pszFormat, tag.get_name(), pszFile, pszFunction, nLine, args);

    va_end(args);
}

template<class char_type>
inline void logger::log(
    log_level                      eLogLevel,
    const basic_string<char_type>& sFormat,
    log_tag                        tag,
    const char*                    pszFile,
    const char*                    pszFunction,
    int                            nLine,
    ...)
{
    va_list args;
    va_start(args, nLine);

    do_log(eLogLevel, sFormat.c_str(), tag.get_name(), pszFile, pszFunction, nLine, args);

    va_end(args);
}

template<class char_type>
inline void logger::do_log(
    log_level        eLogLevel,
    const char_type* pszFormat,
    const char*      pszTag,
    const char*      pszFile,
    const char*      pszFunction,
    int              nLine,
    va_list          args)
{
    va_list argsCopy;
    va_copy(argsCopy, args);

    std::lock_guard lock(m_Mutex);
    for (const auto& stream : m_Streams)
        stream->log(eLogLevel, pszFormat, pszTag, pszFile, pszFunction, nLine, argsCopy);

    va_end(argsCopy);
}

inline void logger::add_stream(std::unique_ptr<base_logger_stream> pStream)
{
    m_Streams.push_back(std::move(pStream));
}

} // namespace qx
