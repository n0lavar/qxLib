/**

    @file      rect.inl
    @author    Khrapov
    @date      12.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class vector_t>
constexpr basic_rect<vector_t>::basic_rect(vector_t size, vector_t pos) noexcept : m_Pos(pos)
{
    check_and_assign_size(size);
}

template<class vector_t>
constexpr basic_rect<vector_t>::basic_rect(
    value_type width,
    value_type height,
    value_type xPos,
    value_type yPos) noexcept
    : m_Pos(xPos, yPos)
{
    check_and_assign_size({ width, height });
}

template<class vector_t>
constexpr void basic_rect<vector_t>::expand(const vector_t& dSize) noexcept
{
    check_and_assign_size(m_Size + dSize);
}

template<class vector_t>
constexpr void basic_rect<vector_t>::contract(const vector_t& dSize) noexcept
{
    check_and_assign_size(m_Size - dSize);
}

template<class vector_t>
constexpr void basic_rect<vector_t>::set_size(const vector_t& size) noexcept
{
    check_and_assign_size(size);
}

template<class vector_t>
constexpr void basic_rect<vector_t>::set_pos(const vector_t& pos) noexcept
{
    m_Pos = pos;
}

template<class vector_t>
constexpr void basic_rect<vector_t>::shift(const vector_t& dPos) noexcept
{
    m_Pos += dPos;
}

template<class vector_t>
constexpr const vector_t& basic_rect<vector_t>::pos() const noexcept
{
    return m_Pos;
}

template<class vector_t>
constexpr const vector_t& basic_rect<vector_t>::min() const noexcept
{
    return pos();
}

template<class vector_t>
constexpr vector_t basic_rect<vector_t>::max() const noexcept
{
    return m_Pos + m_Size;
}

template<class vector_t>
constexpr const vector_t& basic_rect<vector_t>::size() const noexcept
{
    return m_Size;
}

template<class vector_t>
constexpr typename basic_rect<vector_t>::value_type basic_rect<vector_t>::width() const noexcept
{
    return m_Size.x;
}

template<class vector_t>
constexpr typename basic_rect<vector_t>::value_type basic_rect<vector_t>::height() const noexcept
{
    return m_Size.y;
}

template<class vector_t>
constexpr typename basic_rect<vector_t>::value_type basic_rect<vector_t>::left() const noexcept
{
    return m_Pos.x;
}

template<class vector_t>
constexpr typename basic_rect<vector_t>::value_type basic_rect<vector_t>::right() const noexcept
{
    return m_Pos.x + m_Size.x;
}

template<class vector_t>
constexpr typename basic_rect<vector_t>::value_type basic_rect<vector_t>::top() const noexcept
{
    return m_Pos.y;
}

template<class vector_t>
constexpr typename basic_rect<vector_t>::value_type basic_rect<vector_t>::bottom() const noexcept
{
    return m_Pos.y + m_Size.y;
}

template<class vector_t>
constexpr vector_t basic_rect<vector_t>::center() const noexcept
{
    return m_Pos + m_Size / static_cast<value_type>(2.0);
}

template<class vector_t>
constexpr bool basic_rect<vector_t>::empty() const noexcept
{
    return epsilon_equal(area(), static_cast<value_type>(0.0));
}

template<class vector_t>
constexpr typename basic_rect<vector_t>::value_type basic_rect<vector_t>::area() const noexcept
{
    return m_Size.x * m_Size.y;
}

template<class vector_t>
constexpr bool basic_rect<vector_t>::contains(const vector_t& pos, const vector_t& originPos) const noexcept
{
    const vector_t posRelativeToOrigin = pos + originPos;
    return epsilon_less_equal(m_Pos.x, posRelativeToOrigin.x) && epsilon_less_equal(m_Pos.y, posRelativeToOrigin.y)
           && epsilon_greater_equal(m_Pos.x + m_Size.x, posRelativeToOrigin.x)
           && epsilon_greater_equal(m_Pos.y + m_Size.y, posRelativeToOrigin.y);
}

template<class vector_t>
constexpr bool basic_rect<vector_t>::contains(const basic_rect& other, const vector_t& originPos) const noexcept
{
    return contains(other.min(), originPos) && contains(other.max(), originPos);
}

template<class vector_t>
constexpr bool basic_rect<vector_t>::overlaps(const basic_rect& other) const noexcept
{
    return epsilon_less_equal(left(), other.right()) && epsilon_greater_equal(right(), other.left())
           && epsilon_less_equal(top(), other.bottom()) && epsilon_greater_equal(bottom(), other.top());
}

template<class vector_t>
constexpr std::optional<basic_rect<vector_t>> basic_rect<vector_t>::overlap(const basic_rect& other) const noexcept
{
    const value_type x1 = std::max(left(), other.left());
    const value_type x2 = std::min(left() + width(), other.left() + other.width());
    const value_type y1 = std::max(top(), other.top());
    const value_type y2 = std::min(top() + height(), other.top() + other.height());

    if (epsilon_greater_equal(x2 - x1, static_cast<value_type>(0.0))
        && epsilon_greater_equal(y2 - y1, static_cast<value_type>(0.0)))
    {
        return basic_rect({ x2 - x1, y2 - y1 }, { x1, y1 });
    }
    else
    {
        return std::nullopt;
    }
}

template<class vector_t>
constexpr bool basic_rect<vector_t>::operator==(const basic_rect& other) const noexcept
{
    return epsilon_equal(left(), other.left()) && epsilon_equal(top(), other.top())
           && epsilon_equal(width(), other.width()) && epsilon_equal(height(), other.height());
}

template<class vector_t>
constexpr bool basic_rect<vector_t>::operator!=(const basic_rect& other) const noexcept
{
    return !(*this == other);
}

template<class vector_t>
constexpr void basic_rect<vector_t>::check_and_assign_size(const vector_t& size) noexcept
{
    m_Size.x = std::max(size.x, static_cast<value_type>(0.0));
    m_Size.y = std::max(size.y, static_cast<value_type>(0.0));
}

} // namespace qx
