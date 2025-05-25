/**

    @file      class_id.h
    @author    Khrapov
    @date      11.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/format_string.h>
#include <qx/macros/copyable_movable.h>
#include <qx/meta/type_strings.h>

namespace qx
{

/**

    @class   class_id
    @brief   Class id, unique for each class using qx rtti system
    @author  Khrapov
    @date    5.07.2024

**/
class class_id
{
    friend std::hash<class_id>;

public:
    constexpr class_id() noexcept = default;
    QX_COPYMOVABLE(class_id);

    /**
        @brief  Create a class id for a given type (the type doesn't require to use qx rtti system)
        @tparam T - a type
        @retval   - T id
    **/
    template<class T>
    constexpr static class_id create();

    constexpr bool operator==(const class_id& other) const noexcept;
    constexpr bool operator!=(const class_id& other) const noexcept;
    constexpr bool operator<(const class_id& other) const noexcept;

    /**
        @brief  Get class name
        @retval  - class name
    **/
    constexpr string_view get_class_name() const;

private:
    string_view m_svClassName = QX_TEXT("Empty name");
    size_t      m_nId         = 0;
};

constexpr bool class_id::operator==(const class_id& other) const noexcept
{
    return m_nId == other.m_nId;
}

constexpr bool class_id::operator!=(const class_id& other) const noexcept
{
    return m_nId != other.m_nId;
}

constexpr bool class_id::operator<(const class_id& other) const noexcept
{
    return m_nId < other.m_nId;
}

constexpr string_view class_id::get_class_name() const
{
    return m_svClassName;
}

template<class T>
constexpr class_id class_id::create()
{
    class_id result;
    result.m_svClassName = type_strings<T, char_type>::get_signature();
    result.m_nId         = string_hash(result.m_svClassName);
    return result;
}

} // namespace qx

template<>
struct std::hash<qx::class_id>
{
    constexpr size_t operator()(const qx::class_id& id) const noexcept
    {
        return id.m_nId;
    }
};

template<>
struct std::formatter<qx::class_id, qx::char_type> : qx::basic_formatter
{
    template<class FormatContextType>
    constexpr auto format(const qx::class_id& id, FormatContextType& ctx) const
    {
        return std::format_to(ctx.out(), QX_TEXT("{}"), id.get_class_name());
    }
};
