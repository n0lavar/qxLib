//==============================================================================
//
//!\file                          string.h
//
//!\brief       String impl
//!\details     ~
//
//!\author      Khrapov
//!\date        4.09.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/containers/container.h>
#include <qx/containers/string_hash.h>
#include <qx/containers/string_data.h>
#include <qx/meta/constexpr_random.h>
#include <qx/type_traits.h>

#include <vector>
#include <optional>
#include <iostream>
#include <string_view>

namespace qx
{

template<class Traits>
class basic_string;

namespace detail
{
    template<class Traits>
    using ostream = std::basic_ostream<
        typename Traits::value_type,
        std::char_traits<typename Traits::value_type>
    >;

    template<class Traits>
    using istream = std::basic_istream<
        typename Traits::value_type,
        std::char_traits<typename Traits::value_type>
    >;

    using random_string_hash = constexpr_random<
        class random_string_hash_tag,
        QX_UNIQUE_SEED
    >;
}

}

template<class Traits>
qx::detail::istream<Traits>& operator>>(
    qx::detail::istream<Traits>& is,
    qx::basic_string<Traits>& str);

namespace qx
{

//!< case types for .apply_case()
enum class case_type
{
    lower,
    upper,
};

//==============================================================================
//
//!\class                      qx::basic_string
//
//!\brief   String class
//
//!\author  Khrapov
//!\date    20.10.2019
//
//==============================================================================
template<class Traits>
class basic_string
{
    using vector = std::vector<basic_string>;

    template<class _Traits>
    friend detail::istream<_Traits>& ::operator>>(
        qx::detail::istream<_Traits>& is,
        qx::basic_string<_Traits>& str);

public:

    using traits_type       = Traits;
    using value_type        = typename Traits::value_type;
    using pointer           = typename Traits::pointer;
    using const_pointer     = typename Traits::const_pointer;
    using reference         = typename Traits::reference;
    using const_reference   = typename Traits::const_reference;
    using difference_type   = typename Traits::difference_type;
    using size_type         = typename Traits::size_type;
    using sstream_type      = typename std::basic_stringstream<
        value_type, std::char_traits<value_type>,
        std::allocator<value_type>
    >;

    static constexpr size_type npos = std::numeric_limits<size_type>::max();

    IMPL_CONTAINER(basic_string)

public:

                            basic_string (void) = default;
                            basic_string (value_type             chSymbol);
                            basic_string (size_type              nSymbols,
                                          value_type             chSymbol);
                            basic_string (const_pointer          pszSource,
                                          size_type              nSymbols);
                            basic_string (const_pointer          pszSource);
                            basic_string (basic_string        && sAnother)                  noexcept;
                            basic_string (const basic_string   & sAnother);
    template<class FwdIt>   basic_string (FwdIt                  itFirst,
                                          FwdIt                  itLast);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
                            basic_string (const String         & sAnother);

                            ~basic_string(void);

    void                    assign       (value_type             chSymbol);
    void                    assign       (size_type              nSymbols,
                                          value_type             chSymbol);
    void                    assign       (const_pointer          pszSource,
                                          size_type              nSymbols);
    void                    assign       (const_pointer          pszSource);
    void                    assign       (basic_string        && sAnother)                  noexcept;
    void                    assign       (const basic_string   & sAnother);
    template<class FwdIt>
    void                    assign       (FwdIt                  itFirst,
                                          FwdIt                  itLast);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    void                    assign       (const String         & str);

    void                    format       (const_pointer          pszFormat,
                                          ...);
    void                    vformat      (const_pointer          pszFormat,
                                          va_list                args);
    template<class ... Args>
    static basic_string     format_static(const_pointer          pszFormat,
                                          Args...                args);

    size_type               reserve      (size_type              nCapacity);
    void                    shrink_to_fit(void);
    void                    free         (void);

    basic_string            substr       (size_type              nPos,
                                          size_type              nSymbols   = npos) const;

    void                    apply_case   (case_type              eCaseType);

    value_type              front        (void)                                     const;
    value_type              back         (void)                                     const;
    size_type               length       (void)                                     const;
    const_pointer           c_str        (void)                                     const;
    size_type               capacity     (void)                                     const;

    template<typename To>
    std::optional<To>       to           (void)                                     const;

    template<typename From>
    void                    from         (const From&            data,
                                          const_pointer          pszFormat = nullptr);
    template<typename From>
    static  basic_string    sfrom        (const From&            data,
                                          const_pointer          pszFormat = nullptr);

