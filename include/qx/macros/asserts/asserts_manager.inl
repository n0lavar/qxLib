/**

    @file      asserts_manager.inl
    @author    Khrapov
    @date      27.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

inline bool asserts_manager::do_assert(
    string_view     svCondition,
    const category& category,
    assert_type     eAssertType,
    string_view     svUserMessage,
    string_view     svFunction,
    string_view     svFile,
    i32             nLine)
{
    if (m_Config.bLogAssertion)
    {
        QX_LOG_REF(category, m_Config.getVerbosity(eAssertType), "[{}] {}", svCondition, svUserMessage);

        // the error must present when debug break is called
        get_logger().flush();
    }

    if (m_Config.onAssertion)
        m_Config.onAssertion(svCondition, category, eAssertType, svUserMessage, svFunction, svFile, nLine);

#if QX_WIN
    return ::IsDebuggerPresent();
#else
    return false;
#endif
}

inline void asserts_manager::exit(const category& category, assert_type eAssertType)
{
    if (m_Config.onExit)
        m_Config.onExit(category, eAssertType);
}

inline const asserts_manager::config& asserts_manager::get_config() const
{
    return m_Config;
}

inline void asserts_manager::set_config(config config)
{
    m_Config = std::move(config);
}

} // namespace qx
