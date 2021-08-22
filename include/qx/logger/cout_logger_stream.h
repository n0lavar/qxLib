/**

    @file      cout_logger_stream.h
    @brief     Contains qx::cout_logger_stream class
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>

#include <iostream>

namespace qx
{

/**

    @class   cout_logger_stream
    @brief   Logger stream for std::cout output
    @details ~
    @author  Khrapov
    @date    28.07.2021

**/
class cout_logger_stream : public base_logger_stream
{
    /**
        @struct cout_logger_stream::auto_terminal_color
        @date   19.08.2021
    **/
    struct auto_terminal_color
    {
        static constexpr std::string_view reset        = "\033[0m";
        static constexpr std::string_view red          = "\033[0;31m";
        static constexpr std::string_view red_bold     = "\033[1;31m";
        static constexpr std::string_view green        = "\033[0;32m";
        static constexpr std::string_view green_bold   = "\033[1;32m";
        static constexpr std::string_view yellow       = "\033[0;33m";
        static constexpr std::string_view yellow_bold  = "\033[01;33m";
        static constexpr std::string_view blue         = "\033[0;34m";
        static constexpr std::string_view blue_bold    = "\033[1;34m";
        static constexpr std::string_view magenta      = "\033[0;35m";
        static constexpr std::string_view magenta_bold = "\033[1;35m";
        static constexpr std::string_view cyan         = "\033[0;36m";
        static constexpr std::string_view cyan_bold    = "\033[1;36m";

        auto_terminal_color(std::string_view color)
        {
            std::cout << color;
        }
        ~auto_terminal_color(void)
        {
            std::cout << reset;
        }
    };

public:
    /**
        @brief Output to std::cout
        @param svMessage - message string
        @param logUnit   - log unit info
    **/
    virtual void process_output(std::string_view svMessage, log_unit logUnit)
        override;

    /**
        @brief Set whether cout output should be colored
        @param bUsingColors - true if cout output should be colored
    **/
    void set_using_colors(bool bUsingColors) noexcept;

private:
    bool m_bUsingColors = false;
};

} // namespace qx

#include <qx/logger/cout_logger_stream.inl>
