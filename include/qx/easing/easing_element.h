/**

    @file      easing_element.h
    @brief     Contains qx::base_easing_element class
    @author    Khrapov
    @date      4.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/easing/easing_functions.h>
#include <qx/useful_macros.h>

namespace qx
{

/**

    @class   base_easing_element
    @brief   An updatable element representing the value of the easing function
             at a given time
    @details ~
    @tparam  T - floating point ish value
    @author  Khrapov
    @date    04.05.2021

**/
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
    QX_COPYMOVABLE(base_easing_element)

    /**
        @brief base_easing_element object constructor
        @param func   - easing function
        @param fStart - start value
        @param fEnd   - end value
        @param fSpeed - speed of updating
    **/
    base_easing_element(
        const easing::func<T>& func,
        T                      fStart = T(0.f),
        T                      fEnd   = T(1.f),
        T                      fSpeed = T(1.f)) noexcept;

    /**
        @brief Mark element as active and let it update
    **/
    void start(void) noexcept;

    /**
        @brief Pause element if started
    **/
    void pause(void) noexcept;

    /**
        @brief Resume updating if paused
    **/
    void resume(void) noexcept;

    /**
        @brief Mark element as finished
    **/
    void finish(void) noexcept;

    /**
        @brief Mark element as inactive
    **/
    void reset(void) noexcept;

    /**
        @brief  Update element corresponding to easing function
        @param  fDeltaTime - delta time
        @retval            - the portion of time that was not used
    **/
    [[nodiscard]] T update(T fDeltaTime) noexcept;

    /**
        @brief Set speed value
        @param fSpeed - new speed value
    **/
    void set_speed(T fSpeed) noexcept;

    /**
        @brief  Get current value of element
        @retval - current value of element
    **/
    [[nodiscard]] T get(void) const noexcept;

    /**
        @brief  Get a fraction indicating how much of the element has played
        @retval - fraction [0.0, 1.0]
    **/
    [[nodiscard]] T get_fraction(void) const noexcept;

    /**
        @brief  Get speed value
        @retval - speed value
    **/
    [[nodiscard]] T get_speed(void) const noexcept;

    /**
        @brief  Get element status
        @retval - element status
    **/
    [[nodiscard]] status get_status(void) const noexcept;

    /**
        @brief  Check if element is not started
        @retval - true if element is not started
    **/
    [[nodiscard]] bool is_not_started(void) const noexcept;

    /**
        @brief  Check if element is started
        @retval - true if element is started
    **/
    [[nodiscard]] bool is_started(void) const noexcept;

    /**
        @brief  Check if element is paused
        @retval - true if element is paused
    **/
    [[nodiscard]] bool is_paused(void) const noexcept;

    /**
        @brief  Check if element is finished
        @retval - true if element is finished
    **/
    [[nodiscard]] bool is_finished(void) const noexcept;

private:
    easing::func<T> m_EasingFunc;
    status          m_eStatus   = status::not_started;
    T               m_fSpeed    = T(1.f);
    T               m_fCurrentX = T(0.f);
    T               m_fCurrentY = T(0.f);
    T               m_fStartY   = T(0.f);
    T               m_fEndY     = T(1.f);
};

using easing_element = base_easing_element<float>;

} // namespace qx

#include <qx/easing/easing_element.inl>
