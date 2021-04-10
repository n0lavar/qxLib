//==============================================================================
//
//!\file                           color.inl
//
//!\brief       Contains qx::color class
//!\details     ~
//
//!\author      Khrapov
//!\date        10.04.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                          qx::color::color
//
//!\brief   color object constructor
//!\details out of bound values will be clamped
//!\param   fRed   - red component   [0.f, 1.f]
//!\param   fGreen - green component [0.f, 1.f]
//!\param   fBlue  - blue component  [0.f, 1.f]
//!\param   fAlpha - alpha component [0.f, 1.f]
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr color::color(
    float fRed,
    float fGreen,
    float fBlue,
    float fAlpha) noexcept
{
    assign_checked({ fRed, fGreen, fBlue, fAlpha });
}

//==============================================================================
//!\fn                          qx::color::color
//
//!\brief   color object constructor
//!\details out of bound values will be clamped
//!\param   nRed   - red component   [0, 255]
//!\param   nGreen - green component [0, 255]
//!\param   nBlue  - blue component  [0, 255]
//!\param   nAlpha - alpha component [0, 255]
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr color::color(
    int nRed,
    int nGreen,
    int nBlue,
    int nAlpha) noexcept
    : color(
          dec_to_float(nRed),
          dec_to_float(nGreen),
          dec_to_float(nBlue),
          dec_to_float(nAlpha))
{
}

//==============================================================================
//!\fn                            qx::color::r
//
//!\brief  Get red component
//!\retval  - red component
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr float color::r(void) const noexcept
{
    return m_Color.x;
}

//==============================================================================
//!\fn                            qx::color::g
//
//!\brief  Get green component
//!\retval  - green component
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr float color::g(void) const noexcept
{
    return m_Color.y;
}

//==============================================================================
//!\fn                            qx::color::b
//
//!\brief  Get blue component
//!\retval  - blue component
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr float color::b(void) const noexcept
{
    return m_Color.z;
}

//==============================================================================
//!\fn                            qx::color::a
//
//!\brief  Get alpha component
//!\retval  - alpha component
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr float color::a(void) const noexcept
{
    return m_Color.w;
}

//==============================================================================
//!\fn                          qx::color::data
//
//!\brief  Get pointer to the first component
//!\retval  - pointer to the first component
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr const float* color::data(void) const noexcept
{
    return &(m_Color.x);
}

//==============================================================================
//!\fn                       qx::color::operator==
//
//!\param  other - other color
//!\retval       - true if colors are equal
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr bool color::operator==(const color& other) const noexcept
{
    return m_Color == other.m_Color;
}

//==============================================================================
//!\fn                   qx::color::operator glm::vec3
//
//!\retval  - color as vec3
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr color::operator glm::vec3(void) const noexcept
{
    return m_Color;
}

//==============================================================================
//!\fn                   qx::color::operator glm::vec4
//
//!\retval  - color as vec4
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr color::operator glm::vec4(void) const noexcept
{
    return m_Color;
}

//==============================================================================
//!\fn                        qx::color::update_r
//
//!\brief   Add value to red component
//!\details if the new value goes out of range, it will be clamped
//!\param   fDeltaValue - delta value
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::update_r(float fDeltaValue) noexcept
{
    assign_r_checked(m_Color.x + fDeltaValue);
}

//==============================================================================
//!\fn                        qx::color::update_g
//
//!\brief   Add value to green component
//!\details if the new value goes out of range, it will be clamped
//!\param   fDeltaValue - delta value
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::update_g(float fDeltaValue) noexcept
{
    assign_g_checked(m_Color.y + fDeltaValue);
}

//==============================================================================
//!\fn                        qx::color::update_b
//
//!\brief   Add value to blue component
//!\details if the new value goes out of range, it will be clamped
//!\param   fDeltaValue - delta value
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::update_b(float fDeltaValue) noexcept
{
    assign_b_checked(m_Color.z + fDeltaValue);
}

//==============================================================================
//!\fn                        qx::color::update_a
//
//!\brief   Add value to alpha component
//!\details if the new value goes out of range, it will be clamped
//!\param   fDeltaValue - delta value
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::update_a(float fDeltaValue) noexcept
{
    assign_a_checked(m_Color.w + fDeltaValue);
}

//==============================================================================
//!\fn                      qx::color::update_r_dec
//
//!\brief   Add decimal value to red component
//!\details if the new value goes out of range, it will be clamped
//!\param   nDeltaValue - delta value
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::update_r_dec(int nDeltaValue) noexcept
{
    assign_r_checked(m_Color.x + dec_to_float(nDeltaValue));
}

//==============================================================================
//!\fn                      qx::color::update_g_dec
//
//!\brief   Add decimal value to green component
//!\details if the new value goes out of range, it will be clamped
//!\param   nDeltaValue - delta value
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::update_g_dec(int nDeltaValue) noexcept
{
    assign_g_checked(m_Color.y + dec_to_float(nDeltaValue));
}

//==============================================================================
//!\fn                      qx::color::update_b_dec
//
//!\brief   Add decimal value to blue component
//!\details if the new value goes out of range, it will be clamped
//!\param   nDeltaValue - delta value
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::update_b_dec(int nDeltaValue) noexcept
{
    assign_b_checked(m_Color.z + dec_to_float(nDeltaValue));
}

