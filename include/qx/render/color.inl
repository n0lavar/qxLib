/**

    @file      color.inl
    @author    Khrapov
    @date      10.04.2021
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/

template<>
struct std::hash<qx::color>
{
    constexpr size_t operator()(const qx::color& color) const noexcept
    {
        size_t nHash = 0;
        qx::hash_combine(nHash, color.r());
        qx::hash_combine(nHash, color.g());
        qx::hash_combine(nHash, color.b());
        qx::hash_combine(nHash, color.a());
        return nHash;
    }
};

namespace qx
{

namespace details
{

/**

    @class   string_to_color_converter
    @brief   Helper class for string -> color conversion
    @details The only purpose of this class is to hide the map from a user
    @tparam  char_t - string char type
    @author  Khrapov
    @date    5.04.2023

**/
template<class char_t>
class string_to_color_converter final : public singleton<string_to_color_converter<char_t>>
{
    friend color;

#define _QX_ADD_COLOR(snakeCaseName, pascalCaseName, r, g, b)                               \
    add(QX_STR_PREFIX(char_t, #snakeCaseName), color_name_type::css_snake, color(r, g, b)); \
    add(QX_STR_PREFIX(char_t, #pascalCaseName), color_name_type::css_pascal, color(r, g, b));

public:
    string_to_color_converter() noexcept
    {
        _QX_COLORS(_QX_ADD_COLOR)
    }

    /**
        @brief Add new color to the mapping
        @param sName - color name
        @param color - color
    **/
    void add(basic_string<char_t> sName, color_name_type eColorNameType, color color) noexcept
    {
        if (eColorNameType == color_name_type::css_snake)
            m_ColorToCssSnake[color] = sName;
        else if (eColorNameType == color_name_type::css_pascal)
            m_ColorToCssPascal[color] = sName;

        m_StringToColor[sName] = std::move(color);
    }

    /**
        @brief  Try to get ac olor from a color name
        @param  sName - color name
        @retval       - color or nullopt
    **/
    std::optional<color> get(const basic_string<char_t>& sName) const noexcept
    {
        if (const auto it = m_StringToColor.find(sName); it != m_StringToColor.end())
            return it->second;

        return std::nullopt;
    }

    /**
        @brief  Try to a color name get from a color 
        @param  color          - color
        @param  eColorNameType - color type to get
        @retval                - color name or nullopt
    **/
    std::optional<basic_string_view<char_t>> get(const color& color, color_name_type eColorNameType) const noexcept
    {
        if (eColorNameType == color_name_type::css_snake)
        {
            if (const auto it = m_ColorToCssSnake.find(color); it != m_ColorToCssSnake.end())
                return it->second;
        }
        else if (eColorNameType == color_name_type::css_pascal)
        {
            if (const auto it = m_ColorToCssPascal.find(color); it != m_ColorToCssPascal.end())
                return it->second;
        }

        return std::nullopt;
    }

private:
    std::unordered_map<basic_string<char_t>, color> m_StringToColor;
    std::unordered_map<color, basic_string<char_t>> m_ColorToCssSnake;
    std::unordered_map<color, basic_string<char_t>> m_ColorToCssPascal;
};

} // namespace details

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

constexpr unsigned int color::hex_rgb() const noexcept
{
    const unsigned int r = static_cast<unsigned int>(float_to_dec(m_Color.x));
    const unsigned int g = static_cast<unsigned int>(float_to_dec(m_Color.y));
    const unsigned int b = static_cast<unsigned int>(float_to_dec(m_Color.z));

    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + ((b & 0xff) << 0);
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

inline std::optional<color> color::from_string(string_view svColorName) noexcept
{
    if (const auto optColor = details::string_to_color_converter<char_type>::get_instance().get(svColorName))
        return *optColor;

    std::optional<color> optColor;

    const bool bStartsWith0x =
        svColorName.starts_with(QXT("0x")) && (svColorName.size() == 8 || svColorName.size() == 10);

    if (bStartsWith0x || svColorName.starts_with(QXT("#")) && svColorName.size() == 7)
    {
        // TODO no conversion method for string view so far
        // but with SSO this should be fine
        const size_t nOffset    = bStartsWith0x ? 2 : 1;
        string       sColorName = string_view(svColorName.data() + nOffset, svColorName.size() - nOffset);

        auto ReadHex = [](string& s) -> std::optional<color>
        {
            s.to_lower();
            if (const auto optInt = s.template to<u64>(QXT("%llx")))
                return color(*optInt);

            return std::nullopt;
        };

        if (sColorName.length() == 6)
        {
            sColorName += QXT("FF");
            optColor = ReadHex(sColorName);
        }
        else if (sColorName.length() == 8)
        {
            optColor = ReadHex(sColorName);
        }
    }

    return optColor;
}

constexpr color color::from_hash(size_t nHash) noexcept
{
    return color(
        static_cast<u8>(nHash >> 0 & 0xFF),
        static_cast<u8>(nHash >> 8 & 0xFF),
        static_cast<u8>(nHash >> 16 & 0xFF));
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

template<class char_t>
struct QX_FMT_NS::formatter<qx::color, char_t>
{
    template<class format_parse_context_t>
    constexpr auto parse(format_parse_context_t& ctx)
    {
        auto it = ctx.begin();
        if (it != ctx.end())
        {
            if (*it == QX_CHAR_PREFIX(char_t, 's'))
            {
                ++it;
                optColorNameType = qx::color_name_type::css_snake;
            }
            else if (*it == QX_CHAR_PREFIX(char_t, 'p'))
            {
                ++it;
                optColorNameType = qx::color_name_type::css_pascal;
            }
            else if (*it == QX_CHAR_PREFIX(char_t, 'x'))
            {
                ++it;
                optColorNameType = qx::color_name_type::hex_lower;
            }
            else if (*it == QX_CHAR_PREFIX(char_t, 'X'))
            {
                ++it;
                optColorNameType = qx::color_name_type::hex_upper;
            }
            else if (*it == QX_CHAR_PREFIX(char_t, 'r'))
            {
                ++it;
                optColorNameType = qx::color_name_type::rgb;
            }

            if (it != ctx.end())
            {
                if (*it == QX_CHAR_PREFIX(char_t, 'a'))
                {
                    ++it;
                    bAddAlpha = true;
                }
            }
        }

        if (it != ctx.end() && *it != QX_CHAR_PREFIX(char_t, '}'))
            throw QX_FMT_NS::format_error("unknown spec");

        return it;
    }

    template<class format_context_t>
    auto format(const qx::color& color, format_context_t& ctx) const
    {
        const qx::color_name_type eColorNameType =
            optColorNameType ? *optColorNameType : qx::color_name_type::hex_upper;

        std::optional<qx::basic_string_view<char_t>> optResult =
            qx::details::string_to_color_converter<char_t>::get_instance().get(color, eColorNameType);

        if (optResult)
        {
            return std::format_to(ctx.out(), QX_STR_PREFIX(char_t, "{}"), *optResult);
        }
        else
        {
            if (eColorNameType == qx::color_name_type::rgb)
            {
                auto it = std::format_to(
                    ctx.out(),
                    QX_STR_PREFIX(char_t, "{},{},{}"),
                    color.r_dec(),
                    color.g_dec(),
                    color.b_dec());

                if (bAddAlpha)
                    it = std::format_to(ctx.out(), QX_STR_PREFIX(char_t, ",{}"), color.a_dec());

                return it;
            }
            else if (eColorNameType == qx::color_name_type::hex_lower)
            {
                auto it = std::format_to(
                    ctx.out(),
                    QX_STR_PREFIX(char_t, "{:x}{:x}{:x}"),
                    color.r_dec(),
                    color.g_dec(),
                    color.b_dec());

                if (bAddAlpha)
                    it = std::format_to(ctx.out(), QX_STR_PREFIX(char_t, "{:x}"), color.a_dec());

                return it;
            }
            else
            {
                // hex_upper as a fallback
                auto it = std::format_to(
                    ctx.out(),
                    QX_STR_PREFIX(char_t, "{:X}{:X}{:X}"),
                    color.r_dec(),
                    color.g_dec(),
                    color.b_dec());

                if (bAddAlpha || !optColorNameType)
                    it = std::format_to(ctx.out(), QX_STR_PREFIX(char_t, "{:X}"), color.a_dec());

                return it;
            }
        }
    }

    std::optional<qx::color_name_type> optColorNameType;
    bool                               bAddAlpha = false;
};
