//==============================================================================
//
//!\file                     file_logger_stream.inl
//
//!\brief       Contains qx::file_logger_stream class
//!\details     ~
//
//!\author      Khrapov
//!\date        30.07.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn             qx::file_logger_stream::file_logger_stream
//
//!\brief  file_logger_stream object constructor
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline file_logger_stream::file_logger_stream(void)
{
    string& sTime = get_time_buffer();
    format_time_string(sTime);
    m_sSessionTime = sTime + '/';
}

//==============================================================================
//!\fn          qx::file_logger_stream::~file_logger_stream
//
//!\brief  file_logger_stream object destructor
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline file_logger_stream::~file_logger_stream(void)
{
    for (const auto& file : m_Files)
    {
        if (file.second.bWroteToFile)
        {
            fill_file_folder(file.second.eLogPolicy, m_sBufferPath);
            m_sBufferPath += file.second.sFileName;

            std::ofstream ofs(m_sBufferPath.data(), std::ofstream::app);
            if (ofs)
                ofs << "\n\n\n" << std::flush;
        }
    }
}

//==============================================================================
//!\fn               qx::file_logger_stream::process_output
//
//!\brief  Output to file
//!\param  svMessage - message string
//!\param  logUnit   - log unit info
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void file_logger_stream::process_output(
    std::string_view    svMessage,
    log_unit            logUnit)
{
    std::string_view        svFileName;
    log_file_policy         eLogFilePolicy  = log_file_policy::append;
    std::ios_base::openmode ofstreamMode    = std::ofstream::app;

    if (const auto it = m_Files.find(logUnit.svUnitName); it != m_Files.cend())
    {
        svFileName      = it->second.sFileName;
        eLogFilePolicy  = it->second.eLogPolicy;

        if (!it->second.bWroteToFile && eLogFilePolicy == log_file_policy::clear_then_uppend)
            ofstreamMode = std::ofstream::out | std::ofstream::trunc;

        it->second.bWroteToFile = true;
    }
    else
    {
        svFileName = DEFAULT_FILE;
    }

    fill_file_folder(eLogFilePolicy, m_sBufferPath);

    if (!m_sFolder.empty())
        std::filesystem::create_directories(m_sBufferPath.data());

    m_sBufferPath += svFileName;

    std::ofstream ofs(m_sBufferPath.data(), ofstreamMode);
    if (ofs)
    {
        ofs << svMessage;
        ofs.close();
    }
    else
    {
        std::cerr << "output_to_file error: file " << svFileName;
    }
}

//==============================================================================
//!\fn              qx::file_logger_stream::set_logs_folder
//
//!\brief  Set logs folder
//!\param  svFolder - logs folder
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void file_logger_stream::set_logs_folder(
    std::string_view svFolder) noexcept
{
    m_sFolder = svFolder;
    if (!m_sFolder.empty() && !m_sFolder.ends_with('/'))
        m_sFolder += '/';
}

//==============================================================================
//!\fn               qx::file_logger_stream::register_file
//
//!\brief  Register output to specific file for specific unit
//!\param  svUnitName - unit name
//!\param  svFileName - file name
//!\param  eLogPolicy - log file policy
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void file_logger_stream::register_file(
    std::string_view    svUnitName,
    std::string_view    svFileName,
    log_file_policy     eLogPolicy)
{
    if (!svUnitName.empty() &&!svFileName.empty())
        m_Files[svUnitName] = { svFileName, eLogPolicy };
}

//==============================================================================
//!\fn              qx::file_logger_stream::fill_file_folder
//
//!\brief  Fill string with file folder path
//!\param  eLogFilePolicy - file log policy
//!\param  sFileFolder    - output string
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void file_logger_stream::fill_file_folder(
    log_file_policy     eLogFilePolicy,
    string            & sFileFolder) const noexcept
{
    switch (eLogFilePolicy)
    {
    case log_file_policy::folder_time:
        sFileFolder = m_sFolder + m_sSessionTime;
        break;

    case log_file_policy::append:
    case log_file_policy::clear_then_uppend:
    default:
        sFileFolder = m_sFolder;
        break;
    }
}

}