    void                    erase        (iterator               itFirst,
                                          iterator               itLast);
    void                    erase        (iterator               itPos);
    void                    erase        (size_type              nPos);
    void                    erase        (size_type              nPos,
                                          size_type              nSymbols);

    void                    insert       (size_type              nPos,
                                          const_pointer          pszSourse,
                                          size_type              nSymbols   = npos);
    void                    insert       (iterator               itToFirst,
                                          const_iterator         itFromFirst,
                                          const_iterator         itFromLast);
    void                    insert       (iterator               itPos,
                                          const_pointer          pszSourse,
                                          size_type              nSymbols   = npos);

    void                    push_back    (value_type             chSymbol);
    void                    push_front   (value_type             chSymbol);

    size_type               find         (value_type             chSymbol,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos) const;
    size_type               find         (const_pointer          pszWhat,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos,
                                          size_type              nWhatSize  = npos) const;
    size_type               find         (const basic_string   & sWhat,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos) const;
    template<class FwdIt>
    size_type               find         (FwdIt                  itWhatBegin,
                                          FwdIt                  itWhatEnd,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos) const;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    size_type               find         (String                 sWhat,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos) const;

    size_type               find_last_of (value_type             chSymbol,
                                          size_type              nPos       = npos,
                                          size_type              nSymbols   = npos) const;

