//============================================================================
//
//!\file                           hashes.h
//
//!\brief       hashes implementations
//!\details     ~
//
//!\author      Khrapov
//!\date        8.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once
#include <typedefs.h>
#include <cstring>

namespace qx::hash
{
    namespace str
    {
        u32 Murmur32(const char* key, size_t len, u32 seed);
    }
}

#include <hashes.inl>
