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

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <array>
#include <vector>
#include <optional>

#include <qx/containers/container.h>
#include <qx/containers/string_traits.h>
#include <qx/other/hashes.h>
#include <qx/other/random.h>
#include <qx/temp/type_traits.h>

namespace qx
{

template<class Traits>
struct SStrData;

//!< case types for .apply_case()
enum class ECaseType
{
    lower,
    upper,
    random,
};

//==============================================================================z
//
//!\class                        basic_string
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

public:

    using value_type        = typename Traits::value_type;
    using pointer           = typename Traits::pointer;
    using const_pointer     = typename Traits::const_pointer;
    using reference         = typename Traits::reference;
    using const_reference   = typename Traits::const_reference;
    using difference_type   = typename Traits::difference_type;
    using size_type         = typename Traits::size_type;
    using std_string_type   = typename Traits::std_string_type;
    using sstream_type      = typename Traits::sstream_type;

    static constexpr size_type npos = UINT_EMPTY_VALUE;

    IMPL_CONTAINER(basic_string)

public:

                            basic_string (void) = default;
                            basic_string (const_pointer          pSource,
                                          size_type              nSymbols)        { assign(pSource, nSymbols);                 }
                            basic_string (basic_string        && str)    noexcept { assign(std::move(str));                    }
                            basic_string (const basic_string   & str)             { assign(str);                               }
                            basic_string (value_type             ch)              { assign(ch);                                }
                            basic_string (const_pointer          pSource)         { assign(pSource);                           }
                            basic_string (size_type              nSymbols,
                                          value_type             ch)              { assign(nSymbols, ch);                      }
                            basic_string (const std_string_type& str)             { assign(str);                               }
    template<class FwdIt>   basic_string (FwdIt                  first, 
                                          FwdIt                  last)            { assign(first, last);                       }

    void                    assign       (const_pointer          pSource,
                                          size_type              nSymbols);
    void                    assign       (basic_string        && str)    noexcept { std::swap(m_pData, str.m_pData);           }
    void                    assign       (const basic_string   & str);
    void                    assign       (value_type             ch)              { assign(&ch, 1);                            }
    void                    assign       (const_pointer          pSource);
    void                    assign       (size_type              nSymbols,
                                          value_type             ch);
    void                    assign       (const std_string_type& str)             { assign(str.data(), static_cast<size_type>(str.size())); }
    template<class FwdIt>
    void                    assign       (FwdIt                  first,
                                          FwdIt                  last);

    virtual                ~basic_string (void)                                   { free();                                     }

    const   basic_string &  operator=    (basic_string        && str)    noexcept { assign(std::move(str)); return *this;       }
    const   basic_string &  operator=    (const basic_string   & str)             { assign(str);            return *this;       }
    const   basic_string &  operator=    (value_type             ch)              { assign(ch);             return *this;       }
    const   basic_string &  operator=    (const_pointer          pSource)         { assign(pSource);        return *this;       }
    const   basic_string &  operator=    (const std_string_type& str)             { assign(str);            return *this;       }

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
    void                    erase        (iterator               it);
    void                    erase        (size_type              pos);
    void                    erase        (size_type              ind_first,
                                          size_type              nSymbols);

    template<class ... Args, class = typename std::enable_if<are_same_v<typename Traits::value_type, Args...>>::type>
    void                    erase_all_of (Args...                args);
    template<class FwdIt, class = typename std::enable_if<!std::is_same_v<typename Traits::value_type, FwdIt>>::type>
    void                    erase_all_of (FwdIt                  first,
                                          FwdIt                  last);
    void                    erase_line_breaks(void);


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
    void                    insert       (size_type              to_ind,
                                          const_pointer          pSourse,
                                          size_type              nSymbols);

    void                    push_back    (value_type             ch);
    void                    push_front   (value_type             ch);

    size_type               find         (const_pointer          pWhat,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos)     const;
    size_type               find         (value_type             ch,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos)     const;
    size_type               find         (const basic_string   & str,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos)     const;

    basic_string            substr       (size_type              begin,
                                          size_type              strLen     = npos)     const;

    size_type               find_last_of (value_type             ch,
                                          size_type              pos        = npos,
                                          size_type              count      = npos)     const;

    vector                  split        (const_pointer          pSep,
                                          size_type              nSepLen    = npos)     const;
    vector                  split        (const value_type       sep)                   const;
    vector                  split        (const basic_string   & sep)                   const;
    
    void                    apply_case   (ECaseType              ct);

    value_type              front        (void)                                         const { return at(0);           }
    value_type              back         (void)                                         const { return at(size() - 1);  }
    size_type               length       (void)                                         const { return size();          }
    const_pointer           c_str        (void)                                         const { return data();          }

    template<typename To>
    typename std::enable_if<std::is_signed_v<To> && !std::is_unsigned_v<To> && !std::is_floating_point_v<To>,
        std::optional<To>>::type to(int base = 0);

    template<typename To>
    typename std::enable_if<!std::is_signed_v<To> && std::is_unsigned_v<To> && !std::is_floating_point_v<To>,
        std::optional<To>>::type to(int base = 0);

    template<typename To>
    typename std::enable_if<std::is_floating_point_v<To>,
        std::optional<To>>::type to();

    template<typename From>
    void                    from         (const From&            data, 
                                          const_pointer          pszFormat = nullptr);
    template<typename From>
    static  basic_string    sfrom        (const From&            data, 
                                          const_pointer          pszFormat = nullptr);

