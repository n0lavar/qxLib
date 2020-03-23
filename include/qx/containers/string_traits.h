//============================================================================
//
//!\file                       string_traits.h
//
//!\brief       Traits for qx::string
//!\details     ~
//
//!\author      Khrapov
//!\date        24.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <cwctype>
#include <codecvt>
#include <cctype>

#include <qx/other/useful_funcs.h>

#define _TOWSTRING(x) L##x
#define TOWSTRING(x) _TOWSTRING(x)

namespace qx
{

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
    using std_string_type   = std::string;

    static value_type teol (void)                          
    { 
        return '\0';                                            
    }
    static size_type talign (void)                          
    { 
        return 16;                                              
    }
    static size_type tstrlen (const_pointer pStr)           
    { 
        return static_cast<size_type>(std::strlen(pStr));       
    }
    static value_type ttolower (value_type ch)             
    { 
        return std::tolower(ch);                                
    }
    static value_type ttoupper (value_type ch)             
    { 
        return std::toupper(ch);                                
    }
    static i64 ttolli (const_pointer pStr, pointer* pEnd, int base) 
    { 
        return std::strtoll(pStr, pEnd, base); 
    }
    static u64 ttoull (const_pointer pStr, pointer* pEnd, int base) 
    { 
        return std::strtoull(pStr, pEnd, base); 
    }
    static long double ttold(const_pointer pStr, pointer* pEnd)           
    { 
        return std::strtold (pStr, pEnd);       
    }
    static int tstrcmp(const_pointer pFirst, const_pointer pSecond)        
    { 
        return std::strcmp(pFirst, pSecond);                    
    }
    static int tstrncmp(const_pointer  pFirst, const_pointer  pSecond, size_type nCount)         
    { 
        return std::strncmp(pFirst, pSecond, nCount);           
    }
    template<class ... Args>
    static int tsnprintf(pointer pDest, size_type nBuffer, const_pointer pFormat, Args ... args)           
    { 
        return std::snprintf(pDest, nBuffer, pFormat, args...); 
    }
};

//============================================================================
//
//!\struct                   char_traits<wchar_t>
//!\author  Khrapov
//!\date    24.03.2020
//============================================================================
template <>
struct char_traits<wchar_t>
{
    using value_type        = wchar_t;
    using pointer           = wchar_t*;
    using const_pointer     = const wchar_t*;
    using reference         = wchar_t&;
    using const_reference   = const wchar_t&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;
    using std_string_type   = std::wstring;

    static value_type teol (void)                          
    { 
        return L'\0';                                            
    }
    static size_type talign (void)                          
    { 
        return 16;                                              
    }
    static size_type tstrlen (const_pointer pStr)           
    { 
        return static_cast<size_type>(std::wcslen(pStr));
    }
    static value_type ttolower (value_type ch)             
    { 
        return std::towlower(ch);                                
    }
    static value_type ttoupper(value_type ch)
    {
        return std::towupper(ch);
    }
    static i64 ttolli(const_pointer pStr, pointer* pEnd, int base)
    {
        return std::wcstoll(pStr, pEnd, base);
    }
    static u64 ttoull(const_pointer pStr, pointer* pEnd, int base)
    {
        return std::wcstoull(pStr, pEnd, base);
    }
    static long double ttold(const_pointer pStr, pointer* pEnd)
    {
        return std::wcstod(pStr, pEnd);
    }
    static int tstrcmp(const_pointer pFirst, const_pointer pSecond)
    {
        return std::wcscmp(pFirst, pSecond);
    }
    static int tstrncmp(const_pointer  pFirst, const_pointer  pSecond, size_type nCount)
    {
        return std::wcsncmp(pFirst, pSecond, nCount);
    }
    template<class ... Args>
    static int tsnprintf(pointer pDest, size_type nBuffer, const_pointer pFormat, Args ... args)
    {
        return std::swprintf(pDest, nBuffer, pFormat, args...);
    }
};

}

namespace qx::detail
{

template<typename value_type>
const value_type* ChooseStrPrefix(const char* c, const wchar_t* w);

template<>
const char* ChooseStrPrefix<char>(const char* c, const wchar_t* w)
{
    return c;
}

template<>
const wchar_t* ChooseStrPrefix<wchar_t>(const char* c, const wchar_t* w)
{
    return w;
}

template<typename C>
C ChooseCharPrefix(char c, wchar_t w);

template<>
char ChooseCharPrefix<char>(char c, wchar_t w)
{
    return c;
}

template<>
wchar_t ChooseCharPrefix<wchar_t>(char c, wchar_t w)
{
    return w;
}

}

// chose witch of prefixes add to string : L or none
#define STR_PREFIX(value_type, str) qx::detail::ChooseStrPrefix<value_type>(str, TOWSTRING(str))

// chose witch of prefixes add to char : L or none
#define CHAR_PREFIX(value_type, ch) qx::detail::ChooseCharPrefix<value_type>(ch, TOWSTRING(ch))
