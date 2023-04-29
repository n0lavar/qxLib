/**

    @file      string.inl
    @author    Khrapov
    @date      4.09.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>::basic_string(size_type nSymbols, value_type chSymbol) noexcept
{
    assign(nSymbols, chSymbol);
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>::basic_string(const_pointer pszSource, size_type nSymbols) noexcept
{
    assign(pszSource, nSymbols);
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>::basic_string(const_pointer pszSource) noexcept
{
    assign(pszSource);
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>::basic_string(basic_string&& sAnother) noexcept
{
    assign(std::move(sAnother));
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>::basic_string(const basic_string& sAnother) noexcept
{
    assign(sAnother);
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline basic_string<char_t, traits_t>::basic_string(fwd_it_t itFirst, fwd_it_t itLast) noexcept
{
    assign(itFirst, itLast);
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline basic_string<char_t, traits_t>::basic_string(const string_t& sAnother) noexcept
{
    assign(sAnother);
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>::~basic_string() noexcept
{
    free();
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::assign(size_type nSymbols, value_type chSymbol) noexcept
{
    if (_resize(nSymbols))
        std::fill(begin(), end(), chSymbol);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::assign(const_pointer pszSource, size_type nSymbols) noexcept
{
    if (pszSource && _resize(nSymbols))
        std::memmove(data(), pszSource, nSymbols * sizeof(value_type));
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::assign(const_pointer pszSource) noexcept
{
    if (pszSource != data())
        assign(pszSource, traits_t::length(pszSource));
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::assign(basic_string&& sAnother) noexcept
{
    std::swap(m_Data, sAnother.m_Data);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::assign(const basic_string& sAnother) noexcept
{
    if (sAnother.data() != data())
        assign(sAnother.data());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline void basic_string<char_t, traits_t>::assign(fwd_it_t itFirst, fwd_it_t itLast) noexcept
{
    if (_resize(std::distance(itFirst, itLast)))
    {
        fwd_it_t itOther = itFirst;
        iterator itThis  = begin();

        while (itOther != itLast)
        {
            *itThis = *itOther;
            ++itThis;
            ++itOther;
        }
    }
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline void basic_string<char_t, traits_t>::assign(const string_t& sAnother) noexcept
{
    assign(sAnother.cbegin(), sAnother.cend());
}

template<class char_t, class traits_t>
void basic_string<char_t, traits_t>::sprintf(const_pointer pszFormat, ...) noexcept
{
    if (pszFormat)
    {
        va_list args;
        va_start(args, pszFormat);
        this->vsprintf(pszFormat, args);
        va_end(args);
    }
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::vsprintf(const_pointer pszFormat, va_list args) noexcept
{
    if (pszFormat)
    {
        va_list argsCopy;
        va_copy(argsCopy, args);
        int nLength = traits_t::vsnprintf(nullptr, 0, pszFormat, argsCopy);
        va_end(argsCopy);

        if (nLength > 0 && _resize(static_cast<size_type>(nLength)))
            traits_t::vsnprintf(data(), static_cast<size_type>(nLength) + 1, pszFormat, args);
    }
}

template<class char_t, class traits_t>
template<class... args_t>
inline basic_string<char_t, traits_t> basic_string<char_t, traits_t>::static_sprintf(
    const_pointer pszFormat,
    args_t... args) noexcept
{
    basic_string sTemp;
    sTemp.sprintf(pszFormat, args...);
    return sTemp;
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::append_sprintf(const_pointer pszFormat, ...) noexcept
{
    if (pszFormat)
    {
        va_list args;
        va_start(args, pszFormat);
        append_vsprintf(pszFormat, args);
        va_end(args);
    }
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::append_vsprintf(const_pointer pszFormat, va_list args) noexcept
{
    if (pszFormat)
    {
        va_list argsCopy;
        va_copy(argsCopy, args);
        int nLength = traits_t::vsnprintf(nullptr, 0, pszFormat, argsCopy);
        va_end(argsCopy);

        const size_type nSize = size();
        if (nLength > 0 && _resize(nSize + static_cast<size_type>(nLength)))
            traits_t::vsnprintf(data() + nSize, static_cast<size_type>(nLength) + 1, pszFormat, args);
    }
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::swap(basic_string& sOther) noexcept
{
    std::swap(m_Data, sOther.m_Data);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::reserve(
    size_type nCapacity) noexcept
{
    if (nCapacity > capacity())
        _resize(nCapacity, string_resize_type::reserve);

    return capacity();
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::shrink_to_fit() noexcept
{
    if (!m_Data.is_small() && capacity() > size())
        _resize(size(), string_resize_type::shrink_to_fit);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::free() noexcept
{
    m_Data.free();
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::string_view basic_string<char_t, traits_t>::substr(
    size_type nPos,
    size_type nSymbols) const noexcept
{
    return string_view(data() + nPos, nSymbols != npos ? nSymbols : size() - nPos);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::to_lower() noexcept
{
    for (value_type& ch : *this)
        ch = traits_t::to_lower(ch);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::to_upper() noexcept
{
    for (value_type& ch : *this)
        ch = traits_t::to_upper(ch);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::value_type basic_string<char_t, traits_t>::front(void) const noexcept
{
    return at(0);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::value_type basic_string<char_t, traits_t>::back(void) const noexcept
{
    return at(size() - 1);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::length(void) const noexcept
{
    return size();
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::const_pointer basic_string<char_t, traits_t>::c_str(void) const noexcept
{
    return data();
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::capacity(void) const noexcept
{
    return m_Data.capacity();
}

template<class char_t, class traits_t>
constexpr typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::max_size() noexcept
{
    return std::numeric_limits<size_type>::max() - 1 // npos reserved
           - 1;                                      // null terminator
}

template<class char_t, class traits_t>
template<class to_t>
inline std::optional<to_t> basic_string<char_t, traits_t>::to(const_pointer pszFormat) const noexcept
{
    std::optional<to_t> optResult = std::nullopt;

    if constexpr (
        std::is_trivial_v<to_t> && std::is_standard_layout_v<to_t> || std::is_pointer_v<to_t>
        || std::is_same_v<to_t, std::nullptr_t>)
    {
        if constexpr (std::is_same_v<to_t, std::nullptr_t>)
        {
            if (compare(QX_STR_PREFIX(typename traits_t::value_type, "nullptr")) == 0)
            {
                optResult = nullptr;
            }
        }
        else if constexpr (std::is_same_v<to_t, bool>)
        {
            if (compare(QX_STR_PREFIX(typename traits_t::value_type, "true")) == 0)
            {
                optResult = true;
            }
            else if (compare(QX_STR_PREFIX(typename traits_t::value_type, "false")) == 0)
            {
                optResult = false;
            }
        }
        else if (const auto pszSelectedFormat = pszFormat ? pszFormat : get_format_specifier<value_type, to_t>())
        {
            to_t      result;
            const int nConvertedArgs = traits_t::sscanf(data(), pszSelectedFormat, &result);

            if (nConvertedArgs == 1)
                optResult = result;
        }
    }
    else
    {
        to_t         result;
        sstream_type ss(data());
        ss >> result;
        optResult = result;
    }

    return optResult;
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::copy(
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

template<class char_t, class traits_t>
template<class from_t>
inline void basic_string<char_t, traits_t>::from(const from_t& data, const_pointer pszFormat) noexcept
{
    if constexpr (
        std::is_trivial_v<from_t> && std::is_standard_layout_v<from_t> || std::is_pointer_v<from_t>
        || std::is_same_v<from_t, std::nullptr_t>)
    {
        if (!pszFormat)
        {
            if constexpr (std::is_same_v<from_t, std::nullptr_t>)
            {
                pszFormat = QX_STR_PREFIX(typename traits_t::value_type, "nullptr");
            }
            else if constexpr (std::is_same_v<from_t, bool>)
            {
                pszFormat = data ? QX_STR_PREFIX(typename traits_t::value_type, "true")
                                 : QX_STR_PREFIX(typename traits_t::value_type, "false");
            }
            else
            {
                pszFormat = get_format_specifier<value_type, from_t>();
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

template<class char_t, class traits_t>
template<class from_t>
inline basic_string<char_t, traits_t> basic_string<char_t, traits_t>::static_from(
    const from_t& data,
    const_pointer pszFormat) noexcept
{
    basic_string sTemp;
    sTemp.from(data, pszFormat);
    return std::move(sTemp);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::append(value_type chSymbol) noexcept
{
    append(&chSymbol, 1);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::append(const_pointer pszStr, size_type nSymbols) noexcept
{
    if (pszStr)
    {
        const size_type nSize       = size();
        const size_type nSizeSource = nSymbols == npos ? traits_t::length(pszStr) : nSymbols;

        if (_resize(nSize + nSizeSource))
            std::memcpy(data() + nSize, pszStr, nSizeSource * sizeof(value_type));
    }
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::append(const basic_string& sStr) noexcept
{
    append(sStr.data(), sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline void basic_string<char_t, traits_t>::append(fwd_it_t itBegin, fwd_it_t itEnd) noexcept
{
    for (auto it = itBegin; it != itEnd; ++it)
        push_back(*it);
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline void basic_string<char_t, traits_t>::append(const string_t& sStr) noexcept
{
    append(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    size_type  nPos,
    value_type chSymbol) noexcept
{
    return insert(nPos, &chSymbol, 1);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    size_type     nPos,
    const_pointer pszWhat,
    size_type     nSymbols) noexcept
{
    if (pszWhat)
    {
        const size_type nSize       = size();
        const size_type nSizeSource = nSymbols == npos ? traits_t::length(pszWhat) : nSymbols;

        if (nSizeSource > 0 && _resize(nSize + nSizeSource))
        {
            std::memmove(data() + nPos + nSizeSource, data() + nPos, (nSize - nPos) * sizeof(value_type));
            std::memcpy(data() + nPos, pszWhat, nSizeSource * sizeof(value_type));
            return nPos + nSizeSource;
        }
    }

    return npos;
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    size_type nPos,
    fwd_it_t  itWhatBegin,
    fwd_it_t  itWhatEnd) noexcept
{
    if constexpr (is_random_access_iterator<fwd_it_t>)
    {
        return insert(nPos, itWhatBegin.operator->(), static_cast<size_type>(itWhatEnd - itWhatBegin));
    }
    else
    {
        size_type nWhatSize = 0;
        for (auto it = itWhatBegin; it != itWhatEnd; ++it)
            ++nWhatSize;

        size_type nStartSymbols = size();
        if (nWhatSize > 0 && _resize(nStartSymbols + nWhatSize))
        {
            std::memmove(data() + nPos + nWhatSize, data() + nPos, (nStartSymbols - nPos) * sizeof(value_type));

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

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    size_type           nPos,
    const basic_string& sWhat) noexcept
{
    return insert(nPos, sWhat.data(), sWhat.size());
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    size_type nPos,
    string_t  sWhat) noexcept
{
    return insert(static_cast<size_type>(nPos), sWhat.cbegin(), sWhat.cend());
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    const_iterator itPos,
    value_type     chSymbol) noexcept
{
    return insert(static_cast<size_type>(itPos - cbegin()), chSymbol);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    const_iterator itPos,
    const_pointer  pszWhat,
    size_type      nSymbols) noexcept
{
    return insert(static_cast<size_type>(itPos - cbegin()), pszWhat, nSymbols);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    const_iterator      itPos,
    const basic_string& sWhat) noexcept
{
    return insert(static_cast<size_type>(itPos - cbegin()), sWhat.data(), sWhat.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    const_iterator itPos,
    fwd_it_t       itWhatBegin,
    fwd_it_t       itWhatEnd) noexcept
{
    return insert(static_cast<size_type>(itPos - begin()), itWhatBegin, itWhatEnd);
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::insert(
    const_iterator itPos,
    string_t       sWhat) noexcept
{
    return insert(static_cast<size_type>(itPos - begin()), sWhat.cbegin(), sWhat.cend());
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::push_back(value_type chSymbol) noexcept
{
    insert(size(), &chSymbol, 1);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::push_front(value_type chSymbol) noexcept
{
    insert(0, &chSymbol, 1);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::erase(iterator itFirst, iterator itLast) noexcept
{
    if (const typename iterator::difference_type nCharsToErase = itLast - itFirst; nCharsToErase > 0)
    {
        const size_type nStartSize     = size();
        const size_type nSymbolsToCopy = itLast != end() ? traits_t::length(itLast.operator->()) : 0;

        if (nSymbolsToCopy > 0)
        {
            std::memmove(itFirst.operator->(), itLast.operator->(), nSymbolsToCopy * sizeof(value_type));
        }

        if (static_cast<typename iterator::difference_type>(nStartSize) >= nCharsToErase)
        {
            _resize(nStartSize - nCharsToErase);
        }
    }
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::erase(iterator itPos) noexcept
{
    erase(itPos, itPos + 1);
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::erase(size_type nPos) noexcept
{
    erase(iterator(this, nPos), iterator(this, nPos + 1));
}

template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::erase(size_type nPos, size_type nSymbols) noexcept
{
    erase(iterator(this, nPos), iterator(this, nPos + nSymbols));
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::value_type basic_string<char_t, traits_t>::pop_back(void) noexcept
{
    value_type chRet = back();
    erase(size() - 1);
    return chRet;
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::value_type basic_string<char_t, traits_t>::pop_front() noexcept
{
    value_type chRet = front();
    erase(0);
    return chRet;
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_left(void) noexcept
{
    return _trim_left(
        [](value_type ch)
        {
            return traits_t::is_space(ch);
        });
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_left(
    value_type chSymbol) noexcept
{
    return _trim_left(
        [chSymbol](value_type ch)
        {
            return ch == chSymbol;
        });
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_left(
    const_pointer pszStr) noexcept
{
    if (pszStr)
    {
        return _trim_left(
            [pszStr](value_type ch)
            {
                for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0'); ++j)
                {
                    if (pszStr[j] == ch)
                        return true;
                }

                return false;
            });
    }
    else
    {
        return 0;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_left(
    const_pointer pszStr,
    size_type     nStrSize) noexcept
{
    if (pszStr)
    {
        return _trim_left(
            [pszStr, nStrSize](value_type ch)
            {
                for (size_type j = 0; j < nStrSize; ++j)
                    if (pszStr[j] == ch)
                        return true;

                return false;
            });
    }
    else
    {
        return 0;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_left(
    const basic_string& sStr) noexcept
{
    return trim_left(sStr.data(), sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_left(
    fwd_it_t itBegin,
    fwd_it_t itEnd) noexcept
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

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_left(
    const string_t& sStr) noexcept
{
    return trim_left(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_right() noexcept
{
    return _trim_right(
        [](value_type ch)
        {
            return traits_t::is_space(ch);
        });
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_right(
    value_type chSymbol) noexcept
{
    return _trim_right(
        [chSymbol](value_type ch)
        {
            return ch == chSymbol;
        });
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_right(
    const_pointer pszStr) noexcept
{
    if (pszStr)
    {
        return _trim_right(
            [pszStr](value_type ch)
            {
                for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0'); ++j)
                {
                    if (pszStr[j] == ch)
                        return true;
                }

                return false;
            });
    }
    else
    {
        return 0;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_right(
    const_pointer pszStr,
    size_type     nStrSize) noexcept
{
    if (pszStr)
    {
        return _trim_right(
            [pszStr, nStrSize](value_type ch)
            {
                for (size_type j = 0; j < nStrSize; ++j)
                    if (pszStr[j] == ch)
                        return true;

                return false;
            });
    }
    else
    {
        return 0;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_right(
    const basic_string& sStr) noexcept
{
    return trim_right(sStr.data(), sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_right(
    fwd_it_t itBegin,
    fwd_it_t itEnd) noexcept
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

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim_right(
    const string_t& sStr) noexcept
{
    return trim_right(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim(void) noexcept
{
    return _trim(
        [](value_type ch)
        {
            return traits_t::is_space(ch);
        });
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim(
    value_type chSymbol) noexcept
{
    return _trim(
        [chSymbol](value_type ch)
        {
            return ch == chSymbol;
        });
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim(
    const_pointer pszStr) noexcept
{
    if (pszStr)
    {
        return _trim(
            [pszStr](value_type ch)
            {
                for (size_type j = 0; pszStr[j] != QX_CHAR_PREFIX(value_type, '\0'); ++j)
                {
                    if (pszStr[j] == ch)
                        return true;
                }

                return false;
            });
    }
    else
    {
        return 0;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim(
    const_pointer pszStr,
    size_type     nStrSize) noexcept
{
    if (pszStr)
    {
        return _trim(
            [pszStr, nStrSize](value_type ch)
            {
                for (size_type j = 0; j < nStrSize; ++j)
                    if (pszStr[j] == ch)
                        return true;

                return false;
            });
    }
    else
    {
        return 0;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim(
    const basic_string& sStr) noexcept
{
    return trim(sStr.data(), sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim(
    fwd_it_t itBegin,
    fwd_it_t itEnd) noexcept
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

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::trim(
    const string_t& sStr) noexcept
{
    return trim(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove(
    value_type chSymbol,
    size_type  nBegin,
    size_type  nEnd) noexcept
{
    size_type nPos = find(chSymbol, nBegin, nEnd);

    if (nPos != npos)
        erase(nPos, 1);

    return nPos;
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove(
    const_pointer pszStr,
    size_type     nBegin,
    size_type     nEnd,
    size_type     nStrSize) noexcept
{
    if (pszStr)
    {
        const size_type nLocalStrSize = nStrSize != npos ? nStrSize : traits_t::length(pszStr);
        const size_type nPos          = find(pszStr, nBegin, nLocalStrSize, nEnd);

        if (nPos != npos)
            erase(nPos, nLocalStrSize);

        return nPos;
    }
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove(
    const basic_string& sStr,
    size_type           nBegin,
    size_type           nEnd) noexcept
{
    const size_type nPos = find(sStr, nBegin, nEnd);

    if (nPos != npos)
        erase(nPos, sStr.size());

    return nPos;
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove(
    fwd_it_t  itBegin,
    fwd_it_t  itEnd,
    size_type nBegin,
    size_type nEnd) noexcept
{
    const size_type nPos = find(itBegin, itEnd, nBegin, nEnd);

    if (nPos != npos)
        erase(nPos, static_cast<size_type>(std::distance(itBegin, itEnd)));

    return nPos;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove(
    const string_t& sStr,
    size_type       nBegin,
    size_type       nEnd) noexcept
{
    return remove(sStr.cbegin(), sStr.cend(), nBegin, nEnd);
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::remove_prefix(value_type chSymbol) noexcept
{
    return remove(chSymbol, static_cast<size_type>(0), static_cast<size_type>(1)) != npos;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::remove_prefix(const_pointer pszStr, size_type nStrSize) noexcept
{
    return remove(pszStr, static_cast<size_type>(0), nStrSize, nStrSize) != npos;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::remove_prefix(const basic_string& sStr) noexcept
{
    return remove(sStr, static_cast<size_type>(0), sStr.size()) != npos;
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline bool basic_string<char_t, traits_t>::remove_prefix(fwd_it_t itBegin, fwd_it_t itEnd) noexcept
{
    return remove(itBegin, itEnd, static_cast<size_type>(0), static_cast<size_type>(std::distance(itBegin, itEnd)))
           != npos;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::remove_prefix(const string_t& sStr) noexcept
{
    return remove_prefix(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::remove_suffix(value_type chSymbol) noexcept
{
    const size_type nSize = size();
    return remove(chSymbol, nSize - 1, nSize) != npos;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::remove_suffix(const_pointer pszStr, size_type nStrSize) noexcept
{
    if (pszStr)
    {
        const size_type nSize         = size();
        const size_type nLocalStrSize = nStrSize != npos ? nStrSize : traits_t::length(pszStr);

        return remove(pszStr, nSize - nLocalStrSize, nSize, nLocalStrSize) != npos;
    }
    else
    {
        return false;
    }
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::remove_suffix(const basic_string& sStr) noexcept
{
    return remove_suffix(sStr.data(), sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline bool basic_string<char_t, traits_t>::remove_suffix(fwd_it_t itBegin, fwd_it_t itEnd) noexcept
{
    const size_type nSize = size();
    return remove(itBegin, itEnd, nSize - static_cast<size_type>(std::distance(itBegin, itEnd)), nSize) != npos;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::remove_suffix(const string_t& sStr) noexcept
{
    return remove_suffix(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove_all(
    value_type chSymbol,
    size_type  nBegin,
    size_type  nEnd) noexcept
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

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove_all(
    const_pointer pszStr,
    size_type     nBegin,
    size_type     nEnd,
    size_type     nStrSize) noexcept
{
    if (pszStr)
    {
        size_type nOccurrences       = 0;
        size_type nLastOccurrencePos = nBegin;

        do
        {
            ++nOccurrences;
            nLastOccurrencePos = remove(pszStr, nLastOccurrencePos, nEnd, nStrSize);
        } while (nLastOccurrencePos != npos);

        return nOccurrences - 1;
    }
    else
    {
        return 0;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove_all(
    const basic_string& sStr,
    size_type           nBegin,
    size_type           nEnd) noexcept
{
    return remove_all(sStr.data(), nBegin, nEnd, sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove_all(
    fwd_it_t  itFirst,
    fwd_it_t  itLast,
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

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::remove_all(
    const string_t& sStr,
    size_type       nBegin,
    size_type       nEnd) noexcept
{
    return remove_all(sStr.cbegin(), sStr.cend(), nBegin, nEnd);
}

template<class char_t, class traits_t>
template<class find_string_t, class replace_string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::replace(
    const find_string_t&    sFind,
    const replace_string_t& sReplace,
    size_type               nBegin,
    size_type               nEnd) noexcept
{
    auto get_size = []<class T>(const T& val) -> size_type
    {
        if constexpr (std::is_same_v<T, value_type>)
        {
            return 1;
        }
        else if constexpr (std::is_same_v<T, const_pointer>)
        {
            return traits_t::length(val);
        }
        else if constexpr (string_convertable<T>)
        {
            return val.size();
        }
        else
        {
            QX_STATIC_ASSERT_NO_INSTANTIATION("Unexpected type");
            return 0;
        }
    };

    auto get_data = []<class T>(const T& val) -> const_pointer
    {
        if constexpr (std::is_same_v<T, value_type>)
        {
            return &val;
        }
        else if constexpr (std::is_same_v<T, const_pointer>)
        {
            return val;
        }
        else if constexpr (string_convertable<T>)
        {
            return val.data();
        }
        else
        {
            QX_STATIC_ASSERT_NO_INSTANTIATION("Unexpected type");
            return nullptr;
        }
    };

    if (size_type nPos = find(sFind, nBegin, nEnd); nPos != npos)
    {
        const size_type nStartSize   = size();
        const size_type nFindSize    = get_size(sFind);
        const size_type nReplaceSize = get_size(sReplace);
        const size_type nNewSize     = nStartSize - nFindSize + nReplaceSize;

        _resize(nNewSize, string_resize_type::reserve);

        std::memmove(
            data() + nPos + nReplaceSize,
            data() + nPos + nFindSize,
            (nStartSize - nPos - nFindSize) * sizeof(value_type));

        std::memcpy(data() + nPos, get_data(sReplace), nReplaceSize * sizeof(value_type));

        _resize(nNewSize);

        return nPos + nReplaceSize;
    }
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
template<class find_string_t, class replace_string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::replace_all(
    const find_string_t&    sFind,
    const replace_string_t& sReplace,
    size_type               nBegin,
    size_type               nEnd) noexcept
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

template<class char_t, class traits_t>
inline int basic_string<char_t, traits_t>::compare(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1);
}

template<class char_t, class traits_t>
inline int basic_string<char_t, traits_t>::compare(const_pointer pszStr) const noexcept
{
    return traits_t::compare(data(), pszStr);
}

template<class char_t, class traits_t>
inline int basic_string<char_t, traits_t>::compare(const_pointer pStr, size_type nSymbols) const noexcept
{
    return traits_t::compare_n(data(), pStr, nSymbols);
}

template<class char_t, class traits_t>
inline int basic_string<char_t, traits_t>::compare(const basic_string& sStr) const noexcept
{
    return compare(sStr.data(), sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline int basic_string<char_t, traits_t>::compare(fwd_it_t itBegin, fwd_it_t itEnd) const noexcept
{
    return iter_strcmp(cbegin(), cend(), itBegin, itEnd);
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline int basic_string<char_t, traits_t>::compare(const string_t& sStr) const noexcept
{
    return compare(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find(
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

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nWhatSize,
    size_type     nEnd) const noexcept
{
    if (pszWhat)
    {
        const size_type nLocalWhatSize = nWhatSize != npos ? nWhatSize : traits_t::length(pszWhat);

        return _find(
            nBegin,
            nEnd,
            [pszWhat, nLocalWhatSize](const_pointer pCurrentChar)
            {
                return !traits_t::compare_n(pszWhat, pCurrentChar, nLocalWhatSize);
            });
    }
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find(
    const basic_string& sWhat,
    size_type           nBegin,
    size_type           nEnd) const noexcept
{
    return find(sWhat.data(), nBegin, sWhat.size(), nEnd);
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find(
    fwd_it_t  itWhatBegin,
    fwd_it_t  itWhatEnd,
    size_type nBegin,
    size_type nEnd) const noexcept
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

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find(
    string_t  sWhat,
    size_type nBegin,
    size_type nEnd) const noexcept
{
    return find(sWhat.cbegin(), sWhat.cend(), nBegin, nEnd);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::rfind(
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

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::rfind(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nWhatSize,
    size_type     nEnd) const noexcept
{
    if (pszWhat)
    {
        const size_type nLocalWhatSize = nWhatSize != npos ? nWhatSize : traits_t::length(pszWhat);

        return _rfind(
            nBegin,
            nEnd,
            [pszWhat, nLocalWhatSize](const_pointer pCurrentChar)
            {
                return !traits_t::compare_n(pszWhat, pCurrentChar, nLocalWhatSize);
            });
    }
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::rfind(
    const basic_string& sWhat,
    size_type           nBegin,
    size_type           nEnd) const noexcept
{
    return rfind(sWhat.data(), nBegin, sWhat.size(), nEnd);
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::rfind(
    fwd_it_t  itWhatBegin,
    fwd_it_t  itWhatEnd,
    size_type nBegin,
    size_type nEnd) const noexcept
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

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::rfind(
    string_t  sWhat,
    size_type nBegin,
    size_type nEnd) const noexcept
{
    return rfind(sWhat.cbegin(), sWhat.cend(), nBegin, nEnd);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_of(
    value_type chSymbol,
    size_type  nBegin) const noexcept
{
    return find(chSymbol, nBegin);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_of(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nWhatSize) const noexcept
{
    if (pszWhat)
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
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_of(
    const_pointer pszWhat,
    size_type     nBegin) const noexcept
{
    if (pszWhat)
    {
        return _find_first_of(
            pszWhat,
            static_cast<const_pointer>(nullptr),
            nBegin,
            [](const_pointer pChar)
            {
                return *(pChar + 1) != QX_CHAR_PREFIX(value_type, '\0') ? pChar + 1 : nullptr;
            });
    }
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_of(
    const basic_string& sWhat,
    size_type           nBegin) const noexcept
{
    return find_first_of(sWhat.data(), nBegin, sWhat.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_of(
    fwd_it_t  itWhatBegin,
    fwd_it_t  itWhatEnd,
    size_type nBegin) const noexcept
{
    return _find_first_of(
        itWhatBegin,
        itWhatEnd,
        nBegin,
        [](fwd_it_t itChar)
        {
            return ++itChar;
        });
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_of(
    string_t  sWhat,
    size_type nBegin) const noexcept
{
    return find_first_of(sWhat.cbegin(), sWhat.cend(), nBegin);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_of(
    value_type chSymbol,
    size_type  nEnd) const noexcept
{
    return rfind(chSymbol, npos, nEnd);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_of(
    const_pointer pszWhat,
    size_type     nEnd,
    size_type     nWhatSize) const noexcept
{
    if (pszWhat)
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
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_of(
    const_pointer pszWhat,
    size_type     nEnd) const noexcept
{
    if (pszWhat)
    {
        return _find_last_of(
            pszWhat,
            static_cast<const_pointer>(nullptr),
            nEnd,
            [](const_pointer pChar)
            {
                return *(pChar + 1) != QX_CHAR_PREFIX(value_type, '\0') ? pChar + 1 : nullptr;
            });
    }
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_of(
    const basic_string& sWhat,
    size_type           nEnd) const noexcept
{
    return find_last_of(sWhat.data(), nEnd, sWhat.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_of(
    fwd_it_t  itWhatBegin,
    fwd_it_t  itWhatEnd,
    size_type nEnd) const noexcept
{
    return _find_last_of(
        itWhatBegin,
        itWhatEnd,
        nEnd,
        [](fwd_it_t itChar)
        {
            return ++itChar;
        });
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_of(
    string_t  sWhat,
    size_type nEnd) const noexcept
{
    return find_last_of(sWhat.cbegin(), sWhat.cend(), nEnd);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_not_of(
    value_type chSymbol,
    size_type  nBegin) const noexcept
{
    return _find(
        nBegin,
        npos,
        [chSymbol](const_pointer pCurrentChar)
        {
            return *pCurrentChar != chSymbol;
        });
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_not_of(
    const_pointer pszWhat,
    size_type     nBegin,
    size_type     nWhatSize) const noexcept
{
    if (pszWhat)
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
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_not_of(
    const_pointer pszWhat,
    size_type     nBegin) const noexcept
{
    if (pszWhat)
    {
        return _find_first_not_of(
            pszWhat,
            static_cast<const_pointer>(nullptr),
            nBegin,
            [](const_pointer pChar)
            {
                return *(pChar + 1) != QX_CHAR_PREFIX(value_type, '\0') ? pChar + 1 : nullptr;
            });
    }
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_not_of(
    const basic_string& sWhat,
    size_type           nBegin) const noexcept
{
    return find_first_not_of(sWhat.data(), nBegin, sWhat.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_not_of(
    fwd_it_t  itWhatBegin,
    fwd_it_t  itWhatEnd,
    size_type nBegin) const noexcept
{
    return _find_first_not_of(
        itWhatBegin,
        itWhatEnd,
        nBegin,
        [](fwd_it_t itChar)
        {
            return ++itChar;
        });
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_first_not_of(
    string_t  sWhat,
    size_type nBegin) const noexcept
{
    return find_first_not_of(sWhat.cbegin(), sWhat.cend(), nBegin);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_not_of(
    value_type chSymbol,
    size_type  nEnd) const noexcept
{
    return _rfind(
        npos,
        nEnd,
        [chSymbol](const_pointer pCurrentChar)
        {
            return *pCurrentChar != chSymbol;
        });
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_not_of(
    const_pointer pszWhat,
    size_type     nEnd,
    size_type     nWhatSize) const noexcept
{
    if (pszWhat)
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
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_not_of(
    const_pointer pszWhat,
    size_type     nEnd) const noexcept
{
    if (pszWhat)
    {
        return _find_last_not_of(
            pszWhat,
            static_cast<const_pointer>(nullptr),
            nEnd,
            [](const_pointer pChar)
            {
                return *(pChar + 1) != QX_CHAR_PREFIX(value_type, '\0') ? pChar + 1 : nullptr;
            });
    }
    else
    {
        return npos;
    }
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_not_of(
    const basic_string& sWhat,
    size_type           nEnd) const noexcept
{
    return find_last_not_of(sWhat.data(), nEnd, sWhat.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_not_of(
    fwd_it_t  itWhatBegin,
    fwd_it_t  itWhatEnd,
    size_type nEnd) const noexcept
{
    return _find_last_not_of(
        itWhatBegin,
        itWhatEnd,
        nEnd,
        [](fwd_it_t itChar)
        {
            return ++itChar;
        });
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::find_last_not_of(
    string_t  sWhat,
    size_type nEnd) const noexcept
{
    return find_last_not_of(sWhat.cbegin(), sWhat.cend(), nEnd);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::views basic_string<char_t, traits_t>::split(
    const value_type chSeparator) const noexcept
{
    views tokens;

    size_type nStart = 0;
    size_type nEnd   = 0;
    while ((nEnd = find(chSeparator, nStart)) != npos)
    {
        tokens.emplace_back(substr(nStart, nEnd - nStart));
        nStart = nEnd;
        while (traits_t::compare_n(data() + nStart, &chSeparator, 1) == 0)
            ++nStart;
    }

    if (nStart != size())
        tokens.emplace_back(substr(nStart));

    return std::move(tokens);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::views basic_string<char_t, traits_t>::split(
    const_pointer pszSeparator,
    size_type     nSepLen) const noexcept
{
    views tokens;

    if (!pszSeparator)
        return tokens;

    if (nSepLen == npos)
        nSepLen = traits_t::length(pszSeparator);

    size_type nStart = 0;
    size_type nEnd   = 0;
    while ((nEnd = find(pszSeparator, nStart, nSepLen, npos)) != npos)
    {
        tokens.emplace_back(substr(nStart, nEnd - nStart));
        nStart = nEnd;
        while (traits_t::compare_n(data() + nStart, pszSeparator, nSepLen) == 0)
            nStart += nSepLen;
    }

    if (nStart != size())
        tokens.emplace_back(substr(nStart));

    return tokens;
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::views basic_string<char_t, traits_t>::split(
    const basic_string& sSeparator) const noexcept
{
    return split(sSeparator.data(), sSeparator.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline typename basic_string<char_t, traits_t>::views basic_string<char_t, traits_t>::split(
    fwd_it_t itSepFirst,
    fwd_it_t itSepLast) const noexcept
{
    views tokens;

    const size_type nSepLen = static_cast<size_type>(std::distance(itSepFirst, itSepLast));

    size_type nStart = 0;
    size_type nEnd   = 0;
    while ((nEnd = find(itSepFirst, itSepLast, nStart)) != npos)
    {
        tokens.emplace_back(substr(nStart, nEnd - nStart));
        nStart = nEnd + nSepLen;
    }
    tokens.emplace_back(substr(nStart));

    return tokens;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline typename basic_string<char_t, traits_t>::views basic_string<char_t, traits_t>::split(
    const string_t& sSeparator) const noexcept
{
    return split(sSeparator.cbegin(), sSeparator.cend());
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::starts_with(value_type chSymbol) const noexcept
{
    if (!empty())
        return at(0) == chSymbol;
    else
        return false;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::starts_with(const_pointer pszStr, size_type nStrSize) const noexcept
{
    if (pszStr)
    {
        if (size_type nThisSize = size(); nThisSize > 0)
        {
            if (nStrSize == npos)
                nStrSize = traits_t::length(pszStr);

            if (nStrSize <= nThisSize)
                return traits_t::compare_n(data(), pszStr, nStrSize) == 0;
        }
    }

    return false;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::starts_with(const basic_string& sStr) const noexcept
{
    return starts_with(sStr.data(), sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline bool basic_string<char_t, traits_t>::starts_with(fwd_it_t itBegin, fwd_it_t itEnd) const noexcept
{
    auto nStrSize = std::distance(itBegin, itEnd);
    return iter_strcmp(cbegin(), cbegin() + static_cast<size_type>(nStrSize), itBegin, itEnd) == 0;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::starts_with(const string_t& sStr) const noexcept
{
    return starts_with(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::ends_with(value_type chSymbol) const noexcept
{
    const size_type nSize = size();
    if (nSize > 0)
        return at(nSize - 1) == chSymbol;
    else
        return false;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::ends_with(const_pointer pszStr, size_type nStrSize) const noexcept
{
    if (pszStr)
    {
        if (size_type nThisSize = size(); nThisSize > 0)
        {
            if (nStrSize == npos)
                nStrSize = traits_t::length(pszStr);

            if (nStrSize <= nThisSize)
                return traits_t::compare_n(data() + nThisSize - nStrSize, pszStr, nStrSize) == 0;
        }
    }

    return false;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::ends_with(const basic_string& sStr) const noexcept
{
    return ends_with(sStr.data(), sStr.size());
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline bool basic_string<char_t, traits_t>::ends_with(fwd_it_t itBegin, fwd_it_t itEnd) const noexcept
{
    return iter_strcmp(cend() - static_cast<size_type>(std::distance(itBegin, itEnd)), cend(), itBegin, itEnd) == 0;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::ends_with(const string_t& sStr) const noexcept
{
    return ends_with(sStr.cbegin(), sStr.cend());
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::contains(value_type chSymbol) const noexcept
{
    return find(chSymbol) != npos;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::contains(const_pointer pszStr, size_type nStrSize) const noexcept
{
    return find(pszStr, 0, nStrSize) != npos;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::contains(const basic_string& sStr) const noexcept
{
    return find(sStr) != npos;
}

template<class char_t, class traits_t>
template<class fwd_it_t>
inline bool basic_string<char_t, traits_t>::contains(fwd_it_t itBegin, fwd_it_t itEnd) const noexcept
{
    return find(itBegin, itEnd) != npos;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::contains(const string_t& sStr) const noexcept
{
    return find(sStr) != npos;
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>& basic_string<char_t, traits_t>::operator=(const_pointer pszSource) noexcept
{
    assign(pszSource);
    return *this;
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>& basic_string<char_t, traits_t>::operator=(basic_string&& sStr) noexcept
{
    assign(std::move(sStr));
    return *this;
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>& basic_string<char_t, traits_t>::operator=(const basic_string& sStr) noexcept
{
    assign(sStr);
    return *this;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline basic_string<char_t, traits_t>& basic_string<char_t, traits_t>::operator=(const string_t& sStr) noexcept
{
    assign(sStr);
    return *this;
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>& basic_string<char_t, traits_t>::operator+=(value_type chSymbol) noexcept
{
    append(&chSymbol, 1);
    return *this;
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>& basic_string<char_t, traits_t>::operator+=(const_pointer pszSource) noexcept
{
    append(pszSource, traits_t::length(pszSource));
    return *this;
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>& basic_string<char_t, traits_t>::operator+=(const basic_string& sStr) noexcept
{
    append(sStr.data(), sStr.size());
    return *this;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline basic_string<char_t, traits_t>& basic_string<char_t, traits_t>::operator+=(const string_t& sStr) noexcept
{
    append(sStr.cbegin(), sStr.cend());
    return *this;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator==(value_type chSymbol) const noexcept
{
    return size() == 1 && at(0) == chSymbol;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator==(const_pointer pszSource) const noexcept
{
    return compare(pszSource) == 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator==(const basic_string& sStr) const noexcept
{
    return size() == sStr.size() && compare(sStr.data(), sStr.size()) == 0;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::operator==(const string_t& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) == 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator!=(value_type chSymbol) const noexcept
{
    return !operator==(chSymbol);
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator!=(const_pointer pszSource) const noexcept
{
    return !operator==(pszSource);
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator!=(const basic_string& sStr) const noexcept
{
    return !operator==(sStr);
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::operator!=(const string_t& sStr) const noexcept
{
    return !operator==(sStr);
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator<(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) < 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator<(const_pointer pszSource) const noexcept
{
    return compare(pszSource) < 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator<(const basic_string& sStr) const noexcept
{
    return compare(sStr.data(), sStr.size()) < 0;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::operator<(const string_t& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) < 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator<=(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) <= 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator<=(const_pointer pszSource) const noexcept
{
    return compare(pszSource) <= 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator<=(const basic_string& sStr) const noexcept
{
    return compare(sStr.data(), sStr.size()) <= 0;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::operator<=(const string_t& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) <= 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator>(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) > 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator>(const_pointer pszSource) const noexcept
{
    return compare(pszSource) > 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator>(const basic_string& sStr) const noexcept
{
    return compare(sStr.data(), sStr.size()) > 0;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::operator>(const string_t& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) > 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator>=(value_type chSymbol) const noexcept
{
    return compare(&chSymbol, 1) >= 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator>=(const_pointer pszSource) const noexcept
{
    return compare(pszSource) >= 0;
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::operator>=(const basic_string& sStr) const noexcept
{
    return compare(sStr.data(), sStr.size()) >= 0;
}

template<class char_t, class traits_t>
template<string_convertable string_t>
inline bool basic_string<char_t, traits_t>::operator>=(const string_t& sStr) const noexcept
{
    return iter_strcmp(cbegin(), cend(), sStr.cbegin(), sStr.cend()) >= 0;
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::reference basic_string<char_t, traits_t>::operator[](
    size_type nSymbol) noexcept
{
    return at(nSymbol);
}

template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::const_reference basic_string<char_t, traits_t>::operator[](
    size_type nSymbol) const noexcept
{
    return at(nSymbol);
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>::operator std::basic_string_view<
    typename basic_string<char_t, traits_t>::value_type>() const noexcept
{
    return std::basic_string_view<value_type, std::char_traits<value_type>>(data(), size());
}

template<class char_t, class traits_t>
inline basic_string<char_t, traits_t>::operator bool() const noexcept
{
    return !empty();
}

template<class char_t, class traits_t>
inline bool basic_string<char_t, traits_t>::_resize(size_type nSymbols, string_resize_type eType) noexcept
{
    const bool bRet =
        m_Data.resize(nSymbols, eType == string_resize_type::shrink_to_fit ? 0 : traits_t::align(), eType);

    if (bRet && eType == string_resize_type::common)
        at(nSymbols) = QX_CHAR_PREFIX(typename traits_t::value_type, '\0');

    return bRet;
}

template<class char_t, class traits_t>
template<class searcher_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_trim_left(
    const searcher_t& searcher) noexcept
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

template<class char_t, class traits_t>
template<class searcher_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_trim_right(
    const searcher_t& searcher) noexcept
{
    size_type nSymbols = 0;
    size_type nSize    = size();

    for (size_type i = nSize - 1; i != std::numeric_limits<size_type>::max(); --i)
    {
        if (searcher(at(i)))
            ++nSymbols;
        else
            break;
    }

    erase(nSize - nSymbols, nSymbols);
    return nSymbols;
}

template<class char_t, class traits_t>
template<class searcher_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_trim(
    const searcher_t& searcher) noexcept
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

    _resize(nNewSize);
    return nSize - nNewSize;
}

template<class char_t, class traits_t>
template<class comparator_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_find(
    size_type           nBegin,
    size_type           nEnd,
    const comparator_t& comparator) const noexcept
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

template<class char_t, class traits_t>
template<class comparator_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_rfind(
    size_type           nBegin,
    size_type           nEnd,
    const comparator_t& comparator) const noexcept
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

template<class char_t, class traits_t>
template<class incrementer_t, class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_find_first_of(
    fwd_it_t             itBegin,
    fwd_it_t             itEnd,
    size_type            nBegin,
    const incrementer_t& incrementer) const noexcept
{
    for (size_type i = nBegin; i < size(); ++i)
        for (fwd_it_t it = itBegin; it != itEnd; it = incrementer(it))
            if (*it == at(i))
                return i;

    return npos;
}

template<class char_t, class traits_t>
template<class incrementer_t, class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_find_last_of(
    fwd_it_t             itBegin,
    fwd_it_t             itEnd,
    size_type            nEnd,
    const incrementer_t& incrementer) const noexcept
{
    for (size_type i = size() - 1; i != nEnd - 1; --i)
        for (fwd_it_t it = itBegin; it != itEnd; it = incrementer(it))
            if (*it == at(i))
                return i;

    return npos;
}

template<class char_t, class traits_t>
template<class incrementer_t, class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_find_first_not_of(
    fwd_it_t             itBegin,
    fwd_it_t             itEnd,
    size_type            nBegin,
    const incrementer_t& incrementer) const noexcept
{
    for (size_type i = nBegin; i < size(); ++i)
    {
        bool bFoundOneOf = false;
        for (fwd_it_t it = itBegin; !bFoundOneOf && it != itEnd; it = incrementer(it))
            bFoundOneOf |= *it == at(i);

        if (!bFoundOneOf)
            return i;
    }

    return npos;
}

template<class char_t, class traits_t>
template<class incrementer_t, class fwd_it_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::_find_last_not_of(
    fwd_it_t             itBegin,
    fwd_it_t             itEnd,
    size_type            nEnd,
    const incrementer_t& incrementer) const noexcept
{
    for (size_type i = size() - 1; i != nEnd - 1; --i)
    {
        bool bFoundOneOf = false;
        for (fwd_it_t it = itBegin; !bFoundOneOf && it != itEnd; it = incrementer(it))
            bFoundOneOf |= *it == at(i);

        if (!bFoundOneOf)
            return i;
    }

    return npos;
}

template<class char_t, class traits_t>
basic_string<char_t, traits_t> operator+(
    const basic_string<char_t, traits_t>& lhs,
    const basic_string<char_t, traits_t>& rhs) noexcept
{
    basic_string<char_t, traits_t> str(lhs);
    str += rhs;
    return str;
}

template<class char_t, class traits_t>
basic_string<char_t, traits_t> operator+(
    basic_string<char_t, traits_t>&&      lhs,
    const basic_string<char_t, traits_t>& rhs) noexcept
{
    basic_string<char_t, traits_t> str(std::move(lhs));
    str += rhs;
    return str;
}

template<class char_t, class traits_t>
basic_string<char_t, traits_t> operator+(
    const basic_string<char_t, traits_t>& lhs,
    typename traits_t::const_pointer      rhs) noexcept
{
    basic_string<char_t, traits_t> str(lhs);
    str += rhs;
    return str;
}

template<class char_t, class traits_t>
basic_string<char_t, traits_t> operator+(
    basic_string<char_t, traits_t>&& lhs,
    typename traits_t::const_pointer rhs) noexcept
{
    basic_string<char_t, traits_t> str(std::move(lhs));
    str += rhs;
    return str;
}

template<class char_t, class traits_t>
basic_string<char_t, traits_t> operator+(
    typename traits_t::const_pointer      lhs,
    const basic_string<char_t, traits_t>& rhs) noexcept
{
    basic_string<char_t, traits_t> str(lhs);
    str += rhs;
    return str;
}

template<class char_t, class traits_t>
basic_string<char_t, traits_t> operator+(
    const basic_string<char_t, traits_t>& lhs,
    typename traits_t::value_type         rhs) noexcept
{
    basic_string<char_t, traits_t> str(lhs);
    str += rhs;
    return str;
}

template<class char_t, class traits_t>
basic_string<char_t, traits_t> operator+(
    basic_string<char_t, traits_t>&& lhs,
    typename traits_t::value_type    rhs) noexcept
{
    basic_string<char_t, traits_t> str(std::move(lhs));
    str += rhs;
    return str;
}

template<class char_t, class traits_t>
basic_string<char_t, traits_t> operator+(
    typename traits_t::value_type         lhs,
    const basic_string<char_t, traits_t>& rhs) noexcept
{
    basic_string<char_t, traits_t> str(&lhs, 1);
    str += rhs;
    return str;
}

template<class char_t, class traits_t, string_convertable string_t>
basic_string<char_t, traits_t> operator+(const basic_string<char_t, traits_t>& lhs, const string_t& rhs) noexcept
{
    basic_string<char_t, traits_t> str(lhs);
    str += rhs;
    return str;
}

template<class char_t, class traits_t, string_convertable string_t>
basic_string<char_t, traits_t> operator+(basic_string<char_t, traits_t>&& lhs, const string_t& rhs) noexcept
{
    basic_string<char_t, traits_t> str(std::move(lhs));
    str += rhs;
    return str;
}

template<class char_t, class traits_t, string_convertable string_t>
basic_string<char_t, traits_t> operator+(const string_t& lhs, const basic_string<char_t, traits_t>& rhs) noexcept
{
    basic_string<char_t, traits_t> str(lhs);
    str += rhs;
    return str;
}

/**
    @brief  Get string size (excluding null terminator)
    @retval - string size (excluding null terminator)
**/
template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::size_type basic_string<char_t, traits_t>::size(void) const noexcept
{
    return m_Data.size();
}

