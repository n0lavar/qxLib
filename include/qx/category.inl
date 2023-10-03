/**

    @file      category.inl
    @author    Khrapov
    @date      2.01.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

constexpr category::category(string_view svName, const color& categoryColor) noexcept
    : m_Color(categoryColor)
    , m_svName(svName)
{
}

constexpr category category::set_verbosity(verbosity eVerbosity) const noexcept
{
    category category_    = *this;
    category_.m_Verbosity = eVerbosity;
    return category_;
}

constexpr string_view category::get_name() const noexcept
{
    return m_svName;
}

constexpr const color& category::get_color() const noexcept
{
    return m_Color;
}

constexpr verbosity category::get_verbosity() const noexcept
{
    return m_Verbosity;
}

} // namespace qx

constexpr qx::category CatDefault = qx::category(L"", qx::color::white());

namespace qx::details
{

template<size_t nHash>
constexpr const category& get_file_category() noexcept
{
    return CatDefault;
}

} // namespace qx::details
