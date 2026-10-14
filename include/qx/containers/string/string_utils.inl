/**

    @file      string_utils.inl
    @author    Khrapov
    @date      14.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

template<class value_t>
constexpr size_t djb2a_hash(const value_t* pszStr, size_t nSeed, size_t nLen)
{
    size_t nHash = nSeed;

    for (size_t i = 0; i < nLen; ++i)
        nHash = nHash * 33 ^ pszStr[i];

    return nHash;
}

template<class value_t>
constexpr size_t djb2a_hash(const value_t* pszStr, size_t nSeed)
{
    size_t nHash = nSeed;

    for (size_t i = 0; pszStr[i]; ++i)
        nHash = nHash * 33 ^ pszStr[i];

    return nHash;
}

template<class value_t>
constexpr size_t murmur_32_hash(const value_t* pStr, size_t nSeed, size_t nLen) noexcept
{
    size_t nHash = nSeed;

    if (nLen > 3)
    {
        size_t i = nLen >> 2;
        do
        {
            size_t k = 0;

            // constexpr version of std::memcpy(&k, pszStr, sizeof(u32));
            static_assert(
                sizeof(value_t) == sizeof(u8) || sizeof(value_t) == sizeof(u16) || sizeof(value_t) == sizeof(u32));

            if constexpr (sizeof(value_t) == sizeof(u32))
            {
                k += *(pStr + 0);
            }
            else if constexpr (sizeof(value_t) == sizeof(u16))
            {
                k += *(pStr + 0);
                k <<= sizeof(u16);
                k += *(pStr + 1);
            }
            else
            {
                k += *(pStr + 0);
                k <<= sizeof(u8);
                k += *(pStr + 1);
                k <<= sizeof(u8);
                k += *(pStr + 2);
                k <<= sizeof(u8);
                k += *(pStr + 3);
            }

            pStr += sizeof(u32);

            k *= 0xcc9e2d51; //-V101
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;

            nHash ^= k;
            nHash = (nHash << 13) | (nHash >> 19);
            nHash = nHash * 5 + 0xe6546b64; //-V104
        } while (--i);
    }

    if (nLen & 3)
    {
        size_t i = nLen & 3;
        size_t k = 0;
        do
        {
            k <<= 8;
            k |= pStr[i - 1];
        } while (--i);
        k *= 0xcc9e2d51; //-V101
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        nHash ^= k;
    }

    nHash ^= nLen; //-V103
    nHash ^= nHash >> 16;
    nHash *= 0x85ebca6b; //-V101
    nHash ^= nHash >> 13;
    nHash *= 0xc2b2ae35; //-V101
    nHash ^= nHash >> 16;

    return nHash;
}

template<class fwd_it_1_t, class fwd_it_2_t>
constexpr int iter_strcmp(fwd_it_1_t itBegin1, fwd_it_1_t itEnd1, fwd_it_2_t itBegin2, fwd_it_2_t itEnd2) noexcept
{
    auto it1 = itBegin1;
    auto it2 = itBegin2;

    while (it1 != itEnd1 && it2 != itEnd2 && *it1 == *it2)
    {
        ++it1;
        ++it2;
    }

    if (it1 == itEnd1 && it2 == itEnd2)
        return 0;

    if (it1 == itEnd1)
        return -static_cast<int>(*it2);

    if (it2 == itEnd2)
        return static_cast<int>(*it1);

    return static_cast<int>(*it1) - static_cast<int>(*it2);
}

template<class value_t>
constexpr int strcmp(const value_t* pszLeft, const value_t* pszRight)
{
    while (*pszLeft && (*pszLeft == *pszRight))
    {
        ++pszLeft;
        ++pszRight;
    }
    return *pszLeft - *pszRight;
}

namespace details
{

template<class value_t, size_t N>
constexpr const auto& choose_str_prefix(const char (&c)[N], const wchar_t (&w)[N]) noexcept
{
    if constexpr (std::is_same_v<value_t, char>)
        return c;
    else
        return w;
}

template<>
constexpr char choose_char_prefix<char>(char c, wchar_t) noexcept
{
    return c;
}

template<>
constexpr wchar_t choose_char_prefix<wchar_t>(char, wchar_t w) noexcept
{
    return w;
}

} // namespace details

template<class value_t, class T>
constexpr const value_t* get_format_specifier() noexcept
{
    const value_t* pszFormat = nullptr;

    using test_type = std::remove_cvref_t<T>;

    if constexpr (std::is_same_v<test_type, char>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%hhd");
    }
    else if constexpr (std::is_same_v<test_type, unsigned char>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%hhu");
    }
    else if constexpr (std::is_same_v<test_type, short>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%hd");
    }
    else if constexpr (std::is_same_v<test_type, unsigned short>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%hu");
    }
    else if constexpr (std::is_same_v<test_type, int>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%d");
    }
    else if constexpr (std::is_same_v<test_type, unsigned int>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%u");
    }
    else if constexpr (std::is_same_v<test_type, long>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%ld");
    }
    else if constexpr (std::is_same_v<test_type, unsigned long>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%lu");
    }
    else if constexpr (std::is_same_v<test_type, long long>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%lld");
    }
    else if constexpr (std::is_same_v<test_type, unsigned long long>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%llu");
    }
    else if constexpr (std::is_same_v<test_type, float>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%f");
    }
    else if constexpr (std::is_same_v<test_type, double>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%lf");
    }
    else if constexpr (std::is_same_v<test_type, long double>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%Lf");
    }
    else if constexpr (std::is_same_v<std::remove_cv_t<std::remove_pointer_t<test_type>>, char>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%s");
    }
    else if constexpr (std::is_same_v<std::remove_cv_t<std::remove_pointer_t<test_type>>, wchar_t>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%ls");
    }
    else if constexpr (std::is_pointer_v<test_type>)
    {
#if QX_MSVC
        pszFormat = QX_STR_PREFIX(value_t, "0x%p");
#else
        pszFormat = QX_STR_PREFIX(value_t, "%p");
#endif
    }

    return pszFormat;
}

template<class value_t>
constexpr std::size_t strlen(const value_t* psz)
{
    if (!psz)
        return 0;

    std::size_t nLen = 0;
    while (*psz != QX_CHAR_PREFIX(value_t, '\0'))
    {
        ++psz;
        ++nLen;
    }

    return nLen;
}

} // namespace qx
