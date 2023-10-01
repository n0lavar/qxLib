/**

    @file      static_buffer.h
    @author    Khrapov
    @date      15.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/patterns/singleton.h>

#include <functional>
#include <vector>

namespace qx
{

/**

    @class   static_buffer
    @brief   Class contains static buffers of different types
    @details These buffers may be used to decrease number of allocations when you need temporary storage
    @author  Khrapov
    @date    15.08.2022

**/
class static_buffer
{
    QX_SINGLETON_S(static_buffer, thread_local);

public:
    /**
        @brief  Get buffer of type T
        @tparam T - buffer type
        @retval   - buffer instance
    **/
    template<class T>
    T& get_buffer()
    {
        thread_local T buffer = [this]()
        {
            m_Cleaners.push_back(
                []()
                {
                    buffer = T();
                });

            return T();
        }();

        return buffer;
    }

    /**
        @brief   Clear all buffers
        @warning This method should be called from every thread using this class
                 Otherwise we would have to protect the modification of the buffer with a mutex
    **/
    void clear()
    {
        for (const auto& cleaner : m_Cleaners)
            cleaner();
    }

private:
    std::vector<std::function<void()>> m_Cleaners;
};

} // namespace qx
