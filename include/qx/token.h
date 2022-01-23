/**

    @file      token.h
    @brief     Contains qx::token class
    @author    Khrapov
    @date      12.12.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/useful_macros.h>

namespace qx
{

/**

    @class   token
    @brief   Token class for RAII
    @details Functor passed in constructor will be called in destructor
    @author  Khrapov
    @date    12.12.2021

**/
class token
{
public:
    using destroyer = std::function<void()>;

public:
    QX_NONCOPYABLE(token);
    QX_MOVABLE(token);

    /**
        @brief token object constructor
    **/
    token() noexcept = default;

    /**
        @brief token object constructor
        @param _destroyer - functor that will be called when object will be destroyed
    **/
    token(destroyer _destroyer) : m_Destroyer(std::move(_destroyer))
    {
    }

    /**
        @brief token object destructor
    **/
    ~token()
    {
        if (m_Destroyer)
            m_Destroyer();
    }

private:
    destroyer m_Destroyer;
};

} // namespace qx
