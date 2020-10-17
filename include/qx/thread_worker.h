//==============================================================================
//
//!\file                        thread_worker.h
//
//!\brief       Contains thread worker class
//!\details     ~
//
//!\author      Khrapov
//!\date        17.10.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <thread>
#include <atomic>
#include <mutex>

namespace qx
{

//================================================================================
//
//!\class                      qx::thread_worker
//
//!\brief   Thread worker class
//!\details Inherit worker from this class, override thread_run() method
//          with useful work and start the thread with thread_start()
//
//!\author  Khrapov
//!\date    17.10.2020
//
//================================================================================
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

    virtual                ~thread_worker           (void);
            void            thread_start            (bool   bWait = true);
            void            thread_terminate        (bool   bWait = true);
            void            thread_wait_termination (void);

            bool            thread_is_terminating   (void) const;
            bool            thread_is_running       (void) const;
            thread_state    thread_get_state        (void) const;
            std::thread::id thread_get_id           (void) const;

protected:

    virtual void            thread_on_started       (void);
    virtual void            thread_run              (void) = 0;
    virtual void            thread_on_stopped       (void);

private:

    std::thread                 m_Thread;
    std::mutex                  m_TerminationMutex;
    std::atomic<thread_state>   m_eThreadState          = thread_state::inactive;
    std::atomic_bool            m_bThreadTerminating    = false;    // flag to force thread to quit. thread_run()
                                                                    // must check thread_is_terminating() and quit if needed
};

inline                             thread_worker::~thread_worker        ()       { thread_terminate(true); }
inline void                        thread_worker::thread_on_started     ()       {  }
inline void                        thread_worker::thread_on_stopped     ()       {  }
inline thread_worker::thread_state thread_worker::thread_get_state      () const { return m_eThreadState.load(std::memory_order_acquire); }
inline bool                        thread_worker::thread_is_terminating () const { return m_bThreadTerminating.load(std::memory_order_acquire); }
inline bool                        thread_worker::thread_is_running     () const { return thread_get_state() != thread_worker::thread_state::inactive; }
inline std::thread::id             thread_worker::thread_get_id         () const { return m_Thread.get_id(); }

}

#include <qx/thread_worker.inl>
