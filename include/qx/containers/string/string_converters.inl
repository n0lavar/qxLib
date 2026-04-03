/**

    @file      string_converters.inl
    @author    Khrapov
    @date      11.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

QX_SET_FILE_CATEGORY(CatQxConverters);

namespace qx
{

inline void to_wstring(wstring& out, cstring_view stringView, const std::locale& locale)
{
    QX_PERF_SCOPE();

    out.assign(stringView.size(), L'\0');
    std::use_facet<std::ctype<wchar_t>>(locale).widen(
        stringView.data(),
        stringView.data() + stringView.size(),
        out.data());
}

inline wstring to_wstring(cstring_view stringView, const std::locale& locale)
{
    wstring result;
    to_wstring(result, stringView, locale);
    return result;
}

inline void to_wstring(wstring& out, wstring_view stringView, const std::locale& locale)
{
    out = stringView;
}

inline wstring_view to_wstring(wstring_view stringView, const std::locale& locale)
{
    return stringView;
}

inline void to_cstring(cstring& out, wstring_view stringView, const std::locale& locale)
{
    QX_PERF_SCOPE();

    out.assign(stringView.size(), '\0');
    std::use_facet<std::ctype<wchar_t>>(locale)
        .narrow(stringView.data(), stringView.data() + stringView.size(), '?', out.data());
}

inline cstring to_cstring(wstring_view stringView, const std::locale& locale)
{
    cstring result;
    to_cstring(result, stringView, locale);
    return result;
}

inline void to_cstring(cstring& out, cstring_view stringView, const std::locale& locale)
{
    out = stringView;
}

inline cstring_view to_cstring(cstring_view stringView, const std::locale& locale)
{
    return stringView;
}

inline void to_string(string& out, cstring_view stringView, const std::locale& locale)
{
#if QX_CONF_CHAR == QX_CHAR_T_CHAR
    out = stringView;
#elif QX_CONF_CHAR == QX_CHAR_T_WCHAR_T
    to_wstring(out, stringView, locale);
#else
    #error Unsupported char type
#endif
}

inline string to_string(cstring_view stringView, const std::locale& locale)
{
#if QX_CONF_CHAR == QX_CHAR_T_CHAR
    return stringView;
#elif QX_CONF_CHAR == QX_CHAR_T_WCHAR_T
    return to_wstring(stringView, locale);
#else
    #error Unsupported char type
#endif
}

inline void to_string(string& out, wstring_view stringView, const std::locale& locale)
{
#if QX_CONF_CHAR == QX_CHAR_T_CHAR
    to_cstring(out, stringView, locale);
#elif QX_CONF_CHAR == QX_CHAR_T_WCHAR_T
    out = stringView;
#else
    #error Unsupported char type
#endif
}

inline string to_string(wstring_view stringView, const std::locale& locale)
{
#if QX_CONF_CHAR == QX_CHAR_T_CHAR
    return to_cstring(stringView, locale);
#elif QX_CONF_CHAR == QX_CHAR_T_WCHAR_T
    return stringView;
#else
    #error Unsupported char type
#endif
}

inline void utf8_to_string(string& out, cstring_view utf8)
{
    QX_PERF_SCOPE();

#if QX_CONF_CHAR == QX_CHAR_T_CHAR
    out = utf8;
#elif QX_CONF_CHAR == QX_CHAR_T_WCHAR_T
    #if QX_WIN

    // much faster on windows
    const int nLength = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), nullptr, 0);
    out.assign(nLength, L'\n');
    MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), out.data(), nLength);

    #else

    QX_PUSH_SUPPRESS_ALL_WARNINGS();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    out = converter.from_bytes(utf8.data(), utf8.data() + utf8.size());
    QX_POP_SUPPRESS_WARNINGS();

    #endif
#else
    #error Unsupported char type
#endif
}

inline string utf8_to_string(cstring_view utf8)
{
    string sResult;
    utf8_to_string(sResult, utf8);
    return sResult;
}

namespace details
{

template<class char_t, size_t N>
constexpr std::array<char_t, N> to_char_array(std::span<const char, N> svChar)
{
    std::array<char_t, N> result;
    for (size_t i = 0; i < N; ++i)
        result[i] = svChar[i];
    return result;
}

template<class char_t, string_literal array>
struct char_array_helper
{
    static constexpr auto char_array =
        to_char_array<char_t>(std::span<const char, array.size()>(array.data(), array.data() + array.size()));
};

} // namespace details

template<class char_t, string_literal array>
constexpr basic_string_view<char_t> convert_string_literal()
{
    constexpr auto& chars = details::char_array_helper<char_t, array>::char_array;
    return basic_string_view<char_t>(chars.data(), chars.size() - 1);
}

} // namespace qx
