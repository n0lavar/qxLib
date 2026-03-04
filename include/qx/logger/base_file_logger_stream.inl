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

inline std::filesystem::path base_file_logger_stream::prepare_folder_and_get_log_file_path(
    const config& config) noexcept
{
    // make sure the destination directory exists
    std::filesystem::path logDirPath = config.svLogsDirectory;
    if (!std::filesystem::exists(logDirPath))
    {
        if (!std::filesystem::create_directory(logDirPath))
        {
            details::get_cerr<char_type>::get() << QXT("Can't create output folder ") << logDirPath;
            return std::filesystem::path();
        }
    }

    // rotate logs
    if (config.eLogFilePolicy == log_file_policy::time_name && config.nMaxLogFiles > 0)
    {
        std::vector<std::filesystem::directory_entry> logFiles;
        for (const std::filesystem::directory_entry& entry :
             std::filesystem::directory_iterator(logDirPath)
                 | std::views::filter(
                     [&config](const std::filesystem::directory_entry& entry)
                     {
                         return entry.path().extension() == config.svFileExtension;
                     }))
        {
            const std::wstring sFilename = entry.path().filename().wstring();
            if (sFilename.starts_with(config.svFilePrefix))
                logFiles.push_back(entry);
        }

        if (logFiles.size() > config.nMaxLogFiles - 1)
        {
            std::ranges::sort(
                logFiles,
                [](const std::filesystem::directory_entry& left, const std::filesystem::directory_entry& right)
                {
                    return std::filesystem::last_write_time(left) > std::filesystem::last_write_time(right);
                });

            for (size_t i = config.nMaxLogFiles - 1; i < logFiles.size(); ++i)
                std::filesystem::remove(logFiles[i]);
        }
    }

    // construct the log name
    string sLogFile = config.svLogsDirectory;
    if (!config.svLogsDirectory.empty() && !config.svLogsDirectory.ends_with(QXT('/'))
        && !config.svLogsDirectory.ends_with(QXT('\\')))
    {
        sLogFile += QXT('/');
    }
    sLogFile += config.svFilePrefix;

    if (config.eLogFilePolicy == log_file_policy::time_name)
    {
        sLogFile += QXT('_');
        append_time_string(std::back_inserter(sLogFile), QXT('-'), QXT('-'), std::chrono::system_clock::now());
    }

    sLogFile += config.svFileExtension;

    return sLogFile.c_str();
}

} // namespace qx
