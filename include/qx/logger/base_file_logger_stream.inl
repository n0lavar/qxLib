/**

    @file      base_file_logger_stream.inl
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

inline base_file_logger_stream::base_file_logger_stream(const config& streamConfig) : base_logger_stream(streamConfig)
{
}

inline std::filesystem::path base_file_logger_stream::create_folder_and_get_log_file_path(
    log_file_policy eLogFilePolicy,
    string_view     svFileName)
{
    string sLogFile = svFileName;
    if (eLogFilePolicy == log_file_policy::time_name)
    {
        string sTime;
        append_time_string(sTime.begin(), QXT('-'), QXT('-'));
        sLogFile += QXT('_');
        sLogFile += sTime;
    }

    sLogFile += QXT(".log");

    const wstring               sWideLogFile = to_wstring(sLogFile);
    const std::filesystem::path path(sWideLogFile.c_str());
    if (path.has_parent_path() && !std::filesystem::exists(path.parent_path()))
    {
        if (!std::filesystem::create_directory(path.parent_path()))
        {
            details::get_cerr<char_type>::get() << QXT("Can't create output folder ") << sWideLogFile;
            return std::filesystem::path();
        }
    }

    return path;
}

} // namespace qx
