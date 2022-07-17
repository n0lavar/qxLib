/**

    @file      color.h
    @brief     Contains qx::color class
    @author    Khrapov
    @date      2.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/suppress_warnings.h>
#include <qx/useful_macros.h>

#include <algorithm>

QX_PUSH_SUPPRESS_ALL_WARNINGS
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
QX_POP_SUPPRESS_WARNINGS

namespace qx
{

/**

    @class   color
    @brief   RGBA color
    @details ~
    @author  Khrapov
    @date    10.04.2021

**/
class color
{
public:
    QX_COPYMOVABLE(color);

    /**
        @brief color object constructor
    **/
    constexpr color() noexcept = default;

    /**
        @brief   color object constructor
        @details out of bound values will be clamped
        @param   fRed   - red component   [0.f, 1.f]
        @param   fGreen - green component [0.f, 1.f]
        @param   fBlue  - blue component  [0.f, 1.f]
        @param   fAlpha - alpha component [0.f, 1.f]
    **/
    constexpr color(
        float fRed,
        float fGreen,
        float fBlue,
        float fAlpha = 1.f) noexcept;

    /**
        @brief   color object constructor
        @details out of bound values will be clamped
        @param   nRed   - red component   [0, 255]
        @param   nGreen - green component [0, 255]
        @param   nBlue  - blue component  [0, 255]
        @param   nAlpha - alpha component [0, 255]
    **/
    constexpr color(int nRed, int nGreen, int nBlue, int nAlpha = 255) noexcept;

    /**
        @brief color object constructor
        @param nHexValue - hex color value in 0xRRGGBBAA format
    **/
    constexpr explicit color(unsigned int nHexValue) noexcept;

    /**
        @brief color object constructor
        @param vec3 - int vector
    **/
    constexpr explicit color(const glm::ivec3& vec3) noexcept;

    /**
        @brief color object constructor
        @param vec4 - int vector
    **/
    constexpr explicit color(const glm::ivec4& vec4) noexcept;

    /**
        @brief  Get red component
        @retval - red component
    **/
    constexpr float r() const noexcept;

    /**
        @brief  Get green component
        @retval - green component
    **/
    constexpr float g() const noexcept;

    /**
        @brief  Get blue component
        @retval - blue component
    **/
    constexpr float b() const noexcept;

    /**
        @brief  Get alpha component
        @retval - alpha component
    **/
    constexpr float a() const noexcept;

    /**
        @brief  Get color component
        @param  i - component number [0, 3]
        @retval   - component value
    **/
    constexpr float& operator[](size_t i) noexcept;

    /**
        @brief  Get color component
        @param  i - component number [0, 3]
        @retval   - component value
    **/
    constexpr const float& operator[](size_t i) const noexcept;

    /**
        @brief  Get red component as decimal 
        @retval - red component as decimal
    **/
    constexpr int r_dec() const noexcept;

    /**
        @brief  Get green component as decimal 
        @retval - green component as decimal
    **/
    constexpr int g_dec() const noexcept;

    /**
        @brief  Get blue component as decimal 
        @retval - blue component as decimal
    **/
    constexpr int b_dec() const noexcept;

    /**
        @brief  Get alpha component as decimal 
        @retval - alpha component as decimal
    **/
    constexpr int a_dec() const noexcept;

    /**
        @brief  Get pointer to the first component
        @retval - pointer to the first component
    **/
    constexpr const float* data() const noexcept;

    /**
        @brief  Get color as hex
        @retval - hex color value in 0xRRGGBBAA format
    **/
    constexpr unsigned int hex() const noexcept;

    /**
        @brief  operator==
        @param  other - other color
        @retval       - true, if objects are equal
    **/
    constexpr bool operator==(const color& other) const noexcept;

    /**
        @brief  operator glm::vec3
        @retval - color as vec3
    **/
    constexpr operator glm::vec3() const noexcept;

    /**
        @brief  operator glm::vec4
        @retval - color as vec4
    **/
    constexpr operator glm::vec4() const noexcept;

    /**
        @brief   Add value to red component
        @details if the new value goes out of range, it will be clamped
        @param   fDeltaValue - delta value
    **/
    constexpr void update_r(float fDeltaValue) noexcept;

    /**
        @brief   Add value to green component
        @details if the new value goes out of range, it will be clamped
        @param   fDeltaValue - delta value
    **/
    constexpr void update_g(float fDeltaValue) noexcept;

    /**
        @brief   Add value to blue component
        @details if the new value goes out of range, it will be clamped
        @param   fDeltaValue - delta value
    **/
    constexpr void update_b(float fDeltaValue) noexcept;

    /**
        @brief   Add value to alpha component
        @details if the new value goes out of range, it will be clamped
        @param   fDeltaValue - delta value
    **/
    constexpr void update_a(float fDeltaValue) noexcept;

    /**
        @brief   Add value to red component
        @details if the new value goes out of range, it will be clamped
        @param   nDeltaValue - delta value
    **/
    constexpr void update_r_dec(int nDeltaValue) noexcept;

    /**
        @brief   Add value to green component
        @details if the new value goes out of range, it will be clamped
        @param   nDeltaValue - delta value
    **/
    constexpr void update_g_dec(int nDeltaValue) noexcept;

    /**
        @brief   Add value to blue component
        @details if the new value goes out of range, it will be clamped
        @param   nDeltaValue - delta value
    **/
    constexpr void update_b_dec(int nDeltaValue) noexcept;

    /**
        @brief   Add value to alpha component
        @details if the new value goes out of range, it will be clamped
        @param   nDeltaValue - delta value
    **/
    constexpr void update_a_dec(int nDeltaValue) noexcept;

