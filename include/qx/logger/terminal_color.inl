
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

constexpr terminal_color terminal_color::font(const color& color) noexcept
{
    return terminal_color { color, type::font };
}

constexpr terminal_color terminal_color::back(const color& color) noexcept
{
    return terminal_color { color, type::back };
}

constexpr terminal_color terminal_color::reset() noexcept
{
    return terminal_color { type::reset };
}

constexpr terminal_color::terminal_color(const color& color, type eType) noexcept : m_Color(color), m_eType(eType)
{
}

constexpr terminal_color::terminal_color(type eType) noexcept : m_eType(eType)
{
}

inline void terminal_color::test_colors()
{
    // clang-format off
    std::cout << font(qx::color::alice_blue()) << "alice_blue" << std::endl;
    std::cout << font(qx::color::antique_white()) << "antique_white" << std::endl;
    std::cout << font(qx::color::aqua()) << "aqua" << std::endl;
    std::cout << font(qx::color::aquamarine()) << "aquamarine" << std::endl;
    std::cout << font(qx::color::azure()) << "azure" << std::endl;
    std::cout << font(qx::color::beige()) << "beige" << std::endl;
    std::cout << font(qx::color::bisque()) << "bisque" << std::endl;
    std::cout << font(qx::color::black()) << "black" << std::endl;
    std::cout << font(qx::color::blanched_almond()) << "blanched_almond" << std::endl;
    std::cout << font(qx::color::blue()) << "blue" << std::endl;
    std::cout << font(qx::color::blue_violet()) << "blue_violet" << std::endl;
    std::cout << font(qx::color::brown()) << "brown" << std::endl;
    std::cout << font(qx::color::burly_wood()) << "burly_wood" << std::endl;
    std::cout << font(qx::color::cadet_blue()) << "cadet_blue" << std::endl;
    std::cout << font(qx::color::chartreuse()) << "chartreuse" << std::endl;
    std::cout << font(qx::color::chocolate()) << "chocolate" << std::endl;
    std::cout << font(qx::color::coral()) << "coral" << std::endl;
    std::cout << font(qx::color::cornflower_blue()) << "cornflower_blue" << std::endl;
    std::cout << font(qx::color::cornsilk()) << "cornsilk" << std::endl;
    std::cout << font(qx::color::crimson()) << "crimson" << std::endl;
    std::cout << font(qx::color::cyan()) << "cyan" << std::endl;
    std::cout << font(qx::color::dark_blue()) << "dark_blue" << std::endl;
    std::cout << font(qx::color::dark_cyan()) << "dark_cyan" << std::endl;
    std::cout << font(qx::color::dark_goldenrod()) << "dark_goldenrod" << std::endl;
    std::cout << font(qx::color::dark_gray()) << "dark_gray" << std::endl;
    std::cout << font(qx::color::dark_green()) << "dark_green" << std::endl;
    std::cout << font(qx::color::dark_khaki()) << "dark_khaki" << std::endl;
    std::cout << font(qx::color::dark_magenta()) << "dark_magenta" << std::endl;
    std::cout << font(qx::color::dark_olive_green()) << "dark_olive_green" << std::endl;
    std::cout << font(qx::color::dark_orange()) << "dark_orange" << std::endl;
    std::cout << font(qx::color::dark_orchid()) << "dark_orchid" << std::endl;
    std::cout << font(qx::color::dark_red()) << "dark_red" << std::endl;
    std::cout << font(qx::color::dark_salmon()) << "dark_salmon" << std::endl;
    std::cout << font(qx::color::dark_sea_green()) << "dark_sea_green" << std::endl;
    std::cout << font(qx::color::dark_slate_blue()) << "dark_slate_blue" << std::endl;
    std::cout << font(qx::color::dark_slate_gray()) << "dark_slate_gray" << std::endl;
    std::cout << font(qx::color::dark_turquoise()) << "dark_turquoise" << std::endl;
    std::cout << font(qx::color::dark_violet()) << "dark_violet" << std::endl;
    std::cout << font(qx::color::deep_pink()) << "deep_pink" << std::endl;
    std::cout << font(qx::color::deep_sky_blue()) << "deep_sky_blue" << std::endl;
    std::cout << font(qx::color::dim_gray()) << "dim_gray" << std::endl;
    std::cout << font(qx::color::dodger_blue()) << "dodger_blue" << std::endl;
    std::cout << font(qx::color::fire_brick()) << "fire_brick" << std::endl;
    std::cout << font(qx::color::floral_white()) << "floral_white" << std::endl;
    std::cout << font(qx::color::forest_green()) << "forest_green" << std::endl;
    std::cout << font(qx::color::fuchsia()) << "fuchsia" << std::endl;
    std::cout << font(qx::color::gainsboro()) << "gainsboro" << std::endl;
    std::cout << font(qx::color::ghost_white()) << "ghost_white" << std::endl;
    std::cout << font(qx::color::gold()) << "gold" << std::endl;
    std::cout << font(qx::color::goldenrod()) << "goldenrod" << std::endl;
    std::cout << font(qx::color::gray()) << "gray" << std::endl;
    std::cout << font(qx::color::green()) << "green" << std::endl;
    std::cout << font(qx::color::green_yellow()) << "green_yellow" << std::endl;
    std::cout << font(qx::color::honeydew()) << "honeydew" << std::endl;
    std::cout << font(qx::color::hot_pink()) << "hot_pink" << std::endl;
    std::cout << font(qx::color::indian_red()) << "indian_red" << std::endl;
    std::cout << font(qx::color::indigo()) << "indigo" << std::endl;
    std::cout << font(qx::color::ivory()) << "ivory" << std::endl;
    std::cout << font(qx::color::khaki()) << "khaki" << std::endl;
    std::cout << font(qx::color::lavender()) << "lavender" << std::endl;
    std::cout << font(qx::color::lavender_blush()) << "lavender_blush" << std::endl;
    std::cout << font(qx::color::lawn_green()) << "lawn_green" << std::endl;
    std::cout << font(qx::color::lemon_chiffon()) << "lemon_chiffon" << std::endl;
    std::cout << font(qx::color::light_blue()) << "light_blue" << std::endl;
    std::cout << font(qx::color::light_coral()) << "light_coral" << std::endl;
    std::cout << font(qx::color::light_cyan()) << "light_cyan" << std::endl;
    std::cout << font(qx::color::light_goldenrod_yellow()) << "light_goldenrod_yellow" << std::endl;
    std::cout << font(qx::color::light_green()) << "light_green" << std::endl;
    std::cout << font(qx::color::light_grey()) << "light_grey" << std::endl;
    std::cout << font(qx::color::light_pink()) << "light_pink" << std::endl;
    std::cout << font(qx::color::light_salmon()) << "light_salmon" << std::endl;
    std::cout << font(qx::color::light_sea_green()) << "light_sea_green" << std::endl;
    std::cout << font(qx::color::light_sky_blue()) << "light_sky_blue" << std::endl;
    std::cout << font(qx::color::light_slate_gray()) << "light_slate_gray" << std::endl;
    std::cout << font(qx::color::light_steel_blue()) << "light_steel_blue" << std::endl;
    std::cout << font(qx::color::light_yellow()) << "light_yellow" << std::endl;
    std::cout << font(qx::color::lime()) << "lime" << std::endl;
    std::cout << font(qx::color::lime_green()) << "lime_green" << std::endl;
    std::cout << font(qx::color::linen()) << "linen" << std::endl;
    std::cout << font(qx::color::magenta()) << "magenta" << std::endl;
    std::cout << font(qx::color::maroon()) << "maroon" << std::endl;
    std::cout << font(qx::color::medium_aquamarine()) << "medium_aquamarine" << std::endl;
    std::cout << font(qx::color::medium_blue()) << "medium_blue" << std::endl;
    std::cout << font(qx::color::medium_orchid()) << "medium_orchid" << std::endl;
    std::cout << font(qx::color::medium_purple()) << "medium_purple" << std::endl;
    std::cout << font(qx::color::medium_sea_green()) << "medium_sea_green" << std::endl;
    std::cout << font(qx::color::medium_slate_blue()) << "medium_slate_blue" << std::endl;
    std::cout << font(qx::color::medium_spring_green()) << "medium_spring_green" << std::endl;
    std::cout << font(qx::color::medium_turquoise()) << "medium_turquoise" << std::endl;
    std::cout << font(qx::color::medium_violet_red()) << "medium_violet_red" << std::endl;
    std::cout << font(qx::color::midnight_blue()) << "midnight_blue" << std::endl;
    std::cout << font(qx::color::mint_cream()) << "mint_cream" << std::endl;
    std::cout << font(qx::color::misty_rose()) << "misty_rose" << std::endl;
    std::cout << font(qx::color::moccasin()) << "moccasin" << std::endl;
    std::cout << font(qx::color::navajo_white()) << "navajo_white" << std::endl;
    std::cout << font(qx::color::navy()) << "navy" << std::endl;
    std::cout << font(qx::color::old_lace()) << "old_lace" << std::endl;
    std::cout << font(qx::color::olive()) << "olive" << std::endl;
    std::cout << font(qx::color::olive_drab()) << "olive_drab" << std::endl;
    std::cout << font(qx::color::orange()) << "orange" << std::endl;
    std::cout << font(qx::color::orange_red()) << "orange_red" << std::endl;
    std::cout << font(qx::color::orchid()) << "orchid" << std::endl;
    std::cout << font(qx::color::pale_goldenrod()) << "pale_goldenrod" << std::endl;
    std::cout << font(qx::color::pale_green()) << "pale_green" << std::endl;
    std::cout << font(qx::color::pale_turquoise()) << "pale_turquoise" << std::endl;
    std::cout << font(qx::color::pale_violet_red()) << "pale_violet_red" << std::endl;
    std::cout << font(qx::color::papaya_whip()) << "papaya_whip" << std::endl;
    std::cout << font(qx::color::peach_puff()) << "peach_puff" << std::endl;
    std::cout << font(qx::color::peru()) << "peru" << std::endl;
    std::cout << font(qx::color::pink()) << "pink" << std::endl;
    std::cout << font(qx::color::plum()) << "plum" << std::endl;
    std::cout << font(qx::color::powder_blue()) << "powder_blue" << std::endl;
    std::cout << font(qx::color::purple()) << "purple" << std::endl;
    std::cout << font(qx::color::red()) << "red" << std::endl;
    std::cout << font(qx::color::rosy_brown()) << "rosy_brown" << std::endl;
    std::cout << font(qx::color::royal_blue()) << "royal_blue" << std::endl;
    std::cout << font(qx::color::saddle_brown()) << "saddle_brown" << std::endl;
    std::cout << font(qx::color::salmon()) << "salmon" << std::endl;
    std::cout << font(qx::color::sandy_brown()) << "sandy_brown" << std::endl;
    std::cout << font(qx::color::sea_green()) << "sea_green" << std::endl;
    std::cout << font(qx::color::seashell()) << "seashell" << std::endl;
    std::cout << font(qx::color::sienna()) << "sienna" << std::endl;
    std::cout << font(qx::color::silver()) << "silver" << std::endl;
    std::cout << font(qx::color::sky_blue()) << "sky_blue" << std::endl;
    std::cout << font(qx::color::slate_blue()) << "slate_blue" << std::endl;
    std::cout << font(qx::color::slate_gray()) << "slate_gray" << std::endl;
    std::cout << font(qx::color::snow()) << "snow" << std::endl;
    std::cout << font(qx::color::spring_green()) << "spring_green" << std::endl;
    std::cout << font(qx::color::steel_blue()) << "steel_blue" << std::endl;
    std::cout << font(qx::color::tan()) << "tan" << std::endl;
    std::cout << font(qx::color::teal()) << "teal" << std::endl;
    std::cout << font(qx::color::thistle()) << "thistle" << std::endl;
    std::cout << font(qx::color::tomato()) << "tomato" << std::endl;
    std::cout << font(qx::color::turquoise()) << "turquoise" << std::endl;
    std::cout << font(qx::color::violet()) << "violet" << std::endl;
    std::cout << font(qx::color::wheat()) << "wheat" << std::endl;
    std::cout << font(qx::color::white()) << "white" << std::endl;
    std::cout << font(qx::color::white_smoke()) << "white_smoke" << std::endl;
    std::cout << font(qx::color::yellow()) << "yellow" << std::endl;
    std::cout << font(qx::color::yellow_green()) << "yellow_green" << std::endl;

    std::cout << reset();

    std::cout << font(qx::color::black()) << back(qx::color::alice_blue()) << "alice_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::antique_white()) << "antique_white" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::aqua()) << "aqua" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::aquamarine()) << "aquamarine" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::azure()) << "azure" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::beige()) << "beige" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::bisque()) << "bisque" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::black()) << "black" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::blanched_almond()) << "blanched_almond" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::blue()) << "blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::blue_violet()) << "blue_violet" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::brown()) << "brown" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::burly_wood()) << "burly_wood" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::cadet_blue()) << "cadet_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::chartreuse()) << "chartreuse" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::chocolate()) << "chocolate" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::coral()) << "coral" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::cornflower_blue()) << "cornflower_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::cornsilk()) << "cornsilk" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::crimson()) << "crimson" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::cyan()) << "cyan" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_blue()) << "dark_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_cyan()) << "dark_cyan" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_goldenrod()) << "dark_goldenrod" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_gray()) << "dark_gray" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_green()) << "dark_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_khaki()) << "dark_khaki" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_magenta()) << "dark_magenta" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_olive_green()) << "dark_olive_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_orange()) << "dark_orange" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_orchid()) << "dark_orchid" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_red()) << "dark_red" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_salmon()) << "dark_salmon" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_sea_green()) << "dark_sea_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_slate_blue()) << "dark_slate_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_slate_gray()) << "dark_slate_gray" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_turquoise()) << "dark_turquoise" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dark_violet()) << "dark_violet" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::deep_pink()) << "deep_pink" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::deep_sky_blue()) << "deep_sky_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dim_gray()) << "dim_gray" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::dodger_blue()) << "dodger_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::fire_brick()) << "fire_brick" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::floral_white()) << "floral_white" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::forest_green()) << "forest_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::fuchsia()) << "fuchsia" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::gainsboro()) << "gainsboro" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::ghost_white()) << "ghost_white" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::gold()) << "gold" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::goldenrod()) << "goldenrod" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::gray()) << "gray" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::green()) << "green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::green_yellow()) << "green_yellow" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::honeydew()) << "honeydew" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::hot_pink()) << "hot_pink" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::indian_red()) << "indian_red" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::indigo()) << "indigo" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::ivory()) << "ivory" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::khaki()) << "khaki" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::lavender()) << "lavender" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::lavender_blush()) << "lavender_blush" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::lawn_green()) << "lawn_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::lemon_chiffon()) << "lemon_chiffon" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_blue()) << "light_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_coral()) << "light_coral" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_cyan()) << "light_cyan" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_goldenrod_yellow()) << "light_goldenrod_yellow" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_green()) << "light_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_grey()) << "light_grey" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_pink()) << "light_pink" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_salmon()) << "light_salmon" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_sea_green()) << "light_sea_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_sky_blue()) << "light_sky_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_slate_gray()) << "light_slate_gray" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_steel_blue()) << "light_steel_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::light_yellow()) << "light_yellow" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::lime()) << "lime" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::lime_green()) << "lime_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::linen()) << "linen" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::magenta()) << "magenta" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::maroon()) << "maroon" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_aquamarine()) << "medium_aquamarine" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_blue()) << "medium_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_orchid()) << "medium_orchid" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_purple()) << "medium_purple" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_sea_green()) << "medium_sea_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_slate_blue()) << "medium_slate_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_spring_green()) << "medium_spring_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_turquoise()) << "medium_turquoise" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::medium_violet_red()) << "medium_violet_red" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::midnight_blue()) << "midnight_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::mint_cream()) << "mint_cream" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::misty_rose()) << "misty_rose" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::moccasin()) << "moccasin" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::navajo_white()) << "navajo_white" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::navy()) << "navy" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::old_lace()) << "old_lace" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::olive()) << "olive" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::olive_drab()) << "olive_drab" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::orange()) << "orange" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::orange_red()) << "orange_red" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::orchid()) << "orchid" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::pale_goldenrod()) << "pale_goldenrod" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::pale_green()) << "pale_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::pale_turquoise()) << "pale_turquoise" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::pale_violet_red()) << "pale_violet_red" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::papaya_whip()) << "papaya_whip" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::peach_puff()) << "peach_puff" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::peru()) << "peru" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::pink()) << "pink" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::plum()) << "plum" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::powder_blue()) << "powder_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::purple()) << "purple" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::red()) << "red" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::rosy_brown()) << "rosy_brown" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::royal_blue()) << "royal_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::saddle_brown()) << "saddle_brown" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::salmon()) << "salmon" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::sandy_brown()) << "sandy_brown" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::sea_green()) << "sea_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::seashell()) << "seashell" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::sienna()) << "sienna" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::silver()) << "silver" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::sky_blue()) << "sky_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::slate_blue()) << "slate_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::slate_gray()) << "slate_gray" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::snow()) << "snow" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::spring_green()) << "spring_green" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::steel_blue()) << "steel_blue" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::tan()) << "tan" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::teal()) << "teal" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::thistle()) << "thistle" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::tomato()) << "tomato" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::turquoise()) << "turquoise" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::violet()) << "violet" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::wheat()) << "wheat" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::white()) << "white" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::white_smoke()) << "white_smoke" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::yellow()) << "yellow" << reset() << std::endl;
    std::cout << font(qx::color::black()) << back(qx::color::yellow_green()) << "yellow_green" << reset() << std::endl;

    std::cout << reset();
    // clang-format on
}

} // namespace qx
