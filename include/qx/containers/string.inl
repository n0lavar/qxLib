/**

    @file      string.inl
    @author    Khrapov
    @date      4.09.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class Traits>
inline basic_string<Traits>::basic_string(value_type chSymbol) noexcept
{
    assign(chSymbol);
}

template<class Traits>
inline basic_string<Traits>::basic_string(
    size_type  nSymbols,
    value_type chSymbol) noexcept
{
    assign(nSymbols, chSymbol);
}

template<class Traits>
inline basic_string<Traits>::basic_string(
    const_pointer pszSource,
    size_type     nSymbols) noexcept
{
    assign(pszSource, nSymbols);
}

template<class Traits>
inline basic_string<Traits>::basic_string(const_pointer pszSource) noexcept
{
    assign(pszSource);
}

template<class Traits>
inline basic_string<Traits>::basic_string(basic_string&& sAnother) noexcept
{
    assign(std::move(sAnother));
}

template<class Traits>
inline basic_string<Traits>::basic_string(const basic_string& sAnother) noexcept
{
    assign(sAnother);
}

template<class Traits>
template<class FwdIt>
inline basic_string<Traits>::basic_string(FwdIt itFirst, FwdIt itLast) noexcept
{
    assign(itFirst, itLast);
}

template<class Traits>
template<string_convertable String>
inline basic_string<Traits>::basic_string(const String& sAnother) noexcept
{
    assign(sAnother);
}

template<class Traits>
inline basic_string<Traits>::~basic_string(void) noexcept
{
    free();
}

template<class Traits>
inline void basic_string<Traits>::assign(value_type chSymbol) noexcept
{
    assign(&chSymbol, 1);
}

template<class Traits>
inline void basic_string<Traits>::assign(
    size_type  nSymbols,
    value_type chSymbol) noexcept
{
    if (_resize(nSymbols, Traits::align()))
        std::fill(begin(), end(), chSymbol);
}

template<class Traits>
inline void basic_string<Traits>::assign(
    const_pointer pSource,
    size_type     nSymbols) noexcept
{
    if (_resize(nSymbols, Traits::align()))
        std::memmove(data(), pSource, nSymbols * sizeof(value_type));
}

template<class Traits>
inline void basic_string<Traits>::assign(const_pointer pszSource) noexcept
{
    if (pszSource != data())
        assign(pszSource, Traits::length(pszSource));
}

template<class Traits>
inline void basic_string<Traits>::assign(basic_string&& sAnother) noexcept
{
    std::swap(m_Data, sAnother.m_Data);
}

template<class Traits>
inline void basic_string<Traits>::assign(const basic_string& sAnother) noexcept
{
    if (sAnother.data() != data())
        assign(sAnother.data());
}

template<class Traits>
template<class FwdIt>
inline void basic_string<Traits>::assign(FwdIt itFirst, FwdIt itLast) noexcept
{
    clear();
    for (FwdIt it = itFirst; it != itLast; ++it)
        push_back(*it);
}

template<class Traits>
template<string_convertable String>
inline void basic_string<Traits>::assign(const String& sAnother) noexcept
{
    assign(sAnother.cbegin(), sAnother.cend());
}

template<class Traits>
void basic_string<Traits>::sprintf(const_pointer pszFormat, ...) noexcept
{
    va_list args;
    va_start(args, pszFormat);
    this->vsprintf(pszFormat, args);
    va_end(args);
}

template<class Traits>
inline void basic_string<Traits>::vsprintf(
    const_pointer pszFormat,
    va_list       args) noexcept
{
    va_list args_copy;
    va_copy(args_copy, args);
    int length = Traits::vsnprintf(nullptr, 0, pszFormat, args_copy);
    va_end(args_copy);

    if (length > 0 && _resize(static_cast<size_type>(length), Traits::align()))
    {
        Traits::vsnprintf(
            data(),
            static_cast<size_type>(length) + 1,
            pszFormat,
            args);
    }
}

template<class Traits>
template<class... Args>
inline basic_string<Traits> basic_string<Traits>::static_sprintf(
    const_pointer pszFormat,
    Args... args) noexcept
{
    basic_string str;
    str.sprintf(pszFormat, args...);
    return std::move(str);
}

template<class Traits>
inline void basic_string<Traits>::append_sprintf(
    const_pointer pszFormat,
    ...) noexcept
{
    va_list args;
    va_start(args, pszFormat);
    append_vsprintf(pszFormat, args);
    va_end(args);
}

template<class Traits>
inline void basic_string<Traits>::append_vsprintf(
    const_pointer pszFormat,
    va_list       args) noexcept
{
    va_list args_copy;
    va_copy(args_copy, args);
    int length = Traits::vsnprintf(nullptr, 0, pszFormat, args_copy);
    va_end(args_copy);

    const size_type nSize = size();
    if (length > 0
        && _resize(nSize + static_cast<size_type>(length), Traits::align()))
    {
        Traits::vsnprintf(
            data() + nSize,
            static_cast<size_type>(length) + 1,
            pszFormat,
            args);
    }
}

template<class Traits>
inline void basic_string<Traits>::swap(basic_string& sOther) noexcept
{
    std::swap(m_Data, sOther.m_Data);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::reserve(
    size_type nCapacity) noexcept
{
    if (nCapacity > capacity())
        _resize(nCapacity, Traits::align(), string_resize_type::reserve);

    return capacity();
}

template<class Traits>
inline void basic_string<Traits>::shrink_to_fit(void) noexcept
{
    if (!m_Data.is_small() && capacity() > size())
        _resize(size(), 0, string_resize_type::shrink_to_fit);
}

template<class Traits>
inline void basic_string<Traits>::free(void) noexcept
{
    m_Data.free();
}

template<class Traits>
inline typename basic_string<Traits>::string_view basic_string<Traits>::substr(
    size_type nPos,
    size_type nSymbols) const noexcept
{
    return string_view(
        data() + nPos,
        nSymbols != npos ? nSymbols : size() - nPos);
}

template<class Traits>
inline void basic_string<Traits>::to_lower(void) noexcept
{
    for (value_type& ch : *this)
        ch = Traits::to_lower(ch);
}

template<class Traits>
inline void basic_string<Traits>::to_upper(void) noexcept
{
    for (value_type& ch : *this)
        ch = Traits::to_upper(ch);
}

template<class Traits>
inline typename basic_string<Traits>::value_type basic_string<Traits>::front(
    void) const noexcept
{
    return at(0);
}

template<class Traits>
inline typename basic_string<Traits>::value_type basic_string<Traits>::back(
    void) const noexcept
{
    return at(size() - 1);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::length(
    void) const noexcept
{
    return size();
}

template<class Traits>
inline typename basic_string<Traits>::const_pointer basic_string<Traits>::c_str(
    void) const noexcept
{
    return data();
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::capacity(
    void) const noexcept
{
    return m_Data.capacity();
}

template<class Traits>
constexpr typename basic_string<Traits>::size_type basic_string<
    Traits>::max_size(void) noexcept
{
    return std::numeric_limits<size_type>::max() - 1 // npos reserved
           - 1;                                      // null terminator
}

template<class Traits>
template<typename To>
inline std::optional<To> basic_string<Traits>::to(void) const noexcept
{
    std::optional<To> optResult = std::nullopt;

    if constexpr (
        std::is_trivial_v<
            To> && std::is_standard_layout_v<To> || std::is_pointer_v<To> || std::is_same_v<To, std::nullptr_t>)
    {
        if constexpr (std::is_same_v<To, std::nullptr_t>)
        {
            if (compare(QX_STR_PREFIX(typename Traits::value_type, "nullptr"))
                == 0)
            {
                optResult = nullptr;
            }
        }
        else if constexpr (std::is_same_v<To, bool>)
        {
            if (compare(QX_STR_PREFIX(typename Traits::value_type, "true"))
                == 0)
            {
                optResult = true;
            }
            else
            {
                optResult = false;
            }
        }
        else if (auto pszFormat = get_format_specifier<value_type, To>())
        {
            To        result;
            const int nConvertedArgs =
                Traits::sscanf(data(), pszFormat, &result);

            if (nConvertedArgs == 1)
                optResult = result;
        }
    }
    else
    {
        To           result;
        sstream_type ss(data());
        ss >> result;
        optResult = result;
    }

    return optResult;
}

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

template<class Traits>
template<typename From>
inline void basic_string<Traits>::from(
    const From&   data,
    const_pointer pszFormat) noexcept
{
    if constexpr (
        std::is_trivial_v<
            From> && std::is_standard_layout_v<From> || std::is_pointer_v<From> || std::is_same_v<From, std::nullptr_t>)
    {
        if (!pszFormat)
        {
            if constexpr (std::is_same_v<From, std::nullptr_t>)
            {
                pszFormat =
                    QX_STR_PREFIX(typename Traits::value_type, "nullptr");
            }
            else if constexpr (std::is_same_v<From, bool>)
            {
                pszFormat =
                    data ? QX_STR_PREFIX(typename Traits::value_type, "true")
                         : QX_STR_PREFIX(typename Traits::value_type, "false");
            }
            else
            {
                pszFormat = get_format_specifier<value_type, From>();
            }
        }

        if (pszFormat)
            sprintf(pszFormat, data);
    }
    else
    {
        sstream_type ss;
        ss << data;
        assign(ss.str());
    }
}

template<class Traits>
template<typename From>
inline basic_string<Traits> basic_string<Traits>::static_from(
    const From&   data,
    const_pointer pszFormat) noexcept
{
    basic_string str;
    str.from(data, pszFormat);
    return std::move(str);
}

template<class Traits>
inline void basic_string<Traits>::append(value_type chSymbol) noexcept
{
    append(&chSymbol, 1);
}

template<class Traits>
inline void basic_string<Traits>::append(
    const_pointer pszStr,
    size_type     nSymbols) noexcept
{
    const size_type nSize = size();
    const size_type nSizeSource =
        nSymbols == npos ? Traits::length(pszStr) : nSymbols;

    if (_resize(nSize + nSizeSource, Traits::align()))
        std::memcpy(data() + nSize, pszStr, nSizeSource * sizeof(value_type));
}

template<class Traits>
inline void basic_string<Traits>::append(const basic_string& sStr) noexcept
{
    append(sStr.data(), sStr.size());
}

template<class Traits>
template<class FwdIt>
inline void basic_string<Traits>::append(FwdIt itBegin, FwdIt itEnd) noexcept
{
    for (auto it = itBegin; it != itEnd; ++it)
        push_back(*it);
}

template<class Traits>
template<string_convertable String>
inline void basic_string<Traits>::append(const String& sStr) noexcept
{
    append(sStr.cbegin(), sStr.cend());
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type  nPos,
    value_type chSymbol) noexcept
{
    return insert(nPos, &chSymbol, 1);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type     nPos,
    const_pointer pszWhat,
    size_type     nSymbols) noexcept
{
    const size_type nSize = size();
    const size_type nSizeSource =
        nSymbols == npos ? Traits::length(pszWhat) : nSymbols;

    if (nSizeSource > 0 && _resize(nSize + nSizeSource, Traits::align()))
    {
        std::memmove(
            data() + nPos + nSizeSource,
            data() + nPos,
            (nSize - nPos) * sizeof(value_type));

        std::memcpy(data() + nPos, pszWhat, nSizeSource * sizeof(value_type));

        return nPos + nSizeSource;
    }
    else
    {
        return npos;
    }
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type nPos,
    FwdIt     itWhatBegin,
    FwdIt     itWhatEnd) noexcept
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
            ++nWhatSize;

        size_type nStartSymbols = size();
        if (nWhatSize > 0
            && _resize(nStartSymbols + nWhatSize, Traits::align()))
        {
            std::memmove(
                data() + nPos + nWhatSize,
                data() + nPos,
                (nStartSymbols - nPos) * sizeof(value_type));

            size_type nWhatPos = 0;
            for (auto it = itWhatBegin; it != itWhatEnd; ++it)
            {
                at(nPos + nWhatPos) = *it;
                ++nWhatPos;
            }

            return nPos + nWhatSize;
        }
        else
        {
            return npos;
        }
    }
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type           nPos,
    const basic_string& sWhat) noexcept
{
    return insert(nPos, sWhat.data(), sWhat.size());
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    size_type nPos,
    String    sWhat) noexcept
{
    return insert(static_cast<size_type>(nPos), sWhat.cbegin(), sWhat.cend());
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator itPos,
    value_type     chSymbol) noexcept
{
    return insert(static_cast<size_type>(itPos - cbegin()), chSymbol);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator itPos,
    const_pointer  pszWhat,
    size_type      nSymbols) noexcept
{
    return insert(static_cast<size_type>(itPos - cbegin()), pszWhat, nSymbols);
}

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

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator itPos,
    FwdIt          itWhatBegin,
    FwdIt          itWhatEnd) noexcept
{
    return insert(
        static_cast<size_type>(itPos - begin()),
        itWhatBegin,
        itWhatEnd);
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<Traits>::insert(
    const_iterator itPos,
    String         sWhat) noexcept
{
    return insert(
        static_cast<size_type>(itPos - begin()),
        sWhat.cbegin(),
        sWhat.cend());
}

template<class Traits>
inline void basic_string<Traits>::push_back(value_type chSymbol) noexcept
{
    insert(size(), &chSymbol, 1);
}

template<class Traits>
inline void basic_string<Traits>::push_front(value_type chSymbol) noexcept
{
    insert(0, &chSymbol, 1);
}

template<class Traits>
inline void basic_string<Traits>::erase(
    iterator itFirst,
    iterator itLast) noexcept
{
    if (itFirst < itLast)
    {
        size_type nStartSize = size();
        size_type nSymbolsToCopy =
            itLast != end() ? Traits::length(itLast.operator->()) : 0;

        if (nSymbolsToCopy > 0)
        {
            std::memcpy(
                itFirst.operator->(),
                itLast. operator->(),
                nSymbolsToCopy * sizeof(value_type));
        }

        _resize(
            static_cast<size_type>(nStartSize - (itLast - itFirst)),
            Traits::align());
    }
}

template<class Traits>
inline void basic_string<Traits>::erase(iterator itPos) noexcept
{
    erase(itPos, itPos + 1);
}

template<class Traits>
inline void basic_string<Traits>::erase(size_type nPos) noexcept
{
    erase(iterator(this, nPos), iterator(this, nPos + 1));
}

template<class Traits>
inline void basic_string<Traits>::erase(
    size_type nPos,
    size_type nSymbols) noexcept
{
    erase(iterator(this, nPos), iterator(this, nPos + nSymbols));
}

template<class Traits>
inline typename basic_string<Traits>::value_type basic_string<Traits>::pop_back(
    void) noexcept
{
    value_type chRet = back();
    erase(size() - 1);
    return chRet;
}

template<class Traits>
inline typename basic_string<Traits>::value_type basic_string<
    Traits>::pop_front(void) noexcept
{
    value_type chRet = front();
    erase(0);
    return chRet;
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    void) noexcept
{
    return _trim_left(
        [](value_type ch)
        {
            return Traits::is_space(ch);
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    value_type chSymbol) noexcept
{
    return _trim_left(
        [chSymbol](value_type ch)
        {
            return ch == chSymbol;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    const_pointer pszStr) noexcept
{
    return _trim_left(
        [pszStr](value_type ch)
        {
            for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0');
                 ++j)
            {
                if (pszStr[j] == ch)
                    return true;
            }

            return false;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    const_pointer pStr,
    size_type     nStrSize) noexcept
{
    return _trim_left(
        [pStr, nStrSize](value_type ch)
        {
            for (size_type j = 0; j < nStrSize; ++j)
                if (pStr[j] == ch)
                    return true;

            return false;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    const basic_string& sStr) noexcept
{
    return trim_left(sStr.data(), sStr.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    FwdIt itBegin,
    FwdIt itEnd) noexcept
{
    return _trim_left(
        [itBegin, itEnd](auto ch)
        {
            for (auto it = itBegin; it != itEnd; ++it)
                if (*it == ch)
                    return true;

            return false;
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim_left(
    const String& sStr) noexcept
{
    return trim_left(sStr.cbegin(), sStr.cend());
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::trim_right(void) noexcept
{
    return _trim_right(
        [](value_type ch)
        {
            return Traits::is_space(ch);
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::trim_right(value_type chSymbol) noexcept
{
    return _trim_right(
        [chSymbol](value_type ch)
        {
            return ch == chSymbol;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::trim_right(const_pointer pszStr) noexcept
{
    return _trim_right(
        [pszStr](value_type ch)
        {
            for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0');
                 ++j)
            {
                if (pszStr[j] == ch)
                    return true;
            }

            return false;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::trim_right(const_pointer pStr, size_type nStrSize) noexcept
{
    return _trim_right(
        [pStr, nStrSize](value_type ch)
        {
            for (size_type j = 0; j < nStrSize; ++j)
                if (pStr[j] == ch)
                    return true;

            return false;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::trim_right(const basic_string& sStr) noexcept
{
    return trim_right(sStr.data(), sStr.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::trim_right(FwdIt itBegin, FwdIt itEnd) noexcept
{
    return _trim_right(
        [itBegin, itEnd](auto ch)
        {
            for (auto it = itBegin; it != itEnd; ++it)
                if (*it == ch)
                    return true;

            return false;
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::trim_right(const String& sStr) noexcept
{
    return trim_right(sStr.cbegin(), sStr.cend());
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    void) noexcept
{
    return _trim(
        [](value_type ch)
        {
            return Traits::is_space(ch);
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    value_type chSymbol) noexcept
{
    return _trim(
        [chSymbol](value_type ch)
        {
            return ch == chSymbol;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    const_pointer pszStr) noexcept
{
    return _trim(
        [pszStr](value_type ch)
        {
            for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0');
                 ++j)
            {
                if (pszStr[j] == ch)
                    return true;
            }

            return false;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    const_pointer pStr,
    size_type     nStrSize) noexcept
{
    return _trim(
        [pStr, nStrSize](value_type ch)
        {
            for (size_type j = 0; j < nStrSize; ++j)
                if (pStr[j] == ch)
                    return true;

            return false;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    const basic_string& sStr) noexcept
{
    return trim(sStr.data(), sStr.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    FwdIt itBegin,
    FwdIt itEnd) noexcept
{
    return _trim(
        [itBegin, itEnd](auto ch)
        {
            for (auto it = itBegin; it != itEnd; ++it)
                if (*it == ch)
                    return true;

            return false;
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<Traits>::trim(
    const String& sStr) noexcept
{
    return trim(sStr.cbegin(), sStr.cend());
}

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

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    const_pointer pszStr,
    size_type     nBegin,
    size_type     nEnd,
    size_type     nStrSize) noexcept
{
    const size_type nLocalStrSize =
        nStrSize != npos ? nStrSize : Traits::length(pszStr);

    const size_type nPos = find(pszStr, nBegin, nLocalStrSize, nEnd);

    if (nPos != npos)
        erase(nPos, nLocalStrSize);

    return nPos;
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    const basic_string& sStr,
    size_type           nBegin,
    size_type           nEnd) noexcept
{
    const size_type nPos = find(sStr, nBegin, nEnd);

    if (nPos != npos)
        erase(nPos, sStr.size());

    return nPos;
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    FwdIt     itBegin,
    FwdIt     itEnd,
    size_type nBegin,
    size_type nEnd) noexcept
{
    const size_type nPos = find(itBegin, itEnd, nBegin, nEnd);

    if (nPos != npos)
        erase(nPos, static_cast<size_type>(std::distance(itBegin, itEnd)));

    return nPos;
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<Traits>::remove(
    const String& sStr,
    size_type     nBegin,
    size_type     nEnd) noexcept
{
    return remove(sStr.cbegin(), sStr.cend(), nBegin, nEnd);
}

template<class Traits>
inline bool basic_string<Traits>::remove_prefix(value_type chSymbol) noexcept
{
    return remove(
               chSymbol,
               static_cast<size_type>(0),
               static_cast<size_type>(1))
           != npos;
}

template<class Traits>
inline bool basic_string<Traits>::remove_prefix(
    const_pointer pStr,
    size_type     nStrSize) noexcept
{
    return remove(pStr, static_cast<size_type>(0), nStrSize, nStrSize) != npos;
}

template<class Traits>
inline bool basic_string<Traits>::remove_prefix(
    const basic_string& sStr) noexcept
{
    return remove(sStr, static_cast<size_type>(0), sStr.size()) != npos;
}

template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::remove_prefix(
    FwdIt itBegin,
    FwdIt itEnd) noexcept
{
    return remove(
               itBegin,
               itEnd,
               static_cast<size_type>(0),
               static_cast<size_type>(std::distance(itBegin, itEnd)))
           != npos;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::remove_prefix(const String& sStr) noexcept
{
    return remove_prefix(sStr.cbegin(), sStr.cend());
}

template<class Traits>
inline bool basic_string<Traits>::remove_suffix(value_type chSymbol) noexcept
{
    const size_type nSize = size();
    return remove(chSymbol, nSize - 1, nSize) != npos;
}

template<class Traits>
inline bool basic_string<Traits>::remove_suffix(
    const_pointer pStr,
    size_type     nStrSize) noexcept
{
    const size_type nSize = size();
    const size_type nLocalStrSize =
        nStrSize != npos ? nStrSize : Traits::length(pStr);

    return remove(pStr, nSize - nLocalStrSize, nSize, nLocalStrSize) != npos;
}

template<class Traits>
inline bool basic_string<Traits>::remove_suffix(
    const basic_string& sStr) noexcept
{
    return remove_suffix(sStr.data(), sStr.size());
}

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
               nSize)
           != npos;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::remove_suffix(const String& sStr) noexcept
{
    return remove_suffix(sStr.cbegin(), sStr.cend());
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    remove_all(value_type chSymbol, size_type nBegin, size_type nEnd) noexcept
{
    size_type nOccurrences       = 0;
    size_type nLastOccurrencePos = nBegin;

    do
    {
        ++nOccurrences;
        nLastOccurrencePos = remove(chSymbol, nLastOccurrencePos, nEnd);
    } while (nLastOccurrencePos != npos);

    return nOccurrences - 1;
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    remove_all(
        const_pointer pStr,
        size_type     nBegin,
        size_type     nEnd,
        size_type     nStrSize) noexcept
{
    size_type nOccurrences       = 0;
    size_type nLastOccurrencePos = nBegin;

    do
    {
        ++nOccurrences;
        nLastOccurrencePos = remove(pStr, nLastOccurrencePos, nEnd, nStrSize);
    } while (nLastOccurrencePos != npos);

    return nOccurrences - 1;
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    remove_all(
        const basic_string& sStr,
        size_type           nBegin,
        size_type           nEnd) noexcept
{
    return remove_all(sStr.data(), nBegin, nEnd, sStr.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    remove_all(
        FwdIt     itFirst,
        FwdIt     itLast,
        size_type nBegin,
        size_type nEnd) noexcept
{
    size_type nOccurrences       = 0;
    size_type nLastOccurrencePos = nBegin;

    do
    {
        ++nOccurrences;
        nLastOccurrencePos = remove(itFirst, itLast, nLastOccurrencePos, nEnd);
    } while (nLastOccurrencePos != npos);

    return nOccurrences - 1;
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    remove_all(const String& sStr, size_type nBegin, size_type nEnd) noexcept
{
    return remove_all(sStr.cbegin(), sStr.cend(), nBegin, nEnd);
}

template<class Traits>
template<class TFind, class TReplace>
inline typename basic_string<Traits>::size_type basic_string<Traits>::replace(
    TFind     sFind,
    TReplace  sReplace,
    size_type nBegin,
    size_type nEnd) noexcept
{
    size_type nPos = remove(sFind, nBegin, nEnd);
    if (nPos != npos)
        return insert(nPos, sReplace);
    else
        return npos;
}

template<class Traits>
template<class TFind, class TReplace>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    replace_all(
        TFind     sFind,
        TReplace  sReplace,
        size_type nBegin,
        size_type nEnd) noexcept
{
    size_type nOccurrences = 0;
    size_type nPos         = nBegin;

    do
    {
        nPos = replace(sFind, sReplace, nPos, nEnd);
        if (nPos != npos)
            ++nOccurrences;
    } while (nPos != npos);

    return nOccurrences;
}

template<class Traits>
inline int basic_string<Traits>::compare(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1);
}

template<class Traits>
inline int qx::basic_string<Traits>::compare(
    const_pointer pszStr) const noexcept
{
    return Traits::compare(data(), pszStr);
}

template<class Traits>
inline int basic_string<Traits>::compare(const_pointer pStr, size_type nSymbols)
    const noexcept
{
    return Traits::compare_n(data(), pStr, nSymbols);
}

template<class Traits>
inline int basic_string<Traits>::compare(
    const basic_string& sStr) const noexcept
{
    return compare(sStr.data(), sStr.size());
}

template<class Traits>
template<class FwdIt>
inline int basic_string<Traits>::compare(FwdIt itBegin, FwdIt itEnd)
    const noexcept
{
    return iter_strcmp(cbegin(), cend(), itBegin, itEnd);
}

template<class Traits>
template<string_convertable String>
inline int basic_string<Traits>::compare(const String& sStr) const noexcept
{
    return compare(sStr.cbegin(), sStr.cend());
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    value_type chSymbol,
    size_type  nBegin,
    size_type  nEnd) const noexcept
{
    return _find(
        nBegin,
        nEnd,
        [chSymbol](const_pointer pCurrentChar)
        {
            return *pCurrentChar == chSymbol;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nWhatSize,
    size_type     nEnd) const noexcept
{
    const size_type nLocalWhatSize =
        nWhatSize != npos ? nWhatSize : Traits::length(pszWhat);

    return _find(
        nBegin,
        nEnd,
        [pszWhat, nLocalWhatSize](const_pointer pCurrentChar)
        {
            return !Traits::compare_n(pszWhat, pCurrentChar, nLocalWhatSize);
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    const basic_string& sWhat,
    size_type           nBegin,
    size_type           nEnd) const noexcept
{
    return find(sWhat.data(), nBegin, sWhat.size(), nEnd);
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    FwdIt     itWhatBegin,
    FwdIt     itWhatEnd,
    size_type nBegin,
    size_type nEnd) const noexcept
{
    return _find(
        nBegin,
        nEnd,
        [this, itWhatBegin, itWhatEnd, nEnd](const_pointer pCurrentChar)
        {
            return !iter_strcmp(
                const_iterator(
                    this,
                    static_cast<size_type>(pCurrentChar - data())),
                const_iterator(this, static_cast<size_type>(nEnd)),
                itWhatBegin,
                itWhatEnd);
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<Traits>::find(
    String    sWhat,
    size_type nBegin,
    size_type nEnd) const noexcept
{
    return find(sWhat.cbegin(), sWhat.cend(), nBegin, nEnd);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    value_type chSymbol,
    size_type  nBegin,
    size_type  nEnd) const noexcept
{
    return _rfind(
        nBegin,
        nEnd,
        [chSymbol](const_pointer pCurrentChar)
        {
            return *pCurrentChar == chSymbol;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nWhatSize,
    size_type     nEnd) const noexcept
{
    const size_type nLocalWhatSize =
        nWhatSize != npos ? nWhatSize : Traits::length(pszWhat);

    return _rfind(
        nBegin,
        nEnd,
        [pszWhat, nLocalWhatSize](const_pointer pCurrentChar)
        {
            return !Traits::compare_n(pszWhat, pCurrentChar, nLocalWhatSize);
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    const basic_string& sWhat,
    size_type           nBegin,
    size_type           nEnd) const noexcept
{
    return rfind(sWhat.data(), nBegin, sWhat.size(), nEnd);
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    FwdIt     itWhatBegin,
    FwdIt     itWhatEnd,
    size_type nBegin,
    size_type nEnd) const noexcept
{
    return _rfind(
        nBegin,
        nEnd,
        [this, itWhatBegin, itWhatEnd, nEnd](const_pointer pCurrentChar)
        {
            return !iter_strcmp(
                const_iterator(
                    this,
                    static_cast<size_type>(pCurrentChar - data())),
                const_iterator(this, static_cast<size_type>(nEnd)),
                itWhatBegin,
                itWhatEnd);
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<Traits>::rfind(
    String    sWhat,
    size_type nBegin,
    size_type nEnd) const noexcept
{
    return rfind(sWhat.cbegin(), sWhat.cend(), nBegin, nEnd);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_first_of(value_type chSymbol, size_type nBegin) const noexcept
{
    return find(chSymbol, nBegin);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_first_of(const_pointer pszWhat, size_type nBegin, size_type nWhatSize)
        const noexcept
{
    return _find_first_of(
        pszWhat,
        pszWhat + nWhatSize,
        nBegin,
        [](const_pointer pChar)
        {
            return pChar + 1;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_first_of(const_pointer pszWhat, size_type nBegin) const noexcept
{
    return _find_first_of(
        pszWhat,
        static_cast<const_pointer>(nullptr),
        nBegin,
        [](const_pointer pChar)
        {
            return *(pChar + 1) != QX_CHAR_PREFIX(value_type, '\0') ? pChar + 1
                                                                    : nullptr;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_first_of(const basic_string& sWhat, size_type nBegin) const noexcept
{
    return find_first_of(sWhat.data(), nBegin, sWhat.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_first_of(FwdIt itWhatBegin, FwdIt itWhatEnd, size_type nBegin)
    const noexcept
{
    return _find_first_of(
        itWhatBegin,
        itWhatEnd,
        nBegin,
        [](FwdIt itChar)
        {
            return ++itChar;
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_first_of(String sWhat, size_type nBegin) const noexcept
{
    return find_first_of(sWhat.cbegin(), sWhat.cend(), nBegin);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_last_of(value_type chSymbol, size_type nEnd) const noexcept
{
    return rfind(chSymbol, npos, nEnd);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_last_of(const_pointer pszWhat, size_type nEnd, size_type nWhatSize)
        const noexcept
{
    return _find_last_of(
        pszWhat,
        pszWhat + nWhatSize,
        nEnd,
        [](const_pointer pChar)
        {
            return pChar + 1;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_last_of(const_pointer pszWhat, size_type nEnd) const noexcept
{
    return _find_last_of(
        pszWhat,
        static_cast<const_pointer>(nullptr),
        nEnd,
        [](const_pointer pChar)
        {
            return *(pChar + 1) != QX_CHAR_PREFIX(value_type, '\0') ? pChar + 1
                                                                    : nullptr;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_last_of(const basic_string& sWhat, size_type nEnd) const noexcept
{
    return find_last_of(sWhat.data(), nEnd, sWhat.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_last_of(FwdIt itWhatBegin, FwdIt itWhatEnd, size_type nEnd)
    const noexcept
{
    return _find_last_of(
        itWhatBegin,
        itWhatEnd,
        nEnd,
        [](FwdIt itChar)
        {
            return ++itChar;
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_last_of(String sWhat, size_type nEnd) const noexcept
{
    return find_last_of(sWhat.cbegin(), sWhat.cend(), nEnd);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_first_not_of(value_type chSymbol, size_type nBegin) const noexcept
{
    return _find(
        nBegin,
        npos,
        [chSymbol](const_pointer pCurrentChar)
        {
            return *pCurrentChar != chSymbol;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_first_not_of(
        const_pointer pszWhat,
        size_type     nBegin,
        size_type     nWhatSize) const noexcept
{
    return _find_first_not_of(
        pszWhat,
        pszWhat + nWhatSize,
        nBegin,
        [](const_pointer pChar)
        {
            return pChar + 1;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_first_not_of(const_pointer pszWhat, size_type nBegin) const noexcept
{
    return _find_first_not_of(
        pszWhat,
        static_cast<const_pointer>(nullptr),
        nBegin,
        [](const_pointer pChar)
        {
            return *(pChar + 1) != QX_CHAR_PREFIX(value_type, '\0') ? pChar + 1
                                                                    : nullptr;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_first_not_of(const basic_string& sWhat, size_type nBegin)
    const noexcept
{
    return find_first_not_of(sWhat.data(), nBegin, sWhat.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_first_not_of(FwdIt itWhatBegin, FwdIt itWhatEnd, size_type nBegin)
        const noexcept
{
    return _find_first_not_of(
        itWhatBegin,
        itWhatEnd,
        nBegin,
        [](FwdIt itChar)
        {
            return ++itChar;
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_first_not_of(String sWhat, size_type nBegin) const noexcept
{
    return find_first_not_of(sWhat.cbegin(), sWhat.cend(), nBegin);
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_last_not_of(value_type chSymbol, size_type nEnd) const noexcept
{
    return _rfind(
        npos,
        nEnd,
        [chSymbol](const_pointer pCurrentChar)
        {
            return *pCurrentChar != chSymbol;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_last_not_of(const_pointer pszWhat, size_type nEnd, size_type nWhatSize)
        const noexcept
{
    return _find_last_not_of(
        pszWhat,
        pszWhat + nWhatSize,
        nEnd,
        [](const_pointer pChar)
        {
            return pChar + 1;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_last_not_of(const_pointer pszWhat, size_type nEnd) const noexcept
{
    return _find_last_not_of(
        pszWhat,
        static_cast<const_pointer>(nullptr),
        nEnd,
        [](const_pointer pChar)
        {
            return *(pChar + 1) != QX_CHAR_PREFIX(value_type, '\0') ? pChar + 1
                                                                    : nullptr;
        });
}

template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_last_not_of(const basic_string& sWhat, size_type nEnd) const noexcept
{
    return find_last_not_of(sWhat.data(), nEnd, sWhat.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    find_last_not_of(FwdIt itWhatBegin, FwdIt itWhatEnd, size_type nEnd)
        const noexcept
{
    return _find_last_not_of(
        itWhatBegin,
        itWhatEnd,
        nEnd,
        [](FwdIt itChar)
        {
            return ++itChar;
        });
}

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::find_last_not_of(String sWhat, size_type nEnd) const noexcept
{
    return find_last_not_of(sWhat.cbegin(), sWhat.cend(), nEnd);
}

template<class Traits>
inline typename basic_string<Traits>::views basic_string<Traits>::split(
    const value_type chSeparator) const noexcept
{
    views tokens;

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

template<class Traits>
inline typename basic_string<Traits>::views basic_string<Traits>::split(
    const_pointer pszSeparator,
    size_type     nSepLen) const noexcept
{
    views tokens;

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

template<class Traits>
inline typename basic_string<Traits>::views basic_string<Traits>::split(
    const basic_string& sSeparator) const noexcept
{
    return split(sSeparator.data(), sSeparator.size());
}

template<class Traits>
template<class FwdIt>
inline typename basic_string<Traits>::views basic_string<Traits>::split(
    FwdIt itSepFirst,
    FwdIt itSepLast) const noexcept
{
    views tokens;

    const size_type nSepLen =
        static_cast<size_type>(std::distance(itSepFirst, itSepLast));

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

template<class Traits>
template<string_convertable String>
inline typename basic_string<Traits>::views basic_string<Traits>::split(
    const String& sSeparator) const noexcept
{
    return split(sSeparator.cbegin(), sSeparator.cend());
}

template<class Traits>
inline bool basic_string<Traits>::starts_with(
    value_type chSymbol) const noexcept
{
    if (!empty())
        return at(0) == chSymbol;
    else
        return false;
}

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

template<class Traits>
inline bool basic_string<Traits>::starts_with(
    const basic_string& sStr) const noexcept
{
    return starts_with(sStr.data(), sStr.size());
}

template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::starts_with(FwdIt itBegin, FwdIt itEnd)
    const noexcept
{
    auto nStrSize = std::distance(itBegin, itEnd);
    return iter_strcmp(
               cbegin(),
               cbegin() + static_cast<size_type>(nStrSize),
               itBegin,
               itEnd)
           == 0;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::starts_with(const String& sStr) const noexcept
{
    return starts_with(sStr.cbegin(), sStr.cend());
}

template<class Traits>
inline bool basic_string<Traits>::ends_with(value_type chSymbol) const noexcept
{
    const size_type nSize = size();
    if (nSize > 0)
        return at(nSize - 1) == chSymbol;
    else
        return false;
}

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
            return Traits::compare_n(
                       data() + nThisSize - nStrSize,
                       pszStr,
                       nStrSize)
                   == 0;
    }

    return false;
}

template<class Traits>
inline bool basic_string<Traits>::ends_with(
    const basic_string& sStr) const noexcept
{
    return ends_with(sStr.data(), sStr.size());
}

template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::ends_with(FwdIt itBegin, FwdIt itEnd)
    const noexcept
{
    return iter_strcmp(
               cend() - static_cast<size_type>(std::distance(itBegin, itEnd)),
               cend(),
               itBegin,
               itEnd)
           == 0;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::ends_with(const String& sStr) const noexcept
{
    return ends_with(sStr.cbegin(), sStr.cend());
}

template<class Traits>
inline bool basic_string<Traits>::contains(value_type chSymbol) const noexcept
{
    return find(chSymbol) != npos;
}

template<class Traits>
inline bool basic_string<Traits>::contains(
    const_pointer pszStr,
    size_type     nStrSize) const noexcept
{
    return find(pszStr, 0, nStrSize) != npos;
}

template<class Traits>
inline bool basic_string<Traits>::contains(
    const basic_string& sStr) const noexcept
{
    return find(sStr) != npos;
}

template<class Traits>
template<class FwdIt>
inline bool basic_string<Traits>::contains(FwdIt itBegin, FwdIt itEnd)
    const noexcept
{
    return find(itBegin, itEnd) != npos;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::contains(const String& sStr) const noexcept
{
    return find(sStr) != npos;
}

template<class Traits>
inline basic_string<Traits>& basic_string<Traits>::operator=(
    value_type chSymbol) noexcept
{
    assign(chSymbol);
    return *this;
}

template<class Traits>
inline basic_string<Traits>& basic_string<Traits>::operator=(
    const_pointer pszSource) noexcept
{
    assign(pszSource);
    return *this;
}

template<class Traits>
inline basic_string<Traits>& basic_string<Traits>::operator=(
    basic_string&& sStr) noexcept
{
    assign(std::move(sStr));
    return *this;
}

template<class Traits>
inline basic_string<Traits>& basic_string<Traits>::operator=(
    const basic_string& sStr) noexcept
{
    assign(sStr);
    return *this;
}

template<class Traits>
template<string_convertable String>
inline basic_string<Traits>& basic_string<Traits>::operator=(
    const String& sStr) noexcept
{
    assign(sStr);
    return *this;
}

template<class Traits>
inline basic_string<Traits>& basic_string<Traits>::operator+=(
    value_type chSymbol) noexcept
{
    append(&chSymbol, 1);
    return *this;
}

template<class Traits>
inline basic_string<Traits>& basic_string<Traits>::operator+=(
    const_pointer pszSource) noexcept
{
    append(pszSource, Traits::length(pszSource));
    return *this;
}

template<class Traits>
inline basic_string<Traits>& basic_string<Traits>::operator+=(
    const basic_string& sStr) noexcept
{
    append(sStr.data(), sStr.size());
    return *this;
}

template<class Traits>
template<string_convertable String>
inline basic_string<Traits>& basic_string<Traits>::operator+=(
    const String& sStr) noexcept
{
    append(sStr.cbegin(), sStr.cend());
    return *this;
}

template<class Traits>
inline bool basic_string<Traits>::operator==(value_type chSymbol) const noexcept
{
    return size() == 1 && at(0) == chSymbol;
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
    return size() == sStr.size() && compare(sStr.data(), sStr.size()) == 0;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::operator==(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) == 0;
}

template<class Traits>
inline bool basic_string<Traits>::operator!=(value_type chSymbol) const noexcept
{
    return !operator==(chSymbol);
}

template<class Traits>
inline bool basic_string<Traits>::operator!=(
    const_pointer pszSource) const noexcept
{
    return !operator==(pszSource);
}

template<class Traits>
inline bool basic_string<Traits>::operator!=(
    const basic_string& sStr) const noexcept
{
    return !operator==(sStr);
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::operator!=(const String& sStr) const noexcept
{
    return !operator==(sStr);
}

template<class Traits>
inline bool basic_string<Traits>::operator<(value_type chSymbol) const noexcept
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
    return compare(sStr.data(), sStr.size()) < 0;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::operator<(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) < 0;
}

template<class Traits>
inline bool basic_string<Traits>::operator<=(value_type chSymbol) const noexcept
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
    return compare(sStr.data(), sStr.size()) <= 0;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::operator<=(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) <= 0;
}

template<class Traits>
inline bool basic_string<Traits>::operator>(value_type chSymbol) const noexcept
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
    return compare(sStr.data(), sStr.size()) > 0;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::operator>(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) > 0;
}

template<class Traits>
inline bool basic_string<Traits>::operator>=(value_type chSymbol) const noexcept
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
    return compare(sStr.data(), sStr.size()) >= 0;
}

template<class Traits>
template<string_convertable String>
inline bool basic_string<Traits>::operator>=(const String& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) >= 0;
}

template<class Traits>
inline typename basic_string<Traits>::reference basic_string<
    Traits>::operator[](size_type nSymbol) noexcept
{
    return at(nSymbol);
}

template<class Traits>
inline typename basic_string<Traits>::const_reference basic_string<
    Traits>::operator[](size_type nSymbol) const noexcept
{
    return at(nSymbol);
}

template<class Traits>
inline basic_string<Traits>::operator std::basic_string_view<
    typename basic_string<Traits>::value_type>(void) const noexcept
{
    return std::basic_string_view<value_type, std::char_traits<value_type>>(
        data(),
        size());
}

template<class Traits>
inline bool basic_string<Traits>::_resize(
    size_type          nSymbols,
    size_type          nAlign,
    string_resize_type eType) noexcept
{
    const bool bRet = m_Data.resize(nSymbols, nAlign, eType);

    if (bRet && eType == string_resize_type::common)
        at(nSymbols) = QX_CHAR_PREFIX(typename Traits::value_type, '\0');

    return bRet;
}

template<class Traits>
template<class Searcher>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::_trim_left(const Searcher& searcher) noexcept
{
    size_type nSymbols = 0;

    for (size_type i = 0; i < size(); ++i)
    {
        if (searcher(at(i)))
            ++nSymbols;
        else
            break;
    }

    erase(0, nSymbols);
    return nSymbols;
}

template<class Traits>
template<class Searcher>
inline typename basic_string<Traits>::size_type basic_string<
    Traits>::_trim_right(const Searcher& searcher) noexcept
{
    size_type nSymbols = 0;
    size_type nSize    = size();

    for (size_type i = nSize - 1; i != std::numeric_limits<size_type>::max();
         --i)
    {
        if (searcher(at(i)))
            ++nSymbols;
        else
            break;
    }

    erase(nSize - nSymbols, nSymbols);
    return nSymbols;
}

template<class Traits>
template<class Searcher>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_trim(
    const Searcher& searcher) noexcept
{
    const size_type nSize     = size();
    size_type       nStartPos = 0;
    size_type       nEndPos   = nSize;

    while (nStartPos < nSize && searcher(at(nStartPos)))
        ++nStartPos;

    while (nEndPos > nStartPos && searcher(at(nEndPos - 1)))
        --nEndPos;

    size_type nNewSize = nEndPos - nStartPos;

    std::memmove(data(), data() + nStartPos, nNewSize * sizeof(value_type));

    _resize(nNewSize, Traits::align());
    return nSize - nNewSize;
}

template<class Traits>
template<class Comparator>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_find(
    size_type         nBegin,
    size_type         nEnd,
    const Comparator& comparator) const noexcept
{
    if (nEnd == npos)
        nEnd = size();

    const_pointer pData        = data();
    const_pointer pCurrentChar = pData + nBegin;
    const_pointer pEnd         = pData + nEnd;

    while (pCurrentChar < pEnd)
    {
        if (comparator(pCurrentChar))
            return static_cast<size_type>(pCurrentChar - pData);
        else
            ++pCurrentChar;
    }

    return npos;
}

template<class Traits>
template<class Comparator>
inline typename basic_string<Traits>::size_type basic_string<Traits>::_rfind(
    size_type         nBegin,
    size_type         nEnd,
    const Comparator& comparator) const noexcept
{
    if (nBegin == npos)
        nBegin = size() - 1;

    const_pointer pData        = data();
    const_pointer pCurrentChar = pData + nBegin;
    const_pointer pEnd         = pData + nEnd;

    while (pCurrentChar >= pEnd)
    {
        if (comparator(pCurrentChar))
            return static_cast<size_type>(pCurrentChar - pData);
        else
            --pCurrentChar;
    }

    return npos;
}

template<class Traits>
template<class Incrementer, class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    _find_first_of(
        FwdIt              itBegin,
        FwdIt              itEnd,
        size_type          nBegin,
        const Incrementer& incrementer) const noexcept
{
    for (size_type i = nBegin; i < size(); ++i)
        for (FwdIt it = itBegin; it != itEnd; it = incrementer(it))
            if (*it == at(i))
                return i;

    return npos;
}

template<class Traits>
template<class Incrementer, class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    _find_last_of(
        FwdIt              itBegin,
        FwdIt              itEnd,
        size_type          nEnd,
        const Incrementer& incrementer) const noexcept
{
    for (size_type i = size() - 1; i != nEnd - 1; --i)
        for (FwdIt it = itBegin; it != itEnd; it = incrementer(it))
            if (*it == at(i))
                return i;

    return npos;
}

template<class Traits>
template<class Incrementer, class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    _find_first_not_of(
        FwdIt              itBegin,
        FwdIt              itEnd,
        size_type          nBegin,
        const Incrementer& incrementer) const noexcept
{
    for (size_type i = nBegin; i < size(); ++i)
    {
        bool bFoundOneOf = false;
        for (FwdIt it = itBegin; !bFoundOneOf && it != itEnd;
             it       = incrementer(it))
            bFoundOneOf |= *it == at(i);

        if (!bFoundOneOf)
            return i;
    }

    return npos;
}

template<class Traits>
template<class Incrementer, class FwdIt>
inline typename basic_string<Traits>::size_type basic_string<Traits>::
    _find_last_not_of(
        FwdIt              itBegin,
        FwdIt              itEnd,
        size_type          nEnd,
        const Incrementer& incrementer) const noexcept
{
    for (size_type i = size() - 1; i != nEnd - 1; --i)
    {
        bool bFoundOneOf = false;
        for (FwdIt it = itBegin; !bFoundOneOf && it != itEnd;
             it       = incrementer(it))
            bFoundOneOf |= *it == at(i);

        if (!bFoundOneOf)
            return i;
    }

    return npos;
}

template<class Traits>
basic_string<Traits> operator+(
    const basic_string<Traits>& lhs,
    const basic_string<Traits>& rhs) noexcept
{
    basic_string<Traits> str(lhs);
    str += rhs;
    return std::move(str);
}

template<class Traits>
basic_string<Traits> operator+(
    basic_string<Traits>&&      lhs,
    const basic_string<Traits>& rhs) noexcept
{
    basic_string<Traits> str(std::move(lhs));
    str += rhs;
    return str;
}

template<class Traits>
basic_string<Traits> operator+(
    const basic_string<Traits>&    lhs,
    typename Traits::const_pointer rhs) noexcept
{
    basic_string<Traits> str(lhs);
    str += rhs;
    return str;
}

template<class Traits>
basic_string<Traits> operator+(
    basic_string<Traits>&&         lhs,
    typename Traits::const_pointer rhs) noexcept
{
    basic_string<Traits> str(std::move(lhs));
    str += rhs;
    return str;
}

template<class Traits>
basic_string<Traits> operator+(
    typename Traits::const_pointer lhs,
    const basic_string<Traits>&    rhs) noexcept
{
    basic_string<Traits> str(lhs);
    str += rhs;
    return str;
}

template<class Traits>
basic_string<Traits> operator+(
    const basic_string<Traits>& lhs,
    typename Traits::value_type rhs) noexcept
{
    basic_string<Traits> str(lhs);
    str += rhs;
    return str;
}

template<class Traits>
basic_string<Traits> operator+(
    basic_string<Traits>&&      lhs,
    typename Traits::value_type rhs) noexcept
{
    basic_string<Traits> str(std::move(lhs));
    str += rhs;
    return str;
}

template<class Traits>
basic_string<Traits> operator+(
    typename Traits::value_type lhs,
    const basic_string<Traits>& rhs) noexcept
{
    basic_string<Traits> str(lhs);
    str += rhs;
    return str;
}

template<class Traits, string_convertable String>
basic_string<Traits> operator+(
    const basic_string<Traits>& lhs,
    const String&               rhs) noexcept
{
    basic_string<Traits> str(lhs);
    str += rhs;
    return str;
}

template<class Traits, string_convertable String>
basic_string<Traits> operator+(
    basic_string<Traits>&& lhs,
    const String&          rhs) noexcept
{
    basic_string<Traits> str(std::move(lhs));
    str += rhs;
    return str;
}

template<class Traits, string_convertable String>
basic_string<Traits> operator+(
    const String&               lhs,
    const basic_string<Traits>& rhs) noexcept
{
    basic_string<Traits> str(lhs);
    str += rhs;
    return str;
}

/**
    @brief  Get string size (excluding null terminator)
    @retval - string size (excluding null terminator)
**/
template<class Traits>
inline typename basic_string<Traits>::size_type basic_string<Traits>::size(
    void) const noexcept
{
    return m_Data.size();
}

