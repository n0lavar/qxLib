/**

    @file      unique_objects_pool.inl
    @author    Khrapov
    @date      11.02.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class T>
inline unique_objects_pool<T>::token::token(const token& otherToken) noexcept
{
    *this = otherToken;
}

template<class T>
unique_objects_pool<T>::token::token(token&& otherToken) noexcept
{
    *this = std::move(otherToken);
}

template<class T>
inline typename unique_objects_pool<T>::token& unique_objects_pool<T>::token::operator=(
    const token& otherToken) noexcept
{
    m_nId   = otherToken.m_nId;
    m_pPool = otherToken.m_pPool;

    if (is_valid())
        m_pPool->increase_counter(m_nId);

    return *this;
}

template<class T>
typename unique_objects_pool<T>::token& unique_objects_pool<T>::token::operator=(token&& otherToken) noexcept
{
    std::swap(m_nId, otherToken.m_nId);
    std::swap(m_pPool, otherToken.m_pPool);

    return *this;
}

template<class T>
inline unique_objects_pool<T>::token::~token() noexcept
{
    if (is_valid())
        m_pPool->decrease_counter(m_nId);
}

template<class T>
inline bool unique_objects_pool<T>::token::is_valid() const noexcept
{
    return m_pPool && m_nId != kInvalidId;
}

template<class T>
inline unique_objects_pool<T>::token::operator bool() const noexcept
{
    return is_valid();
}

template<class T>
inline const T& unique_objects_pool<T>::token::operator*() const noexcept
{
    return m_pPool->get_value(m_nId);
}

template<class T>
inline const T* unique_objects_pool<T>::token::operator->() const noexcept
{
    return &m_pPool->get_value(m_nId);
}

template<class T>
inline bool unique_objects_pool<T>::token::operator==(const token& other) const noexcept
{
    return m_pPool == other.m_pPool && m_nId == other.m_nId;
}

template<class T>
inline unique_objects_pool<T>::token::token(u64 nId, unique_objects_pool* pPool) noexcept : m_nId(nId)
                                                                                          , m_pPool(pPool)
{
}

template<class T>
inline unique_objects_pool<T>::unique_objects_pool(bool bAutoCleanup) noexcept : m_bAutoShrink(bAutoCleanup)
{
}

template<class T>
template<class U>
inline typename unique_objects_pool<T>::token unique_objects_pool<T>::get_or_create(U&& value) noexcept
{
    QX_PERF_SCOPE();

    token result;

    std::unique_lock lock(m_UniqueObjectsPoolMutex);
    data_by_value&   set = m_Pool.template get<value_tag>();
    if (auto it = set.find(std::as_const(value)); it != set.end())
    {
        result = token(it->nId, this);
        set.modify(
            it,
            [](data& _data)
            {
                ++_data.nCounter;
            });
    }
    else
    {
        data _data { T(std::forward<U>(value)), m_nCurrentId++, 1 };
        result = token(_data.nId, this);
        set.insert(_data);
    }

    return result;
}

template<class T>
inline void unique_objects_pool<T>::shrink()
{
    QX_PERF_SCOPE();

    if (m_bAutoShrink)
        return;

    std::unique_lock lock(m_UniqueObjectsPoolMutex);
    data_by_id&      set = m_Pool.template get<id_tag>();
    do
    {
        auto it = std::find_if(
            set.begin(),
            set.end(),
            [&](const data& _data)
            {
                return _data.nCounter == 0;
            });

        if (it != set.end())
            set.erase(it);
        else
            break;
    } while (true);
}

template<class T>
inline size_t unique_objects_pool<T>::size() const
{
    QX_PERF_SCOPE();

    std::shared_lock lock(m_UniqueObjectsPoolMutex);
    return m_Pool.size();
}

template<class T>
inline bool unique_objects_pool<T>::empty() const
{
    QX_PERF_SCOPE();

    return size() == 0;
}

template<class T>
inline void unique_objects_pool<T>::increase_counter(u64 nId) noexcept
{
    QX_PERF_SCOPE();

    std::unique_lock lock(m_UniqueObjectsPoolMutex);
    data_by_id&      set = m_Pool.template get<id_tag>();
    if (auto it = set.find(nId); it != set.end())
    {
        set.modify(
            it,
            [](data& _data)
            {
                ++_data.nCounter;
            });
    }
}

template<class T>
inline void unique_objects_pool<T>::decrease_counter(u64 nId) noexcept
{
    QX_PERF_SCOPE();

    std::unique_lock lock(m_UniqueObjectsPoolMutex);
    data_by_id&      set = m_Pool.template get<id_tag>();
    if (auto it = set.find(nId); it != set.end())
    {
        if (m_bAutoShrink && it->nCounter == 1)
        {
            set.erase(it);
        }
        else
        {
            set.modify(
                it,
                [](data& _data)
                {
                    --_data.nCounter;
                });
        }
    }
}

template<class T>
inline const T& unique_objects_pool<T>::get_value(u64 nId) noexcept
{
    QX_PERF_SCOPE();

    std::shared_lock lock(m_UniqueObjectsPoolMutex);
    data_by_id&      set = m_Pool.template get<id_tag>();

    // only tokens can access this method -> object always exists
    return set.find(nId)->value;
}

} // namespace qx
