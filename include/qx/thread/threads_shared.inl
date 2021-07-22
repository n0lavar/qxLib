//==============================================================================
//
//!\file                       threads_shared.inl
//
//!\brief       Contains qx::threads_shared class
//!\details     ~
//
//!\author      Khrapov
//!\date        4.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//-------------------------------- shared_proxy --------------------------------

//==============================================================================
//!\fn   qx::shared_proxy<Data, SynchronizationPrimitive>::shared_proxy
//
//!\brief  shared_proxy object constructor
//!\param  pData                     - pointer to the protected data
//!\param  pSynchronizationPrimitive - pointer to the synchronization primitive
//!\param  bTryLock                  - if true, function won't wait for other
//                                     threads to unlock the sp and will construct
//                                     shared_proxy with nullptrs
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template<class Data, class SynchronizationPrimitive>
inline shared_proxy<Data, SynchronizationPrimitive>::shared_proxy(
    Data                      * pData,
    SynchronizationPrimitive  * pSynchronizationPrimitive,
    bool                        bTryLock)
    : m_pSynchronizationPrimitive(pSynchronizationPrimitive)
    , m_pData(pData)
{
    if (!bTryLock)
    {
        lock_synchronization_primitive(m_pSynchronizationPrimitive);
    }
    else
    {
        if (!try_lock_synchronization_primitive(m_pSynchronizationPrimitive))
        {
            m_pSynchronizationPrimitive = nullptr;
            m_pData = nullptr;
        }
    }
}

//==============================================================================
//!\fn   qx::shared_proxy<Data, SynchronizationPrimitive>::shared_proxy
//
//!\brief  shared_proxy object constructor
//!\param  other - other shared_proxy
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline shared_proxy<Data, SynchronizationPrimitive>::shared_proxy(
    shared_proxy&& other) noexcept
{
    std::swap(m_pSynchronizationPrimitive, other.m_pSynchronizationPrimitive);
    std::swap(m_pData, other.m_pData);
}

//==============================================================================
//!\fn    qx::shared_proxy<Data, SynchronizationPrimitive>::operator=
//
//!\brief  Assign by other
//!\param  other - other shared_proxy
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline shared_proxy<Data, SynchronizationPrimitive>&
    shared_proxy<Data, SynchronizationPrimitive>::operator=(
    shared_proxy&& other) noexcept
{
    std::swap(m_pSynchronizationPrimitive, other.m_pSynchronizationPrimitive);
    std::swap(m_pData, other.m_pData);
    return *this;
}

//==============================================================================
//!\fn  qx::shared_proxy<Data, SynchronizationPrimitive>::~shared_proxy
//
//!\brief  shared_proxy object destructor
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline shared_proxy<Data, SynchronizationPrimitive>::~shared_proxy()
{
    if (m_pSynchronizationPrimitive && m_pData)
        unlock_synchronization_primitive(m_pSynchronizationPrimitive);
}

//==============================================================================
//!\fn      shared_proxy<Data, SynchronizationPrimitive>::operator->
//
//!\brief  operator->
//!\retval  - data pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline Data* shared_proxy<Data, SynchronizationPrimitive>::operator->(
    void) noexcept
{
    return m_pData;
}

//==============================================================================
//!\fn      shared_proxy<Data, SynchronizationPrimitive>::operator->
//
//!\brief  const operator->
//!\retval  - data const pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline const Data* shared_proxy<Data, SynchronizationPrimitive>::operator->(
    void) const noexcept
{
    return m_pData;
}

//==============================================================================
//!\fn      shared_proxy<Data, SynchronizationPrimitive>::operator*
//
//!\brief  operator*
//!\retval  - data reference
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline Data& shared_proxy<Data, SynchronizationPrimitive>::operator*(
    void) noexcept
{
    return *m_pData;
}

//==============================================================================
//!\fn      shared_proxy<Data, SynchronizationPrimitive>::operator*
//
//!\brief  const operator*
//!\retval  - data const reference
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline const Data& shared_proxy<Data, SynchronizationPrimitive>::operator*(
    void) const noexcept
{
    return *m_pData;
}



