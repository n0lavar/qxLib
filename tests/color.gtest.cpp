/**

    @file      color.gtest.cpp
    @author    Khrapov
    @date      16.07.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

#include <common.h>

//V_EXCLUDE_PATH *color.gtest.cpp

#include <qx/math/between.h>
#include <qx/render/color.h>

template<class... Args>
void TestColor(const qx::color& color, int r = -1, int g = -1, int b = -1, const Args&... args)
{
    if (r != -1)
        EXPECT_EQ(r, color.r_dec());
    if (g != -1)
        EXPECT_EQ(g, color.g_dec());
    if (b != -1)
        EXPECT_EQ(b, color.b_dec());

    EXPECT_TRUE(qx::between(0.f, color.r(), 1.f));
    EXPECT_TRUE(qx::between(0.f, color.g(), 1.f));
    EXPECT_TRUE(qx::between(0.f, color.b(), 1.f));
    EXPECT_TRUE(qx::between(0.f, color.a(), 1.f));

    EXPECT_TRUE(qx::between(0, color.r_dec(), 255));
    EXPECT_TRUE(qx::between(0, color.g_dec(), 255));
    EXPECT_TRUE(qx::between(0, color.b_dec(), 255));
    EXPECT_TRUE(qx::between(0, color.a_dec(), 255));

    ASSERT_TRUE(color.data());
    EXPECT_EQ(color.size(), 4);
    EXPECT_EQ(color.data()[0], color.r());
    EXPECT_EQ(color.data()[1], color.g());
    EXPECT_EQ(color.data()[2], color.b());
    EXPECT_EQ(color.data()[3], color.a());

    glm::vec4 vec4color = color;
    EXPECT_EQ(vec4color[0], color.r());
    EXPECT_EQ(vec4color[1], color.g());
    EXPECT_EQ(vec4color[2], color.b());
    EXPECT_EQ(vec4color[3], color.a());

    glm::vec3 vec3color = color;
    EXPECT_EQ(vec3color[0], color.r());
    EXPECT_EQ(vec3color[1], color.g());
    EXPECT_EQ(vec3color[2], color.b());

    auto CheckName = [&color](const auto& name)
    {
        if (name)
        {
            const auto optFromName = qx::color::from_string(name);
            EXPECT_TRUE(optFromName) << name;
            if (optFromName)
                EXPECT_EQ(*optFromName, color) << name;
        }
    };

    (
        [&]()
        {
            if (args)
            {
                const auto optFromName = qx::color::from_string(args);
                EXPECT_TRUE(optFromName) << args;
                if (optFromName)
                    EXPECT_EQ(*optFromName, color) << args;
            }
        }(),
        ...);

    // unsigned int hex = color.hex();
    // EXPECT_EQ(qx::color(hex), color);
}

#define EXPAND_ARGS(snakeName, pascalName, hashName, name0x, name0xXX, r, g, b)                                     \
    qx::color::snakeName(), r, g, b, QXT(#snakeName), QXT(#pascalName), QXT(hashName), QXT(name0x), \
        QXT(name0xXX)

TEST(color, colors)
{
    // clang-format off
    TestColor(qx::color(), 255, 255, 255);
    TestColor(EXPAND_ARGS(alice_blue             , AliceBlue            , "#F0F8FF", "0xF0F8FF", "0xF0F8FFFF", 240, 248, 255));
    TestColor(EXPAND_ARGS(antique_white          , AntiqueWhite         , "#FAEBD7", "0xFAEBD7", "0xFAEBD7FF", 250, 235, 215));
    TestColor(EXPAND_ARGS(aqua                   , Aqua                 , "#00FFFF", "0x00FFFF", "0x00FFFFFF",   0, 255, 255));
    TestColor(EXPAND_ARGS(aquamarine             , Aquamarine           , "#7FFFD4", "0x7FFFD4", "0x7FFFD4FF", 127, 255, 212));
    TestColor(EXPAND_ARGS(azure                  , Azure                , "#F0FFFF", "0xF0FFFF", "0xF0FFFFFF", 240, 255, 255));
    TestColor(EXPAND_ARGS(beige                  , Beige                , "#F5F5DC", "0xF5F5DC", "0xF5F5DCFF", 245, 245, 220));
    TestColor(EXPAND_ARGS(bisque                 , Bisque               , "#FFE4C4", "0xFFE4C4", "0xFFE4C4FF", 255, 228, 196));
    TestColor(EXPAND_ARGS(black                  , Black                , "#000000", "0x000000", "0x000000FF",   0,   0,   0));
    TestColor(EXPAND_ARGS(blanched_almond        , BlanchedAlmond       , "#FFEBCD", "0xFFEBCD", "0xFFEBCDFF", 255, 235, 205));
    TestColor(EXPAND_ARGS(blue                   , Blue                 , "#0000FF", "0x0000FF", "0x0000FFFF",   0,   0, 255));
    TestColor(EXPAND_ARGS(blue_violet            , BlueViolet           , "#8A2BE2", "0x8A2BE2", "0x8A2BE2FF", 138,  43, 226));
    TestColor(EXPAND_ARGS(brown                  , Brown                , "#A52A2A", "0xA52A2A", "0xA52A2AFF", 165,  42,  42));
    TestColor(EXPAND_ARGS(burly_wood             , BurlyWood            , "#DEB887", "0xDEB887", "0xDEB887FF", 222, 184, 135));
    TestColor(EXPAND_ARGS(cadet_blue             , CadetBlue            , "#5F9EA0", "0x5F9EA0", "0x5F9EA0FF",  95, 158, 160));
    TestColor(EXPAND_ARGS(chartreuse             , Chartreuse           , "#7FFF00", "0x7FFF00", "0x7FFF00FF", 127, 255,   0));
    TestColor(EXPAND_ARGS(chocolate              , Chocolate            , "#D2691E", "0xD2691E", "0xD2691EFF", 210, 105,  30));
    TestColor(EXPAND_ARGS(coral                  , Coral                , "#FF7F50", "0xFF7F50", "0xFF7F50FF", 255, 127,  80));
    TestColor(EXPAND_ARGS(cornflower_blue        , CornflowerBlue       , "#6495ED", "0x6495ED", "0x6495EDFF", 100, 149, 237));
    TestColor(EXPAND_ARGS(cornsilk               , Cornsilk             , "#FFF8DC", "0xFFF8DC", "0xFFF8DCFF", 255, 248, 220));
    TestColor(EXPAND_ARGS(crimson                , Crimson              , "#DC143C", "0xDC143C", "0xDC143CFF", 220,  20,  60));
    TestColor(EXPAND_ARGS(cyan                   , Cyan                 , "#00FFFF", "0x00FFFF", "0x00FFFFFF",   0, 255, 255));
    TestColor(EXPAND_ARGS(dark_blue              , DarkBlue             , "#00008B", "0x00008B", "0x00008BFF",   0,   0, 139));
    TestColor(EXPAND_ARGS(dark_cyan              , DarkCyan             , "#008B8B", "0x008B8B", "0x008B8BFF",   0, 139, 139));
    TestColor(EXPAND_ARGS(dark_goldenrod         , DarkGoldenrod        , "#B8860B", "0xB8860B", "0xB8860BFF", 184, 134,  11));
    TestColor(EXPAND_ARGS(dark_gray              , DarkGray             , "#A9A9A9", "0xA9A9A9", "0xA9A9A9FF", 169, 169, 169));
    TestColor(EXPAND_ARGS(dark_green             , DarkGreen            , "#006400", "0x006400", "0x006400FF",   0, 100,   0));
    TestColor(EXPAND_ARGS(dark_khaki             , DarkKhaki            , "#BDB76B", "0xBDB76B", "0xBDB76BFF", 189, 183, 107));
    TestColor(EXPAND_ARGS(dark_magenta           , DarkMagenta          , "#8B008B", "0x8B008B", "0x8B008BFF", 139,   0, 139));
    TestColor(EXPAND_ARGS(dark_olive_green       , DarkOliveGreen       , "#556B2F", "0x556B2F", "0x556B2FFF",  85, 107,  47));
    TestColor(EXPAND_ARGS(dark_orange            , DarkOrange           , "#FF8C00", "0xFF8C00", "0xFF8C00FF", 255, 140,   0));
    TestColor(EXPAND_ARGS(dark_orchid            , DarkOrchid           , "#9932CC", "0x9932CC", "0x9932CCFF", 153,  50, 204));
    TestColor(EXPAND_ARGS(dark_red               , DarkRed              , "#8B0000", "0x8B0000", "0x8B0000FF", 139,   0,   0));
    TestColor(EXPAND_ARGS(dark_salmon            , DarkSalmon           , "#E9967A", "0xE9967A", "0xE9967AFF", 233, 150, 122));
    TestColor(EXPAND_ARGS(dark_sea_green         , DarkSeaGreen         , "#8FBC8F", "0x8FBC8F", "0x8FBC8FFF", 143, 188, 143));
    TestColor(EXPAND_ARGS(dark_slate_blue        , DarkSlateBlue        , "#483D8B", "0x483D8B", "0x483D8BFF",  72,  61, 139));
    TestColor(EXPAND_ARGS(dark_slate_gray        , DarkSlateGray        , "#2F4F4F", "0x2F4F4F", "0x2F4F4FFF",  47,  79,  79));
    TestColor(EXPAND_ARGS(dark_turquoise         , DarkTurquoise        , "#00CED1", "0x00CED1", "0x00CED1FF",   0, 206, 209));
    TestColor(EXPAND_ARGS(dark_violet            , DarkViolet           , "#9400D3", "0x9400D3", "0x9400D3FF", 148,   0, 211));
    TestColor(EXPAND_ARGS(deep_pink              , DeepPink             , "#FF1493", "0xFF1493", "0xFF1493FF", 255,  20, 147));
    TestColor(EXPAND_ARGS(deep_sky_blue          , DeepSkyBlue          , "#00BFFF", "0x00BFFF", "0x00BFFFFF",   0, 191, 255));
    TestColor(EXPAND_ARGS(dim_gray               , DimGray              , "#696969", "0x696969", "0x696969FF", 105, 105, 105));
    TestColor(EXPAND_ARGS(dodger_blue            , DodgerBlue           , "#1E90FF", "0x1E90FF", "0x1E90FFFF",  30, 144, 255));
    TestColor(EXPAND_ARGS(fire_brick             , FireBrick            , "#B22222", "0xB22222", "0xB22222FF", 178,  34,  34));
    TestColor(EXPAND_ARGS(floral_white           , FloralWhite          , "#FFFAF0", "0xFFFAF0", "0xFFFAF0FF", 255, 250, 240));
    TestColor(EXPAND_ARGS(forest_green           , ForestGreen          , "#228B22", "0x228B22", "0x228B22FF",  34, 139,  34));
    TestColor(EXPAND_ARGS(fuchsia                , Fuchsia              , "#FF00FF", "0xFF00FF", "0xFF00FFFF", 255,   0, 255));
    TestColor(EXPAND_ARGS(gainsboro              , Gainsboro            , "#DCDCDC", "0xDCDCDC", "0xDCDCDCFF", 220, 220, 220));
    TestColor(EXPAND_ARGS(ghost_white            , GhostWhite           , "#F8F8FF", "0xF8F8FF", "0xF8F8FFFF", 248, 248, 255));
    TestColor(EXPAND_ARGS(gold                   , Gold                 , "#FFD700", "0xFFD700", "0xFFD700FF", 255, 215,   0));
    TestColor(EXPAND_ARGS(goldenrod              , Goldenrod            , "#DAA520", "0xDAA520", "0xDAA520FF", 218, 165,  32));
    TestColor(EXPAND_ARGS(gray                   , Gray                 , "#808080", "0x808080", "0x808080FF", 128, 128, 128));
    TestColor(EXPAND_ARGS(green                  , Green                , "#008000", "0x008000", "0x008000FF",   0, 128,   0));
    TestColor(EXPAND_ARGS(green_yellow           , GreenYellow          , "#ADFF2F", "0xADFF2F", "0xADFF2FFF", 173, 255,  47));
    TestColor(EXPAND_ARGS(honeydew               , Honeydew             , "#F0FFF0", "0xF0FFF0", "0xF0FFF0FF", 240, 255, 240));
    TestColor(EXPAND_ARGS(hot_pink               , HotPink              , "#FF69B4", "0xFF69B4", "0xFF69B4FF", 255, 105, 180));
    TestColor(EXPAND_ARGS(indian_red             , IndianRed            , "#CD5C5C", "0xCD5C5C", "0xCD5C5CFF", 205,  92,  92));
    TestColor(EXPAND_ARGS(indigo                 , Indigo               , "#4B0082", "0x4B0082", "0x4B0082FF",  75,   0, 130));
    TestColor(EXPAND_ARGS(ivory                  , Ivory                , "#FFFFF0", "0xFFFFF0", "0xFFFFF0FF", 255, 255, 240));
    TestColor(EXPAND_ARGS(khaki                  , Khaki                , "#F0E68C", "0xF0E68C", "0xF0E68CFF", 240, 230, 140));
    TestColor(EXPAND_ARGS(lavender               , Lavender             , "#E6E6FA", "0xE6E6FA", "0xE6E6FAFF", 230, 230, 250));
    TestColor(EXPAND_ARGS(lavender_blush         , LavenderBlush        , "#FFF0F5", "0xFFF0F5", "0xFFF0F5FF", 255, 240, 245));
    TestColor(EXPAND_ARGS(lawn_green             , LawnGreen            , "#7CFC00", "0x7CFC00", "0x7CFC00FF", 124, 252,   0));
    TestColor(EXPAND_ARGS(lemon_chiffon          , LemonChiffon         , "#FFFACD", "0xFFFACD", "0xFFFACDFF", 255, 250, 205));
    TestColor(EXPAND_ARGS(light_blue             , LightBlue            , "#ADD8E6", "0xADD8E6", "0xADD8E6FF", 173, 216, 230));
    TestColor(EXPAND_ARGS(light_coral            , LightCoral           , "#F08080", "0xF08080", "0xF08080FF", 240, 128, 128));
    TestColor(EXPAND_ARGS(light_cyan             , LightCyan            , "#E0FFFF", "0xE0FFFF", "0xE0FFFFFF", 224, 255, 255));
    TestColor(EXPAND_ARGS(light_goldenrod_yellow , LightGoldenrodYellow , "#FAFAD2", "0xFAFAD2", "0xFAFAD2FF", 250, 250, 210));
    TestColor(EXPAND_ARGS(light_green            , LightGreen           , "#90EE90", "0x90EE90", "0x90EE90FF", 144, 238, 144));
    TestColor(EXPAND_ARGS(light_grey             , LightGrey            , "#D3D3D3", "0xD3D3D3", "0xD3D3D3FF", 211, 211, 211));
    TestColor(EXPAND_ARGS(light_pink             , LightPink            , "#FFB6C1", "0xFFB6C1", "0xFFB6C1FF", 255, 182, 193));
    TestColor(EXPAND_ARGS(light_salmon           , LightSalmon          , "#FFA07A", "0xFFA07A", "0xFFA07AFF", 255, 160, 122));
    TestColor(EXPAND_ARGS(light_sea_green        , LightSeaGreen        , "#20B2AA", "0x20B2AA", "0x20B2AAFF",  32, 178, 170));
    TestColor(EXPAND_ARGS(light_sky_blue         , LightSkyBlue         , "#87CEFA", "0x87CEFA", "0x87CEFAFF", 135, 206, 250));
    TestColor(EXPAND_ARGS(light_slate_gray       , LightSlateGray       , "#778899", "0x778899", "0x778899FF", 119, 136, 153));
    TestColor(EXPAND_ARGS(light_steel_blue       , LightSteelBlue       , "#B0C4DE", "0xB0C4DE", "0xB0C4DEFF", 176, 196, 222));
    TestColor(EXPAND_ARGS(light_yellow           , LightYellow          , "#FFFFE0", "0xFFFFE0", "0xFFFFE0FF", 255, 255, 224));
    TestColor(EXPAND_ARGS(lime                   , Lime                 , "#00FF00", "0x00FF00", "0x00FF00FF",   0, 255,   0));
    TestColor(EXPAND_ARGS(lime_green             , LimeGreen            , "#32CD32", "0x32CD32", "0x32CD32FF",  50, 205,  50));
    TestColor(EXPAND_ARGS(linen                  , Linen                , "#FAF0E6", "0xFAF0E6", "0xFAF0E6FF", 250, 240, 230));
    TestColor(EXPAND_ARGS(magenta                , Magenta              , "#FF00FF", "0xFF00FF", "0xFF00FFFF", 255,   0, 255));
    TestColor(EXPAND_ARGS(maroon                 , Maroon               , "#800000", "0x800000", "0x800000FF", 128,   0,   0));
    TestColor(EXPAND_ARGS(medium_aquamarine      , MediumAquamarine     , "#66CDAA", "0x66CDAA", "0x66CDAAFF", 102, 205, 170));
    TestColor(EXPAND_ARGS(medium_blue            , MediumBlue           , "#0000CD", "0x0000CD", "0x0000CDFF",   0,   0, 205));
    TestColor(EXPAND_ARGS(medium_orchid          , MediumOrchid         , "#BA55D3", "0xBA55D3", "0xBA55D3FF", 186,  85, 211));
    TestColor(EXPAND_ARGS(medium_purple          , MediumPurple         , "#9370DB", "0x9370DB", "0x9370DBFF", 147, 112, 219));
    TestColor(EXPAND_ARGS(medium_sea_green       , MediumSeaGreen       , "#3CB371", "0x3CB371", "0x3CB371FF",  60, 179, 113));
    TestColor(EXPAND_ARGS(medium_slate_blue      , MediumSlateBlue      , "#7B68EE", "0x7B68EE", "0x7B68EEFF", 123, 104, 238));
    TestColor(EXPAND_ARGS(medium_spring_green    , MediumSpringGreen    , "#00FA9A", "0x00FA9A", "0x00FA9AFF",   0, 250, 154));
    TestColor(EXPAND_ARGS(medium_turquoise       , MediumTurquoise      , "#48D1CC", "0x48D1CC", "0x48D1CCFF",  72, 209, 204));
    TestColor(EXPAND_ARGS(medium_violet_red      , MediumVioletRed      , "#C71585", "0xC71585", "0xC71585FF", 199,  21, 133));
    TestColor(EXPAND_ARGS(midnight_blue          , MidnightBlue         , "#191970", "0x191970", "0x191970FF",  25,  25, 112));
    TestColor(EXPAND_ARGS(mint_cream             , MintCream            , "#F5FFFA", "0xF5FFFA", "0xF5FFFAFF", 245, 255, 250));
    TestColor(EXPAND_ARGS(misty_rose             , MistyRose            , "#FFE4E1", "0xFFE4E1", "0xFFE4E1FF", 255, 228, 225));
    TestColor(EXPAND_ARGS(moccasin               , Moccasin             , "#FFE4B5", "0xFFE4B5", "0xFFE4B5FF", 255, 228, 181));
    TestColor(EXPAND_ARGS(navajo_white           , NavajoWhite          , "#FFDEAD", "0xFFDEAD", "0xFFDEADFF", 255, 222, 173));
    TestColor(EXPAND_ARGS(navy                   , Navy                 , "#000080", "0x000080", "0x000080FF",   0,   0, 128));
    TestColor(EXPAND_ARGS(old_lace               , OldLace              , "#FDF5E6", "0xFDF5E6", "0xFDF5E6FF", 253, 245, 230));
    TestColor(EXPAND_ARGS(olive                  , Olive                , "#808000", "0x808000", "0x808000FF", 128, 128,   0));
    TestColor(EXPAND_ARGS(olive_drab             , OliveDrab            , "#6B8E23", "0x6B8E23", "0x6B8E23FF", 107, 142,  35));
    TestColor(EXPAND_ARGS(orange                 , Orange               , "#FFA500", "0xFFA500", "0xFFA500FF", 255, 165,   0));
    TestColor(EXPAND_ARGS(orange_red             , OrangeRed            , "#FF4500", "0xFF4500", "0xFF4500FF", 255,  69,   0));
    TestColor(EXPAND_ARGS(orchid                 , Orchid               , "#DA70D6", "0xDA70D6", "0xDA70D6FF", 218, 112, 214));
    TestColor(EXPAND_ARGS(pale_goldenrod         , PaleGoldenrod        , "#EEE8AA", "0xEEE8AA", "0xEEE8AAFF", 238, 232, 170));
    TestColor(EXPAND_ARGS(pale_green             , PaleGreen            , "#98FB98", "0x98FB98", "0x98FB98FF", 152, 251, 152));
    TestColor(EXPAND_ARGS(pale_turquoise         , PaleTurquoise        , "#AFEEEE", "0xAFEEEE", "0xAFEEEEFF", 175, 238, 238));
    TestColor(EXPAND_ARGS(pale_violet_red        , PaleVioletRed        , "#DB7093", "0xDB7093", "0xDB7093FF", 219, 112, 147));
    TestColor(EXPAND_ARGS(papaya_whip            , PapayaWhip           , "#FFEFD5", "0xFFEFD5", "0xFFEFD5FF", 255, 239, 213));
    TestColor(EXPAND_ARGS(peach_puff             , PeachPuff            , "#FFDAB9", "0xFFDAB9", "0xFFDAB9FF", 255, 218, 185));
    TestColor(EXPAND_ARGS(peru                   , Peru                 , "#CD853F", "0xCD853F", "0xCD853FFF", 205, 133,  63));
    TestColor(EXPAND_ARGS(pink                   , Pink                 , "#FFC0CB", "0xFFC0CB", "0xFFC0CBFF", 255, 192, 203));
    TestColor(EXPAND_ARGS(plum                   , Plum                 , "#DDA0DD", "0xDDA0DD", "0xDDA0DDFF", 221, 160, 221));
    TestColor(EXPAND_ARGS(powder_blue            , PowderBlue           , "#B0E0E6", "0xB0E0E6", "0xB0E0E6FF", 176, 224, 230));
    TestColor(EXPAND_ARGS(purple                 , Purple               , "#800080", "0x800080", "0x800080FF", 128,   0, 128));
    TestColor(EXPAND_ARGS(red                    , Red                  , "#FF0000", "0xFF0000", "0xFF0000FF", 255,   0,   0));
    TestColor(EXPAND_ARGS(rosy_brown             , RosyBrown            , "#BC8F8F", "0xBC8F8F", "0xBC8F8FFF", 188, 143, 143));
    TestColor(EXPAND_ARGS(royal_blue             , RoyalBlue            , "#4169E1", "0x4169E1", "0x4169E1FF",  65, 105, 225));
    TestColor(EXPAND_ARGS(saddle_brown           , SaddleBrown          , "#8B4513", "0x8B4513", "0x8B4513FF", 139,  69,  19));
    TestColor(EXPAND_ARGS(salmon                 , Salmon               , "#FA8072", "0xFA8072", "0xFA8072FF", 250, 128, 114));
    TestColor(EXPAND_ARGS(sandy_brown            , SandyBrown           , "#F4A460", "0xF4A460", "0xF4A460FF", 244, 164,  96));
    TestColor(EXPAND_ARGS(sea_green              , SeaGreen             , "#2E8B57", "0x2E8B57", "0x2E8B57FF",  46, 139,  87));
    TestColor(EXPAND_ARGS(seashell               , Seashell             , "#FFF5EE", "0xFFF5EE", "0xFFF5EEFF", 255, 245, 238));
    TestColor(EXPAND_ARGS(sienna                 , Sienna               , "#A0522D", "0xA0522D", "0xA0522DFF", 160,  82,  45));
    TestColor(EXPAND_ARGS(silver                 , Silver               , "#C0C0C0", "0xC0C0C0", "0xC0C0C0FF", 192, 192, 192));
    TestColor(EXPAND_ARGS(sky_blue               , SkyBlue              , "#87CEEB", "0x87CEEB", "0x87CEEBFF", 135, 206, 235));
    TestColor(EXPAND_ARGS(slate_blue             , SlateBlue            , "#6A5ACD", "0x6A5ACD", "0x6A5ACDFF", 106,  90, 205));
    TestColor(EXPAND_ARGS(slate_gray             , SlateGray            , "#708090", "0x708090", "0x708090FF", 112, 128, 144));
    TestColor(EXPAND_ARGS(snow                   , Snow                 , "#FFFAFA", "0xFFFAFA", "0xFFFAFAFF", 255, 250, 250));
    TestColor(EXPAND_ARGS(spring_green           , SpringGreen          , "#00FF7F", "0x00FF7F", "0x00FF7FFF",   0, 255, 127));
    TestColor(EXPAND_ARGS(steel_blue             , SteelBlue            , "#4682B4", "0x4682B4", "0x4682B4FF",  70, 130, 180));
    TestColor(EXPAND_ARGS(tan                    , Tan                  , "#D2B48C", "0xD2B48C", "0xD2B48CFF", 210, 180, 140));
    TestColor(EXPAND_ARGS(teal                   , Teal                 , "#008080", "0x008080", "0x008080FF",   0, 128, 128));
    TestColor(EXPAND_ARGS(thistle                , Thistle              , "#D8BFD8", "0xD8BFD8", "0xD8BFD8FF", 216, 191, 216));
    TestColor(EXPAND_ARGS(tomato                 , Tomato               , "#FF6347", "0xFF6347", "0xFF6347FF", 255,  99,  71));
    TestColor(EXPAND_ARGS(turquoise              , Turquoise            , "#40E0D0", "0x40E0D0", "0x40E0D0FF",  64, 224, 208));
    TestColor(EXPAND_ARGS(violet                 , Violet               , "#EE82EE", "0xEE82EE", "0xEE82EEFF", 238, 130, 238));
    TestColor(EXPAND_ARGS(wheat                  , Wheat                , "#F5DEB3", "0xF5DEB3", "0xF5DEB3FF", 245, 222, 179));
    TestColor(EXPAND_ARGS(white                  , White                , "#FFFFFF", "0xFFFFFF", "0xFFFFFFFF", 255, 255, 255));
    TestColor(EXPAND_ARGS(white_smoke            , WhiteSmoke           , "#F5F5F5", "0xF5F5F5", "0xF5F5F5FF", 245, 245, 245));
    TestColor(EXPAND_ARGS(yellow                 , Yellow               , "#FFFF00", "0xFFFF00", "0xFFFF00FF", 255, 255,   0));
    TestColor(EXPAND_ARGS(yellow_green           , YellowGreen          , "#9ACD32", "0x9ACD32", "0x9ACD32FF", 154, 205,  50));
    // clang-format on
}

TEST(color, set)
{
    qx::color color(1.f, 1.f, 1.f, 1.f);
    TestColor(color, 255, 255, 255);

    color.set_r(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_g(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_b(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 1.f);

    color.set_a(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.set_r(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.set_g(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.set_b(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 0.5f);

    color.set_a(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_r(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_g(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_b(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_a(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 0.f);
}

TEST(color, set_dec)
{
    qx::color color(255, 255, 255, 255);
    TestColor(color);

    color.set_r_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_g_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_b_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_a_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.set_r_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.set_g_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.set_b_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 127);

    color.set_a_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_r_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_g_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_b_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_a_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 0);
}

TEST(color, update)
{
    qx::color color(0.f, 0.f, 0.f, 0.f);
    TestColor(color);

    color.update_r(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 0.f);

    color.update_g(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 0.f);

    color.update_b(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.f);

    color.update_a(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.update_r(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.update_g(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.update_b(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 0.5f);

    color.update_a(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.update_r(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.update_g(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.update_b(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 1.f);

    color.update_a(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 0.f);
}

TEST(color, update_dec)
{
    qx::color color(0, 0, 0, 0);
    TestColor(color);

    color.update_r_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 0);

    color.update_g_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 0);

    color.update_b_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 0);

    color.update_a_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.update_r_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.update_g_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.update_b_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 127);

    color.update_a_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.update_r_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.update_g_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.update_b_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 255);

    color.update_a_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 0);
}

TEST(color, format)
{
    qx::color color = qx::color::alice_blue();
    expect_equal(qx::string::static_format(QXT("{}"), color), qx::string(QXT("F0F8FFFF")));
    expect_equal(qx::string::static_format(QXT("{:s}"), color), qx::string(QXT("alice_blue")));
    expect_equal(qx::string::static_format(QXT("{:p}"), color), qx::string(QXT("AliceBlue")));
    expect_equal(qx::string::static_format(QXT("{:x}"), color), qx::string(QXT("f0f8ff")));
    expect_equal(qx::string::static_format(QXT("{:xa}"), color), qx::string(QXT("f0f8ffff")));
    expect_equal(qx::string::static_format(QXT("{:X}"), color), qx::string(QXT("F0F8FF")));
    expect_equal(qx::string::static_format(QXT("{:Xa}"), color), qx::string(QXT("F0F8FFFF")));
    expect_equal(qx::string::static_format(QXT("{:r}"), color), qx::string(QXT("240,248,255")));
    expect_equal(qx::string::static_format(QXT("{:ra}"), color), qx::string(QXT("240,248,255,255")));
}
