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
#include <qx/macros/static_assert.h>

namespace qx
{

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

    // Whether to preserve contents using memcpy when resizing from small to big and back
    // Keep in mind, that std::realloc (big -> big and small -> big) preserves contents always, adding some performance overhead
    static constexpr bool bPreserveContents = traits_type::bPreserveContents;

    static constexpr size_type nBufferSize = nSBOSize - 2 * sizeof(size_type);
    using buffer_type                      = std::array<std::byte, nBufferSize>;

public:
    sbo_bytes() noexcept = default;
    sbo_bytes(sbo_bytes&& other) noexcept;

    ~sbo_bytes() noexcept;

    sbo_bytes& operator=(sbo_bytes&& other) noexcept;

    /**
        @brief  Make sure the capacity is at least nRequestedSize and allocate memory if needed, and change the size to nRequestedSize
        @param  nRequestedSize - required size (bytes)
        @retval                - false if memory allocation failed, true otherwise
    **/
    bool resize(size_type nRequestedSize) noexcept;

    /**
        @brief  Make sure the capacity is at least nRequestedSize and allocate memory if needed, but do not change the size
        @param  nRequestedSize - required size (bytes)
        @retval                - false if memory allocation failed, true otherwise
    **/
    bool reserve(size_type nRequestedSize) noexcept;

    /**
        @brief  Reduce capacity to fit the size, possibly moving data to the internal buffer if the size becomes small
        @retval  - false if memory allocation failed, SBO remains valid in this case, true otherwise
    **/
    bool shrink_to_fit() noexcept;

    /**
        @brief Free allocated memory
    **/
    void free() noexcept;

    /**
        @brief  Get SBO data: from a buffer or from a heap
        @retval - SBO data pointer
    **/
    QX_FORCE_INLINE std::byte* data() noexcept;

    /**
        @brief  Get SBO data: from a buffer or from a heap
        @retval  - SBO data pointer
    **/
    QX_FORCE_INLINE const std::byte* data() const noexcept;

    /**
        @brief  Get SBO size (bytes)
        @retval - SBO size (bytes)
    **/
    QX_FORCE_INLINE size_type size() const noexcept;

    /**
        @brief  Get SBO capacity (bytes)
        @retval - SBO capacity (bytes), can't be less than nBufferSize
    **/
    QX_FORCE_INLINE size_type capacity() const noexcept;

    /**
        @brief  Is the SBO small and fits into the local buffer
        @retval - true if the SBO is small and fits into the local buffer
    **/
    QX_FORCE_INLINE bool is_small() const noexcept;

private:
    /**
        @brief   Resize SBO using heap memory
        @details The initial state can be either small or big, but the final state will be big.
                 If the initial state is small, data will be preserved if bPreserveContents is true.
        @param   nNewSize - required size (bytes)
        @retval           - false if memory allocation failed, true otherwise
    **/
    bool reallocate_to_big(size_type nNewSize) noexcept;

    /**
        @brief   Resize SBO using local buffer
        @details The initial state must be big, but the final state will be small and fit into the local buffer.
                 Data will be preserved if bPreserveContents is true.
        @param   nNewSize - required size (bytes)
    **/
    void reallocate_to_small(size_type nNewSize) noexcept;

    /**
        @brief  Get new size according to the growth strategy
        @param  nRequestedSize - required size (bytes)
        @retval                - new size
    **/
    QX_FORCE_INLINE size_type get_new_size(size_type nRequestedSize) const noexcept;

private:
    union
    {
        buffer_type buffer = buffer_type();
        std::byte*  pData;
    } m_Data;

    size_type m_nSize          = 0;
    size_type m_nAllocatedSize = 0;
};

} // namespace qx

#include <qx/memory/sbo_bytes.inl>
