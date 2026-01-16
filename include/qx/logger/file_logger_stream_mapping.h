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

#if !QX_WIN
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

namespace qx
{

/**

    @class   file_logger_stream_mapping
    @brief   Memory-mapped file based logger stream (fast append)
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

    // size_t
    //
    virtual void do_log(const category& category, verbosity eVerbosity, string_view svMessage) override;
    virtual void do_flush() override;

private:
    bool remap_to_capacity(uint64_t newCap);

    bool ensure_capacity(uint64_t nAdditionalBytes);

    static uint64_t align_up_u64(uint64_t v, uint64_t a);

private:
#if QX_WIN
    HANDLE m_hFile = INVALID_HANDLE_VALUE;
    HANDLE m_hMap  = INVALID_HANDLE_VALUE;
#else
    int m_Fd = -1;
#endif

    std::byte* m_pData = nullptr;

    uint64_t m_nSize        = 0; // bytes written
    uint64_t m_nCapacity    = 0; // mapped capacity in bytes
    uint64_t m_nGranularity = 0; // allocation granularity
};

} // namespace qx

#include <qx/logger/file_logger_stream_mapping.inl>
