//==============================================================================
//
//!\file                          string.h
//
//!\brief       Lite string impl
//!\details     ~
//
//!\author      Khrapov
//!\date        4.09.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/containers/container.h>
#include <qx/containers/string_traits.h>
#include <qx/meta/constexpr_random.h>
#include <qx/type_traits.h>

#include <array>
#include <vector>
#include <optional>
#include <iostream>
#include <string_view>

namespace qx
{

template<class Traits>
struct str_data
{
    typename Traits::size_type nSize          = 0;
    typename Traits::size_type nAllocatedSize = 0;

    // note: https://www.viva64.com/ru/w/v119/
    static constexpr typename Traits::size_type struct_size(void)
    {
        return sizeof(str_data) + offsetof(str_data, nAllocatedSize);
    }
};

template<class Traits>
class basic_string;

namespace detail
{
    template<class Traits>
    using ostream = std::basic_ostream<typename Traits::value_type, std::char_traits<typename Traits::value_type>>;

    template<class Traits>
    using istream = std::basic_istream<typename Traits::value_type, std::char_traits<typename Traits::value_type>>;

    using random_string_hash = constexpr_random<class random_string_hash_tag, QX_UNIQUE_SEED>;
}

}

template<class Traits>
qx::detail::istream<Traits>& operator>>(qx::detail::istream<Traits>& is, qx::basic_string<Traits>& str);

namespace qx
{

//!< case types for .apply_case()
enum class ECaseType
{
    lower,
    upper,
};

//==============================================================================z
//
//!\class                      qx::basic_string
//
//!\brief   Lite string class
//
//!\author  Khrapov
//!\date    20.10.2019
//
//==============================================================================
template<class Traits>
class basic_string
{
    using vector = std::vector<basic_string>;

    enum class EResizeType
    {
        common,
        reserve,
        fit
    };

    template<class _Traits>
    friend detail::istream<_Traits>& ::operator>>(qx::detail::istream<_Traits>& is, qx::basic_string<_Traits>& str);

public:

    using value_type        = typename Traits::value_type;
    using pointer           = typename Traits::pointer;
    using const_pointer     = typename Traits::const_pointer;
    using reference         = typename Traits::reference;
    using const_reference   = typename Traits::const_reference;
    using difference_type   = typename Traits::difference_type;
    using size_type         = typename Traits::size_type;
    using sstream_type      = typename std::basic_stringstream<value_type, std::char_traits<value_type>, std::allocator<value_type>>;

    static constexpr size_type npos = UINT_EMPTY_VALUE;

    IMPL_CONTAINER(basic_string)

public:

                            basic_string (void) = default;
                            basic_string (const_pointer          pSource,
                                          size_type              nSymbols)        { assign(pSource, nSymbols); }
                            basic_string (basic_string        && str)    noexcept { assign(std::move(str)); }
                            basic_string (const basic_string   & str)             { assign(str); }
                            basic_string (value_type             ch)              { assign(ch); }
                            basic_string (const_pointer          pSource)         { assign(pSource); }
                            basic_string (size_type              nSymbols,
                                          value_type             ch)              { assign(nSymbols, ch); }
    template<class FwdIt>   basic_string (FwdIt                  first,
                                          FwdIt                  last)            { assign(first, last); }
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
                            basic_string (const String         & str)             { assign(str.cbegin(), str.cend()); }

    void                    assign       (const_pointer          pSource,
                                          size_type              nSymbols);
    void                    assign       (basic_string        && str)    noexcept { std::swap(m_pData, str.m_pData); }
    void                    assign       (const basic_string   & str);
    void                    assign       (value_type             ch)              { assign(&ch, 1); }
    void                    assign       (const_pointer          pSource);
    void                    assign       (size_type              nSymbols,
                                          value_type             ch);
    template<class FwdIt>
    void                    assign       (FwdIt                  first,
                                          FwdIt                  last);
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    void                    assign       (const String         & str)             { assign(str.cbegin(), str.cend()); }

    virtual                ~basic_string (void)                                   { free(); }

    const   basic_string &  operator=    (basic_string        && str)    noexcept { assign(std::move(str));             return *this; }
    const   basic_string &  operator=    (const basic_string   & str)             { assign(str);                        return *this; }
    const   basic_string &  operator=    (value_type             ch)              { assign(ch);                         return *this; }
    const   basic_string &  operator=    (const_pointer          pSource)         { assign(pSource);                    return *this; }
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    const   basic_string &  operator=    (const String         & str)             { assign(str.cbegin(), str.cend());   return *this; }

