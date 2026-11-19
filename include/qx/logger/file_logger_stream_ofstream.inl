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
    const std::filesystem::path path = prepare_folder_and_get_log_file_path(streamConfig);

    m_File = std::ofstream(
        path,
        std::ios_base::binary
            | (streamConfig.eLogFilePolicy == log_file_policy::clear_then_upend ? std::ios_base::trunc
                                                                                : std::ios_base::app));

    if (!m_File)
    {
        details::get_cerr<char_type>::get() << QXT("Can't open log file ") << path;
        return;
    }

    if (bufferSize.value > 0)
    {
        const unit<size_t, units::data> bytes = convert(bufferSize).to(units::data::bytes);
        m_Buffer.resize(bytes.value);
        m_File.rdbuf()->pubsetbuf(m_Buffer.data(), m_Buffer.size());
    }
}

inline file_logger_stream_ofstream::~file_logger_stream_ofstream()
{
    if (m_File)
        m_File << std::flush;
}

inline void file_logger_stream_ofstream::do_log(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage)
{
    if (m_File)
    {
        const cstring_view svUtf8 = to_utf8(svMessage);
        m_File.write(svUtf8.data(), static_cast<std::streamsize>(svUtf8.size()));
    }
}

inline void file_logger_stream_ofstream::do_flush()
{
    if (m_File)
        m_File << std::flush;
}

} // namespace qx
