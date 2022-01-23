/**

    @file      thread_worker.h
    @brief     Contains qx::thread_worker class
    @author    Khrapov
    @date      17.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <atomic>
#include <mutex>
#include <thread>

namespace qx
{

/**

    @class   thread_worker
    @brief   Thread worker class
    @details Inherit worker from this class, override thread_run() method
             with useful work and start the thread with thread_start()
    @author  Khrapov
    @date    17.10.2020

**/
class thread_worker
{
public:
    enum class thread_state
    {
        inactive,
        starting,
        running,
        stopping
    };

public:
    /**
        @brief thread_worker object destructor
    **/
    virtual ~thread_worker();

    /**
        @brief Create and start thread
        @param bWait - wait real thread starting
    **/
    void thread_start(bool bWait = true);

    /**
        @brief Terminate thread. thread_run() must check thread_is_terminating()
               and quit if needed
        @param bWait - wait for termination
    **/
    void thread_terminate(bool bWait = true);

    /**
        @brief Wait for thread termination
    **/
    void thread_wait_termination();

    /**
        @brief   Set "terminate in destructor" flag
        @details You may want to disable terminate in destructor if you want
                 to destruct your own objects before thread termination.
                 Don't forget to call thread_terminate() in your destructor
        @param   bTerminate - true if need to terminate in destructor
    **/
    void thread_set_terminate_in_destructor(bool bTerminate = true);

    /**
        @brief  Is thread terminating
        @retval - true if thread is terminating
    **/
    bool thread_is_terminating() const;

    /**
        @brief  Is thread running
        @retval - true if thread is running
    **/
    bool thread_is_running() const;

    /**
        @brief  Get thread state
        @retval - thread state
    **/
    thread_state thread_get_state() const;

    /**
        @brief  Get thread id
        @retval - thread id
    **/
    std::thread::id thread_get_id() const;

protected:
    /**
        @brief Thread started event
    **/
    virtual void thread_on_started();

    /**
        @brief Thread work method
    **/
    virtual void thread_run() = 0;

    /**
        @brief Thread stopped event
    **/
    virtual void thread_on_stopped();

private:
    std::thread               m_Thread;
    std::mutex                m_mtxTermination;
    std::atomic<thread_state> m_eThreadState           = thread_state::inactive;
    std::atomic_bool          m_bTerminateOnDestructor = true;

    //!< flag to force thread to quit. thread_run()
    //!< must check thread_is_terminating() and quit if needed
    std::atomic_bool m_bThreadTerminating = false;
};

} // namespace qx

#include <qx/thread/thread_worker.inl>
