/**

    @file      thread_worker.inl
    @brief     Contains qx::thread_worker class implementation
    @author    Khrapov
    @date      17.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline thread_worker::~thread_worker()
{
    if (m_bTerminateOnDestructor.load(std::memory_order_acquire))
        thread_terminate(true);
}

inline void thread_worker::thread_start(bool bWait)
{
    thread_terminate(true);
    m_bThreadTerminating.store(false, std::memory_order_release);

    m_Thread = std::thread(
        [this]()
        {
            m_eThreadState.store(
                thread_state::starting,
                std::memory_order_release);
            thread_on_started();

            m_eThreadState.store(
                thread_state::running,
                std::memory_order_release);
            thread_run();

            m_eThreadState.store(
                thread_state::stopping,
                std::memory_order_release);
            thread_on_stopped();

            m_eThreadState.store(
                thread_state::inactive,
                std::memory_order_release);
            m_bThreadTerminating.store(true, std::memory_order_release);
        });

    while (bWait && !thread_is_running() && !thread_is_terminating())
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

inline void thread_worker::thread_terminate(bool bWait)
{
    m_bThreadTerminating.store(true, std::memory_order_release);
    if (bWait)
    {
        thread_wait_termination();
        m_Thread = std::thread();
    }
}

inline void thread_worker::thread_wait_termination()
{
    std::lock_guard lock(m_mtxTermination);
    if (m_Thread.joinable())
        m_Thread.join();
}

inline void thread_worker::thread_set_terminate_in_destructor(bool bTerminate)
{
    m_bTerminateOnDestructor.store(bTerminate, std::memory_order_release);
}

inline void thread_worker::thread_on_started(void)
{
}

inline void thread_worker::thread_on_stopped(void)
{
}

inline thread_worker::thread_state thread_worker::thread_get_state(void) const
{
    return m_eThreadState.load(std::memory_order_acquire);
}

inline bool thread_worker::thread_is_terminating(void) const
{
    return m_bThreadTerminating.load(std::memory_order_acquire);
}

inline bool thread_worker::thread_is_running(void) const
{
    return thread_get_state() != thread_state::inactive;
}

inline std::thread::id thread_worker::thread_get_id(void) const
{
    return m_Thread.get_id();
}

} // namespace qx
