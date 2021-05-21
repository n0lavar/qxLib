//==============================================================================
//
//!\file                        logger_worker.h
//
//!\brief       Contains logger_worker class
//!\details     ~
//
//!\author      Khrapov
//!\date        21.10.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/logger/logger.h>
#include <qx/thread/threads_shared.h>
#include <qx/thread/thread_worker.h>

#include <memory>
#include <queue>

namespace qx
{

//==============================================================================
//
//!\class                      qx::logger_worker
//
//!\brief   Logger that works in another thread and don't waste time by
//          printing to console and file
//!\details You can use QX_TRACE_FROM, QX_TRACE_ERROR_FROM and QX_TRACE_ASSERT_FROM
//          with this class
//
//!\author  Khrapov
//!\date    21.10.2020
//
//==============================================================================
class logger_worker : public thread_worker
{
    using log_line = std::pair<string, std::string_view>;   // line and color

public:

    virtual        ~logger_worker       (void);
                    logger_worker       (std::unique_ptr<logger> pLogger);

    template <typename Duration>
    void            set_check_period    (Duration               duration);
    void            flush               (void);
    void            process_output      (logger::level          eLogLevel,
                                         const char           * pszFormat,
                                         const char           * pszAssertExpression,
                                         const char           * pszTag,
                                         const char           * pszFile,
                                         const char           * pszFunction,
                                         int                    nLine,
                                         std::string_view       svColor,
                                         ...);

private:

    virtual void    thread_on_started   (void)      override;
    virtual void    thread_run          (void)      override;
    virtual void    thread_on_stopped   (void)      override;

            void    process_console     (void);
            void    process_file        (void);

private:

    std::atomic_flag            m_bFlushing;

    std::unique_ptr<logger>     m_pLogger;
    std::chrono::milliseconds   m_CheckPeriod = std::chrono::milliseconds(500);

    threads_shared<std::queue<log_line>>                m_ConsoleLogsQueue;
    threads_shared<std::unordered_map<string, string>>  m_FileLogsQueue;    // file name and text
};

}

#include <qx/logger/logger_worker.inl>