    /**
        @brief   Set new value of red component
        @details if the new value goes out of range, it will be clamped
        @param   fValue - new value of component
    **/
    constexpr void set_r(float fValue) noexcept;

    /**
        @brief   Set new value of green component
        @details if the new value goes out of range, it will be clamped
        @param   fValue - new value of component
    **/
    constexpr void set_g(float fValue) noexcept;

    /**
        @brief   Set new value of blue component
        @details if the new value goes out of range, it will be clamped
        @param   fValue - new value of component
    **/
    constexpr void set_b(float fValue) noexcept;

    /**
        @brief   Set new value of alpha component
        @details if the new value goes out of range, it will be clamped
        @param   fValue - new value of component
    **/
    constexpr void set_a(float fValue) noexcept;

    /**
        @brief   Set new value of red component
        @details if the new value goes out of range, it will be clamped
        @param   nValue - new value of component
    **/
    constexpr void set_r_dec(int nValue) noexcept;

    /**
        @brief   Set new value of green component
        @details if the new value goes out of range, it will be clamped
        @param   nValue - new value of component
    **/
    constexpr void set_g_dec(int nValue) noexcept;

    /**
        @brief   Set new value of blue component
        @details if the new value goes out of range, it will be clamped
        @param   nValue - new value of component
    **/
    constexpr void set_b_dec(int nValue) noexcept;

    /**
        @brief   Set new value of alpha component
        @details if the new value goes out of range, it will be clamped
        @param   nValue - new value of component
    **/
    constexpr void set_a_dec(int nValue) noexcept;

    /**
        @brief Make color darker 
        @param fPercent - dark factor
    **/
    constexpr void darken(float fPercent) noexcept;

    /**
        @brief Make color brighter
        @param fPercent - brighter factor
    **/
    constexpr void brighten(float fPercent) noexcept;

    /**
        @brief  Make darker color
        @param  other    - original color
        @param  fPercent - dark factor
        @retval          - darker color
    **/
    constexpr static color darken(const color& other, float fPercent) noexcept;

    /**
        @brief  Make brighter color
        @param  other    - original color
        @param  fPercent - brighter factor
        @retval          - brighter color
    **/
    constexpr static color brighten(
        const color& other,
        float        fPercent) noexcept;

    /**
        @brief  Get aqua color
        @retval - aqua color
    **/
    static constexpr color aqua(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get black color
        @param  fAlpha - alpha component
        @retval        - black color
    **/
    static constexpr color black(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get blue color
        @param  fAlpha - alpha component
        @retval        - blue color
    **/
    static constexpr color blue(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get fuchsia color
        @param  fAlpha - alpha component
        @retval        - fuchsia color
    **/
    static constexpr color fuchsia(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get gray color
        @param  fAlpha - alpha component
        @retval        - gray color
    **/
    static constexpr color gray(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get green color
        @param  fAlpha - alpha component
        @retval        - green color
    **/
    static constexpr color green(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get lime color
        @param  fAlpha - alpha component
        @retval        - lime color
    **/
    static constexpr color lime(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get maroon color
        @param  fAlpha - alpha component
        @retval        - maroon color
    **/
    static constexpr color maroon(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get navy color
        @param  fAlpha - alpha component
        @retval        - navy color
    **/
    static constexpr color navy(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get olive color
        @param  fAlpha - alpha component
        @retval        - olive color
    **/
    static constexpr color olive(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get purple color
        @param  fAlpha - alpha component
        @retval        - purple color
    **/
    static constexpr color purple(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get red color
        @param  fAlpha - alpha component
        @retval        - red color
    **/
    static constexpr color red(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get silver color
        @param  fAlpha - alpha component
        @retval        - silver color
    **/
    static constexpr color silver(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get teal color
        @param  fAlpha - alpha component
        @retval        - teal color
    **/
    static constexpr color teal(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get white color
        @param  fAlpha - alpha component
        @retval        - white color
    **/
    static constexpr color white(float fAlpha = 1.f) noexcept;

    /**
        @brief  Get yellow color
        @param  fAlpha - alpha component
        @retval        - yellow color
    **/
    static constexpr color yellow(float fAlpha = 1.f) noexcept;

    /**
        @brief   Get empty color (0, 0, 0, 0)
        @details - empty color can be useful for out of border values
                   as they won't affect calc result
        @retval  - empty color
    **/
    static constexpr color empty() noexcept;

    /**
        @brief  Get number of float components
        @retval  - number of float components
    **/
    static constexpr size_t size() noexcept;

private:
    /**
        @brief  Clamp a value to a valid range
        @param  fValue - input value
        @retval        - clamped value [0.f, 1.f]
    **/
    static constexpr float clamp_value(float fValue) noexcept;

    /**
        @brief  Convert decimal value to float
        @param  nValue - decimal value   [0, 255]
        @retval        - float value     [0.f, 1.f]
    **/
    static constexpr float dec_to_float(int nValue) noexcept;

    /**
        @brief  Convert float value to decimal
        @param  fValue - float value     [0.f, 1.f]
        @retval        - decimal value   [0, 255]
    **/
    static constexpr int float_to_dec(float fValue) noexcept;

    /**
        @brief Clamp all vector components and assign
        @param other - color vector
    **/
    constexpr void assign_checked(const glm::vec4& other) noexcept;

    /**
        @brief Clamp component and assign
        @param pComponent - component field
        @param fValue     - new component value
    **/
    static constexpr void assign_component_checked(
        float& pComponent,
        float  fValue) noexcept;

private:
    glm::vec4 m_Color = glm::vec4(1.f);
};

} // namespace qx

#include <qx/render/color.inl>
