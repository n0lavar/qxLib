/**

    @file      color.inl
    @author    Khrapov
    @date      10.04.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

namespace detail
{

/**

    @class   string_to_color_converter
    @brief   Helper class for string -> color conversion
    @details The only purpose of this class is to hide the map from a user
    @author  Khrapov
    @date    5.04.2023

**/
class string_to_color_converter
{
    QX_SINGLETON(string_to_color_converter);
    friend color;

private:
    /**
        @brief Add new color to the mapping
        @param nNameHash - color name hash
        @param color     - color
    **/
    void add(size_t nNameHash, color color)
    {
        m_StringToColor[nNameHash] = color;
    }

    /**
        @brief  Try to get color from the color name
        @param  nNameHash - color name hash
        @retval           - color or nullopt
    **/
    std::optional<color> get(size_t nNameHash) const
    {
        if (const auto it = m_StringToColor.find(nNameHash); it != m_StringToColor.end())
            return it->second;

        return std::nullopt;
    }

private:
    std::unordered_map<size_t, color> m_StringToColor;
};

} // namespace detail

constexpr color::color(float fRed, float fGreen, float fBlue, float fAlpha) noexcept
{
    assign_checked({ fRed, fGreen, fBlue, fAlpha });
}

constexpr color::color(int nRed, int nGreen, int nBlue, int nAlpha) noexcept
    : color(dec_to_float(nRed), dec_to_float(nGreen), dec_to_float(nBlue), dec_to_float(nAlpha))
{
}

constexpr color::color(u64 nHexValue) noexcept
    : color(
        dec_to_float(nHexValue >> 24 & 0xFF),
        dec_to_float(nHexValue >> 16 & 0xFF),
        dec_to_float(nHexValue >> 8 & 0xFF),
        dec_to_float(nHexValue >> 0 & 0xFF))
{
}

constexpr color::color(const glm::ivec3& vec3) noexcept
    : color(dec_to_float(vec3.x), dec_to_float(vec3.y), dec_to_float(vec3.z), 1.f)
{
}

constexpr color::color(const glm::ivec4& vec4) noexcept
    : color(dec_to_float(vec4.x), dec_to_float(vec4.y), dec_to_float(vec4.z), dec_to_float(vec4.w))
{
}

constexpr float color::r() const noexcept
{
    return m_Color.x;
}

constexpr float color::g() const noexcept
{
    return m_Color.y;
}

constexpr float color::b() const noexcept
{
    return m_Color.z;
}

constexpr float color::a() const noexcept
{
    return m_Color.w;
}

constexpr float& color::operator[](size_t i) noexcept
{
    return m_Color[static_cast<glm::length_t>(i)];
}

constexpr const float& color::operator[](size_t i) const noexcept
{
    return m_Color[static_cast<glm::length_t>(i)];
}

constexpr int color::r_dec() const noexcept
{
    return float_to_dec(m_Color.x);
}

constexpr int color::g_dec() const noexcept
{
    return float_to_dec(m_Color.y);
}

constexpr int color::b_dec() const noexcept
{
    return float_to_dec(m_Color.z);
}

constexpr int color::a_dec() const noexcept
{
    return float_to_dec(m_Color.w);
}

constexpr const float* color::data() const noexcept
{
    return &(m_Color.x);
}

constexpr unsigned int color::hex_rgba() const noexcept
{
    const unsigned int r = static_cast<unsigned int>(float_to_dec(m_Color.x));
    const unsigned int g = static_cast<unsigned int>(float_to_dec(m_Color.y));
    const unsigned int b = static_cast<unsigned int>(float_to_dec(m_Color.z));
    const unsigned int a = static_cast<unsigned int>(float_to_dec(m_Color.w));

    return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (a & 0xff);
}

