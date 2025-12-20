/**

    @file      bytes_sbo.h
    @author    Khrapov
    @date      20.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <array>
#include <cstddef>
#include <cstring> // std::memmove

namespace qx
{

enum class sbo_resize_type
{
    common,
    reserve,
    shrink_to_fit
};

/**

    @class   bytes_sbo
    @brief   A type erased small buffer object that works with raw data
    @tparam  traits_t - SBO traits type
    @author  Khrapov
    @date    20.12.2025

**/
template<class traits_t>
class bytes_sbo
{
    using size_type                                  = typename traits_t::size_type;
    static constexpr size_type nSBOSize              = traits_t::nSBOSize;
    static constexpr bool      bShrinkToFitWhenSmall = traits_t::bShrinkToFitWhenSmall;

    using buffer = std::array<std::byte, nSBOSize>;

public:
    bytes_sbo() noexcept = default;
    bytes_sbo(bytes_sbo&& other) noexcept;

    ~bytes_sbo() noexcept;

    bytes_sbo& operator=(bytes_sbo&& other) noexcept;

    /**
        @brief  Get SBO data: from a buffer or from a heap
        @retval - string pointer
    **/
    std::byte* data() noexcept;

    /**
        @brief Free allocated memory
    **/
    void free() noexcept;

    /**
        @brief  Resize SBO
        @param  nNewSize - new size (bytes)
        @param  nAlign   - align (if 16 then size 13->16 16->16 18->32)
        @param  eType    - resize type
        @retval          - true if memory alloc is successful
    **/
    bool resize(size_type nNewSize, size_type nAlign, sbo_resize_type eType) noexcept;

    /**
        @brief  Get SBO size (bytes)
        @retval - SBO size (bytes)
    **/
    size_type size() const noexcept;

    /**
        @brief  Get SBO capacity (bytes)
        @retval - SBO capacity (bytes), can't be less than nSBOSize
    **/
    size_type capacity() const noexcept;

    /**
        @brief  Is the SBO small and fits into the local buffer
        @retval - true if the SBO is small and fits into the local buffer
    **/
    bool is_small() const noexcept;

private:
    union
    {
        std::byte* m_pData = nullptr;
        buffer     m_Buffer;
    };

    size_type m_nSize          = 0;
    size_type m_nAllocatedSize = 0;
};

} // namespace qx

#include <qx/sbo/bytes_sbo.inl>
