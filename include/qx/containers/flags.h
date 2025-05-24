/**

    @file      flags.h
    @author    Khrapov
    @date      01.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/macros/copyable_movable.h>
#include <qx/meta/concepts.h>
#include <qx/meta/type_traits.h>

#include <limits>

/**
    @def   QX_FLAGS_ENUM_CLASS
    @brief Define to let to use this enum class in different binary operations returning qx::flags
    @param enumName - enum class name
**/
#define QX_FLAGS_ENUM_CLASS(enumName)                                   \
    inline qx::flags<enumName> operator|(enumName left, enumName right) \
    {                                                                   \
        return qx::flags(left) | right;                                 \
    }                                                                   \
    inline qx::flags<enumName> operator&(enumName left, enumName right) \
    {                                                                   \
        return qx::flags(left) & right;                                 \
    }                                                                   \
    inline qx::flags<enumName> operator^(enumName left, enumName right) \
    {                                                                   \
        return qx::flags(left) ^ right;                                 \
    }

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
    // ------------------------------------------------ common operators -----------------------------------------------

    constexpr flags() noexcept = default;

    /**
        @brief Reverse (or logically negotiate) all bits
    **/
    constexpr void reverse() noexcept;

    /**
        @brief Shift bits to the left
        @param nShift - num of positions to shift
    **/
    constexpr void shift_left(size_t nShift) noexcept;

    /**
        @brief Shift bits to the right
        @param nShift - num of positions to shift
    **/
    constexpr void shift_right(size_t nShift) noexcept;

    constexpr flags operator~() const noexcept;

    constexpr flags& operator<<=(size_t nShift) noexcept;
    constexpr flags& operator>>=(size_t nShift) noexcept;

    constexpr flags operator<<(size_t nShift) const noexcept;
    constexpr flags operator>>(size_t nShift) const noexcept;

    // ------------------------------------------------ enum_t operators -----------------------------------------------

    /**
        @brief   flags object constructor
        @details Separate method for 1 arg to allow type deduction
        @param   eFlag - flag to add at construction
    **/
    constexpr flags(enum_t eFlag) noexcept;

    /**
        @brief  flags object constructor
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to add at construction
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
    constexpr flags(args_t... flags) noexcept;

    /**
        @brief  Add all the flags specified
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to add
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
    constexpr void add(args_t... flags) noexcept;

    /**
        @brief  Remove all the flags specified
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to remove
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
    constexpr void remove(args_t... flags) noexcept;

    /**
        @brief  Apply a bitwise XOR to a flags value
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to apply
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 1 && are_specific_v<enum_t, args_t...>)
    constexpr void xor_(args_t... flags) noexcept;

    constexpr auto   operator<=>(enum_t eFlag) const noexcept;
    constexpr flags& operator=(enum_t eFlag) noexcept;

    constexpr flags& operator|=(enum_t eFlag) noexcept;
    constexpr flags& operator&=(enum_t eFlag) noexcept;
    constexpr flags& operator^=(enum_t eFlag) noexcept;

    constexpr flags operator|(enum_t eFlag) const noexcept;
    constexpr flags operator&(enum_t eFlag) const noexcept;
    constexpr flags operator^(enum_t eFlag) const noexcept;

    // ------------------------------------------------ flags operators ------------------------------------------------

    QX_COPYMOVABLE(flags);

    /**
        @brief  Add all the flags specified
        @param  flags_ - flags to add
    **/
    constexpr void add(flags flags_) noexcept;

    /**
        @brief  Remove all the flags specified
        @param  flags_ - flags to remove
    **/
    constexpr void remove(flags flags_) noexcept;

    /**
        @brief  Apply a bitwise XOR to a flags value
        @param  flags_ - flags to apply
    **/
    constexpr void xor_(flags flags_) noexcept;

    constexpr auto operator<=>(const flags&) const noexcept = default;

    constexpr flags& operator|=(flags flags_) noexcept;
    constexpr flags& operator&=(flags flags_) noexcept;
    constexpr flags& operator^=(flags flags_) noexcept;

    constexpr flags operator|(flags flags_) const noexcept;
    constexpr flags operator&(flags flags_) const noexcept;
    constexpr flags operator^(flags flags_) const noexcept;

    // --------------------------------------------------- algorithms --------------------------------------------------

    /**
        @brief  Check if flag is present
        @param  eFlag - flag to check
        @retval       - true if flag is present
    **/
    constexpr bool contains(enum_t eFlag) const noexcept;

    /**
        @brief  Check if all the specified flags are present
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to check
        @retval true if all the specified flags are present
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
    constexpr bool contains_all(args_t... flags) const noexcept;

    /**
        @brief  Check if all the specified flags are present
        @param  other - flags to check
        @retval       - true if all the specified flags are present
    **/
    constexpr bool contains_all(flags other) const noexcept;

    /**
        @brief  Check if any of the specified flags is present
        @tparam args_t... - template parameters pack, all types should be same as enum_t
        @param  flags     - flags to check
        @retval           - true if any of the specified flags is present
    **/
    template<class... args_t>
        requires(sizeof...(args_t) >= 2 && are_specific_v<enum_t, args_t...>)
    constexpr bool contains_any(args_t... flags) const noexcept;

    /**
        @brief  Check if any of the specified flags is present
        @param  other - flags to check
        @retval       - true if any of the specified flags is present
    **/
    constexpr bool contains_any(flags other) const noexcept;

    /**
        @brief  Convert to the corresponding integer value
        @retval  - integer value
    **/
    constexpr underlying_type to_integer() const noexcept;

    /**
        @brief  Get a flags with all bits equal 1
        @retval  - flags with all bits equal 1
    **/
    static constexpr flags all_flags() noexcept;

private:
    underlying_type m_EnumFlags = 0;
};

} // namespace qx

#include <qx/containers/flags.inl>
