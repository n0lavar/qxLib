/**

    @file      transform.h
    @author    Khrapov
    @date      1.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <concepts>

namespace qx
{

/**
    @brief std::transform equivalent that makes the code a bit shorter
    @code
    std::vector numbers { 1, 2, 3 };

    {
        std::vector<qx::string> strings;
        strings.resize(numbers.size());
        std::transform(
            numbers.begin(),
            numbers.end(),
            strings.begin(),
            [](int nNumber)
            {
                return qx::string::static_from(nNumber);
            });
        return strings;
    }
    
    // vs

    {
        return qx::transform_return<std::vector>(
            numbers,
            [](int nNumber)
            {
                return qx::string::static_from(nNumber);
            });
    }
    
    @endcode
    @tparam result_container_t      - any container type, that supports iteration and .insert(it, value)
    @tparam input_container_t       - any container type, that supports iteration
    @tparam transform_callable_t    - callable type, that takes input_container_t's element type, the return value of this callable forms result_container_t's element type 
    @tparam result_container_rest_t - any types required for result_container_t after element type
    @param  input                   - input container, may be moved
    @param  transformCallable       - transformation callable
    @retval                         - container with transformed elements
**/
template<
    template<class...> class result_container_t,
    class input_container_t,
    class transform_callable_t,
    class... result_container_rest_t>
auto transform_return(input_container_t&& input, const transform_callable_t& transformCallable);

} // namespace qx

#include <qx/algo/transform.inl>
