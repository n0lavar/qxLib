//==============================================================================
//
//!\file                       logger_worker.inl
//
//!\brief       Contains logger_worker class
//!\details     ~
//
//!\author      Khrapov
//!\date        21.10.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                  qx::logger_worker::logger_worker
//
//!\brief  logger_worker object constructor
//!\param  pLogger - tuned instance of logger. you won't be able to edit it
//                   after creating of logger_worker for better performance
//!\author Khrapov
//!\date   24.10.2020
//==============================================================================
inline logger_worker::logger_worker(std::unique_ptr<logger> pLogger)
    : m_pLogger(std::move(pLogger))
{
    thread_set_terminate_in_destructor(true);
}

//==============================================================================
//!\fn                   logger_worker::~logger_worker
//
//!\brief  logger_worker object destructor
//!\author Khrapov
//!\date   26.10.2020
//==============================================================================
inline logger_worker::~logger_worker(void)
{
    // firstly - wait for logging to be done
    thread_terminate(true);

    // secondly - destruct queues
}

//==============================================================================
//!\fn           qx::logger_worker::set_check_period<Duration>
//
//!\brief  Set period to check queue and flush data to cout and files
//!\param  duration - period
//!\author Khrapov
//!\date   25.10.2020
//==============================================================================
template<typename Duration>
inline void logger_worker::set_check_period(Duration duration)
{
    m_CheckPeriod = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

//==============================================================================
//!\fn                 qx::logger_worker::process_output
//
//!\brief  Process tracings
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  pszTag               - tracing tag or nullptr
//!\param  pszFile              - file name string
//!\param  pszFunction          - function name string
//!\param  nLine                - code line number
//!\param  svColor              - ascii color string
//!\param  ...                  - additional args for format
//!\author Khrapov
//!\date   24.10.2020
//==============================================================================
inline void logger_worker::process_output(
    logger::level       eLogLevel,
    const char        * pszFormat,
    const char        * pszAssertExpression,
    const char        * pszTag,
    const char        * pszFile,
    const char        * pszFunction,
    int                 nLine,
    std::string_view    svColor,
    ...)
{
    // check is thread safe as nobody can't edit units
    if (auto pUnitInfo = m_pLogger->get_unit_info(
        eLogLevel,
        pszTag,
        pszFile,
        pszFunction))
    {
        thread_local string sMsg;
        thread_local string sFormat;

        auto& traceUnitInfo = pUnitInfo->get_trace_unit_info();

        va_list args;
        va_start(args, svColor);
        sMsg.clear();

        if (auto formatFunc = traceUnitInfo.formatFunc; formatFunc)
        {
            formatFunc(
                sMsg,
                sFormat,
                eLogLevel,
                pszFormat,
                pszAssertExpression,
                pszTag,
                pszFile,
                pszFunction,
                nLine,
                args);
        }

        va_end(args);

        if (!sMsg.empty())
        {
            if (eLogLevel >= traceUnitInfo.eFileLevel)
            {
                std::lock_guard lock(m_mtxFileLogsQueue);
                m_FileLogsQueue[traceUnitInfo.sLogFileName] += sMsg;
                pUnitInfo->set_wrote_to_file();
            }

            if (eLogLevel >= traceUnitInfo.eConsoleLevel)
            {
                std::lock_guard lock(m_mtxConsoleLogsQueue);
                m_ConsoleLogsQueue.push({ std::move(sMsg), svColor });
            }
        }
    }
}

//==============================================================================
//!\fn                qx::logger_worker::thread_on_started
//
//!\brief  Thread started event
//!\author Khrapov
//!\date   24.10.2020
//==============================================================================
inline void logger_worker::thread_on_started(void)
{
    // Optimization
    // Don't synchronize to the standard C streams after each input/output operation
    std::ios_base::sync_with_stdio(false);

    // This unties cin from cout.
    // Tied streams ensure that one stream is flushed automatically
    // before each I/O operation on the other stream
    std::cin.tie(nullptr);
}

//==============================================================================
//!\fn                   qx::logger_worker::thread_run
//
//!\brief  Thread main function
//!\author Khrapov
//!\date   24.10.2020
//==============================================================================
inline void logger_worker::thread_run(void)
{
    while (!thread_is_terminating())
    {
        auto StartTime = std::chrono::steady_clock::now();
        process_console();
        process_file();
        std::this_thread::sleep_until(StartTime + m_CheckPeriod);
    }
}

//==============================================================================
//!\fn                qx::logger_worker::thread_on_stopped
//
//!\brief  Thread ended event
//!\author Khrapov
//!\date   24.10.2020
//==============================================================================
inline void logger_worker::thread_on_stopped(void)
{
    process_console();
    std::cout << std::flush;

    process_file();
    m_pLogger->on_terminate();
}

//==============================================================================
//!\fn                 qx::logger_worker::process_console
//
//!\brief  Print to console from queue
//!\author Khrapov
//!\date   24.10.2020
//==============================================================================
inline void logger_worker::process_console(void)
{
    auto get_log_line = [this]() -> log_line
    {
        std::lock_guard lock(m_mtxConsoleLogsQueue);
        auto log = m_ConsoleLogsQueue.front();
        m_ConsoleLogsQueue.pop();
        return std::move(log);
    };

    m_mtxConsoleLogsQueue.lock();
    size_t nStartSize = m_ConsoleLogsQueue.size();
    m_mtxConsoleLogsQueue.unlock();

    for (size_t i = 0; i < nStartSize; i++)
    {
        auto opt_log_line = get_log_line();
        m_pLogger->output_to_cout(opt_log_line.first, opt_log_line.second);
    }
}

//==============================================================================
//!\fn                  qx::logger_worker::process_file
//
//!\brief  Print to files from queue
//!\author Khrapov
//!\date   24.10.2020
//==============================================================================
inline void logger_worker::process_file(void)
{
    m_mtxFileLogsQueue.lock();

    bool bEmpty = std::all_of(
        m_FileLogsQueue.cbegin(),
        m_FileLogsQueue.cend(),
        [](const auto& pair) { return pair.second.empty(); });

    m_mtxFileLogsQueue.unlock();

    if (!bEmpty)
    {
        std::unordered_map<string, string> logs;

        m_mtxFileLogsQueue.lock();
        logs = m_FileLogsQueue;
        for (auto& [sFile, sText] : m_FileLogsQueue)
            sText.clear();
        m_mtxFileLogsQueue.unlock();

        for (auto& [sFile, sText] : logs)
            if (!sFile.empty() && !sText.empty())
                m_pLogger->output_to_file(sText, sFile);
    }
}

}
