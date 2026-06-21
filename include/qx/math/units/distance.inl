/**

    @file      distance.inl
    @author    Khrapov
    @date      24.09.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/

template<>
struct qx::units::traits<qx::units::distance>
{
    template<arithmetic_c T>
    static constexpr unit<T, distance> normalize(unit<T, distance> unit) noexcept;

    template<class char_t>
    static constexpr auto get_suffixes() noexcept;

    static constexpr bool is_si(distance eDistance) noexcept;
};

template<qx::arithmetic_c T>
class qx::convert<T, qx::units::distance> : public units::details::base_converter<T, units::distance>
{
public:
    using units::details::base_converter<T, units::distance>::base_converter;

    constexpr unit<T, units::distance> to(units::distance eTo) const noexcept;
};

namespace qx::units::details
{

template<class T>
constexpr f64 to_meters(distance eFrom, T value) noexcept
{
    const double fValue  = static_cast<double>(value);
    double       fResult = 0.f;
    if (traits<distance>::is_si(eFrom))
    {
        fResult = fValue * pow(10, static_cast<int>(eFrom));
    }
    else
    {
        switch (eFrom)
        {
        case distance::mils:
            fResult = fValue * 0.0000254;
            break;

        case distance::inches:
            fResult = fValue * 0.0254;
            break;

        case distance::hands:
            fResult = fValue * 0.1016;
            break;

        case distance::links:
            fResult = fValue * 0.201168;
            break;

        case distance::feet:
            fResult = fValue * 0.3048;
            break;

        case distance::yards:
            fResult = fValue * 0.9144;
            break;

        case distance::rods:
            fResult = fValue * 5.0292;
            break;

        case distance::chains:
            fResult = fValue * 20.1168;
            break;

        case distance::furlongs:
            fResult = fValue * 201.168;
            break;

        case distance::miles:
            fResult = fValue * 1609.344;
            break;

        case distance::leagues:
            fResult = fValue * 4828.032;
            break;

        case distance::fathoms:
            fResult = fValue * 1.8288;
            break;

        case distance::cables:
            fResult = fValue * 185.2;
            break;

        case distance::nautical_miles:
            fResult = fValue * 1852.0;
            break;

        case distance::astronomical_units:
            fResult = fValue * 149597870700.0;
            break;

        case distance::light_years:
            fResult = fValue * 9460730472580800.0;
            break;

        case distance::parsecs:
            fResult = fValue * 30856775814913673.0;
            break;
        }
    }

    return fResult;
}

template<class T>
constexpr T from_meters(f64 fMeters, distance eTo) noexcept
{
    double fResult = 0.f;
    if (traits<distance>::is_si(eTo))
    {
        fResult = fMeters / pow(10, static_cast<int>(eTo));
    }
    else
    {
        switch (eTo)
        {
        case distance::mils:
            fResult = fMeters / 0.0000254;
            break;

        case distance::inches:
            fResult = fMeters / 0.0254;
            break;

        case distance::hands:
            fResult = fMeters / 0.1016;
            break;

        case distance::links:
            fResult = fMeters / 0.201168;
            break;

        case distance::feet:
            fResult = fMeters / 0.3048;
            break;

        case distance::yards:
            fResult = fMeters / 0.9144;
            break;

        case distance::rods:
            fResult = fMeters / 5.0292;
            break;

        case distance::chains:
            fResult = fMeters / 20.1168;
            break;

        case distance::furlongs:
            fResult = fMeters / 201.168;
            break;

        case distance::miles:
            fResult = fMeters / 1609.344;
            break;

        case distance::leagues:
            fResult = fMeters / 4828.032;
            break;

        case distance::fathoms:
            fResult = fMeters / 1.8288;
            break;

        case distance::cables:
            fResult = fMeters / 185.2;
            break;

        case distance::nautical_miles:
            fResult = fMeters / 1852.0;
            break;

        case distance::astronomical_units:
            fResult = fMeters / 149597870700.0;
            break;

        case distance::light_years:
            fResult = fMeters / 9460730472580800.0;
            break;

        case distance::parsecs:
            fResult = fMeters / 30856775814913673.0;
            break;
        }
    }

    return static_cast<T>(fResult);
}

} // namespace qx::units::details

template<qx::arithmetic_c T>
constexpr qx::unit<T, qx::units::distance> qx::units::traits<qx::units::distance>::normalize(
    unit<T, distance> unit) noexcept
{
    const f64 fMeters = details::to_meters(unit.type, unit.value);

    distance eTo = distance::petameters;
    if (fMeters < pow(10, static_cast<int>(distance::micrometers)))
    {
        eTo = distance::nanometers;
    }
    else if (fMeters < pow(10, static_cast<int>(distance::millimeters)))
    {
        eTo = distance::micrometers;
    }
    else if (fMeters < pow(10, static_cast<int>(distance::centimeters)))
    {
        eTo = distance::millimeters;
    }
    // skip decimeters as rarely used
    else if (fMeters < pow(10, static_cast<int>(distance::meters)))
    {
        eTo = distance::centimeters;
    }
    // skip decameters and hectometers as rarely used
    else if (fMeters < pow(10, static_cast<int>(distance::kilometers)))
    {
        eTo = distance::meters;
    }
    else if (fMeters < pow(10, static_cast<int>(distance::megameters)))
    {
        eTo = distance::kilometers;
    }
    else if (fMeters < pow(10, static_cast<int>(distance::gigameters)))
    {
        eTo = distance::megameters;
    }
    else if (fMeters < pow(10, static_cast<int>(distance::terameters)))
    {
        eTo = distance::gigameters;
    }
    else if (fMeters < pow(10, static_cast<int>(distance::petameters)))
    {
        eTo = distance::terameters;
    }

    return convert(unit).to(eTo);
}

template<class char_t>
constexpr auto qx::units::traits<qx::units::distance>::get_suffixes() noexcept
{
    using pair_type = std::pair<distance, basic_string_view<char_t>>;
    return std::array { pair_type { distance::nanometers, QX_STR_PREFIX(char_t, "nm") },
                        pair_type { distance::micrometers, QX_STR_PREFIX(char_t, "um") },
                        pair_type { distance::millimeters, QX_STR_PREFIX(char_t, "mm") },
                        pair_type { distance::centimeters, QX_STR_PREFIX(char_t, "cm") },
                        pair_type { distance::decimeters, QX_STR_PREFIX(char_t, "dm") },
                        pair_type { distance::meters, QX_STR_PREFIX(char_t, "m") },
                        pair_type { distance::decameters, QX_STR_PREFIX(char_t, "dam") },
                        pair_type { distance::hectometers, QX_STR_PREFIX(char_t, "hm") },
                        pair_type { distance::kilometers, QX_STR_PREFIX(char_t, "km") },
                        pair_type { distance::megameters, QX_STR_PREFIX(char_t, "Mm") },
                        pair_type { distance::gigameters, QX_STR_PREFIX(char_t, "Gm") },
                        pair_type { distance::terameters, QX_STR_PREFIX(char_t, "Tm") },
                        pair_type { distance::petameters, QX_STR_PREFIX(char_t, "Pm") },

                        pair_type { distance::mils, QX_STR_PREFIX(char_t, "mil") },
                        pair_type { distance::inches, QX_STR_PREFIX(char_t, "in") },
                        pair_type { distance::hands, QX_STR_PREFIX(char_t, "hh") },
                        pair_type { distance::links, QX_STR_PREFIX(char_t, "li") },
                        pair_type { distance::feet, QX_STR_PREFIX(char_t, "ft") },
                        pair_type { distance::yards, QX_STR_PREFIX(char_t, "yd") },
                        pair_type { distance::rods, QX_STR_PREFIX(char_t, "rd") },
                        pair_type { distance::chains, QX_STR_PREFIX(char_t, "ch") },
                        pair_type { distance::furlongs, QX_STR_PREFIX(char_t, "fur") },
                        pair_type { distance::miles, QX_STR_PREFIX(char_t, "mi") },
                        pair_type { distance::leagues, QX_STR_PREFIX(char_t, "lea") },

                        pair_type { distance::fathoms, QX_STR_PREFIX(char_t, "fm") },
                        pair_type { distance::cables, QX_STR_PREFIX(char_t, "cables") },
                        pair_type { distance::nautical_miles, QX_STR_PREFIX(char_t, "nmi") },

                        pair_type { distance::astronomical_units, QX_STR_PREFIX(char_t, "AU") },
                        pair_type { distance::light_years, QX_STR_PREFIX(char_t, "ly") },
                        pair_type { distance::parsecs, QX_STR_PREFIX(char_t, "pc") } };
}

constexpr bool qx::units::traits<qx::units::distance>::is_si(distance eDistance) noexcept
{
    return eDistance < distance::_last_metric;
}

template<qx::arithmetic_c T>
constexpr qx::unit<T, qx::units::distance> qx::convert<T, qx::units::distance>::to(units::distance eTo) const noexcept
{
    if (this->m_From.type == eTo)
        return { this->m_From.value, eTo };

    const f64 fMeters = units::details::to_meters(this->m_From.type, this->m_From.value);
    return { units::details::from_meters<T>(fMeters, eTo), eTo };
}

template<class char_t>
struct QX_FMT_NS::formatter<qx::units::distance, char_t>
    : qx::units::details::unit_formatter<qx::units::distance, char_t>
{
};
