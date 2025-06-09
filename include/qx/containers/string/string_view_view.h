/**

    @file      string_view_view.h
    @author    Khrapov
    @date      24.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_view_iterator.h>

namespace qx
{

/**

    @class   string_view_view
    @brief   Class that allows to iterate over a string view using a delimiter character
    @tparam  char_t - char type
    @author  Khrapov
    @date    24.10.2023

**/
template<class char_t>
class string_view_view : public std::ranges::view_interface<string_view_view<char_t>>
{
public:
    /**
        @brief string_view_view object constructor
        @param svFull                   - string to iterate
        @param chDelimiter              - delimiter character
        @param eDelimiterInclusionFlags - flags that determine whether to include delimiters in parts when iterating
    **/
    constexpr string_view_view(
        basic_string_view<char_t>        svFull,
        char_t                           chDelimiter,
        flags<delimiter_inclusion_flags> eDelimiterInclusionFlags = delimiter_inclusion_flags::none) noexcept;

    /**
        @brief  Return iterator to beginning
        @retval  - iterator to beginning
    **/
    string_view_iterator<char_t> begin() const noexcept;

    /**
        @brief  Return iterator to end
        @retval  - iterator to end
    **/
    string_view_iterator<char_t> end() const noexcept;

private:
    basic_string_view<char_t>        m_svFull;
    char_t                           m_chDelimiter;
    flags<delimiter_inclusion_flags> m_eDelimiterInclusionFlags = delimiter_inclusion_flags::none;
};

} // namespace qx

#include <qx/containers/string/string_view_view.inl>
