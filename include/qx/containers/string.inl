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
inline basic_string<Traits>::basic_string(value_type chSymbol)
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
inline basic_string<Traits>::basic_string(size_type nSymbols, value_type chSymbol)
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
inline basic_string<Traits>::basic_string(const_pointer pszSource, size_type nSymbols)
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
inline basic_string<Traits>::basic_string(const_pointer pszSource)
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
inline basic_string<Traits>::basic_string(const basic_string& sAnother)
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
inline basic_string<Traits>::basic_string(FwdIt itFirst, FwdIt itLast)
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
inline basic_string<Traits>::basic_string (const String & sAnother)
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
inline basic_string<Traits>::~basic_string(void)
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
inline void basic_string<Traits>::assign(value_type chSymbol)
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
inline void basic_string<Traits>::assign(size_type nSymbols, value_type chSymbol)
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
inline void basic_string<Traits>::assign(const_pointer pszSource, size_type nSymbols)
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
inline void basic_string<Traits>::assign(const_pointer pszSource)
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
inline void basic_string<Traits>::assign(const basic_string& sAnother)
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
inline void basic_string<Traits>::assign(FwdIt itFirst, FwdIt itLast)
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
inline void basic_string<Traits>::assign(const String& sAnother)
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
void basic_string<Traits>::format(const_pointer pszFormat, ...)
{
    va_list args;
    va_start(args, pszFormat);
    vformat(pszFormat, args);
    va_end(args);
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::format_static<...Args>
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
inline basic_string<Traits> basic_string<Traits>::format_static(
    const_pointer pszFormat,
    Args...       args)
{
    basic_string str;
    str.format(pszFormat, args...);
    return std::move(str);
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
inline void basic_string<Traits>::vformat(const_pointer pszFormat, va_list args)
{
    va_list args_copy;
    va_copy(args_copy, args);
    int length = Traits::vsnprintf(nullptr, 0, pszFormat, args_copy);
    va_end(args_copy);

    if (length > 0 && resize(static_cast<size_type>(length), Traits::align()))
        Traits::vsnprintf(data(), static_cast<size_type>(length) + 1, pszFormat, args);
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
inline typename basic_string<Traits>::size_type basic_string<Traits>::reserve(size_type nCapacity)
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
inline void basic_string<Traits>::shrink_to_fit(void)
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
inline void basic_string<Traits>::free(void)
{
    m_Data.free();
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::substr
//
//!\brief  Find substring
//!\param  nPos     - start index
//!\param  nSymbols - string size (npos - to the end)
//!\retval          - substring
//!\author Khrapov
//!\date   31.10.2019
//==============================================================================
template<class Traits>
inline basic_string<Traits> basic_string<Traits>::substr(
    size_type nPos,
    size_type nSymbols) const
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
inline void basic_string<Traits>::apply_case(case_type eCaseType)
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
inline typename basic_string<Traits>::value_type basic_string<Traits>::front(void) const
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
inline typename basic_string<Traits>::value_type basic_string<Traits>::back(void) const
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
inline typename basic_string<Traits>::size_type basic_string<Traits>::length(void) const
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
inline typename basic_string<Traits>::const_pointer basic_string<Traits>::c_str(void) const
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
inline typename basic_string<Traits>::size_type basic_string<Traits>::capacity(void) const
{
    return m_Data.capacity();
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
inline std::optional<To> basic_string<Traits>::to(void) const
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
//!\fn               qx::basic_string<Traits>::from<From>
//
//!\brief  Construct string from custom type
//!\param  data      - data of type From
//!\param  pszFormat - format string if default is not enough
//!\author Khrapov
//!\date   24.03.2020
//==============================================================================
template<class Traits>
template<typename From>
inline void basic_string<Traits>::from(const From& data, const_pointer pszFormat)
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
    const_pointer pszFormat)
{
    basic_string str;
    str.from(data, pszFormat);
    return std::move(str);
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
inline void basic_string<Traits>::erase(iterator itFirst, iterator itLast)
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
inline void basic_string<Traits>::erase(iterator itPos)
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
inline void basic_string<Traits>::erase(size_type nPos)
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
inline void basic_string<Traits>::erase(size_type nPos, size_type nSymbols)
{
    erase(iterator(this, nPos), iterator(this, nPos + nSymbols));
}
//==============================================================================
//!\fn         qx::basic_string<Traits>::remove_all_of<...Args, >
//
//!\brief  Remove all chars container including from string
//!\param  ...args - symbols to remove
//!\author Khrapov
//!\date   22.03.2020
//==============================================================================
template<class Traits>
template<class ... Args, class>
inline void basic_string<Traits>::remove_all_of(Args... args)
{
    std::array<typename Traits::value_type, sizeof...(args)> to_remove { args... };
    remove_all_of(to_remove.cbegin(), to_remove.cend());
}

//==============================================================================
//!\fn         qx::basic_string<Traits>::remove_all_of<FwdIt, >
//
//!\brief  Remove all chars container including from string
//!\param  itFirst - symbols to erase begin iterator
//!\param  itLast  - symbols to erase end iterator
//!\author Khrapov
//!\date   22.03.2020
//==============================================================================
template<class Traits>
template<class FwdIt, class>
inline void basic_string<Traits>::remove_all_of(FwdIt itFirst, FwdIt itLast)
{
    for (auto it = begin(); it < end(); ++it)
    {
        auto firstSeqIt = it;
        while (std::any_of(itFirst, itLast, [&it] (value_type ch) { return ch == *it; }))
            ++it;

        erase(firstSeqIt, it);
        it -= static_cast<size_t>(it - firstSeqIt);
    }
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  nPos      - first char index
//!\param  pszSourse - sourse string
//!\param  nSymbols  - number of symbols to insert
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(
    size_type     nPos,
    const_pointer pszSourse,
    size_type     nSymbols)
{
    size_type nStartSymbols = size();
    size_type nSizeSource = nSymbols == npos ? Traits::length(pszSourse) : nSymbols;

    if (resize(nStartSymbols + nSizeSource, Traits::align()))
    {
        std::memmove(
            data() + nPos + nSizeSource,
            data() + nPos,
            (nStartSymbols - nPos) * sizeof(value_type));

        std::memcpy(data() + nPos, pszSourse, nSizeSource * sizeof(value_type));
    }
}

//==============================================================================
//!\fn                    basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  itToFirst   - target string inserting iterator
//!\param  itFromFirst - source string first iterator
//!\param  itFromLast  - source string last iterator
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(
    iterator       itToFirst,
    const_iterator itFromFirst,
    const_iterator itFromLast)
{
    insert(
        static_cast<size_type>(itToFirst - begin()),
        itFromFirst.operator->(),
        static_cast<size_type>(itFromLast - itFromFirst));
}

//==============================================================================
//!\fn                    basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  itPos     - first char index
//!\param  pszSourse - source string
//!\param  nSymbols  - number of chars in source string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(
    iterator        itPos,
    const_pointer   pszSourse,
    size_type       nSymbols)
{
    insert(
        static_cast<size_type>(itPos - begin()),
        pszSourse,
        nSymbols == npos ? Traits::length(pszSourse) : nSymbols);
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
inline void basic_string<Traits>::push_back(value_type chSymbol)
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
inline void basic_string<Traits>::push_front(value_type chSymbol)
{
    insert(0, &chSymbol, 1);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find
//
//!\brief  Find first match
//!\param  chSymbol - char to find
//!\param  nBegin   - start searching index
//!\param  nEnd     - end searching index (-1 - to the end)
//!\retval          - substring index or npos if not found
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    value_type    chSymbol,
    size_type     nBegin,
    size_type     nEnd) const
{
    if (nEnd == npos)
        nEnd = size();

    const_pointer pCurrentChar = data() + nBegin;
    const_pointer pEnd         = data() + nEnd;

    do
    {
        if (*pCurrentChar == chSymbol)
            return static_cast<size_type>(pCurrentChar - data());
        else
            pCurrentChar = step_to(pCurrentChar, pEnd);
    } while (pCurrentChar != pEnd);

    return npos;
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find
//
//!\brief  Find first match
//!\param  pszWhat - c-string to find
//!\param  nBegin  - start searching index
//!\param  nEnd    - end searching index (-1 - to the end).
//         if nEnd < nBegin, seach backward
//!\retval          - substring index
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nEnd) const
{
    size_type nSizeWhat = Traits::length(pszWhat);

    if (nEnd == npos)
        nEnd = size();

    const_pointer pCurrentChar = data() + nBegin;
    const_pointer pEnd         = data() + nEnd;

    do
    {
        if (!Traits::compare_n(pszWhat, pCurrentChar, nSizeWhat))
            return static_cast<size_type>(pCurrentChar - data());
        else
            pCurrentChar = step_to(pCurrentChar, pEnd);
    } while (pCurrentChar != pEnd);

    return npos;
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
    size_type           nEnd) const
{
    return find(sWhat.data(), nBegin, nEnd);
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
    size_type   nEnd) const
{
    if (nEnd == npos)
        nEnd = size();

    const_pointer pStart = data();
    const_pointer pCurrentChar = pStart + nBegin;
    const_pointer pEnd = pStart + nEnd;

    do
    {
        if (!iter_strcmp(
                const_iterator(this, static_cast<size_type>(pCurrentChar - pStart)),
                const_iterator(this, static_cast<size_type>(pEnd - pStart)),
                itWhatBegin,
                itWhatEnd))
        {
            return static_cast<size_type>(pCurrentChar - pStart);
        }
        else
        {
            pCurrentChar = step_to(pCurrentChar, pEnd);
        }
    } while (pCurrentChar != pEnd);

    return npos;
}

//==============================================================================
//!\fn                basic_string<Traits>::find<String, >
//
//!\brief  Find substring
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
    size_type nEnd) const
{
    return find(sWhat.cbegin(), sWhat.cend(), nBegin, nEnd);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_last_of
//
//!\brief  Find last position of catacter
//!\param  chSymbol - char to find
//!\param  nPos     - start searching index (from the end). npos - from the very end
//!\param  nSymbols - number of symbols to check (npos - to the beginning)
//!\retval          - symbol index or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(
    value_type chSymbol,
    size_type  nPos,
    size_type  nSymbols) const
{
    if (nPos == npos)
        nPos = size();

    if (nSymbols == npos)
        nSymbols = size();

    return find(chSymbol, nPos, nPos - nSymbols);
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
    const value_type chSeparator) const
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
    size_type     nSepLen) const
{
    vector tokens;

    if (nSepLen == npos)
        nSepLen = Traits::length(pszSeparator);

    size_type start = 0;
    size_type end   = 0;
    while ((end = find(pszSeparator, start)) != npos)
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
    const basic_string& sSeparator) const
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
    FwdIt itSepLast) const
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
    const String& sSeparator) const
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
inline bool basic_string<Traits>::starts_with(value_type chSymbol) const
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
    size_type     nStrSize) const
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
inline bool basic_string<Traits>::starts_with(const basic_string& sStr) const
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
inline bool basic_string<Traits>::starts_with(FwdIt itBegin, FwdIt itEnd) const
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
inline bool basic_string<Traits>::starts_with(const String& sStr) const
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
inline bool basic_string<Traits>::ends_with(value_type chSymbol) const
{
    size_type nSize = size();
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
    size_type     nStrSize) const
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
inline bool basic_string<Traits>::ends_with(const basic_string& sStr) const
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
inline bool basic_string<Traits>::ends_with(FwdIt itBegin, FwdIt itEnd) const
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
inline bool basic_string<Traits>::ends_with(const String& sStr) const
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
inline bool basic_string<Traits>::contains(value_type chSymbol) const
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
inline bool basic_string<Traits>::contains(const_pointer pszStr, size_type nStrSize) const
{
    return find(pszStr, nStrSize) != npos;
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
inline bool basic_string<Traits>::contains(const basic_string& sStr) const
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
inline bool basic_string<Traits>::contains(FwdIt itBegin, FwdIt itEnd) const
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
inline bool basic_string<Traits>::contains(const String& sStr) const
{
    return find(sStr) != npos;
}


//---------------------------------- operator= ---------------------------------

template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(value_type chSymbol)
{
    assign(chSymbol);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(const_pointer pszSource)
{
    assign(pszSource);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(basic_string&& sStr) noexcept
{
    assign(std::move(sStr));
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(const basic_string& sStr)
{
    assign(sStr);
    return *this;
}
template<class Traits>
template<class String, class>
inline const basic_string<Traits>& basic_string<Traits>::operator=(const String& sStr)
{
    assign(sStr);
    return *this;
}

//--------------------------------- operator+= ---------------------------------

template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(value_type chSymbol)
{
    append(&chSymbol, 1);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(const_pointer pszSource)
{
    append(pszSource, Traits::length(pszSource));
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(const basic_string& sStr)
{
    append(sStr.data(), sStr.size());
    return *this;
}
template<class Traits>
template<class String, class>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(const String& sStr)
{
    append(sStr.cbegin(), sStr.cend());
    return *this;
}

//--------------------------------- operator== ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator==(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) == 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator==(const_pointer pszSource) const noexcept
{
    return compare(pszSource) == 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator==(const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) == 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator==(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) == 0;
}

//--------------------------------- operator!= ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator!=(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) != 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator!=(const_pointer pszSource) const noexcept
{
    return compare(pszSource) != 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator!=(const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) != 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator!=(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) != 0;
}

//---------------------------------- operator< ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator<(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) < 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator<(const_pointer pszSource) const noexcept
{
    return compare(pszSource) < 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator<(const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) < 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator<(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) < 0;
}

//--------------------------------- operator<= ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator<=(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) <= 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator<=(const_pointer pszSource) const noexcept
{
    return compare(pszSource) <= 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator<=(const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) <= 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator<=(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) <= 0;
}

//---------------------------------- operator> ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator>(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) > 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator>(const_pointer pszSource) const noexcept
{
    return compare(pszSource) > 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator>(const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) > 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator>(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) > 0;
}

//--------------------------------- operator>= ---------------------------------

template<class Traits>
inline bool basic_string<Traits>::operator>=(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) >= 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator>=(const_pointer pszSource) const noexcept
{
    return compare(pszSource) >= 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator>=(const basic_string& sStr) const noexcept
{
    return compare(sStr.data()) >= 0;
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator>=(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) >= 0;
}

//--------------------------------- operator[] ---------------------------------

template<class Traits>
inline typename basic_string<Traits>::reference basic_string<Traits>::operator[](size_type nSymbol) noexcept
{
    return at(nSymbol);
}
template<class Traits>
inline typename basic_string<Traits>::const_reference basic_string<Traits>::operator[](size_type nSymbol) const noexcept
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
inline constexpr typename basic_string<Traits>::const_pointer basic_string<Traits>::get_format_specifier(void)
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
//!\fn                 qx::basic_string<Traits>::at
//
//!\param  ind - char index
//!\retval     - char value
//!\author Khrapov
//!\date   19.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::reference basic_string<Traits>::at(size_type ind)
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
inline void basic_string<Traits>::clear(void)
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
inline typename basic_string<Traits>::size_type basic_string<Traits>::size(void) const
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
inline typename basic_string<Traits>::pointer basic_string<Traits>::data(void)
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
    string_resize_type  eType)
{
    bool bRet = m_Data.resize(nSymbols, nAlign, eType);

    if (bRet && eType == string_resize_type::common)
        at(nSymbols) = QX_CHAR_PREFIX(typename Traits::value_type, '\0');

    return bRet;
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::append
//
//!\brief  Append string to the current
//!\param  pSource  - source string
//!\param  nSymbols - source string size
//!\author Khrapov
//!\date   27.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::append(const_pointer pSource, size_type nSymbols)
{
    size_type nCurrentSymbls = size();
    if (resize(nCurrentSymbls + nSymbols, Traits::align()))
        std::memcpy(data() + nCurrentSymbls, pSource, nSymbols * sizeof(value_type));
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
inline void basic_string<Traits>::append(FwdIt itBegin, FwdIt itEnd)
{
    for (auto it = itBegin; it != itEnd; ++it)
        push_back(*it);
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
inline int basic_string<Traits>::compare(const_pointer pStr, size_type nSymbols) const
{
    if (nSymbols > 0)
        return Traits::compare_n(data(), pStr, nSymbols);
    else
        return Traits::compare(data(), pStr);
}

}



//-------------------------- hashes for strings types --------------------------

namespace std
{
    template<>
    struct hash<qx::string>
    {
        u32 operator()(const qx::string& str) const
        {
            return qx::murmur_32_hash(str.data(),
                                      str.size(),
                                      qx::detail::random_string_hash::next());
        }
    };

    template<>
    struct hash<qx::wstring>
    {
        u32 operator()(const qx::wstring& str) const
        {
            return qx::murmur_32_hash(str.data(),
                                      str.size(),
                                      qx::detail::random_string_hash::next());
        }
    };
}



//----------------------- istream / ostream overloading ----------------------

template<class Traits>
qx::detail::ostream<Traits>& operator<<(qx::detail::ostream<Traits>& os, const qx::basic_string<Traits>& str)
{
    os << str.data();
    return os;
}

template<class Traits>
qx::detail::istream<Traits>& operator>>(qx::detail::istream<Traits>& is, qx::basic_string<Traits>& str)
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
