//==============================================================================
//
//!\file                       thread_worker.inl
//
//!\brief       Contains thread worker class
//!\details     ~
//
//!\author      Khrapov
//!\date        17.10.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                  qx::thread_worker::thread_start
//
//!\brief  Create and start thread
//!\param  bWait - wait real thread starting
//!\author Khrapov
//!\date   17.10.2020
//==============================================================================
inline void thread_worker::thread_start(bool bWait)
{
    thread_terminate(true);
    m_bThreadTerminating.store(false, std::memory_order_release);

    m_Thread = std::thread([this]()
        {
            m_eThreadState.store(thread_state::starting, std::memory_order_release);
            thread_on_started();

            m_eThreadState.store(thread_state::running, std::memory_order_release);
            thread_run();

            m_eThreadState.store(thread_state::stopping, std::memory_order_release);
            thread_on_stopped();

            m_eThreadState.store(thread_state::inactive, std::memory_order_release);
            m_bThreadTerminating.store(true, std::memory_order_release);
        }
    );

    while (bWait && !thread_is_running() && !thread_is_terminating())
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

//==============================================================================
//!\fn                qx::thread_worker::thread_terminate
//
//!\brief  Terminate thread. thread_run() must check thread_is_terminating()
//         and quit if needed
//!\param  bWait - wait for termination
//!\author Khrapov
//!\date   17.10.2020
//==============================================================================
inline void thread_worker::thread_terminate(bool bWait)
{
    m_bThreadTerminating.store(true, std::memory_order_release);
    if (bWait)
    {
        thread_wait_termination();
        m_Thread = std::thread();
    }
}

//==============================================================================
//!\fn             qx::thread_worker::thread_wait_termination
//
//!\brief  Wait for thread termination
//!\author Khrapov
//!\date   17.10.2020
//==============================================================================
inline void thread_worker::thread_wait_termination()
{
    std::lock_guard lock(m_TerminationMutex);
    if (m_Thread.joinable())
        m_Thread.join();
}

}
