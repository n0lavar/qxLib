/**

    @file      destruction_callback.h
    @brief     Contains qx::test_destruction_callback class
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
class destruction_callback
{
public:
    using destroyer = std::function<void()>;

public:
    QX_NONCOPYABLE(destruction_callback);
    QX_MOVABLE(destruction_callback);

    /**
        @brief destruction_callback object constructor
    **/
    destruction_callback() noexcept = default;

    /**
        @brief destruction_callback object constructor
        @param _destroyer - functor that will be called when object will be destroyed
    **/
    destruction_callback(destroyer _destroyer) : m_Destroyer(std::move(_destroyer))
    {
    }

    /**
        @brief destruction_callback object destructor
    **/
    ~destruction_callback()
    {
        if (m_Destroyer)
            m_Destroyer();
    }

private:
    destroyer m_Destroyer;
};

} // namespace qx
