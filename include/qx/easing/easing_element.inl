//==============================================================================
//
//!\file                       easing_element.inl
//
//!\brief       Contains qx::base_easing_element class
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
//!\fn            qx::base_easing_element<T>::base_easing_element
//
//!\brief  base_easing_element object constructor
//!\param  func   - easing function
//!\param  fStart - start value
//!\param  fEnd   - end value
//!\param  fSpeed - speed of updating
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline base_easing_element<T>::base_easing_element(
    easing::func<T> func,
    T               fStart,
    T               fEnd,
    T               fSpeed) noexcept
    : m_EasingFunc  (std::move(func))
    , m_fCurrentY   (fStart)
    , m_fStartY     (fStart)
    , m_fEndY       (fEnd)
{
    set_speed(fSpeed);
}

//==============================================================================
//!\fn                 qx::base_easing_element<T>::start
//
//!\brief  Mark element as active and let it update
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline void base_easing_element<T>::start(void) noexcept
{
    m_eStatus   = status::started;
    m_fCurrentX = T(0.f);
    m_fCurrentY = m_fStartY;
}

//==============================================================================
//!\fn                 qx::base_easing_element<T>::pause
//
//!\brief  Pause element if started
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline void base_easing_element<T>::pause(void) noexcept
{
    if (m_eStatus == status::started)
        m_eStatus = status::paused;
}

//==============================================================================
//!\fn                 qx::base_easing_element<T>::resume
//
//!\brief  Resume updating if paused
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline void base_easing_element<T>::resume(void) noexcept
{
    if (m_eStatus == status::paused)
        m_eStatus = status::started;
}

//==============================================================================
//!\fn                 qx::base_easing_element<T>::finish
//
//!\brief  Mark element as finished
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline void base_easing_element<T>::finish(void) noexcept
{
    m_eStatus = status::finished;
    m_fCurrentX = T(1.f);
    m_fCurrentY = m_fEndY;
}

//==============================================================================
//!\fn                 qx::base_easing_element<T>::reset
//
//!\brief  Mark element as inactive
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline void base_easing_element<T>::reset(void) noexcept
{
    m_eStatus = status::not_started;
    m_fCurrentX = T(0.f);
    m_fCurrentY = m_fStartY;
}

//==============================================================================
//!\fn                 qx::base_easing_element<T>::update
//
//!\brief  Update element corresponding to easing function
//!\param  fDeltaTime - delta time
//!\retval  - the portion of time that was not used
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline T base_easing_element<T>::update(T fDeltaTime) noexcept
{
    T fRet = T(0.f);

    if (m_eStatus == status::started)
    {
        m_fCurrentX = m_fCurrentX + fDeltaTime * m_fSpeed;

        if (m_fCurrentX < T(1.f))
        {
            m_fCurrentY = m_fStartY
                + m_EasingFunc(m_fCurrentX) * (m_fEndY - m_fStartY);
        }
        else
        {
            fRet = (m_fCurrentX - T(1.f)) / m_fSpeed;
            finish();
        }
    }
    else
    {
        fRet = fDeltaTime;
    }

    return fRet;
}

//==============================================================================
//!\fn               qx::base_easing_element<T>::set_speed
//
//!\brief  Set speed value
//!\param  fSpeed - new speed value
//!\author Khrapov
//!\date   6.05.2021
//==============================================================================
template<typename T>
inline void base_easing_element<T>::set_speed(T fSpeed) noexcept
{
    if (fSpeed > T(0.f))
        m_fSpeed = fSpeed;
}

//==============================================================================
//!\fn                  qx::base_easing_element<T>::get
//
//!\brief  Get current value of element
//!\retval  - current value of element
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline T base_easing_element<T>::get(void) const noexcept
{
    return m_fCurrentY;
}

//==============================================================================
//!\fn               qx::base_easing_element<T>::get_fraction
//
//!\brief  Get a fraction indicating how much of the element has played
//!\retval  - fraction [0.0, 1.0]
//!\author Khrapov
//!\date   6.05.2021
//==============================================================================
template<typename T>
inline T base_easing_element<T>::get_fraction(void) const noexcept
{
    return m_fCurrentX;
}

//==============================================================================
//!\fn                 base_easing_element<T>::get_speed
//
//!\brief  Get speed value
//!\retval  - speed value
//!\author Khrapov
//!\date   6.05.2021
//==============================================================================
template<typename T>
inline T base_easing_element<T>::get_speed(void) const noexcept
{
    return m_fSpeed;
}

//==============================================================================
//!\fn               qx::base_easing_element<T>::get_status
//
//!\brief  Get element status
//!\retval  - element status
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline typename base_easing_element<T>::status
    base_easing_element<T>::get_status(void) const noexcept
{
    return m_eStatus;
}

//==============================================================================
//!\fn             qx::base_easing_element<T>::is_not_started
//
//!\brief  Check if element is not started
//!\retval  - true if element is not started
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_element<T>::is_not_started(void) const noexcept
{
    return m_eStatus == status::not_started;
}

//==============================================================================
//!\fn               qx::base_easing_element<T>::is_started
//
//!\brief  Check if element is started
//!\retval  - true if element is started
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_element<T>::is_started(void) const noexcept
{
    return m_eStatus == status::started;
}

//==============================================================================
//!\fn               qx::base_easing_element<T>::is_paused
//
//!\brief  Check if element is paused
//!\retval  - true if element is paused
//!\author Khrapov
//!\date   11.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_element<T>::is_paused(void) const noexcept
{
    return m_eStatus == status::paused;
}

//==============================================================================
//!\fn              qx::base_easing_element<T>::is_finished
//
//!\brief  Check if element is finished
//!\retval  - true if element is finished
//!\author Khrapov
//!\date   4.05.2021
//==============================================================================
template<typename T>
inline bool base_easing_element<T>::is_finished(void) const noexcept
{
    return m_eStatus == status::finished;
}

}