/**
    @brief  Get c-string
    @retval - c-string
**/
template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::pointer basic_string<char_t, traits_t>::data(void) noexcept
{
    return m_Data.data();
}

/**
    @brief  Get char at the ind position
    @param  nIndex - char index
    @retval        - char value
**/
template<class char_t, class traits_t>
inline typename basic_string<char_t, traits_t>::reference basic_string<char_t, traits_t>::at(size_type nIndex) noexcept
{
    return data()[nIndex];
}

/**
    @brief Clear string
**/
template<class char_t, class traits_t>
inline void basic_string<char_t, traits_t>::clear() noexcept
{
    assign(QX_STR_PREFIX(typename traits_t::value_type, ""));
}

} // namespace qx



//------------------------------------ hash ------------------------------------

namespace std
{

template<class char_t, class traits_t>
struct hash<qx::basic_string<char_t, traits_t>>
{
    size_t operator()(const qx::basic_string<char_t, traits_t>& str) const noexcept
    {
        return traits_t::hash_function(str.data(), traits_t::hash_seed(), str.size());
    }
};

} // namespace std



//------------------------------------ swap ------------------------------------

namespace std //-V1061
{

template<class char_t, class traits_t>
void swap(qx::basic_string<char_t, traits_t>& lhs, qx::basic_string<char_t, traits_t>& rhs) noexcept
{
    lhs.swap(rhs);
}

} // namespace std



