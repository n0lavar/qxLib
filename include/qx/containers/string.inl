//============================================================================
//
//!\file                         string.inl
//
//!\brief       Lite string impl
//!\details     ~
//
//!\author      Khrapov
//!\date        4.09.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================

namespace qx
{

//============================================================================
//!\fn                  basic_string<Traits>::assign
//
//!\brief  Assign string
//!\param  pSource  - source string pointer
//!\param  nSymbols - source string size
//!\author Khrapov
//!\date   27.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(const_pointer pSource, size_type nSymbols)
{
    if (Resize(nSymbols, Traits::talign()))
        std::memcpy(m_pData, pSource, nSymbols * sizeof(value_type));
}

//============================================================================
//!\fn               basic_string<Traits>::assign
//
//!\brief  Assign by filling
//!\param  nSymbols - num of symbols of char
//!\param  ch       - char
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::assign(size_type nSymbols, value_type ch)
{
    if (Resize(nSymbols, Traits::talign()))
        std::fill(begin(), end(), ch);
}

//============================================================================
//!\fn                basic_string<Traits>::operator=
//
//!\param  str - source string
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<class Traits>
inline const basic_string<Traits> & basic_string<Traits>::operator=(basic_string<Traits> && str) noexcept
{
    if (this != &str)
        std::swap(m_pData, str.m_pData);

    return *this;
}

//============================================================================
//!\fn                basic_string<Traits>::operator=
//
//!\param  str - source string
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<class Traits>
inline const basic_string<Traits> & basic_string<Traits>::operator=(const basic_string<Traits> & str)
{
    if (this != &str)
        assign(str.m_pData, str.size());

    return *this;
}

//============================================================================
//!\fn                basic_string<Traits>::operator=
//
//!\param  ch - char to init
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<class Traits>
inline const basic_string<Traits> & basic_string<Traits>::operator=(value_type ch)
{
    assign(&ch, 1);
    return *this;
}

//============================================================================
//!\fn                basic_string<Traits>::operator=
//
//!\param  pSource - source string pointer
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<class Traits>
inline const basic_string<Traits> & basic_string<Traits>::operator=(const_pointer pSource)
{
    if (m_pData != pSource)
        assign(pSource, Traits::tstrlen(pSource));

    return *this;
}

//============================================================================
//!\fn                 basic_string<Traits>::operator=
//
//!\param  str - std string
//!\author Khrapov
//!\date   24.03.2020
//============================================================================
template<class Traits>
inline const basic_string<Traits>& basic_string<Traits>::operator=(const std_string_type& str)
{
    assign(str.data(), static_cast<size_type>(str.size())); 
    return *this;
}

//============================================================================
//!\fn               basic_string<Traits>::assign<FwdIt>
//
//!\brief  Assign by iterators
//!\param  first - first iterator of source
//!\param  last  - last iterator of source
//!\author Khrapov
//!\date   21.03.2020
//============================================================================
template<class Traits>
template<class FwdIt>
inline void basic_string<Traits>::assign(FwdIt first, FwdIt last)
{
    clear();
    for (FwdIt it = first; it != last; it++)
        push_back(*it);
}

//============================================================================
//!\fn             basic_string<Traits>::format<...Args>
//
//!\brief  Format string
//!\param  pStr    - format pattern
//!\param  ...args - arguments
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<class Traits>
template<class ...Args>
inline void basic_string<Traits>::format(const_pointer pStr, Args ...args)
{
    int length = Traits::tsnprintf(nullptr, 0, pStr, args...);
    if (length > 0 && Resize(length, Traits::talign()))
        Traits::tsnprintf(m_pData, static_cast<size_t>(length) + 1, pStr, args...);
}

//============================================================================
//!\fn             basic_string<Traits>::sformat<...Args>
//
//!\brief  Static format string
//!\param  pStr    - format pattern
//!\param  ...args - arguments
//!\retval         - result string
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<class Traits>
template<class ...Args>
inline basic_string<Traits> basic_string<Traits>::sformat(const_pointer pStr, Args ...args)
{
    basic_string str;
    str.format(pStr, args...);
    return std::move(str);
}

//============================================================================
//!\fn                 basic_string<Traits>::capacity
//
//!\brief  Get allocated memory size (including null terminator)
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::capacity(void) const
{
    auto pData = GetStrData();
    return pData 
        ? pData->nAllocatedSize 
        : 0;
}

//============================================================================
//!\fn                 basic_string<Traits>::reserve
//
//!\brief  Reserve memory for the string
//!\param  nCapacity - new capacity
//!\retval           - string capacity
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::reserve(size_type nCapacity)
{
    if (nCapacity > size())
        Resize(nCapacity, Traits::talign(), true);

    return capacity();
}
//============================================================================
//!\fn                   basic_string<Traits>::fit
//
//!\brief  Fit allocated size to string's actual size
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::fit(void)
{
    auto pData = GetStrData();
    if (pData && pData->nAllocatedSize > pData->nSize)
        Resize(pData->nSize);
}

//============================================================================
//!\fn                  basic_string<Traits>::erase
//
//!\brief  Erase substrung
//!\param  first - first substr char iterator
//!\param  last  - last substr char iterator (excluded)
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(iterator first, iterator last)
{
    if (first < last)
    {
        size_type nStartSize = size();

        if (size_type nSymbolsToCopy = last != end() ? Traits::tstrlen(last.operator->()) : 0; nSymbolsToCopy > 0)
            std::memcpy(first.operator->(), last.operator->(), nSymbolsToCopy * sizeof(value_type));

        Resize(static_cast<size_type>(nStartSize - (last - first)), Traits::talign());
    }
}

//============================================================================
//!\fn                  basic_string<Traits>::erase
//
//!\brief  Erase char
//!\param  it - char iterator
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(iterator it)
{
    erase(it, it + 1);
}

//============================================================================
//!\fn                  basic_string<Traits>::erase
//
//!\brief  Erase char
//!\param  pos - char position
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(size_type pos)
{
    erase(iterator(this, pos), iterator(this, pos + 1));
}

//============================================================================
//!\fn                  basic_string<Traits>::erase
//
//!\brief  Erase substrung
//!\param  ind_first - first substr char index
//!\param  nSymbols  - num symbols to erase
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::erase(size_type ind_first, size_type nSymbols)
{
    erase(iterator(this, ind_first), iterator(this, static_cast<size_t>(ind_first) + nSymbols));
}

//============================================================================
//!\fn           basic_string<Traits>::erase_all_of<...Args, >
//
//!\brief  Erase all chars container including from string
//!\param  ...args - symbols to erase
//!\author Khrapov
//!\date   22.03.2020
//============================================================================
template<class Traits>
template<class ... Args, class>
inline void basic_string<Traits>::erase_all_of(Args... args)
{
    std::array<typename Traits::value_type, sizeof...(args)> toRemove { args... };
    erase_all_of(toRemove.begin(), toRemove.end());
}

//============================================================================
//!\fn           basic_string<Traits>::erase_all_of<FwdIt, >
//
//!\brief  Erase all chars container including from string
//!\param  first - symbols to erase begin iterator
//!\param  last  - symbols to erase end iterator
//!\author Khrapov
//!\date   22.03.2020
//============================================================================
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
        it -= it - firstSeqIt; //-V765
    }
}

