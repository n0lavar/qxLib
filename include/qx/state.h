/**

    @file      state.h
    @brief     Contains qx::state class
    @author    Khrapov
    @date      26.04.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/useful_macros.h>

#include <limits>

namespace qx
{

/**
    @struct qx::state_default_traits
    @date   27.04.2021
**/
struct state_default_traits
{
    using type                          = int;
    static constexpr type default_value = std::numeric_limits<int>::max();
};

/**

    @class   qx::basic_state
    @brief   State abstraction class
    @details State is an entity that can be set to its default value
    @tparam  Traits - state traits type \see qx::state_default_traits
    @author  Khrapov
    @date    27.04.2021
    
**/
template<class Traits>
class basic_state
{
    friend struct std::hash<basic_state<Traits>>;

public:
    using type                          = typename Traits::type;
    static constexpr type default_value = Traits::default_value;

    QX_COPYMOVABLE(basic_state);

    /**
        @brief basic_state object constructor
    **/
    basic_state(void) = default;

    /**
        @brief basic_state object constructor
        @param value - start value
    **/
    basic_state(const type& value);

    /**
        @brief  operator=
        @param  value - new state value
        @retval       - this object reference
    **/
    basic_state& operator=(const type& value);

    /**
        @brief  operator==
        @param   - other state
        @retval  - true, if objects are equal
    **/
    bool operator==(const basic_state&) const = default;

    /**
        @brief  operator==
        @param  value - state value
        @retval       - true, if objects are equal
    **/
    bool operator==(const type& value) const;

    /**
        @brief Reset current state to its default value
    **/
    void reset(void);

    /**
        @brief  Is current state default
        @retval - true if default
    **/
    bool is_default(void) const;

private:
    type m_State = default_value;
};

using state = basic_state<state_default_traits>;

} // namespace qx

#include <qx/state.inl>
