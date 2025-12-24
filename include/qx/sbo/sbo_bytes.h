/**

    @file      sbo_bytes.h
    @author    Khrapov
    @date      20.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <array>
#include <cstddef>

#include <qx/macros/common.h>

namespace qx
{

enum class sbo_resize_type
{
    common,
    reserve,
    shrink_to_fit
};

/**

    @class   sbo_bytes
    @brief   A type erased small buffer object that works with raw data
    @tparam  traits_t - SBO traits type
    @author  Khrapov
    @date    20.12.2025

**/
template<class traits_t>
class sbo_bytes
{
public:
    using traits_type = traits_t;
    using size_type   = typename traits_type::size_type;

    // the final size of the whole sbo_bytes object, including internal data
    static constexpr size_type nSBOSize = traits_type::nSBOSize;
    static_assert(nSBOSize >= 32);

    // when the size changes so it becomes less or equal a buffer size, should we free a memory and move back to a buffer?
    static constexpr bool bShrinkToFitWhenSmall = traits_type::bShrinkToFitWhenSmall;

    static constexpr size_type nBufferSize = nSBOSize - 2 * sizeof(size_type);
    using buffer                           = std::array<std::byte, nBufferSize>;

public:
    sbo_bytes() noexcept = default;
    sbo_bytes(sbo_bytes&& other) noexcept;

    ~sbo_bytes() noexcept;

    sbo_bytes& operator=(sbo_bytes&& other) noexcept;

    /**
        @brief  Resize SBO
        @param  nNewSize       - new size (bytes)
        @param  nAlignment     - alignment (if 16 then size 13->16 16->16 18->32)
        @param  eSboResizeType - a resize type
        @param  bMemmove       - in case the content is relocated, should we call memmove or the callee will handle the moving?
        @retval                - true if memory alloc is successful
    **/
    bool resize(size_type nNewSize, size_type nAlignment, sbo_resize_type eSboResizeType, bool bMemmove) noexcept;

    /**
        @brief Free allocated memory
    **/
    void free() noexcept;

    /**
        @brief  Get SBO data: from a buffer or from a heap
        @retval - SBO data pointer
    **/
    std::byte* data() noexcept;

    /**
        @brief  Get SBO data: from a buffer or from a heap
        @retval  - SBO data pointer
    **/
    const std::byte* data() const noexcept;

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
        buffer     m_Buffer;
        std::byte* m_pData = nullptr;
    };

    size_type m_nSize          = 0;
    size_type m_nAllocatedSize = 0;
};

} // namespace qx

#include <qx/sbo/sbo_bytes.inl>
