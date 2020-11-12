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
//!\param  pSource  - source string pointer
//!\param  nSymbols - source string size
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(const_pointer pSource, size_type nSymbols)
{
    assign(pSource, nSymbols);
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  str - another string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(basic_string&& str) noexcept
{
    assign(std::move(str));
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  str - another string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(const basic_string& str)
{
    assign(str);
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  ch - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(value_type ch)
{
    assign(ch);
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  pSource - const pointer
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(const_pointer pSource)
{
    assign(pSource);
}

//==============================================================================
//!\fn                 basic_string<Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  nSymbols - num of symbols of char
//!\param  ch       - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline basic_string<Traits>::basic_string(size_type nSymbols, value_type ch)
{
    assign(nSymbols, ch);
}

//==============================================================================
//!\fn             basic_string<Traits>::basic_string<FwdIt>
//
//!\brief  basic_string object constructor
//!\param  first - first iterator of source
//!\param  last  - last iterator of source
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline basic_string<Traits>::basic_string(FwdIt first, FwdIt last)
{
    assign(first, last);
}

//==============================================================================
//!\fn            basic_string<Traits>::basic_string<String, >
//
//!\brief  basic_string object constructor
//!\param  str - char container
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline basic_string<Traits>::basic_string (const String & str)
{
    assign(str);
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
//!\fn                qx::basic_string<Traits>::assign
//
//!\brief  Assign string
//!\param  pSource  - source string pointer
//!\param  nSymbols - source string size
//!\author Khrapov
//!\date   27.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(const_pointer pSource, size_type nSymbols)
{
    if (resize(nSymbols, Traits::align()))
        std::memmove(data(), pSource, nSymbols * sizeof(value_type));
}

//==============================================================================
//!\fn                  qx::basic_string<Traits>::assign
//
//!\brief  Assign by another string
//!\param  str - string
//!\author Khrapov
//!\date   27.08.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(const basic_string& str)
{
    if (str.data() != data())
        assign(str.data());
}

//==============================================================================
//!\fn                    basic_string<Traits>::assign
//
//!\brief  Assign by single char
//!\param  ch - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(value_type ch)
{
    assign(&ch, 1);
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
inline void basic_string<Traits>::assign(const_pointer pSource)
{
    if (pSource != data())
        assign(pSource, Traits::length(pSource));
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
inline void basic_string<Traits>::assign(size_type nSymbols, value_type ch)
{
    if (resize(nSymbols, Traits::align()))
        std::fill(begin(), end(), ch);
}

//==============================================================================
//!\fn                    basic_string<Traits>::assign
//
//!\brief  Assign by moving from another string
//!\param  str - another string
//!\author Khrapov
//!\date   7.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(basic_string&& str) noexcept
{
    std::swap(m_Data, str.m_Data);
}

//==============================================================================
//!\fn             qx::basic_string<Traits>::assign<FwdIt>
//
//!\brief  Assign by iterators
//!\param  first - first iterator of source
//!\param  last  - last iterator of source
//!\author Khrapov
//!\date   21.03.2020
//==============================================================================
template<class Traits>
template<class FwdIt>
inline void basic_string<Traits>::assign(FwdIt first, FwdIt last)
{
    clear();
    for (FwdIt it = first; it != last; ++it)
        push_back(*it);
}

//==============================================================================
//!\fn               basic_string<Traits>::assign<String, >
//
//!\brief  Assign by char container
//!\param  str - char container
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline void basic_string<Traits>::assign(const String& str)
{
    assign(str.cbegin(), str.cend());
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
//!\fn                 qx::basic_string<Traits>::fit
//
//!\brief  Fit allocated size to string's actual size
//!\author Khrapov
//!\date   29.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::fit(void)
{
    if (!m_Data.is_small() && capacity() > size())
        resize(size(), 0, string_resize_type::fit);
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
//!\fn                qx::basic_string<Traits>::erase
//
//!\brief  Erase substrung
//!\param  first - first substr char iterator
//!\param  last  - last substr char iterator (excluded)
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(iterator first, iterator last)
{
    if (first < last)
    {
        size_type nStartSize = size();
        size_type nSymbolsToCopy = last != end()
            ? Traits::length(last.operator->())
            : 0;

        if (nSymbolsToCopy > 0)
        {
            std::memcpy(
                first.operator->(),
                last.operator->(),
                nSymbolsToCopy * sizeof(value_type));
        }

        resize(static_cast<size_type>(nStartSize - (last - first)), Traits::align());
    }
}

//==============================================================================
//!\fn                    basic_string<Traits>::erase
//
//!\brief  Erase on iterator
//!\param  it - iterator
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(iterator it)
{
    erase(it, it + 1);
}

//==============================================================================
//!\fn                    basic_string<Traits>::erase
//
//!\brief  Erase on position
//!\param  pos - position
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(size_type pos)
{
    erase(iterator(this, pos), iterator(this, pos + 1));
}

//==============================================================================
//!\fn                    basic_string<Traits>::erase
//
//!\brief  Erase substring
//!\param  ind_first - start position
//!\param  nSymbols  - number of symbols
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(size_type ind_first, size_type nSymbols)
{
    erase(iterator(this, ind_first), iterator(this, ind_first + nSymbols));
}
//==============================================================================
//!\fn         qx::basic_string<Traits>::erase_all_of<...Args, >
//
//!\brief  Erase all chars container including from string
//!\param  ...args - symbols to erase
//!\author Khrapov
//!\date   22.03.2020
//==============================================================================
template<class Traits>
template<class ... Args, class>
inline void basic_string<Traits>::erase_all_of(Args... args)
{
    std::array<typename Traits::value_type, sizeof...(args)> toRemove { args... };
    erase_all_of(toRemove.cbegin(), toRemove.cend());
}

//==============================================================================
//!\fn         qx::basic_string<Traits>::erase_all_of<FwdIt, >
//
//!\brief  Erase all chars container including from string
//!\param  first - symbols to erase begin iterator
//!\param  last  - symbols to erase end iterator
//!\author Khrapov
//!\date   22.03.2020
//==============================================================================
template<class Traits>
template<class FwdIt, class>
inline void basic_string<Traits>::erase_all_of(FwdIt first, FwdIt last)
{
    for (auto it = begin(); it < end(); ++it)
    {
        auto firstSeqIt = it;
        while (std::any_of(first, last, [&it] (value_type ch) { return ch == *it; }))
            ++it;

        erase(firstSeqIt, it);
        it -= static_cast<size_t>(it - firstSeqIt);
    }
}

//==============================================================================
//!\fn          qx::basic_string<Traits>::erase_line_breaks
//
//!\brief  Erase \r and \n symbols from the string
//!\author Khrapov
//!\date   30.12.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::erase_line_breaks(void)
{
    erase_all_of(QX_CHAR_PREFIX(typename Traits::value_type, '\r'),
                 QX_CHAR_PREFIX(typename Traits::value_type, '\n'));
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to_ind   - first char index
//!\param  pSourse  - sourse string
//!\param  nSymbols - number of symbols to insert
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(
    size_type     to_ind,
    const_pointer pSourse,
    size_type     nSymbols)
{
    size_type nStartSymbols = size();
    if (resize(nStartSymbols + nSymbols, Traits::align()))
    {
        std::memmove(
            data() + to_ind + nSymbols,
            data() + to_ind,
            (nStartSymbols - to_ind) * sizeof(value_type));

        std::memcpy(data() + to_ind, pSourse, nSymbols * sizeof(value_type));
    }
}

//==============================================================================
//!\fn                    basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to_first   - target string inserting iterator
//!\param  from_first - source string first iterator
//!\param  from_last  - source string last iterator
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(
    iterator       to_first,
    const_iterator from_first,
    const_iterator from_last)
{
    insert(
        static_cast<size_type>(to_first - begin()),
        from_first.operator->(),
        static_cast<size_type>(from_last - from_first));
}

//==============================================================================
//!\fn                    basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to      - first char iterator
//!\param  pSourse - source string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(iterator to, const_pointer pSourse)
{
    insert(
        static_cast<size_type>(to - begin()),
        pSourse,
        Traits::length(pSourse));
}

//==============================================================================
//!\fn                    basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to       - first char index
//!\param  pSourse  - source string
//!\param  nSymbols - number of chars in source string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(
    iterator        to,
    const_pointer   pSourse,
    size_type       nSymbols)
{
    insert(
        static_cast<size_type>(to - begin()),
        pSourse,
        nSymbols);
}

//==============================================================================
//!\fn                    basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to      - first char index
//!\param  pSourse - source string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(size_type to_ind, const_pointer pSourse)
{
    insert(
        to_ind,
        pSourse,
        Traits::length(pSourse));
}

//==============================================================================
//!\fn                  basic_string<Traits>::push_back
//
//!\brief  Insert char in the end of the string
//!\param  ch - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::push_back(value_type ch)
{
    insert(size(), &ch, 1);
}

//==============================================================================
//!\fn                  basic_string<Traits>::push_front
//
//!\brief  Insert char in the beginning of the string
//!\param  ch - char
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::push_front(value_type ch)
{
    insert(0, &ch, 1);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find
//
//!\brief  Find first match
//!\param  pWhat    - c-string to find
//!\param  indBegin - start searching index
//!\param  indEnd   - end searching index (-1 - to the end).
//         if indEnd < indBegin, seach backward
//!\retval          - substring index
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    const_pointer pWhat,
    size_type     indBegin,
    size_type     indEnd) const
{
    size_type nSizeWhat = Traits::length(pWhat);

    if (indEnd == npos)
        indEnd = size();

    const_pointer pCurrentChar = data() + indBegin;
    const_pointer pEnd         = data() + indEnd;

    do
    {
        if (!Traits::compare_n(pWhat, pCurrentChar, nSizeWhat))
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
//!\param  ch       - char to find
//!\param  indBegin - start searching index
//!\param  indEnd   - end searching index (-1 - to the end)
//!\retval          - substring index or npos if not found
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    value_type    ch,
    size_type     indBegin,
    size_type     indEnd) const
{
    if (indEnd == npos)
        indEnd = size();

    const_pointer pCurrentChar = data() + indBegin;
    const_pointer pEnd         = data() + indEnd;

    do
    {
        if (*pCurrentChar == ch)
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
//!\param  str      - string to find
//!\param  indBegin - start searching index
//!\param  indEnd   - end searching index
//!\retval          - substring index or npos if not found
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    const basic_string& str,
    size_type           indBegin,
    size_type           indEnd) const
{
    return find(str.data(), indBegin, indEnd);
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::substr
//
//!\brief  Find substring
//!\param  begin - start index
//!\param  size  - string size (-1 - to the end)
//!\retval       - substring
//!\author Khrapov
//!\date   31.10.2019
//==============================================================================
template<class Traits>
inline basic_string<Traits> basic_string<Traits>::substr(
    size_type begin,
    size_type strLen) const
{
    basic_string str(data() + begin, (strLen != npos ? strLen : size() - begin));
    return std::move(str);
}

//==============================================================================
//!\fn                qx::basic_string<Traits>::find_last_of
//
//!\brief  Find last position of catacter
//!\param  ch    - char to find
//!\param  pos   - start searching index (from the end). npos - from the very end
//!\param  count - number of symbols to check (npos - to the beginning)
//!\retval       - symbol index or npos
//!\author Khrapov
//!\date   30.10.2019
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(
    value_type ch,
    size_type  pos,
    size_type  count) const
{
    if (pos == npos)
        pos = size();

    if (count == npos)
        count = size();

    basic_string str(ch);
    return find(str, pos, pos - count);
}

//==============================================================================
//!\fn                 qx::basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  pSep    - separator string
//!\param  nSepLen - separator string length (npos if str is null terminated)
//!\retval         - vector of strings
//!\author Khrapov
//!\date   21.03.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::vector basic_string<Traits>::split(
    const_pointer pSep,
    size_type     nSepLen) const
{
    vector tokens;

    if (nSepLen == npos)
        nSepLen = Traits::length(pSep);

    size_type start = 0, end = 0;
    while ((end = find(pSep, start)) != npos)
    {
        tokens.push_back(substr(start, end - start));
        start = end + nSepLen;
    }
    tokens.push_back(substr(start));

    return std::move(tokens);
}

//==============================================================================
//!\fn                 qx::basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  sep - char separator
//!\retval     - vector of strings
//!\author Khrapov
//!\date   21.03.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::vector basic_string<Traits>::split(
    const value_type sep) const
{
    vector tokens;

    size_type start = 0, end = 0;
    while ((end = find(sep, start)) != npos)
    {
        tokens.push_back(substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(substr(start));

    return std::move(tokens);
}

//==============================================================================
//!\fn                    basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  sep - separator string
//!\retval     - vector of strings
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline typename basic_string<Traits>::vector basic_string<Traits>::split(
    const basic_string& sep) const
{
    return split(sep.data(), sep.size());
}

//==============================================================================
//!\fn            qx::basic_string<Traits>::apply_case
//
//!\brief  Apply case type to the whole string
//!\param  ct - case type \see case_type
//!\author Khrapov
//!\date   31.10.2019
//==============================================================================
template<class Traits>
inline void basic_string<Traits>::apply_case(case_type ct)
{
    switch (ct)
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
//!\fn            qx::basic_string<Traits>::starts_with
//
//!\brief  Check if current string starts with char
//!\param  ch - char for comparison
//!\retval - true if starts with char
//!\author Khrapov
//!\date   08.10.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::starts_with(value_type ch) const
{
    if (!empty())
        return at(0) == ch;
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
//!\fn                 basic_string<Traits>::starts_with
//
//!\brief  Check if current string starts with string
//!\param  str - string to check
//!\retval     - true if starts with string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::starts_with(const basic_string& str) const
{
    return starts_with(str.data(), str.size());
}

//==============================================================================
//!\fn            basic_string<Traits>::starts_with<String, >
//
//!\brief  Check if current string starts with string
//!\param  str - string container to check
//!\retval     - true if starts with string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::starts_with(const String& str) const
{
    return starts_with(str.cbegin(), str.cend());
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
inline bool basic_string<Traits>::ends_with(value_type ch) const
{
    size_type nSize = size();
    if (nSize > 0)
        return at(nSize - 1) == ch;
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
    auto nStrSize = std::distance(itBegin, itEnd);
    return iter_strcmp(
        cend() - static_cast<size_type>(nStrSize),
        cend(),
        itBegin,
        itEnd) == 0;
}

//==============================================================================
//!\fn                  basic_string<Traits>::ends_with
//
//!\brief  Check if current string ends with string
//!\param  str - string to check
//!\retval     - true if starts with string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
inline bool basic_string<Traits>::ends_with(const basic_string& str) const
{
    return ends_with(str.data(), str.size());
}

//==============================================================================
//!\fn             basic_string<Traits>::ends_with<String, >
//
//!\brief  Check if current string ends with string
//!\param  str - string container to check
//!\retval     - true if starts with string
//!\author Khrapov
//!\date   13.11.2020
//==============================================================================
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::ends_with(const String& str) const
{
    return ends_with(str.cbegin(), str.cend());
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

template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(basic_string&& str) noexcept
{
    assign(std::move(str));
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(const basic_string& str)
{
    assign(str);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(value_type ch)
{
    assign(ch);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(const_pointer pSource)
{
    assign(pSource);
    return *this;
}
template<class Traits>
template<class String, class>
inline const basic_string<Traits>& basic_string<Traits>::operator=(const String& str)
{
    assign(str);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(const basic_string& str)
{
    append(str.data(), str.size());
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(value_type ch)
{
    append(&ch, 1);
    return *this;
}
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(const_pointer pSource)
{
    append(pSource, Traits::length(pSource));
    return *this;
}
template<class Traits>
template<class String, class>
inline const basic_string<Traits>& basic_string<Traits>::operator+=(const String& str)
{
    append(str.cbegin(), str.cend());
    return *this;
}
template<class Traits>
inline bool basic_string<Traits>::operator==(const basic_string& str) const
{
    return !compare(str.data());
}
template<class Traits>
inline bool basic_string<Traits>::operator==(value_type ch) const
{
    return !compare(&ch, 1);
}
template<class Traits>
inline bool basic_string<Traits>::operator==(const_pointer pSource) const
{
    return !compare(pSource);
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator==(const String& str) const
{
    return iter_strcmp(cbegin(), cend(), str.cbegin(), str.cend()) == 0;
}
template<class Traits>
inline bool basic_string<Traits>::operator!=(const basic_string& str) const
{
    return !operator==(str);
}
template<class Traits>
inline bool basic_string<Traits>::operator!=(value_type ch) const
{
    return !operator==(ch);
}
template<class Traits>
inline bool basic_string<Traits>::operator!=(const_pointer pSource) const
{
    return !operator==(pSource);
}
template<class Traits>
template<class String, class>
inline bool basic_string<Traits>::operator!=(const String& str) const
{
    return !operator==(str);
}
template<class Traits>
inline typename basic_string<Traits>::reference basic_string<Traits>::operator[](size_type ind)
{
    return at(ind);
}
template<class Traits>
inline typename basic_string<Traits>::const_reference basic_string<Traits>::operator[](size_type ind) const
{
    return at(ind);
}
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
    auto TryPushBack = [&str, &is, &ret_bit](typename qx::basic_string<Traits>::value_type ch) -> bool
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
            TryPushBack(ch);
            break;
        }
    }

    // add other symbols until space symbol
    while (is.get(ch))
    {
        if (!Traits::is_space(ch))
        {
            if (!TryPushBack(ch))
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
