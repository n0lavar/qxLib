//==============================================================================
//
//!\file                      easing_sequence.inl
//
//!\brief       Contains qx::base_easing_sequence class
//!\details     ~
//
//!\author      Khrapov
//!\date        4.05.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn              qx::base_easing_sequence<T>::push_back
//
//!\brief  Add easing element to queue
//!\param  element - element
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::push_back(easing_element_type element) noexcept
{
    m_ElementsSequence.push_back(std::move(element));
    update_total_time();
}

//==============================================================================
//!\fn         qx::base_easing_sequence<T>::emplace_back<...Args>
//
//!\brief  Add easing element to queue by constructing in-place
//!\param  ...args - arguments for constructing
//!\author Khrapov
//!\date   16.05.2021
//==============================================================================
template<typename T>
template<typename ...Args>
inline void base_easing_sequence<T>::emplace_back(Args && ...args) noexcept
{
    m_ElementsSequence.emplace_back(std::forward<Args>(args)...);
    update_total_time();
}

//==============================================================================
//!\fn                 qx::base_easing_sequence<T>::clear
//
//!\brief  Clear elements queue
//!\author Khrapov
//!\date   16.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::clear(void) noexcept
{
    m_ElementsSequence.clear();
    m_nCurrentElement = 0;
    m_fCurrentTime = T(0.f);
}

//==============================================================================
//!\fn                qx::base_easing_sequence<T>::start
//
//!\brief  Start easing element sequence playing
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::start(void) noexcept
{
    reset();
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->start();
}

//==============================================================================
//!\fn                qx::base_easing_sequence<T>::pause
//
//!\brief  Pause easing element sequence playing
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::pause(void) noexcept
{
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->pause();
}

//==============================================================================
//!\fn                  qx::base_easing_sequence<T>::resume
//
//!\brief  Resume easing element sequence playing
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::resume(void) noexcept
{
    if (auto pCurrentElement = get_current_element())
        pCurrentElement->resume();
}

//==============================================================================
//!\fn                qx::base_easing_sequence<T>::skip
//
//!\brief  Skip current element
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::skip() noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        pCurrentElement->finish();
        update(T(0.f));
    }
}

//==============================================================================
//!\fn                qx::base_easing_sequence<T>::reset
//
//!\brief  Reset sequence
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::reset(void) noexcept
{
    m_nCurrentElement = 0;
    m_fCurrentTime = T(0.f);
    for (auto& element : m_ElementsSequence)
        element.reset();
}

//==============================================================================
//!\fn               qx::base_easing_sequence<T>::update
//
//!\brief  Update easing element sequence
//!\param  fDeltaTime - delta time
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::update(T fDeltaTime) noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        T fNotUsedTime = pCurrentElement->update(fDeltaTime * m_fSpeed) / m_fSpeed;
        if (pCurrentElement->is_finished())
        {
            m_nCurrentElement++;
            m_fCurrentTime += T(1.f) / pCurrentElement->get_speed();
            if (m_nCurrentElement >= m_ElementsSequence.size() && m_bLoop)
            {
                m_nCurrentElement = 0;
                m_fCurrentTime = T(0.f);
            }

            if (auto pNewElement = get_current_element())
            {
                pNewElement->start();
                update(fNotUsedTime);
            }
        }
    }
}

//==============================================================================
//!\fn              qx::base_easing_sequence<T>::set_looped
//
//!\brief  Set loop state
//!\param  bLoop - true if loop
//!\author Khrapov
//!\date   18.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::set_looped(bool bLooped) noexcept
{
    m_bLoop = bLooped;
}

//==============================================================================
//!\fn               qx::base_easing_sequence<T>::set_speed
//
//!\brief  Set updating speed value
//!\param  fSpeed - speed
//!\author Khrapov
//!\date   19.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::set_speed(T fSpeed) noexcept
{
    m_fSpeed = fSpeed;
}

//==============================================================================
//!\fn                  qx::base_easing_sequence<T>::get
//
//!\brief  Get value of current sequence element
//!\retval  - value of current sequence element
//!\author Khrapov
//!\date   6.05.2021
//==============================================================================
template<typename T>
inline T base_easing_sequence<T>::get(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->get();
    }
    else if (!m_ElementsSequence.empty()
        && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().get();
    }
    else
    {
        return T(0.f);
    }
}

