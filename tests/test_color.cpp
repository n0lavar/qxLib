/**

    @file      test_color.cpp
    @author    Khrapov
    @date      16.07.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

#include <common.h>

//V_EXCLUDE_PATH *test_color.cpp

#include <qx/math/common.h>
#include <qx/render/color.h>

template<class... Args>
void TestColor(const qx::color& color, const Args&... args)
{
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

#define EXPAND_ARGS(snakeName, pascalName, lowerName, hashName, name0x, name0xXX)                                 \
    qx::color::snakeName(), #snakeName, L## #snakeName, #pascalName, L## #pascalName, #lowerName, L## #lowerName, \
        hashName, L##hashName, name0x, L##name0x, name0xXX, L##name0xXX

TEST(color, colors)
{
    // clang-format off
    TestColor(qx::color());
    TestColor(EXPAND_ARGS(alice_blue             , AliceBlue            , aliceblue            , "#F0F8FF", "0xF0F8FF", "0xF0F8FFFF"));
    TestColor(EXPAND_ARGS(antique_white          , AntiqueWhite         , antiquewhite         , "#FAEBD7", "0xFAEBD7", "0xFAEBD7FF"));
    TestColor(EXPAND_ARGS(aqua                   , Aqua                 , aqua                 , "#00FFFF", "0x00FFFF", "0x00FFFFFF"));
    TestColor(EXPAND_ARGS(aquamarine             , Aquamarine           , aquamarine           , "#7FFFD4", "0x7FFFD4", "0x7FFFD4FF"));
    TestColor(EXPAND_ARGS(azure                  , Azure                , azure                , "#F0FFFF", "0xF0FFFF", "0xF0FFFFFF"));
    TestColor(EXPAND_ARGS(beige                  , Beige                , beige                , "#F5F5DC", "0xF5F5DC", "0xF5F5DCFF"));
    TestColor(EXPAND_ARGS(bisque                 , Bisque               , bisque               , "#FFE4C4", "0xFFE4C4", "0xFFE4C4FF"));
    TestColor(EXPAND_ARGS(black                  , Black                , black                , "#000000", "0x000000", "0x000000FF"));
    TestColor(EXPAND_ARGS(blanched_almond        , BlanchedAlmond       , blanchedalmond       , "#FFEBCD", "0xFFEBCD", "0xFFEBCDFF"));
    TestColor(EXPAND_ARGS(blue                   , Blue                 , blue                 , "#0000FF", "0x0000FF", "0x0000FFFF"));
    TestColor(EXPAND_ARGS(blue_violet            , BlueViolet           , blueviolet           , "#8A2BE2", "0x8A2BE2", "0x8A2BE2FF"));
    TestColor(EXPAND_ARGS(brown                  , Brown                , brown                , "#A52A2A", "0xA52A2A", "0xA52A2AFF"));
    TestColor(EXPAND_ARGS(burly_wood             , BurlyWood            , burlywood            , "#DEB887", "0xDEB887", "0xDEB887FF"));
    TestColor(EXPAND_ARGS(cadet_blue             , CadetBlue            , cadetblue            , "#5F9EA0", "0x5F9EA0", "0x5F9EA0FF"));
    TestColor(EXPAND_ARGS(chartreuse             , Chartreuse           , chartreuse           , "#7FFF00", "0x7FFF00", "0x7FFF00FF"));
    TestColor(EXPAND_ARGS(chocolate              , Chocolate            , chocolate            , "#D2691E", "0xD2691E", "0xD2691EFF"));
    TestColor(EXPAND_ARGS(coral                  , Coral                , coral                , "#FF7F50", "0xFF7F50", "0xFF7F50FF"));
    TestColor(EXPAND_ARGS(cornflower_blue        , CornflowerBlue       , cornflowerblue       , "#6495ED", "0x6495ED", "0x6495EDFF"));
    TestColor(EXPAND_ARGS(cornsilk               , Cornsilk             , cornsilk             , "#FFF8DC", "0xFFF8DC", "0xFFF8DCFF"));
    TestColor(EXPAND_ARGS(crimson                , Crimson              , crimson              , "#DC143C", "0xDC143C", "0xDC143CFF"));
    TestColor(EXPAND_ARGS(cyan                   , Cyan                 , cyan                 , "#00FFFF", "0x00FFFF", "0x00FFFFFF"));
    TestColor(EXPAND_ARGS(dark_blue              , DarkBlue             , darkblue             , "#00008B", "0x00008B", "0x00008BFF"));
    TestColor(EXPAND_ARGS(dark_cyan              , DarkCyan             , darkcyan             , "#008B8B", "0x008B8B", "0x008B8BFF"));
    TestColor(EXPAND_ARGS(dark_goldenrod         , DarkGoldenrod        , darkgoldenrod        , "#B8860B", "0xB8860B", "0xB8860BFF"));
    TestColor(EXPAND_ARGS(dark_gray              , DarkGray             , darkgray             , "#A9A9A9", "0xA9A9A9", "0xA9A9A9FF"));
    TestColor(EXPAND_ARGS(dark_green             , DarkGreen            , darkgreen            , "#006400", "0x006400", "0x006400FF"));
    TestColor(EXPAND_ARGS(dark_khaki             , DarkKhaki            , darkkhaki            , "#BDB76B", "0xBDB76B", "0xBDB76BFF"));
    TestColor(EXPAND_ARGS(dark_magenta           , DarkMagenta          , darkmagenta          , "#8B008B", "0x8B008B", "0x8B008BFF"));
    TestColor(EXPAND_ARGS(dark_olive_green       , DarkOliveGreen       , darkolivegreen       , "#556B2F", "0x556B2F", "0x556B2FFF"));
    TestColor(EXPAND_ARGS(dark_orange            , DarkOrange           , darkorange           , "#FF8C00", "0xFF8C00", "0xFF8C00FF"));
    TestColor(EXPAND_ARGS(dark_orchid            , DarkOrchid           , darkorchid           , "#9932CC", "0x9932CC", "0x9932CCFF"));
    TestColor(EXPAND_ARGS(dark_red               , DarkRed              , darkred              , "#8B0000", "0x8B0000", "0x8B0000FF"));
    TestColor(EXPAND_ARGS(dark_salmon            , DarkSalmon           , darksalmon           , "#E9967A", "0xE9967A", "0xE9967AFF"));
    TestColor(EXPAND_ARGS(dark_sea_green         , DarkSeaGreen         , darkseagreen         , "#8FBC8F", "0x8FBC8F", "0x8FBC8FFF"));
    TestColor(EXPAND_ARGS(dark_slate_blue        , DarkSlateBlue        , darkslateblue        , "#483D8B", "0x483D8B", "0x483D8BFF"));
    TestColor(EXPAND_ARGS(dark_slate_gray        , DarkSlateGray        , darkslategray        , "#2F4F4F", "0x2F4F4F", "0x2F4F4FFF"));
    TestColor(EXPAND_ARGS(dark_turquoise         , DarkTurquoise        , darkturquoise        , "#00CED1", "0x00CED1", "0x00CED1FF"));
    TestColor(EXPAND_ARGS(dark_violet            , DarkViolet           , darkviolet           , "#9400D3", "0x9400D3", "0x9400D3FF"));
    TestColor(EXPAND_ARGS(deep_pink              , DeepPink             , deeppink             , "#FF1493", "0xFF1493", "0xFF1493FF"));
    TestColor(EXPAND_ARGS(deep_sky_blue          , DeepSkyBlue          , deepskyblue          , "#00BFFF", "0x00BFFF", "0x00BFFFFF"));
    TestColor(EXPAND_ARGS(dim_gray               , DimGray              , dimgray              , "#696969", "0x696969", "0x696969FF"));
    TestColor(EXPAND_ARGS(dodger_blue            , DodgerBlue           , dodgerblue           , "#1E90FF", "0x1E90FF", "0x1E90FFFF"));
    TestColor(EXPAND_ARGS(fire_brick             , FireBrick            , firebrick            , "#B22222", "0xB22222", "0xB22222FF"));
    TestColor(EXPAND_ARGS(floral_white           , FloralWhite          , floralwhite          , "#FFFAF0", "0xFFFAF0", "0xFFFAF0FF"));
    TestColor(EXPAND_ARGS(forest_green           , ForestGreen          , forestgreen          , "#228B22", "0x228B22", "0x228B22FF"));
    TestColor(EXPAND_ARGS(fuchsia                , Fuchsia              , fuchsia              , "#FF00FF", "0xFF00FF", "0xFF00FFFF"));
    TestColor(EXPAND_ARGS(gainsboro              , Gainsboro            , gainsboro            , "#DCDCDC", "0xDCDCDC", "0xDCDCDCFF"));
    TestColor(EXPAND_ARGS(ghost_white            , GhostWhite           , ghostwhite           , "#F8F8FF", "0xF8F8FF", "0xF8F8FFFF"));
    TestColor(EXPAND_ARGS(gold                   , Gold                 , gold                 , "#FFD700", "0xFFD700", "0xFFD700FF"));
    TestColor(EXPAND_ARGS(goldenrod              , Goldenrod            , goldenrod            , "#DAA520", "0xDAA520", "0xDAA520FF"));
    TestColor(EXPAND_ARGS(gray                   , Gray                 , gray                 , "#808080", "0x808080", "0x808080FF"));
    TestColor(EXPAND_ARGS(green                  , Green                , green                , "#008000", "0x008000", "0x008000FF"));
    TestColor(EXPAND_ARGS(green_yellow           , GreenYellow          , greenyellow          , "#ADFF2F", "0xADFF2F", "0xADFF2FFF"));
    TestColor(EXPAND_ARGS(honeydew               , Honeydew             , honeydew             , "#F0FFF0", "0xF0FFF0", "0xF0FFF0FF"));
    TestColor(EXPAND_ARGS(hot_pink               , HotPink              , hotpink              , "#FF69B4", "0xFF69B4", "0xFF69B4FF"));
    TestColor(EXPAND_ARGS(indian_red             , IndianRed            , indianred            , "#CD5C5C", "0xCD5C5C", "0xCD5C5CFF"));
    TestColor(EXPAND_ARGS(indigo                 , Indigo               , indigo               , "#4B0082", "0x4B0082", "0x4B0082FF"));
    TestColor(EXPAND_ARGS(ivory                  , Ivory                , ivory                , "#FFFFF0", "0xFFFFF0", "0xFFFFF0FF"));
    TestColor(EXPAND_ARGS(khaki                  , Khaki                , khaki                , "#F0E68C", "0xF0E68C", "0xF0E68CFF"));
    TestColor(EXPAND_ARGS(lavender               , Lavender             , lavender             , "#E6E6FA", "0xE6E6FA", "0xE6E6FAFF"));
    TestColor(EXPAND_ARGS(lavender_blush         , LavenderBlush        , lavenderblush        , "#FFF0F5", "0xFFF0F5", "0xFFF0F5FF"));
    TestColor(EXPAND_ARGS(lawn_green             , LawnGreen            , lawngreen            , "#7CFC00", "0x7CFC00", "0x7CFC00FF"));
    TestColor(EXPAND_ARGS(lemon_chiffon          , LemonChiffon         , lemonchiffon         , "#FFFACD", "0xFFFACD", "0xFFFACDFF"));
    TestColor(EXPAND_ARGS(light_blue             , LightBlue            , lightblue            , "#ADD8E6", "0xADD8E6", "0xADD8E6FF"));
    TestColor(EXPAND_ARGS(light_coral            , LightCoral           , lightcoral           , "#F08080", "0xF08080", "0xF08080FF"));
    TestColor(EXPAND_ARGS(light_cyan             , LightCyan            , lightcyan            , "#E0FFFF", "0xE0FFFF", "0xE0FFFFFF"));
    TestColor(EXPAND_ARGS(light_goldenrod_yellow , LightGoldenrodYellow , lightgoldenrodyellow , "#FAFAD2", "0xFAFAD2", "0xFAFAD2FF"));
    TestColor(EXPAND_ARGS(light_green            , LightGreen           , lightgreen           , "#90EE90", "0x90EE90", "0x90EE90FF"));
    TestColor(EXPAND_ARGS(light_grey             , LightGrey            , lightgrey            , "#D3D3D3", "0xD3D3D3", "0xD3D3D3FF"));
    TestColor(EXPAND_ARGS(light_pink             , LightPink            , lightpink            , "#FFB6C1", "0xFFB6C1", "0xFFB6C1FF"));
    TestColor(EXPAND_ARGS(light_salmon           , LightSalmon          , lightsalmon          , "#FFA07A", "0xFFA07A", "0xFFA07AFF"));
    TestColor(EXPAND_ARGS(light_sea_green        , LightSeaGreen        , lightseagreen        , "#20B2AA", "0x20B2AA", "0x20B2AAFF"));
    TestColor(EXPAND_ARGS(light_sky_blue         , LightSkyBlue         , lightskyblue         , "#87CEFA", "0x87CEFA", "0x87CEFAFF"));
    TestColor(EXPAND_ARGS(light_slate_gray       , LightSlateGray       , lightslategray       , "#778899", "0x778899", "0x778899FF"));
    TestColor(EXPAND_ARGS(light_steel_blue       , LightSteelBlue       , lightsteelblue       , "#B0C4DE", "0xB0C4DE", "0xB0C4DEFF"));
    TestColor(EXPAND_ARGS(light_yellow           , LightYellow          , lightyellow          , "#FFFFE0", "0xFFFFE0", "0xFFFFE0FF"));
    TestColor(EXPAND_ARGS(lime                   , Lime                 , lime                 , "#00FF00", "0x00FF00", "0x00FF00FF"));
    TestColor(EXPAND_ARGS(lime_green             , LimeGreen            , limegreen            , "#32CD32", "0x32CD32", "0x32CD32FF"));
    TestColor(EXPAND_ARGS(linen                  , Linen                , linen                , "#FAF0E6", "0xFAF0E6", "0xFAF0E6FF"));
    TestColor(EXPAND_ARGS(magenta                , Magenta              , magenta              , "#FF00FF", "0xFF00FF", "0xFF00FFFF"));
    TestColor(EXPAND_ARGS(maroon                 , Maroon               , maroon               , "#800000", "0x800000", "0x800000FF"));
    TestColor(EXPAND_ARGS(medium_aquamarine      , MediumAquamarine     , mediumaquamarine     , "#66CDAA", "0x66CDAA", "0x66CDAAFF"));
    TestColor(EXPAND_ARGS(medium_blue            , MediumBlue           , mediumblue           , "#0000CD", "0x0000CD", "0x0000CDFF"));
    TestColor(EXPAND_ARGS(medium_orchid          , MediumOrchid         , mediumorchid         , "#BA55D3", "0xBA55D3", "0xBA55D3FF"));
    TestColor(EXPAND_ARGS(medium_purple          , MediumPurple         , mediumpurple         , "#9370DB", "0x9370DB", "0x9370DBFF"));
    TestColor(EXPAND_ARGS(medium_sea_green       , MediumSeaGreen       , mediumseagreen       , "#3CB371", "0x3CB371", "0x3CB371FF"));
    TestColor(EXPAND_ARGS(medium_slate_blue      , MediumSlateBlue      , mediumslateblue      , "#7B68EE", "0x7B68EE", "0x7B68EEFF"));
    TestColor(EXPAND_ARGS(medium_spring_green    , MediumSpringGreen    , mediumspringgreen    , "#00FA9A", "0x00FA9A", "0x00FA9AFF"));
    TestColor(EXPAND_ARGS(medium_turquoise       , MediumTurquoise      , mediumturquoise      , "#48D1CC", "0x48D1CC", "0x48D1CCFF"));
    TestColor(EXPAND_ARGS(medium_violet_red      , MediumVioletRed      , mediumvioletred      , "#C71585", "0xC71585", "0xC71585FF"));
    TestColor(EXPAND_ARGS(midnight_blue          , MidnightBlue         , midnightblue         , "#191970", "0x191970", "0x191970FF"));
    TestColor(EXPAND_ARGS(mint_cream             , MintCream            , mintcream            , "#F5FFFA", "0xF5FFFA", "0xF5FFFAFF"));
    TestColor(EXPAND_ARGS(misty_rose             , MistyRose            , mistyrose            , "#FFE4E1", "0xFFE4E1", "0xFFE4E1FF"));
    TestColor(EXPAND_ARGS(moccasin               , Moccasin             , moccasin             , "#FFE4B5", "0xFFE4B5", "0xFFE4B5FF"));
    TestColor(EXPAND_ARGS(navajo_white           , NavajoWhite          , navajowhite          , "#FFDEAD", "0xFFDEAD", "0xFFDEADFF"));
    TestColor(EXPAND_ARGS(navy                   , Navy                 , navy                 , "#000080", "0x000080", "0x000080FF"));
    TestColor(EXPAND_ARGS(old_lace               , OldLace              , oldlace              , "#FDF5E6", "0xFDF5E6", "0xFDF5E6FF"));
    TestColor(EXPAND_ARGS(olive                  , Olive                , olive                , "#808000", "0x808000", "0x808000FF"));
    TestColor(EXPAND_ARGS(olive_drab             , OliveDrab            , olivedrab            , "#6B8E23", "0x6B8E23", "0x6B8E23FF"));
    TestColor(EXPAND_ARGS(orange                 , Orange               , orange               , "#FFA500", "0xFFA500", "0xFFA500FF"));
    TestColor(EXPAND_ARGS(orange_red             , OrangeRed            , orangered            , "#FF4500", "0xFF4500", "0xFF4500FF"));
    TestColor(EXPAND_ARGS(orchid                 , Orchid               , orchid               , "#DA70D6", "0xDA70D6", "0xDA70D6FF"));
    TestColor(EXPAND_ARGS(pale_goldenrod         , PaleGoldenrod        , palegoldenrod        , "#EEE8AA", "0xEEE8AA", "0xEEE8AAFF"));
    TestColor(EXPAND_ARGS(pale_green             , PaleGreen            , palegreen            , "#98FB98", "0x98FB98", "0x98FB98FF"));
    TestColor(EXPAND_ARGS(pale_turquoise         , PaleTurquoise        , paleturquoise        , "#AFEEEE", "0xAFEEEE", "0xAFEEEEFF"));
    TestColor(EXPAND_ARGS(pale_violet_red        , PaleVioletRed        , palevioletred        , "#DB7093", "0xDB7093", "0xDB7093FF"));
    TestColor(EXPAND_ARGS(papaya_whip            , PapayaWhip           , papayawhip           , "#FFEFD5", "0xFFEFD5", "0xFFEFD5FF"));
    TestColor(EXPAND_ARGS(peach_puff             , PeachPuff            , peachpuff            , "#FFDAB9", "0xFFDAB9", "0xFFDAB9FF"));
    TestColor(EXPAND_ARGS(peru                   , Peru                 , peru                 , "#CD853F", "0xCD853F", "0xCD853FFF"));
    TestColor(EXPAND_ARGS(pink                   , Pink                 , pink                 , "#FFC0CB", "0xFFC0CB", "0xFFC0CBFF"));
    TestColor(EXPAND_ARGS(plum                   , Plum                 , plum                 , "#DDA0DD", "0xDDA0DD", "0xDDA0DDFF"));
    TestColor(EXPAND_ARGS(powder_blue            , PowderBlue           , powderblue           , "#B0E0E6", "0xB0E0E6", "0xB0E0E6FF"));
    TestColor(EXPAND_ARGS(purple                 , Purple               , purple               , "#800080", "0x800080", "0x800080FF"));
    TestColor(EXPAND_ARGS(red                    , Red                  , red                  , "#FF0000", "0xFF0000", "0xFF0000FF"));
    TestColor(EXPAND_ARGS(rosy_brown             , RosyBrown            , rosybrown            , "#BC8F8F", "0xBC8F8F", "0xBC8F8FFF"));
    TestColor(EXPAND_ARGS(royal_blue             , RoyalBlue            , royalblue            , "#4169E1", "0x4169E1", "0x4169E1FF"));
    TestColor(EXPAND_ARGS(saddle_brown           , SaddleBrown          , saddlebrown          , "#8B4513", "0x8B4513", "0x8B4513FF"));
    TestColor(EXPAND_ARGS(salmon                 , Salmon               , salmon               , "#FA8072", "0xFA8072", "0xFA8072FF"));
    TestColor(EXPAND_ARGS(sandy_brown            , SandyBrown           , sandybrown           , "#F4A460", "0xF4A460", "0xF4A460FF"));
    TestColor(EXPAND_ARGS(sea_green              , SeaGreen             , seagreen             , "#2E8B57", "0x2E8B57", "0x2E8B57FF"));
    TestColor(EXPAND_ARGS(seashell               , Seashell             , seashell             , "#FFF5EE", "0xFFF5EE", "0xFFF5EEFF"));
    TestColor(EXPAND_ARGS(sienna                 , Sienna               , sienna               , "#A0522D", "0xA0522D", "0xA0522DFF"));
    TestColor(EXPAND_ARGS(silver                 , Silver               , silver               , "#C0C0C0", "0xC0C0C0", "0xC0C0C0FF"));
    TestColor(EXPAND_ARGS(sky_blue               , SkyBlue              , skyblue              , "#87CEEB", "0x87CEEB", "0x87CEEBFF"));
    TestColor(EXPAND_ARGS(slate_blue             , SlateBlue            , slateblue            , "#6A5ACD", "0x6A5ACD", "0x6A5ACDFF"));
    TestColor(EXPAND_ARGS(slate_gray             , SlateGray            , slategray            , "#708090", "0x708090", "0x708090FF"));
    TestColor(EXPAND_ARGS(snow                   , Snow                 , snow                 , "#FFFAFA", "0xFFFAFA", "0xFFFAFAFF"));
    TestColor(EXPAND_ARGS(spring_green           , SpringGreen          , springgreen          , "#00FF7F", "0x00FF7F", "0x00FF7FFF"));
    TestColor(EXPAND_ARGS(steel_blue             , SteelBlue            , steelblue            , "#4682B4", "0x4682B4", "0x4682B4FF"));
    TestColor(EXPAND_ARGS(tan                    , Tan                  , tan                  , "#D2B48C", "0xD2B48C", "0xD2B48CFF"));
    TestColor(EXPAND_ARGS(teal                   , Teal                 , teal                 , "#008080", "0x008080", "0x008080FF"));
    TestColor(EXPAND_ARGS(thistle                , Thistle              , thistle              , "#D8BFD8", "0xD8BFD8", "0xD8BFD8FF"));
    TestColor(EXPAND_ARGS(tomato                 , Tomato               , tomato               , "#FF6347", "0xFF6347", "0xFF6347FF"));
    TestColor(EXPAND_ARGS(turquoise              , Turquoise            , turquoise            , "#40E0D0", "0x40E0D0", "0x40E0D0FF"));
    TestColor(EXPAND_ARGS(violet                 , Violet               , violet               , "#EE82EE", "0xEE82EE", "0xEE82EEFF"));
    TestColor(EXPAND_ARGS(wheat                  , Wheat                , wheat                , "#F5DEB3", "0xF5DEB3", "0xF5DEB3FF"));
    TestColor(EXPAND_ARGS(white                  , White                , white                , "#FFFFFF", "0xFFFFFF", "0xFFFFFFFF"));
    TestColor(EXPAND_ARGS(white_smoke            , WhiteSmoke           , whitesmoke           , "#F5F5F5", "0xF5F5F5", "0xF5F5F5FF"));
    TestColor(EXPAND_ARGS(yellow                 , Yellow               , yellow               , "#FFFF00", "0xFFFF00", "0xFFFF00FF"));
    TestColor(EXPAND_ARGS(yellow_green           , YellowGreen          , yellowgreen          , "#9ACD32", "0x9ACD32", "0x9ACD32FF"));
    // clang-format on
}

TEST(color, set)
{
    qx::color color(1.f, 1.f, 1.f, 1.f);
    TestColor(color);

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
