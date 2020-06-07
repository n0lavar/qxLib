//==============================================================================
//
//!\file                          hashes.inl
//
//!\brief       hashes implementations
//!\details     ~
//
//!\author      Khrapov
//!\date        8.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx::hash::str
{

//==============================================================================
//!\fn                  qx::hash::str::Murmur32<Char>
//
//!\brief   Murmur hash
//!\details https://en.wikipedia.org/wiki/MurmurHash
//          https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
//
//!\param   key  - key value, string for hashing
//!\param   len  - string length
//!\param   seed - seed for hashing
//!\retval       - 32bit unsigned value
//!\author Khrapov
//!\date   8.01.2020
//==============================================================================
template<typename Char>
inline u32 Murmur32(const Char* key, size_t len, u32 seed)
{
    u32 h = seed;
    if (len > 3)
    {
        size_t i = len >> 2;
        do
        {
            u32 k;
            memcpy(&k, key, sizeof(u32));
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

}