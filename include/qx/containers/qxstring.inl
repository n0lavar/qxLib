//============================================================================
//
//!\file                         qxstring.inl
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

template<class Traits>
inline typename Traits::size_type AlignSize(typename Traits::size_type nSize,
                                            typename Traits::size_type nAlign)
{
    return ((nSize + nAlign) - (nSize + nAlign) % nAlign) * sizeof(Traits::value_type);
}

//============================================================================
//!\fn               basic_string<T, Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  pSource  - source string pointer
//!\param  nSymbols - source string length
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<typename T, class Traits>
basic_string<T, Traits>::basic_string(const_pointer pSource, size_type nSymbols)
{
    Assign(pSource, nSymbols);
}

//============================================================================
//!\fn               basic_string<T, Traits>::basic_string
//
//!\brief  basic_string object constructor
//!\param  ch       - char
//!\param  nSymbols - num of symbols of char
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<typename T, class Traits>
basic_string<T, Traits>::basic_string(value_type ch, size_type nSymbols)
{
    if (Resize(nSymbols, Traits::talign()))
        for (size_type i = 0; i < size(); i++)
            m_pData[i] = ch;
}

//============================================================================
//!\fn                basic_string<T, Traits>::operator=
//
//!\param  str - source string
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<typename T, class Traits>
const basic_string<T, Traits> & basic_string<T, Traits>::operator=(basic_string<T, Traits> && str) noexcept
{
    if (this != &str)
        std::swap(m_pData, str.m_pData);

    return *this;
}

//============================================================================
//!\fn                basic_string<T, Traits>::operator=
//
//!\param  str - source string
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<typename T, class Traits>
const basic_string<T, Traits> & basic_string<T, Traits>::operator=(const basic_string<T, Traits> & str)
{
    if (this != &str)
        Assign(str.m_pData, str.size());

    return *this;
}

//============================================================================
//!\fn                basic_string<T, Traits>::operator=
//
//!\param  ch - char to init
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<typename T, class Traits>
const basic_string<T, Traits> & basic_string<T, Traits>::operator=(value_type ch)
{
    Assign(&ch, 1);
    return *this;
}

//============================================================================
//!\fn                basic_string<T, Traits>::operator=
//
//!\param  pSource - source string pointer
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<typename T, class Traits>
const basic_string<T, Traits> & basic_string<T, Traits>::operator=(const_pointer pSource)
{
    if (m_pData != pSource)
        Assign(pSource, Traits::tstrlen(pSource));

    return *this;
}

//============================================================================
//!\fn             basic_string<T, Traits>::format<...Args>
//
//!\brief  Format string
//!\param  pStr    - format pattern
//!\param  ...args - arguments
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<typename T, class Traits>
template<class ...Args>
void basic_string<T, Traits>::format(const_pointer pStr, Args ...args)
{
    size_type length = Traits::tsnprintf(nullptr, 0, pStr, args...);
    if (length > 0 && Resize(length, Traits::talign()))
        Traits::tsnprintf(m_pData, static_cast<size_t>(length + 1), pStr, args...);
}

//============================================================================
//!\fn             basic_string<T, Traits>::sformat<...Args>
//
//!\brief  Static format string
//!\param  pStr    - format pattern
//!\param  ...args - arguments
//!\retval         - result string
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<typename T, class Traits>
template<class ...Args>
basic_string<T, Traits> basic_string<T, Traits>::sformat(const_pointer pStr, Args ...args)
{
    basic_string str;
    str.format(pStr, args...);
    return std::move(str);
}

//============================================================================
//!\fn                 basic_string<T, Traits>::capacity
//
//!\brief  Get allocated memory size
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<typename T, class Traits>
typename basic_string<T, Traits>::size_type basic_string<T, Traits>::capacity(void) const
{
    auto pData = GetStrData();
    return pData ? pData->nAllocatedSize : 0;
}

//============================================================================
//!\fn                 basic_string<T, Traits>::reserve
//
//!\brief  Reserve memory for the string
//!\param  nCapacity - new capacity
//!\retval           - string capacity
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<typename T, class Traits>
typename basic_string<T, Traits>::size_type basic_string<T, Traits>::reserve(size_type nCapacity)
{
    if (nCapacity > size())
        Resize(nCapacity, Traits::talign(), true);

    return capacity();
}
//============================================================================
//!\fn                   basic_string<T, Traits>::fit
//
//!\brief  Fit allocated size to string's actual size
//!\author Khrapov
//!\date   29.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::fit(void)
{
    auto pData = GetStrData();
    if (pData && pData->nAllocatedSize > pData->nSize)
        Resize(pData->nSize);
}