//============================================================================
//!\fn          qx::basic_string<Traits>::erase_line_breaks
//
//!\brief  Erase \r and \n symbols from the string
//!\author Khrapov
//!\date   30.12.2019
//============================================================================
template<class Traits>
inline void qx::basic_string<Traits>::erase_line_breaks(void)
{
    erase_all_of(CHAR_PREFIX(typename Traits::value_type, '\r'), 
                 CHAR_PREFIX(typename Traits::value_type, '\n'));
}

//============================================================================
//!\fn                  basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to_first   - first targer string char iterator
//!\param  from_first - first substr char iterator
//!\param  from_last  - second substr char iterator (excluding)
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(iterator to_first, const_iterator from_first, const_iterator from_last)
{
    insert(to_first - begin(), from_first.operator->(), from_last - from_first);
}

//============================================================================
//!\fn                  basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to      - first targer string char iterator
//!\param  pSourse - zero terminated sourse string
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(iterator to, const_pointer pSourse)
{
    insert(to - begin(), pSourse, Traits::tstrlen(pSourse));
}

//============================================================================
//!\fn                  basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to       - first targer string char iterator
//!\param  pSourse  - sourse string
//!\param  nSymbols - number of chars in sourse string
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(iterator to, const_pointer pSourse, size_type nSymbols)
{
    insert(to - begin(), pSourse, nSymbols);
}

