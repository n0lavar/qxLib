/**

    @file      iterate_several_containers.h
    @brief     Contains qx::iterate_several_containers function
    @details   ~
    @author    Khrapov
    @date      26.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

namespace qx
{

/**
    @brief  Iterate several containers in a row with one func
    @tparam func_t       - callable type
    @tparam containers_t - containers types pack
    @param  func         - iteration callable
    @param  containers   - containers to iterate
**/
template<class func_t, class... containers_t>
void iterate_several_containers(const func_t& func, const containers_t&... containers)
{
    auto iteration_func = [&]<class container_t>(const container_t& container)
    {
        for (const auto& elem : container)
            func(elem);
    };

    (iteration_func(containers), ...);
}

} // namespace qx
