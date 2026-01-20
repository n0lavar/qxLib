/**

    @file      file_logger_stream_fopen.inl
    @author    Khrapov
    @date      15.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline file_logger_stream_fopen::file_logger_stream_fopen(
    const config&             streamConfig,
    unit<size_t, units::data> bufferSize)
    : base_file_logger_stream(streamConfig)
{
    std::ios_base::sync_with_stdio(false);

    const char* pszOpeningMode = streamConfig.eLogFilePolicy == log_file_policy::clear_then_uppend ? "wb" : "ab";

    const std::filesystem::path path =
        create_folder_and_get_log_file_path(streamConfig.eLogFilePolicy, streamConfig.svFileName);

    QX_DISABLE_MSVC_WARNINGS(4996);
    m_pFile = std::fopen(path.generic_string().c_str(), pszOpeningMode);
    if (!m_pFile)
    {
        string sLastError = to_string(std::strerror(errno));
        details::get_cerr<char_type>::get() << QXT("Can't open log file: ") << path << QXT(", error: ") << sLastError;
        return;
    }
    QX_RESTORE_MSVC_WARNINGS(4996);

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

inline void file_logger_stream_fopen::do_log(const category& category, verbosity eVerbosity, string_view svMessage)
{
    if (m_pFile)
    {
#if QX_WIN || QX_CONF_USE_CHAR
        std::fwrite(svMessage.data(), sizeof(char_type), svMessage.size(), m_pFile);
#else
        std::array<char16_t, 2048> chunk;

        const char_type* pData           = svMessage.data();
        size_t           nCharsRemaining = svMessage.size();

        while (nCharsRemaining > 0)
        {
            size_t nCharsToTake = std::min(nCharsRemaining, chunk.size());
            for (size_t i = 0; i < nCharsToTake; ++i)
            {
                chunk[i] = static_cast<char16_t>(static_cast<char16_t>(pData[i]) & 0xFFFFu);
            }

            std::fwrite(chunk.data(), sizeof(char16_t), nCharsToTake, m_pFile);

            pData += nCharsToTake;
            nCharsRemaining -= nCharsToTake;
        }
#endif
    }
}

inline void file_logger_stream_fopen::do_flush()
{
    if (m_pFile)
        std::fflush(m_pFile);
}

} // namespace qx
