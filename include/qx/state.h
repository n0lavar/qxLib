/**

    @file      state.h
    @brief     Contains qx::state class
    @author    Khrapov
    @date      26.04.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/useful_macros.h>

namespace qx
{

/**

    @class   state
    @brief   State abstraction class
    @details State is an entity that can be set to its default value
    @tparam  T - state value type
    @author  Khrapov
    @date    27.04.2021
    
**/
template<class T>
class state
{
    friend struct std::hash<state<T>>;

public:
    QX_COPYMOVABLE(state<T>);

    /**
        @brief basic_state object constructor
    **/
    state(void) noexcept = default;

    /**
        @brief state object constructor
        @param value - start value
    **/
    state(const T& value) noexcept;

    /**
        @brief basic_state object constructor
        @param value        - start value
        @param defaultValue - default value
    **/
    state(const T& value, const T& defaultValue) noexcept;

    /**
        @brief  operator=
        @param  value - new state value
        @retval       - this object reference
    **/
    state& operator=(const T& value) noexcept;

    /**
        @brief  operator==
        @param   - other state
        @retval  - true, if objects are equal
    **/
    bool operator==(const state&) const noexcept = default;

    /**
        @brief  operator==
        @param  value - state value
        @retval       - true, if objects are equal
    **/
    bool operator==(const T& value) const noexcept;

    /**
        @brief  operator->
        @retval - state object pointer
    **/
    T* operator->(void) noexcept;

    /**
        @brief  operator->
        @retval - state object pointer
    **/
    const T* operator->(void) const noexcept;

    /**
        @brief  operator*
        @retval - state object reference
    **/
    T& operator*(void) noexcept;

    /**
        @brief  operator*
        @retval - state object reference
    **/
    const T& operator*(void) const noexcept;

    /**
        @brief Reset current state to its default value
    **/
    void reset(void) noexcept;

    /**
        @brief  Is current state default
        @retval - true if default
    **/
    bool is_default(void) const noexcept;

private:
    T m_State;
    T m_DefaultValue;
};

} // namespace qx

#include <qx/state.inl>
