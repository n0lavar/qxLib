/**

    @file      string_view_iterator.h
    @author    Khrapov
    @date      24.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/containers/flags.h>
#include <qx/containers/string/string_view.h>
#include <qx/typedefs.h>

namespace qx
{

enum class delimiter_inclusion_flags : u8
{
    none  = 0,
    begin = 1 << 0,
    end   = 1 << 1
};
QX_FLAGS_ENUM_CLASS(delimiter_inclusion_flags);

/**

    @class   string_view_iterator
    @brief   Iterator class that allows to iterate over a string view using a delimiter character
    @details This class is not supposed to use manually, @see string_view_view
    @tparam  char_t - char type
    @author  Khrapov
    @date    24.10.2023

**/
template<class char_t>
class string_view_iterator
{
public:
    using value_type        = basic_string_view<char_t>;
    using size_type         = size_t;
    using iterator_category = std::forward_iterator_tag;
    using iterator_concept  = std::forward_iterator_tag;

public:
    /**
        @brief  Return iterator to beginning
        @param  svFull                   - string to iterate
        @param  chDelimiter              - delimiter character
        @param  eDelimiterInclusionFlags - flags that determine whether to include delimiters in parts when iterating
        @retval                          - iterator to beginning
    **/
    [[nodiscard]] static constexpr string_view_iterator begin(
        value_type                       svFull,
        char_t                           chDelimiter,
        flags<delimiter_inclusion_flags> eDelimiterInclusionFlags = delimiter_inclusion_flags::none);

    /**
        @brief  Return iterator to end
        @retval  - iterator to end
    **/
    [[nodiscard]] static constexpr string_view_iterator end();

    [[nodiscard]] constexpr value_type           operator*() const noexcept;
    constexpr string_view_iterator&              operator++() noexcept;
    [[nodiscard]] constexpr string_view_iterator operator++(int) const noexcept;
    constexpr bool operator==(const string_view_iterator& itOther) const noexcept = default;
    constexpr bool operator!=(const string_view_iterator& itOther) const noexcept = default;

private:
    /**
        @brief string_view_iterator object constructor
        @param svFull                   - string to iterate
        @param chDelimiter              - delimiter character
        @param eDelimiterInclusionFlags - flags that determine whether to include delimiters in parts when iterating
    **/
    constexpr string_view_iterator(
        value_type                       svFull,
        char_t                           chDelimiter,
        flags<delimiter_inclusion_flags> eDelimiterInclusionFlags) noexcept;

    /**
        @brief Go to the next part
    **/
    constexpr void next() noexcept;

private:
    value_type                       m_svFull;
    value_type                       m_svCurrent;
    char_t                           m_chDelimiter;
    flags<delimiter_inclusion_flags> m_eDelimiterInclusionFlags = delimiter_inclusion_flags::none;
};

} // namespace qx

#include <qx/containers/string/string_view_iterator.inl>
