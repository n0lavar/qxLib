/**

    @file      file_logger_stream_fopen.inl
    @author    Khrapov
    @date      15.01.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline file_logger_stream_fopen::file_logger_stream_fopen(
    const config&             streamConfig,
    unit<size_t, units::data> bufferSize) noexcept
    : base_file_logger_stream(streamConfig)
{
    const std::filesystem::path path = prepare_folder_and_get_log_file_path(streamConfig);

    std::ios_base::sync_with_stdio(false);

    m_pFile = std::fopen(
        path.generic_string().c_str(),
        streamConfig.eLogFilePolicy == log_file_policy::clear_then_upend ? "wb" : "ab");
    if (!m_pFile)
    {
        string sLastError = to_string(std::strerror(errno));
        details::get_cerr<char_type>::get() << QXT("Can't open log file: ") << path << QXT(", error: ") << sLastError;
        return;
    }

    if (bufferSize.value > 0)
    {
        const unit<size_t, units::data> bytes = convert(bufferSize).to(units::data::bytes);
        m_Buffer.resize(bytes.value);
        std::setvbuf(m_pFile, m_Buffer.data(), _IOFBF, m_Buffer.size());
    }
}

inline file_logger_stream_fopen::file_logger_stream_fopen(file_logger_stream_fopen&& other) noexcept
    : base_file_logger_stream(std::move(other))
{
    std::swap(m_Buffer, other.m_Buffer);
    std::swap(m_pFile, other.m_pFile);
}

inline file_logger_stream_fopen::~file_logger_stream_fopen()
{
    if (m_pFile)
    {
        std::fclose(m_pFile);
        m_pFile = nullptr;
    }
}

inline void file_logger_stream_fopen::do_log(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage)
{
    if (m_pFile)
    {
        const cstring_view svUtf8 = to_utf8(svMessage);
        std::fwrite(svUtf8.data(), sizeof(char), svUtf8.size(), m_pFile);
    }
}

inline void file_logger_stream_fopen::do_flush()
{
    if (m_pFile)
        std::fflush(m_pFile);
}

} // namespace qx
