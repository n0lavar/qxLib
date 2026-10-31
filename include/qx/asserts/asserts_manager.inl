/**

    @file      asserts_manager.inl
    @author    Khrapov
    @date      27.12.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

inline bool is_debugger_present() noexcept
{
#if QX_WIN
    return ::IsDebuggerPresent() != 0;
#elif QX_LINUX
    std::FILE* pStatus = std::fopen("/proc/thread-self/status", "r");
    if (!pStatus)
        return false;

    char buffer[512];
    int  nTracerPid = 0;
    while (std::fgets(buffer, sizeof(buffer), pStatus))
    {
        if (std::sscanf(buffer, "TracerPid: %d", &nTracerPid) == 1)
            break;
    }
    std::fclose(pStatus);
    return nTracerPid != 0;
#elif QX_MACOS && (QX_WITH_DEBUG_INFO)
    int        mib[] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, getpid() };
    kinfo_proc info {};
    size_t     nSize = sizeof(info);
    return sysctl(mib, 4, &info, &nSize, nullptr, 0) == 0 && (info.kp_proc.p_flag & P_TRACED) != 0;
#else
    return false;
#endif
}

inline bool asserts_manager::do_assert(
    string_view     svCondition,
    const category& category,
    assert_type     eAssertType,
    string          sUserMessage,
    string_view     svFunction,
    string_view     svFile,
    i32             nLine)
{
    config currentConfig;
    {
        std::shared_lock lock(m_Mutex);
        for (const interceptor_entry& interceptor : m_Interceptors)
            if (interceptor.callback(svCondition, category, eAssertType, sUserMessage, svFunction, svFile, nLine))
                return false;

        currentConfig = m_Config;
    }

    if (currentConfig.bLogAssertion)
    {
        QX_LOG_REF(category, currentConfig.getVerbosity(eAssertType), "[{}] {}", svCondition, sUserMessage);

        // the error must present when debug break is called
        get_logger().flush();

        std::shared_lock _(get_logger().get_streams_mutex());
        if (auto* pStream = get_logger().get_stream<error_context_stream>())
            pStream->on_error(std::this_thread::get_id());
    }

    if (currentConfig.onAssertion)
        currentConfig.onAssertion(svCondition, category, eAssertType, sUserMessage, svFunction, svFile, nLine);

    return is_debugger_present();
}

inline void asserts_manager::exit(const category& category, assert_type eAssertType)
{
    const config currentConfig = get_config();
    if (currentConfig.onExit)
        currentConfig.onExit(category, eAssertType);
}

inline asserts_manager::config asserts_manager::get_config() const
{
    std::shared_lock lock(m_Mutex);
    return m_Config;
}

inline void asserts_manager::set_config(config config)
{
    std::unique_lock lock(m_Mutex);
    m_Config = std::move(config);
}

inline void asserts_manager::add_interceptor(const void* pOwner, interceptor_func interceptor)
{
    std::unique_lock lock(m_Mutex);
    m_Interceptors.push_back({ pOwner, std::move(interceptor) });
}

inline void asserts_manager::remove_interceptor(const void* pOwner)
{
    std::unique_lock lock(m_Mutex);
    std::erase_if(
        m_Interceptors,
        [pOwner](const interceptor_entry& entry)
        {
            return entry.pOwner == pOwner;
        });
}

} // namespace qx
