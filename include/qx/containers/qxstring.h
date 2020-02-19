//============================================================================
//
//!\file                          qxstring.h
//
//!\brief       Lite string impl
//!\details     ~
//
//!\author      Khrapov
//!\date        4.09.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <functional>
#include <array>
#include <vector>
#include <cctype>
#include <cstring>
#include <optional>

#include <qx/containers/container.h>
#include <qx/other/hashes.h>
#include <qx/other/useful_funcs.h>

namespace qx
{

template<class Traits>
struct SStrData;

template <class T>
struct char_traits;

//============================================================================
//
//!\struct                      char_traits<char>
//!\author  Khrapov
//!\date    30.10.2019
//============================================================================
template <>
struct char_traits<char>
{
    using value_type        = char;
    using pointer           = char*;
    using const_pointer     = const char*;
    using reference         = char&;
    using const_reference   = const char&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;

    static value_type   teol        (void)                          { return '\0';                                              }
    static size_type    talign      (void)                          { return 16;                                                }
    static size_type    tstrlen     (const_pointer  pStr)           { return static_cast<size_type>(std::strlen(pStr));         }
    static value_type   ttolower    (value_type     ch)             { return std::tolower(ch);                                  }
    static value_type   ttoupper    (value_type     ch)             { return std::toupper(ch);                                  }

    static i64          ttolli      (const_pointer  pStr, int base) { return std::strtoll   (pStr, nullptr, base);              }
    static u64          ttoull      (const_pointer  pStr, int base) { return std::strtoull  (pStr, nullptr, base);              }
    static long double  ttold       (const_pointer  pStr)           { return std::strtold   (pStr, nullptr);                    }

    static int          tstrcmp     (const_pointer  pFirst,
                                     const_pointer  pSecond)        { return std::strcmp(pFirst, pSecond);                      }
    static int          tstrncmp    (const_pointer  pFirst,
                                     const_pointer  pSecond,        
                                     size_type      nCount)         { return std::strncmp(pFirst, pSecond, nCount);             }
    template<class ... Args>
    static int          tsnprintf   (pointer       pDest,
                                     size_type     nBuffer,
                                     const_pointer pFormat,
                                     Args ...      args)            { return std::snprintf(pDest, nBuffer, pFormat, args...);   }

};

//!< case types for .apply_case()
enum class eCaseType
{
    original = 0,
    lower,
    upper,
    all_capitalized,
    sentence,
    random
};

//============================================================================
//
//!\class                        cStringType
//
//!\brief   Lite string class
//
//!\author  Khrapov
//!\date    20.10.2019
//
//============================================================================
template<typename T, class Traits>
class basic_string
{
    using vector = std::vector<basic_string>;

public:

    using value_type        = typename Traits::value_type;
    using pointer           = typename Traits::pointer;
    using const_pointer     = typename Traits::const_pointer;
    using reference         = typename Traits::reference;
    using const_reference   = typename Traits::const_reference;
    using difference_type   = typename Traits::difference_type;
    using size_type         = typename Traits::size_type;

    static const size_type npos = -1;

    IMPL_CONTAINER(basic_string)

public:
                            basic_string (void) = default;
                            basic_string (const_pointer          pSource,
                                          size_type              nSymbols);
                            basic_string (basic_string        && str)    noexcept { std::swap(m_pData, str.m_pData);                            }
                            basic_string (const basic_string   & str)             : basic_string(str.m_pData)                        {          }
                            basic_string (value_type             ch)              : basic_string(&ch, 1)                             {          }
                            basic_string (const_pointer          pSource)         : basic_string(pSource, Traits::tstrlen(pSource))  {          }
                            basic_string (size_type              nSymbols,
                                          value_type             ch);

    virtual                ~basic_string (void)                                   { clear();                                                    }

    const   basic_string &  operator=    (basic_string        && str)    noexcept;
    const   basic_string &  operator=    (const basic_string   & str);
    const   basic_string &  operator=    (value_type             ch);
    const   basic_string &  operator=    (const_pointer          pSource);

    template<class ... Args>
    void                    format       (const_pointer          pStr,
                                          Args...                args);
    template<class ... Args>
    static basic_string     sformat      (const_pointer          pStr,
                                          Args...                args);

    size_type               capacity     (void)                                         const;

    size_type               reserve      (size_type              nCapacity);

    void                    fit          (void);

    void                    erase        (iterator               first,
                                          iterator               last);
    void                    erase        (iterator               it);
    void                    erase        (size_type              pos);
    void                    erase        (size_type              ind_first,
                                          size_type              nSymbols);

    void                    insert       (const_iterator         from_first,
                                          const_iterator         from_last,
                                          iterator               to_first);
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

    size_type               find         (const_pointer          pWhat,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos)     const;
    size_type               find         (value_type             ch,
                                          size_type              indBegin   = 0,
                                          size_type              indEnd     = npos)     const;

    basic_string            substr       (size_type              begin,
                                          size_type              strLen     = npos)     const;

    size_type               find_last_of (value_type             ch,
                                          size_type              pos        = npos,
                                          size_type              count      = npos)     const;

    vector                  split        (const basic_string   & sep)                   const;
    static vector           split        (const basic_string   & text,
                                          const basic_string   & sep);

    void                    delete_line_breaks(void);
    static basic_string     delete_line_breaks(const_pointer     pSourse);

    void                    apply_case   (eCaseType              ct);

