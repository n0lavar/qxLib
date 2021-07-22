//==============================================================================
//
//!\file                        threads_shared.h
//
//!\brief       Contains qx::threads_shared class
//!\details     ~
//
//!\author      Khrapov
//!\date        4.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/useful_macros.h>

#include <mutex>
#include <optional>

namespace qx
{

template<class Data, class SynchronizationPrimitive>
class threads_shared;

//==============================================================================
//
//!\class       qx::shared_proxy<Data, SynchronizationPrimitive>
//
//!\brief   A proxy class that provides access to an object stored in
//          threads_shared and provides raii for synchronization primitives
//!\details Locks synchronization primitive in constructor and unlocks
//          in destructor
//
//!\author  Khrapov
//!\date    4.03.2021
//
//==============================================================================
template<class Data, class SynchronizationPrimitive>
class shared_proxy
{
    friend threads_shared<Data, SynchronizationPrimitive>;

private:

    shared_proxy   (Data                    * pData,
                    SynchronizationPrimitive* pSynchronizationPrimitive,
                    bool                      bTryLock);

public:

    QX_NONCOPYABLE(shared_proxy)

                    shared_proxy    (shared_proxy&& other)  noexcept;
    shared_proxy&   operator=       (shared_proxy&& other)  noexcept;

                    ~shared_proxy   (void);

    [[nodiscard]] Data        * operator->  (void)          noexcept;
    [[nodiscard]] const Data  * operator->  (void) const    noexcept;
    [[nodiscard]] Data        & operator*   (void)          noexcept;
    [[nodiscard]] const Data  & operator*   (void) const    noexcept;

private:

    SynchronizationPrimitive  * m_pSynchronizationPrimitive = nullptr;
    Data                      * m_pData                     = nullptr;
};

//==============================================================================
//
//!\class      qx::threads_shared<Data, SynchronizationPrimitive>
//
//!\brief   A class that provides thread-safe access to an object,
//          including construction and destruction
//!\details ~
//
//!\author  Khrapov
//!\date    4.03.2021
//
//==============================================================================
template<class Data, class SynchronizationPrimitive = std::mutex>
class threads_shared
{
    // class guaranties thread safe construction and destruction of threads_shared
    class synchronization_primitive_raii
    {
    public:

        synchronization_primitive_raii      (void);
        ~synchronization_primitive_raii     (void);
        SynchronizationPrimitive* get_object(void)  noexcept;

    private:

        SynchronizationPrimitive sp;
    };

public:

    using proxy = shared_proxy<Data, SynchronizationPrimitive>;

    QX_NONCOPYMOVABLE(threads_shared)

    template<class... Args>             threads_shared  (Args&&... args);
                                        ~threads_shared (void);
    [[nodiscard]] proxy                 lock            (void);
    [[nodiscard]] std::optional<proxy>  try_lock        (void);

private:

    synchronization_primitive_raii  m_SynchronizationPrimitiveRAII;
    Data                            m_Data;
};

template<class SynchronizationPrimitive>
inline void lock_synchronization_primitive(SynchronizationPrimitive* pSP)
{
    pSP->lock();
}

template<class SynchronizationPrimitive>
inline void unlock_synchronization_primitive(SynchronizationPrimitive* pSP)
{
    pSP->unlock();
}

template<class SynchronizationPrimitive>
inline bool try_lock_synchronization_primitive(SynchronizationPrimitive* pSP)
{
    return pSP->try_lock();
}

}

#include <qx/thread/threads_shared.inl>
