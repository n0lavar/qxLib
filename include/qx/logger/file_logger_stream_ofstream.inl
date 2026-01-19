/**

    @file      file_logger_stream_ofstream.inl
    @author    Khrapov
    @date      14.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline file_logger_stream_ofstream::file_logger_stream_ofstream(
    const config&             streamConfig,
    unit<size_t, units::data> bufferSize)
    : base_file_logger_stream(streamConfig)
{
    std::ios_base::openmode openingMode =
        streamConfig.eLogFilePolicy == log_file_policy::clear_then_uppend ? std::ios_base::trunc : std::ios_base::app;
    openingMode |= std::ios_base::binary;

    const std::filesystem::path path =
        create_folder_and_get_log_file_path(streamConfig.eLogFilePolicy, streamConfig.svFileName);
    m_File = std::basic_ofstream<char_type>(path, openingMode);
    if (!m_File)
    {
        details::get_cerr<char_type>::get() << QXT("Can't open log file ") << path;
        return;
    }

    if (bufferSize.value > 0)
    {
        const unit<size_t, units::data> bytes = convert(bufferSize).to(units::data::bytes);
        m_Buffer.resize(bytes.value / sizeof(char_type));
        m_File.rdbuf()->pubsetbuf(m_Buffer.data(), m_Buffer.size());
    }

    QX_DISABLE_MSVC_WARNINGS(4996);
    m_File.imbue(std::locale(std::locale(), new std::codecvt_utf16<char_type, 0x10ffff, std::little_endian>));
    QX_RESTORE_MSVC_WARNINGS(4996);
}

inline file_logger_stream_ofstream::~file_logger_stream_ofstream()
{
    if (m_File)
        m_File << std::flush;
}

inline void file_logger_stream_ofstream::do_log(const category& category, verbosity eVerbosity, string_view svMessage)
{
    if (m_File)
        m_File.write(svMessage.data(), svMessage.size());
}

inline void file_logger_stream_ofstream::do_flush()
{
    if (m_File)
        m_File << std::flush;
}

} // namespace qx
