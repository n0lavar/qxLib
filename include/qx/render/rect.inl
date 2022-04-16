/**

    @file      rect.inl
    @author    Khrapov
    @date      12.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

constexpr rect::rect(vector_type size, vector_type pos) noexcept : m_Pos(pos)
{
    check_and_assign_size(size);
}

constexpr rect::rect(
    value_type width,
    value_type height,
    value_type xPos,
    value_type yPos) noexcept
    : m_Pos(xPos, yPos)
{
    check_and_assign_size({ width, height });
}

constexpr void rect::expand(const vector_type& dSize) noexcept
{
    check_and_assign_size(m_Size + dSize);
}

constexpr void rect::contract(const vector_type& dSize) noexcept
{
    check_and_assign_size(m_Size - dSize);
}

constexpr void rect::set_size(const vector_type& size) noexcept
{
    check_and_assign_size(size);
}

constexpr void rect::set_pos(const vector_type& pos) noexcept
{
    m_Pos = pos;
}

constexpr void rect::shift(const vector_type& dPos) noexcept
{
    m_Pos += dPos;
}

constexpr const rect::vector_type& rect::pos() const noexcept
{
    return m_Pos;
}

constexpr const rect::vector_type& rect::min() const noexcept
{
    return pos();
}

constexpr rect::vector_type rect::max() const noexcept
{
    return m_Pos + m_Size;
}

constexpr const rect::vector_type& rect::size() const noexcept
{
    return m_Size;
}

constexpr rect::value_type rect::width() const noexcept
{
    return m_Size.x;
}

constexpr rect::value_type rect::height() const noexcept
{
    return m_Size.y;
}

constexpr rect::value_type rect::left() const noexcept
{
    return m_Pos.x;
}

constexpr rect::value_type rect::right() const noexcept
{
    return m_Pos.x + m_Size.x;
}

constexpr rect::value_type rect::top() const noexcept
{
    return m_Pos.y;
}

constexpr rect::value_type rect::bottom() const noexcept
{
    return m_Pos.y + m_Size.y;
}

constexpr rect::vector_type rect::center() const noexcept
{
    return m_Pos + m_Size / 2.f;
}

constexpr bool rect::empty() const noexcept
{
    return epsilon_equal(area(), 0.f);
}

constexpr rect::value_type rect::area() const noexcept
{
    return m_Size.x * m_Size.y;
}

constexpr bool rect::contains(
    const vector_type& pos,
    const vector_type& originPos) const noexcept
{
    const vector_type posRelativeToOrigin = pos + originPos;
    return epsilon_less_equal(m_Pos.x, posRelativeToOrigin.x)
           && epsilon_less_equal(m_Pos.y, posRelativeToOrigin.y)
           && epsilon_greater_equal(m_Pos.x + m_Size.x, posRelativeToOrigin.x)
           && epsilon_greater_equal(m_Pos.y + m_Size.y, posRelativeToOrigin.y);
}

constexpr bool rect::contains(const rect& other, const vector_type& originPos)
    const noexcept
{
    return contains(other.min(), originPos) && contains(other.max(), originPos);
}

constexpr bool rect::overlaps(const rect& other) const noexcept
{
    return epsilon_less_equal(left(), other.right())
           && epsilon_greater_equal(right(), other.left())
           && epsilon_less_equal(top(), other.bottom())
           && epsilon_greater_equal(bottom(), other.top());
}

constexpr std::optional<rect> rect::overlap(const rect& other) const noexcept
{
    const value_type x1 = std::max(left(), other.left());
    const value_type x2 =
        std::min(left() + width(), other.left() + other.width());
    const value_type y1 = std::max(top(), other.top());
    const value_type y2 =
        std::min(top() + height(), other.top() + other.height());

    if (epsilon_greater_equal(x2 - x1, 0.f)
        && epsilon_greater_equal(y2 - y1, 0.f))
    {
        return rect({ x2 - x1, y2 - y1 }, { x1, y1 });
    }
    else
    {
        return std::nullopt;
    }
}

constexpr bool rect::operator==(const rect& other) const noexcept
{
    return epsilon_equal(left(), other.left())
           && epsilon_equal(top(), other.top())
           && epsilon_equal(width(), other.width())
           && epsilon_equal(height(), other.height());
}

constexpr bool rect::operator!=(const rect& other) const noexcept
{
    return !(*this == other);
}

constexpr void rect::check_and_assign_size(const vector_type& size) noexcept
{
    m_Size.x = std::max(size.x, 0.f);
    m_Size.y = std::max(size.y, 0.f);
}

} // namespace qx
