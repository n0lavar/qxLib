/**

    @file      state.inl
    @brief     
    @author    Khrapov
    @date      20.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class Traits>
inline basic_state<Traits>::basic_state(const type& value) : m_State(value)
{
}

template<class Traits>
inline basic_state<Traits>& basic_state<Traits>::operator=(const type& value)
{
    m_State = value;
    return *this;
}

template<class Traits>
inline bool basic_state<Traits>::operator==(const type& value) const
{
    return m_State == value;
}

template<class Traits>
inline void basic_state<Traits>::reset(void)
{
    m_State = default_value;
}

template<class Traits>
inline bool basic_state<Traits>::is_default(void) const
{
    return m_State == default_value;
}

} // namespace qx

namespace std
{

template<class Traits>
struct hash<qx::basic_state<Traits>>
{
    size_t operator()(const qx::basic_state<Traits>& state) const noexcept
    {
        return std::hash<typename Traits::type>()(state.m_State);
    }
};

} // namespace std
