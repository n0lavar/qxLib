/**

    @file      iterate.h
    @brief     Contains qx::iterate functions along with default filters and adapters for him
    @details   ~
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

constexpr auto always_true = [](const auto&)
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
    @tparam  Container - container of elements type
    @tparam  Callable  - callable type. if callable returns false, iteration breaks
    @tparam  Filter    - filter type. if filter returns true, callable is applied
    @tparam  Adapter   - adapter type. converts container element type to another type for callable and filter
    @param   container - container object
    @param   callable  - callable object
    @param   filter    - filter object
    @param   adapter   - adapter object
**/
template<
    class Container,
    class Callable,
    class Filter  = decltype(iterate_filters::always_true),
    class Adapter = decltype(iterate_adapters::no_change)>
void iterate(
    const Container& container,
    const Callable&  callable,
    const Filter&    filter  = iterate_filters::always_true,
    const Adapter&   adapter = iterate_adapters::no_change)
{
    for (const auto& element : container)
    {
        auto adaptedElement = adapter(element);
        if (filter(adaptedElement) && callable(adaptedElement))
            break;
    }
}

} // namespace qx
