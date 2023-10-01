/**

    @file      color.h
    @author    Khrapov
    @date      2.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>
#include <qx/containers/string/string_view.h>
#include <qx/macros/copyable_movable.h>
#include <qx/macros/suppress_warnings.h>
#include <qx/patterns/singleton.h>

#include <algorithm>
#include <unordered_map>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
QX_POP_SUPPRESS_WARNINGS();

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
    constexpr explicit color(u64 nHexValue) noexcept;

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
        @retval - hex color value in 0xRRGGBB format
    **/
    constexpr unsigned int hex_rgb() const noexcept;

    /**
        @brief  Get color as hex
        @retval - hex color value in 0xRRGGBBAA format
    **/
    constexpr unsigned int hex_rgba() const noexcept;

    /**
        @brief  Get color as hex
        @retval  - hex color value in 0xAARRGGBB format
    **/
    constexpr unsigned int hex_argb() const noexcept;

    constexpr bool operator==(const color& other) const noexcept;
    constexpr      operator glm::vec3() const noexcept;
    constexpr      operator glm::vec4() const noexcept;

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

private:
    /**
        @brief  Add color for string -> color mapping
        @param  svColorName - color name
        @param  nRed        - red component
        @param  nGreen      - green component
        @param  nBlue       - blue component
        @retval             - always true
    **/
    static bool add_color_to_mapping(string_view svColorName, int nRed, int nGreen, int nBlue) noexcept;

