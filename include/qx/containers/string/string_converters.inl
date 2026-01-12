/**

    @file      string_converters.inl
    @author    Khrapov
    @date      11.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

QX_SET_FILE_CATEGORY(CatQxConverters);

namespace qx
{

inline wstring to_wstring(cstring_view stringView, const std::locale& locale)
{
    QX_PERF_SCOPE();

    std::vector<wchar_t> buf(stringView.size());
    std::use_facet<std::ctype<wchar_t>>(locale).widen(
        stringView.data(),
        stringView.data() + stringView.size(),
        buf.data());

    return wstring(buf.data(), buf.size());
}

inline wstring_view to_wstring(wstring_view stringView, const std::locale& locale)
{
    return stringView;
}

inline cstring to_cstring(wstring_view stringView, const std::locale& locale)
{
    QX_PERF_SCOPE();

    std::vector<char> buf(stringView.size());
    std::use_facet<std::ctype<wchar_t>>(locale)
        .narrow(stringView.data(), stringView.data() + stringView.size(), '?', buf.data());
    return cstring(buf.data(), buf.size());
}

inline cstring_view to_cstring(cstring_view stringView, const std::locale& locale)
{
    return stringView;
}

inline string to_string(cstring_view stringView, const std::locale& locale)
{
#ifdef QX_CONF_USE_CHAR
    return stringView;
#elif defined(QX_CONF_USE_WCHAR)
    return to_wstring(stringView, locale);
#endif
}

inline string to_string(wstring_view stringView, const std::locale& locale)
{
#ifdef QX_CONF_USE_CHAR
    return to_cstring(stringView, locale);
#elif defined(QX_CONF_USE_WCHAR)
    return stringView;
#endif
}

inline string utf8_to_string(cstring_view pszUtf8)
{
    QX_PERF_SCOPE();

#ifdef QX_CONF_USE_WCHAR
    #if QX_WIN

    // much faster on windows
    const int nLength = MultiByteToWideChar(CP_UTF8, 0, pszUtf8.data(), static_cast<int>(pszUtf8.size()), nullptr, 0);
    string    sRet(nLength, QXT('\n'));
    MultiByteToWideChar(CP_UTF8, 0, pszUtf8.data(), static_cast<int>(pszUtf8.size()), sRet.data(), nLength);
    return sRet;

    #else

    QX_PUSH_SUPPRESS_ALL_WARNINGS();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(pszUtf8.data(), pszUtf8.data() + pszUtf8.size());
    QX_POP_SUPPRESS_WARNINGS();

    #endif
#endif
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
    return basic_string_view<char_t>(details::char_array_helper<char_t, array>::char_array.data());
}

} // namespace qx
