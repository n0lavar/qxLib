/**

    @file      threads_shared.inl
    @author    Khrapov
    @date      4.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

//-------------------------------- shared_proxy --------------------------------

template<class data_t, class synchronization_primitive_t>
inline shared_proxy<data_t, synchronization_primitive_t>::shared_proxy(
    data_t*                     pData,
    synchronization_primitive_t* pSynchronizationPrimitive,
    bool                      bTryLock)
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
            m_pData                     = nullptr;
        }
    }
}

template<class data_t, class synchronization_primitive_t>
inline shared_proxy<data_t, synchronization_primitive_t>::shared_proxy(shared_proxy&& other) noexcept
{
    std::swap(m_pSynchronizationPrimitive, other.m_pSynchronizationPrimitive);
    std::swap(m_pData, other.m_pData);
}

template<class data_t, class synchronization_primitive_t>
inline shared_proxy<data_t, synchronization_primitive_t>& shared_proxy<data_t, synchronization_primitive_t>::operator=(
    shared_proxy&& other) noexcept
{
    std::swap(m_pSynchronizationPrimitive, other.m_pSynchronizationPrimitive);
    std::swap(m_pData, other.m_pData);
    return *this;
}

template<class data_t, class synchronization_primitive_t>
inline shared_proxy<data_t, synchronization_primitive_t>::~shared_proxy()
{
    if (m_pSynchronizationPrimitive && m_pData)
        unlock_synchronization_primitive(m_pSynchronizationPrimitive);
}

template<class data_t, class synchronization_primitive_t>
inline data_t* shared_proxy<data_t, synchronization_primitive_t>::operator->(void) noexcept
{
    return m_pData;
}

template<class data_t, class synchronization_primitive_t>
inline const data_t* shared_proxy<data_t, synchronization_primitive_t>::operator->(void) const noexcept
{
    return m_pData;
}

template<class data_t, class synchronization_primitive_t>
inline data_t& shared_proxy<data_t, synchronization_primitive_t>::operator*(void) noexcept
{
    return *m_pData;
}

template<class data_t, class synchronization_primitive_t>
inline const data_t& shared_proxy<data_t, synchronization_primitive_t>::operator*(void) const noexcept
{
    return *m_pData;
}



//----------------------- synchronization_primitive_raii -----------------------

template<class data_t, class synchronization_primitive_t>
inline threads_shared<data_t, synchronization_primitive_t>::synchronization_primitive_raii::synchronization_primitive_raii()
{
    lock_synchronization_primitive(&sp);
}

template<class data_t, class synchronization_primitive_t>
inline threads_shared<data_t, synchronization_primitive_t>::synchronization_primitive_raii::~synchronization_primitive_raii()
{
    unlock_synchronization_primitive(&sp);
}

template<class data_t, class synchronization_primitive_t>
inline synchronization_primitive_t* threads_shared<data_t, synchronization_primitive_t>::synchronization_primitive_raii::
    get_object() noexcept
{
    return &sp;
}



//------------------------------- threads_shared -------------------------------

template<class data_t, class synchronization_primitive_t>
template<class... args_t>
inline threads_shared<data_t, synchronization_primitive_t>::threads_shared(args_t&&... args)
    : m_Data(std::forward<args_t>(args)...)
{
    // unlock the state that was locked in
    // synchronization_primitive_raii::synchronization_primitive_raii()
    unlock_synchronization_primitive(m_SynchronizationPrimitiveRAII.get_object());
}

template<class data_t, class synchronization_primitive_t>
inline threads_shared<data_t, synchronization_primitive_t>::~threads_shared()
{
    // wait for the rest of the threads to finish working
    // unlocking will be carried out in
    // synchronization_primitive_raii::~synchronization_primitive_raii()
    lock_synchronization_primitive(m_SynchronizationPrimitiveRAII.get_object());
}

template<class data_t, class synchronization_primitive_t>
inline typename threads_shared<data_t, synchronization_primitive_t>::proxy threads_shared<data_t, synchronization_primitive_t>::
    lock()
{
    return proxy(&m_Data, m_SynchronizationPrimitiveRAII.get_object(), false);
}

template<class data_t, class synchronization_primitive_t>
inline std::optional<typename threads_shared<data_t, synchronization_primitive_t>::proxy> threads_shared<
    data_t,
    synchronization_primitive_t>::try_lock()
{
    auto object = proxy(&m_Data, m_SynchronizationPrimitiveRAII.get_object(), true);
    if (object.m_pSynchronizationPrimitive && object.m_pData)
        return { std::move(object) };
    else
        return std::nullopt;
}

} // namespace qx