//----------------------- istream / ostream overloading ----------------------

template<class char_t, class traits_t>
qx::detail::ostream<char_t>& operator<<(qx::detail::ostream<char_t>& os, const qx::basic_string<char_t, traits_t>& str)
{
    os << str.data();
    return os;
}

template<class char_t, class traits_t>
qx::detail::istream<char_t>& operator>>(qx::detail::istream<char_t>& is, qx::basic_string<char_t, traits_t>& str)
{
    typename qx::detail::istream<traits_t>::iostate ret_bit = qx::detail::istream<traits_t>::goodbit;

    auto try_push_back = [&str, &is, &ret_bit](char_t ch) -> bool
    {
        typename traits_t::size_type nCurrentSize = str.size();
        if (str._resize(nCurrentSize + 1))
        {
            str[nCurrentSize] = ch;
            return true;
        }
        else
        {
            is.unget();
            ret_bit |= qx::detail::istream<traits_t>::failbit;
            return false;
        }
    };

    str.clear();
    char_t ch;

    // skip all space symbols and add first symbol is any
    while (is.get(ch))
    {
        if (!traits_t::is_space(ch))
        {
            try_push_back(ch);
            break;
        }
    }

    // add other symbols until space symbol
    while (is.get(ch))
    {
        if (!traits_t::is_space(ch))
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
