/**

    @file      base_file_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_file_logger_stream::base_file_logger_stream(const config& streamConfig) noexcept
    : base_logger_stream(streamConfig)
{
}

inline std::filesystem::path base_file_logger_stream::create_folder_and_get_log_file_path(
    log_file_policy eLogFilePolicy,
    string_view     svFileName) noexcept
{
    string sLogFile = svFileName;
    if (eLogFilePolicy == log_file_policy::time_name)
    {
        string sTime;
        append_time_string(sTime.begin(), QXT('-'), QXT('-'), std::chrono::system_clock::now());

        size_t nInsetPos = sLogFile.rfind(QXT(".log"));
        if (nInsetPos == string::npos)
            nInsetPos = sLogFile.size();

        sLogFile.insert(nInsetPos, QXT('_'));
        sLogFile.insert(nInsetPos + 1, sTime);
    }

    std::filesystem::path path(sLogFile.c_str());
    if (path.has_parent_path() && !std::filesystem::exists(path.parent_path()))
    {
        if (!std::filesystem::create_directory(path.parent_path()))
        {
            details::get_cerr<char_type>::get() << QXT("Can't create output folder ") << sLogFile;
            return std::filesystem::path();
        }
    }

    return path;
}

} // namespace qx