    template<class ... Args>
    void                    format       (const_pointer          pStr,
                                          Args...                args);
    template<class ... Args>
    static basic_string     sformat      (const_pointer          pStr,
                                          Args...                args);

    size_type               capacity     (void)                                         const;

    size_type               reserve      (size_type              nCapacity);
    void                    fit          (void);
    void                    free         (void);

    void                    erase        (iterator               first,
                                          iterator               last);
    void                    erase        (iterator               it)        { erase(it, it + 1); };
    void                    erase        (size_type              pos)       { erase(iterator(this, pos), iterator(this, pos + 1)); }
    void                    erase        (size_type              ind_first,
                                          size_type              nSymbols)  { erase(iterator(this, ind_first), iterator(this, ind_first + nSymbols)); }

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
                                          const_iterator         from_last) { insert(to_first - begin(), from_first.operator->(), from_last - from_first); }
    void                    insert       (iterator               to,
                                          const_pointer          pSourse)   { insert(to - begin(), pSourse, Traits::tstrlen(pSourse)); }
    void                    insert       (iterator               to,
                                          const_pointer          pSourse,
                                          size_type              nSymbols)  { insert(to - begin(), pSourse, nSymbols); }
    void                    insert       (size_type              to_ind,
                                          const_pointer          pSourse)   { insert(to_ind, pSourse, Traits::tstrlen(pSourse)); }

    void                    push_back    (value_type             ch)        { insert(size(), &ch, 1); }
    void                    push_front   (value_type             ch)        { insert(0, &ch, 1); }

    size_type               find         (const_pointer          pWhat,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos) const;
    size_type               find         (value_type             ch,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos) const;
    size_type               find         (const basic_string   & str,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos) const { return find(str.m_pData, indBegin, indEnd); }

    basic_string            substr       (size_type              begin,
                                          size_type              strLen     = npos) const;

    size_type               find_last_of (value_type             ch,
                                          size_type              pos        = npos,
                                          size_type              count      = npos) const;

    vector                  split        (const_pointer          pSep,
                                          size_type              nSepLen    = npos) const;
    vector                  split        (const value_type       sep)               const;
    vector                  split        (const basic_string   & sep)               const { return split(sep.m_pData, sep.size()); }

    void                    apply_case   (ECaseType              ct);

    value_type              front        (void)                                     const { return at(0); }
    value_type              back         (void)                                     const { return at(size() - 1); }
    size_type               length       (void)                                     const { return size(); }
    const_pointer           c_str        (void)                                     const { return data(); }

    bool                    starts_with  (value_type             ch)                const;
    bool                    starts_with  (const_pointer          pszStr,
                                          size_type              nStrSize   = npos) const;
    template<class FwdIt>
    bool                    starts_with  (FwdIt                  itBegin,
                                          FwdIt                  itEnd)             const;
    bool                    starts_with  (const basic_string   & str)               const { return starts_with(str.data(), str.size()); }
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    starts_with  (const String         & str)               const { return starts_with(str.cbegin(), str.cend()); }

    bool                    ends_with    (value_type             ch)                const;
    bool                    ends_with    (const_pointer          pszStr,
                                          size_type              nStrSize   = npos) const;
    template<class FwdIt>
    bool                    ends_with    (FwdIt                  itBegin,
                                          FwdIt                  itEnd)             const;
    bool                    ends_with    (const basic_string   & str)               const { return ends_with(str.data(), str.size()); }
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    ends_with    (const String         & str)               const { return ends_with(str.cbegin(), str.cend()); }

    template<typename To>
    std::optional<To>       to           (void)                                     const;

    template<typename From>
    void                    from         (const From&            data,
                                          const_pointer          pszFormat = nullptr);
    template<typename From>
    static  basic_string    sfrom        (const From&            data,
                                          const_pointer          pszFormat = nullptr);

