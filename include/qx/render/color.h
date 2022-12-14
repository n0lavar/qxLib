/**

    @file      color.h
    @brief     Contains qx::color class
    @author    Khrapov
    @date      2.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/copyable_movable.h>
#include <qx/macros/suppress_warnings.h>

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
    constexpr color(float fRed, float fGreen, float fBlue, float fAlpha = 1.f) noexcept;

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
    constexpr static color brighten(const color& other, float fPercent) noexcept;

    /// Color functions
    /// @see https://www.cssportal.com/html-colors/x11-colors.php

    // clang-format off
    static constexpr auto alice_blue             (float fAlpha = 1.f) noexcept { return color(240, 248, 255, float_to_dec(fAlpha)); }
    static constexpr auto antique_white          (float fAlpha = 1.f) noexcept { return color(250, 235, 215, float_to_dec(fAlpha)); }
    static constexpr auto aqua                   (float fAlpha = 1.f) noexcept { return color(0, 255, 255, float_to_dec(fAlpha)); }
    static constexpr auto aquamarine             (float fAlpha = 1.f) noexcept { return color(127, 255, 212, float_to_dec(fAlpha)); }
    static constexpr auto azure                  (float fAlpha = 1.f) noexcept { return color(240, 255, 255, float_to_dec(fAlpha)); }
    static constexpr auto beige                  (float fAlpha = 1.f) noexcept { return color(245, 245, 220, float_to_dec(fAlpha)); }
    static constexpr auto bisque                 (float fAlpha = 1.f) noexcept { return color(255, 228, 196, float_to_dec(fAlpha)); }
    static constexpr auto black                  (float fAlpha = 1.f) noexcept { return color(0, 0, 0, float_to_dec(fAlpha)); }
    static constexpr auto blanched_almond        (float fAlpha = 1.f) noexcept { return color(255, 235, 205, float_to_dec(fAlpha)); }
    static constexpr auto blue                   (float fAlpha = 1.f) noexcept { return color(0, 0, 255, float_to_dec(fAlpha)); }
    static constexpr auto blue_violet            (float fAlpha = 1.f) noexcept { return color(138, 43, 226, float_to_dec(fAlpha)); }
    static constexpr auto brown                  (float fAlpha = 1.f) noexcept { return color(165, 42, 42, float_to_dec(fAlpha)); }
    static constexpr auto burly_wood             (float fAlpha = 1.f) noexcept { return color(222, 184, 135, float_to_dec(fAlpha)); }
    static constexpr auto cadet_blue             (float fAlpha = 1.f) noexcept { return color(95, 158, 160, float_to_dec(fAlpha)); }
    static constexpr auto chartreuse             (float fAlpha = 1.f) noexcept { return color(127, 255, 0, float_to_dec(fAlpha)); }
    static constexpr auto chocolate              (float fAlpha = 1.f) noexcept { return color(210, 105, 30, float_to_dec(fAlpha)); }
    static constexpr auto coral                  (float fAlpha = 1.f) noexcept { return color(255, 127, 80, float_to_dec(fAlpha)); }
    static constexpr auto cornflower_blue        (float fAlpha = 1.f) noexcept { return color(100, 149, 237, float_to_dec(fAlpha)); }
    static constexpr auto cornsilk               (float fAlpha = 1.f) noexcept { return color(255, 248, 220, float_to_dec(fAlpha)); }
    static constexpr auto crimson                (float fAlpha = 1.f) noexcept { return color(220, 20, 60, float_to_dec(fAlpha)); }
    static constexpr auto cyan                   (float fAlpha = 1.f) noexcept { return color(0, 255, 255, float_to_dec(fAlpha)); }
    static constexpr auto dark_blue              (float fAlpha = 1.f) noexcept { return color(0, 0, 139, float_to_dec(fAlpha)); }
    static constexpr auto dark_cyan              (float fAlpha = 1.f) noexcept { return color(0, 139, 139, float_to_dec(fAlpha)); }
    static constexpr auto dark_goldenrod         (float fAlpha = 1.f) noexcept { return color(184, 134, 11, float_to_dec(fAlpha)); }
    static constexpr auto dark_gray              (float fAlpha = 1.f) noexcept { return color(169, 169, 169, float_to_dec(fAlpha)); }
    static constexpr auto dark_green             (float fAlpha = 1.f) noexcept { return color(0, 100, 0, float_to_dec(fAlpha)); }
    static constexpr auto dark_khaki             (float fAlpha = 1.f) noexcept { return color(189, 183, 107, float_to_dec(fAlpha)); }
    static constexpr auto dark_magenta           (float fAlpha = 1.f) noexcept { return color(139, 0, 139, float_to_dec(fAlpha)); }
    static constexpr auto dark_olive_green       (float fAlpha = 1.f) noexcept { return color(85, 107, 47, float_to_dec(fAlpha)); }
    static constexpr auto dark_orange            (float fAlpha = 1.f) noexcept { return color(255, 140, 0, float_to_dec(fAlpha)); }
    static constexpr auto dark_orchid            (float fAlpha = 1.f) noexcept { return color(153, 50, 204, float_to_dec(fAlpha)); }
    static constexpr auto dark_red               (float fAlpha = 1.f) noexcept { return color(139, 0, 0, float_to_dec(fAlpha)); }
    static constexpr auto dark_salmon            (float fAlpha = 1.f) noexcept { return color(233, 150, 122, float_to_dec(fAlpha)); }
    static constexpr auto dark_sea_green         (float fAlpha = 1.f) noexcept { return color(143, 188, 143, float_to_dec(fAlpha)); }
    static constexpr auto dark_slate_blue        (float fAlpha = 1.f) noexcept { return color(72, 61, 139, float_to_dec(fAlpha)); }
    static constexpr auto dark_slate_gray        (float fAlpha = 1.f) noexcept { return color(47, 79, 79, float_to_dec(fAlpha)); }
    static constexpr auto dark_turquoise         (float fAlpha = 1.f) noexcept { return color(0, 206, 209, float_to_dec(fAlpha)); }
    static constexpr auto dark_violet            (float fAlpha = 1.f) noexcept { return color(148, 0, 211, float_to_dec(fAlpha)); }
    static constexpr auto deep_pink              (float fAlpha = 1.f) noexcept { return color(255, 20, 147, float_to_dec(fAlpha)); }
    static constexpr auto deep_sky_blue          (float fAlpha = 1.f) noexcept { return color(0, 191, 255, float_to_dec(fAlpha)); }
    static constexpr auto dim_gray               (float fAlpha = 1.f) noexcept { return color(105, 105, 105, float_to_dec(fAlpha)); }
    static constexpr auto dodger_blue            (float fAlpha = 1.f) noexcept { return color(30, 144, 255, float_to_dec(fAlpha)); }
    static constexpr auto fire_brick             (float fAlpha = 1.f) noexcept { return color(178, 34, 34, float_to_dec(fAlpha)); }
    static constexpr auto floral_white           (float fAlpha = 1.f) noexcept { return color(255, 250, 240, float_to_dec(fAlpha)); }
    static constexpr auto forest_green           (float fAlpha = 1.f) noexcept { return color(34, 139, 34, float_to_dec(fAlpha)); }
    static constexpr auto fuchsia                (float fAlpha = 1.f) noexcept { return color(255, 0, 255, float_to_dec(fAlpha)); }
    static constexpr auto gainsboro              (float fAlpha = 1.f) noexcept { return color(220, 220, 220, float_to_dec(fAlpha)); }
    static constexpr auto ghost_white            (float fAlpha = 1.f) noexcept { return color(248, 248, 255, float_to_dec(fAlpha)); }
    static constexpr auto gold                   (float fAlpha = 1.f) noexcept { return color(255, 215, 0, float_to_dec(fAlpha)); }
    static constexpr auto goldenrod              (float fAlpha = 1.f) noexcept { return color(218, 165, 32, float_to_dec(fAlpha)); }
    static constexpr auto gray                   (float fAlpha = 1.f) noexcept { return color(128, 128, 128, float_to_dec(fAlpha)); }
    static constexpr auto green                  (float fAlpha = 1.f) noexcept { return color(0, 128, 0, float_to_dec(fAlpha)); }
    static constexpr auto green_yellow           (float fAlpha = 1.f) noexcept { return color(173, 255, 47, float_to_dec(fAlpha)); }
    static constexpr auto honeydew               (float fAlpha = 1.f) noexcept { return color(240, 255, 240, float_to_dec(fAlpha)); }
    static constexpr auto hot_pink               (float fAlpha = 1.f) noexcept { return color(255, 105, 180, float_to_dec(fAlpha)); }
    static constexpr auto indian_red             (float fAlpha = 1.f) noexcept { return color(205, 92, 92, float_to_dec(fAlpha)); }
    static constexpr auto indigo                 (float fAlpha = 1.f) noexcept { return color(75, 0, 130, float_to_dec(fAlpha)); }
    static constexpr auto ivory                  (float fAlpha = 1.f) noexcept { return color(255, 255, 240, float_to_dec(fAlpha)); }
    static constexpr auto khaki                  (float fAlpha = 1.f) noexcept { return color(240, 230, 140, float_to_dec(fAlpha)); }
    static constexpr auto lavender               (float fAlpha = 1.f) noexcept { return color(230, 230, 250, float_to_dec(fAlpha)); }
    static constexpr auto lavender_blush         (float fAlpha = 1.f) noexcept { return color(255, 240, 245, float_to_dec(fAlpha)); }
    static constexpr auto lawn_green             (float fAlpha = 1.f) noexcept { return color(124, 252, 0, float_to_dec(fAlpha)); }
    static constexpr auto lemon_chiffon          (float fAlpha = 1.f) noexcept { return color(255, 250, 205, float_to_dec(fAlpha)); }
    static constexpr auto light_blue             (float fAlpha = 1.f) noexcept { return color(173, 216, 230, float_to_dec(fAlpha)); }
    static constexpr auto light_coral            (float fAlpha = 1.f) noexcept { return color(240, 128, 128, float_to_dec(fAlpha)); }
    static constexpr auto light_cyan             (float fAlpha = 1.f) noexcept { return color(224, 255, 255, float_to_dec(fAlpha)); }
    static constexpr auto light_goldenrod_yellow (float fAlpha = 1.f) noexcept { return color(250, 250, 210, float_to_dec(fAlpha)); }
    static constexpr auto light_green            (float fAlpha = 1.f) noexcept { return color(144, 238, 144, float_to_dec(fAlpha)); }
    static constexpr auto light_grey             (float fAlpha = 1.f) noexcept { return color(211, 211, 211, float_to_dec(fAlpha)); }
    static constexpr auto light_pink             (float fAlpha = 1.f) noexcept { return color(255, 182, 193, float_to_dec(fAlpha)); }
    static constexpr auto light_salmon           (float fAlpha = 1.f) noexcept { return color(255, 160, 122, float_to_dec(fAlpha)); }
    static constexpr auto light_sea_green        (float fAlpha = 1.f) noexcept { return color(32, 178, 170, float_to_dec(fAlpha)); }
    static constexpr auto light_sky_blue         (float fAlpha = 1.f) noexcept { return color(135, 206, 250, float_to_dec(fAlpha)); }
    static constexpr auto light_slate_gray       (float fAlpha = 1.f) noexcept { return color(119, 136, 153, float_to_dec(fAlpha)); }
    static constexpr auto light_steel_blue       (float fAlpha = 1.f) noexcept { return color(176, 196, 222, float_to_dec(fAlpha)); }
    static constexpr auto light_yellow           (float fAlpha = 1.f) noexcept { return color(255, 255, 224, float_to_dec(fAlpha)); }
    static constexpr auto lime                   (float fAlpha = 1.f) noexcept { return color(0, 255, 0, float_to_dec(fAlpha)); }
    static constexpr auto lime_green             (float fAlpha = 1.f) noexcept { return color(50, 205, 50, float_to_dec(fAlpha)); }
    static constexpr auto linen                  (float fAlpha = 1.f) noexcept { return color(250, 240, 230, float_to_dec(fAlpha)); }
    static constexpr auto magenta                (float fAlpha = 1.f) noexcept { return color(255, 0, 255, float_to_dec(fAlpha)); }
    static constexpr auto maroon                 (float fAlpha = 1.f) noexcept { return color(128, 0, 0, float_to_dec(fAlpha)); }
    static constexpr auto medium_aquamarine      (float fAlpha = 1.f) noexcept { return color(102, 205, 170, float_to_dec(fAlpha)); }
    static constexpr auto medium_blue            (float fAlpha = 1.f) noexcept { return color(0, 0, 205, float_to_dec(fAlpha)); }
    static constexpr auto medium_orchid          (float fAlpha = 1.f) noexcept { return color(186, 85, 211, float_to_dec(fAlpha)); }
    static constexpr auto medium_purple          (float fAlpha = 1.f) noexcept { return color(147, 112, 219, float_to_dec(fAlpha)); }
    static constexpr auto medium_sea_green       (float fAlpha = 1.f) noexcept { return color(60, 179, 113, float_to_dec(fAlpha)); }
    static constexpr auto medium_slate_blue      (float fAlpha = 1.f) noexcept { return color(123, 104, 238, float_to_dec(fAlpha)); }
    static constexpr auto medium_spring_green    (float fAlpha = 1.f) noexcept { return color(0, 250, 154, float_to_dec(fAlpha)); }
    static constexpr auto medium_turquoise       (float fAlpha = 1.f) noexcept { return color(72, 209, 204, float_to_dec(fAlpha)); }
    static constexpr auto medium_violet_red      (float fAlpha = 1.f) noexcept { return color(199, 21, 133, float_to_dec(fAlpha)); }
    static constexpr auto midnight_blue          (float fAlpha = 1.f) noexcept { return color(25, 25, 112, float_to_dec(fAlpha)); }
    static constexpr auto mint_cream             (float fAlpha = 1.f) noexcept { return color(245, 255, 250, float_to_dec(fAlpha)); }
    static constexpr auto misty_rose             (float fAlpha = 1.f) noexcept { return color(255, 228, 225, float_to_dec(fAlpha)); }
    static constexpr auto moccasin               (float fAlpha = 1.f) noexcept { return color(255, 228, 181, float_to_dec(fAlpha)); }
    static constexpr auto navajo_white           (float fAlpha = 1.f) noexcept { return color(255, 222, 173, float_to_dec(fAlpha)); }
    static constexpr auto navy                   (float fAlpha = 1.f) noexcept { return color(0, 0, 128, float_to_dec(fAlpha)); }
    static constexpr auto old_lace               (float fAlpha = 1.f) noexcept { return color(253, 245, 230, float_to_dec(fAlpha)); }
    static constexpr auto olive                  (float fAlpha = 1.f) noexcept { return color(128, 128, 0, float_to_dec(fAlpha)); }
    static constexpr auto olive_drab             (float fAlpha = 1.f) noexcept { return color(107, 142, 35, float_to_dec(fAlpha)); }
    static constexpr auto orange                 (float fAlpha = 1.f) noexcept { return color(255, 165, 0, float_to_dec(fAlpha)); }
    static constexpr auto orange_red             (float fAlpha = 1.f) noexcept { return color(255, 69, 0, float_to_dec(fAlpha)); }
    static constexpr auto orchid                 (float fAlpha = 1.f) noexcept { return color(218, 112, 214, float_to_dec(fAlpha)); }
    static constexpr auto pale_goldenrod         (float fAlpha = 1.f) noexcept { return color(238, 232, 170, float_to_dec(fAlpha)); }
    static constexpr auto pale_green             (float fAlpha = 1.f) noexcept { return color(152, 251, 152, float_to_dec(fAlpha)); }
    static constexpr auto pale_turquoise         (float fAlpha = 1.f) noexcept { return color(175, 238, 238, float_to_dec(fAlpha)); }
    static constexpr auto pale_violet_red        (float fAlpha = 1.f) noexcept { return color(219, 112, 147, float_to_dec(fAlpha)); }
    static constexpr auto papaya_whip            (float fAlpha = 1.f) noexcept { return color(255, 239, 213, float_to_dec(fAlpha)); }
    static constexpr auto peach_puff             (float fAlpha = 1.f) noexcept { return color(255, 218, 185, float_to_dec(fAlpha)); }
    static constexpr auto peru                   (float fAlpha = 1.f) noexcept { return color(205, 133, 63, float_to_dec(fAlpha)); }
    static constexpr auto pink                   (float fAlpha = 1.f) noexcept { return color(255, 192, 203, float_to_dec(fAlpha)); }
    static constexpr auto plum                   (float fAlpha = 1.f) noexcept { return color(221, 160, 221, float_to_dec(fAlpha)); }
    static constexpr auto powder_blue            (float fAlpha = 1.f) noexcept { return color(176, 224, 230, float_to_dec(fAlpha)); }
    static constexpr auto purple                 (float fAlpha = 1.f) noexcept { return color(128, 0, 128, float_to_dec(fAlpha)); }
    static constexpr auto red                    (float fAlpha = 1.f) noexcept { return color(255, 0, 0, float_to_dec(fAlpha)); }
    static constexpr auto rosy_brown             (float fAlpha = 1.f) noexcept { return color(188, 143, 143, float_to_dec(fAlpha)); }
    static constexpr auto royal_blue             (float fAlpha = 1.f) noexcept { return color(65, 105, 225, float_to_dec(fAlpha)); }
    static constexpr auto saddle_brown           (float fAlpha = 1.f) noexcept { return color(139, 69, 19, float_to_dec(fAlpha)); }
    static constexpr auto salmon                 (float fAlpha = 1.f) noexcept { return color(250, 128, 114, float_to_dec(fAlpha)); }
    static constexpr auto sandy_brown            (float fAlpha = 1.f) noexcept { return color(244, 164, 96, float_to_dec(fAlpha)); }
    static constexpr auto sea_green              (float fAlpha = 1.f) noexcept { return color(46, 139, 87, float_to_dec(fAlpha)); }
    static constexpr auto seashell               (float fAlpha = 1.f) noexcept { return color(255, 245, 238, float_to_dec(fAlpha)); }
    static constexpr auto sienna                 (float fAlpha = 1.f) noexcept { return color(160, 82, 45, float_to_dec(fAlpha)); }
    static constexpr auto silver                 (float fAlpha = 1.f) noexcept { return color(192, 192, 192, float_to_dec(fAlpha)); }
    static constexpr auto sky_blue               (float fAlpha = 1.f) noexcept { return color(135, 206, 235, float_to_dec(fAlpha)); }
    static constexpr auto slate_blue             (float fAlpha = 1.f) noexcept { return color(106, 90, 205, float_to_dec(fAlpha)); }
    static constexpr auto slate_gray             (float fAlpha = 1.f) noexcept { return color(112, 128, 144, float_to_dec(fAlpha)); }
    static constexpr auto snow                   (float fAlpha = 1.f) noexcept { return color(255, 250, 250, float_to_dec(fAlpha)); }
    static constexpr auto spring_green           (float fAlpha = 1.f) noexcept { return color(0, 255, 127, float_to_dec(fAlpha)); }
    static constexpr auto steel_blue             (float fAlpha = 1.f) noexcept { return color(70, 130, 180, float_to_dec(fAlpha)); }
    static constexpr auto tan                    (float fAlpha = 1.f) noexcept { return color(210, 180, 140, float_to_dec(fAlpha)); }
    static constexpr auto teal                   (float fAlpha = 1.f) noexcept { return color(0, 128, 128, float_to_dec(fAlpha)); }
    static constexpr auto thistle                (float fAlpha = 1.f) noexcept { return color(216, 191, 216, float_to_dec(fAlpha)); }
    static constexpr auto tomato                 (float fAlpha = 1.f) noexcept { return color(255, 99, 71, float_to_dec(fAlpha)); }
    static constexpr auto turquoise              (float fAlpha = 1.f) noexcept { return color(64, 224, 208, float_to_dec(fAlpha)); }
    static constexpr auto violet                 (float fAlpha = 1.f) noexcept { return color(238, 130, 238, float_to_dec(fAlpha)); }
    static constexpr auto wheat                  (float fAlpha = 1.f) noexcept { return color(245, 222, 179, float_to_dec(fAlpha)); }
    static constexpr auto white                  (float fAlpha = 1.f) noexcept { return color(255, 255, 255, float_to_dec(fAlpha)); }
    static constexpr auto white_smoke            (float fAlpha = 1.f) noexcept { return color(245, 245, 245, float_to_dec(fAlpha)); }
    static constexpr auto yellow                 (float fAlpha = 1.f) noexcept { return color(255, 255, 0, float_to_dec(fAlpha)); }
    static constexpr auto yellow_green           (float fAlpha = 1.f) noexcept { return color(154, 205, 50, float_to_dec(fAlpha)); }
    // clang-format on

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
    static constexpr void assign_component_checked(float& pComponent, float fValue) noexcept;

private:
    glm::vec4 m_Color = glm::vec4(1.f);
};

} // namespace qx

#include <qx/render/color.inl>
