#include "color.h"
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

constexpr float color::r(void) const noexcept
{
    return m_Color.x;
}

constexpr float color::g(void) const noexcept
{
    return m_Color.y;
}

constexpr float color::b(void) const noexcept
{
    return m_Color.z;
}

constexpr float color::a(void) const noexcept
{
    return m_Color.w;
}

constexpr const float* color::data(void) const noexcept
{
    return &(m_Color.x);
}

constexpr bool color::operator==(const color& other) const noexcept
{
    return m_Color == other.m_Color;
}

constexpr color::operator glm::vec3(void) const noexcept
{
    return m_Color;
}

constexpr color::operator glm::vec4(void) const noexcept
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

constexpr color color::aqua(void) noexcept
{
    return color(000, 255, 255);
}

constexpr color color::black(void) noexcept
{
    return color(000, 000, 000);
}

constexpr color color::blue(void) noexcept
{
    return color(000, 000, 255);
}

constexpr color color::fuchsia(void) noexcept
{
    return color(255, 000, 255);
}

constexpr color color::gray(void) noexcept
{
    return color(128, 128, 128);
}

constexpr color color::green(void) noexcept
{
    return color(000, 128, 000);
}

constexpr color color::lime(void) noexcept
{
    return color(000, 255, 000);
}

constexpr color color::maroon(void) noexcept
{
    return color(128, 000, 000);
}

constexpr color color::navy(void) noexcept
{
    return color(000, 000, 128);
}

constexpr color color::olive(void) noexcept
{
    return color(128, 128, 000);
}

constexpr color color::purple(void) noexcept
{
    return color(128, 000, 128);
}

constexpr color color::red(void) noexcept
{
    return color(255, 000, 000);
}

constexpr color color::silver(void) noexcept
{
    return color(192, 192, 192);
}

constexpr color color::teal(void) noexcept
{
    return color(000, 128, 128);
}

constexpr color color::white(void) noexcept
{
    return color(255, 255, 255);
}

constexpr color color::yellow(void) noexcept
{
    return color(255, 255, 000);
}

constexpr color color::empty(void) noexcept
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
