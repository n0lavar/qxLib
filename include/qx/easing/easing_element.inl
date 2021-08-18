/**

    @file      easing_element.inl
    @brief     Contains qx::base_easing_element class implementation
    @author    Khrapov
    @date      4.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<typename T>
inline base_easing_element<T>::base_easing_element(
    const easing::func<T>& func,
    T                      fStart,
    T                      fEnd,
    T                      fSpeed) noexcept
    : m_EasingFunc(func)
    , m_fCurrentY(fStart)
    , m_fStartY(fStart)
    , m_fEndY(fEnd)
{
    set_speed(fSpeed);
}

template<typename T>
inline void base_easing_element<T>::start(void) noexcept
{
    m_eStatus   = status::started;
    m_fCurrentX = T(0.f);
    m_fCurrentY = m_fStartY;
}

template<typename T>
inline void base_easing_element<T>::pause(void) noexcept
{
    if (m_eStatus == status::started)
        m_eStatus = status::paused;
}

template<typename T>
inline void base_easing_element<T>::resume(void) noexcept
{
    if (m_eStatus == status::paused)
        m_eStatus = status::started;
}

template<typename T>
inline void base_easing_element<T>::finish(void) noexcept
{
    m_eStatus   = status::finished;
    m_fCurrentX = T(1.f);
    m_fCurrentY = m_fEndY;
}

template<typename T>
inline void base_easing_element<T>::reset(void) noexcept
{
    m_eStatus   = status::not_started;
    m_fCurrentX = T(0.f);
    m_fCurrentY = m_fStartY;
}

template<typename T>
inline T base_easing_element<T>::update(T fDeltaTime) noexcept
{
    T fRet = T(0.f);

    if (m_eStatus == status::started)
    {
        m_fCurrentX = m_fCurrentX + fDeltaTime * m_fSpeed;

        if (m_fCurrentX < T(1.f))
        {
            m_fCurrentY =
                m_fStartY + m_EasingFunc(m_fCurrentX) * (m_fEndY - m_fStartY);
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

template<typename T>
inline void base_easing_element<T>::set_speed(T fSpeed) noexcept
{
    if (fSpeed > T(0.f))
        m_fSpeed = fSpeed;
}

template<typename T>
inline T base_easing_element<T>::get(void) const noexcept
{
    return m_fCurrentY;
}

template<typename T>
inline T base_easing_element<T>::get_fraction(void) const noexcept
{
    return m_fCurrentX;
}

template<typename T>
inline T base_easing_element<T>::get_speed(void) const noexcept
{
    return m_fSpeed;
}

template<typename T>
inline typename base_easing_element<T>::status base_easing_element<
    T>::get_status(void) const noexcept
{
    return m_eStatus;
}

template<typename T>
inline bool base_easing_element<T>::is_not_started(void) const noexcept
{
    return m_eStatus == status::not_started;
}

template<typename T>
inline bool base_easing_element<T>::is_started(void) const noexcept
{
    return m_eStatus == status::started;
}

template<typename T>
inline bool base_easing_element<T>::is_paused(void) const noexcept
{
    return m_eStatus == status::paused;
}

template<typename T>
inline bool base_easing_element<T>::is_finished(void) const noexcept
{
    return m_eStatus == status::finished;
}

} // namespace qx
