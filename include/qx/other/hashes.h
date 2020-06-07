//==============================================================================
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
//==============================================================================
#pragma once

#include <qx/other/typedefs.h>

namespace qx::hash
{
    namespace str
    {
        template<typename Char>
        u32 Murmur32(const Char* key, size_t len, u32 seed);
    }
}

#include <qx/other/hashes.inl>
