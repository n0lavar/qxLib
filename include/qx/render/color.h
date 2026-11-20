/**

    @file      color.h
    @author    Khrapov
    @date      2.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>
#include <qx/containers/string/string_view.h>
#include <qx/hash.h>
#include <qx/macros/common.h>
#include <qx/macros/copyable_movable.h>
#include <qx/macros/suppress_warnings.h>
#include <qx/patterns/singleton.h>

#include <algorithm>
#include <unordered_map>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
QX_POP_SUPPRESS_ALL_WARNINGS();

/// @see https://www.cssportal.com/html-colors/x11-colors.php
// clang-format off
#define QX_DETAILS_COLORS(macro)\
    macro(alice_blue             , AliceBlue            , aliceblue            , 240, 248, 255) \
    macro(antique_white          , AntiqueWhite         , antiquewhite         , 250, 235, 215) \
    macro(aqua                   , Aqua                 , aqua                 ,   0, 255, 255) \
    macro(aquamarine             , Aquamarine           , aquamarine           , 127, 255, 212) \
    macro(azure                  , Azure                , azure                , 240, 255, 255) \
    macro(beige                  , Beige                , beige                , 245, 245, 220) \
    macro(bisque                 , Bisque               , bisque               , 255, 228, 196) \
    macro(black                  , Black                , black                ,   0,   0,   0) \
    macro(blanched_almond        , BlanchedAlmond       , blanchedalmond       , 255, 235, 205) \
    macro(blue                   , Blue                 , blue                 ,   0,   0, 255) \
    macro(blue_violet            , BlueViolet           , blueviolet           , 138,  43, 226) \
    macro(brown                  , Brown                , brown                , 165,  42,  42) \
    macro(burly_wood             , BurlyWood            , burlywood            , 222, 184, 135) \
    macro(cadet_blue             , CadetBlue            , cadetblue            ,  95, 158, 160) \
    macro(chartreuse             , Chartreuse           , chartreuse           , 127, 255,   0) \
    macro(chocolate              , Chocolate            , chocolate            , 210, 105,  30) \
    macro(coral                  , Coral                , coral                , 255, 127,  80) \
    macro(cornflower_blue        , CornflowerBlue       , cornflowerblue       , 100, 149, 237) \
    macro(cornsilk               , Cornsilk             , cornsilk             , 255, 248, 220) \
    macro(crimson                , Crimson              , crimson              , 220,  20,  60) \
    macro(cyan                   , Cyan                 , cyan                 ,   0, 255, 255) \
    macro(dark_blue              , DarkBlue             , darkblue             ,   0,   0, 139) \
    macro(dark_cyan              , DarkCyan             , darkcyan             ,   0, 139, 139) \
    macro(dark_goldenrod         , DarkGoldenrod        , darkgoldenrod        , 184, 134,  11) \
    macro(dark_gray              , DarkGray             , darkgray             , 169, 169, 169) \
    macro(dark_green             , DarkGreen            , darkgreen            ,   0, 100,   0) \
    macro(dark_khaki             , DarkKhaki            , darkkhaki            , 189, 183, 107) \
    macro(dark_magenta           , DarkMagenta          , darkmagenta          , 139,   0, 139) \
    macro(dark_olive_green       , DarkOliveGreen       , darkolivegreen       ,  85, 107,  47) \
    macro(dark_orange            , DarkOrange           , darkorange           , 255, 140,   0) \
    macro(dark_orchid            , DarkOrchid           , darkorchid           , 153,  50, 204) \
    macro(dark_red               , DarkRed              , darkred              , 139,   0,   0) \
    macro(dark_salmon            , DarkSalmon           , darksalmon           , 233, 150, 122) \
    macro(dark_sea_green         , DarkSeaGreen         , darkseagreen         , 143, 188, 143) \
    macro(dark_slate_blue        , DarkSlateBlue        , darkslateblue        ,  72,  61, 139) \
    macro(dark_slate_gray        , DarkSlateGray        , darkslategray        ,  47,  79,  79) \
    macro(dark_turquoise         , DarkTurquoise        , darkturquoise        ,   0, 206, 209) \
    macro(dark_violet            , DarkViolet           , darkviolet           , 148,   0, 211) \
    macro(deep_pink              , DeepPink             , deeppink             , 255,  20, 147) \
    macro(deep_sky_blue          , DeepSkyBlue          , deepskyblue          ,   0, 191, 255) \
    macro(dim_gray               , DimGray              , dimgray              , 105, 105, 105) \
    macro(dodger_blue            , DodgerBlue           , dodgerblue           ,  30, 144, 255) \
    macro(fire_brick             , FireBrick            , firebrick            , 178,  34,  34) \
    macro(floral_white           , FloralWhite          , floralwhite          , 255, 250, 240) \
    macro(forest_green           , ForestGreen          , forestgreen          ,  34, 139,  34) \
    macro(fuchsia                , Fuchsia              , fuchsia              , 255,   0, 255) \
    macro(gainsboro              , Gainsboro            , gainsboro            , 220, 220, 220) \
    macro(ghost_white            , GhostWhite           , ghostwhite           , 248, 248, 255) \
    macro(gold                   , Gold                 , gold                 , 255, 215,   0) \
    macro(goldenrod              , Goldenrod            , goldenrod            , 218, 165,  32) \
    macro(gray                   , Gray                 , gray                 , 128, 128, 128) \
    macro(green                  , Green                , green                ,   0, 128,   0) \
    macro(green_yellow           , GreenYellow          , greenyellow          , 173, 255,  47) \
    macro(honeydew               , Honeydew             , honeydew             , 240, 255, 240) \
    macro(hot_pink               , HotPink              , hotpink              , 255, 105, 180) \
    macro(indian_red             , IndianRed            , indianred            , 205,  92,  92) \
    macro(indigo                 , Indigo               , indigo               ,  75,   0, 130) \
    macro(ivory                  , Ivory                , ivory                , 255, 255, 240) \
    macro(khaki                  , Khaki                , khaki                , 240, 230, 140) \
    macro(lavender               , Lavender             , lavender             , 230, 230, 250) \
    macro(lavender_blush         , LavenderBlush        , lavenderblush        , 255, 240, 245) \
    macro(lawn_green             , LawnGreen            , lawngreen            , 124, 252,   0) \
    macro(lemon_chiffon          , LemonChiffon         , lemonchiffon         , 255, 250, 205) \
    macro(light_blue             , LightBlue            , lightblue            , 173, 216, 230) \
    macro(light_coral            , LightCoral           , lightcoral           , 240, 128, 128) \
    macro(light_cyan             , LightCyan            , lightcyan            , 224, 255, 255) \
    macro(light_goldenrod_yellow , LightGoldenrodYellow , lightgoldenrodyellow , 250, 250, 210) \
    macro(light_green            , LightGreen           , lightgreen           , 144, 238, 144) \
    macro(light_grey             , LightGrey            , lightgrey            , 211, 211, 211) \
    macro(light_pink             , LightPink            , lightpink            , 255, 182, 193) \
    macro(light_salmon           , LightSalmon          , lightsalmon          , 255, 160, 122) \
    macro(light_sea_green        , LightSeaGreen        , lightseagreen        ,  32, 178, 170) \
    macro(light_sky_blue         , LightSkyBlue         , lightskyblue         , 135, 206, 250) \
    macro(light_slate_gray       , LightSlateGray       , lightslategray       , 119, 136, 153) \
    macro(light_steel_blue       , LightSteelBlue       , lightsteelblue       , 176, 196, 222) \
    macro(light_yellow           , LightYellow          , lightyellow          , 255, 255, 224) \
    macro(lime                   , Lime                 , lime                 ,   0, 255,   0) \
    macro(lime_green             , LimeGreen            , limegreen            ,  50, 205,  50) \
    macro(linen                  , Linen                , linen                , 250, 240, 230) \
    macro(magenta                , Magenta              , magenta              , 255,   0, 255) \
    macro(maroon                 , Maroon               , maroon               , 128,   0,   0) \
    macro(medium_aquamarine      , MediumAquamarine     , mediumaquamarine     , 102, 205, 170) \
    macro(medium_blue            , MediumBlue           , mediumblue           ,   0,   0, 205) \
    macro(medium_orchid          , MediumOrchid         , mediumorchid         , 186,  85, 211) \
    macro(medium_purple          , MediumPurple         , mediumpurple         , 147, 112, 219) \
    macro(medium_sea_green       , MediumSeaGreen       , mediumseagreen       ,  60, 179, 113) \
    macro(medium_slate_blue      , MediumSlateBlue      , mediumslateblue      , 123, 104, 238) \
    macro(medium_spring_green    , MediumSpringGreen    , mediumspringgreen    ,   0, 250, 154) \
    macro(medium_turquoise       , MediumTurquoise      , mediumturquoise      ,  72, 209, 204) \
    macro(medium_violet_red      , MediumVioletRed      , mediumvioletred      , 199,  21, 133) \
    macro(midnight_blue          , MidnightBlue         , midnightblue         ,  25,  25, 112) \
    macro(mint_cream             , MintCream            , mintcream            , 245, 255, 250) \
    macro(misty_rose             , MistyRose            , mistyrose            , 255, 228, 225) \
    macro(moccasin               , Moccasin             , moccasin             , 255, 228, 181) \
    macro(navajo_white           , NavajoWhite          , navajowhite          , 255, 222, 173) \
    macro(navy                   , Navy                 , navy                 ,   0,   0, 128) \
    macro(old_lace               , OldLace              , oldlace              , 253, 245, 230) \
    macro(olive                  , Olive                , olive                , 128, 128,   0) \
    macro(olive_drab             , OliveDrab            , olivedrab            , 107, 142,  35) \
    macro(orange                 , Orange               , orange               , 255, 165,   0) \
    macro(orange_red             , OrangeRed            , orangered            , 255,  69,   0) \
    macro(orchid                 , Orchid               , orchid               , 218, 112, 214) \
    macro(pale_goldenrod         , PaleGoldenrod        , palegoldenrod        , 238, 232, 170) \
    macro(pale_green             , PaleGreen            , palegreen            , 152, 251, 152) \
    macro(pale_turquoise         , PaleTurquoise        , paleturquoise        , 175, 238, 238) \
    macro(pale_violet_red        , PaleVioletRed        , palevioletred        , 219, 112, 147) \
    macro(papaya_whip            , PapayaWhip           , papayawhip           , 255, 239, 213) \
    macro(peach_puff             , PeachPuff            , peachpuff            , 255, 218, 185) \
    macro(peru                   , Peru                 , peru                 , 205, 133,  63) \
    macro(pink                   , Pink                 , pink                 , 255, 192, 203) \
    macro(plum                   , Plum                 , plum                 , 221, 160, 221) \
    macro(powder_blue            , PowderBlue           , powderblue           , 176, 224, 230) \
    macro(purple                 , Purple               , purple               , 128,   0, 128) \
    macro(red                    , Red                  , red                  , 255,   0,   0) \
    macro(rosy_brown             , RosyBrown            , rosybrown            , 188, 143, 143) \
    macro(royal_blue             , RoyalBlue            , royalblue            ,  65, 105, 225) \
    macro(saddle_brown           , SaddleBrown          , saddlebrown          , 139,  69,  19) \
    macro(salmon                 , Salmon               , salmon               , 250, 128, 114) \
    macro(sandy_brown            , SandyBrown           , sandybrown           , 244, 164,  96) \
    macro(sea_green              , SeaGreen             , seagreen             ,  46, 139,  87) \
    macro(seashell               , Seashell             , seashell             , 255, 245, 238) \
    macro(sienna                 , Sienna               , sienna               , 160,  82,  45) \
    macro(silver                 , Silver               , silver               , 192, 192, 192) \
    macro(sky_blue               , SkyBlue              , skyblue              , 135, 206, 235) \
    macro(slate_blue             , SlateBlue            , slateblue            , 106,  90, 205) \
    macro(slate_gray             , SlateGray            , slategray            , 112, 128, 144) \
    macro(snow                   , Snow                 , snow                 , 255, 250, 250) \
    macro(spring_green           , SpringGreen          , springgreen          ,   0, 255, 127) \
    macro(steel_blue             , SteelBlue            , steelblue            ,  70, 130, 180) \
    macro(tan                    , Tan                  , tan                  , 210, 180, 140) \
    macro(teal                   , Teal                 , teal                 ,   0, 128, 128) \
    macro(thistle                , Thistle              , thistle              , 216, 191, 216) \
    macro(tomato                 , Tomato               , tomato               , 255,  99,  71) \
    macro(turquoise              , Turquoise            , turquoise            ,  64, 224, 208) \
    macro(violet                 , Violet               , violet               , 238, 130, 238) \
    macro(wheat                  , Wheat                , wheat                , 245, 222, 179) \
    macro(white                  , White                , white                , 255, 255, 255) \
    macro(white_smoke            , WhiteSmoke           , whitesmoke           , 245, 245, 245) \
    macro(yellow                 , Yellow               , yellow               , 255, 255,   0) \
    macro(yellow_green           , YellowGreen          , yellowgreen          , 154, 205,  50) \
    QX_EMPTY_MACRO
// clang-format on


namespace qx
{

enum class color_name_type
{
    //              | formatter | output example
    // -------------|-----------|-------------------
    css_snake,  //  | {:s}      | alice_blue
    css_pascal, //  | {:p}      | AliceBlue
    css_lower,  //  | {:l}      | aliceblue
    hex_lower,  //  | {:x[a]}   | f0f8ff[ff]
    hex_upper,  //  | {:X[a]}   | F0F8FF[FF]
    rgb,        //  | {:r[a]}   | 240,248,255[,255]
};

/**

    @class   color
    @brief   RGBA color
    @author  Khrapov
    @date    10.04.2021

**/
class color
{
    QX_COPYMOVABLE(color);

public:
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
        @return - red component
    **/
    constexpr float r() const noexcept;