    std::optional<i8>       to           (i8,    int base = 0)                          const;
    std::optional<i16>      to           (i16,   int base = 0)                          const;
    std::optional<i32>      to           (i32,   int base = 0)                          const;
    std::optional<i64>      to           (i64,   int base = 0)                          const;
    std::optional<u8>       to           (u8,    int base = 0)                          const;
    std::optional<u16>      to           (u16,   int base = 0)                          const;
    std::optional<u32>      to           (u32,   int base = 0)                          const;
    std::optional<u64>      to           (u64,   int base = 0)                          const;
    std::optional<float>    to           (float)                                        const;
    std::optional<double>   to           (double)                                       const;
    std::optional<long double> to        (long double)                                  const;

    const   basic_string &  operator+=   (const basic_string   & str)             { Append(str.data(), str.size());             return *this;   }
    const   basic_string &  operator+=   (value_type             ch)              { Append(&ch, 1);                             return *this;   }
    const   basic_string &  operator+=   (const_pointer          pSource)         { Append(pSource, Traits::tstrlen(pSource));  return *this;   }

    bool                    operator==   (const basic_string   & str)       const { return !Compare(str.data());                                }
    bool                    operator==   (value_type             ch)        const { return !Compare(&ch, 1);                                    }
    bool                    operator==   (const_pointer          pSource)   const { return !Compare(pSource);                                   }

    bool                    operator!=   (const basic_string   & str)       const { return !operator==(str);                                    }
    bool                    operator!=   (value_type             ch)        const { return !operator==(ch);                                     }
    bool                    operator!=   (const_pointer          pSource)   const { return !operator==(pSource);                                }

    reference               operator[]   (size_type              ind);
    const_reference         operator[]   (size_type              ind)       const { return operator[](ind);                                     }

                            operator const char*()                          const { return data();                                              }

#if defined(__has_include) && __has_include(<string>)
                           basic_string (const std::string & str)       : basic_string(str.data(), static_cast<size_type>(str.size()))   {      }
    const   basic_string & operator=    (const std::string & str)       { Assign(str.data(), static_cast<size_type>(str.size())); return *this; }
    const   basic_string & operator+=   (const std::string & str)       { Append(str.data(), static_cast<size_type>(str.size())); return *this; }
    bool                   operator==   (const std::string & str) const { return !Compare(str.data());                                          }
    bool                   operator!=   (const std::string & str) const { return !operator==(str);                                              }
#endif

private:
    SStrData<Traits>          * GetStrData      (void);
    const SStrData<Traits>    * GetStrData      (void)                                          const;

    bool                        Resize          (size_type              nSymbols,
                                                 size_type              nAlign          = 0,
                                                 bool                   bReserve        = false);

    void                        Assign          (const_pointer          pSource,
                                                 size_type              nSymbols);
    void                        Append          (cstr                   pSource,
                                                 size_type              nSymbols);
    int                         Compare         (cstr                   pStr,
                                                 size_type              nSymbols = 0)           const;

private:
    T* m_pData = nullptr;
};

#define _STR_OP_PLUS_BODY { basic_string<U, UT> str(lhs); str += rhs; return str; }

template<typename U, class UT> basic_string<U, UT> operator+ (const basic_string<U, UT>&                  lhs, const basic_string<U, UT>&                  rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (basic_string<U, UT>&&                       lhs, basic_string<U, UT>&&                       rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (basic_string<U, UT>&&                       lhs, const basic_string<U, UT>&                  rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (const basic_string<U, UT>&                  lhs, basic_string<U, UT>&&                       rhs) _STR_OP_PLUS_BODY

template<typename U, class UT> basic_string<U, UT> operator+ (const basic_string<U, UT>&                  lhs, typename basic_string<U, UT>::const_pointer rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (basic_string<U, UT>&&                       lhs, typename basic_string<U, UT>::const_pointer rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (typename basic_string<U, UT>::const_pointer lhs, const basic_string<U, UT>&                  rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (typename basic_string<U, UT>::const_pointer lhs, basic_string<U, UT>&&                       rhs) _STR_OP_PLUS_BODY

template<typename U, class UT> basic_string<U, UT> operator+ (const basic_string<U, UT>&                  lhs, typename basic_string<U, UT>::value_type    rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (basic_string<U, UT>&&                       lhs, typename basic_string<U, UT>::value_type    rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (typename basic_string<U, UT>::value_type    lhs, const basic_string<U, UT>&                  rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (typename basic_string<U, UT>::value_type    lhs, basic_string<U, UT>&&                       rhs) _STR_OP_PLUS_BODY

#if defined (__has_include) && __has_include(<string>)
template<typename U, class UT> basic_string<U, UT> operator+ (const std::string&                          lhs, const basic_string<U, UT>&                  rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (std::string&&                               lhs, basic_string<U, UT>&&                       rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (basic_string<U, UT>&&                       lhs, const std::string&                          rhs) _STR_OP_PLUS_BODY
template<typename U, class UT> basic_string<U, UT> operator+ (const basic_string<U, UT>&                  lhs, std::string&&                               rhs) _STR_OP_PLUS_BODY
#endif

//============================================================================
//
//!\struct                   SStrData<Traits>
//!\author  Khrapov
//!\date    27.10.2019
//============================================================================
template<class Traits>
struct SStrData
{
    typename Traits::size_type   nSize           = 0;
    typename Traits::size_type   nAllocatedSize  = 0;

    // note: https://www.viva64.com/ru/w/v119/
    static typename Traits::size_type structSize(void)
        { return sizeof(SStrData) + offsetof(SStrData, nAllocatedSize); }
};

using string = basic_string<char, qx::char_traits<char>>;

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
    struct hash<const char*>
    {
        u32 operator()(const char* psz) const
        {
            return qx::hash::str::Murmur32(psz, 0, 652148);
        }
    };
}

#include <qx/containers/qxstring.inl>
