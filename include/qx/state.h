/**

    @file      state.h
    @author    Khrapov
    @date      26.04.2021
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/copyable_movable.h>

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
    QX_COPYMOVABLE(state);

    state() noexcept = default;

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

    state& operator=(const T& value) noexcept;

    bool operator==(const state&) const noexcept = default;
    bool operator==(const T& value) const noexcept;

    T*       operator->() noexcept;
    const T* operator->() const noexcept;

    T&       operator*() noexcept;
    const T& operator*() const noexcept;

    /**
        @brief Reset current state to its default value
    **/
    void reset() noexcept;

    /**
        @brief  Is current state default
        @retval - true if default
    **/
    bool is_default() const noexcept;

private:
    T m_State;
    T m_DefaultValue;
};

} // namespace qx

#include <qx/state.inl>
