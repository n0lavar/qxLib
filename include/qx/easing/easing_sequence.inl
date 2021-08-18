/**

    @file      easing_sequence.inl
    @brief     Contains qx::base_easing_sequence class implementation
    @author    Khrapov
    @date      4.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<typename T>
inline void base_easing_sequence<T>::push_back(
    easing_element_type element) noexcept
{
    m_ElementsSequence.push_back(std::move(element));
    update_total_time();
}

template<typename T>
template<typename... Args>
inline void base_easing_sequence<T>::emplace_back(Args&&... args) noexcept
{
    m_ElementsSequence.emplace_back(std::forward<Args>(args)...);
    update_total_time();
}

template<typename T>
inline void base_easing_sequence<T>::clear(void) noexcept
{
    m_ElementsSequence.clear();
    m_nCurrentElement = 0;
    m_fCurrentTime    = T(0.f);
}

template<typename T>
inline void base_easing_sequence<T>::start(void) noexcept
{
    reset();
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->start();
}

template<typename T>
inline void base_easing_sequence<T>::pause(void) noexcept
{
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->pause();
}

template<typename T>
inline void base_easing_sequence<T>::resume(void) noexcept
{
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->resume();
}

template<typename T>
inline void base_easing_sequence<T>::skip() noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        pCurrentElement->finish();
        update(T(0.f));
    }
}

template<typename T>
inline void base_easing_sequence<T>::reset(void) noexcept
{
    m_nCurrentElement = 0;
    m_fCurrentTime    = T(0.f);
    for (auto& element : m_ElementsSequence)
        element.reset();
}

template<typename T>
inline void base_easing_sequence<T>::update(T fDeltaTime) noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        T fNotUsedTime =
            pCurrentElement->update(fDeltaTime * m_fSpeed) / m_fSpeed;

        if (pCurrentElement->is_finished())
        {
            ++m_nCurrentElement;
            m_fCurrentTime += T(1.f) / pCurrentElement->get_speed();
            if (m_nCurrentElement >= m_ElementsSequence.size() && m_bLoop)
            {
                m_nCurrentElement = 0;
                m_fCurrentTime    = T(0.f);
            }

            if (auto pNewElement = get_current_element())
            {
                pNewElement->start();
                update(fNotUsedTime);
            }
        }
    }
}

template<typename T>
inline void base_easing_sequence<T>::set_looped(bool bLooped) noexcept
{
    m_bLoop = bLooped;
}

template<typename T>
inline void base_easing_sequence<T>::set_speed(T fSpeed) noexcept
{
    m_fSpeed = fSpeed;
}

template<typename T>
inline T base_easing_sequence<T>::get(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->get();
    }
    else if (
        !m_ElementsSequence.empty()
        && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().get();
    }
    else
    {
        return T(0.f);
    }
}

template<typename T>
inline T base_easing_sequence<T>::get_fraction(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return (m_fCurrentTime
                + pCurrentElement->get_fraction()
                      / pCurrentElement->get_speed())
               / m_fTotalTime;
    }
    else if (m_fTotalTime > T(0.f))
    {
        return m_fCurrentTime / m_fTotalTime;
    }
    else
    {
        return T(0.f);
    }
}

template<typename T>
inline T base_easing_sequence<T>::get_speed(void) const noexcept
{
    return m_fSpeed;
}

template<typename T>
inline bool base_easing_sequence<T>::is_not_started(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_not_started();
    }
    else if (
        !m_ElementsSequence.empty()
        && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_not_started();
    }
    else
    {
        return true;
    }
}

template<typename T>
inline bool base_easing_sequence<T>::is_started(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_started();
    }
    else if (
        !m_ElementsSequence.empty()
        && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_started();
    }
    else
    {
        return false;
    }
}

template<typename T>
inline bool base_easing_sequence<T>::is_paused(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
        return pCurrentElement->is_paused();
    else
        return false;
}

template<typename T>
inline bool base_easing_sequence<T>::is_finished(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_finished();
    }
    else if (
        !m_ElementsSequence.empty()
        && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_finished();
    }
    else
    {
        return false;
    }
}

template<typename T>
inline bool base_easing_sequence<T>::is_looped(void) const noexcept
{
    return m_bLoop;
}

template<typename T>
inline typename base_easing_sequence<T>::easing_element_type*
    base_easing_sequence<T>::get_current_element(void) noexcept
{
    return m_nCurrentElement < m_ElementsSequence.size()
               ? &m_ElementsSequence[m_nCurrentElement]
               : nullptr;
}

template<typename T>
inline const typename base_easing_sequence<T>::easing_element_type*
    base_easing_sequence<T>::get_current_element(void) const noexcept
{
    return const_cast<base_easing_sequence*>(
               static_cast<const base_easing_sequence*>(this))
        ->get_current_element();
}

template<typename T>
inline void base_easing_sequence<T>::update_total_time(void) noexcept
{
    m_fTotalTime += T(1.f) / m_ElementsSequence.back().get_speed();
}

} // namespace qx
