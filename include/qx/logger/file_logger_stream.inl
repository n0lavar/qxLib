/**

    @file      file_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline file_logger_stream::file_logger_stream(bool bAlwaysFlush, log_file_policy eLogFilePolicy, string_view svFileName)
    : base_logger_stream(bAlwaysFlush)
{
    string                  sLogFile    = svFileName;
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
        string& sTime = get_log_buffer().sMessage;
        sTime.clear();
        append_time_string(sTime, L'-', L'-');
        sLogFile += L'_';
        sLogFile += sTime;
    }
    break;
    }

    sLogFile += L".log";

    const wstring               sWideLogFile = to_wstring(sLogFile);
    const std::filesystem::path path(sWideLogFile.c_str());
    if (path.has_parent_path() && !std::filesystem::exists(path.parent_path()))
    {
        if (!std::filesystem::create_directory(path.parent_path()))
        {
            std::wcerr << L"Can't create output folder " << sWideLogFile;
            return;
        }
    }

    m_File = std::basic_ofstream<wchar_t>(path, openingMode);
    if (!m_File)
    {
        std::wcerr << L"Can't open log file " << sWideLogFile;
        return;
    }

    QX_DISABLE_MSVC_WARNINGS(4996);
    m_File.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    QX_RESTORE_MSVC_WARNINGS(4996);
}

inline file_logger_stream::~file_logger_stream()
{
    if (m_File)
        m_File << L"\n\n\n" << std::flush;
}

inline void file_logger_stream::flush()
{
    QX_PERF_SCOPE(CatLogger, "Flush to the file");
    m_File << std::flush;
}

inline void file_logger_stream::do_log(
    string_view                            svMessage,
    const log_unit&                        logUnit,
    const std::vector<logger_color_range>& colors,
    verbosity                              eVerbosity)
{
    QX_PERF_SCOPE(CatLogger, "Log to the file");
    m_File << qx::to_wstring(svMessage);
}

} // namespace qx
