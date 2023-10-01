/**

    @file      flags.h
    @author    Khrapov
    @date      01.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/meta/concepts.h>
#include "qx/macros/copyable_movable.h"
#include "qx/meta/type_traits.h"

namespace qx
{

/**

    @class   flags
    @brief   Wrapper for enumerations to be used as a list of flags
    @tparam  enum_t - enum flags type 
    @code

    enum class EFlags
    {
        None   = 0,
        First  = 1 << 0,
        Second = 1 << 1,
        Third  = 1 << 2,
        Fourth = 1 << 3,
    };

    qx::flags<EFlags> flags;

    @endcode

**/
template<enumeration_c enum_t>
class flags
{
    using underlying_type = std::underlying_type_t<enum_t>;

public:
    QX_COPYMOVABLE(flags);

    flags() noexcept                              = default;
    auto operator<=>(const flags&) const noexcept = default;

    /**
        @brief   flags object constructor
        @details Separate method for 1 arg to allow type deduction
        @param   eFlag - 
    **/
    flags(enum_t eFlag) noexcept;

    /**
        @brief  flags object constructor
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to add at construction
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
    flags(args_t... flags) noexcept;

    flags& operator=(enum_t eFlag) noexcept;
    auto   operator<=>(enum_t eFlag) const noexcept;

    /**
        @brief  Add all the flags specified
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to add
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
    void add(args_t... flags) noexcept;

    /**
        @brief  Remove all the flags specified
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to remove
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
    void remove(args_t... flags) noexcept;

    /**
        @brief  Check if flag is present
        @param  eFlag - flag to check
        @retval       - true if flag is present
    **/
    bool contains(enum_t eFlag) const noexcept;


    /**
        @brief  Check if all the specified flags are present
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to check
        @retval true if all the specified flags are present
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
    bool contains_all(args_t... flags) const noexcept;

    /**
        @brief  Check if any of the specified flags is present
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to check
        @retval           - true if any of the specified flags is present
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
    bool contains_any(args_t... flags) const noexcept;

private:
    underlying_type m_EnumFlags = 0;
};

} // namespace qx

#include <qx/containers/flags.inl>
