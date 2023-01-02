/**

    @file      category.inl
    @author    Khrapov
    @date      2.01.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

constexpr category::category(const char* pszName, const color& categoryColor, const char* pszDescription) noexcept
    : m_Color(categoryColor)
    , m_pszName(pszName)
    , m_pszDescription(pszDescription)
{
}

constexpr const char* category::get_name() const noexcept
{
    return m_pszName;
}

constexpr const char* category::get_description() const noexcept
{
    return m_pszDescription;
}

constexpr const color& category::get_color() const noexcept
{
    return m_Color;
}

} // namespace qx

constexpr qx::category CatDefault(nullptr, qx::color::empty());

namespace qx::details
{

template<size_t nHash>
constexpr const category& get_file_category() noexcept
{
    return CatDefault;
}

} // namespace qx::details
