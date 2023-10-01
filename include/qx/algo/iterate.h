/**

    @file      iterate.h
    @author    Khrapov
    @date      23.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <utility>

namespace qx
{

namespace iterate_adapters
{

constexpr auto no_change = []<class T>(T&& value)
{
    return std::forward<T>(value);
};

} // namespace iterate_adapters

namespace iterate_filters
{

constexpr auto always_true = [](const auto&...)
{
    return true;
};

} // namespace iterate_filters

/**
    @brief   Iterate container with filter
    @details This function is useful when:
             1. you don't want to use getter for container
                (for ex. even const vector of shared_ptr will allow the client to make one more shared_ptr)
             2. you don't want the client to know what type of container you are using
             3. you want the client to be able to iterate only over a part of the value of an element of the vector
    @see     code examples in test_iterate.cpp
    @tparam  container_t - container of elements type
    @tparam  callable_t  - callable type. if callable returns false, iteration breaks
    @tparam  filter_t    - filter type. if filter returns true, callable is applied
    @tparam  adapter_t   - adapter type. converts container element type to another type for callable and filter
    @param   container   - container object
    @param   callable    - callable object
    @param   filter      - filter object
    @param   adapter     - adapter object
**/
template<
    class container_t,
    class callable_t,
    class filter_t  = decltype(iterate_filters::always_true),
    class adapter_t = decltype(iterate_adapters::no_change)>
void iterate(
    const container_t& container,
    const callable_t&  callable,
    const filter_t&    filter  = iterate_filters::always_true,
    const adapter_t&   adapter = iterate_adapters::no_change)
{
    for (const auto& element : container)
    {
        auto adaptedElement = adapter(element);
        if (filter(adaptedElement) && callable(adaptedElement))
            break;
    }
}

} // namespace qx
