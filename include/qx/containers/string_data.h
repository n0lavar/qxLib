//==============================================================================
//
//!\file                         string_data.h
//
//!\brief       Contains string_data class
//!\details     ~
//
//!\author      Khrapov
//!\date        8.11.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <array>

namespace qx
{

enum class string_resize_type
{
    common,
    reserve,
    shrink_to_fit
};

//==============================================================================
//
//!\class                   qx::string_data<Traits>
//
//!\brief   Represents string data and implements small string optimization
//!\details ~
//
//!\author  Khrapov
//!\date    8.11.2020
//
//==============================================================================
template <class Traits>
class string_data
{
    using value_type    = typename Traits::value_type;
    using pointer       = typename Traits::pointer;
    using size_type     = typename Traits::size_type;
    using buffer        = std::array<value_type, Traits::small_string_size()>;

public:

    pointer     data        (void);
    void        free        (void);
    bool        resize      (size_type          nSymbols,
                             size_type          nAlign,
                             string_resize_type eType);

    size_type   size        (void) const    { return m_nSize; }
    size_type   capacity    (void) const;
    bool        is_small    (void) const    { return m_nAllocatedSize == 0; }

private:

    union
    {
        pointer m_pData = nullptr;
        buffer  m_Buffer;
    };

    size_type   m_nSize             = 0;
    size_type   m_nAllocatedSize    = 0;
};

}

#include <qx/containers/string_data.inl>
