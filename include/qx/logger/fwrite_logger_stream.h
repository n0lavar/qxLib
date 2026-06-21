/**

    @file      fwrite_logger_stream.h
    @author    Khrapov
    @date      18.01.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/logger/base_standard_streams_stream.h>

#include <cstdio>

namespace qx
{

/**

    @class   fwrite_logger_stream
    @brief   Logger stream based on std::fwrite output
    @author  Khrapov
    @date    18.01.2026

**/
class fwrite_logger_stream : public base_standard_streams_stream
{
    QX_RTTI_CLASS(fwrite_logger_stream, base_standard_streams_stream);

public:
    /**
        @brief fwrite_logger_stream object constructor
        @param streamConfig - logger stream configuration
    **/
    fwrite_logger_stream(const config& streamConfig = config()) noexcept;

    fwrite_logger_stream(fwrite_logger_stream&&) noexcept = default;

    // base_logger_stream
    //
    virtual void do_flush() override;

private:
    // base_standard_streams_stream
    //
    virtual void cout_colorized(verbosity eVerbosity, string_view svMessage, const color& rangeColor) override;
    virtual void cout_common(verbosity eVerbosity, string_view svMessage) override;
};

} // namespace qx

#include <qx/logger/fwrite_logger_stream.inl>