//============================================================================
//!\fn                  basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to_ind  - first targer string char index
//!\param  pSourse - zero terminated sourse string
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(size_type to_ind, const_pointer pSourse)
{
    insert(to_ind, pSourse, Traits::tstrlen(pSourse));
}

//============================================================================
//!\fn                  basic_string<Traits>::insert
//
//!\brief  Insert substring
//!\param  to_ind   - first targer string char index
//!\param  pSourse  - sourse string
//!\param  nSymbols - number of symbols to insert
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::insert(size_type to_ind, const_pointer pSourse, size_type nSymbols)
{
    size_type nStartSymbols = size();
    if (Resize(nStartSymbols + nSymbols, Traits::talign()))
    {
        std::memmove(m_pData + to_ind + nSymbols, m_pData + to_ind, (nStartSymbols - to_ind) * sizeof(value_type));
        std::memcpy(m_pData + to_ind, pSourse, nSymbols * sizeof(value_type));
    }
}

//============================================================================
//!\fn                 basic_string<Traits>::push_back
//
//!\brief  Push char to the end 
//!\param  ch - char
//!\author Khrapov
//!\date   21.03.2020
//============================================================================
template<class Traits>
inline void basic_string<Traits>::push_back(value_type ch)
{
    insert(size(), &ch, 1);
}

//============================================================================
//!\fn                 basic_string<Traits>::push_front
//
//!\brief  Push char to the front
//!\param  ch - char
//!\author Khrapov
//!\date   21.03.2020
//============================================================================
template<class Traits>
inline void basic_string<Traits>::push_front(value_type ch)
{
    insert(0, &ch, 1);
}

//============================================================================
//!\fn                  basic_string<Traits>::find
//
//!\brief  Find first match
//!\param  pWhat    - c-string to find
//!\param  indBegin - start searching index
//!\param  indEnd   - end searching index (-1 - to the end).
//         if indEnd < indBegin, seach backward
//!\retval          - substring index
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(const_pointer pWhat,
                                                                           size_type     indBegin,
                                                                           size_type     indEnd) const
{
    size_type nSizeWhat = Traits::tstrlen(pWhat);

    if (indEnd == npos)
        indEnd = size();

    pointer       pCurrentChar = m_pData + indBegin;
    const_pointer pEnd         = m_pData + indEnd;

    do
    {
        if (!Traits::tstrncmp(pWhat, pCurrentChar, nSizeWhat))
            return static_cast<size_type>(pCurrentChar - m_pData);
        else
            qx::step_to(pCurrentChar, pEnd);
    } while (pCurrentChar != pEnd);

    return npos;
}

//============================================================================
//!\fn                  basic_string<Traits>::find
//
//!\brief  Find first match
//!\param  ch       - char to find
//!\param  indBegin - start searching index
//!\param  indEnd   - end searching index (-1 - to the end)
//!\retval          - substring index
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(value_type    ch,
                                                                           size_type     indBegin,
                                                                           size_type     indEnd) const
{
    if (indEnd == npos)
        indEnd = size();

    pointer       pCurrentChar = m_pData + indBegin;
    const_pointer pEnd         = m_pData + indEnd;

    do
    {
        if (*pCurrentChar == ch)
            return static_cast<size_type>(pCurrentChar - m_pData);
        else
            qx::step_to(pCurrentChar, pEnd);
    } while (pCurrentChar != pEnd);

    return npos;
}

//============================================================================
//!\fn                  basic_string<Traits>::find
//
//!\brief  Find first match
//!\param  str      - string to find
//!\param  indBegin - start searching index
//!\param  indEnd   - end searching index (-1 - to the end)
//!\retval          - substring index
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(const basic_string& str, 
                                                                           size_type           indBegin, 
                                                                           size_type           indEnd) const
{
    return find(str.data(), indBegin, indEnd);
}

//============================================================================
//!\fn              basic_string<Traits>::substr
//
//!\brief  Find substring
//!\param  begin - start index
//!\param  size  - string size (-1 - to the end)
//!\retval       - substring
//!\author Khrapov
//!\date   31.10.2019
//============================================================================
template<class Traits>
inline basic_string<Traits> basic_string<Traits>::substr(size_type begin, size_type strLen) const
{
    basic_string str(m_pData + begin, (strLen != npos ? strLen : size() - begin));
    return std::move(str);
}

