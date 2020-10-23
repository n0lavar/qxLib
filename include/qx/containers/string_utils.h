//==============================================================================
//
//!\file                         string_utils.h
//
//!\brief
//!\details     ~
//
//!\author      Khrapov
//!\date        17.10.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/typedefs.h>

namespace qx
{

//==============================================================================
//!\fn                      qx::murmur_32_hash<Char>
//
//!\brief   Murmur hash
//!\details https://en.wikipedia.org/wiki/MurmurHash
//          https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
//
//!\param   key  - key value, string for hashing (char must be 1, 2 or 4 bytes long)
//!\param   len  - string length
//!\param   seed - seed for hashing
//!\retval       - 32bit unsigned value
//!\author  Khrapov
//!\date    10.09.2020
//==============================================================================
template<typename Char>
inline constexpr u32 murmur_32_hash(const Char* key, size_t len, u32 seed)
{
    u32 h = seed;
    if (len > 3)
    {
        size_t i = len >> 2;
        do
        {
            u32 k = 0;

            // constexpr version of std::memcpy(&k, key, sizeof(u32));
            if constexpr (sizeof(Char) == sizeof(u32))
            {
                k += *(key + 0);
            }
            else if constexpr (sizeof(Char) == sizeof(u16))
            {
                k += *(key + 0);
                k <<= sizeof(u16);
                k += *(key + 1);
            }
            else
            {
                k += *(key + 0);
                k <<= sizeof(u8);
                k += *(key + 1);
                k <<= sizeof(u8);
                k += *(key + 2);
                k <<= sizeof(u8);
                k += *(key + 3);
            }

            key += sizeof(u32);
            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
            h = (h << 13) | (h >> 19);
            h = h * 5 + 0xe6546b64;
        } while (--i);
    }
    if (len & 3)
    {
        size_t i = len & 3;
        u32 k = 0;
        do
        {
            k <<= 8;
            k |= key[i - 1];
        } while (--i);
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
    }
    h ^= len; //-V103
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

//==============================================================================
//!\fn                  qx::iter_strcmp<FwdIt1, FwdIt2>
//
//!\brief  Compares string 1 with string 2
//!\param  itBegin1 - string 1 begin iterator
//!\param  itEnd1   - string 1 end iterator
//!\param  itBegin2 - string 2 begin iterator
//!\param  itEnd2   - string 2 end iterator
//!\retval          - < 0 the first character that does not match has a lower value in str 1 than in str 2
//                      0 the contents of both strings are equal
//                    > 0 the first character that does not match has a greater value in str 1 than in str 2
//!\date   23.10.2020
//==============================================================================
template<class FwdIt1, class FwdIt2>
inline int iter_strcmp(FwdIt1 itBegin1, FwdIt1 itEnd1, FwdIt2 itBegin2, FwdIt2 itEnd2)
{
    int nRet = 0;

    if (itBegin1 != itEnd1 && itBegin2 != itEnd2)
    {
        auto it1 = itBegin1;
        auto it2 = itBegin2;
        while (it2 != itEnd2 && (*it1 == *it2))
        {
            ++it2;
            ++it1;
        }
        nRet = *it1 - (it2 == itEnd2 ? *it1 : *it2);
    }

    return nRet;
}

}
