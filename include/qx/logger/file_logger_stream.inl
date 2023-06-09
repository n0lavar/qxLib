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

    m_WCharFile = std::basic_ofstream<wchar_t>(path, openingMode);
    if (!m_WCharFile)
    {
        std::wcerr << L"Can't open log file " << sLogFile;
    }
    else
    {
        QX_DISABLE_MSVC_WARNINGS(4996);
        m_WCharFile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
        QX_RESTORE_MSVC_WARNINGS(4996);
    }
}

inline file_logger_stream::~file_logger_stream()
{
    if (m_WCharFile)
        m_WCharFile << L"\n\n\n" << std::flush;
}

inline void file_logger_stream::flush()
{
    QX_PERF_SCOPE(CatLogger, "Flush to the file");
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

template<class char_t>
inline void file_logger_stream::log_file(
    std::basic_string_view<char_t> svMessage,
    const log_unit&                logUnit,
    log_level                      eLogLevel)
{
    QX_PERF_SCOPE(CatLogger, "Log to the file");

    if constexpr (std::is_same_v<char_t, char>)
        m_WCharFile << qx::to_wstring(svMessage);
    else
        m_WCharFile << svMessage;
}

} // namespace qx