//==============================================================================
//!\fn                      qx::color::update_a_dec
//
//!\brief   Add decimal value to alpha component
//!\details if the new value goes out of range, it will be clamped
//!\param   nDeltaValue - delta value
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::update_a_dec(int nDeltaValue) noexcept
{
    assign_a_checked(m_Color.w + dec_to_float(nDeltaValue));
}

//==============================================================================
//!\fn                          qx::color::set_r
//
//!\brief   Set new value of red component
//!\details if the new value goes out of range, it will be clamped
//!\param   fValue - new value of red component
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::set_r(float fValue) noexcept
{
    assign_r_checked(fValue);
}

//==============================================================================
//!\fn                          qx::color::set_g
//
//!\brief   Set new value of green component
//!\details if the new value goes out of range, it will be clamped
//!\param   fValue - new value of red component
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::set_g(float fValue) noexcept
{
    assign_g_checked(fValue);
}

//==============================================================================
//!\fn                          qx::color::set_b
//
//!\brief   Set new value of blue component
//!\details if the new value goes out of range, it will be clamped
//!\param   fValue - new value of red component
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::set_b(float fValue) noexcept
{
    assign_b_checked(fValue);
}

//==============================================================================
//!\fn                          qx::color::set_a
//
//!\brief   Set new value of alpha component
//!\details if the new value goes out of range, it will be clamped
//!\param   fValue - new value of red component
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::set_a(float fValue) noexcept
{
    assign_a_checked(fValue);
}

//==============================================================================
//!\fn                        qx::color::set_r_dec
//
//!\brief   Set new value of red component as decimal
//!\details if the new value goes out of range, it will be clamped
//!\param   nValue - new value of red component as decimal
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::set_r_dec(int nValue) noexcept
{
    assign_r_checked(dec_to_float(nValue));
}

//==============================================================================
//!\fn                        qx::color::set_g_dec
//
//!\brief   Set new value of green component as decimal
//!\details if the new value goes out of range, it will be clamped
//!\param   nValue - new value of red component as decimal
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::set_g_dec(int nValue) noexcept
{
    assign_g_checked(dec_to_float(nValue));
}

//==============================================================================
//!\fn                        qx::color::set_b_dec
//
//!\brief   Set new value of blue component as decimal
//!\details if the new value goes out of range, it will be clamped
//!\param   nValue - new value of red component as decimal
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::set_b_dec(int nValue) noexcept
{
    assign_b_checked(dec_to_float(nValue));
}

//==============================================================================
//!\fn                        qx::color::set_a_dec
//
//!\brief   Set new value of alpha component as decimal
//!\details if the new value goes out of range, it will be clamped
//!\param   nValue - new value of red component as decimal
//!\author  Khrapov
//!\date    10.04.2021
//==============================================================================
constexpr void color::set_a_dec(int nValue) noexcept
{
    assign_a_checked(dec_to_float(nValue));
}

//==============================================================================
//!\fn                       qx::color::clamp_value
//
//!\brief  Clamp a value to a valid range
//!\param  fValue - input value
//!\retval        - clamped value [0.f, 1.f]
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr float color::clamp_value(float fValue) noexcept
{
    return std::clamp(fValue, 0.f, 1.f);
}

//==============================================================================
//!\fn                      qx::color::dec_to_float
//
//!\brief  Convert decimal value to float
//!\param  nValue - decimal value   [0, 255]
//!\retval        - float value     [0.f, 1.f]
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr float color::dec_to_float(int nValue) noexcept
{
    return nValue / 255.f;
}

//==============================================================================
//!\fn                     qx::color::assign_checked
//
//!\brief  Clamp all vector components and assign
//!\param  other - color vector
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr void color::assign_checked(const glm::vec4& other) noexcept
{
    assign_r_checked(other.x);
    assign_g_checked(other.y);
    assign_b_checked(other.z);
    assign_a_checked(other.w);
}

//==============================================================================
//!\fn                    qx::color::assign_r_checked
//
//!\brief  Clamp red component and assign
//!\param  fValue - component value
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr void color::assign_r_checked(float fValue) noexcept
{
    m_Color.x = clamp_value(fValue);
}

//==============================================================================
//!\fn                    qx::color::assign_g_checked
//
//!\brief  Clamp green component and assign
//!\param  fValue - component value
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr void color::assign_g_checked(float fValue) noexcept
{
    m_Color.y = clamp_value(fValue);
}

//==============================================================================
//!\fn                    qx::color::assign_b_checked
//
//!\brief  Clamp blue component and assign
//!\param  fValue - component value
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr void color::assign_b_checked(float fValue) noexcept
{
    m_Color.z = clamp_value(fValue);
}

//==============================================================================
//!\fn                    qx::color::assign_a_checked
//
//!\brief  Clamp alpha component and assign
//!\param  fValue - component value
//!\author Khrapov
//!\date   10.04.2021
//==============================================================================
constexpr void color::assign_a_checked(float fValue) noexcept
{
    m_Color.w = clamp_value(fValue);
}

}