//----------------------- synchronization_primitive_raii -----------------------

//==============================================================================
//!\fn  qx::threads_shared<Data, SynchronizationPrimitive>
//      ::synchronization_primitive_raii::synchronization_primitive_raii
//
//!\brief  synchronization_primitive_raii object constructor
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline threads_shared<Data, SynchronizationPrimitive>
    ::synchronization_primitive_raii::synchronization_primitive_raii(void)
{
    lock_synchronization_primitive(&sp);
}

//==============================================================================
//!\fn  qx::threads_shared<Data, SynchronizationPrimitive>
//      ::synchronization_primitive_raii::~synchronization_primitive_raii
//
//!\brief  synchronization_primitive_raii object destructor
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline threads_shared<Data, SynchronizationPrimitive>
    ::synchronization_primitive_raii::~synchronization_primitive_raii()
{
    unlock_synchronization_primitive(&sp);
}

//==============================================================================
//!\fn  qx::threads_shared<Data, SynchronizationPrimitive>
//      ::synchronization_primitive_raii::get_object
//
//!\brief  Get synchronization primitive stored in proxy
//!\retval  - synchronization primitive
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline SynchronizationPrimitive* threads_shared<Data, SynchronizationPrimitive>
    ::synchronization_primitive_raii::get_object(void) noexcept
{
    return &sp;
}



//------------------------------- threads_shared -------------------------------

//==============================================================================
//!\fn qx::threads_shared<Data, SynchronizationPrimitive>::threads_shared
//
//!\brief  threads_shared object constructor
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template<class Data, class SynchronizationPrimitive>
template<class ... Args>
inline threads_shared<Data, SynchronizationPrimitive>::threads_shared(Args&&... args)
    : m_Data(std::forward<Args>(args)...)
{
    // unlock the state that was locked in
    // synchronization_primitive_raii::synchronization_primitive_raii()
    unlock_synchronization_primitive(m_SynchronizationPrimitiveRAII.get_object());
}

//==============================================================================
//!\fn qx::threads_shared<Data, SynchronizationPrimitive>::~threads_shared
//
//!\brief  threads_shared object destructor
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template<class Data, class SynchronizationPrimitive>
inline threads_shared<Data, SynchronizationPrimitive>::~threads_shared()
{
    // wait for the rest of the threads to finish working
    // unlocking will be carried out in
    // synchronization_primitive_raii::~synchronization_primitive_raii()
    lock_synchronization_primitive(m_SynchronizationPrimitiveRAII.get_object());
}

//==============================================================================
//!\fn      qx::threads_shared<Data, SynchronizationPrimitive>::lock
//
//!\brief     Wait for other threads to finish work with data object and retrieve
//            proxy object
//!\retval  - proxy that provides access to an object stored in threads_shared
//            and provides raii for synchronization primitives
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template<class Data, class SynchronizationPrimitive>
inline typename threads_shared<Data, SynchronizationPrimitive>::proxy
    threads_shared<Data, SynchronizationPrimitive>::lock()
{
    return proxy(&m_Data, m_SynchronizationPrimitiveRAII.get_object(), false);
}

//==============================================================================
//!\fn    qx::threads_shared<Data, SynchronizationPrimitive>::try_lock
//
//!\brief     Try to lock synchronization primitive and get proxy
//!\retval  - first: true if locked successfully
//            second: valid proxy that provides access to an object stored
//            in threads_shared and provides raii for synchronization primitives
//            if first is true, otherwise empty proxy
//!\author Khrapov
//!\date   5.03.2021
//==============================================================================
template <class Data, class SynchronizationPrimitive>
inline std::optional<typename threads_shared<Data, SynchronizationPrimitive>::proxy>
    threads_shared<Data, SynchronizationPrimitive>::try_lock(void)
{
    auto object = proxy(&m_Data, m_SynchronizationPrimitiveRAII.get_object(), true);
    if (object.m_pSynchronizationPrimitive && object.m_pData)
        return { std::move(object) };
    else
        return std::nullopt;
}

}
