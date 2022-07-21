/**

    @file      threads_shared.inl
    @author    Khrapov
    @date      4.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

//-------------------------------- shared_proxy --------------------------------

template<class Data, class SynchronizationPrimitive>
inline shared_proxy<Data, SynchronizationPrimitive>::shared_proxy(
    Data*                     pData,
    SynchronizationPrimitive* pSynchronizationPrimitive,
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

template<class Data, class SynchronizationPrimitive>
inline shared_proxy<Data, SynchronizationPrimitive>::shared_proxy(shared_proxy&& other) noexcept
{
    std::swap(m_pSynchronizationPrimitive, other.m_pSynchronizationPrimitive);
    std::swap(m_pData, other.m_pData);
}

template<class Data, class SynchronizationPrimitive>
inline shared_proxy<Data, SynchronizationPrimitive>& shared_proxy<Data, SynchronizationPrimitive>::operator=(
    shared_proxy&& other) noexcept
{
    std::swap(m_pSynchronizationPrimitive, other.m_pSynchronizationPrimitive);
    std::swap(m_pData, other.m_pData);
    return *this;
}

template<class Data, class SynchronizationPrimitive>
inline shared_proxy<Data, SynchronizationPrimitive>::~shared_proxy()
{
    if (m_pSynchronizationPrimitive && m_pData)
        unlock_synchronization_primitive(m_pSynchronizationPrimitive);
}

template<class Data, class SynchronizationPrimitive>
inline Data* shared_proxy<Data, SynchronizationPrimitive>::operator->(void) noexcept
{
    return m_pData;
}

template<class Data, class SynchronizationPrimitive>
inline const Data* shared_proxy<Data, SynchronizationPrimitive>::operator->(void) const noexcept
{
    return m_pData;
}

template<class Data, class SynchronizationPrimitive>
inline Data& shared_proxy<Data, SynchronizationPrimitive>::operator*(void) noexcept
{
    return *m_pData;
}

template<class Data, class SynchronizationPrimitive>
inline const Data& shared_proxy<Data, SynchronizationPrimitive>::operator*(void) const noexcept
{
    return *m_pData;
}



//----------------------- synchronization_primitive_raii -----------------------

template<class Data, class SynchronizationPrimitive>
inline threads_shared<Data, SynchronizationPrimitive>::synchronization_primitive_raii::synchronization_primitive_raii()
{
    lock_synchronization_primitive(&sp);
}

template<class Data, class SynchronizationPrimitive>
inline threads_shared<Data, SynchronizationPrimitive>::synchronization_primitive_raii::~synchronization_primitive_raii()
{
    unlock_synchronization_primitive(&sp);
}

template<class Data, class SynchronizationPrimitive>
inline SynchronizationPrimitive* threads_shared<Data, SynchronizationPrimitive>::synchronization_primitive_raii::
    get_object() noexcept
{
    return &sp;
}



//------------------------------- threads_shared -------------------------------

template<class Data, class SynchronizationPrimitive>
template<class... Args>
inline threads_shared<Data, SynchronizationPrimitive>::threads_shared(Args&&... args)
    : m_Data(std::forward<Args>(args)...)
{
    // unlock the state that was locked in
    // synchronization_primitive_raii::synchronization_primitive_raii()
    unlock_synchronization_primitive(m_SynchronizationPrimitiveRAII.get_object());
}

template<class Data, class SynchronizationPrimitive>
inline threads_shared<Data, SynchronizationPrimitive>::~threads_shared()
{
    // wait for the rest of the threads to finish working
    // unlocking will be carried out in
    // synchronization_primitive_raii::~synchronization_primitive_raii()
    lock_synchronization_primitive(m_SynchronizationPrimitiveRAII.get_object());
}

template<class Data, class SynchronizationPrimitive>
inline typename threads_shared<Data, SynchronizationPrimitive>::proxy threads_shared<Data, SynchronizationPrimitive>::
    lock()
{
    return proxy(&m_Data, m_SynchronizationPrimitiveRAII.get_object(), false);
}

template<class Data, class SynchronizationPrimitive>
inline std::optional<typename threads_shared<Data, SynchronizationPrimitive>::proxy> threads_shared<
    Data,
    SynchronizationPrimitive>::try_lock()
{
    auto object = proxy(&m_Data, m_SynchronizationPrimitiveRAII.get_object(), true);
    if (object.m_pSynchronizationPrimitive && object.m_pData)
        return { std::move(object) };
    else
        return std::nullopt;
}

} // namespace qx
