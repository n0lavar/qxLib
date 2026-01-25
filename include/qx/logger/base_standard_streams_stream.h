/**

    @file      base_standard_streams_stream.h
    @author    Khrapov
    @date      18.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/logger/terminal_color.h>

namespace qx
{

/**

    @class   base_standard_streams_stream
    @brief   A base class for logger streams based on standard streams
    @author  Khrapov
    @date    18.01.2026

**/
class base_standard_streams_stream : public base_logger_stream
{
public:
    struct config : base_logger_stream::config
    {
        // Is it necessary to insert colour tags to highlight certain parts of messages?
        // For example, each category has its own colour.
        // Consoles can understand these tags, but they may be unnecessary when outputting to another location.
        bool bUseColors = false;

        //Should the order of normal messages and errors be synchronised?
        //These two types of messages go to different standard streams, and in general,
        //preserving the order is not guaranteed.
        //This option flushes the stream if the previous message was of a different type.
        bool bSyncUsualAndErrorMessages = true;
    };

public:
    /**
        @brief base_standard_streams_stream object constructor
        @param streamConfig - logger stream configuration
    **/
    base_standard_streams_stream(const config& streamConfig) noexcept;

    base_standard_streams_stream(base_standard_streams_stream&&) noexcept = default;

    // base_logger_stream
    //
    virtual void do_log(const category& category, verbosity eVerbosity, string_view svMessage) override;

protected:
    /**
        @brief Check the previous message type and flush if needed
        @param eCurrentMessageVerbosity - current message verbosity
    **/
    void check_previous_message(verbosity eCurrentMessageVerbosity);

private:
    /**
        @brief Output colorized message to standard streams
        @param eVerbosity - message verbosity
        @param svMessage  - message text
        @param rangeColor - a terminal color for the message
    **/
    virtual void cout_colorized(verbosity eVerbosity, string_view svMessage, const color& rangeColor) = 0;

    /**
        @brief Output a message with a default color
        @param eVerbosity - message verbosity
        @param svMessage  - message text
    **/
    virtual void cout_common(verbosity eVerbosity, string_view svMessage) = 0;

private:
    bool m_bUsingColors               = false;
    bool m_bSyncUsualAndErrorMessages = true;
    bool m_bPrevMessageWasError       = false;
};

} // namespace qx

#include <qx/logger/base_standard_streams_stream.inl>
