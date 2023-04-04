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
    @tparam FuncType       - callable type
    @tparam ContainersType - containers types pack
    @param  func           - iteration callable
    @param  containers     - containers to iterate
**/
template<class FuncType, class... ContainersType>
void iterate_several_containers(const FuncType& func, const ContainersType&... containers)
{
    auto iteration_func = [&]<class Container>(const Container& container)
    {
        for (const auto& elem : container)
            func(elem);
    };

    (iteration_func(containers), ...);
}

} // namespace qx