//============================================================================
//!\fn                  basic_string<Traits>::find_last_of
//
//!\brief  Find last position of catacter
//!\param  ch    - char to find
//!\param  pos   - start searching index (from the end). npos - from the very end
//!\param  count - number of symbols to check (npos - to the beginning)
//!\retval       - symbol index or npos
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find_last_of(value_type ch,
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

//============================================================================
//!\fn                   basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  pSep    - separator string
//!\param  nSepLen - separator string length (npos if str is null terminated)
//!\retval         - vector of strings
//!\author Khrapov
//!\date   21.03.2020
//============================================================================
template<class Traits>
inline typename qx::basic_string<Traits>::vector basic_string<Traits>::split(const_pointer pSep, 
                                                                             size_type     nSepLen) const
{
    vector tokens;

    if (nSepLen == npos)
        nSepLen = Traits::tstrlen(pSep);

    size_type start = 0, end = 0;
    while ((end = find(pSep, start)) != qx::string::npos)
    {
        tokens.push_back(substr(start, end - start));
        start = end + nSepLen;
    }
    tokens.push_back(substr(start));

    return std::move(tokens);
}

//============================================================================
//!\fn                   basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  sep - char separator
//!\retval     - vector of strings
//!\author Khrapov
//!\date   21.03.2020
//============================================================================
template<class Traits>
inline typename qx::basic_string<Traits>::vector basic_string<Traits>::split(const value_type sep) const
{
    vector tokens;

    size_type start = 0, end = 0;
    while ((end = find(sep, start)) != qx::string::npos)
    {
        tokens.push_back(substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(substr(start));

    return std::move(tokens);
}

//============================================================================
//!\fn                  basic_string<Traits>::split
//
//!\brief  Split string by separator
//!\param  sep   - char to find
//!\retval       - vector of strings
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<class Traits>
inline typename qx::basic_string<Traits>::vector qx::basic_string<Traits>::split(const basic_string & sep) const
{
    return std::move(split(sep.data(), sep.size()));
}

//============================================================================
//!\fn              basic_string<Traits>::apply_case
//
//!\brief  Apply case type to the whole string
//!\param  ct - case type \see eCaseType
//!\author Khrapov
//!\date   31.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::apply_case(eCaseType ct)
{
    switch (ct)
    {
    case eCaseType::lower:
        for (value_type& ch : *this)
            ch = Traits::ttolower(ch);

        break;

    case eCaseType::upper:
        for (value_type& ch : *this)
            ch = Traits::ttoupper(ch);

        break;

    case eCaseType::random:
        for (value_type& ch : *this)
        {
            ch = qx::random(0, 1)
                ? Traits::ttoupper(ch)
                : Traits::ttolower(ch);
        }
        break;
    }
}

//============================================================================
//!\fn                   basic_string<Traits>::to<To>
//
//!\brief  Convert to integral signed type
//!\param  base - base of the interpreted integer value (0, 2-36)
//!\retval      - value or nullopt
//!\author Khrapov
//!\date   22.03.2020
//============================================================================
template<typename Traits>
template<typename To>
inline typename std::enable_if<std::is_signed_v<To> && !std::is_unsigned_v<To> && !std::is_floating_point_v<To>,
    std::optional<To>>::type basic_string<Traits>::to(int base)
{
    errno = 0;
    pointer pEnd = nullptr;
    i64 nRet = Traits::ttolli(m_pData, &pEnd, base);

    if (errno != 0
        || pEnd == m_pData
        || nRet < std::numeric_limits<To>::min()
        || nRet > std::numeric_limits<To>::max())
    {
        return std::nullopt;
    }

    return static_cast<To>(nRet);
}

//============================================================================
//!\fn                   basic_string<Traits>::to<To>
//
//!\brief  Convert to integral unsigned type
//!\param  base - base of the interpreted integer value (0, 2-36)
//!\retval      - value or nullopt
//!\author Khrapov
//!\date   22.03.2020
//============================================================================
template<typename Traits>
template<typename To>
inline typename std::enable_if<!std::is_signed_v<To> && std::is_unsigned_v<To> && !std::is_floating_point_v<To>,
    std::optional<To>>::type basic_string<Traits>::to(int base)
{
    errno = 0;
    pointer pEnd = nullptr;
    u64 nRet = Traits::ttoull(m_pData, &pEnd, base);

    if (errno != 0
        || pEnd == m_pData
        || nRet < std::numeric_limits<To>::min()
        || nRet > std::numeric_limits<To>::max())
    {
        return std::nullopt;
    }

    return static_cast<To>(nRet);
}

//============================================================================
//!\fn                   basic_string<Traits>::to<To>
//
//!\brief  Convert to floating point type
//!\retval  - value or nullopt
//!\author Khrapov
//!\date   22.03.2020
//============================================================================
template<typename Traits>
template<typename To>
inline typename std::enable_if<std::is_floating_point_v<To>,
    std::optional<To>>::type basic_string<Traits>::to()
{
    errno = 0;
    pointer pEnd = nullptr;
    long double nRet = Traits::ttold(m_pData, &pEnd);

    if (errno != 0
        || pEnd == m_pData
        || nRet < -std::numeric_limits<To>::max()
        || nRet >  std::numeric_limits<To>::max())
    {
        return std::nullopt;
    }

    return static_cast<To>(nRet);
}

//============================================================================
//!\fn                 basic_string<Traits>::from<From>
//
//!\brief  Construct string from custom type
//!\param  data      - data of type From
//!\param  pszFormat - format string if default is not enough
//!\author Khrapov
//!\date   24.03.2020
//============================================================================
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
            if constexpr (std::is_same_v<From, char>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%hhd");
            }
            else if constexpr (std::is_same_v<From, unsigned char>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%hhu");
            }
            else if constexpr (std::is_same_v<From, short>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%hd");
            }
            else if constexpr (std::is_same_v<From, unsigned short>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%hu");
            }
            else if constexpr (std::is_same_v<From, int>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%d");
            }
            else if constexpr (std::is_same_v<From, unsigned int>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%u");
            }
            else if constexpr (std::is_same_v<From, long>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%ld");
            }
            else if constexpr (std::is_same_v<From, unsigned long>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%lu");
            }
            else if constexpr (std::is_same_v<From, long long>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%lld");
            }
            else if constexpr (std::is_same_v<From, unsigned long long>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%llu");
            }
            else if constexpr (std::is_same_v<From, float>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%f");
            }
            else if constexpr (std::is_same_v<From, double>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%lf");
            }
            else if constexpr (std::is_same_v<From, long double>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "%Lf");
            }
            else if constexpr (std::is_pointer_v<From>)
            {
#ifdef _MSC_VER
                pszFormat = STR_PREFIX(typename Traits::value_type, "0x%p");
#else
                pszFormat = STR_PREFIX(typename Traits::value_type, "%p");
#endif
            }
            else if constexpr (std::is_same_v <From, std::nullptr_t>)
            {
                pszFormat = STR_PREFIX(typename Traits::value_type, "nullptr");
            }
            else if constexpr (std::is_same_v<From, bool>)
            {
                pszFormat = data
                    ? STR_PREFIX(typename Traits::value_type, "true")
                    : STR_PREFIX(typename Traits::value_type, "false");
            }
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

//============================================================================
//!\fn                basic_string<Traits>::sfrom<From>
//
//!\brief  Construct string from custom type and get it
//!\param  data      - data of type From
//!\param  pszFormat - format string if default is not enough
//!\retval           - constructed string
//!\author Khrapov
//!\date   24.03.2020
//============================================================================
template<class Traits>
template<typename From>
inline basic_string<Traits> basic_string<Traits>::sfrom(const From& data, const_pointer pszFormat)
{
    basic_string str;
    str.from(data, pszFormat);
    return std::move(str);
}

//============================================================================
//!\fn                basic_string<Traits>::operator[]
//
//!\param  ind - char index
//!\retval     - char value
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::reference basic_string<Traits>::operator[](size_type ind)
{
    return m_pData[ind];
}

//============================================================================
//!\fn                   basic_string<Traits>::at
//
//!\param  ind - char index
//!\retval     - char value
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::reference basic_string<Traits>::at(size_type ind)
{ 
    return operator[](ind); 
}

//============================================================================
//!\fn                  basic_string<Traits>::clear
//
//!\brief  Clear string
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::clear(void)
{
    std::free(GetStrData());
    m_pData = nullptr;
}

//============================================================================
//!\fn                   basic_string<Traits>::size
//
//!\brief  Get string size (excluding null terminator)
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::size(void) const
{
    const auto pData = GetStrData();
    return pData
        ? pData->nSize
        : 0;
}

//============================================================================
//!\fn                   basic_string<Traits>::data
//
//!\brief  Get c-string
//!\author Khrapov
//!\date   28.10.2019
//============================================================================
template<class Traits>
inline typename basic_string<Traits>::pointer basic_string<Traits>::data(void)
{
    return m_pData;
}
//============================================================================
//!\fn                basic_string<Traits>::GetStrData
//
//!\brief  Get string info struct
//!\author Khrapov
//!\date   27.10.2019
//============================================================================
template<class Traits>
inline SStrData<Traits> * basic_string<Traits>::GetStrData(void)
{
    return m_pData
        ? reinterpret_cast<SStrData<Traits>*>(reinterpret_cast<mem_t>(m_pData) - SStrData<Traits>::structSize())
        : nullptr;
}

//============================================================================
//!\fn                basic_string<Traits>::GetStrData
//
//!\brief  Get string info struct
//!\author Khrapov
//!\date   27.10.2019
//============================================================================
template<class Traits>
inline const SStrData<Traits>* basic_string<Traits>::GetStrData(void) const
{
    return m_pData
        ? reinterpret_cast<const SStrData<Traits>*>(reinterpret_cast<mem_t>(m_pData) - SStrData<Traits>::structSize())
        : nullptr;
}

//============================================================================
//!\fn                  basic_string<Traits>::Resize
//
//!\brief  Resize string.
//         If new size is smaller, string will be truncated
//!\param  nSymbols - new size
//!\param  nAlign   - align (if 16 then size 13->16 16->16 18->32)
//!\param  bReserve - reserve (don't change size and don't add null terminator to the end)
//!\retval          - true if memory alloc is succesful
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<class Traits>
inline bool basic_string<Traits>::Resize(size_type nSymbols, size_type nAlign, bool bReserve)
{
    typename Traits::size_type nSizeToAllocate = nAlign
        ? qx::align_size<typename Traits::value_type>(nSymbols + 1, nAlign)
        : nSymbols + 1;

    SStrData<Traits>* pStrData = GetStrData();

    // increase or decrease size
    void* pNewBlock = std::realloc(pStrData, SStrData<Traits>::structSize() + nSizeToAllocate * sizeof(value_type));
    if (pNewBlock)
    {
        pStrData = reinterpret_cast<SStrData<Traits>*>(pNewBlock);
        pStrData->nAllocatedSize = nSizeToAllocate;

        if (!bReserve)
            pStrData->nSize = nSymbols;
        else if (!m_pData)
            pStrData->nSize = 0;

        m_pData = reinterpret_cast<pointer>(reinterpret_cast<mem_t>(pNewBlock) + SStrData<Traits>::structSize());
    }
    else
        return false;

    if (!bReserve)
        m_pData[nSymbols] = Traits::teol();

    return true;
}

//============================================================================
//!\fn                  basic_string<Traits>::Append
//
//!\brief  Append string to the current
//!\param  pSource  - source string
//!\param  nSymbols - source string size
//!\author Khrapov
//!\date   27.10.2019
//============================================================================
template<class Traits>
inline void basic_string<Traits>::Append(const_pointer pSource, size_type nSymbols)
{
    size_type nCurrentSymbls = size();
    if (Resize(nCurrentSymbls + nSymbols, Traits::talign()))
        std::memcpy(m_pData + nCurrentSymbls, pSource, nSymbols * sizeof(value_type));
}

//============================================================================
//!\fn                 basic_string<Traits>::Compare
//
//!\brief  Performs a binary comparison of the characters
//!\param  pStr     - string to compare
//!\param  nSymbols - number of symbols to compare (0 - string is zero terminated)
//!\retval          -   < 0 the first character that does not match has a lower value in this than in pStr
//                        0 the contents of both strings are equal
//                      > 0 the first character that does not match has a greater value in this than in pStr
//!\author Khrapov
//!\date   28.10.2019
//============================================================================
template<class Traits>
inline int basic_string<Traits>::Compare(const_pointer pStr, size_type nSymbols) const
{
    if (nSymbols)
        return Traits::tstrncmp(m_pData, pStr, nSymbols);
    else
        return Traits::tstrcmp(m_pData, pStr);
}

}