//============================================================================
//!\fn                  basic_string<T, Traits>::erase
//
//!\brief  Erase substrung
//!\param  first - first substr char iterator
//!\param  last  - last substr char iterator (excluded)
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::erase(iterator first, iterator last)
{
    size_type nStartSize = size();

    if (size_type nSymbolsToCopy = last != end() ? Traits::tstrlen(last.operator->()) : 0; nSymbolsToCopy > 0)
        memcpy(first.operator->(), last.operator->(), nSymbolsToCopy * sizeof(value_type));

    Resize(static_cast<size_type>(nStartSize - (last - first)), Traits::talign());
}

//============================================================================
//!\fn                  basic_string<T, Traits>::erase
//
//!\brief  Erase char
//!\param  it - char iterator
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::erase(iterator it)
{
    erase(it, it + 1);
}

//============================================================================
//!\fn                  basic_string<T, Traits>::erase
//
//!\brief  Erase char
//!\param  pos - char position
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::erase(size_type pos)
{
    erase(iterator(pos), iterator(pos + 1));
}

//============================================================================
//!\fn                  basic_string<T, Traits>::erase
//
//!\brief  Erase substrung
//!\param  ind_first - first substr char index
//!\param  nSymbols  - num symbols to erase
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::erase(size_type ind_first, size_type nSymbols)
{
    erase(iterator(this, ind_first), iterator(this, static_cast<size_t>(ind_first) + nSymbols));
}

//============================================================================
//!\fn                  basic_string<T, Traits>::insert
//
//!\brief  Insert substrung
//!\param  from_first - first substr char iterator
//!\param  from_last  - second substr char iterator
//!\param  to_first   - first targer string char iterator
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::insert(const_iterator from_first, const_iterator from_last, iterator to_first)
{
    insert(to_first - begin(), from_first.operator->(), from_last - from_first);
}

//============================================================================
//!\fn                  basic_string<T, Traits>::insert
//
//!\brief  Insert substrung
//!\param  to      - first targer string char iterator
//!\param  pSourse - zero terminated sourse string
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::insert(iterator to, const_pointer pSourse)
{
    insert(to - begin(), pSourse, Traits::tstrlen(pSourse));
}

//============================================================================
//!\fn                  basic_string<T, Traits>::insert
//
//!\brief  Insert substrung
//!\param  to       - first targer string char iterator
//!\param  pSourse  - sourse string
//!\param  nSymbols - number of chars in sourse string
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::insert(iterator to, const_pointer pSourse, size_type nSymbols)
{
    insert(to - begin(), pSourse, nSymbols);
}

//============================================================================
//!\fn                  basic_string<T, Traits>::insert
//
//!\brief  Insert substrung
//!\param  to_ind  - first targer string char index
//!\param  pSourse - zero terminated sourse string
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::insert(size_type to_ind, const_pointer pSourse)
{
    insert(to_ind, pSourse, Traits::tstrlen(pSourse));
}

//============================================================================
//!\fn                  basic_string<T, Traits>::insert
//
//!\brief  Insert substrung
//!\param  to_ind   - first targer string char index
//!\param  pSourse  - sourse string
//!\param  nSymbols - number of symbols to insert
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::insert(size_type to_ind, const_pointer pSourse, size_type nSymbols)
{
    size_type nStartSymbols = size();
    Resize(nStartSymbols + nSymbols, Traits::talign());
    memcpy(m_pData + to_ind + nSymbols, m_pData + to_ind, (nStartSymbols - to_ind) * sizeof(value_type));
    memcpy(m_pData + to_ind, pSourse, nSymbols * sizeof(value_type));
}

//============================================================================
//!\fn                  basic_string<T, Traits>::find
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
template<typename T, class Traits>
typename basic_string<T, Traits>::size_type basic_string<T, Traits>::find(const_pointer pWhat,
                                                                          size_type     indBegin,
                                                                          size_type     indEnd) const
{
    size_type nSize = size();
    size_type nSizeWhat = Traits::tstrlen(pWhat);

    if (indEnd == npos)
        indEnd = nSize;

    if (qx::between(0, nSize, indBegin) && qx::between(0, nSize, indEnd))
    {
        pointer         pCurrentChar = m_pData + indBegin;
        const_pointer   pEnd = m_pData + indEnd;

        do
        {
            if (!Traits::tstrncmp(pWhat, pCurrentChar, nSizeWhat))
                return static_cast<size_type>(pCurrentChar - m_pData);
            else
                qx::step_to(pCurrentChar, pEnd);
        } while (pCurrentChar != pEnd);
    }

    return npos;
}