/**
    @brief  Get c-string
    @retval - c-string
**/
template<class Traits>
inline typename basic_string<Traits>::pointer basic_string<Traits>::data(
    void) noexcept
{
    return m_Data.data();
}

/**
    @brief  Get char at the ind position
    @param  nIndex - char index
    @retval        - char value
**/
template<class Traits>
inline typename basic_string<Traits>::reference basic_string<Traits>::at(
    size_type nIndex) noexcept
{
    return data()[nIndex];
}

/**
    @brief Clear string
**/
template<class Traits>
inline void basic_string<Traits>::clear(void) noexcept
{
    assign(QX_STR_PREFIX(typename Traits::value_type, ""));
}

} // namespace qx



//------------------------------------ hash ------------------------------------

namespace std
{

template<class Traits>
struct hash<qx::basic_string<Traits>>
{
    size_t operator()(const qx::basic_string<Traits>& str) const noexcept
    {
        return Traits::hash_function(
            str.data(),
            Traits::hash_seed(),
            str.size());
    }
};

} // namespace std



//------------------------------------ swap ------------------------------------

namespace std
{

template<class Traits>
void swap(qx::basic_string<Traits>& lhs, qx::basic_string<Traits>& rhs) noexcept
{
    lhs.swap(rhs);
}

} // namespace std



//----------------------- istream / ostream overloading ----------------------

template<class Traits>
qx::detail::ostream<Traits>& operator<<(
    qx::detail::ostream<Traits>&    os,
    const qx::basic_string<Traits>& str)
{
    os << str.data();
    return os;
}

template<class Traits>
qx::detail::istream<Traits>& operator>>(
    qx::detail::istream<Traits>& is,
    qx::basic_string<Traits>&    str)
{
    typename qx::detail::istream<Traits>::iostate ret_bit =
        qx::detail::istream<Traits>::goodbit;
    auto try_push_back =
        [&str, &is, &ret_bit](
            typename qx::basic_string<Traits>::value_type ch) -> bool
    {
        typename qx::basic_string<Traits>::size_type nCurrentSize = str.size();
        if (str._resize(nCurrentSize + 1, Traits::align()))
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
