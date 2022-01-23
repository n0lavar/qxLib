/**

    @file      rect.h
    @brief     Contains qx::rect class
    @author    Khrapov
    @date      12.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <algorithm>
#include <optional>

#include <qx/useful_macros.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS
#include <glm/vec2.hpp>
QX_POP_SUPPRESS_WARNINGS

namespace qx
{

/**

    @class   rect
    @brief   Rectangle class
    @details ~
    @author  Khrapov
    @date    12.11.2021

**/
class rect
{
public:
    using vector_type = glm::vec2;
    using value_type  = vector_type::value_type;

public:
    QX_COPYMOVABLE(rect);

    /**
        @brief rect object constructor
    **/
    constexpr rect(void) noexcept = default;

    /**
        @brief rect object constructor
        @param size - rect size
        @param pos  - upper left corner pos
    **/
    constexpr explicit rect(
        vector_type size,
        vector_type pos = vector_type(value_type(0.f))) noexcept;

    /**
        @brief rect object constructor
        @param width  - rect width
        @param height - rect height
        @param xPos   - rect upper left corner x pos
        @param yPos   - rect upper left corner y pos
    **/
    constexpr rect(
        value_type width,
        value_type height,
        value_type xPos = value_type(0.f),
        value_type yPos = value_type(0.f)) noexcept;

    /**
        @brief Expand rect
        @param dSize - size to expand
    **/
    constexpr void expand(const vector_type& dSize) noexcept;

    /**
        @brief Contract rect
        @param dSize - size to contract
    **/
    constexpr void contract(const vector_type& dSize) noexcept;

    /**
        @brief Change rect size
        @param size - new size
    **/
    constexpr void set_size(const vector_type& size) noexcept;

    /**
        @brief Set rect position
        @param pos - rect position
    **/
    constexpr void set_pos(const vector_type& pos) noexcept;

    /**
        @brief Shift rect position
        @param dPos - position delta
    **/
    constexpr void shift(const vector_type& dPos) noexcept;

    /**
        @brief  Get upper left corner pos
        @retval - upper left corner pos
    **/
    constexpr const vector_type& pos(void) const noexcept;

    /**
        @brief   Get min rect pos
        @details same as pos()
        @retval  - min rect pos
    **/
    constexpr const vector_type& min(void) const noexcept;

    /**
        @brief  Get max rect pos
        @retval - max rect pos
    **/
    constexpr vector_type max(void) const noexcept;

    /**
        @brief  Get rect size
        @retval - rect size
    **/
    constexpr const vector_type& size(void) const noexcept;

    /**
        @brief  Get rect width
        @retval - rect width
    **/
    constexpr value_type width(void) const noexcept;

    /**
        @brief  Get rect height
        @retval - rect height
    **/
    constexpr value_type height(void) const noexcept;

    /**
        @brief  Get rect left border coord (x)
        @retval - rect left border coord (x)
    **/
    constexpr value_type left(void) const noexcept;

    /**
        @brief  rect right border coord (x)
        @retval - rect right border coord (x)
    **/
    constexpr value_type right(void) const noexcept;

    /**
        @brief  rect top border coord (y)
        @retval - rect top border coord (y)
    **/
    constexpr value_type top(void) const noexcept;

    /**
        @brief  rect bottom border coord (y)
        @retval - rect bottom border coord (y)
    **/
    constexpr value_type bottom(void) const noexcept;

    /**
        @brief  Get rect center pos
        @retval - rect center pos
    **/
    constexpr vector_type center(void) const noexcept;

    /**
        @brief  Is rect empty
        @retval - true if rect is empty
    **/
    constexpr bool empty(void) const noexcept;

    /**
        @brief  Calc rect area
        @retval - rect area
    **/
    constexpr value_type area(void) const noexcept;

    /**
        @brief  Is point inside rect
        @param  pos       - point pos
        @param  originPos - coordinate system center pos
        @retval           - true if pos is inside rect
    **/
    constexpr bool contains(
        const vector_type& pos,
        const vector_type& originPos = vector_type(0.f)) const noexcept;

    /**
        @brief  Is other rect inside this rect
        @param  other     - other rect
        @param  originPos - coordinate system center pos
        @retval           - true if other rect is inside this rect
    **/
    constexpr bool contains(
        const rect&        other,
        const vector_type& originPos = vector_type(0.f)) const noexcept;

    /**
        @brief  Is this rect overlaps other rect
        @param  other - other rect
        @retval       - true if this rect is overlaps other rect
    **/
    constexpr bool overlaps(const rect& other) const noexcept;

    /**
        @brief  Get rect representing overlap this rect by other rect
        @param  other - other rect
        @retval       - rect representing overlap this rect by other rect or nullopt
    **/
    constexpr std::optional<rect> overlap(const rect& other) const noexcept;

    /**
        @brief  operator==
        @param  other - other rect
        @retval       - true, if objects are equal
    **/
    constexpr bool operator==(const rect& other) const noexcept;

    /**
        @brief  operator!=
        @param  other - other rect
        @retval       - true, if objects are not equal
    **/
    constexpr bool operator!=(const rect& other) const noexcept;

private:
    /**
        @brief Check new size and assign if size is positive
        @param size - new size
    **/
    constexpr void check_and_assign_size(const vector_type& size) noexcept;

private:
    vector_type m_Size = vector_type(0.f);
    vector_type m_Pos  = vector_type(0.f);
};

} // namespace qx

#include <qx/render/rect.inl>
