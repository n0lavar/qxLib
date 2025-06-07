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

    @class   base_string_view_iterator
    @brief   Iterator class that allows to iterate over a string view using a delimiter character
    @tparam  char_t           - char type
    @tparam  bForwardIterator - false if this is a reverse iterator
    @author  Khrapov
    @date    24.10.2023

**/
template<class char_t, bool bForwardIterator>
class base_string_view_iterator
{
public:
    using value_type        = basic_string_view<char_t>;
    using size_type         = size_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using iterator_concept  = std::bidirectional_iterator_tag;

public:
    /**
        @brief base_string_view_iterator object constructor
        @param svFull                   - string to iterate
        @param chDelimiter              - delimiter character
        @param eDelimiterInclusionFlags - flags that determine whether to include delimiters in parts when iterating
    **/
    constexpr base_string_view_iterator(
        value_type                       svFull,
        char_t                           chDelimiter,
        flags<delimiter_inclusion_flags> eDelimiterInclusionFlags = delimiter_inclusion_flags::none) noexcept;

    /**
        @brief  Check if this iterator is valid (i.e. it didn't reach the end of the sequence)
        @retval  - true if this iterator is valid
    **/
    operator bool() const noexcept;

    [[nodiscard]] constexpr value_type                operator*() const noexcept;
    constexpr base_string_view_iterator&              operator++() noexcept;
    [[nodiscard]] constexpr base_string_view_iterator operator++(int) const noexcept;
    constexpr base_string_view_iterator&              operator--() noexcept;
    [[nodiscard]] constexpr base_string_view_iterator operator--(int) const noexcept;
    constexpr bool operator==(const base_string_view_iterator& itOther) const noexcept = default;
    constexpr bool operator!=(const base_string_view_iterator& itOther) const noexcept = default;

private:
    /**
        @brief Go to the next part
        @param bForwardDirection - true if this is a forward direction for the current bForwardIterator
    **/
    constexpr void next(bool bForwardDirection) noexcept;

private:
    value_type                       m_svFull;
    size_t                           m_nCurrentBegin;
    size_t                           m_nCurrentEnd;
    char_t                           m_chDelimiter;
    flags<delimiter_inclusion_flags> m_eDelimiterInclusionFlags = delimiter_inclusion_flags::none;
};

template<class char_t>
using string_view_iterator = base_string_view_iterator<char_t, true>;

template<class char_t>
using reverse_string_view_iterator = base_string_view_iterator<char_t, false>;

} // namespace qx

#include <qx/containers/string/string_view_iterator.inl>
