/**

    @file      locale.inl
    @author    Khrapov
    @date      07.11.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

namespace details
{

inline auto& get_locale_state()
{
    struct locale_state
    {
#if QX_STRING_USE_CRT_LOCALE
        struct crt_locale_deleter
        {
            void operator()(_locale_t locale) const noexcept
            {
                if (locale)
                    _free_locale(locale);
            }
        };

        using crt_locale_ptr = std::unique_ptr<std::remove_pointer_t<_locale_t>, crt_locale_deleter>;

        locale_state()
        {
            set(locale);
        }
#endif

        void set(const std::locale& value)
        {
#if QX_STRING_USE_CRT_LOCALE
            // On Windows, libc++ queries and switches the C locale for each character,
            // causing contention on the CRT locale lock. The default named locale can
            // instead use explicit CRT locale conversions without changing thread locale.
            // These convert single bytes, not UTF-8 sequences; behavior for every CRT
            // locale has not been verified. Explicit, custom and classic locales, or
            // failure to create the CRT locale, fall back to the C++ facet.
            const std::string sName = value.name();
            crt_locale_ptr    crtValue;
            if (sName != "*" && sName != "C")
                crtValue.reset(_create_locale(LC_CTYPE, sName.c_str()));
#endif
            locale = value;
            facet  = &std::use_facet<std::ctype<wchar_t>>(locale);
#if QX_STRING_USE_CRT_LOCALE
            crtLocale = std::move(crtValue);
#endif
        }

        std::locale                locale = std::locale();
        const std::ctype<wchar_t>* facet  = &std::use_facet<std::ctype<wchar_t>>(locale);
#if QX_STRING_USE_CRT_LOCALE
        crt_locale_ptr crtLocale;
#endif
    };

    static locale_state s_State;
    return s_State;
}

} // namespace details

inline void set_locale(const std::locale& locale)
{
    details::get_locale_state().set(locale);
}

inline const std::locale& get_locale()
{
    return details::get_locale_state().locale;
}

inline const std::ctype<wchar_t>& get_locale_facet()
{
    return *details::get_locale_state().facet;
}

} // namespace qx
