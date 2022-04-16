/**

    @file      utils.h
    @brief     Contains different utils
    @details   ~
    @author    Khrapov
    @date      20.03.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

namespace qx
{

/**
    @struct  visit_overload
    @details This struct allows to visit std::variant with lambdas
    @link    https://www.cppstories.com/2018/09/visit-variants/
    @tparam  Ts - lambda types

    @code

    struct Fluid { };
    struct LightItem { };
    struct HeavyItem { };
    struct FragileItem { };

    int main() {
        std::variant<Fluid, LightItem, HeavyItem, FragileItem> package;

        std::visit(qx::visit_overload
            {
                [](const Fluid& )     { std::cout << "fluid\n"; },
                [](const LightItem& ) { std::cout << "light item\n"; },
                [](const auto&)       { std::cout << "default\n"; }
            },
            package);
    }
    
    @endcode 
**/
template<class... Ts>
struct visit_overload : Ts...
{
    using Ts::operator()...;
};

} // namespace qx
