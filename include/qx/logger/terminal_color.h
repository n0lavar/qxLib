/**

    @file      terminal_color.h
    @brief     Contains qx::terminal_color class
    @details   ~
    @author    Khrapov
    @date      10.12.2022
    @copyright � Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>
#include <qx/render/color.h>
#include <qx/static_buffer.h>

#include <iostream>

namespace qx
{

class terminal_color;

}

template<class char_type>
std::basic_ostream<char_type>& operator<<(std::basic_ostream<char_type>& os, const qx::terminal_color& terminalColor);

namespace qx
{

/**

    @class   terminal_color
    @brief   Class for colors manipulating in terminal
    @details Always check which colors are available in your machine, for ex. with qx::terminal_color::test_colors()
    @author  Khrapov
    @date    13.12.2022

    @code
    
    std::cout << qx::terminal_color::font(qx::color::green()) << "green" << qx::terminal_color::reset() << std::endl;
    
    @endcode

**/
class terminal_color
{
    template<class char_type>
    friend std::basic_ostream<char_type>& ::operator<<(
        std::basic_ostream<char_type>& is,
        const terminal_color&          terminalColor);

    enum class type
    {
        font,
        back,
        reset
    };

public:
    /**
        @brief  Set font color
        @param  color - new font color
        @retval       - terminal_color instance to pass to the ostream
    **/
    static constexpr terminal_color font(const color& color) noexcept;

    /**
        @brief  Set background color
        @param  color - new background color
        @retval       - terminal_color instance to pass to the ostream
    **/
    static constexpr terminal_color back(const color& color) noexcept;

    /**
        @brief  Reset all colors
        @retval  - terminal_color instance to pass to the ostream
    **/
    static constexpr terminal_color reset() noexcept;

    /**
        @brief Output colors available in qx::color to test if terminal color work
    **/
    static void test_colors();

private:
    /**
        @brief terminal_color object constructor
        @param color - color to set
        @param eType - output type
    **/
    constexpr terminal_color(const color& color, type eType) noexcept;

    /**
        @brief terminal_color object constructor
        @param eType - output type
    **/
    constexpr terminal_color(type eType) noexcept;

private:
    color m_Color = color::white();
    type  m_eType = type::reset;
};

} // namespace qx

#include <qx/logger/terminal_color.inl>