/**

    @file      rect.inl
    @author    Khrapov
    @date      12.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class VectorType>
constexpr basic_rect<VectorType>::basic_rect(vector_type size, vector_type pos) noexcept : m_Pos(pos)
{
    check_and_assign_size(size);
}

template<class VectorType>
constexpr basic_rect<VectorType>::basic_rect(
    value_type width,
    value_type height,
    value_type xPos,
    value_type yPos) noexcept
    : m_Pos(xPos, yPos)
{
    check_and_assign_size({ width, height });
}

template<class VectorType>
constexpr void basic_rect<VectorType>::expand(const vector_type& dSize) noexcept
{
    check_and_assign_size(m_Size + dSize);
}

template<class VectorType>
constexpr void basic_rect<VectorType>::contract(const vector_type& dSize) noexcept
{
    check_and_assign_size(m_Size - dSize);
}

template<class VectorType>
constexpr void basic_rect<VectorType>::set_size(const vector_type& size) noexcept
{
    check_and_assign_size(size);
}

template<class VectorType>
constexpr void basic_rect<VectorType>::set_pos(const vector_type& pos) noexcept
{
    m_Pos = pos;
}

template<class VectorType>
constexpr void basic_rect<VectorType>::shift(const vector_type& dPos) noexcept
{
    m_Pos += dPos;
}

template<class VectorType>
constexpr const typename basic_rect<VectorType>::vector_type& basic_rect<VectorType>::pos() const noexcept
{
    return m_Pos;
}

template<class VectorType>
constexpr const typename basic_rect<VectorType>::vector_type& basic_rect<VectorType>::min() const noexcept
{
    return pos();
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::vector_type basic_rect<VectorType>::max() const noexcept
{
    return m_Pos + m_Size;
}

template<class VectorType>
constexpr const typename basic_rect<VectorType>::vector_type& basic_rect<VectorType>::size() const noexcept
{
    return m_Size;
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::value_type basic_rect<VectorType>::width() const noexcept
{
    return m_Size.x;
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::value_type basic_rect<VectorType>::height() const noexcept
{
    return m_Size.y;
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::value_type basic_rect<VectorType>::left() const noexcept
{
    return m_Pos.x;
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::value_type basic_rect<VectorType>::right() const noexcept
{
    return m_Pos.x + m_Size.x;
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::value_type basic_rect<VectorType>::top() const noexcept
{
    return m_Pos.y;
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::value_type basic_rect<VectorType>::bottom() const noexcept
{
    return m_Pos.y + m_Size.y;
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::vector_type basic_rect<VectorType>::center() const noexcept
{
    return m_Pos + m_Size / static_cast<value_type>(2.0);
}

template<class VectorType>
constexpr bool basic_rect<VectorType>::empty() const noexcept
{
    return epsilon_equal(area(), static_cast<value_type>(0.0));
}

template<class VectorType>
constexpr typename basic_rect<VectorType>::value_type basic_rect<VectorType>::area() const noexcept
{
    return m_Size.x * m_Size.y;
}

template<class VectorType>
constexpr bool basic_rect<VectorType>::contains(const vector_type& pos, const vector_type& originPos) const noexcept
{
    const vector_type posRelativeToOrigin = pos + originPos;
    return epsilon_less_equal(m_Pos.x, posRelativeToOrigin.x) && epsilon_less_equal(m_Pos.y, posRelativeToOrigin.y)
           && epsilon_greater_equal(m_Pos.x + m_Size.x, posRelativeToOrigin.x)
           && epsilon_greater_equal(m_Pos.y + m_Size.y, posRelativeToOrigin.y);
}

template<class VectorType>
constexpr bool basic_rect<VectorType>::contains(const basic_rect& other, const vector_type& originPos) const noexcept
{
    return contains(other.min(), originPos) && contains(other.max(), originPos);
}

template<class VectorType>
constexpr bool basic_rect<VectorType>::overlaps(const basic_rect& other) const noexcept
{
    return epsilon_less_equal(left(), other.right()) && epsilon_greater_equal(right(), other.left())
           && epsilon_less_equal(top(), other.bottom()) && epsilon_greater_equal(bottom(), other.top());
}

template<class VectorType>
constexpr std::optional<basic_rect<VectorType>> basic_rect<VectorType>::overlap(const basic_rect& other) const noexcept
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

template<class VectorType>
constexpr bool basic_rect<VectorType>::operator==(const basic_rect& other) const noexcept
{
    return epsilon_equal(left(), other.left()) && epsilon_equal(top(), other.top())
           && epsilon_equal(width(), other.width()) && epsilon_equal(height(), other.height());
}

template<class VectorType>
constexpr bool basic_rect<VectorType>::operator!=(const basic_rect& other) const noexcept
{
    return !(*this == other);
}

template<class VectorType>
constexpr void basic_rect<VectorType>::check_and_assign_size(const vector_type& size) noexcept
{
    m_Size.x = std::max(size.x, static_cast<value_type>(0.0));
    m_Size.y = std::max(size.y, static_cast<value_type>(0.0));
}

} // namespace qx
