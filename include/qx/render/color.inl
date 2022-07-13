/**

    @file      color.inl
    @author    Khrapov
    @date      10.04.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

constexpr color::color(
    float fRed,
    float fGreen,
    float fBlue,
    float fAlpha) noexcept
{
    assign_checked({ fRed, fGreen, fBlue, fAlpha });
}

constexpr color::color(int nRed, int nGreen, int nBlue, int nAlpha) noexcept
    : color(
        dec_to_float(nRed),
        dec_to_float(nGreen),
        dec_to_float(nBlue),
        dec_to_float(nAlpha))
{
}

constexpr color::color(unsigned int nHexValue) noexcept
    : color(
        dec_to_float(nHexValue >> 24 & 0xFF),
        dec_to_float(nHexValue >> 16 & 0xFF),
        dec_to_float(nHexValue >> 8 & 0xFF),
        dec_to_float(nHexValue >> 0 & 0xFF))
{
}

constexpr color::color(const glm::ivec3& vec3) noexcept
    : color(
        dec_to_float(vec3.x),
        dec_to_float(vec3.y),
        dec_to_float(vec3.z),
        1.f)
{
}

constexpr color::color(const glm::ivec4& vec4) noexcept
    : color(
        dec_to_float(vec4.x),
        dec_to_float(vec4.y),
        dec_to_float(vec4.z),
        dec_to_float(vec4.w))
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

constexpr unsigned int color::hex() const noexcept
{
    const unsigned int r = static_cast<unsigned int>(float_to_dec(m_Color.x));
    const unsigned int g = static_cast<unsigned int>(float_to_dec(m_Color.y));
    const unsigned int b = static_cast<unsigned int>(float_to_dec(m_Color.z));
    const unsigned int a = static_cast<unsigned int>(float_to_dec(m_Color.w));

    return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
           + (a & 0xff);
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
    assign_r_checked(m_Color.x + fDeltaValue);
}

constexpr void color::update_g(float fDeltaValue) noexcept
{
    assign_g_checked(m_Color.y + fDeltaValue);
}

constexpr void color::update_b(float fDeltaValue) noexcept
{
    assign_b_checked(m_Color.z + fDeltaValue);
}

constexpr void color::update_a(float fDeltaValue) noexcept
{
    assign_a_checked(m_Color.w + fDeltaValue);
}

constexpr void color::update_r_dec(int nDeltaValue) noexcept
{
    assign_r_checked(m_Color.x + dec_to_float(nDeltaValue));
}

constexpr void color::update_g_dec(int nDeltaValue) noexcept
{
    assign_g_checked(m_Color.y + dec_to_float(nDeltaValue));
}

constexpr void color::update_b_dec(int nDeltaValue) noexcept
{
    assign_b_checked(m_Color.z + dec_to_float(nDeltaValue));
}

constexpr void color::update_a_dec(int nDeltaValue) noexcept
{
    assign_a_checked(m_Color.w + dec_to_float(nDeltaValue));
}

constexpr void color::set_r(float fValue) noexcept
{
    assign_r_checked(fValue);
}

constexpr void color::set_g(float fValue) noexcept
{
    assign_g_checked(fValue);
}

constexpr void color::set_b(float fValue) noexcept
{
    assign_b_checked(fValue);
}

constexpr void color::set_a(float fValue) noexcept
{
    assign_a_checked(fValue);
}

constexpr void color::set_r_dec(int nValue) noexcept
{
    assign_r_checked(dec_to_float(nValue));
}

constexpr void color::set_g_dec(int nValue) noexcept
{
    assign_g_checked(dec_to_float(nValue));
}

constexpr void color::set_b_dec(int nValue) noexcept
{
    assign_b_checked(dec_to_float(nValue));
}

constexpr void color::set_a_dec(int nValue) noexcept
{
    assign_a_checked(dec_to_float(nValue));
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

constexpr color color::aqua(float fAlpha) noexcept
{
    return color(000, 255, 255, float_to_dec(fAlpha));
}

constexpr color color::black(float fAlpha) noexcept
{
    return color(000, 000, 000, float_to_dec(fAlpha));
}

constexpr color color::blue(float fAlpha) noexcept
{
    return color(000, 000, 255, float_to_dec(fAlpha));
}

constexpr color color::fuchsia(float fAlpha) noexcept
{
    return color(255, 000, 255, float_to_dec(fAlpha));
}

constexpr color color::gray(float fAlpha) noexcept
{
    return color(128, 128, 128, float_to_dec(fAlpha));
}

constexpr color color::green(float fAlpha) noexcept
{
    return color(000, 128, 000, float_to_dec(fAlpha));
}

constexpr color color::lime(float fAlpha) noexcept
{
    return color(000, 255, 000, float_to_dec(fAlpha));
}

constexpr color color::maroon(float fAlpha) noexcept
{
    return color(128, 000, 000, float_to_dec(fAlpha));
}

constexpr color color::navy(float fAlpha) noexcept
{
    return color(000, 000, 128, float_to_dec(fAlpha));
}

constexpr color color::olive(float fAlpha) noexcept
{
    return color(128, 128, 000, float_to_dec(fAlpha));
}

constexpr color color::purple(float fAlpha) noexcept
{
    return color(128, 000, 128, float_to_dec(fAlpha));
}

constexpr color color::red(float fAlpha) noexcept
{
    return color(255, 000, 000, float_to_dec(fAlpha));
}

constexpr color color::silver(float fAlpha) noexcept
{
    return color(192, 192, 192, float_to_dec(fAlpha));
}

constexpr color color::teal(float fAlpha) noexcept
{
    return color(000, 128, 128, float_to_dec(fAlpha));
}

constexpr color color::white(float fAlpha) noexcept
{
    return color(255, 255, 255, float_to_dec(fAlpha));
}

constexpr color color::yellow(float fAlpha) noexcept
{
    return color(255, 255, 000, float_to_dec(fAlpha));
}

constexpr color color::empty() noexcept
{
    return color(0, 0, 0, 0);
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
    assign_r_checked(other.x);
    assign_g_checked(other.y);
    assign_b_checked(other.z);
    assign_a_checked(other.w);
}

constexpr void color::assign_r_checked(float fValue) noexcept
{
    m_Color.x = clamp_value(fValue);
}

constexpr void color::assign_g_checked(float fValue) noexcept
{
    m_Color.y = clamp_value(fValue);
}

constexpr void color::assign_b_checked(float fValue) noexcept
{
    m_Color.z = clamp_value(fValue);
}

constexpr void color::assign_a_checked(float fValue) noexcept
{
    m_Color.w = clamp_value(fValue);
}

} // namespace qx
