/**

    @file      terminal_color.inl
    @author    Khrapov
    @date      14.12.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

template<class char_type>
std::basic_ostream<char_type>& operator<<(std::basic_ostream<char_type>& os, const qx::terminal_color& terminalColor)
{
    auto& sBuffer = qx::static_buffer::get_instance().get_buffer<qx::basic_string<char_type>>();

    switch (terminalColor.m_eType)
    {
    case qx::terminal_color::type::font:
        sBuffer.sprintf(
            QX_STR_PREFIX(char_type, "\033[38;2;%d;%d;%dm"),
            terminalColor.m_Color.r_dec(),
            terminalColor.m_Color.g_dec(),
            terminalColor.m_Color.b_dec());
        break;

    case qx::terminal_color::type::back:
        sBuffer.sprintf(
            QX_STR_PREFIX(char_type, "\033[48;2;%d;%d;%dm"),
            terminalColor.m_Color.r_dec(),
            terminalColor.m_Color.g_dec(),
            terminalColor.m_Color.b_dec());
        break;

    case qx::terminal_color::type::reset:
        sBuffer = QX_STR_PREFIX(char_type, "\033[0m");
        break;
    }

    os << sBuffer;
    return os;
}

namespace qx
{

constexpr terminal_color terminal_color::font(const color& fontColor) noexcept
{
    return terminal_color { fontColor, type::font };
}

constexpr terminal_color terminal_color::back(const color& bgColor) noexcept
{
    return terminal_color { bgColor, type::back };
}

constexpr terminal_color terminal_color::reset() noexcept
{
    return terminal_color { type::reset };
}

constexpr terminal_color::terminal_color(const color& inColor, type eType) noexcept : m_Color(inColor), m_eType(eType)
{
}

constexpr terminal_color::terminal_color(type eType) noexcept : m_eType(eType)
{
}

inline void terminal_color::test_colors()
{
    using namespace std;

    cout << font(color::alice_blue()) << "alice_blue" << endl;
    cout << font(color::antique_white()) << "antique_white" << endl;
    cout << font(color::aqua()) << "aqua" << endl;
    cout << font(color::aquamarine()) << "aquamarine" << endl;
    cout << font(color::azure()) << "azure" << endl;
    cout << font(color::beige()) << "beige" << endl;
    cout << font(color::bisque()) << "bisque" << endl;
    cout << font(color::black()) << "black" << endl;
    cout << font(color::blanched_almond()) << "blanched_almond" << endl;
    cout << font(color::blue()) << "blue" << endl;
    cout << font(color::blue_violet()) << "blue_violet" << endl;
    cout << font(color::brown()) << "brown" << endl;
    cout << font(color::burly_wood()) << "burly_wood" << endl;
    cout << font(color::cadet_blue()) << "cadet_blue" << endl;
    cout << font(color::chartreuse()) << "chartreuse" << endl;
    cout << font(color::chocolate()) << "chocolate" << endl;
    cout << font(color::coral()) << "coral" << endl;
    cout << font(color::cornflower_blue()) << "cornflower_blue" << endl;
    cout << font(color::cornsilk()) << "cornsilk" << endl;
    cout << font(color::crimson()) << "crimson" << endl;
    cout << font(color::cyan()) << "cyan" << endl;
    cout << font(color::dark_blue()) << "dark_blue" << endl;
    cout << font(color::dark_cyan()) << "dark_cyan" << endl;
    cout << font(color::dark_goldenrod()) << "dark_goldenrod" << endl;
    cout << font(color::dark_gray()) << "dark_gray" << endl;
    cout << font(color::dark_green()) << "dark_green" << endl;
    cout << font(color::dark_khaki()) << "dark_khaki" << endl;
    cout << font(color::dark_magenta()) << "dark_magenta" << endl;
    cout << font(color::dark_olive_green()) << "dark_olive_green" << endl;
    cout << font(color::dark_orange()) << "dark_orange" << endl;
    cout << font(color::dark_orchid()) << "dark_orchid" << endl;
    cout << font(color::dark_red()) << "dark_red" << endl;
    cout << font(color::dark_salmon()) << "dark_salmon" << endl;
    cout << font(color::dark_sea_green()) << "dark_sea_green" << endl;
    cout << font(color::dark_slate_blue()) << "dark_slate_blue" << endl;
    cout << font(color::dark_slate_gray()) << "dark_slate_gray" << endl;
    cout << font(color::dark_turquoise()) << "dark_turquoise" << endl;
    cout << font(color::dark_violet()) << "dark_violet" << endl;
    cout << font(color::deep_pink()) << "deep_pink" << endl;
    cout << font(color::deep_sky_blue()) << "deep_sky_blue" << endl;
    cout << font(color::dim_gray()) << "dim_gray" << endl;
    cout << font(color::dodger_blue()) << "dodger_blue" << endl;
    cout << font(color::fire_brick()) << "fire_brick" << endl;
    cout << font(color::floral_white()) << "floral_white" << endl;
    cout << font(color::forest_green()) << "forest_green" << endl;
    cout << font(color::fuchsia()) << "fuchsia" << endl;
    cout << font(color::gainsboro()) << "gainsboro" << endl;
    cout << font(color::ghost_white()) << "ghost_white" << endl;
    cout << font(color::gold()) << "gold" << endl;
    cout << font(color::goldenrod()) << "goldenrod" << endl;
    cout << font(color::gray()) << "gray" << endl;
    cout << font(color::green()) << "green" << endl;
    cout << font(color::green_yellow()) << "green_yellow" << endl;
    cout << font(color::honeydew()) << "honeydew" << endl;
    cout << font(color::hot_pink()) << "hot_pink" << endl;
    cout << font(color::indian_red()) << "indian_red" << endl;
    cout << font(color::indigo()) << "indigo" << endl;
    cout << font(color::ivory()) << "ivory" << endl;
    cout << font(color::khaki()) << "khaki" << endl;
    cout << font(color::lavender()) << "lavender" << endl;
    cout << font(color::lavender_blush()) << "lavender_blush" << endl;
    cout << font(color::lawn_green()) << "lawn_green" << endl;
    cout << font(color::lemon_chiffon()) << "lemon_chiffon" << endl;
    cout << font(color::light_blue()) << "light_blue" << endl;
    cout << font(color::light_coral()) << "light_coral" << endl;
    cout << font(color::light_cyan()) << "light_cyan" << endl;
    cout << font(color::light_goldenrod_yellow()) << "light_goldenrod_yellow" << endl;
    cout << font(color::light_green()) << "light_green" << endl;
    cout << font(color::light_grey()) << "light_grey" << endl;
    cout << font(color::light_pink()) << "light_pink" << endl;
    cout << font(color::light_salmon()) << "light_salmon" << endl;
    cout << font(color::light_sea_green()) << "light_sea_green" << endl;
    cout << font(color::light_sky_blue()) << "light_sky_blue" << endl;
    cout << font(color::light_slate_gray()) << "light_slate_gray" << endl;
    cout << font(color::light_steel_blue()) << "light_steel_blue" << endl;
    cout << font(color::light_yellow()) << "light_yellow" << endl;
    cout << font(color::lime()) << "lime" << endl;
    cout << font(color::lime_green()) << "lime_green" << endl;
    cout << font(color::linen()) << "linen" << endl;
    cout << font(color::magenta()) << "magenta" << endl;
    cout << font(color::maroon()) << "maroon" << endl;
    cout << font(color::medium_aquamarine()) << "medium_aquamarine" << endl;
    cout << font(color::medium_blue()) << "medium_blue" << endl;
    cout << font(color::medium_orchid()) << "medium_orchid" << endl;
    cout << font(color::medium_purple()) << "medium_purple" << endl;
    cout << font(color::medium_sea_green()) << "medium_sea_green" << endl;
    cout << font(color::medium_slate_blue()) << "medium_slate_blue" << endl;
    cout << font(color::medium_spring_green()) << "medium_spring_green" << endl;
    cout << font(color::medium_turquoise()) << "medium_turquoise" << endl;
    cout << font(color::medium_violet_red()) << "medium_violet_red" << endl;
    cout << font(color::midnight_blue()) << "midnight_blue" << endl;
    cout << font(color::mint_cream()) << "mint_cream" << endl;
    cout << font(color::misty_rose()) << "misty_rose" << endl;
    cout << font(color::moccasin()) << "moccasin" << endl;
    cout << font(color::navajo_white()) << "navajo_white" << endl;
    cout << font(color::navy()) << "navy" << endl;
    cout << font(color::old_lace()) << "old_lace" << endl;
    cout << font(color::olive()) << "olive" << endl;
    cout << font(color::olive_drab()) << "olive_drab" << endl;
    cout << font(color::orange()) << "orange" << endl;
    cout << font(color::orange_red()) << "orange_red" << endl;
    cout << font(color::orchid()) << "orchid" << endl;
    cout << font(color::pale_goldenrod()) << "pale_goldenrod" << endl;
    cout << font(color::pale_green()) << "pale_green" << endl;
    cout << font(color::pale_turquoise()) << "pale_turquoise" << endl;
    cout << font(color::pale_violet_red()) << "pale_violet_red" << endl;
    cout << font(color::papaya_whip()) << "papaya_whip" << endl;
    cout << font(color::peach_puff()) << "peach_puff" << endl;
    cout << font(color::peru()) << "peru" << endl;
    cout << font(color::pink()) << "pink" << endl;
    cout << font(color::plum()) << "plum" << endl;
    cout << font(color::powder_blue()) << "powder_blue" << endl;
    cout << font(color::purple()) << "purple" << endl;
    cout << font(color::red()) << "red" << endl;
    cout << font(color::rosy_brown()) << "rosy_brown" << endl;
    cout << font(color::royal_blue()) << "royal_blue" << endl;
    cout << font(color::saddle_brown()) << "saddle_brown" << endl;
    cout << font(color::salmon()) << "salmon" << endl;
    cout << font(color::sandy_brown()) << "sandy_brown" << endl;
    cout << font(color::sea_green()) << "sea_green" << endl;
    cout << font(color::seashell()) << "seashell" << endl;
    cout << font(color::sienna()) << "sienna" << endl;
    cout << font(color::silver()) << "silver" << endl;
    cout << font(color::sky_blue()) << "sky_blue" << endl;
    cout << font(color::slate_blue()) << "slate_blue" << endl;
    cout << font(color::slate_gray()) << "slate_gray" << endl;
    cout << font(color::snow()) << "snow" << endl;
    cout << font(color::spring_green()) << "spring_green" << endl;
    cout << font(color::steel_blue()) << "steel_blue" << endl;
    cout << font(color::tan()) << "tan" << endl;
    cout << font(color::teal()) << "teal" << endl;
    cout << font(color::thistle()) << "thistle" << endl;
    cout << font(color::tomato()) << "tomato" << endl;
    cout << font(color::turquoise()) << "turquoise" << endl;
    cout << font(color::violet()) << "violet" << endl;
    cout << font(color::wheat()) << "wheat" << endl;
    cout << font(color::white()) << "white" << endl;
    cout << font(color::white_smoke()) << "white_smoke" << endl;
    cout << font(color::yellow()) << "yellow" << endl;
    cout << font(color::yellow_green()) << "yellow_green" << endl;

    cout << reset();

    cout << font(color::black()) << back(color::alice_blue()) << "alice_blue" << reset() << endl;
    cout << font(color::black()) << back(color::antique_white()) << "antique_white" << reset() << endl;
    cout << font(color::black()) << back(color::aqua()) << "aqua" << reset() << endl;
    cout << font(color::black()) << back(color::aquamarine()) << "aquamarine" << reset() << endl;
    cout << font(color::black()) << back(color::azure()) << "azure" << reset() << endl;
    cout << font(color::black()) << back(color::beige()) << "beige" << reset() << endl;
    cout << font(color::black()) << back(color::bisque()) << "bisque" << reset() << endl;
    cout << font(color::black()) << back(color::black()) << "black" << reset() << endl;
    cout << font(color::black()) << back(color::blanched_almond()) << "blanched_almond" << reset() << endl;
    cout << font(color::black()) << back(color::blue()) << "blue" << reset() << endl;
    cout << font(color::black()) << back(color::blue_violet()) << "blue_violet" << reset() << endl;
    cout << font(color::black()) << back(color::brown()) << "brown" << reset() << endl;
    cout << font(color::black()) << back(color::burly_wood()) << "burly_wood" << reset() << endl;
    cout << font(color::black()) << back(color::cadet_blue()) << "cadet_blue" << reset() << endl;
    cout << font(color::black()) << back(color::chartreuse()) << "chartreuse" << reset() << endl;
    cout << font(color::black()) << back(color::chocolate()) << "chocolate" << reset() << endl;
    cout << font(color::black()) << back(color::coral()) << "coral" << reset() << endl;
    cout << font(color::black()) << back(color::cornflower_blue()) << "cornflower_blue" << reset() << endl;
    cout << font(color::black()) << back(color::cornsilk()) << "cornsilk" << reset() << endl;
    cout << font(color::black()) << back(color::crimson()) << "crimson" << reset() << endl;
    cout << font(color::black()) << back(color::cyan()) << "cyan" << reset() << endl;
    cout << font(color::black()) << back(color::dark_blue()) << "dark_blue" << reset() << endl;
    cout << font(color::black()) << back(color::dark_cyan()) << "dark_cyan" << reset() << endl;
    cout << font(color::black()) << back(color::dark_goldenrod()) << "dark_goldenrod" << reset() << endl;
    cout << font(color::black()) << back(color::dark_gray()) << "dark_gray" << reset() << endl;
    cout << font(color::black()) << back(color::dark_green()) << "dark_green" << reset() << endl;
    cout << font(color::black()) << back(color::dark_khaki()) << "dark_khaki" << reset() << endl;
    cout << font(color::black()) << back(color::dark_magenta()) << "dark_magenta" << reset() << endl;
    cout << font(color::black()) << back(color::dark_olive_green()) << "dark_olive_green" << reset() << endl;
    cout << font(color::black()) << back(color::dark_orange()) << "dark_orange" << reset() << endl;
    cout << font(color::black()) << back(color::dark_orchid()) << "dark_orchid" << reset() << endl;
    cout << font(color::black()) << back(color::dark_red()) << "dark_red" << reset() << endl;
    cout << font(color::black()) << back(color::dark_salmon()) << "dark_salmon" << reset() << endl;
    cout << font(color::black()) << back(color::dark_sea_green()) << "dark_sea_green" << reset() << endl;
    cout << font(color::black()) << back(color::dark_slate_blue()) << "dark_slate_blue" << reset() << endl;
    cout << font(color::black()) << back(color::dark_slate_gray()) << "dark_slate_gray" << reset() << endl;
    cout << font(color::black()) << back(color::dark_turquoise()) << "dark_turquoise" << reset() << endl;
    cout << font(color::black()) << back(color::dark_violet()) << "dark_violet" << reset() << endl;
    cout << font(color::black()) << back(color::deep_pink()) << "deep_pink" << reset() << endl;
    cout << font(color::black()) << back(color::deep_sky_blue()) << "deep_sky_blue" << reset() << endl;
    cout << font(color::black()) << back(color::dim_gray()) << "dim_gray" << reset() << endl;
    cout << font(color::black()) << back(color::dodger_blue()) << "dodger_blue" << reset() << endl;
    cout << font(color::black()) << back(color::fire_brick()) << "fire_brick" << reset() << endl;
    cout << font(color::black()) << back(color::floral_white()) << "floral_white" << reset() << endl;
    cout << font(color::black()) << back(color::forest_green()) << "forest_green" << reset() << endl;
    cout << font(color::black()) << back(color::fuchsia()) << "fuchsia" << reset() << endl;
    cout << font(color::black()) << back(color::gainsboro()) << "gainsboro" << reset() << endl;
    cout << font(color::black()) << back(color::ghost_white()) << "ghost_white" << reset() << endl;
    cout << font(color::black()) << back(color::gold()) << "gold" << reset() << endl;
    cout << font(color::black()) << back(color::goldenrod()) << "goldenrod" << reset() << endl;
    cout << font(color::black()) << back(color::gray()) << "gray" << reset() << endl;
    cout << font(color::black()) << back(color::green()) << "green" << reset() << endl;
    cout << font(color::black()) << back(color::green_yellow()) << "green_yellow" << reset() << endl;
    cout << font(color::black()) << back(color::honeydew()) << "honeydew" << reset() << endl;
    cout << font(color::black()) << back(color::hot_pink()) << "hot_pink" << reset() << endl;
    cout << font(color::black()) << back(color::indian_red()) << "indian_red" << reset() << endl;
    cout << font(color::black()) << back(color::indigo()) << "indigo" << reset() << endl;
    cout << font(color::black()) << back(color::ivory()) << "ivory" << reset() << endl;
    cout << font(color::black()) << back(color::khaki()) << "khaki" << reset() << endl;
    cout << font(color::black()) << back(color::lavender()) << "lavender" << reset() << endl;
    cout << font(color::black()) << back(color::lavender_blush()) << "lavender_blush" << reset() << endl;
    cout << font(color::black()) << back(color::lawn_green()) << "lawn_green" << reset() << endl;
    cout << font(color::black()) << back(color::lemon_chiffon()) << "lemon_chiffon" << reset() << endl;
    cout << font(color::black()) << back(color::light_blue()) << "light_blue" << reset() << endl;
    cout << font(color::black()) << back(color::light_coral()) << "light_coral" << reset() << endl;
    cout << font(color::black()) << back(color::light_cyan()) << "light_cyan" << reset() << endl;
    cout << font(color::black()) << back(color::light_goldenrod_yellow()) << "light_goldenrod_yellow" << reset()
         << endl;
    cout << font(color::black()) << back(color::light_green()) << "light_green" << reset() << endl;
    cout << font(color::black()) << back(color::light_grey()) << "light_grey" << reset() << endl;
    cout << font(color::black()) << back(color::light_pink()) << "light_pink" << reset() << endl;
    cout << font(color::black()) << back(color::light_salmon()) << "light_salmon" << reset() << endl;
    cout << font(color::black()) << back(color::light_sea_green()) << "light_sea_green" << reset() << endl;
    cout << font(color::black()) << back(color::light_sky_blue()) << "light_sky_blue" << reset() << endl;
    cout << font(color::black()) << back(color::light_slate_gray()) << "light_slate_gray" << reset() << endl;
    cout << font(color::black()) << back(color::light_steel_blue()) << "light_steel_blue" << reset() << endl;
    cout << font(color::black()) << back(color::light_yellow()) << "light_yellow" << reset() << endl;
    cout << font(color::black()) << back(color::lime()) << "lime" << reset() << endl;
    cout << font(color::black()) << back(color::lime_green()) << "lime_green" << reset() << endl;
    cout << font(color::black()) << back(color::linen()) << "linen" << reset() << endl;
    cout << font(color::black()) << back(color::magenta()) << "magenta" << reset() << endl;
    cout << font(color::black()) << back(color::maroon()) << "maroon" << reset() << endl;
    cout << font(color::black()) << back(color::medium_aquamarine()) << "medium_aquamarine" << reset() << endl;
    cout << font(color::black()) << back(color::medium_blue()) << "medium_blue" << reset() << endl;
    cout << font(color::black()) << back(color::medium_orchid()) << "medium_orchid" << reset() << endl;
    cout << font(color::black()) << back(color::medium_purple()) << "medium_purple" << reset() << endl;
    cout << font(color::black()) << back(color::medium_sea_green()) << "medium_sea_green" << reset() << endl;
    cout << font(color::black()) << back(color::medium_slate_blue()) << "medium_slate_blue" << reset() << endl;
    cout << font(color::black()) << back(color::medium_spring_green()) << "medium_spring_green" << reset() << endl;
    cout << font(color::black()) << back(color::medium_turquoise()) << "medium_turquoise" << reset() << endl;
    cout << font(color::black()) << back(color::medium_violet_red()) << "medium_violet_red" << reset() << endl;
    cout << font(color::black()) << back(color::midnight_blue()) << "midnight_blue" << reset() << endl;
    cout << font(color::black()) << back(color::mint_cream()) << "mint_cream" << reset() << endl;
    cout << font(color::black()) << back(color::misty_rose()) << "misty_rose" << reset() << endl;
    cout << font(color::black()) << back(color::moccasin()) << "moccasin" << reset() << endl;
    cout << font(color::black()) << back(color::navajo_white()) << "navajo_white" << reset() << endl;
    cout << font(color::black()) << back(color::navy()) << "navy" << reset() << endl;
    cout << font(color::black()) << back(color::old_lace()) << "old_lace" << reset() << endl;
    cout << font(color::black()) << back(color::olive()) << "olive" << reset() << endl;
    cout << font(color::black()) << back(color::olive_drab()) << "olive_drab" << reset() << endl;
    cout << font(color::black()) << back(color::orange()) << "orange" << reset() << endl;
    cout << font(color::black()) << back(color::orange_red()) << "orange_red" << reset() << endl;
    cout << font(color::black()) << back(color::orchid()) << "orchid" << reset() << endl;
    cout << font(color::black()) << back(color::pale_goldenrod()) << "pale_goldenrod" << reset() << endl;
    cout << font(color::black()) << back(color::pale_green()) << "pale_green" << reset() << endl;
    cout << font(color::black()) << back(color::pale_turquoise()) << "pale_turquoise" << reset() << endl;
    cout << font(color::black()) << back(color::pale_violet_red()) << "pale_violet_red" << reset() << endl;
    cout << font(color::black()) << back(color::papaya_whip()) << "papaya_whip" << reset() << endl;
    cout << font(color::black()) << back(color::peach_puff()) << "peach_puff" << reset() << endl;
    cout << font(color::black()) << back(color::peru()) << "peru" << reset() << endl;
    cout << font(color::black()) << back(color::pink()) << "pink" << reset() << endl;
    cout << font(color::black()) << back(color::plum()) << "plum" << reset() << endl;
    cout << font(color::black()) << back(color::powder_blue()) << "powder_blue" << reset() << endl;
    cout << font(color::black()) << back(color::purple()) << "purple" << reset() << endl;
    cout << font(color::black()) << back(color::red()) << "red" << reset() << endl;
    cout << font(color::black()) << back(color::rosy_brown()) << "rosy_brown" << reset() << endl;
    cout << font(color::black()) << back(color::royal_blue()) << "royal_blue" << reset() << endl;
    cout << font(color::black()) << back(color::saddle_brown()) << "saddle_brown" << reset() << endl;
    cout << font(color::black()) << back(color::salmon()) << "salmon" << reset() << endl;
    cout << font(color::black()) << back(color::sandy_brown()) << "sandy_brown" << reset() << endl;
    cout << font(color::black()) << back(color::sea_green()) << "sea_green" << reset() << endl;
    cout << font(color::black()) << back(color::seashell()) << "seashell" << reset() << endl;
    cout << font(color::black()) << back(color::sienna()) << "sienna" << reset() << endl;
    cout << font(color::black()) << back(color::silver()) << "silver" << reset() << endl;
    cout << font(color::black()) << back(color::sky_blue()) << "sky_blue" << reset() << endl;
    cout << font(color::black()) << back(color::slate_blue()) << "slate_blue" << reset() << endl;
    cout << font(color::black()) << back(color::slate_gray()) << "slate_gray" << reset() << endl;
    cout << font(color::black()) << back(color::snow()) << "snow" << reset() << endl;
    cout << font(color::black()) << back(color::spring_green()) << "spring_green" << reset() << endl;
    cout << font(color::black()) << back(color::steel_blue()) << "steel_blue" << reset() << endl;
    cout << font(color::black()) << back(color::tan()) << "tan" << reset() << endl;
    cout << font(color::black()) << back(color::teal()) << "teal" << reset() << endl;
    cout << font(color::black()) << back(color::thistle()) << "thistle" << reset() << endl;
    cout << font(color::black()) << back(color::tomato()) << "tomato" << reset() << endl;
    cout << font(color::black()) << back(color::turquoise()) << "turquoise" << reset() << endl;
    cout << font(color::black()) << back(color::violet()) << "violet" << reset() << endl;
    cout << font(color::black()) << back(color::wheat()) << "wheat" << reset() << endl;
    cout << font(color::black()) << back(color::white()) << "white" << reset() << endl;
    cout << font(color::black()) << back(color::white_smoke()) << "white_smoke" << reset() << endl;
    cout << font(color::black()) << back(color::yellow()) << "yellow" << reset() << endl;
    cout << font(color::black()) << back(color::yellow_green()) << "yellow_green" << reset() << endl;

    cout << reset();
}

} // namespace qx
