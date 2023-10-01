/**

    @file      string_view.h
    @author    Khrapov
    @date      11.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_setup.h>

#include <string_view>

namespace qx
{

// the string views are to be replaced with our own type
template<class... args_t>
using basic_string_view = std::basic_string_view<args_t...>;

using cstring_view = basic_string_view<char>;
using wstring_view = basic_string_view<wchar_t>;
using string_view  = basic_string_view<char_type>;

} // namespace qx