    const   basic_string &  operator+=   (const basic_string   & str)             { append(str.data(), str.size());             return *this; }
    const   basic_string &  operator+=   (value_type             ch)              { append(&ch, 1);                             return *this; }
    const   basic_string &  operator+=   (const_pointer          pSource)         { append(pSource, Traits::tstrlen(pSource));  return *this; }
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    const   basic_string &  operator+=   (const String         & str)            { append(str.cbegin(), str.cend());            return *this; }

    bool                    operator==   (const basic_string   & str)       const { return !compare(str.data()); }
    bool                    operator==   (value_type             ch)        const { return !compare(&ch, 1); }
    bool                    operator==   (const_pointer          pSource)   const { return !compare(pSource); }
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator==   (const String         & str)       const { return iter_strcmp(cbegin(), cend(), str.cbegin(), str.cend()) == 0; }

    bool                    operator!=   (const basic_string   & str)       const { return !operator==(str); }
    bool                    operator!=   (value_type             ch)        const { return !operator==(ch); }
    bool                    operator!=   (const_pointer          pSource)   const { return !operator==(pSource); }
    template<class String, class = typename std::enable_if_t<std::is_class_v<String>>>
    bool                    operator!=   (const String         & str)       const { return !operator==(str); }

    reference               operator[]   (size_type              ind)             { return m_pData[ind]; }
    const_reference         operator[]   (size_type              ind)       const { return operator[](ind); }

    operator std::basic_string_view<value_type, std::char_traits<value_type>>() const noexcept
    {
        return std::basic_string_view<value_type, std::char_traits<value_type>>(data(), size());
    }

private:

    str_data<Traits>      * get_str_data (void);
    const str_data<Traits>* get_str_data (void)                                                     const;
    bool                    resize       (size_type              nSymbols,
                                          size_type              nAlign,
                                          EResizeType            eType      = EResizeType::common);
    void                    append       (const_pointer          pSource,
                                          size_type              nSymbols);
    template<class FwdIt>
    void                    append       (FwdIt                  itBegin,
                                          FwdIt                  itEnd);
    int                     compare      (const_pointer          pStr,
                                          size_type              nSymbols   = 0)                    const;

    template<typename T>
    static constexpr const_pointer get_format_specifier(void);

private:

    pointer m_pData = nullptr;
};

#define _STR_OP_PLUS_BODY { basic_string<UT> str(std::move(lhs)); str += rhs; return std::move(str); }

template<class UT> basic_string<UT> operator+ (const basic_string<UT>   & lhs, const basic_string<UT>   & rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>        && lhs, basic_string<UT>        && rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>        && lhs, const basic_string<UT>   & rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (const basic_string<UT>   & lhs, basic_string<UT>        && rhs) _STR_OP_PLUS_BODY

template<class UT> basic_string<UT> operator+ (const basic_string<UT>   & lhs, typename UT::const_pointer rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>        && lhs, typename UT::const_pointer rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (typename UT::const_pointer lhs, const basic_string<UT>   & rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (typename UT::const_pointer lhs, basic_string<UT>        && rhs) _STR_OP_PLUS_BODY

template<class UT> basic_string<UT> operator+ (const basic_string<UT>   & lhs, typename UT::value_type    rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>        && lhs, typename UT::value_type    rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (typename UT::value_type    lhs, const basic_string<UT>   & rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (typename UT::value_type    lhs, basic_string<UT>        && rhs) _STR_OP_PLUS_BODY

template<class UT, class String, class = typename std::enable_if_t<std::is_class_v<String>>>
basic_string<UT>                    operator+ (const basic_string<UT>   & lhs, const String             & rhs) _STR_OP_PLUS_BODY
template<class UT, class String, class = typename std::enable_if_t<std::is_class_v<String>>>
basic_string<UT>                    operator+ (basic_string<UT>        && lhs, const String             & rhs) _STR_OP_PLUS_BODY
template<class UT, class String, class = typename std::enable_if_t<std::is_class_v<String>>>
basic_string<UT>                    operator+ (const String             & lhs, const basic_string<UT>   & rhs) _STR_OP_PLUS_BODY
template<class UT, class String, class = typename std::enable_if_t<std::is_class_v<String>>>
basic_string<UT>                    operator+ (const String             & lhs, basic_string<UT>        && rhs) _STR_OP_PLUS_BODY


using string    = basic_string<qx::char_traits<char>>;
using wstring   = basic_string<qx::char_traits<wchar_t>>;

}

#include <qx/containers/string.inl>