//============================================================================
//!\fn                  basic_string<T, Traits>::find
//
//!\brief  Find first match
//!\param  ch       - char to find
//!\param  indBegin - start searching index
//!\param  indEnd   - end searching index (-1 - to the end)
//!\retval          - substring index
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
typename basic_string<T, Traits>::size_type basic_string<T, Traits>::find(value_type    ch,
                                                                          size_type     indBegin,
                                                                          size_type     indEnd) const
{
    basic_string str(ch);
    return find(str.data(), indBegin, indEnd);
}

//============================================================================
//!\fn              basic_string<T, Traits>::substr
//
//!\brief  Find substring
//!\param  begin - start index
//!\param  size  - string size (-1 - to the end)
//!\retval       - substring
//!\author Khrapov
//!\date   31.10.2019
//============================================================================
template<typename T, class Traits>
basic_string<T, Traits> basic_string<T, Traits>::substr(size_type begin, size_type strLen) const
{
    basic_string str(m_pData + begin, (strLen != npos ? strLen : size() - begin));
    return std::move(str);
}

//============================================================================
//!\fn                  basic_string<T, Traits>::find_last_of
//
//!\brief  Find last position of catacter
//!\param  ch    - char to find
//!\param  pos   - start searching index (from the end). npos - from the very end
//!\param  count - number of symbols to check (npos - to the beginning)
//!\retval       - symbol index or npos
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
typename basic_string<T, Traits>::size_type basic_string<T, Traits>::find_last_of(value_type ch, 
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
//!\fn                  basic_string<T, Traits>::split
//
//!\brief  Split string by separator
//!\param  sep   - char to find
//!\retval       - vector of strings
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
std::vector<basic_string<T, Traits>> qx::basic_string<T, Traits>::split(const basic_string & sep) const
{
    std::vector<qx::string> tokens;

    size_type start = 0, end = 0;
    while ((end = find(sep.data(), start)) != qx::string::npos)
    {
        tokens.push_back(substr(start, end - start));
        start = end + sep.size();
    }
    tokens.push_back(substr(start));

    return std::move(tokens);
}

//============================================================================
//!\fn                  basic_string<T, Traits>::split
//
//!\brief  Split string by separator
//!\param  text  - string to split
//!\param  sep   - char to find
//!\retval       - vector of strings
//!\author Khrapov
//!\date   30.10.2019
//============================================================================
template<typename T, class Traits>
std::vector<basic_string<T, Traits>> qx::basic_string<T, Traits>::split(const basic_string & text, 
                                                                        const basic_string & sep)
{
    return text.split(sep);
}

//============================================================================
//!\fn          qx::basic_string<T, Traits>::delete_line_breaks
//
//!\brief  Delete \r and \n symbols in the string
//!\author Khrapov
//!\date   30.12.2019
//============================================================================
template<typename T, class Traits>
void qx::basic_string<T, Traits>::delete_line_breaks(void)
{
    constexpr std::array toRemove { '\r', '\n' };
    for (auto it = begin(); it < end(); ++it)
        if (std::any_of(toRemove.begin(), toRemove.end(), [&it] (char ch) { return ch == *it; }))
            erase(it);
}

//============================================================================
//!\fn            basic_string<T, Traits>::delete_line_breaks
//
//!\brief  Delete \r and \n symbols in the string
//!\param  pSourse - source string pointer
//!\retval         - result string
//!\author Khrapov
//!\date   30.12.2019
//============================================================================
template<typename T, class Traits>
basic_string<T, Traits> basic_string<T, Traits>::delete_line_breaks(const_pointer pSourse)
{
    basic_string str(pSourse);
    str.delete_line_breaks();
    return std::move(str);
}

//============================================================================
//!\fn              basic_string<T, Traits>::apply_case
//
//!\brief  Apply case type to the whole string
//!\param  ct - case type \see eCaseType
//!\author Khrapov
//!\date   31.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::apply_case(eCaseType ct)
{
    switch (ct) //-V719
    {
    case eCaseType::lower:
        std::for_each(begin(), end(), [] (value_type& ch) { ch = Traits::ttolower(ch); });
        break;

    case eCaseType::upper:
        std::for_each(begin(), end(), [] (value_type& ch) { ch = Traits::ttoupper(ch); });
        break;

    case eCaseType::all_capitalized:
    case eCaseType::sentence:
    case eCaseType::random:
        //ASSERT(0);  // write code
        break;
    }
}

//============================================================================
//!\fn              basic_string<T, Traits>::to
//
//!\brief  Try convert string into param type
//!\param  fake param to specializate convert type
//         to avoid function template partial specialization
//         usage: 
//         int number = str.to(int()).value_or(0);
//!\param  base - expected number base (0, 2-36)
//!\retval - converted value if successful
//           nullopt if range error
//           0 if no convertion is possible
//!\author Khrapov
//!\date   31.10.2019
//============================================================================

template<typename T, class Traits>
inline std::optional<i8> basic_string<T, Traits>::to(i8, int base) const
{
    errno = 0;
    i64 nRet = Traits::ttolli(m_pData, base);

    if (errno != 0 || nRet > std::numeric_limits<i8>::max() || nRet < std::numeric_limits<i8>::min())
        return std::nullopt;

    return static_cast<i8>(nRet);
}

template<typename T, class Traits>
inline std::optional<i16> basic_string<T, Traits>::to(i16, int base) const
{
    errno = 0;
    i64 nRet = Traits::ttolli(m_pData, base);

    if (errno != 0 || nRet > std::numeric_limits<i16>::max() || nRet < std::numeric_limits<i16>::min())
        return std::nullopt;

    return static_cast<i16>(nRet);
}

template<typename T, class Traits>
inline std::optional<i32> basic_string<T, Traits>::to(i32, int base) const
{
    errno = 0;
    i64 nRet = Traits::ttolli(m_pData, base);

    if (errno != 0 || nRet > std::numeric_limits<i32>::max() || nRet < std::numeric_limits<i32>::min())
        return std::nullopt;

    return static_cast<i32>(nRet);
}

template<typename T, class Traits>
inline std::optional<i64> basic_string<T, Traits>::to(i64, int base) const
{
    errno = 0;
    i64 nRet = Traits::ttolli(m_pData, base);

    if (errno != 0)
        return std::nullopt;

    return nRet;
}

template<typename T, class Traits>
inline std::optional<u8> basic_string<T, Traits>::to(u8, int base) const
{
    errno = 0;
    u64 nRet = Traits::ttoull(m_pData, base);

    if (errno != 0 || nRet > std::numeric_limits<u8>::max())
        return std::nullopt;

    return static_cast<u8>(nRet);
}

template<typename T, class Traits>
inline std::optional<u16> basic_string<T, Traits>::to(u16, int base) const
{
    errno = 0;
    u64 nRet = Traits::ttoull(m_pData, base);

    if (errno != 0 || nRet > std::numeric_limits<u16>::max())
        return std::nullopt;

    return static_cast<u16>(nRet);
}

template<typename T, class Traits>
inline std::optional<u32> basic_string<T, Traits>::to(u32, int base) const
{
    errno = 0;
    u64 nRet = Traits::ttoull(m_pData, base);

    if (errno != 0 || nRet > std::numeric_limits<u32>::max())
        return std::nullopt;

    return static_cast<u32>(nRet);
}

template<typename T, class Traits>
inline std::optional<u64> basic_string<T, Traits>::to(u64, int base) const
{
    errno = 0;
    u64 nRet = Traits::ttoull(m_pData, base);

    if (errno != 0)
        return std::nullopt;

    return nRet;
}

template<typename T, class Traits>
inline std::optional<float> basic_string<T, Traits>::to(float) const
{
    errno = 0;
    long double nRet = Traits::ttold(m_pData);

    if (errno != 0 || nRet < -std::numeric_limits<float>::max() || nRet > std::numeric_limits<float>::max())
        return std::nullopt;

    return static_cast<float>(nRet);
}

template<typename T, class Traits>
inline std::optional<double> qx::basic_string<T, Traits>::to(double) const
{
    errno = 0;
    long double nRet = Traits::ttold(m_pData);

    if (errno != 0 || nRet < -std::numeric_limits<double>::max() || nRet > std::numeric_limits<double>::max())
        return std::nullopt;

    return static_cast<double>(nRet);
}

template<typename T, class Traits>
inline std::optional<long double> qx::basic_string<T, Traits>::to(long double) const
{
    errno = 0;
    long double nRet = Traits::ttold(m_pData);

    if (errno != 0)
        return std::nullopt;

    return nRet;
}

//============================================================================
//!\fn                basic_string<T, Traits>::operator[]
//
//!\param  ind - char index
//!\retval     - char value
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<typename T, class Traits>
typename basic_string<T, Traits>::reference basic_string<T, Traits>::operator[](size_type ind)
{
    return m_pData[ind];
}

//============================================================================
//!\fn                  basic_string<T, Traits>::clear
//
//!\brief  Clear string
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::clear(void)
{
    if (m_pData)
    {
        free(GetStrData());
        m_pData = nullptr;
    }
}

//============================================================================
//!\fn                   basic_string<T, Traits>::size
//
//!\brief  Get string size
//!\author Khrapov
//!\date   19.10.2019
//============================================================================
template<typename T, class Traits>
typename basic_string<T, Traits>::size_type basic_string<T, Traits>::size(void) const
{
    const auto pData = GetStrData();
    return pData
        ? pData->nSize
        : 0;
}

//============================================================================
//!\fn                   basic_string<T, Traits>::data
//
//!\brief  Get c-string
//!\author Khrapov
//!\date   28.10.2019
//============================================================================
template<typename T, class Traits>
typename basic_string<T, Traits>::const_pointer basic_string<T, Traits>::data(void) const
{
    return m_pData;
}
template<typename T, class Traits>
typename basic_string<T, Traits>::pointer basic_string<T, Traits>::data(void)
{
    return m_pData;
}

//============================================================================
//!\fn                basic_string<T, Traits>::GetStrData
//
//!\brief  Get string info struct
//!\author Khrapov
//!\date   27.10.2019
//============================================================================
template<typename T, class Traits>
SStrData<Traits> * basic_string<T, Traits>::GetStrData(void)
{
    return m_pData
        ? reinterpret_cast<SStrData<Traits>*>(reinterpret_cast<mem_t>(m_pData) - SStrData<Traits>::structSize())
        : nullptr;
}

//============================================================================
//!\fn                basic_string<T, Traits>::GetStrData
//
//!\brief  Get string info struct
//!\author Khrapov
//!\date   27.10.2019
//============================================================================
template<typename T, class Traits>
const SStrData<Traits>* basic_string<T, Traits>::GetStrData(void) const
{
    return m_pData
        ? reinterpret_cast<const SStrData<Traits>*>(reinterpret_cast<mem_t>(m_pData) - SStrData<Traits>::structSize())
        : nullptr;
}

//============================================================================
//!\fn                  basic_string<T, Traits>::Resize
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
template<typename T, class Traits>
bool basic_string<T, Traits>::Resize(size_type nSymbols, size_type nAlign, bool bReserve)
{
    typename Traits::size_type nSizeToAllocate = nAlign
        ? AlignSize<Traits>(nSymbols + 1, nAlign)
        : nSymbols + 1;

    SStrData<Traits>* pStrData = GetStrData();

    // increase or decrease size
    void* pNewBlock = pStrData
        ? realloc(pStrData, SStrData<Traits>::structSize() + nSizeToAllocate * sizeof(value_type))
        : malloc(SStrData<Traits>::structSize() + nSizeToAllocate * sizeof(value_type));

    if (pNewBlock)
    {
        pStrData = reinterpret_cast<SStrData<Traits>*>(pNewBlock);
        pStrData->nAllocatedSize = nSizeToAllocate;

        if (!bReserve)
            pStrData->nSize = nSymbols;

        m_pData = reinterpret_cast<pointer>(reinterpret_cast<mem_t>(pNewBlock) + SStrData<Traits>::structSize());
    }
    else
        return false;

    if (!bReserve)
        m_pData[nSymbols] = Traits::teol();

    return true;
}

//============================================================================
//!\fn                  basic_string<T, Traits>::Assign
//
//!\brief  Assign string
//!\param  pSource  - source string pointer
//!\param  nSymbols - source string size
//!\author Khrapov
//!\date   27.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::Assign(const_pointer pSource, size_type nSymbols)
{
    if (Resize(nSymbols, Traits::talign()))
        memcpy(m_pData, pSource, nSymbols);
}

//============================================================================
//!\fn                  basic_string<T, Traits>::Append
//
//!\brief  Append string to the current
//!\param  pSource  - source string
//!\param  nSymbols - source string size
//!\author Khrapov
//!\date   27.10.2019
//============================================================================
template<typename T, class Traits>
void basic_string<T, Traits>::Append(cstr pSource, size_type nSymbols)
{
    size_type nCurrentSymbls = size();
    if (Resize(nCurrentSymbls + nSymbols, Traits::talign()))
        memcpy(m_pData + nCurrentSymbls, pSource, nSymbols * sizeof(value_type));
}

//============================================================================
//!\fn                 basic_string<T, Traits>::Compare
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
template<typename T, class Traits>
int basic_string<T, Traits>::Compare(cstr pStr, size_type nSymbols) const
{
    if (nSymbols)
        return Traits::tstrncmp(m_pData, pStr, nSymbols);
    else
        return Traits::tstrcmp(m_pData, pStr);
}

}