    /**
        @brief  Get green component
        @return - green component
    **/
    constexpr float g() const noexcept;

    /**
        @brief  Get blue component
        @return - blue component
    **/
    constexpr float b() const noexcept;

    /**
        @brief  Get alpha component
        @return - alpha component
    **/
    constexpr float a() const noexcept;

    /**
        @brief  Get color component
        @param  i - component number [0, 3]
        @return   - component value
    **/
    constexpr float& operator[](size_t i) noexcept;

    /**
        @brief  Get color component
        @param  i - component number [0, 3]
        @return   - component value
    **/
    constexpr const float& operator[](size_t i) const noexcept;

    /**
        @brief  Get red component as decimal 
        @return - red component as decimal
    **/
    constexpr int r_dec() const noexcept;

    /**
        @brief  Get green component as decimal 
        @return - green component as decimal
    **/
    constexpr int g_dec() const noexcept;

    /**
        @brief  Get blue component as decimal 
        @return - blue component as decimal
    **/
    constexpr int b_dec() const noexcept;

    /**
        @brief  Get alpha component as decimal 
        @return - alpha component as decimal
    **/
    constexpr int a_dec() const noexcept;

    /**
        @brief  Get pointer to the first component
        @return - pointer to the first component
    **/
    constexpr const float* data() const noexcept;

