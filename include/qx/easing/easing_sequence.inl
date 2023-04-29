/**

    @file      easing_sequence.inl
    @author    Khrapov
    @date      4.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class T>
inline void base_easing_sequence<T>::push_back(easing_element_type element) noexcept
{
    m_ElementsSequence.push_back(std::move(element));
    update_total_time();
}

template<class T>
template<class... args_t>
inline void base_easing_sequence<T>::emplace_back(args_t&&... args) noexcept
{
    m_ElementsSequence.emplace_back(std::forward<args_t>(args)...);
    update_total_time();
}

template<class T>
inline void base_easing_sequence<T>::clear() noexcept
{
    m_ElementsSequence.clear();
    m_nCurrentElement = 0;
    m_fCurrentTime    = T(0.f);
}

template<class T>
inline void base_easing_sequence<T>::start() noexcept
{
    reset();
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->start();
}

template<class T>
inline void base_easing_sequence<T>::pause() noexcept
{
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->pause();
}

template<class T>
inline void base_easing_sequence<T>::resume() noexcept
{
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->resume();
}

template<class T>
inline void base_easing_sequence<T>::skip() noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        pCurrentElement->finish();
        update(T(0.f));
    }
}

template<class T>
inline void base_easing_sequence<T>::reset() noexcept
{
    m_nCurrentElement = 0;
    m_fCurrentTime    = T(0.f);
    for (auto& element : m_ElementsSequence)
        element.reset();
}

template<class T>
inline void base_easing_sequence<T>::update(T fDeltaTime) noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        T fNotUsedTime = pCurrentElement->update(fDeltaTime * m_fSpeed) / m_fSpeed;

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

template<class T>
inline void base_easing_sequence<T>::set_looped(bool bLooped) noexcept
{
    m_bLoop = bLooped;
}

template<class T>
inline void base_easing_sequence<T>::set_speed(T fSpeed) noexcept
{
    m_fSpeed = fSpeed;
}

template<class T>
inline T base_easing_sequence<T>::get() const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->get();
    }
    else if (!m_ElementsSequence.empty() && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().get();
    }
    else
    {
        return T(0.f);
    }
}

template<class T>
inline T base_easing_sequence<T>::get_fraction() const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return (m_fCurrentTime + pCurrentElement->get_fraction() / pCurrentElement->get_speed()) / m_fTotalTime;
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

template<class T>
inline T base_easing_sequence<T>::get_speed() const noexcept
{
    return m_fSpeed;
}

template<class T>
inline bool base_easing_sequence<T>::is_not_started() const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_not_started();
    }
    else if (!m_ElementsSequence.empty() && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_not_started();
    }
    else
    {
        return true;
    }
}

template<class T>
inline bool base_easing_sequence<T>::is_started() const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_started();
    }
    else if (!m_ElementsSequence.empty() && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_started();
    }
    else
    {
        return false;
    }
}

template<class T>
inline bool base_easing_sequence<T>::is_paused() const noexcept
{
    if (auto pCurrentElement = get_current_element())
        return pCurrentElement->is_paused();
    else
        return false;
}

template<class T>
inline bool base_easing_sequence<T>::is_finished() const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_finished();
    }
    else if (!m_ElementsSequence.empty() && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_finished();
    }
    else
    {
        return false;
    }
}

template<class T>
inline bool base_easing_sequence<T>::is_looped() const noexcept
{
    return m_bLoop;
}

template<class T>
inline typename base_easing_sequence<T>::easing_element_type* base_easing_sequence<T>::get_current_element() noexcept
{
    return m_nCurrentElement < m_ElementsSequence.size() ? &m_ElementsSequence[m_nCurrentElement] : nullptr;
}

template<class T>
inline const typename base_easing_sequence<T>::easing_element_type* base_easing_sequence<T>::get_current_element()
    const noexcept
{
    return const_cast<base_easing_sequence*>(static_cast<const base_easing_sequence*>(this))->get_current_element();
}

template<class T>
inline void base_easing_sequence<T>::update_total_time() noexcept
{
    m_fTotalTime += T(1.f) / m_ElementsSequence.back().get_speed();
}

} // namespace qx
