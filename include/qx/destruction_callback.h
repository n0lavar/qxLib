/**

    @file      destruction_callback.h
    @author    Khrapov
    @date      12.12.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/copyable_movable.h>

namespace qx
{

/**

    @class   destruction_callback
    @brief   Class for RAII: functor passed in constructor will be called in destructor
    @author  Khrapov
    @date    12.12.2021

**/
class [[nodiscard]] destruction_callback
{
public:
    using destroyer_type = std::function<void()>;

public:
    QX_NONCOPYABLE(destruction_callback);

    destruction_callback() noexcept = default;

    /**
        @brief  destruction_callback object constructor
        @tparam destroyer_t - callable type
        @param  destroyer   - functor that will be called when object is destroyed
    **/
    template<class destroyer_t>
    destruction_callback(destroyer_t destroyer);

    destruction_callback(destruction_callback&& other) noexcept;

    destruction_callback& operator=(destruction_callback&& other) noexcept;

    ~destruction_callback();

private:
    destroyer_type m_Destroyer;
};

inline destruction_callback::destruction_callback(destruction_callback&& other) noexcept
{
    std::swap(m_Destroyer, other.m_Destroyer);
}

inline destruction_callback& destruction_callback::operator=(destruction_callback&& other) noexcept
{
    std::swap(m_Destroyer, other.m_Destroyer);
    return *this;
}

inline destruction_callback::~destruction_callback()
{
    if (m_Destroyer)
        m_Destroyer();
}

template<class destroyer_t>
destruction_callback::destruction_callback(destroyer_t destroyer) : m_Destroyer(std::move(destroyer))
{
}

} // namespace qx