    const   basic_string &  operator+=   (const basic_string   & str)             { Append(str.data(), str.size());             return *this;   }
    const   basic_string &  operator+=   (value_type             ch)              { Append(&ch, 1);                             return *this;   }
    const   basic_string &  operator+=   (const_pointer          pSource)         { Append(pSource, Traits::tstrlen(pSource));  return *this;   }
    const   basic_string &  operator+=   (const std_string_type & str)            { Append(str.data(), static_cast<size_type>(str.size())); return *this; }

    bool                    operator==   (const basic_string   & str)       const { return !Compare(str.data());                                }
    bool                    operator==   (value_type             ch)        const { return !Compare(&ch, 1);                                    }
    bool                    operator==   (const_pointer          pSource)   const { return !Compare(pSource);                                   }
    bool                    operator==   (const std_string_type& str)       const { return !Compare(str.data());                                }

    bool                    operator!=   (const basic_string   & str)       const { return !operator==(str);                                    }
    bool                    operator!=   (value_type             ch)        const { return !operator==(ch);                                     }
    bool                    operator!=   (const_pointer          pSource)   const { return !operator==(pSource);                                }
    bool                    operator!=   (const std_string_type& str)       const { return !operator==(str);                                    }

    reference               operator[]   (size_type              ind);
    const_reference         operator[]   (size_type              ind)       const { return operator[](ind);                                     }

private:

    SStrData<Traits>      * GetStrData   (void);
    const SStrData<Traits>* GetStrData   (void)                                                     const;
    bool                    Resize       (size_type              nSymbols,
                                          size_type              nAlign     = 0,
                                          EResizeType            eType      = EResizeType::common);
    void                    Append       (const_pointer          pSource,
                                          size_type              nSymbols);
    int                     Compare      (const_pointer          pStr,
                                          size_type              nSymbols   = 0)                    const;
private:

    pointer m_pData = nullptr;
};

#define _STR_OP_PLUS_BODY { basic_string<UT> str(std::move(lhs)); str += rhs; return std::move(str); }

template<class UT> basic_string<UT> operator+ (const basic_string<UT>&              lhs, const basic_string<UT>&                rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>&&                   lhs, basic_string<UT>&&                     rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>&&                   lhs, const basic_string<UT>&                rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (const basic_string<UT>&              lhs, basic_string<UT>&&                     rhs) _STR_OP_PLUS_BODY
                                                                                                                                
template<class UT> basic_string<UT> operator+ (const basic_string<UT>&              lhs, typename UT::const_pointer             rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>&&                   lhs, typename UT::const_pointer             rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (typename UT::const_pointer           lhs, const basic_string<UT>&                rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (typename UT::const_pointer           lhs, basic_string<UT>&&                     rhs) _STR_OP_PLUS_BODY
                                                                                                                                
template<class UT> basic_string<UT> operator+ (const basic_string<UT>&              lhs, typename UT::value_type                rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>&&                   lhs, typename UT::value_type                rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (typename UT::value_type              lhs, const basic_string<UT>&                rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (typename UT::value_type              lhs, basic_string<UT>&&                     rhs) _STR_OP_PLUS_BODY
                                                                                                                                          
template<class UT> basic_string<UT> operator+ (const basic_string<UT>&              lhs, const typename UT::std_string_type&    rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (basic_string<UT>&&                   lhs, const typename UT::std_string_type&    rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (const typename UT::std_string_type&  lhs, const basic_string<UT>&                rhs) _STR_OP_PLUS_BODY
template<class UT> basic_string<UT> operator+ (const typename UT::std_string_type&  lhs, basic_string<UT>&&                     rhs) _STR_OP_PLUS_BODY

//==============================================================================
//
//!\struct                   SStrData<Traits>
//!\author  Khrapov
//!\date    27.10.2019
//==============================================================================
template<class Traits>
struct SStrData
{
    typename Traits::size_type   nSize           = 0;
    typename Traits::size_type   nAllocatedSize  = 0;

    // note: https://www.viva64.com/ru/w/v119/
    static typename Traits::size_type structSize(void)
        { return sizeof(SStrData) + offsetof(SStrData, nAllocatedSize); }
};

using string    = basic_string<qx::char_traits<16>>;    // char sequence with 16 alignment
using wstring   = basic_string<qx::wchar_traits<16>>;   // wchar_t sequence with 16 alignment
using pstring   = basic_string<qx::char_traits<1>>;     // char sequence without alignment (precise)
using wpstring  = basic_string<qx::wchar_traits<1>>;    // wchar_t sequence without alignment (precise)

}

namespace std
{
    template<>
    struct hash<qx::string>
    {
        u32 operator()(const qx::string& str) const
        {
            return qx::hash::str::Murmur32(str.data(), str.size(), 342451);
        }
    };

    template<>
    struct hash<qx::wstring>
    {
        u32 operator()(const qx::wstring& str) const
        {
            return qx::hash::str::Murmur32(str.data(), str.size(), 62548);
        }
    };

    template<>
    struct hash<qx::pstring>
    {
        u32 operator()(const qx::pstring& str) const
        {
            return qx::hash::str::Murmur32(str.data(), str.size(), 78524);
        }
    };

    template<>
    struct hash<qx::wpstring>
    {
        u32 operator()(const qx::wpstring& str) const
        {
            return qx::hash::str::Murmur32(str.data(), str.size(), 108540);
        }
    };
}

#include <qx/containers/string.inl>