//==============================================================================
//!\fn              qx::base_easing_sequence<T>::get_fraction
//
//!\brief  Get a fraction indicating how much of the sequence has played
//!\retval  - fraction [0.0, 1.0]
//!\author Khrapov
//!\date   18.05.2021
//==============================================================================
template<typename T>
inline T base_easing_sequence<T>::get_fraction(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return (m_fCurrentTime
            + pCurrentElement->get_fraction() / pCurrentElement->get_speed())
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

//==============================================================================
//!\fn               qx::base_easing_sequence<T>::get_speed
//
//!\brief  Get updating speed value
//!\retval  - speed
//!\author Khrapov
//!\date   19.05.2021
//==============================================================================
template<typename T>
inline T base_easing_sequence<T>::get_speed(void) const noexcept
{
    return m_fSpeed;
}

//==============================================================================
//!\fn            qx::base_easing_sequence<T>::is_not_started
//
//!\brief   Is sequence not started
//!\retval  - true if sequence is not started
//!\author Khrapov
//!\date   18.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_sequence<T>::is_not_started(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_not_started();
    }
    else if (!m_ElementsSequence.empty()
        && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_not_started();
    }
    else
    {
        return true;
    }
}

//==============================================================================
//!\fn              qx::base_easing_sequence<T>::is_started
//
//!\brief   Is sequence started
//!\retval  - true if sequence is started
//!\author Khrapov
//!\date   18.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_sequence<T>::is_started(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_started();
    }
    else if (!m_ElementsSequence.empty()
        && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_started();
    }
    else
    {
        return false;
    }
}

//==============================================================================
//!\fn               qx::base_easing_sequence<T>::is_paused
//
//!\brief   Is sequence paused
//!\retval  - true if sequence is paused
//!\author Khrapov
//!\date   18.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_sequence<T>::is_paused(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
        return pCurrentElement->is_paused();
    else
        return false;
}

//==============================================================================
//!\fn              qx::base_easing_sequence<T>::is_finished
//
//!\brief   Is sequence finished
//!\retval  - true if sequence is finished
//!\author Khrapov
//!\date   18.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_sequence<T>::is_finished(void) const noexcept
{
    if (auto pCurrentElement = get_current_element())
    {
        return pCurrentElement->is_finished();
    }
    else if (!m_ElementsSequence.empty()
        && m_nCurrentElement >= m_ElementsSequence.size())
    {
        return m_ElementsSequence.back().is_finished();
    }
    else
    {
        return false;
    }
}

//==============================================================================
//!\fn               qx::base_easing_sequence<T>::is_looped
//
//!\brief   Is sequence looped
//!\retval  - true if sequence is looped
//!\author Khrapov
//!\date   18.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_sequence<T>::is_looped(void) const noexcept
{
    return m_bLoop;
}

//==============================================================================
//!\fn          qx::base_easing_sequence<T>::get_current_element
//
//!\brief  Get current element pointer or nullptr if no elements
//!\retval  -  current element pointer or nullptr if no elements
//!\author Khrapov
//!\date   16.05.2021
//==============================================================================
template<typename T>
inline typename base_easing_sequence<T>::easing_element_type*
    base_easing_sequence<T>::get_current_element(void) noexcept
{
    return m_nCurrentElement < m_ElementsSequence.size()
        ? &m_ElementsSequence[m_nCurrentElement]
        : nullptr;
}

//==============================================================================
//!\fn          qx::base_easing_sequence<T>::get_current_element
//
//!\brief  Get current element pointer or nullptr if no elements
//!\retval  -  current element pointer or nullptr if no elements
//!\author Khrapov
//!\date   16.05.2021
//==============================================================================
template<typename T>
inline const typename base_easing_sequence<T>::easing_element_type*
    base_easing_sequence<T>::get_current_element(void) const noexcept
{
    return const_cast<base_easing_sequence*>(
        static_cast<const base_easing_sequence*>(this))->get_current_element();
}

//==============================================================================
//!\fn           qx::base_easing_sequence<T>::update_total_time
//
//!\brief  Update total time by adding time from last element
//!\author Khrapov
//!\date   19.05.2021
//==============================================================================
template<typename T>
inline void base_easing_sequence<T>::update_total_time(void) noexcept
{
    m_fTotalTime += T(1.f) / m_ElementsSequence.back().get_speed();
}

}
