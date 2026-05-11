/**

    @file      base.h
    @author    Khrapov
    @date      11.08.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/containers/string/format_string.h>
#include <qx/containers/string/string.h>
#include <qx/meta/concepts.h>

#include <optional>

namespace qx
{

namespace units
{

template<enumeration_c unit_t>
struct traits;

}

template<class T>
concept unit_enum_c = enumeration_c<T> && requires { units::traits<T>(); };

/**
    @struct unit
    @code
    // The things you can do with `qx::unit`:
    // 1. Convert it using `qx::convert`:
    qx::unit result = qx::convert(unit).to(qx::units::unit_type::type2);
    // 2. Format it:
    qx::string = qx::string::static_format(QXT("{}"), unit); // -> for ex. 20kB
    // 3. Create it from a string:
    std::optional<qx::unit<int, qx::units::data>> optResult =
        qx::unit_from_string<int, qx::units::data, qx::char_type>(QXT("20KiB"));
    // 4. Get the nearest meaningful value (SI units):
    // 2000B -> 1.95KiB
    // 3000B -> 2.92KiB
    qx::unit converted1 = qx::normalize_unit(unit);
    @endcode 
    @tparam T      - floating point or integral type
    @tparam unit_t - unit type enum
**/
template<arithmetic_c T, unit_enum_c unit_t>
struct unit
{
    constexpr      operator T() const noexcept;
    constexpr bool operator==(const unit<T, unit_t>& other) const noexcept;

    T      value;
    unit_t type;
};

/**

    @class   convert
    @brief   A conversion class
    @code
    // Usage:
    float result = qx::convert(value, qx::units::unit_type::type1).to(qx::units::unit_type::type2);
    // or
    qx::unit result = qx::convert(value, qx::units::unit_type::type1).to(qx::units::unit_type::type2);
    @endcode 
    @tparam  T      - floating point or integral value type
    @tparam  unit_t - unit type enum
    @author  Khrapov
    @date    13.08.2025

**/
template<arithmetic_c T, unit_enum_c unit_t>
class convert;

/**
    @brief  The function returns the closest value greater than one from the SI for the unit of measurement.
    @tparam T      - floating point or integral value type
    @tparam unit_t - unit type enum
    @param  unit   - input unit
    @retval        - the closest value greater than one from the SI for the unit of measurement
**/
template<arithmetic_c T, unit_enum_c unit_t>
constexpr unit<T, unit_t> normalize_unit(unit<T, unit_t> unit) noexcept;

/**
    @brief  The function returns the closest value greater than one from the SI for the unit of measurement.
    @tparam T            - floating point or integral value type
    @tparam unit_t       - unit type enum
    @param  value        - input unit value
    @param  eInitialType - input unit type
    @retval              - the closest value greater than one from the SI for the unit of measurement
**/
template<arithmetic_c T, unit_enum_c unit_t>
constexpr unit<T, unit_t> normalize_unit(T value, unit_t eInitialType) noexcept;

/**
    @brief   Creates a unit from a string
    @details Input examples: `20KiB` `20 KiB` `20 KiB ` `20KiB `
    @tparam  T       - expected value type
    @tparam  unit_t  - unit enum
    @tparam  char_t  - input string char type
    @param   svValue - input string value
    @retval          - a unit if created successfully or `std::nullopt`
**/
template<arithmetic_c T, unit_enum_c unit_t, class char_t>
std::optional<unit<T, unit_t>> unit_from_string(basic_string_view<char_t> svValue) noexcept;

/**
    @brief   Creates a unit from a string
    @details Input examples: `20KiB` `20 KiB` `20 KiB ` `20KiB `
    @tparam  T        - expected value type
    @tparam  unit_t   - unit enum
    @tparam  char_t   - input string char type
    @param   pszValue - input string value
    @retval           - a unit if created successfully or `std::nullopt`
**/
template<arithmetic_c T, unit_enum_c unit_t, class char_t>
std::optional<unit<T, unit_t>> unit_from_string(const char_t* pszValue) noexcept;

/**
    @brief  Get a unit suffix if exists
    @tparam unit_t - unit enum
    @tparam char_t - result string view char type
    @param  eUnit  - unit to search
    @retval        - unit suffix
**/
template<unit_enum_c unit_t, class char_t = char_type>
constexpr std::optional<basic_string_view<char_t>> get_unit_suffix(unit_t eUnit) noexcept;

} // namespace qx

#include <qx/math/units/base.inl>
