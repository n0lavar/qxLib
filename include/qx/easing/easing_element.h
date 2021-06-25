//==============================================================================
//
//!\file                          easing_element.h
//
//!\brief       Contains qx::base_easing_element class
//!\details     ~
//
//!\author      Khrapov
//!\date        4.05.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/easing/easing_functions.h>

namespace qx
{

//==============================================================================
//
//!\class                  qx::base_easing_element<T>
//
//!\brief   An updatable element representing the value of the easing function
//          at a given time
//!\details ~
//
//!\author  Khrapov
//!\date    04.05.2021
//
//==============================================================================
template<typename T>
class base_easing_element
{
public:

    enum class status
    {
        not_started,
        started,
        paused,
        finished
    };

    using type = T;

public:

    base_easing_element     (const base_easing_element&)        noexcept = default;
    base_easing_element     (base_easing_element&&)             noexcept = default;
    base_easing_element     (const easing::func<T>& func,
                             T              fStart  = T(0.f),
                             T              fEnd    = T(1.f),
                             T              fSpeed  = T(1.f))   noexcept;

    base_easing_element& operator=(const base_easing_element&)  noexcept = default;
    base_easing_element& operator=(base_easing_element&&)       noexcept = default;

    void                    start           (void)              noexcept;
    void                    pause           (void)              noexcept;
    void                    resume          (void)              noexcept;
    void                    finish          (void)              noexcept;
    void                    reset           (void)              noexcept;
    [[nodiscard]] T         update          (T  fDeltaTime)     noexcept;
    void                    set_speed       (T  fSpeed)         noexcept;

    [[nodiscard]] T         get             (void)      const   noexcept;
    [[nodiscard]] T         get_fraction    (void)      const   noexcept;
    [[nodiscard]] T         get_speed       (void)      const   noexcept;
    [[nodiscard]] status    get_status      (void)      const   noexcept;
    [[nodiscard]] bool      is_not_started  (void)      const   noexcept;
    [[nodiscard]] bool      is_started      (void)      const   noexcept;
    [[nodiscard]] bool      is_paused       (void)      const   noexcept;
    [[nodiscard]] bool      is_finished     (void)      const   noexcept;

private:

    easing::func<T> m_EasingFunc;
    status          m_eStatus       = status::not_started;
    T               m_fSpeed        = T(1.f);
    T               m_fCurrentX     = T(0.f);
    T               m_fCurrentY     = T(0.f);
    T               m_fStartY       = T(0.f);
    T               m_fEndY         = T(1.f);
};

using easing_element = base_easing_element<float>;

}

#include <qx/easing/easing_element.inl>
