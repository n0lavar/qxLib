/**

    @file      rect.h
    @author    Khrapov
    @date      12.11.2021
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <algorithm>
#include <optional>

#include <qx/macros/copyable_movable.h>
#include <qx/math/common.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <glm/vec2.hpp>
QX_POP_SUPPRESS_WARNINGS();

namespace qx
{

/**

    @class   rect
    @brief   Rectangle class
    @author  Khrapov
    @date    12.11.2021

**/
template<class vector_t>
class basic_rect
{
public:
    using vector_type = vector_t;
    using value_type  = typename vector_type::value_type;

public:
    QX_COPYMOVABLE(basic_rect);

    constexpr basic_rect() noexcept = default;

    /**
        @brief basic_rect object constructor
        @param size - rect size
        @param pos  - upper left corner pos
    **/
    constexpr explicit basic_rect(vector_t size, vector_t pos = vector_t(value_type(0.f))) noexcept;

    /**
        @brief basic_rect object constructor
        @param width  - rect width
        @param height - rect height
        @param xPos   - rect upper left corner x pos
        @param yPos   - rect upper left corner y pos
    **/
    constexpr basic_rect(
        value_type width,
        value_type height,
        value_type xPos = value_type(0.f),
        value_type yPos = value_type(0.f)) noexcept;

    /**
        @brief Expand rect
        @param dSize - size to expand
    **/
    constexpr void expand(const vector_t& dSize) noexcept;

    /**
        @brief Contract rect
        @param dSize - size to contract
    **/
    constexpr void contract(const vector_t& dSize) noexcept;

    /**
        @brief Change rect size
        @param size - new size
    **/
    constexpr void set_size(const vector_t& size) noexcept;

    /**
        @brief Set rect position
        @param pos - rect position
    **/
    constexpr void set_pos(const vector_t& pos) noexcept;

    /**
        @brief Shift rect position
        @param dPos - position delta
    **/
    constexpr void shift(const vector_t& dPos) noexcept;

    /**
        @brief  Get upper left corner pos
        @retval - upper left corner pos
    **/
    constexpr const vector_t& pos() const noexcept;

    /**
        @brief   Get min rect pos
        @details same as pos()
        @retval  - min rect pos
    **/
    constexpr const vector_t& min() const noexcept;

    /**
        @brief  Get max rect pos
        @retval - max rect pos
    **/
    constexpr vector_t max() const noexcept;

    /**
        @brief  Get rect size
        @retval - rect size
    **/
    constexpr const vector_t& size() const noexcept;

    /**
        @brief  Get rect width
        @retval - rect width
    **/
    constexpr value_type width() const noexcept;

    /**
        @brief  Get rect height
        @retval - rect height
    **/
    constexpr value_type height() const noexcept;

    /**
        @brief  Get rect left border coordinate (x)
        @retval - rect left border coordinate (x)
    **/
    constexpr value_type left() const noexcept;

    /**
        @brief  rect right border coordinate (x)
        @retval - rect right border coordinate (x)
    **/
    constexpr value_type right() const noexcept;

    /**
        @brief  rect top border coordinate (y)
        @retval - rect top border coordinate (y)
    **/
    constexpr value_type top() const noexcept;

    /**
        @brief  rect bottom border coordinate (y)
        @retval - rect bottom border coordinate (y)
    **/
    constexpr value_type bottom() const noexcept;

    /**
        @brief  Get rect center pos
        @retval - rect center pos
    **/
    constexpr vector_t center() const noexcept;

    /**
        @brief  Is rect empty
        @retval - true if rect is empty
    **/
    constexpr bool empty() const noexcept;

    /**
        @brief  Calc rect area
        @retval - rect area
    **/
    constexpr value_type area() const noexcept;

    /**
        @brief  Is point inside rect
        @param  pos       - point pos
        @param  originPos - coordinate system center pos
        @retval           - true if pos is inside rect
    **/
    constexpr bool contains(const vector_t& pos, const vector_t& originPos = vector_t(0.f)) const noexcept;

    /**
        @brief  Is other rect inside this rect
        @param  other     - other rect
        @param  originPos - coordinate system center pos
        @retval           - true if other rect is inside this rect
    **/
    constexpr bool contains(const basic_rect& other, const vector_t& originPos = vector_t(0.f)) const noexcept;

    /**
        @brief  Is this rect overlaps other rect
        @param  other - other rect
        @retval       - true if this rect is overlaps other rect
    **/
    constexpr bool overlaps(const basic_rect& other) const noexcept;

    /**
        @brief  Get rect representing overlap this rect by other rect
        @param  other - other rect
        @retval       - rect representing overlap this rect by other rect or nullopt
    **/
    constexpr std::optional<basic_rect> overlap(const basic_rect& other) const noexcept;

    constexpr bool operator==(const basic_rect& other) const noexcept;
    constexpr bool operator!=(const basic_rect& other) const noexcept;

private:
    /**
        @brief Check new size and assign if size is positive
        @param size - new size
    **/
    constexpr void check_and_assign_size(const vector_t& size) noexcept;

private:
    vector_t m_Size = vector_t(0.f);
    vector_t m_Pos  = vector_t(0.f);
};

using rect  = basic_rect<glm::vec2>;
using drect = basic_rect<glm::dvec2>;

} // namespace qx

#include <qx/render/rect.inl>
