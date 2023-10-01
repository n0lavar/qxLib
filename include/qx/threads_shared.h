/**

    @file      threads_shared.h
    @author    Khrapov
    @date      4.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/copyable_movable.h>

#include <mutex>
#include <optional>

namespace qx
{

template<class data_t, class synchronization_primitive_t>
class threads_shared;

/**

    @class   shared_proxy
    @brief   A proxy class that provides access to an object stored in
             threads_shared and provides raii for synchronization primitives
    @details Locks synchronization primitive in constructor and unlocks in destructor
    @tparam  data_t                      - data type
    @tparam  synchronization_primitive_t - synchronization primitive type
    @author  Khrapov
    @date    4.03.2021

**/
template<class data_t, class synchronization_primitive_t>
class shared_proxy
{
    friend threads_shared<data_t, synchronization_primitive_t>;

private:
    /**
        @brief shared_proxy object constructor
        @param pData                     - pointer to the protected data
        @param pSynchronizationPrimitive - pointer to the synchronization primitive
        @param bTryLock                  - if true, function won't wait for other
                                           threads to unlock the sp and will construct
                                           shared_proxy with nullptrs
    **/
    shared_proxy(data_t* pData, synchronization_primitive_t* pSynchronizationPrimitive, bool bTryLock);

public:
    QX_NONCOPYABLE(shared_proxy);

    shared_proxy(shared_proxy&& other) noexcept;
    shared_proxy& operator=(shared_proxy&& other) noexcept;

    ~shared_proxy();

    [[nodiscard]] data_t*       operator->() noexcept;
    [[nodiscard]] const data_t* operator->() const noexcept;

    [[nodiscard]] data_t&       operator*() noexcept;
    [[nodiscard]] const data_t& operator*() const noexcept;

private:
    synchronization_primitive_t* m_pSynchronizationPrimitive = nullptr;
    data_t*                      m_pData                     = nullptr;
};

/**

    @class   threads_shared
    @brief   A class that provides thread-safe access to an object,
             including construction and destruction
    @tparam  data_t                      - data type
    @tparam  synchronization_primitive_t - synchronization primitive type
    @author  Khrapov
    @date    20.08.2021

**/
template<class data_t, class synchronization_primitive_t = std::mutex>
class threads_shared
{
    /**

        @class   synchronization_primitive_raii
        @brief   class guaranties thread safe construction and destruction of threads_shared
        @details ~
        @author  Khrapov
        @date    20.08.2021

    **/
    class synchronization_primitive_raii
    {
    public:
        synchronization_primitive_raii();
        ~synchronization_primitive_raii();

        /**
            @brief  Get synchronization primitive stored in proxy
            @retval - synchronization primitive
        **/
        synchronization_primitive_t* get_object() noexcept;

    private:
        synchronization_primitive_t sp;
    };

public:
    using proxy = shared_proxy<data_t, synchronization_primitive_t>;

    QX_NONCOPYMOVABLE(threads_shared);

    /**
        @brief  threads_shared object constructor
        @tparam args_t - template parameter pack type
        @param  args   - arguments to constructing Data object
    **/
    template<class... args_t>
    threads_shared(args_t&&... args);

    /**
        @brief threads_shared object destructor
    **/
    ~threads_shared();

    /**
        @brief  Wait for other threads to finish work with data object and retrieve
                proxy object
        @retval - proxy that provides access to an object stored in threads_shared
                  and provides raii for synchronization primitives
    **/
    [[nodiscard]] proxy lock();

    /**
        @brief  Try to lock synchronization primitive and get proxy
        @retval - proxy that provides access to an object stored
                  in threads_shared or std::nullopt
    **/
    [[nodiscard]] std::optional<proxy> try_lock();

private:
    synchronization_primitive_raii m_SynchronizationPrimitiveRAII;
    data_t                         m_Data;
};

template<class synchronization_primitive_t>
inline void lock_synchronization_primitive(synchronization_primitive_t* pSP)
{
    pSP->lock();
}

template<class synchronization_primitive_t>
inline void unlock_synchronization_primitive(synchronization_primitive_t* pSP)
{
    pSP->unlock();
}

template<class synchronization_primitive_t>
inline bool try_lock_synchronization_primitive(synchronization_primitive_t* pSP)
{
    return pSP->try_lock();
}

} // namespace qx

#include <qx/threads_shared.inl>