constexpr unsigned int color::hex_argb() const noexcept
{
    const unsigned int r = static_cast<unsigned int>(float_to_dec(m_Color.x));
    const unsigned int g = static_cast<unsigned int>(float_to_dec(m_Color.y));
    const unsigned int b = static_cast<unsigned int>(float_to_dec(m_Color.z));
    const unsigned int a = static_cast<unsigned int>(float_to_dec(m_Color.w));

    return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

constexpr bool color::operator==(const color& other) const noexcept
{
    return m_Color == other.m_Color;
}

constexpr color::operator glm::vec3() const noexcept
{
    return m_Color;
}

constexpr color::operator glm::vec4() const noexcept
{
    return m_Color;
}

constexpr void color::update_r(float fDeltaValue) noexcept
{
    assign_component_checked(m_Color.x, m_Color.x + fDeltaValue);
}

constexpr void color::update_g(float fDeltaValue) noexcept
{
    assign_component_checked(m_Color.y, m_Color.y + fDeltaValue);
}

constexpr void color::update_b(float fDeltaValue) noexcept
{
    assign_component_checked(m_Color.z, m_Color.z + fDeltaValue);
}

constexpr void color::update_a(float fDeltaValue) noexcept
{
    assign_component_checked(m_Color.w, m_Color.w + fDeltaValue);
}

constexpr void color::update_r_dec(int nDeltaValue) noexcept
{
    assign_component_checked(m_Color.x, m_Color.x + dec_to_float(nDeltaValue));
}

constexpr void color::update_g_dec(int nDeltaValue) noexcept
{
    assign_component_checked(m_Color.y, m_Color.y + dec_to_float(nDeltaValue));
}

constexpr void color::update_b_dec(int nDeltaValue) noexcept
{
    assign_component_checked(m_Color.z, m_Color.z + dec_to_float(nDeltaValue));
}

constexpr void color::update_a_dec(int nDeltaValue) noexcept
{
    assign_component_checked(m_Color.w, m_Color.w + dec_to_float(nDeltaValue));
}

constexpr void color::set_r(float fValue) noexcept
{
    assign_component_checked(m_Color.x, fValue);
}

constexpr void color::set_g(float fValue) noexcept
{
    assign_component_checked(m_Color.y, fValue);
}

constexpr void color::set_b(float fValue) noexcept
{
    assign_component_checked(m_Color.z, fValue);
}

constexpr void color::set_a(float fValue) noexcept
{
    assign_component_checked(m_Color.w, fValue);
}

constexpr void color::set_r_dec(int nValue) noexcept
{
    assign_component_checked(m_Color.x, dec_to_float(nValue));
}

constexpr void color::set_g_dec(int nValue) noexcept
{
    assign_component_checked(m_Color.y, dec_to_float(nValue));
}

constexpr void color::set_b_dec(int nValue) noexcept
{
    assign_component_checked(m_Color.z, dec_to_float(nValue));
}

constexpr void color::set_a_dec(int nValue) noexcept
{
    assign_component_checked(m_Color.w, dec_to_float(nValue));
}

constexpr void color::darken(float fPercent) noexcept
{
    brighten(-fPercent);
}

constexpr void color::brighten(float fPercent) noexcept
{
    m_Color.x *= (100.f + fPercent) / 100.f;
    m_Color.y *= (100.f + fPercent) / 100.f;
    m_Color.z *= (100.f + fPercent) / 100.f;
}

constexpr color color::darken(const color& other, float fPercent) noexcept
{
    color ret = other;
    ret.darken(fPercent);
    return ret;
}

constexpr color color::brighten(const color& other, float fPercent) noexcept
{
    color ret = other;
    ret.brighten(fPercent);
    return ret;
}

template<class TChar>
inline bool color::add_color_to_mapping(
    std::basic_string_view<TChar> svColorName,
    int                           nRed,
    int                           nGreen,
    int                           nBlue) noexcept
{
    basic_string<TChar> sName = svColorName;
    detail::string_to_color_converter::get_instance().add(
        basic_string_hash<fast_hash_string_traits<TChar>>(sName),
        color(nRed, nGreen, nBlue));

    sName.remove_all(QX_CHAR_PREFIX(TChar, '_'));
    detail::string_to_color_converter::get_instance().add(
        basic_string_hash<fast_hash_string_traits<TChar>>(sName),
        color(nRed, nGreen, nBlue));

    return true;
}

template<class TChar>
inline std::optional<color> color::from_string(std::basic_string_view<TChar> svColorName) noexcept
{
    if (const auto optColor = detail::string_to_color_converter::get_instance().get(
            basic_string_hash<fast_hash_string_traits<TChar>>(svColorName)))
    {
        return *optColor;
    }

    std::optional<color> optColor;

    const bool bStartsWith0x =
        svColorName.starts_with(QX_STR_PREFIX(TChar, "0x")) && (svColorName.size() == 8 || svColorName.size() == 10);

    if (bStartsWith0x || svColorName.starts_with(QX_STR_PREFIX(TChar, "#")) && svColorName.size() == 7)
    {
        // TODO no conversion method for string view so far
        // but with SSO this should be fine
        const size_t        nOffset = bStartsWith0x ? 2 : 1;
        basic_string<TChar> sColorName =
            std::basic_string_view<TChar>(svColorName.data() + nOffset, svColorName.size() - nOffset);

        auto ReadHex = [](basic_string<TChar>& s) -> std::optional<color>
        {
            s.to_lower();
            if (const auto optInt = s.template to<u64>(QX_STR_PREFIX(TChar, "%llx")))
                return color(*optInt);

            return std::nullopt;
        };

        if (sColorName.length() == 6)
        {
            sColorName += QX_STR_PREFIX(TChar, "FF");
            optColor = ReadHex(sColorName);
        }
        else if (sColorName.length() == 8)
        {
            optColor = ReadHex(sColorName);
        }
    }

    return optColor;
}

template<class TChar>
inline std::optional<color> color::from_string(const TChar* pszColorName) noexcept
{
    return from_string(std::basic_string_view<TChar>(pszColorName));
}

constexpr color color::empty() noexcept
{
    return color(0, 0, 0, 0);
}

constexpr size_t color::size() noexcept
{
    return 4;
}

constexpr float color::clamp_value(float fValue) noexcept
{
    return std::clamp(fValue, 0.f, 1.f);
}

constexpr float color::dec_to_float(int nValue) noexcept
{
    return static_cast<float>(nValue) / 255.f;
}

constexpr int color::float_to_dec(float fValue) noexcept
{
    return static_cast<int>(fValue * 255.f);
}

constexpr void color::assign_checked(const glm::vec4& other) noexcept
{
    assign_component_checked(m_Color.x, other.x);
    assign_component_checked(m_Color.y, other.y);
    assign_component_checked(m_Color.z, other.z);
    assign_component_checked(m_Color.w, other.w);
}

constexpr void color::assign_component_checked(float& pComponent, float fValue) noexcept
{
    pComponent = clamp_value(fValue);
}

} // namespace qx
