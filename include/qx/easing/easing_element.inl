/**

    @file      easing_element.inl
    @author    Khrapov
    @date      4.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class T>
inline base_easing_element<T>::base_easing_element(const easing::func<T>& func, T fStart, T fEnd, T fSpeed) noexcept
    : m_EasingFunc(func)
    , m_fCurrentY(fStart)
    , m_fStartY(fStart)
    , m_fEndY(fEnd)
{
    set_speed(fSpeed);
}

template<class T>
inline void base_easing_element<T>::start() noexcept
{
    m_eStatus   = status::started;
    m_fCurrentX = T(0.f);
    m_fCurrentY = m_fStartY;
}

template<class T>
inline void base_easing_element<T>::pause() noexcept
{
    if (m_eStatus == status::started)
        m_eStatus = status::paused;
}

template<class T>
inline void base_easing_element<T>::resume() noexcept
{
    if (m_eStatus == status::paused)
        m_eStatus = status::started;
}

template<class T>
inline void base_easing_element<T>::finish() noexcept
{
    m_eStatus   = status::finished;
    m_fCurrentX = T(1.f);
    m_fCurrentY = m_fEndY;
}

template<class T>
inline void base_easing_element<T>::reset() noexcept
{
    m_eStatus   = status::not_started;
    m_fCurrentX = T(0.f);
    m_fCurrentY = m_fStartY;
}

template<class T>
inline T base_easing_element<T>::update(T fDeltaTime) noexcept
{
    T fRet = T(0.f);

    if (m_eStatus == status::started)
    {
        m_fCurrentX = m_fCurrentX + fDeltaTime * m_fSpeed;

        if (m_fCurrentX < T(1.f))
        {
            m_fCurrentY = m_fStartY + m_EasingFunc(m_fCurrentX) * (m_fEndY - m_fStartY);
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

template<class T>
inline void base_easing_element<T>::set_speed(T fSpeed) noexcept
{
    if (fSpeed > T(0.f))
        m_fSpeed = fSpeed;
}

template<class T>
inline T base_easing_element<T>::get() const noexcept
{
    return m_fCurrentY;
}

template<class T>
inline T base_easing_element<T>::get_fraction() const noexcept
{
    return m_fCurrentX;
}

template<class T>
inline T base_easing_element<T>::get_speed() const noexcept
{
    return m_fSpeed;
}

template<class T>
inline typename base_easing_element<T>::status base_easing_element<T>::get_status() const noexcept
{
    return m_eStatus;
}

template<class T>
inline bool base_easing_element<T>::is_not_started() const noexcept
{
    return m_eStatus == status::not_started;
}

template<class T>
inline bool base_easing_element<T>::is_started() const noexcept
{
    return m_eStatus == status::started;
}

template<class T>
inline bool base_easing_element<T>::is_paused() const noexcept
{
    return m_eStatus == status::paused;
}

template<class T>
inline bool base_easing_element<T>::is_finished() const noexcept
{
    return m_eStatus == status::finished;
}

} // namespace qx