    size_type               remove       (value_type             chSymbol,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos);
    size_type               remove       (const_pointer          pszStr,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos,
                                          size_type              nStrSize   = npos);
    size_type               remove       (const basic_string   & sStr,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos);
    template<class FwdIt>
    size_type               remove       (FwdIt                  itBegin,
                                          FwdIt                  itEnd,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    size_type               remove       (const String         & sStr,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos);

    size_type               remove_all   (value_type             chSymbol,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos);
    size_type               remove_all   (const_pointer          pszStr,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos,
                                          size_type              nStrSize   = npos);
    size_type               remove_all   (const basic_string   & sStr,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos);
    template<class FwdIt>
    size_type               remove_all   (FwdIt                  itFirst,
                                          FwdIt                  itLast,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    size_type               remove_all   (const String         & sStr,
                                          size_type              nBegin     = 0,
                                          size_type              nEnd       = npos);

    vector                  split        (const value_type       chSeparator)       const;
    vector                  split        (const_pointer          pszSeparator,
                                          size_type              nSepLen    = npos) const;
    vector                  split        (const basic_string   & sSeparator)        const;
    template<class FwdIt>
    vector                  split        (FwdIt                  itSepFirst,
                                          FwdIt                  itSepLast)         const;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    vector                  split        (const String         & sSeparator)        const;

    bool                    starts_with  (value_type             chSymbol)          const;
    bool                    starts_with  (const_pointer          pszStr,
                                          size_type              nStrSize   = npos) const;
    bool                    starts_with  (const basic_string   & sStr)              const;
    template<class FwdIt>
    bool                    starts_with  (FwdIt                  itBegin,
                                          FwdIt                  itEnd)             const;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    starts_with  (const String         & sStr)              const;

    bool                    ends_with    (value_type             chSymbol)          const;
    bool                    ends_with    (const_pointer          pszStr,
                                          size_type              nStrSize   = npos) const;
    bool                    ends_with    (const basic_string   & sStr)              const;
    template<class FwdIt>
    bool                    ends_with    (FwdIt                  itBegin,
                                          FwdIt                  itEnd)             const;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    ends_with    (const String         & sStr)              const;

    bool                    contains     (value_type             chSymbol)          const;
    bool                    contains     (const_pointer          pszStr,
                                          size_type              nStrSize   = npos) const;
    bool                    contains     (const basic_string   & sStr)              const;
    template<class FwdIt>
    bool                    contains     (FwdIt                  itBegin,
                                          FwdIt                  itEnd)             const;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    contains     (const String         & sStr)              const;

    const   basic_string &  operator=    (value_type             chSymbol);
    const   basic_string &  operator=    (const_pointer          pszSource);
    const   basic_string &  operator=    (basic_string        && sStr)                    noexcept;
    const   basic_string &  operator=    (const basic_string   & sStr);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    const   basic_string &  operator=    (const String         & sStr);

    const   basic_string &  operator+=   (value_type             chSymbol);
    const   basic_string &  operator+=   (const_pointer          pszSource);
    const   basic_string &  operator+=   (const basic_string   & sStr);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    const   basic_string &  operator+=   (const String         & sStr);

    bool                    operator==   (value_type             chSymbol)          const noexcept;
    bool                    operator==   (const_pointer          pszSource)         const noexcept;
    bool                    operator==   (const basic_string   & sStr)              const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator==   (const String         & sStr)              const noexcept;

    bool                    operator!=   (value_type             chSymbol)          const noexcept;
    bool                    operator!=   (const_pointer          pszSource)         const noexcept;
    bool                    operator!=   (const basic_string   & sStr)              const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator!=   (const String         & sStr)              const noexcept;

    bool                    operator<    (value_type             chSymbol)          const noexcept;
    bool                    operator<    (const_pointer          pszSource)         const noexcept;
    bool                    operator<    (const basic_string   & sStr)              const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator<    (const String         & sStr)              const noexcept;

    bool                    operator<=   (value_type             chSymbol)          const noexcept;
    bool                    operator<=   (const_pointer          pszSource)         const noexcept;
    bool                    operator<=   (const basic_string   & sStr)              const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator<=   (const String         & sStr)              const noexcept;

    bool                    operator>    (value_type             chSymbol)          const noexcept;
    bool                    operator>    (const_pointer          pszSource)         const noexcept;
    bool                    operator>    (const basic_string   & sStr)              const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator>    (const String         & sStr)              const noexcept;

    bool                    operator>=   (value_type             chSymbol)          const noexcept;
    bool                    operator>=   (const_pointer          pszSource)         const noexcept;
    bool                    operator>=   (const basic_string   & sStr)              const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator>=   (const String         & sStr)              const noexcept;

    reference               operator[]   (size_type              nSymbol)                 noexcept;
    const_reference         operator[]   (size_type              nSymbol)           const noexcept;

    operator std::basic_string_view<value_type, std::char_traits<value_type>>()     const noexcept;

private:

    bool                    resize       (size_type              nSymbols,
                                          size_type              nAlign,
                                          string_resize_type     eType      = string_resize_type::common);
    void                    append       (const_pointer          pSource,
                                          size_type              nSymbols);
    template<class FwdIt>
    void                    append       (FwdIt                  itBegin,
                                          FwdIt                  itEnd);
    int                     compare      (const_pointer          pStr,
                                          size_type              nSymbols   = 0)    const;

    template<typename T>
    static constexpr const_pointer get_format_specifier(void);

private:

    string_data<Traits> m_Data;
};

#define _QX_STR_OP_PLUS_BODY { basic_string<UT> str(std::move(lhs)); str += rhs; return std::move(str); }

template<class UT>
basic_string<UT> operator+ (const basic_string<UT>   & lhs, const basic_string<UT>   & rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (basic_string<UT>        && lhs, basic_string<UT>        && rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (basic_string<UT>        && lhs, const basic_string<UT>   & rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (const basic_string<UT>   & lhs, basic_string<UT>        && rhs) _QX_STR_OP_PLUS_BODY

template<class UT>
basic_string<UT> operator+ (const basic_string<UT>   & lhs, typename UT::const_pointer rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (basic_string<UT>        && lhs, typename UT::const_pointer rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (typename UT::const_pointer lhs, const basic_string<UT>   & rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (typename UT::const_pointer lhs, basic_string<UT>        && rhs) _QX_STR_OP_PLUS_BODY

template<class UT>
basic_string<UT> operator+ (const basic_string<UT>   & lhs, typename UT::value_type    rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (basic_string<UT>        && lhs, typename UT::value_type    rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (typename UT::value_type    lhs, const basic_string<UT>   & rhs) _QX_STR_OP_PLUS_BODY
template<class UT>
basic_string<UT> operator+ (typename UT::value_type    lhs, basic_string<UT>        && rhs) _QX_STR_OP_PLUS_BODY

template<class UT, class String, class = typename std::enable_if_t<std::is_class_v<String>>>
basic_string<UT> operator+ (const basic_string<UT>   & lhs, const String             & rhs) _QX_STR_OP_PLUS_BODY
template<class UT, class String, class = typename std::enable_if_t<std::is_class_v<String>>>
basic_string<UT> operator+ (basic_string<UT>        && lhs, const String             & rhs) _QX_STR_OP_PLUS_BODY
template<class UT, class String, class = typename std::enable_if_t<std::is_class_v<String>>>
basic_string<UT> operator+ (const String             & lhs, const basic_string<UT>   & rhs) _QX_STR_OP_PLUS_BODY
template<class UT, class String, class = typename std::enable_if_t<std::is_class_v<String>>>
basic_string<UT> operator+ (const String             & lhs, basic_string<UT>        && rhs) _QX_STR_OP_PLUS_BODY


using string    = basic_string<qx::char_traits<char>>;
using wstring   = basic_string<qx::char_traits<wchar_t>>;

}

#include <qx/containers/string.inl>
