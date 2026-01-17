/**

    @file      file_logger_stream_mapping.h
    @author    Khrapov
    @date      14.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/logger/base_file_logger_stream.h>
#include <qx/math/units/data.h>
#include <qx/windows.h>

#if QX_CLANG || QX_APPLE_CLANG || QX_GNU
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

namespace qx
{

/**

    @class   file_logger_stream_mapping
    @brief   High-performance file logger based on memory-mapped I/O.
    @details This logger implementation writes log data directly into a
             memory-mapped file region (mmap / CreateFileMapping).
             Instead of using traditional buffered I/O (fopen / WriteFile),
             the file is mapped into the process address space and written
             via simple memory copies.
    @author  Khrapov
    @date    15.01.2026

**/
class file_logger_stream_mapping : public base_file_logger_stream
{
public:
    /**
        @brief file_logger_stream_mapping object constructor
        @param streamConfig   - file logger configuration
        @param initialMapSize - initial mapping size (outer capacity). mapping grows when needed
    **/
    file_logger_stream_mapping(
        const config&             streamConfig   = config(),
        unit<size_t, units::data> initialMapSize = { 1, units::data::mebibytes });

    file_logger_stream_mapping(file_logger_stream_mapping&& other) noexcept;

    virtual ~file_logger_stream_mapping() override;

    // base_logger_stream
    //
    virtual void do_log(const category& category, verbosity eVerbosity, string_view svMessage) override;
    virtual void do_flush() override;

private:
    /**
        @brief Remap file to a new capacity.

        @details This function performs a full remapping sequence:

        1) Unmap the old memory view (if any)
        2) Destroy the old mapping object (Windows)
        3) Resize the file to `nNewCapacity`
        4) Create a new memory mapping with the new size
        5) Map the file into the process address space

        The file is always resized *before* mapping, because the OS
        cannot map memory beyond the current end of file.

        All sizes are expected to be aligned to the system granularity.

        This operation is relatively expensive and should not be performed
        frequently. It is typically triggered only when the log buffer
        runs out of space.

        @param  nNewCapacity - new capacity in bytes (must be >= current size)
        @retval              - true - remapping succeeded  
    **/
    bool remap_to_capacity(size_t nNewCapacity);

    /**
        @brief Ensure that mapped file has enough space for additional data.

        @details Checks whether the current mapped capacity is sufficient to store `nAdditionalBytes` more bytes.

        If there is not enough space, the file is grown (usually doubled), aligned to the system granularity,
        and remapped using remap_to_capacity().

        This function guarantees that subsequent writes will not overflow the mapped memory region.

        @param  nAdditionalBytes - Number of bytes that need to be written
        @retval                  - true - enough space is available or remapping succeeded  
    **/
    bool ensure_capacity(size_t nAdditionalBytes);

    /**
        @brief Align value up to the nearest multiple of alignment.

        @details This function rounds the given value `nValue` *upwards* to the nearest
        multiple of `nAlignment` (alignment / granularity / page size).

        If `nValue` is already aligned, it is returned unchanged.

        This is required for memory mapping and file resizing because operating systems work with fixed-size pages:

        - Windows: Allocation Granularity (usually 64 KB)
        - Linux:   Page Size (usually 4 KB)
        - macOS:   Page Size (usually 16 KB)

        Mapping or resizing a file to a non-aligned size may fail or cause undefined behavior.

        @param  nValue     - value to align
        @param  nAlignment - alignment / granularity / page size
        @retval            - aligned value >= value
    **/
    static size_t align_up_u64(size_t nValue, size_t nAlignment);

private:
#if QX_WIN
    HANDLE m_hFile = INVALID_HANDLE_VALUE;
    HANDLE m_hMap  = INVALID_HANDLE_VALUE;
#else
    int m_Fd = -1;
#endif

    std::byte* m_pData = nullptr;

    size_t m_nSize        = 0; // bytes written
    size_t m_nCapacity    = 0; // mapped capacity in bytes
    size_t m_nGranularity = 0; // allocation granularity
};

} // namespace qx

#include <qx/logger/file_logger_stream_mapping.inl>
