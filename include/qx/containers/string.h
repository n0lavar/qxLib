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
                            basic_string (const_pointer          pSource,
                                          size_type              nSymbols);
                            basic_string (basic_string        && str)                       noexcept;
                            basic_string (const basic_string   & str);
                            basic_string (value_type             ch);
                            basic_string (const_pointer          pSource);
                            basic_string (size_type              nSymbols,
                                          value_type             ch);
    template<class FwdIt>   basic_string (FwdIt                  first,
                                          FwdIt                  last);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
                            basic_string (const String         & str);

                            ~basic_string(void);

    void                    assign       (const_pointer          pSource,
                                          size_type              nSymbols);
    void                    assign       (basic_string        && str)                       noexcept;
    void                    assign       (const basic_string   & str);
    void                    assign       (value_type             ch);
    void                    assign       (const_pointer          pSource);
    void                    assign       (size_type              nSymbols,
                                          value_type             ch);
    template<class FwdIt>
    void                    assign       (FwdIt                  first,
                                          FwdIt                  last);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    void                    assign       (const String         & str);

    void                    format       (const_pointer          pszFormat,
                                          ...);
    void                    vformat      (const_pointer          pszFormat,
                                          va_list                args);

    template<class ... Args>
    static basic_string     format_static(const_pointer          pszFormat,
                                          Args...                args);

    size_type               capacity     (void)                                     const;

    size_type               reserve      (size_type              nCapacity);
    void                    shrink_to_fit(void);
    void                    free         (void);

    void                    erase        (iterator               first,
                                          iterator               last);
    void                    erase        (iterator               it);
    void                    erase        (size_type              pos);
    void                    erase        (size_type              ind_first,
                                          size_type              nSymbols);

    template<class ... Args, class = typename std::enable_if_t<are_same_v<typename Traits::value_type, Args...>>>
    void                    erase_all_of (Args...                args);
    template<class FwdIt, class = typename std::enable_if_t<!std::is_same_v<typename Traits::value_type, FwdIt>>>
    void                    erase_all_of (FwdIt                  first,
                                          FwdIt                  last);
    void                    erase_line_breaks(void);


    void                    insert       (size_type              to_ind,
                                          const_pointer          pSourse,
                                          size_type              nSymbols);
    void                    insert       (iterator               to_first,
                                          const_iterator         from_first,
                                          const_iterator         from_last);
    void                    insert       (iterator               to,
                                          const_pointer          pSourse);
    void                    insert       (iterator               to,
                                          const_pointer          pSourse,
                                          size_type              nSymbols);
    void                    insert       (size_type              to_ind,
                                          const_pointer          pSourse);

    void                    push_back    (value_type             ch);
    void                    push_front   (value_type             ch);

    size_type               find         (const_pointer          pWhat,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos) const;
    size_type               find         (value_type             ch,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos) const;
    size_type               find         (const basic_string   & str,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos) const;

    basic_string            substr       (size_type              begin,
                                          size_type              strLen     = npos) const;

    size_type               find_last_of (value_type             ch,
                                          size_type              pos        = npos,
                                          size_type              count      = npos) const;

    vector                  split        (const_pointer          pSep,
                                          size_type              nSepLen    = npos) const;
    vector                  split        (const value_type       sep)               const;
    vector                  split        (const basic_string   & sep)               const;

    void                    apply_case   (case_type              ct);

    value_type              front        (void)                                     const;
    value_type              back         (void)                                     const;
    size_type               length       (void)                                     const;
    const_pointer           c_str        (void)                                     const;

    bool                    starts_with  (value_type             ch)                const;
    bool                    starts_with  (const_pointer          pszStr,
                                          size_type              nStrSize   = npos) const;
    template<class FwdIt>
    bool                    starts_with  (FwdIt                  itBegin,
                                          FwdIt                  itEnd)             const;
    bool                    starts_with  (const basic_string   & str)               const;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    starts_with  (const String         & str)               const;

    bool                    ends_with    (value_type             ch)                const;
    bool                    ends_with    (const_pointer          pszStr,
                                          size_type              nStrSize   = npos) const;
    template<class FwdIt>
    bool                    ends_with    (FwdIt                  itBegin,
                                          FwdIt                  itEnd)             const;
    bool                    ends_with    (const basic_string   & str)               const;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    ends_with    (const String         & str)               const;

    template<typename To>
    std::optional<To>       to           (void)                                     const;

    template<typename From>
    void                    from         (const From&            data,
                                          const_pointer          pszFormat = nullptr);
    template<typename From>
    static  basic_string    sfrom        (const From&            data,
                                          const_pointer          pszFormat = nullptr);

    const   basic_string &  operator=    (basic_string        && str)                     noexcept;
    const   basic_string &  operator=    (const basic_string   & str);
    const   basic_string &  operator=    (value_type             ch);
    const   basic_string &  operator=    (const_pointer          pSource);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    const   basic_string &  operator=    (const String         & str);

    const   basic_string &  operator+=   (const basic_string   & str);
    const   basic_string &  operator+=   (value_type             ch);
    const   basic_string &  operator+=   (const_pointer          pSource);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    const   basic_string &  operator+=   (const String         & str);

    bool                    operator==   (const basic_string   & str)               const noexcept;
    bool                    operator==   (value_type             ch)                const noexcept;
    bool                    operator==   (const_pointer          pSource)           const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator==   (const String         & str)               const noexcept;

    bool                    operator!=   (const basic_string   & str)               const noexcept;
    bool                    operator!=   (value_type             ch)                const noexcept;
    bool                    operator!=   (const_pointer          pSource)           const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator!=   (const String         & str)               const noexcept;

    bool                    operator<    (const basic_string   & str)               const noexcept;
    bool                    operator<    (value_type             ch)                const noexcept;
    bool                    operator<    (const_pointer          pSource)           const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator<    (const String         & str)               const noexcept;

    bool                    operator<=   (const basic_string   & str)               const noexcept;
    bool                    operator<=   (value_type             ch)                const noexcept;
    bool                    operator<=   (const_pointer          pSource)           const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator<=   (const String         & str)               const noexcept;

    bool                    operator>    (const basic_string   & str)               const noexcept;
    bool                    operator>    (value_type             ch)                const noexcept;
    bool                    operator>    (const_pointer          pSource)           const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator>    (const String         & str)               const noexcept;

    bool                    operator>=   (const basic_string   & str)               const noexcept;
    bool                    operator>=   (value_type             ch)                const noexcept;
    bool                    operator>=   (const_pointer          pSource)           const noexcept;
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator>=   (const String         & str)               const noexcept;

    reference               operator[]   (size_type              ind)                     noexcept;
    const_reference         operator[]   (size_type              ind)               const noexcept;

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
