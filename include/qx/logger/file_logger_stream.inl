/**

    @file      file_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

namespace details
{

template<class char_t /* = char */>
struct get_cerr
{
    static auto& get()
    {
        return std::cerr;
    }
};

template<>
struct get_cerr</* class char_t = */ wchar_t>
{
    static auto& get()
    {
        return std::wcerr;
    }
};

} // namespace details

inline file_logger_stream::file_logger_stream(file_logger_config config)
    : base_logger_stream(config.bProtectLog, config.bAlwaysFlush)
{
    string                  sLogFile    = config.svFileName;
    std::ios_base::openmode openingMode = std::ios_base::app;
    switch (config.eLogFilePolicy)
    {
    case log_file_policy::clear_then_uppend:
    {
        openingMode = std::ios_base::trunc;
    }
    break;

    case log_file_policy::time_name:
    {
        string sTime;
        append_time_string(sTime.begin(), QXT('-'), QXT('-'));
        sLogFile += QXT('_');
        sLogFile += sTime;
    }
    break;
    }

    sLogFile += QXT(".log");

    const wstring               sWideLogFile = to_wstring(sLogFile);
    const std::filesystem::path path(sWideLogFile.c_str());
    if (path.has_parent_path() && !std::filesystem::exists(path.parent_path()))
    {
        if (!std::filesystem::create_directory(path.parent_path()))
        {
            details::get_cerr<char_type>::get() << QXT("Can't create output folder ") << sWideLogFile;
            return;
        }
    }

    m_File = std::basic_ofstream<char_type>(path, openingMode);
    if (!m_File)
    {
        details::get_cerr<char_type>::get() << QXT("Can't open log file ") << sWideLogFile;
        return;
    }

    QX_DISABLE_MSVC_WARNINGS(4996);
    m_File.imbue(std::locale(std::locale(), new std::codecvt_utf8<char_type>));
    QX_RESTORE_MSVC_WARNINGS(4996);
}

inline file_logger_stream::~file_logger_stream()
{
    if (m_File)
        m_File << QXT("\n\n\n") << std::flush;
}

inline void file_logger_stream::flush()
{
    if (m_File)
    {
        QX_PERF_SCOPE(CatLogger, "Flush to the file");
        m_File << std::flush;
    }
}

inline void file_logger_stream::do_log(const category& category, verbosity eVerbosity, string_view svMessage)
{
    if (m_File)
    {
        QX_PERF_SCOPE(CatLogger, "Log to the file");
        m_File << svMessage;
    }
}

} // namespace qx
