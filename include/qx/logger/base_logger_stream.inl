/**

    @file      base_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/

QX_SET_FILE_CATEGORY(CatLogger);

namespace qx
{

namespace details
{

template<class char_t /* = char */>
struct get_cerr
{
    static auto& get() noexcept
    {
        return std::cerr;
    }
};

template<>
struct get_cerr</* class char_t = */ wchar_t>
{
    static auto& get() noexcept
    {
        return std::wcerr;
    }
};

template<class char_t /* = char */>
struct get_cout
{
    static auto& get() noexcept
    {
        return std::cout;
    }
};

template<>
struct get_cout</* class char_t = */ wchar_t>
{
    static auto& get() noexcept
    {
        return std::wcout;
    }
};

} // namespace details

inline base_logger_stream::base_logger_stream(const config& streamConfig) noexcept
    : m_pMutex(std::make_unique<std::recursive_mutex>())
    , m_eMinFlushVerbosity(streamConfig.eMinFlushVerbosity)
    , m_bProtectLog(streamConfig.bProtectLog)
{
}

inline compile_pattern_result base_logger_stream::set_pattern(pattern_string_t sPattern) noexcept
{
    const compile_pattern_result eResult = compile_pattern(sPattern);

    if (eResult == compile_pattern_result::ok)
        m_optPattern = std::move(sPattern);

    return eResult;
}

inline std::optional<string_view> base_logger_stream::get_pattern() const noexcept
{
    return m_optPattern ? std::optional<string_view>(*m_optPattern) : std::nullopt;
}

inline void base_logger_stream::log(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage)
{
    QX_PERF_SCOPE("Log");

    if (m_bProtectLog)
        m_pMutex->lock();

    do_log(category, eVerbosity, threadId, messageTime, svFile, svFunction, nLine, svMessage);

    if (eVerbosity >= m_eMinFlushVerbosity)
        flush();

    if (m_bProtectLog)
        m_pMutex->unlock();
}

inline void base_logger_stream::flush()
{
    QX_PERF_SCOPE("Flush");

    if (m_bProtectLog)
        m_pMutex->lock();

    do_flush();

    if (m_bProtectLog)
        m_pMutex->unlock();
}

inline bool base_logger_stream::log_unconditionally_required(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine) const noexcept
{
    return false;
}

} // namespace qx
