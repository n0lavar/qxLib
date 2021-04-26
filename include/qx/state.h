//==============================================================================
//
//!\file                            state.h
//
//!\brief       Contains qx::state class
//!\details     ~
//
//!\author      Khrapov
//!\date        26.04.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <limits>

namespace qx
{

//==============================================================================
//
//!\struct                  qx::state_default_traits
//!\author  Khrapov
//!\date    27.04.2021
//==============================================================================
struct state_default_traits
{
    using type = int;
    static constexpr type default_value = std::numeric_limits<int>::max();
};

//==============================================================================
//
//!\class                  qx::basic_state<Traits>
//
//!\brief   State abstraction class
//!\details ~
//
//!\author  Khrapov
//!\date    27.04.2021
//
//==============================================================================
template<class Traits>
class basic_state
{
    friend struct std::hash<basic_state<Traits>>;

public:

    using type = typename Traits::type;
    static constexpr type default_value = Traits::default_value;

    basic_state(void)               = default;
    basic_state(const basic_state&) = default;
    basic_state(basic_state&&)      = default;
    basic_state(const type& value)
        : m_State(value)
    {
    }

    basic_state& operator=(const basic_state&)  = default;
    basic_state& operator=(basic_state&&)       = default;
    basic_state& operator=(const type& value)
    {
        m_State = value;
        return *this;
    }

    bool operator==(const basic_state&) const = default;
    bool operator==(const type& value)  const
    {
        return m_State == value;
    }

    void reset(void)
    {
        m_State = default_value;
    }

    bool is_default(void) const
    {
        return m_State == default_value;
    }

private:

    type m_State = default_value;
};

using state = basic_state<state_default_traits>;

}

namespace std
{
    template <class Traits>
    struct hash<qx::basic_state<Traits>>
    {
        size_t operator()(const qx::basic_state<Traits>& state) const noexcept
        {
            return std::hash<typename Traits::type>()(
                state.m_State);
        }
    };
}
