/**

    @file      string_data.h
    @author    Khrapov
    @date      8.11.2020
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <array>
#include <cstring> // std::memmove

namespace qx
{

enum class string_resize_type
{
    common,
    reserve,
    shrink_to_fit
};

/**

    @class   string_data
    @brief   Represents string data
    @details Implements small string optimization
    @tparam  traits_t - char traits. \see string_traits.h
    @author  Khrapov
    @date    8.11.2020

**/
template<class traits_t>
class string_data
{
    using value_type = typename traits_t::value_type;
    using pointer    = typename traits_t::pointer;
    using size_type  = typename traits_t::size_type;
    using buffer     = std::array<value_type, traits_t::small_string_size()>;

public:
    /**
        @brief  Get string data: from buffer or from pointer
        @retval - string pointer
    **/
    pointer data() noexcept;

    /**
        @brief Free allocated memory
    **/
    void free() noexcept;

    /**
        @brief  Resize string data
        @param  nSymbols - new size
        @param  nAlign   - align (if 16 then size 13->16 16->16 18->32)
        @param  eType    - resize type
        @retval          - true if memory alloc is successful
    **/
    bool resize(size_type nSymbols, size_type nAlign, string_resize_type eType) noexcept;

    /**
        @brief  Get string length
        @retval - string length
    **/
    size_type size() const noexcept;

    /**
        @brief  Get capacity of string
        @retval - string capacity, can't be less than Traits::small_string_size()
    **/
    size_type capacity() const noexcept;

    /**
        @brief  Is string small and fits in the local buffer
        @retval - true if string is small and fits in the local buffer
    **/
    bool is_small() const noexcept;

private:
    union
    {
        pointer m_pData = nullptr;
        buffer  m_Buffer;
    };

    size_type m_nSize          = 0;
    size_type m_nAllocatedSize = 0;
};

} // namespace qx

#include <qx/containers/string/string_data.inl>
