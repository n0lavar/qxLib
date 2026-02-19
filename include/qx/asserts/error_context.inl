/**

    @file      error_context.inl
    @author    Khrapov
    @date      10.02.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline error_context::error_context(verbosity eMinCaptureVerbosity, string_view svHeader, string_view svFooter) noexcept
    : m_svHeader(svHeader)
    , m_svFooter(svFooter)
    , m_eMinCatchVerbosity(eMinCaptureVerbosity)
{
    std::shared_lock _(get_logger().get_streams_mutex());

    if (auto* pStream = get_logger().get_stream<error_context_stream>())
    {
        m_OnMessagesToken = (*pStream->get_on_messages().lock())[std::this_thread::get_id()].add_token(
            *this,
            &error_context::on_message);
        m_OnErrorToken = pStream->get_on_error().lock()->add_token(*this, &error_context::on_error);
    }
}

inline error_context::~error_context() noexcept
{
    std::shared_lock _(get_logger().get_streams_mutex());

    if (auto* pStream = get_logger().get_stream<error_context_stream>())
    {
        (*pStream->get_on_messages().lock())[std::this_thread::get_id()].remove(m_OnMessagesToken);
        pStream->get_on_error().lock()->remove(m_OnErrorToken);
    }
}

inline void error_context::on_message(verbosity eVerbosity, string_view svMessage) noexcept
{
    if (eVerbosity >= m_eMinCatchVerbosity)
        m_sMessages += svMessage;
}

inline void error_context::on_error() noexcept
{
    if (!m_sMessages.empty())
    {
        m_sMessages.insert(0, QXT('\n'));
        m_sMessages.insert(0, m_svHeader);
        m_sMessages.insert(0, QXT('\n'));
        m_sMessages += m_svFooter;
        QX_LOG(qx::verbosity::log, m_sMessages);
    }
}

} // namespace qx