    /**
        @brief  Get color as hex
        @return - hex color value in 0xRRGGBB format
    **/
    constexpr unsigned int hex_rgb() const noexcept;

    /**
        @brief  Get color as hex
        @return - hex color value in 0xRRGGBBAA format
    **/
    constexpr unsigned int hex_rgba() const noexcept;

    /**
        @brief  Get color as hex
        @return  - hex color value in 0xAARRGGBB format
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
        @return          - darker color
    **/
    constexpr static color darken(const color& other, float fPercent) noexcept;

    /**
        @brief  Make brighter color
        @param  other    - original color
        @param  fPercent - brighter factor
        @return          - brighter color
    **/
    constexpr static color brighten(const color& other, float fPercent) noexcept;

#define QX_DETAILS_COLOR_METHOD(snakeCaseName, pascalCaseName, lowerCaseName, r, g, b) \
    static constexpr auto snakeCaseName(float fAlpha = 1.f) noexcept                   \
    {                                                                                  \
        return color(r, g, b, float_to_dec(fAlpha));                                   \
    }

    /// Color functions
    QX_DETAILS_COLORS(QX_DETAILS_COLOR_METHOD);

    /**
        @brief  Try to create color from string
        @param  svColorName - color name: css style (alice_blue, AliceBlue, aliceblue) or #F0F8FF or 0xF0F8FFFF(0xRRGGBBAA) or 0xF0F8FF(0xRRGGBB)
        @return             - found color or nullopt
    **/
    static std::optional<color> from_string(string_view svColorName) noexcept;

    /**
        @brief  Generate a color unique for a hash value
        @param  nHash - hash value
        @return       - generated color
    **/
    static constexpr color from_hash(size_t nHash) noexcept;

    /**
        @brief   Get empty color (0, 0, 0, 0)
        @details - empty color can be useful for out of border values
                   as they won't affect calc result
        @return  - empty color
    **/
    static constexpr color empty() noexcept;

    /**
        @brief  Get number of float components
        @return  - number of float components
    **/
    static constexpr size_t size() noexcept;

private:
    /**
        @brief  Clamp a value to a valid range
        @param  fValue - input value
        @return        - clamped value [0.f, 1.f]
    **/
    static constexpr float clamp_value(float fValue) noexcept;

    /**
        @brief  Convert decimal value to float
        @param  nValue - decimal value   [0, 255]
        @return        - float value     [0.f, 1.f]
    **/
    static constexpr float dec_to_float(int nValue) noexcept;

    /**
        @brief  Convert float value to decimal
        @param  fValue - float value     [0.f, 1.f]
        @return        - decimal value   [0, 255]
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