#define _QX_DEFINE_COLOR(snakeCaseName, pascalCaseName, r, g, b)                                                     \
    static constexpr auto snakeCaseName(float fAlpha = 1.f) noexcept                                                 \
    {                                                                                                                \
        return color(r, g, b, float_to_dec(fAlpha));                                                                 \
    }                                                                                                                \
    inline static const volatile bool QX_LINE_NAME(_stub1) = add_color_to_mapping(QX_TEXT(#snakeCaseName), r, g, b); \
    inline static const volatile bool QX_LINE_NAME(_stub2) = add_color_to_mapping(QX_TEXT(#pascalCaseName), r, g, b)

public:
    /// Color functions
    /// @see https://www.cssportal.com/html-colors/x11-colors.php

    // clang-format off
    _QX_DEFINE_COLOR(alice_blue             , AliceBlue            , 240, 248, 255);
    _QX_DEFINE_COLOR(antique_white          , AntiqueWhite         , 250, 235, 215);
    _QX_DEFINE_COLOR(aqua                   , Aqua                 ,   0, 255, 255);
    _QX_DEFINE_COLOR(aquamarine             , Aquamarine           , 127, 255, 212);
    _QX_DEFINE_COLOR(azure                  , Azure                , 240, 255, 255);
    _QX_DEFINE_COLOR(beige                  , Beige                , 245, 245, 220);
    _QX_DEFINE_COLOR(bisque                 , Bisque               , 255, 228, 196);
    _QX_DEFINE_COLOR(black                  , Black                ,   0,   0,   0);
    _QX_DEFINE_COLOR(blanched_almond        , BlanchedAlmond       , 255, 235, 205);
    _QX_DEFINE_COLOR(blue                   , Blue                 ,   0,   0, 255);
    _QX_DEFINE_COLOR(blue_violet            , BlueViolet           , 138,  43, 226);
    _QX_DEFINE_COLOR(brown                  , Brown                , 165,  42,  42);
    _QX_DEFINE_COLOR(burly_wood             , BurlyWood            , 222, 184, 135);
    _QX_DEFINE_COLOR(cadet_blue             , CadetBlue            ,  95, 158, 160);
    _QX_DEFINE_COLOR(chartreuse             , Chartreuse           , 127, 255,   0);
    _QX_DEFINE_COLOR(chocolate              , Chocolate            , 210, 105,  30);
    _QX_DEFINE_COLOR(coral                  , Coral                , 255, 127,  80);
    _QX_DEFINE_COLOR(cornflower_blue        , CornflowerBlue       , 100, 149, 237);
    _QX_DEFINE_COLOR(cornsilk               , Cornsilk             , 255, 248, 220);
    _QX_DEFINE_COLOR(crimson                , Crimson              , 220,  20,  60);
    _QX_DEFINE_COLOR(cyan                   , Cyan                 ,   0, 255, 255);
    _QX_DEFINE_COLOR(dark_blue              , DarkBlue             ,   0,   0, 139);
    _QX_DEFINE_COLOR(dark_cyan              , DarkCyan             ,   0, 139, 139);
    _QX_DEFINE_COLOR(dark_goldenrod         , DarkGoldenrod        , 184, 134,  11);
    _QX_DEFINE_COLOR(dark_gray              , DarkGray             , 169, 169, 169);
    _QX_DEFINE_COLOR(dark_green             , DarkGreen            ,   0, 100,  0);
    _QX_DEFINE_COLOR(dark_khaki             , DarkKhaki            , 189, 183, 107);
    _QX_DEFINE_COLOR(dark_magenta           , DarkMagenta          , 139,   0, 139);
    _QX_DEFINE_COLOR(dark_olive_green       , DarkOliveGreen       ,  85, 107,  47);
    _QX_DEFINE_COLOR(dark_orange            , DarkOrange           , 255, 140,   0);
    _QX_DEFINE_COLOR(dark_orchid            , DarkOrchid           , 153,  50, 204);
    _QX_DEFINE_COLOR(dark_red               , DarkRed              , 139,   0,   0);
    _QX_DEFINE_COLOR(dark_salmon            , DarkSalmon           , 233, 150, 122);
    _QX_DEFINE_COLOR(dark_sea_green         , DarkSeaGreen         , 143, 188, 143);
    _QX_DEFINE_COLOR(dark_slate_blue        , DarkSlateBlue        ,  72,  61, 139);
    _QX_DEFINE_COLOR(dark_slate_gray        , DarkSlateGray        ,  47,  79,  79);
    _QX_DEFINE_COLOR(dark_turquoise         , DarkTurquoise        ,   0, 206, 209);
    _QX_DEFINE_COLOR(dark_violet            , DarkViolet           , 148,   0, 211);
    _QX_DEFINE_COLOR(deep_pink              , DeepPink             , 255,  20, 147);
    _QX_DEFINE_COLOR(deep_sky_blue          , DeepSkyBlue          ,   0, 191, 255);
    _QX_DEFINE_COLOR(dim_gray               , DimGray              , 105, 105, 105);
    _QX_DEFINE_COLOR(dodger_blue            , DodgerBlue           ,  30, 144, 255);
    _QX_DEFINE_COLOR(fire_brick             , FireBrick            , 178,  34,  34);
    _QX_DEFINE_COLOR(floral_white           , FloralWhite          , 255, 250, 240);
    _QX_DEFINE_COLOR(forest_green           , ForestGreen          ,  34, 139,  34);
    _QX_DEFINE_COLOR(fuchsia                , Fuchsia              , 255,   0, 255);
    _QX_DEFINE_COLOR(gainsboro              , Gainsboro            , 220, 220, 220);
    _QX_DEFINE_COLOR(ghost_white            , GhostWhite           , 248, 248, 255);
    _QX_DEFINE_COLOR(gold                   , Gold                 , 255, 215,   0);
    _QX_DEFINE_COLOR(goldenrod              , Goldenrod            , 218, 165,  32);
    _QX_DEFINE_COLOR(gray                   , Gray                 , 128, 128, 128);
    _QX_DEFINE_COLOR(green                  , Green                ,   0, 128,   0);
    _QX_DEFINE_COLOR(green_yellow           , GreenYellow          , 173, 255,  47);
    _QX_DEFINE_COLOR(honeydew               , Honeydew             , 240, 255, 240);
    _QX_DEFINE_COLOR(hot_pink               , HotPink              , 255, 105, 180);
    _QX_DEFINE_COLOR(indian_red             , IndianRed            , 205,  92,  92);
    _QX_DEFINE_COLOR(indigo                 , Indigo               ,  75,   0, 130);
    _QX_DEFINE_COLOR(ivory                  , Ivory                , 255, 255, 240);
    _QX_DEFINE_COLOR(khaki                  , Khaki                , 240, 230, 140);
    _QX_DEFINE_COLOR(lavender               , Lavender             , 230, 230, 250);
    _QX_DEFINE_COLOR(lavender_blush         , LavenderBlush        , 255, 240, 245);
    _QX_DEFINE_COLOR(lawn_green             , LawnGreen            , 124, 252,   0);
    _QX_DEFINE_COLOR(lemon_chiffon          , LemonChiffon         , 255, 250, 205);
    _QX_DEFINE_COLOR(light_blue             , LightBlue            , 173, 216, 230);
    _QX_DEFINE_COLOR(light_coral            , LightCoral           , 240, 128, 128);
    _QX_DEFINE_COLOR(light_cyan             , LightCyan            , 224, 255, 255);
    _QX_DEFINE_COLOR(light_goldenrod_yellow , LightGoldenrodYellow , 250, 250, 210);
    _QX_DEFINE_COLOR(light_green            , LightGreen           , 144, 238, 144);
    _QX_DEFINE_COLOR(light_grey             , LightGrey            , 211, 211, 211);
    _QX_DEFINE_COLOR(light_pink             , LightPink            , 255, 182, 193);
    _QX_DEFINE_COLOR(light_salmon           , LightSalmon          , 255, 160, 122);
    _QX_DEFINE_COLOR(light_sea_green        , LightSeaGreen        ,  32, 178, 170);
    _QX_DEFINE_COLOR(light_sky_blue         , LightSkyBlue         , 135, 206, 250);
    _QX_DEFINE_COLOR(light_slate_gray       , LightSlateGray       , 119, 136, 153);
    _QX_DEFINE_COLOR(light_steel_blue       , LightSteelBlue       , 176, 196, 222);
    _QX_DEFINE_COLOR(light_yellow           , LightYellow          , 255, 255, 224);
    _QX_DEFINE_COLOR(lime                   , Lime                 ,   0, 255,   0);
    _QX_DEFINE_COLOR(lime_green             , LimeGreen            ,  50, 205,  50);
    _QX_DEFINE_COLOR(linen                  , Linen                , 250, 240, 230);
    _QX_DEFINE_COLOR(magenta                , Magenta              , 255,   0, 255);
    _QX_DEFINE_COLOR(maroon                 , Maroon               , 128,   0,   0);
    _QX_DEFINE_COLOR(medium_aquamarine      , MediumAquamarine     , 102, 205, 170);
    _QX_DEFINE_COLOR(medium_blue            , MediumBlue           ,   0,   0, 205);
    _QX_DEFINE_COLOR(medium_orchid          , MediumOrchid         , 186,  85, 211);
    _QX_DEFINE_COLOR(medium_purple          , MediumPurple         , 147, 112, 219);
    _QX_DEFINE_COLOR(medium_sea_green       , MediumSeaGreen       ,  60, 179, 113);
    _QX_DEFINE_COLOR(medium_slate_blue      , MediumSlateBlue      , 123, 104, 238);
    _QX_DEFINE_COLOR(medium_spring_green    , MediumSpringGreen    ,   0, 250, 154);
    _QX_DEFINE_COLOR(medium_turquoise       , MediumTurquoise      ,  72, 209, 204);
    _QX_DEFINE_COLOR(medium_violet_red      , MediumVioletRed      , 199,  21, 133);
    _QX_DEFINE_COLOR(midnight_blue          , MidnightBlue         ,  25,  25, 112);
    _QX_DEFINE_COLOR(mint_cream             , MintCream            , 245, 255, 250);
    _QX_DEFINE_COLOR(misty_rose             , MistyRose            , 255, 228, 225);
    _QX_DEFINE_COLOR(moccasin               , Moccasin             , 255, 228, 181);
    _QX_DEFINE_COLOR(navajo_white           , NavajoWhite          , 255, 222, 173);
    _QX_DEFINE_COLOR(navy                   , Navy                 ,   0,   0, 128);
    _QX_DEFINE_COLOR(old_lace               , OldLace              , 253, 245, 230);
    _QX_DEFINE_COLOR(olive                  , Olive                , 128, 128,   0);
    _QX_DEFINE_COLOR(olive_drab             , OliveDrab            , 107, 142,  35);
    _QX_DEFINE_COLOR(orange                 , Orange               , 255, 165,   0);
    _QX_DEFINE_COLOR(orange_red             , OrangeRed            , 255,  69,   0);
    _QX_DEFINE_COLOR(orchid                 , Orchid               , 218, 112, 214);
    _QX_DEFINE_COLOR(pale_goldenrod         , PaleGoldenrod        , 238, 232, 170);
    _QX_DEFINE_COLOR(pale_green             , PaleGreen            , 152, 251, 152);
    _QX_DEFINE_COLOR(pale_turquoise         , PaleTurquoise        , 175, 238, 238);
    _QX_DEFINE_COLOR(pale_violet_red        , PaleVioletRed        , 219, 112, 147);
    _QX_DEFINE_COLOR(papaya_whip            , PapayaWhip           , 255, 239, 213);
    _QX_DEFINE_COLOR(peach_puff             , PeachPuff            , 255, 218, 185);
    _QX_DEFINE_COLOR(peru                   , Peru                 , 205, 133,  63);
    _QX_DEFINE_COLOR(pink                   , Pink                 , 255, 192, 203);
    _QX_DEFINE_COLOR(plum                   , Plum                 , 221, 160, 221);
    _QX_DEFINE_COLOR(powder_blue            , PowderBlue           , 176, 224, 230);
    _QX_DEFINE_COLOR(purple                 , Purple               , 128,   0, 128);
    _QX_DEFINE_COLOR(red                    , Red                  , 255,   0,   0);
    _QX_DEFINE_COLOR(rosy_brown             , RosyBrown            , 188, 143, 143);
    _QX_DEFINE_COLOR(royal_blue             , RoyalBlue            ,  65, 105, 225);
    _QX_DEFINE_COLOR(saddle_brown           , SaddleBrown          , 139,  69,  19);
    _QX_DEFINE_COLOR(salmon                 , Salmon               , 250, 128, 114);
    _QX_DEFINE_COLOR(sandy_brown            , SandyBrown           , 244, 164,  96);
    _QX_DEFINE_COLOR(sea_green              , SeaGreen             ,  46, 139,  87);
    _QX_DEFINE_COLOR(seashell               , Seashell             , 255, 245, 238);
    _QX_DEFINE_COLOR(sienna                 , Sienna               , 160,  82,  45);
    _QX_DEFINE_COLOR(silver                 , Silver               , 192, 192, 192);
    _QX_DEFINE_COLOR(sky_blue               , SkyBlue              , 135, 206, 235);
    _QX_DEFINE_COLOR(slate_blue             , SlateBlue            , 106,  90, 205);
    _QX_DEFINE_COLOR(slate_gray             , SlateGray            , 112, 128, 144);
    _QX_DEFINE_COLOR(snow                   , Snow                 , 255, 250, 250);
    _QX_DEFINE_COLOR(spring_green           , SpringGreen          ,   0, 255, 127);
    _QX_DEFINE_COLOR(steel_blue             , SteelBlue            ,  70, 130, 180);
    _QX_DEFINE_COLOR(tan                    , Tan                  , 210, 180, 140);
    _QX_DEFINE_COLOR(teal                   , Teal                 ,   0, 128, 128);
    _QX_DEFINE_COLOR(thistle                , Thistle              , 216, 191, 216);
    _QX_DEFINE_COLOR(tomato                 , Tomato               , 255,  99,  71);
    _QX_DEFINE_COLOR(turquoise              , Turquoise            ,  64, 224, 208);
    _QX_DEFINE_COLOR(violet                 , Violet               , 238, 130, 238);
    _QX_DEFINE_COLOR(wheat                  , Wheat                , 245, 222, 179);
    _QX_DEFINE_COLOR(white                  , White                , 255, 255, 255);
    _QX_DEFINE_COLOR(white_smoke            , WhiteSmoke           , 245, 245, 245);
    _QX_DEFINE_COLOR(yellow                 , Yellow               , 255, 255,   0);
    _QX_DEFINE_COLOR(yellow_green           , YellowGreen          , 154, 205,  50);
    // clang-format on

    /**
        @brief  Try to create color from string
        @param  svColorName - color name: css style (alice_blue, AliceBlue, aliceblue) or #F0F8FF or 0xF0F8FFFF(0xRRGGBBAA) or 0xF0F8FF(0xRRGGBB)
        @retval             - found color or nullopt
    **/
    static std::optional<color> from_string(string_view svColorName) noexcept;

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
