/**

    @file      state.inl
    @author    Khrapov
    @date      20.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class T>
inline state<T>::state(const T& value) noexcept : m_State(value)
{
}

template<class T>
inline state<T>::state(const T& value, const T& defaultValue) noexcept
    : m_State(value)
    , m_DefaultValue(defaultValue)
{
}

template<class T>
inline state<T>& state<T>::operator=(const T& value) noexcept
{
    m_State = value;
    return *this;
}

template<class T>
inline bool state<T>::operator==(const T& value) const noexcept
{
    return m_State == value;
}

template<class T>
inline T* state<T>::operator->() noexcept
{
    return &m_State;
}

template<class T>
inline const T* state<T>::operator->() const noexcept
{
    return &m_State;
}

template<class T>
inline T& state<T>::operator*() noexcept
{
    return m_State;
}

template<class T>
inline const T& state<T>::operator*() const noexcept
{
    return m_State;
}

template<class T>
inline void state<T>::reset() noexcept
{
    m_State = m_DefaultValue;
}

template<class T>
inline bool state<T>::is_default() const noexcept
{
    return m_State == m_DefaultValue;
}

} // namespace qx

namespace std
{

template<class T>
struct hash<qx::state<T>>
{
    size_t operator()(const qx::state<T>& state) const noexcept
    {
        return std::hash<T>()(state.m_State);
    }
};

} // namespace std
