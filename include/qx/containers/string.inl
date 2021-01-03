#include "string.h"
//==============================================================================
//
//!\file                         string.inl
//
//!\brief       String impl
//!\details     ~
//
//!\author      Khrapov
//!\date        4.09.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  chSymbol - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(value_type chSymbol) noexcept
{
    assign(chSymbol);
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  nSymbols - num of symbols of char
//!\param  chSymbol - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(size_type nSymbols, value_type chSymbol) noexcept
{
    assign(nSymbols, chSymbol);
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  pszSource - source string pointer
//!\param  nSymbols  - source string size
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(
    const_pointer pszSource,
    size_type     nSymbols) noexcept
{
    assign(pszSource, nSymbols);
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  pszSource - const pointer
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(const_pointer pszSource) noexcept
{
    assign(pszSource);
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  sAnother - another string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(basic_string&& sAnother) noexcept
{
    assign(std::move(sAnother));
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  sAnother - another string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(const basic_string& sAnother) noexcept
{
    assign(sAnother);
}

//==============================================================================
//!\fn             basic_string<Traits>::basic_string<FwdIt>
//
//!\brief  basic_string object constructor
//!\param  itFirst - first iterator of source
//!\param  itLast  - last iterator of source
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline basic_string<Traits>::basic_string(FwdIt itFirst, FwdIt itLast) noexcept
{
    assign(itFirst, itLast);
}

//==============================================================================
//!\fn            basic_string<Traits>::basic_string<String, >
//
//!\brief  basic_string object constructor
//!\param  sAnother - char container
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline basic_string<Traits>::basic_string (const String & sAnother) noexcept
{
    assign(sAnother);
}

//==============================================================================
//!\fn                basic_string<Traits>::~basic_string
//
//!\brief  basic_string object destructor
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::~basic_string(void) noexcept
{
    free();
}

//==============================================================================
//!\fn                    basic_string<Traits>::assign
//
//!\brief  Assign by single char
//!\param  chSymbol - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(value_type chSymbol) noexcept
{
    assign(&chSymbol, 1);
}

//==============================================================================
//!\fn             qx::basic_string<Traits>::assign
//
//!\brief  Assign by filling
//!\param  nSymbols - num of symbols of char
//!\param  ch       - char
//!\author Khrapov
//!\date   29.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(
    size_type  nSymbols,
    value_type chSymbol) noexcept
{
    if (resize(nSymbols, Traits::align()))
        std::fill(begin(), end(), chSymbol);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::assign
//
//!\brief  Assign string
//!\param  pszSource - source string pointer
//!\param  nSymbols  - source string size
//!\author Khrapov
//!\date   27.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(
    const_pointer pszSource,
    size_type     nSymbols) noexcept
{
    if (resize(nSymbols, Traits::align()))
        std::memmove(data(), pszSource, nSymbols * sizeof(value_type));
}

//==============================================================================
//!\fn                  qx::basic_string<Traits>::assign
//
//!\brief  Assign by const pointer
//!\param  pSource - const pointer
//!\author Khrapov
//!\date   27.08.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(const_pointer pszSource) noexcept
{
    if (pszSource != data())
        assign(pszSource, Traits::length(pszSource));
}

//==============================================================================
//!\fn                  qx::basic_string<Traits>::assign
//
//!\brief  Assign by another string
//!\param  sAnother - another string
//!\author Khrapov
//!\date   27.08.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(const basic_string& sAnother) noexcept
{
    if (sAnother.data() != data())
        assign(sAnother.data());
}

//==============================================================================
//!\fn                    basic_string<Traits>::assign
//
//!\brief  Assign by moving from another string
//!\param  sAnother - another string
//!\author Khrapov
//!\date   7.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(basic_string&& sAnother) noexcept
{
    std::swap(m_Data, sAnother.m_Data);
}

//==============================================================================
//!\fn             qx::basic_string<Traits>::assign<FwdIt>
//
//!\brief  Assign by iterators
//!\param  itFirst - first iterator of source
//!\param  itLast  - last iterator of source
//!\author Khrapov
//!\date   21.03.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline void basic_string<Traits>::assign(FwdIt itFirst, FwdIt itLast) noexcept
{
    clear();
    for (FwdIt it = itFirst; it != itLast; ++it)
        push_back(*it);
}

//==============================================================================
//!\fn               basic_string<Traits>::assign<String, >
//
//!\brief  Assign by char container
//!\param  sAnother - char container
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline void basic_string<Traits>::assign(const String& sAnother) noexcept
{
    assign(sAnother.cbegin(), sAnother.cend());
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::format
//
//!\brief  Format string
//!\param  pszFormat - format pattern. this str as pszFormat is UB
//!\param  ...       - arguments
//!\author Khrapov
//!\date   29.10.2019
//==============================================================================
template<class Traits>
void basic_string<Traits>::format(const_pointer pszFormat, ...) noexcept
{
    va_list args;
    va_start(args, pszFormat);
    vformat(pszFormat, args);
    va_end(args);
}

//==============================================================================
//!\fn                   basic_string<Traits>::vformat
//
//!\brief  Format string with given va_args
//!\param  pszFormat - format pattern. this str as pszFormat is UB
//!\param  args      - args pack
//!\author Khrapov
//!\date   5.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::vformat(
    const_pointer pszFormat,
    va_list       args) noexcept
{
    va_list args_copy;
    va_copy(args_copy, args);
    int length = Traits::vsnprintf(nullptr, 0, pszFormat, args_copy);
    va_end(args_copy);

    if (length > 0 && resize(static_cast<size_type>(length), Traits::align()))
        Traits::vsnprintf(data(), static_cast<size_type>(length) + 1, pszFormat, args);
}

//==============================================================================
//!\fn             qx::basic_string<Traits>::sformat<...Args>
//
//!\brief  Static format string
//!\param  pFormat - format pattern
//!\param  ...args - arguments
//!\retval         - result string
//!\author Khrapov
//!\date   29.10.2019
//==============================================================================
template<class Traits>
template<class ...Args>
inline basic_string<Traits> basic_string<Traits>::sformat(
    const_pointer pszFormat,
    Args...       args) noexcept
{
    basic_string str;
    str.format(pszFormat, args...);
    return std::move(str);
}

//==============================================================================
//!\fn           qx::basic_string<Traits>::append_format
//
//!\brief  Format string and uppend to the current string
//!\param  pszFormat - format pattern. this str as pszFormat is UB
//!\param  ...       - arguments
//!\author Khrapov
//!\date   31.12.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::append_format(
    const_pointer pszFormat,
    ...) noexcept
{
    va_list args;
    va_start(args, pszFormat);
    append_vformat(pszFormat, args);
    va_end(args);
}

//==============================================================================
//!\fn               basic_string<Traits>::append_vformat
//
//!\brief  Format string and uppend to the current string
//!\param  pszFormat - format pattern. this str as pszFormat is UB
//!\param  args      - args pack
//!\author Khrapov
//!\date   31.12.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::append_vformat(
    const_pointer pszFormat,
    va_list       args) noexcept
{
    va_list args_copy;
    va_copy(args_copy, args);
    int length = Traits::vsnprintf(nullptr, 0, pszFormat, args_copy);
    va_end(args_copy);

    const size_type nSize = size();
    if (length > 0 && resize(nSize + static_cast<size_type>(length), Traits::align()))
        Traits::vsnprintf(data() + nSize, static_cast<size_type>(length) + 1, pszFormat, args);
}

//==============================================================================
//!\fn                    basic_string<Traits>::swap
//
//!\brief  Swap this str and other
//!\param  sOther - other str
//!\author Khrapov
//!\date   1.01.2021
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::swap(basic_string& sOther) noexcept
{
    std::swap(m_Data, sOther.m_Data);
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::reserve
//
//!\brief  Reserve memory for the string
//!\param  nCapacity - new capacity
//!\retval           - string capacity
//!\author Khrapov
//!\date   29.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::reserve(
    size_type nCapacity) noexcept
{
    if (nCapacity > capacity())
        resize(nCapacity, Traits::align(), string_resize_type::reserve);

    return capacity();
}
//==============================================================================
//!\fn            qx::basic_string<Traits>::shrink_to_fit
//
//!\brief  Fit allocated size to string's actual size
//!\author Khrapov
//!\date   29.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::shrink_to_fit(void) noexcept
{
    if (!m_Data.is_small() && capacity() > size())
        resize(size(), 0, string_resize_type::shrink_to_fit);
}

//==============================================================================
//!\fn                   qx::basic_string<Traits>::free
//
//!\brief  Clear string and free allocated memory
//!\author Khrapov
//!\date   27.08.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::free(void) noexcept
{
    m_Data.free();
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::substr
//
//!\brief  Get substring
//!\param  nPos     - start index
//!\param  nSymbols - string size (npos - to the end)
//!\retval          - substring
//!\author Khrapov
//!\date   31.10.2019
//==============================================================================
template<class Traits>
inline basic_string<Traits> basic_string<Traits>::substr(
    size_type nPos,
    size_type nSymbols) const noexcept
{
    basic_string str(data() + nPos, (nSymbols != npos ? nSymbols : size() - nPos));
    return std::move(str);
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::apply_case
//
//!\brief  Apply case type to the whole string
//!\param  eCaseType - case type \see case_type
//!\author Khrapov
//!\date   31.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::apply_case(case_type eCaseType) noexcept
{
    switch (eCaseType)
    {
    case case_type::lower:
        for (value_type& ch : *this)
            ch = Traits::to_lower(ch);

        break;

    case case_type::upper:
        for (value_type& ch : *this)
            ch = Traits::to_upper(ch);

        break;
    }
}

//==============================================================================
//!\fn                    basic_string<Traits>::front
//
//!\brief  Get first char of the string
//!\retval  - first char of the string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::value_type basic_string<Traits>::front(
    void) const noexcept
{
    return at(0);
}

//==============================================================================
//!\fn                     basic_string<Traits>::back
//
//!\brief  Get last char of the string
//!\retval  - last char of the string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::value_type basic_string<Traits>::back(
    void) const noexcept
{
    return at(size() - 1);
}

//==============================================================================
//!\fn                    basic_string<Traits>::length
//
//!\brief  Get string length
//!\retval  - string length
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::length(
    void) const noexcept
{
    return size();
}

//==============================================================================
//!\fn                    basic_string<Traits>::c_str
//
//!\brief  Get pointer to string zero terminated
//!\retval  - pointer to string zero terminated
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::const_pointer basic_string<Traits>::c_str(
    void) const noexcept
{
    return data();
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::capacity
//
//!\brief  Get allocated memory size (including null terminator)
//!\author Khrapov
//!\date   29.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::capacity(
    void) const noexcept
{
    return m_Data.capacity();
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::max_size
//
//!\brief  Get the theoretical maximum of string max size
//!\author Khrapov
//!\date   17.12.2020
//==============================================================================
template<class Traits>
constexpr typename basic_string<Traits>::size_type basic_string<Traits>::max_size(
    void) noexcept
{
    return std::numeric_limits<size_type>::max()
        - 1     // npos reserved
        - 1;    // null terminator
}

//==============================================================================
//!\fn                  qx::basic_string<Traits>::to<To>
//
//!\brief  Convert string to specified type
//!\retval  - value if succeeded or nullopt
//!\author Khrapov
//!\date   11.09.2020
//==============================================================================
template<class Traits>
template<typename To>
inline std::optional<To> basic_string<Traits>::to(void) const noexcept
{
    std::optional<To> optResult = std::nullopt;

    if constexpr (std::is_pod_v<To>
               || std::is_pointer_v<To>
               || std::is_same_v<To, std::nullptr_t>)
    {
        if constexpr (std::is_same_v<To, std::nullptr_t>)
        {
            if (compare(QX_STR_PREFIX(typename Traits::value_type, "nullptr")) == 0)
                optResult = nullptr;
        }
        else if constexpr (std::is_same_v<To, bool>)
        {
            if (compare(QX_STR_PREFIX(typename Traits::value_type, "true")) == 0)
                optResult = true;
            else
                optResult = false;
        }
        else if (auto pszFormat = get_format_specifier<To>())
        {
            To result;
            int nConvertedArgs = Traits::sscanf(data(), pszFormat, &result);
            if (nConvertedArgs == 1)
                optResult = result;
        }
    }
    else
    {
        To result;
        sstream_type ss(data());
        ss >> result;
        optResult = result;
    }

    return optResult;
}

//==============================================================================
//!\fn                  qx::basic_string<Traits>::copy
//
//!\brief  Copies a substring [nPos, nPos + nCount) to character string pointed to by pDest
//!\param  pDest     - pointer to the destination character string
//!\param  nCount    - length of the substring
//!\param  nPos      - position of the first character to include
//!\retval pszFormat - number of characters copied
//!\author Khrapov
//!\date   31.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::copy(
    pointer   pDest,
    size_type nCount,
    size_type nPos) const noexcept
{
    size_type nCharsToCopy = 0;

    if (pDest && nCount > 0 && nPos < size())
    {
        nCharsToCopy = std::min(nPos + nCount, size()) - nPos;
        std::memcpy(pDest, data() + nPos, nCharsToCopy * sizeof(value_type));
    }

    return nCharsToCopy;
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::from<From>
//
//!\brief   Construct string from custom type
//!\details overloaded operator<< of data types have to be noexcept
//!\param   data      - data of type From
//!\param   pszFormat - format string if default is not enough
//!\author  Khrapov
//!\date    24.03.2020
//==============================================================================
template<class Traits>
template<typename From>
inline void basic_string<Traits>::from(
    const From  & data,
    const_pointer pszFormat) noexcept
{
    if constexpr (std::is_pod_v<From>
               || std::is_pointer_v<From>
               || std::is_same_v<From, std::nullptr_t>)
    {
        if (!pszFormat)
        {
            if constexpr (std::is_same_v <From, std::nullptr_t>)
            {
                pszFormat = QX_STR_PREFIX(typename Traits::value_type, "nullptr");
            }
            else if constexpr (std::is_same_v<From, bool>)
            {
                pszFormat = data
                    ? QX_STR_PREFIX(typename Traits::value_type, "true")
                    : QX_STR_PREFIX(typename Traits::value_type, "false");
            }
            else
                pszFormat = get_format_specifier<From>();
        }

        if (pszFormat)
            format(pszFormat, data);
    }
    else
    {
        sstream_type ss;
        ss << data;
        assign(ss.str());
    }
}

//==============================================================================
//!\fn              qx::basic_string<Traits>::sfrom<From>
//
//!\brief  Construct string from custom type and get it
//!\param  data      - data of type From
//!\param  pszFormat - format string if default is not enough
//!\retval           - constructed string
//!\author Khrapov
//!\date   24.03.2020
//==============================================================================
template<class Traits>
template<typename From>
inline basic_string<Traits> basic_string<Traits>::sfrom(
    const From&   data,
    const_pointer pszFormat) noexcept
{
    basic_string str;
    str.from(data, pszFormat);
    return std::move(str);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::append
//
//!\brief  Append char to the current
//!\param  chSymbol - char to append
//!\author Khrapov
//!\date   31.12.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::append(value_type chSymbol) noexcept
{
    append(&chSymbol, 1);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::append
//
//!\brief  Append string to the current
//!\param  pszStr   - source string
//!\param  nSymbols - source string size
//!\author Khrapov
//!\date   27.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::append(
    const_pointer pszStr,
    size_type     nSymbols) noexcept
{
    const size_type nSize = size();
    const size_type nSizeSource = nSymbols == npos
        ? Traits::length(pszStr)
        : nSymbols;

    if (resize(nSize + nSizeSource, Traits::align()))
        std::memcpy(data() + nSize, pszStr, nSizeSource * sizeof(value_type));
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::append
//
//!\brief  Append string to the current
//!\param  sStr - source string
//!\author Khrapov
//!\date   31.12.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::append(const basic_string& sStr) noexcept
{
    append(sStr.data(), sStr.size());
}

//==============================================================================
//!\fn                basic_string<Traits>::append<FwdIt>
//
//!\brief  Append string to the current
//!\param  itBegin - other string begin iterator
//!\param  itEnd   - other end begin iterator
//!\author Khrapov
//!\date   23.10.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline void basic_string<Traits>::append(FwdIt itBegin, FwdIt itEnd) noexcept
{
    for (auto it = itBegin; it != itEnd; ++it)
        push_back(*it);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::append
//
//!\brief  Append string to the current
//!\param  sStr - source string
//!\author Khrapov
//!\date   31.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline void basic_string<Traits>::append(const String& sStr) noexcept
{
    append(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  nPos     - first char index
//!\param  chSymbol - symbol to insert
//!\retval           - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type  nPos,
    value_type chSymbol) noexcept
{
    return insert(nPos, &chSymbol, 1);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  nPos      - first char index
//!\param  pszSourse - sourse string
//!\param  nSymbols  - number of symbols to insert
//!\retval           - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type     nPos,
    const_pointer pszSourse,
    size_type     nSymbols) noexcept
{
    const size_type nSize = size();
    const size_type nSizeSource = nSymbols == npos
        ? Traits::length(pszSourse)
        : nSymbols;

    if (nSizeSource > 0 && resize(nSize + nSizeSource, Traits::align()))
    {
        std::memmove(
            data() + nPos + nSizeSource,
            data() + nPos,
            (nSize - nPos) * sizeof(value_type));

        std::memcpy(
            data() + nPos,
            pszSourse,
            nSizeSource * sizeof(value_type));

        return nPos + nSizeSource;
    }
    else
        return npos;
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  nPos  - first char index
//!\param  sWhat - sourse string
//!\retval       - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type           nPos,
    const basic_string& sWhat) noexcept
{
    return insert(nPos, sWhat.data(), sWhat.size());
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  nPos        - first char index
//!\param  itWhatBegin - sourse first iterator
//!\param  itWhatEnd   - sourse last iterator
//!\retval             - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type   nPos,
    FwdIt       itWhatBegin,
    FwdIt       itWhatEnd) noexcept
{
    if constexpr (is_random_access_iterator_v<FwdIt>)
    {
        return insert(
            nPos,
            itWhatBegin.operator->(),
            static_cast<size_type>(itWhatEnd - itWhatBegin));
    }
    else
    {
        size_type nWhatSize = 0;
        for (auto it = itWhatBegin; it != itWhatEnd; ++it)
            nWhatSize++;

        size_type nStartSymbols = size();
        if (nWhatSize > 0 && resize(nStartSymbols + nWhatSize, Traits::align()))
        {
            std::memmove(
                data() + nPos + nWhatSize,
                data() + nPos,
                (nStartSymbols - nPos) * sizeof(value_type));

            size_type nWhatPos = 0;
            for (auto it = itWhatBegin; it != itWhatEnd; ++it)
            {
                at(nPos + nWhatPos) = *it;
                nWhatPos++;
            }

            return nPos + nWhatSize;
        }
        else
            return npos;
    }
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  nPos  - first char index
//!\param  sWhat - sourse string
//!\retval       - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type nPos,
    String    sWhat) noexcept
{
    return insert(static_cast<size_type>(nPos), sWhat.cbegin(), sWhat.cend());
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  itPos    - first char iterator
//!\param  chSymbol - symbol to insert
//!\retval          - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator  itPos,
    value_type      chSymbol) noexcept
{
    return insert(static_cast<size_type>(itPos - cbegin()), chSymbol);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  itPos     - first char iterator
//!\param  pszSourse - sourse string
//!\param  nSymbols  - number of symbols to insert
//!\retval           - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator  itPos,
    const_pointer   pszWhat,
    size_type       nSymbols) noexcept
{
    return insert(static_cast<size_type>(itPos - cbegin()), pszWhat, nSymbols);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  itPos - first char iterator
//!\param  sWhat - sourse string
//!\retval       - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator      itPos,
    const basic_string& sWhat) noexcept
{
    return insert(
        static_cast<size_type>(itPos - cbegin()),
        sWhat.data(),
        sWhat.size());
}

//==============================================================================
//!\fn                    basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  itPos       - first char iterator
//!\param  itWhatBegin - source string first iterator
//!\param  itWhatEnd   - source string last iterator
//!\retval             - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator  itPos,
    FwdIt           itWhatBegin,
    FwdIt           itWhatEnd) noexcept
{
    return insert(
        static_cast<size_type>(itPos - begin()),
        itWhatBegin,
        itWhatEnd);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  itPos - first char iterator
//!\param  sWhat - sourse string
//!\retval       - pos of char after last char of inserted string or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator itPos,
    String         sWhat) noexcept
{
    return insert(
        static_cast<size_type>(itPos - begin()),
        sWhat.cbegin(),
        sWhat.cend());
}

//==============================================================================
//!\fn                  basic_string<Traits>::push_back
//
//!\brief  Insert char in the end of the string
//!\param  chSymbol - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::push_back(value_type chSymbol) noexcept
{
    insert(size(), &chSymbol, 1);
}

//==============================================================================
//!\fn                  basic_string<Traits>::push_front
//
//!\brief  Insert char in the beginning of the string
//!\param  chSymbol - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::push_front(value_type chSymbol) noexcept
{
    insert(0, &chSymbol, 1);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::erase
//
//!\brief  Erase substrung
//!\param  itFirst - first substr char iterator
//!\param  itLast  - last substr char iterator (excluded)
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(
    iterator itFirst,
    iterator itLast) noexcept
{
    if (itFirst < itLast)
    {
        size_type nStartSize = size();
        size_type nSymbolsToCopy = itLast != end()
            ? Traits::length(itLast.operator->())
            : 0;

        if (nSymbolsToCopy > 0)
        {
            std::memcpy(
                itFirst.operator->(),
                itLast.operator->(),
                nSymbolsToCopy * sizeof(value_type));
        }

        resize(static_cast<size_type>(nStartSize - (itLast - itFirst)), Traits::align());
    }
}

//==============================================================================
//!\fn                    basic_string<Traits>::erase
//
//!\brief  Erase on iterator
//!\param  itPos - iterator
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(iterator itPos) noexcept
{
    erase(itPos, itPos + 1);
}

//==============================================================================
//!\fn                    basic_string<Traits>::erase
//
//!\brief  Erase on position
//!\param  nPos - position
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(size_type nPos) noexcept
{
    erase(iterator(this, nPos), iterator(this, nPos + 1));
}

//==============================================================================
//!\fn                    basic_string<Traits>::erase
//
//!\brief  Erase substring
//!\param  nPos     - start position
//!\param  nSymbols - number of symbols
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(
    size_type nPos,
    size_type nSymbols) noexcept
{
    erase(iterator(this, nPos), iterator(this, nPos + nSymbols));
}

//==============================================================================
//!\fn                   basic_string<Traits>::pop_back
//
//!\brief  Erase last char and return it
//!\retval - last char
//!\author Khrapov
//!\date   18.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::value_type basic_string<Traits>::pop_back(
    void) noexcept
{
    value_type chRet = back();
    erase(size() - 1);
    return chRet;
}

//==============================================================================
//!\fn                   basic_string<Traits>::pop_front
//
//!\brief  Erase first char and return it
//!\retval - first char
//!\author Khrapov
//!\date   18.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::value_type basic_string<Traits>::pop_front(
    void) noexcept
{
    value_type chRet = front();
    erase(0);
    return chRet;
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_left
//
//!\brief  Trim the string to the left (whitespace characters)
//!\retval - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    void) noexcept
{
    return _trim_left([](value_type ch) { return Traits::is_space(ch); });
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_left
//
//!\brief  Trim the string to the left
//!\param  chSymbol - symbol to delete
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    value_type chSymbol) noexcept
{
    return _trim_left([chSymbol](value_type ch) { return ch == chSymbol; });
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_left
//
//!\brief  Trim the string to the left
//!\param  pszStr - string with symbols to delete
//!\retval        - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    const_pointer pszStr) noexcept
{
    return _trim_left([pszStr](value_type ch)
        {
            for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0'); j++)
                if (pszStr[j] == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_left
//
//!\brief  Trim the string to the left
//!\param  pszStr   - string with symbols to delete
//!\param  nStrSize - string size
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    const_pointer pszStr,
    size_type     nStrSize) noexcept
{
    return _trim_left([pszStr, nStrSize](value_type ch)
        {
            for (size_type j = 0; j < nStrSize; j++)
                if (pszStr[j] == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_left
//
//!\brief  Trim the string to the left
//!\param  sStr - string with symbols to delete
//!\retval      - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    const basic_string& sStr) noexcept
{
    return trim_left(sStr.data(), sStr.size());
}

//==============================================================================
//!\fn             basic_string<Traits>::trim_left<FwdIt>
//
//!\brief  Trim the string to the left
//!\param  itBegin - begin it of string with symbols to delete
//!\param  itEnd   - begin it of string with symbols to delete
//!\retval         - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    FwdIt itBegin,
    FwdIt itEnd) noexcept
{
    return _trim_left([itBegin, itEnd](auto ch)
        {
            for (auto it = itBegin; it != itEnd; ++it)
                if (*it == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn           basic_string<Traits>::trim_left<String, >
//
//!\brief  Trim the string to the left
//!\param  sStr - string with symbols to delete
//!\retval      - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    const String& sStr) noexcept
{
    return trim_left(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_right
//
//!\brief  Trim the string to the right (whitespace characters)
//!\retval - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_right(
    void) noexcept
{
    return _trim_right([](value_type ch) { return Traits::is_space(ch); });
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_right
//
//!\brief  Trim the string to the right
//!\param  chSymbol - symbol to delete
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_right(
    value_type chSymbol) noexcept
{
    return _trim_right([chSymbol](value_type ch) { return ch == chSymbol; });
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_right
//
//!\brief  Trim the string to the right
//!\param  pszStr - string with symbols to delete
//!\retval        - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_right(
    const_pointer pszStr) noexcept
{
    return _trim_right([pszStr](value_type ch)
        {
            for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0'); j++)
                if (pszStr[j] == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_right
//
//!\brief  Trim the string to the right
//!\param  pszStr   - string with symbols to delete
//!\param  nStrSize - string size
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_right(
    const_pointer pszStr,
    size_type     nStrSize) noexcept
{
    return _trim_right([pszStr, nStrSize](value_type ch)
        {
            for (size_type j = 0; j < nStrSize; j++)
                if (pszStr[j] == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn                basic_string<Traits>::trim_right
//
//!\brief  Trim the string to the right
//!\param  sStr - string with symbols to delete
//!\retval      - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_right(
    const basic_string& sStr) noexcept
{
    return trim_right(sStr.data(), sStr.size());
}

//==============================================================================
//!\fn             basic_string<Traits>::trim_right<FwdIt>
//
//!\brief  Trim the string to the right
//!\param  itBegin - begin it of string with symbols to delete
//!\param  itEnd   - begin it of string with symbols to delete
//!\retval         - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_right(
    FwdIt itBegin,
    FwdIt itEnd) noexcept
{
    return _trim_right([itBegin, itEnd](auto ch)
        {
            for (auto it = itBegin; it != itEnd; ++it)
                if (*it == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn           basic_string<Traits>::trim_right<String, >
//
//!\brief  Trim the string to the right
//!\param  sStr - string with symbols to delete
//!\retval      - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_right(
    const String& sStr) noexcept
{
    return trim_right(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn                   basic_string<Traits>::trim
//
//!\brief  Trim the string to the both sides (whitespace characters)
//!\retval - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    void) noexcept
{
    return _trim([](value_type ch) { return Traits::is_space(ch); });
}

//==============================================================================
//!\fn                   basic_string<Traits>::trim
//
//!\brief  Trim the string to the both sides
//!\param  chSymbol - symbol to delete
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    value_type chSymbol) noexcept
{
    return _trim([chSymbol](value_type ch) { return ch == chSymbol; });
}

//==============================================================================
//!\fn                   basic_string<Traits>::trim
//
//!\brief  Trim the string to the both sides
//!\param  pszStr - string with symbols to delete
//!\retval        - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    const_pointer pszStr) noexcept
{
    return _trim([pszStr](value_type ch)
        {
            for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0'); j++)
                if (pszStr[j] == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn                   basic_string<Traits>::trim
//
//!\brief  Trim the string to the both sides
//!\param  pszStr   - string with symbols to delete
//!\param  nStrSize - string size
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    const_pointer pszStr,
    size_type     nStrSize) noexcept
{
    return _trim([pszStr, nStrSize](value_type ch)
        {
            for (size_type j = 0; j < nStrSize; j++)
                if (pszStr[j] == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn                   basic_string<Traits>::trim
//
//!\brief  Trim the string to the both sides
//!\param  sStr - string with symbols to delete
//!\retval      - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    const basic_string& sStr) noexcept
{
    return trim(sStr.data(), sStr.size());
}

//==============================================================================
//!\fn                basic_string<Traits>::trim<FwdIt>
//
//!\brief  Trim the string to the both sides
//!\param  itBegin - begin it of string with symbols to delete
//!\param  itEnd   - begin it of string with symbols to delete
//!\retval         - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    FwdIt itBegin,
    FwdIt itEnd) noexcept
{
    return _trim([itBegin, itEnd](auto ch)
        {
            for (auto it = itBegin; it != itEnd; ++it)
                if (*it == ch)
                    return true;

            return false;
        });
}

//==============================================================================
//!\fn              basic_string<Traits>::trim<String, >
//
//!\brief  Trim the string to the both sides
//!\param  sStr - string with symbols to delete
//!\retval      - number of deleted symbols
//!\author Khrapov
//!\date   24.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    const String& sStr) noexcept
{
    return trim(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn                   qx::basic_string<Traits>::remove
//
//!\brief  Remove the first occurrence of a substring in a string
//!\param  chSymbol - char to remove
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index
//!\retval          - position where the first occurrence was or npos
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    value_type chSymbol,
    size_type  nBegin,
    size_type  nEnd) noexcept
{
    size_type nPos = find(chSymbol, nBegin, nEnd);

    if (nPos != npos)
        erase(nPos, 1);

    return nPos;
}

//==============================================================================
//!\fn                   qx::basic_string<Traits>::remove
//
//!\brief  Remove the first occurrence of a substring in a string
//!\param  pszStr   - c-string to remove
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index
//!\param  nStrSize - c-string size
//!\retval          - position where the first occurrence was or npos
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    const_pointer pszStr,
    size_type     nBegin,
    size_type     nEnd,
    size_type     nStrSize) noexcept
{
    size_type nLocalStrSize = nStrSize != npos
        ? nStrSize
        : Traits::length(pszStr);

    size_type nPos = find(pszStr, nBegin, nLocalStrSize, nEnd);

    if (nPos != npos)
        erase(nPos, nLocalStrSize);

    return nPos;
}

//==============================================================================
//!\fn                   qx::basic_string<Traits>::remove
//
//!\brief  Remove the first occurrence of a substring in a string
//!\param  sStr   - string to remove
//!\param  nBegin - start searching index
//!\param  nEnd   - end searching index
//!\retval        - position where the first occurrence was or npos
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    const basic_string& sStr,
    size_type           nBegin,
    size_type           nEnd) noexcept
{
    size_type nPos = find(sStr, nBegin, nEnd);

    if (nPos != npos)
        erase(nPos, sStr.size());

    return nPos;
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::remove<FwdIt>
//
//!\brief  Remove the first occurrence of a substring in a string
//!\param  itBegin - string begin iterator
//!\param  itEnd   - string end iterator
//!\param  nBegin  - start searching index
//!\param  nEnd    - end searching index
//!\retval         - position where the first occurrence was or npos
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    FwdIt     itBegin,
    FwdIt     itEnd,
    size_type nBegin,
    size_type nEnd) noexcept
{
    size_type nPos = find(itBegin, itEnd, nBegin, nEnd);

    if (nPos != npos)
        erase(nPos, static_cast<size_type>(std::distance(itBegin, itEnd)));

    return nPos;
}

//==============================================================================
//!\fn              qx::basic_string<Traits>::remove<String, >
//
//!\brief  Remove the first occurrence of a substring in a string
//!\param  sStr   - string to remove
//!\param  nBegin - start searching index
//!\param  nEnd   - end searching index
//!\retval        - position where the first occurrence was or npos
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    const String& sStr,
    size_type     nBegin,
    size_type     nEnd) noexcept
{
    return remove(sStr.cbegin(), sStr.cend(), nBegin, nEnd);
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::remove_prefix
//
//!\brief  Remove string prefix if matches
//!\param  chSymbol - char to remove
//!\retval          - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::remove_prefix(value_type chSymbol) noexcept
{
    return remove(chSymbol, 0u, 1u) != npos;
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::remove_prefix
//
//!\brief  Remove string prefix if matches
//!\param  pszStr   - c-string to remove
//!\param  nStrSize - c-string size
//!\retval          - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::remove_prefix(
    const_pointer pszStr,
    size_type     nStrSize) noexcept
{
    return remove(pszStr, 0u, nStrSize, nStrSize) != npos;
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::remove_prefix
//
//!\brief  Remove string prefix if matches
//!\param  sStr   - string to remove
//!\retval        - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::remove_prefix(
    const basic_string& sStr) noexcept
{
    return remove(sStr, 0u, sStr.size()) != npos;
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::remove_prefix<Traits>
//
//!\brief  Remove string prefix if matches
//!\param  itBegin - string to remove begin iterator
//!\param  itEnd   - string to remove end iterator
//!\retval         - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::remove_prefix(
    FwdIt itBegin,
    FwdIt itEnd) noexcept
{
    return remove(
        itBegin,
        itEnd,
        0u,
        static_cast<size_type>(std::distance(itBegin, itEnd))) != npos;
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::remove_prefix<String, >
//
//!\brief  Remove string prefix if matches
//!\param  sStr   - string to remove
//!\retval        - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::remove_prefix(const String& sStr) noexcept
{
    return remove_prefix(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::remove_suffix
//
//!\brief  Remove string suffix if matches
//!\param  chSymbol - char to remove
//!\retval          - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::remove_suffix(value_type chSymbol) noexcept
{
    const size_type nSize = size();
    return remove(
        chSymbol,
        nSize - 1,
        nSize) != npos;
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::remove_suffix
//
//!\brief  Remove string suffix if matches
//!\param  pszStr   - c-string to remove
//!\param  nStrSize - c-string size
//!\retval          - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::remove_suffix(
    const_pointer pszStr,
    size_type     nStrSize) noexcept
{
    const size_type nSize = size();
    const size_type nLocalStrSize = nStrSize != npos
        ? nStrSize
        : Traits::length(pszStr);

    return remove(
        pszStr,
        nSize - nLocalStrSize,
        nSize,
        nLocalStrSize) != npos;
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::remove_suffix
//
//!\brief  Remove string suffix if matches
//!\param  sStr   - string to remove
//!\retval        - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::remove_suffix(
    const basic_string& sStr) noexcept
{
    return remove_suffix(sStr.data(), sStr.size());
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::remove_suffix<Traits>
//
//!\brief  Remove string suffix if matches
//!\param  itBegin - string to remove begin iterator
//!\param  itEnd   - string to remove end iterator
//!\retval         - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::remove_suffix(
    FwdIt itBegin,
    FwdIt itEnd) noexcept
{
    const size_type nSize = size();
    return remove(
        itBegin,
        itEnd,
        nSize - static_cast<size_type>(std::distance(itBegin, itEnd)),
        nSize) != npos;
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::remove_suffix<String, >
//
//!\brief  Remove string suffix if matches
//!\param  sStr   - string to remove
//!\retval        - true if removed
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::remove_suffix(const String& sStr) noexcept
{
    return remove_suffix(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn                   qx::basic_string<Traits>::remove
//
//!\brief  Remove all occurrences of a substring in a string
//!\param  chSymbol - char to remove
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index
//!\retval          - number of deleted occurrences
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove_all(
    value_type chSymbol,
    size_type  nBegin,
    size_type  nEnd) noexcept
{
    size_type nOccurrences = 0;
    size_type nLastOccurrencePos = nBegin;

    do
    {
        nOccurrences++;
        nLastOccurrencePos = remove(chSymbol, nLastOccurrencePos, nEnd);
    } while (nLastOccurrencePos != npos);

    return nOccurrences - 1;
}

//==============================================================================
//!\fn                   qx::basic_string<Traits>::remove
//
//!\brief  Remove all occurrences of a substring in a string
//!\param  pszStr - c-string to remove
//!\param  nBegin - start searching index
//!\param  nEnd   - end searching index
//!\param  nEnd   - c-string size
//!\retval        - number of deleted occurrences
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove_all(
    const_pointer pszStr,
    size_type     nBegin,
    size_type     nEnd,
    size_type     nStrSize) noexcept
{
    size_type nOccurrences = 0;
    size_type nLastOccurrencePos = nBegin;

    do
    {
        nOccurrences++;
        nLastOccurrencePos = remove(pszStr, nLastOccurrencePos, nEnd, nStrSize);
    } while (nLastOccurrencePos != npos);

    return nOccurrences - 1;
}

//==============================================================================
//!\fn                   qx::basic_string<Traits>::remove
//
//!\brief  Remove all occurrences of a substring in a string
//!\param  sStr   - string to remove
//!\param  nBegin - start searching index
//!\param  nEnd   - end searching index
//!\retval        - number of deleted occurrences
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove_all(
    const basic_string& sStr,
    size_type           nBegin,
    size_type           nEnd) noexcept
{
    return remove_all(sStr.data(), nBegin, nEnd, sStr.size());
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::remove<FwdIt>
//
//!\brief  Remove all occurrences of a substring in a string
//!\param  itBegin - string begin iterator
//!\param  itEnd   - string end iterator
//!\param  nBegin  - start searching index
//!\param  nEnd    - end searching index
//!\retval         - number of deleted occurrences
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove_all(
    FwdIt     itFirst,
    FwdIt     itLast,
    size_type nBegin,
    size_type nEnd) noexcept
{
    size_type nOccurrences = 0;
    size_type nLastOccurrencePos = nBegin;

    do
    {
        nOccurrences++;
        nLastOccurrencePos = remove(itFirst, itLast, nLastOccurrencePos, nEnd);
    } while (nLastOccurrencePos != npos);

    return nOccurrences - 1;
}

//==============================================================================
//!\fn              qx::basic_string<Traits>::remove<String, >
//
//!\brief  Remove all occurrences of a substring in a string
//!\param  sStr   - string to remove
//!\param  nBegin - start searching index
//!\param  nEnd   - end searching index
//!\retval        - number of deleted occurrences
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove_all(
    const String& sStr,
    size_type     nBegin,
    size_type     nEnd) noexcept
{
    return remove_all(sStr.cbegin(), sStr.cend(), nBegin, nEnd);
}

//==============================================================================
//!\fn              qx::basic_string<Traits>::replace<replace>
//
//!\brief  Replace first occurence of sFind with sReplace
//!\param  sFind    - string to find and replase
//!\param  sReplace - string to replace with
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index
//!\retval          - pos of char after last char of replaced string or npos
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class T1, class T2>
inline typename basic_string<Traits>::size_type basic_string<Traits>::replace(
    T1        sFind,
    T2        sReplace,
    size_type nBegin,
    size_type nEnd) noexcept
{
    size_type nPos = remove(sFind, nBegin, nEnd);
    if (nPos != npos)
        return insert(nPos, sReplace);
    else
        return npos;
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::replace_all<replace>
//
//!\brief  Replace all occurences of sFind with sReplace
//!\param  sFind    - string to find and replase
//!\param  sReplace - string to replace with
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index
//!\retval          - number of replaced occurences
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class T1, class T2>
inline typename basic_string<Traits>::size_type basic_string<Traits>::replace_all(
    T1        sFind,
    T2        sReplace,
    size_type nBegin,
    size_type nEnd) noexcept
{
    size_type nOccurences = 0;
    size_type nPos = nBegin;

    do
    {
        nPos = replace(sFind, sReplace, nPos, nEnd);
        if (nPos != npos)
            nOccurences++;
    } while (nPos != npos);

    return nOccurences;
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::compare
//
//!\brief  Performs a binary comparison of the characters
//!\param  chSymbol - symbol to compare
//!\retval          -   < 0 the first character that does not match has a lower value in this than in chSymbol
//                        0 the contents of both strings are equal
//                      > 0 the first character that does not match has a greater value in this than in chSymbol
//!\author Khrapov
//!\date   30.12.2020
//==============================================================================
template<class Traits>
inline int basic_string<Traits>::compare(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1);
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::compare
//
//!\brief  Performs a binary comparison of the characters
//!\param  pStr     - string to compare
//!\param  nSymbols - number of symbols to compare (0 - string is zero terminated)
//!\retval          -   < 0 the first character that does not match has a lower value in this than in pStr
//                        0 the contents of both strings are equal
//                      > 0 the first character that does not match has a greater value in this than in pStr
//!\author Khrapov
//!\date   28.10.2019
//==============================================================================
template<class Traits>
inline int basic_string<Traits>::compare(
    const_pointer pStr,
    size_type     nSymbols) const noexcept
{
    if (nSymbols > 0)
        return Traits::compare_n(data(), pStr, nSymbols);
    else
        return Traits::compare(data(), pStr);
}

//==============================================================================
//!\fn               qx::basic_string<Traits>::compare
//
//!\brief  Performs a binary comparison of the characters
//!\param  sStr     - string to compare
//!\retval          -   < 0 the first character that does not match has a lower value in this than in sStr
//                        0 the contents of both strings are equal
//                      > 0 the first character that does not match has a greater value in this than in sStr
//!\author Khrapov
//!\date   30.12.2020
//==============================================================================
template<class Traits>
inline int basic_string<Traits>::compare(const basic_string& sStr) const noexcept
{
    return compare(sStr.data(), sStr.size());
}

//==============================================================================
//!\fn           qx::basic_string<Traits>::compare<FwdIt>
//
//!\brief  Performs a binary comparison of the characters
//!\param  itBegin  - string to compare begin iterator
//!\param  itEnd    - string to compare end iterator
//!\retval          -   < 0 the first character that does not match has a lower value in this than in [itBegin, itEnd]
//                        0 the contents of both strings are equal
//                      > 0 the first character that does not match has a greater value in this than in [itBegin, itEnd]
//!\author Khrapov
//!\date   30.12.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline int basic_string<Traits>::compare(
    FwdIt itBegin,
    FwdIt itEnd) const noexcept
{
    return iter_strcmp(cbegin(), cend(), itBegin, itEnd);
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::compare<Stringm >
//
//!\brief  Performs a binary comparison of the characters
//!\param  sStr     - string to compare
//!\retval          -   < 0 the first character that does not match has a lower value in this than in sStr
//                        0 the contents of both strings are equal
//                      > 0 the first character that does not match has a greater value in this than in sStr
//!\author Khrapov
//!\date   30.12.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline int basic_string<Traits>::compare(const String& sStr) const noexcept
{
    return compare(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find
//
//!\brief  Find substring
//!\param  chSymbol - char to find
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index (npos - to the end)
//!\retval          - substring index or npos if not found
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    value_type    chSymbol,
    size_type     nBegin,
    size_type     nEnd) const noexcept
{
    return _find(
        nBegin,
        nEnd,
        [chSymbol](const_pointer pCurrentChar)
        {
            return *pCurrentChar == chSymbol;
        });
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find
//
//!\brief  Find substring
//!\param  pszWhat   - c-string to find
//!\param  nBegin    - start searching index
//!\param  nWhatSize - c-string length
//!\param  nEnd      - end searching index (npos - to the end).
//!\retval           - substring index
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nWhatSize,
    size_type     nEnd) const noexcept
{
    size_type nLocalWhatSize = nWhatSize != npos
        ? nWhatSize
        : Traits::length(pszWhat);

    return _find(
        nBegin,
        nEnd,
        [pszWhat, nLocalWhatSize](const_pointer pCurrentChar)
        {
            return !Traits::compare_n(pszWhat, pCurrentChar, nLocalWhatSize);
        });
}

//==============================================================================
//!\fn                     basic_string<Traits>::find
//
//!\brief  Find substring
//!\param  sWhat    - string to find
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index
//!\retval          - substring index or npos if not found
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    const basic_string& sWhat,
    size_type           nBegin,
    size_type           nEnd) const noexcept
{
    return find(sWhat.data(), nBegin, sWhat.size(), nEnd);
}

//==============================================================================
//!\fn                 basic_string<Traits>::find<FwdIt>
//
//!\brief  Find substring
//!\param  itWhatBegin - substring begin iterator
//!\param  itWhatEnd   - substring end iterator
//!\param  nBegin      - start searching index
//!\param  nEnd        - end searching index
//!\retval             - substring index or npos if not found
//!\author Khrapov
//!\date   30.11.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    FwdIt       itWhatBegin,
    FwdIt       itWhatEnd,
    size_type   nBegin,
    size_type   nEnd) const noexcept
{
    return _find(
        nBegin,
        nEnd,
        [this, itWhatBegin, itWhatEnd, nEnd](const_pointer pCurrentChar)
        {
            return !iter_strcmp(
                const_iterator(this, static_cast<size_type>(pCurrentChar - data())),
                const_iterator(this, static_cast<size_type>(nEnd)),
                itWhatBegin,
                itWhatEnd);
        });
}

//==============================================================================
//!\fn                basic_string<Traits>::find<String, >
//
//!\brief  Find substring (reverse direction)
//!\param  sWhat  - substring
//!\param  nBegin - start searching index
//!\param  nEnd   - end searching index
//!\retval        - substring index or npos if not found
//!\author Khrapov
//!\date   30.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    String    sWhat,
    size_type nBegin,
    size_type nEnd) const noexcept
{
    return find(sWhat.cbegin(), sWhat.cend(), nBegin, nEnd);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::rfind
//
//!\brief  Find substring (reverse direction)
//!\param  chSymbol - char to find
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index
//!                   (if nBegin < end, result is equivalent of find(...))
//!\retval          - substring index or npos if not found
//!\author Khrapov
//!\date   1.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    value_type    chSymbol,
    size_type     nBegin,
    size_type     nEnd) const noexcept
{
    return _rfind(
        nBegin,
        nEnd,
        [chSymbol](const_pointer pCurrentChar)
        {
            return *pCurrentChar == chSymbol;
        });
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::rfind
//
//!\brief  Find substring (reverse direction)
//!\param  pszWhat   - c-string to find
//!\param  nBegin    - start searching index
//!\param  nWhatSize - c-string length
//!\param  nEnd      - end searching index
//!                    (if nBegin < end, result is equivalent of find(...))
//!\retval           - substring index
//!\author Khrapov
//!\date   1.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nWhatSize,
    size_type     nEnd) const noexcept
{
    size_type nLocalWhatSize = nWhatSize != npos
        ? nWhatSize
        : Traits::length(pszWhat);

    return _rfind(
        nBegin,
        nEnd,
        [pszWhat, nLocalWhatSize](const_pointer pCurrentChar)
        {
            return !Traits::compare_n(pszWhat, pCurrentChar, nLocalWhatSize);
        });
}

//==============================================================================
//!\fn                     basic_string<Traits>::rfind
//
//!\brief  Find substring (reverse direction)
//!\param  sWhat    - string to find
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index
//!                   (if nBegin < end, result is equivalent of find(...))
//!\retval          - substring index or npos if not found
//!\author Khrapov
//!\date   1.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    const basic_string& sWhat,
    size_type           nBegin,
    size_type           nEnd) const noexcept
{
    return rfind(sWhat.data(), nBegin, sWhat.size(), nEnd);
}

//==============================================================================
//!\fn                 basic_string<Traits>::rfind<FwdIt>
//
//!\brief  Find substring (reverse direction)
//!\param  itWhatBegin - substring begin iterator
//!\param  itWhatEnd   - substring end iterator
//!\param  nBegin      - start searching index
//!\param  nEnd        - end searching index
//!                      (if nBegin < end, result is equivalent of find(...))
//!\retval             - substring index or npos if not found
//!\author Khrapov
//!\date   1.01.2021
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    FwdIt       itWhatBegin,
    FwdIt       itWhatEnd,
    size_type   nBegin,
    size_type   nEnd) const noexcept
{
    return _rfind(
        nBegin,
        nEnd,
        [this, itWhatBegin, itWhatEnd, nEnd](const_pointer pCurrentChar)
        {
            return !iter_strcmp(
                const_iterator(this, static_cast<size_type>(pCurrentChar - data())),
                const_iterator(this, static_cast<size_type>(nEnd)),
                itWhatBegin,
                itWhatEnd);
        });
}

//==============================================================================
//!\fn                basic_string<Traits>::rfind<String, >
//
//!\brief  Find substring (reverse direction)
//!\param  sWhat  - substring
//!\param  nBegin - start searching index
//!\param  nEnd   - end searching index
//!\retval        - substring index or npos if not found
//!\author Khrapov
//!\date   1.01.2021
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    String    sWhat,
    size_type nBegin,
    size_type nEnd) const noexcept
{
    return rfind(sWhat.cbegin(), sWhat.cend(), nBegin, nEnd);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_first_of
//
//!\brief  Find first position of character
//!\param  chSymbol - char to find
//!\param  nPos     - position at which the search is to finish
//!\retval          - symbol index or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_first_of(
    value_type chSymbol,
    size_type  nPos) const noexcept
{
    return find(chSymbol, 0, nPos);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_first_of
//
//!\brief  Finds the first character equal to one of characters in the given character sequence
//!\param  pszWhat   - string identifying characters to search for
//!\param  nPos      - position at which the search is to finish
//!\param  nWhatSize - length of character string identifying characters to search for
//!\retval           - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_first_of(
    const_pointer pszWhat,
    size_type     nPos,
    size_type     nWhatSize) const noexcept
{
    size_type nChar = 0;
    return _find_first_of(
        nPos,
        [&nChar, pszWhat, nWhatSize]()
        {
            std::optional<value_type> ret = std::nullopt;
            if (nChar < nWhatSize)
            {
                ret = pszWhat[nChar];
                nChar++;
            }
            return ret;
        });
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_first_of
//
//!\brief  Finds the first character equal to one of characters in the given character sequence
//!\param  pszWhat   - null terminated string identifying characters to search for
//!\param  nPos      - position at which the search is to finish
//!\retval           - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_first_of(
    const_pointer pszWhat,
    size_type     nPos) const noexcept
{
    size_type nChar = 0;
    return _find_first_of(
        nPos,
        [&nChar, pszWhat]()
        {
            std::optional<value_type> ret = std::nullopt;
            if (pszWhat[nChar] != QX_CHAR_PREFIX(value_type, '\0'))
            {
                ret = pszWhat[nChar];
                nChar++;
            }
            return ret;
        });
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_first_of
//
//!\brief  Finds the first character equal to one of characters in the given character sequence
//!\param  sWhat - string identifying characters to search for
//!\param  nPos  - position at which the search is to finish
//!\retval       - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_first_of(
    const basic_string& sWhat,
    size_type           nPos) const noexcept
{
    return find_first_of(sWhat.data(), nPos, sWhat.size());
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::find_first_of<FwdIt>
//
//!\brief  Finds the first character equal to one of characters in the given character sequence
//!\param  itWhatBegin - begin it of string identifying characters to search for
//!\param  itWhatEnd   - end it of string identifying characters to search for
//!\param  nPos        - position at which the search is to finish
//!\retval             - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_first_of(
    FwdIt     itWhatBegin,
    FwdIt     itWhatEnd,
    size_type nPos) const noexcept
{
    FwdIt it = itWhatBegin;
    return _find_first_of(
        nPos,
        [&it, itWhatEnd]()
        {
            std::optional<value_type> ret = std::nullopt;
            if (it != itWhatEnd)
            {
                ret = *it;
                ++it;
            }
            return ret;
        });
}

//==============================================================================
//!\fn           qx::basic_string<Traits>::find_first_of<String, >
//
//!\brief  Finds the first character equal to one of characters in the given character sequence
//!\param  sWhat - string identifying characters to search for
//!\param  nPos  - position at which the search is to finish
//!\retval       - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_first_of(
    String    sWhat,
    size_type nPos) const noexcept
{
    return find_first_of(sWhat.cbegin(), sWhat.cend(), nPos);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_last_of
//
//!\brief  Find last position of character
//!\param  chSymbol - char to find
//!\param  nPos     - position at which the search is to finish
//!\retval          - symbol index or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(
    value_type chSymbol,
    size_type  nPos) const noexcept
{
    return rfind(chSymbol, npos, nPos);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_last_of
//
//!\brief  Finds the last character equal to one of characters in the given character sequence
//!\param  pszWhat   - string identifying characters to search for
//!\param  nPos      - position at which the search is to finish
//!\param  nWhatSize - length of character string identifying characters to search for
//!\retval           - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(
    const_pointer pszWhat,
    size_type     nPos,
    size_type     nWhatSize) const noexcept
{
    size_type nChar = 0;
    return _find_last_of(
        nPos,
        [&nChar, pszWhat, nWhatSize]()
        {
            std::optional<value_type> ret = std::nullopt;
            if (nChar < nWhatSize)
            {
                ret = pszWhat[nChar];
                nChar++;
            }
            return ret;
        });
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_last_of
//
//!\brief  Finds the last character equal to one of characters in the given character sequence
//!\param  pszWhat   - null terminated string identifying characters to search for
//!\param  nPos      - position at which the search is to finish
//!\retval           - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(
    const_pointer pszWhat,
    size_type     nPos) const noexcept
{
    size_type nChar = 0;
    return _find_last_of(
        nPos,
        [&nChar, pszWhat]()
        {
            std::optional<value_type> ret = std::nullopt;
            if (pszWhat[nChar] != QX_CHAR_PREFIX(value_type, '\0'))
            {
                ret = pszWhat[nChar];
                nChar++;
            }
            return ret;
        });
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_last_of
//
//!\brief  Finds the last character equal to one of characters in the given character sequence
//!\param  sWhat - string identifying characters to search for
//!\param  nPos  - position at which the search is to finish
//!\retval       - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(
    const basic_string& sWhat,
    size_type           nPos) const noexcept
{
    return find_last_of(sWhat.data(), nPos, sWhat.size());
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::find_last_of<FwdIt>
//
//!\brief  Finds the last character equal to one of characters in the given character sequence
//!\param  itWhatBegin - begin it of string identifying characters to search for
//!\param  itWhatEnd   - end it of string identifying characters to search for
//!\param  nPos        - position at which the search is to finish
//!\retval             - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(
    FwdIt     itWhatBegin,
    FwdIt     itWhatEnd,
    size_type nPos) const noexcept
{
    FwdIt it = itWhatBegin;
    return _find_last_of(
        nPos,
        [&it, itWhatEnd]()
        {
            std::optional<value_type> ret = std::nullopt;
            if (it != itWhatEnd)
            {
                ret = *it;
                ++it;
            }
            return ret;
        });
}

//==============================================================================
//!\fn           qx::basic_string<Traits>::find_last_of<String, >
//
//!\brief  Finds the last character equal to one of characters in the given character sequence
//!\param  sWhat - string identifying characters to search for
//!\param  nPos  - position at which the search is to finish
//!\retval       - symbol index or npos
//!\author Khrapov
//!\date   2.01.2021
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(
    String    sWhat,
    size_type nPos) const noexcept
{
    return find_last_of(sWhat.cbegin(), sWhat.cend(), nPos);
}

//==============================================================================
//!\fn                 qx::basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  chSeparator - char separator
//!\retval             - vector of strings
//!\author Khrapov
//!\date   21.03.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::vector basic_string<Traits>::split(
    const value_type chSeparator) const noexcept
{
    vector tokens;

    size_type start = 0;
    size_type end   = 0;
    while ((end = find(chSeparator, start)) != npos)
    {
        tokens.push_back(substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(substr(start));

    return std::move(tokens);
}

//==============================================================================
//!\fn                 qx::basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  pszSeparator - separator string
//!\param  nSepLen      - separator string length (npos if str is null terminated)
//!\retval              - vector of strings
//!\author Khrapov
//!\date   21.03.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::vector basic_string<Traits>::split(
    const_pointer pszSeparator,
    size_type     nSepLen) const noexcept
{
    vector tokens;

    if (nSepLen == npos)
        nSepLen = Traits::length(pszSeparator);

    size_type start = 0;
    size_type end   = 0;
    while ((end = find(pszSeparator, start, nSepLen, npos)) != npos)
    {
        tokens.push_back(substr(start, end - start));
        start = end + nSepLen;
    }
    tokens.push_back(substr(start));

    return std::move(tokens);
}

//==============================================================================
//!\fn                    basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  sSeparator - separator string
//!\retval            - vector of strings
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::vector basic_string<Traits>::split(
    const basic_string& sSeparator) const noexcept
{
    return split(sSeparator.data(), sSeparator.size());
}

//==============================================================================
//!\fn                    basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  itSepFirst - separator begin iterator
//!\param  itSepLast  - separator end iterator
//!\retval            - vector of strings
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::vector basic_string<Traits>::split(
    FwdIt itSepFirst,
    FwdIt itSepLast) const noexcept
{
    vector tokens;

    size_type nSepLen = static_cast<size_type>(std::distance(itSepFirst, itSepLast));

    size_type start = 0;
    size_type end   = 0;
    while ((end = find(itSepFirst, itSepLast, start)) != npos)
    {
        tokens.push_back(substr(start, end - start));
        start = end + nSepLen;
    }
    tokens.push_back(substr(start));

    return std::move(tokens);
}

//==============================================================================
//!\fn                    basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  sSeparator - separator string
//!\retval            - vector of strings
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline typename basic_string<Traits>::vector basic_string<Traits>::split(
    const String& sSeparator) const noexcept
{
    return split(sSeparator.cbegin(), sSeparator.cend());
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::starts_with
//
//!\brief  Check if current string starts with char
//!\param  chSymbol - char for comparison
//!\retval - true if starts with char
//!\author Khrapov
//!\date   08.10.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::starts_with(value_type chSymbol) const noexcept
{
    if (!empty())
        return at(0) == chSymbol;
    else
        return false;
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::starts_with
//
//!\brief  Check if current string starts with string
//!\param  pszStr   - const pointer to string
//!\param  nStrSize - string length
//!\retval          - true if starts with string
//!\author Khrapov
//!\date   08.10.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::starts_with(
    const_pointer pszStr,
    size_type     nStrSize) const noexcept
{
    if (size_type nThisSize = size(); nThisSize > 0)
    {
        if (nStrSize == npos)
            nStrSize = Traits::length(pszStr);

        if (nStrSize <= nThisSize)
            return Traits::compare_n(data(), pszStr, nStrSize) == 0;
    }

    return false;
}

//==============================================================================
//!\fn                 basic_string<Traits>::starts_with
//
//!\brief  Check if current string starts with string
//!\param  sStr - string to check
//!\retval      - true if starts with string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::starts_with(
    const basic_string& sStr) const noexcept
{
    return starts_with(sStr.data(), sStr.size());
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::starts_with<FwdIt>
//
//!\brief  Check if current string starts with string
//!\param  itBegin - string begin iterator
//!\param  itEnd   - string end iterator
//!\retval         - true if starts with string
//!\author Khrapov
//!\date   23.10.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::starts_with(
    FwdIt itBegin,
    FwdIt itEnd) const noexcept
{
    auto nStrSize = std::distance(itBegin, itEnd);
    return iter_strcmp(
        cbegin(),
        cbegin() + static_cast<size_type>(nStrSize),
        itBegin,
        itEnd) == 0;
}

//==============================================================================
//!\fn            basic_string<Traits>::starts_with<String, >
//
//!\brief  Check if current string starts with string
//!\param  sStr - string container to check
//!\retval      - true if starts with string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::starts_with(const String& sStr) const noexcept
{
    return starts_with(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::ends_with
//
//!\brief  Check if current string ends with char
//!\param  ch - char for comparison
//!\retval - true if ends with char
//!\author Khrapov
//!\date   08.10.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::ends_with(value_type chSymbol) const noexcept
{
    const size_type nSize = size();
    if (nSize > 0)
        return at(nSize - 1) == chSymbol;
    else
        return false;
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::ends_with
//
//!\brief  Check if current string ends with string
//!\param  pszStr   - const pointer to string
//!\param  nStrSize - string length
//!\retval          - true if ends with string
//!\author Khrapov
//!\date   08.10.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::ends_with(
    const_pointer pszStr,
    size_type     nStrSize) const noexcept
{

    if (size_type nThisSize = size(); nThisSize > 0)
    {
        if (nStrSize == npos)
            nStrSize = Traits::length(pszStr);

        if (nStrSize <= nThisSize)
            return Traits::compare_n(data() + nThisSize - nStrSize, pszStr, nStrSize) == 0;
    }

    return false;
}

//==============================================================================
//!\fn                  basic_string<Traits>::ends_with
//
//!\brief  Check if current string ends with string
//!\param  sStr - string to check
//!\retval      - true if starts with string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::ends_with(
    const basic_string& sStr) const noexcept
{
    return ends_with(sStr.data(), sStr.size());
}

//==============================================================================
//!\fn               basic_string<Traits>::ends_with<FwdIt>
//
//!\brief  Check if current string ends with string
//!\param  itBegin - string begin iterator
//!\param  itEnd   - string end iterator
//!\retval         - true if ends with string
//!\author Khrapov
//!\date   23.10.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::ends_with(
    FwdIt itBegin,
    FwdIt itEnd) const noexcept
{
    return iter_strcmp(
        cend() - static_cast<size_type>(std::distance(itBegin, itEnd)),
        cend(),
        itBegin,
        itEnd) == 0;
}

//==============================================================================
//!\fn             basic_string<Traits>::ends_with<String, >
//
//!\brief  Check if current string ends with string
//!\param  sStr - string container to check
//!\retval      - true if starts with string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::ends_with(const String& sStr) const noexcept
{
    return ends_with(sStr.cbegin(), sStr.cend());
}

//==============================================================================
//!\fn                   basic_string<Traits>::contains
//
//!\brief  Check if string contains char. Equal to find != npos
//!\param  chSymbol - char to check
//!\retval          - true if this string contains substring, otherwise false
//!\author Khrapov
//!\date   30.11.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::contains(value_type chSymbol) const noexcept
{
    return find(chSymbol) != npos;
}

//==============================================================================
//!\fn                   basic_string<Traits>::contains
//
//!\brief  Check if string contains substring. Equal to find != npos
//!\param  pszStr   - substring to check
//!\param  nStrSize - substring size
//!\retval          - true if this string contains substring, otherwise false
//!\author Khrapov
//!\date   30.11.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::contains(
    const_pointer pszStr,
    size_type nStrSize) const noexcept
{
    return find(pszStr, 0, nStrSize) != npos;
}

//==============================================================================
//!\fn                   basic_string<Traits>::contains
//
//!\brief  Check if string contains substring. Equal to find != npos
//!\param  sStr - string to check
//!\retval      - true if this string contains substring, otherwise false
//!\author Khrapov
//!\date   30.11.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::contains(
    const basic_string& sStr) const noexcept
{
    return find(sStr) != npos;
}

//==============================================================================
//!\fn               basic_string<Traits>::contains<FwdIt>
//
//!\brief  Check if string contains substring. Equal to find != npos
//!\param  itBegin - substring begin iterator
//!\param  itEnd   - substring end iterator
//!\retval         - true if this string contains substring, otherwise false
//!\author Khrapov
//!\date   30.11.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::contains(
    FwdIt itBegin,
    FwdIt itEnd) const noexcept
{
    return find(itBegin, itEnd) != npos;
}

//==============================================================================
//!\fn              basic_string<Traits>::contains<String, >
//
//!\brief  Check if string contains substring. Equal to find != npos
//!\param  sStr - string to check
//!\retval      - true if this string contains substring, otherwise false
//!\author Khrapov
//!\date   30.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::contains(const String& sStr) const noexcept
{
    return find(sStr) != npos;
}


//---------------------------------- operator= ---------------------------------

template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(
    value_type chSymbol) noexcept
{
    assign(chSymbol);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(
    const_pointer pszSource) noexcept
{
    assign(pszSource);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(
    basic_string&& sStr) noexcept
{
    assign(std::move(sStr));
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(
    const basic_string& sStr) noexcept
{
    assign(sStr);
    return *this;
}
template<class Traits>
template<class String, class>
inline const basic_string<Traits>& basic_string<Traits>::operator=(
    const String& sStr) noexcept
{
    assign(sStr);
    return *this;
}

//--------------------------------- operator+= ---------------------------------

template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(
    value_type chSymbol) noexcept
{
    append(&chSymbol, 1);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(
    const_pointer pszSource) noexcept
{
    append(pszSource, Traits::length(pszSource));
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(
    const basic_string& sStr) noexcept
{
    append(sStr.data(), sStr.size());
    return *this;
}
template<class Traits>
template<class String, class>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(
    const String& sStr) noexcept
{
    append(sStr.cbegin(), sStr.cend());
    return *this;
}

//--------------------------------- operator== ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator==(
    value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) == 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator==(
    const_pointer pszSource) const noexcept
{
    return compare(pszSource) == 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator==(
    const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) == 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator==(
    const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) == 0;
}

//--------------------------------- operator!= ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator!=(
    value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) != 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator!=(
    const_pointer pszSource) const noexcept
{
    return compare(pszSource) != 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator!=(
    const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) != 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator!=(
    const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) != 0;
}

//---------------------------------- operator< ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator<(
    value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) < 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator<(
    const_pointer pszSource) const noexcept
{
    return compare(pszSource) < 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator<(
    const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) < 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator<(
    const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) < 0;
}

//--------------------------------- operator<= ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator<=(
    value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) <= 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator<=(
    const_pointer pszSource) const noexcept
{
    return compare(pszSource) <= 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator<=(
    const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) <= 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator<=(
    const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) <= 0;
}

//---------------------------------- operator> ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator>(
    value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) > 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator>(
    const_pointer pszSource) const noexcept
{
    return compare(pszSource) > 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator>(
    const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) > 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator>(
    const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) > 0;
}

//--------------------------------- operator>= ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator>=(
    value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) >= 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator>=(
    const_pointer pszSource) const noexcept
{
    return compare(pszSource) >= 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator>=(
    const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) >= 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator>=(
    const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) >= 0;
}

//--------------------------------- operator[] ---------------------------------

template<class Traits>
inline typename basic_string<Traits>::reference basic_string<Traits>::operator[](
    size_type nSymbol) noexcept
{
    return at(nSymbol);
}
template<class Traits>
inline typename basic_string<Traits>::const_reference basic_string<Traits>::operator[](
    size_type nSymbol) const noexcept
{
    return at(nSymbol);
}

//----------------------- operator std::basic_string_view ----------------------

template<class Traits>
inline basic_string<Traits>::operator std::basic_string_view<
    typename basic_string<Traits>::value_type,
    std::char_traits<typename basic_string<Traits>::value_type>>() const noexcept
{
    return std::basic_string_view<value_type, std::char_traits<value_type>>(data(), size());
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::get_format_specifier<T>
//
//!\brief  Get format specifier for type
//!\retval  - format specifier or nullptr if type is not supported
//!\author Khrapov
//!\date   11.09.2020
//==============================================================================
template<class Traits>
template<typename T>
constexpr typename basic_string<Traits>::const_pointer basic_string<Traits>::get_format_specifier(
    void) noexcept
{
    const_pointer pszFormat = nullptr;

    if constexpr (std::is_same_v<T, char>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%hhd");
    }
    else if constexpr (std::is_same_v<T, unsigned char>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%hhu");
    }
    else if constexpr (std::is_same_v<T, short>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%hd");
    }
    else if constexpr (std::is_same_v<T, unsigned short>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%hu");
    }
    else if constexpr (std::is_same_v<T, int>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%d");
    }
    else if constexpr (std::is_same_v<T, unsigned int>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%u");
    }
    else if constexpr (std::is_same_v<T, long>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%ld");
    }
    else if constexpr (std::is_same_v<T, unsigned long>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%lu");
    }
    else if constexpr (std::is_same_v<T, long long>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%lld");
    }
    else if constexpr (std::is_same_v<T, unsigned long long>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%llu");
    }
    else if constexpr (std::is_same_v<T, float>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%f");
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%lf");
    }
    else if constexpr (std::is_same_v<T, long double>)
    {
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%Lf");
    }
    else if constexpr (std::is_pointer_v<T>)
    {
#if QX_MSVC
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "0x%p");
#else
        pszFormat = QX_STR_PREFIX(typename Traits::value_type, "%p");
#endif
    }

    return pszFormat;
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::_trim_left<Searcher>
//
//!\brief  Common algorithm for trimming string to the left
//!\param  searcher - function that returns true if symbol has to be deleted
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class Searcher>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_trim_left(
    const Searcher& searcher) noexcept
{
    size_type nSymbols = 0;

    for (size_type i = 0; i < size(); i++)
    {
        if (searcher(at(i)))
            nSymbols++;
        else
            break;
    }

    erase(0, nSymbols);
    return nSymbols;
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::_trim_right<Searcher>
//
//!\brief  Common algorithm for trimming string to the right
//!\param  searcher - function that returns true if symbol has to be deleted
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class Searcher>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_trim_right(
    const Searcher& searcher) noexcept
{
    size_type nSymbols = 0;
    size_type nSize = size();

    for (size_type i = nSize - 1; i != std::numeric_limits<size_type>::max(); i--)
    {
        if (searcher(at(i)))
            nSymbols++;
        else
            break;
    }

    erase(nSize - nSymbols, nSymbols);
    return nSymbols;
}

//==============================================================================
//!\fn              qx::basic_string<Traits>::_trim<Searcher>
//
//!\brief  Common algorithm for trimming string to the both sides
//!\param  searcher - function that returns true if symbol has to be deleted
//!\retval          - number of deleted symbols
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class Searcher>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_trim(
    const Searcher& searcher) noexcept
{
    const size_type nSize = size();
    size_type nStartPos = 0;
    size_type nEndPos = nSize;

    while (nStartPos < nSize && searcher(at(nStartPos)))
        nStartPos++;

    while (nEndPos > nStartPos && searcher(at(nEndPos - 1)))
        nEndPos--;

    size_type nNewSize = nEndPos - nStartPos;

    std::memmove(
        data(),
        data() + nStartPos,
        nNewSize * sizeof(value_type));

    resize(nNewSize, Traits::align());
    return nSize - nNewSize;
}

//==============================================================================
//!\fn              qx::basic_string<Traits>::_find<Comparator>
//
//!\brief  Common algorithm for finding substring
//!\param  nBegin     - start searching index
//!\param  nEnd       - end searching index (npos - to the end)
//!\param  comparator - comparator function
//!\retval            - substring index or npos if not found
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class Comparator>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_find(
    size_type         nBegin,
    size_type         nEnd,
    const Comparator& comparator) const noexcept
{
    if (nEnd == npos)
        nEnd = size();

    const_pointer pData = data();
    const_pointer pCurrentChar = pData + nBegin;
    const_pointer pEnd = pData + nEnd;

    while (pCurrentChar < pEnd)
    {
        if (comparator(pCurrentChar))
            return static_cast<size_type>(pCurrentChar - pData);
        else
            pCurrentChar++;
    }

    return npos;
}

//==============================================================================
//!\fn              qx::basic_string<Traits>::_rfind<Comparator>
//
//!\brief  Common algorithm for reverse finding substring
//!\param  nBegin     - start searching index
//!\param  nEnd       - end searching index
//!\param  comparator - comparator function
//!\retval            - substring index or npos if not found
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class Comparator>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_rfind(
    size_type         nBegin,
    size_type         nEnd,
    const Comparator& comparator) const noexcept
{
    if (nBegin == npos)
        nBegin = size() - 1;

    const_pointer pData = data();
    const_pointer pCurrentChar = pData + nBegin;
    const_pointer pEnd = pData + nEnd;

    while (pCurrentChar >= pEnd)
    {
        if (comparator(pCurrentChar))
            return static_cast<size_type>(pCurrentChar - pData);
        else
            pCurrentChar--;
    }

    return npos;
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::_find_last_of<Comparator>
//
//!\brief  Common algorithm for find_last_of
//!\param  nPos        - position at which the search is to finish
//!\param  char_getter - function that returns new char till "of" string end
//!\retval             - symbol index or npos
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class CharGetter>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_find_last_of(
    size_type         nPos,
    const CharGetter& char_getter) const noexcept
{
    const size_type nSize = size();
    size_type nLast = npos;

    auto chCurrent = char_getter();
    while (nLast != nSize - 1 && chCurrent.has_value())
    {
        size_type nCharLastPos = find_last_of(chCurrent.value(), nPos);
        if (nCharLastPos != npos)
        {
            if (nLast != npos)
                nLast = std::max(nCharLastPos, nLast);
            else
                nLast = nCharLastPos;
        }

        chCurrent = char_getter();
    }

    return nLast;
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::_find_first_of<Comparator>
//
//!\brief  Common algorithm for find_first_of
//!\param  nPos        - position at which the search is to finish
//!\param  char_getter - function that returns new char till "of" string end
//!\retval             - symbol index or npos
//!\author Khrapov
//!\date   02.12.2020
//==============================================================================
template<class Traits>
template<class CharGetter>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_find_first_of(
    size_type         nPos,
    const CharGetter& char_getter) const noexcept
{
    size_type nFirst = npos;

    auto chCurrent = char_getter();
    while (nFirst != 0 && chCurrent.has_value())
    {
        size_type nCharFirstPos = find_first_of(chCurrent.value(), nPos);
        if (nCharFirstPos != npos)
        {
            if (nFirst != npos)
                nFirst = std::min(nCharFirstPos, nFirst);
            else
                nFirst = nCharFirstPos;
        }

        chCurrent = char_getter();
    }

    return nFirst;
}

//==============================================================================
//!\fn                 qx::basic_string<Traits>::at
//
//!\param  ind - char index
//!\retval     - char value
//!\author Khrapov
//!\date   19.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::reference basic_string<Traits>::at(
    size_type ind) noexcept
{
    return data()[ind];
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::clear
//
//!\brief  Clear string
//!\author Khrapov
//!\date   19.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::clear(void) noexcept
{
    assign(QX_STR_PREFIX(typename Traits::value_type, ""));
}

//==============================================================================
//!\fn                 qx::basic_string<Traits>::size
//
//!\brief  Get string size (excluding null terminator)
//!\author Khrapov
//!\date   19.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::size(
    void) const noexcept
{
    return m_Data.size();
}

//==============================================================================
//!\fn                 qx::basic_string<Traits>::data
//
//!\brief  Get c-string
//!\author Khrapov
//!\date   28.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::pointer basic_string<Traits>::data(
    void) noexcept
{
    return m_Data.data();
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::resize
//
//!\brief  Resize string.
//         If new size is smaller, string will be truncated
//!\param  nSymbols - new size
//!\param  nAlign   - align (if 16 then size 13->16 16->16 18->32)
//!\param  eType    - resize type
//!\retval          - true if memory alloc is succesful
//!\author Khrapov
//!\date   29.10.2019
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::resize(
    size_type           nSymbols,
    size_type           nAlign,
    string_resize_type  eType) noexcept
{
    bool bRet = m_Data.resize(nSymbols, nAlign, eType);

    if (bRet && eType == string_resize_type::common)
        at(nSymbols) = QX_CHAR_PREFIX(typename Traits::value_type, '\0');

    return bRet;
}

}



//------------------------------------ hash ------------------------------------

namespace std
{
    template<class Traits>
    struct hash<qx::basic_string<Traits>>
    {
        u32 operator()(const qx::basic_string<Traits>& str) const noexcept
        {
            return qx::murmur_32_hash(str.data(),
                                      str.size(),
                                      Traits::hash_seed());
        }
    };
}



//------------------------------------ swap ------------------------------------

namespace std
{
    template<class Traits>
    void swap(qx::basic_string<Traits>& lhs, qx::basic_string<Traits>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}



//----------------------- istream / ostream overloading ----------------------

template<class Traits>
qx::detail::ostream<Traits>& operator<<(
    qx::detail::ostream<Traits>   & os,
    const qx::basic_string<Traits>& str)
{
    os << str.data();
    return os;
}

template<class Traits>
qx::detail::istream<Traits>& operator>>(
    qx::detail::istream<Traits>& is,
    qx::basic_string<Traits>   & str)
{
    typename qx::detail::istream<Traits>::iostate ret_bit = qx::detail::istream<Traits>::goodbit;
    auto try_push_back = [&str, &is, &ret_bit](typename qx::basic_string<Traits>::value_type ch) -> bool
    {
        typename qx::basic_string<Traits>::size_type nCurrentSize = str.size();
        if (str.resize(nCurrentSize + 1, Traits::align()))
        {
            str[nCurrentSize] = ch;
            return true;
        }
        else
        {
            is.unget();
            ret_bit |= qx::detail::istream<Traits>::failbit;
            return false;
        }
    };

    str.clear();
    typename qx::basic_string<Traits>::value_type ch;

    // skip all space symbols and add first symbol is any
    while (is.get(ch))
    {
        if (!Traits::is_space(ch))
        {
            try_push_back(ch);
            break;
        }
    }

    // add other symbols until space symbol
    while (is.get(ch))
    {
        if (!Traits::is_space(ch))
        {
            if (!try_push_back(ch))
                break;
        }
        else
        {
            is.unget();
            break;
        }
    }

    is.setstate(ret_bit);
    return is;
}
