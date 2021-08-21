/**

    @file      threads_shared.h
    @brief     Contains qx::threads_shared class
    @author    Khrapov
    @date      4.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/useful_macros.h>

#include <mutex>
#include <optional>

namespace qx
{

template<class Data, class SynchronizationPrimitive>
class threads_shared;

/**

    @class   qx::shared_proxy
    @brief   A proxy class that provides access to an object stored in
             threads_shared and provides raii for synchronization primitives
    @details Locks synchronization primitive in constructor and unlocks
             in destructor
    @tparam  Data                     - data type
    @tparam  SynchronizationPrimitive - synchronization primitive type
    @author  Khrapov
    @date    4.03.2021

**/
template<class Data, class SynchronizationPrimitive>
class shared_proxy
{
    friend threads_shared<Data, SynchronizationPrimitive>;

private:
    /**
        @brief shared_proxy object constructor
        @param pData                     - pointer to the protected data
        @param pSynchronizationPrimitive - pointer to the synchronization primitive
        @param bTryLock                  - if true, function won't wait for other
                                           threads to unlock the sp and will construct
                                           shared_proxy with nullptrs
    **/
    shared_proxy(
        Data*                     pData,
        SynchronizationPrimitive* pSynchronizationPrimitive,
        bool                      bTryLock);

public:
    QX_NONCOPYABLE(shared_proxy);

    /**
        @brief shared_proxy object constructor
        @param other - other shared_proxy rvalue ref
    **/
    shared_proxy(shared_proxy&& other) noexcept;

    /**
        @brief  operator=
        @param  other - Assign by other shared_proxy
        @retval       - this object rvalue ref
    **/
    shared_proxy& operator=(shared_proxy&& other) noexcept;

    /**
        @brief shared_proxy object destructor
    **/
    ~shared_proxy(void);

    /**
        @brief  operator->
        @retval - data pointer
    **/
    [[nodiscard]] Data* operator->(void) noexcept;

    /**
        @brief  operator->
        @retval - data const pointer
    **/
    [[nodiscard]] const Data* operator->(void) const noexcept;

    /**
        @brief  operator*
        @retval - data reference
    **/
    [[nodiscard]] Data& operator*(void) noexcept;

    /**
        @brief  operator*
        @retval - data const reference
    **/
    [[nodiscard]] const Data& operator*(void) const noexcept;

private:
    SynchronizationPrimitive* m_pSynchronizationPrimitive = nullptr;
    Data*                     m_pData                     = nullptr;
};

/**

    @class   qx::threads_shared
    @brief   A class that provides thread-safe access to an object,
             including construction and destruction
    @details ~
    @tparam  Data                     - data type
    @tparam  SynchronizationPrimitive - synchronization primitive type
    @author  Khrapov
    @date    20.08.2021

**/
template<class Data, class SynchronizationPrimitive = std::mutex>
class threads_shared
{
    /**

        @class   qx::threads_shared::synchronization_primitive_raii

        @brief   class guaranties thread safe construction and destruction of threads_shared
        @details ~

        @author  Khrapov
        @date    20.08.2021

    **/
    class synchronization_primitive_raii
    {
    public:
        /**
            @brief synchronization_primitive_raii object constructor
        **/
        synchronization_primitive_raii(void);

        /**
            @brief synchronization_primitive_raii object destructor
        **/
        ~synchronization_primitive_raii(void);

        /**
            @brief  Get synchronization primitive stored in proxy
            @retval - synchronization primitive
        **/
        SynchronizationPrimitive* get_object(void) noexcept;

    private:
        SynchronizationPrimitive sp;
    };

public:
    using proxy = shared_proxy<Data, SynchronizationPrimitive>;

    QX_NONCOPYMOVABLE(threads_shared);

    /**
        @brief  threads_shared object constructor
        @tparam Args - template parameter pack type
        @param  args - arguments to constructing Data object
    **/
    template<class... Args>
    threads_shared(Args&&... args);

    /**
        @brief threads_shared object destructor
    **/
    ~threads_shared(void);

    /**
        @brief  Wait for other threads to finish work with data object and retrieve
                proxy object
        @retval - proxy that provides access to an object stored in threads_shared
                  and provides raii for synchronization primitives
    **/
    [[nodiscard]] proxy lock(void);

    /**
        @brief  Try to lock synchronization primitive and get proxy
        @retval - proxy that provides access to an object stored
                  in threads_shared or std::nullopt
    **/
    [[nodiscard]] std::optional<proxy> try_lock(void);

private:
    synchronization_primitive_raii m_SynchronizationPrimitiveRAII;
    Data                           m_Data;
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

} // namespace qx

#include <qx/thread/threads_shared.inl>
