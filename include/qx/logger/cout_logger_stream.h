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
public:
    struct auto_terminal_color
    {
        static constexpr std::string_view font_black         = "\033[30m";
        static constexpr std::string_view back_black         = "\033[40m";
        static constexpr std::string_view font_red           = "\033[31m";
        static constexpr std::string_view back_red           = "\033[41m";
        static constexpr std::string_view font_green         = "\033[32m";
        static constexpr std::string_view back_green         = "\033[42m";
        static constexpr std::string_view font_yellow        = "\033[33m";
        static constexpr std::string_view back_yellow        = "\033[43m";
        static constexpr std::string_view font_blue          = "\033[34m";
        static constexpr std::string_view back_blue          = "\033[44m";
        static constexpr std::string_view font_mag           = "\033[35m";
        static constexpr std::string_view back_mag           = "\033[45m";
        static constexpr std::string_view font_cyan          = "\033[36m";
        static constexpr std::string_view back_cyan          = "\033[46m";
        static constexpr std::string_view font_bright_gray   = "\033[37m";
        static constexpr std::string_view back_bright_gray   = "\033[47m";
        static constexpr std::string_view font_dark_gray     = "\033[90m";
        static constexpr std::string_view back_dark_gray     = "\033[100m";
        static constexpr std::string_view font_bright_red    = "\033[91m";
        static constexpr std::string_view back_bright_red    = "\033[101m";
        static constexpr std::string_view font_bright_green  = "\033[92m";
        static constexpr std::string_view back_bright_green  = "\033[102m";
        static constexpr std::string_view font_bright_yellow = "\033[93m";
        static constexpr std::string_view back_bright_yellow = "\033[103m";
        static constexpr std::string_view font_bright_blue   = "\033[94m";
        static constexpr std::string_view back_bright_blue   = "\033[104m";
        static constexpr std::string_view font_bright_mag    = "\033[95m";
        static constexpr std::string_view back_bright_mag    = "\033[105m";
        static constexpr std::string_view font_bright_cyan   = "\033[96m";
        static constexpr std::string_view back_bright_cyan   = "\033[106m";
        static constexpr std::string_view font_bright_white  = "\033[97m";
        static constexpr std::string_view back_bright_white  = "\033[107m";
        static constexpr std::string_view reset              = "\033[0m";

        auto_terminal_color(std::string_view color)
        {
            std::cout << color;
        }
        ~auto_terminal_color()
        {
            std::cout << reset;
        }
    };

public:
    /**
        @brief cout_logger_stream object constructor
        @param bUseColors        - use color when output is not info
        @param bDisableStdioSync - don't synchronize to the standard C streams after each input/output operation
        @param bUntieCin         - untie cin from cout
    **/
    cout_logger_stream(bool bUseColors = true, bool bDisableStdioSync = true, bool bUntieCin = true);

    /**
        @brief Output to std::cout
        @param svMessage - message string
        @param logUnit   - log unit info
        @param eLogLevel - this message log level
    **/
    virtual void do_log(std::string_view svMessage, const log_unit& logUnit, log_level eLogLevel) override;

    /**
        @brief Output to std::wcout
        @param svMessage - message string
        @param logUnit   - log unit info
        @param eLogLevel - this message log level
    **/
    virtual void do_log(std::wstring_view svMessage, const log_unit& logUnit, log_level eLogLevel) override;

    /**
        @brief Set whether cout output should be colored
        @param bUsingColors - true if cout output should be colored
    **/
    void set_using_colors(bool bUsingColors) noexcept;

private:
    /**
        @brief  Get cout by char type
        @tparam char_type - char type
        @retval           - cout ref
    **/
    template<class char_type>
    static std::basic_ostream<char_type>& get_cout() noexcept;

    /**
        @brief  Output to std::basic_ostream 
        @tparam char_type - char type
        @param  svMessage - message string
        @param  logUnit   - log unit info
        @param  eLogLevel - this message log level
    **/
    template<class char_type>
    void log_cout(std::basic_string_view<char_type> svMessage, const log_unit& logUnit, log_level eLogLevel);

private:
    bool m_bUsingColors = true;
};

} // namespace qx

#include <qx/logger/cout_logger_stream.inl>
