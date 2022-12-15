/**

    @file      file_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline file_logger_stream::file_logger_stream(
    bool              bAlwaysFlush,
    log_file_policy   eLogFilePolicy,
    std::wstring_view svFileName)
    : base_logger_stream(bAlwaysFlush)
{
    wstring                 sLogFile    = svFileName;
    std::ios_base::openmode openingMode = std::ios_base::app;
    switch (eLogFilePolicy)
    {
    case log_file_policy::clear_then_uppend:
    {
        openingMode = std::ios_base::trunc;
    }
    break;

    case log_file_policy::time_name:
    {
        wstring& sTime = get_log_buffer<wchar_t>().sFormat;
        format_time_string(sTime, L'-', L'-');
        sLogFile += L'_';
        sLogFile += sTime;
    }
    break;
    }

    sLogFile += L".log";

    const std::filesystem::path path(sLogFile.c_str());

    m_CharFile = std::basic_ofstream<char>(path, openingMode);
    if (!m_CharFile)
        std::wcerr << L"Can't open log file " << sLogFile;

    m_WCharFile = std::basic_ofstream<wchar_t>(path, openingMode);
    if (!m_WCharFile)
        std::wcerr << L"Can't open log file " << sLogFile;
}

inline file_logger_stream::~file_logger_stream()
{
    if (m_CharFile)
        m_CharFile << "\n\n\n" << std::flush;
}

inline void file_logger_stream::flush()
{
    m_CharFile << std::flush;
    m_WCharFile << std::flush;
}

inline void file_logger_stream::do_log(
    std::string_view                       svMessage,
    const log_unit&                        logUnit,
    const std::vector<logger_color_range>& colors,
    log_level                              eLogLevel)
{
    log_file(svMessage, logUnit, eLogLevel);
}

inline void file_logger_stream::do_log(
    std::wstring_view                      svMessage,
    const log_unit&                        logUnit,
    const std::vector<logger_color_range>& colors,
    log_level                              eLogLevel)
{
    log_file(svMessage, logUnit, eLogLevel);
}

template<class char_type>
inline void file_logger_stream::log_file(
    std::basic_string_view<char_type> svMessage,
    const log_unit&                   logUnit,
    log_level                         eLogLevel)
{
    if constexpr (std::is_same_v<char_type, char>)
        m_CharFile << svMessage;
    else
        m_WCharFile << svMessage;
}

} // namespace qx
