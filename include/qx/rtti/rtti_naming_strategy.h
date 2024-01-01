/**

    @file      rtti_naming_strategy.h
    @brief     Contains naming strategies for qx::rtti_root class
    @details   The naming strategy determines what will be returned
               by get_class_id_static()
    @author    Khrapov
    @date      9.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

namespace qx
{

/**
    @struct  rtti_naming_strategy_empty
    @brief   Returns empty string_view in get_name: { '\0' }
    @details Does not lead to storing the string in static memory in the release build,
             even if it is specified in the template argument
    @author  Khrapov
    @date    10.09.2021
**/
struct rtti_naming_strategy_empty
{
    static constexpr string_view get_name(string_view) noexcept
    {
        return QX_TEXT("");
    }
};

/**
    @struct rtti_naming_strategy_class_name
    @brief  Returns class name string_view in get_name
    @author Khrapov
    @date   10.09.2021
**/
struct rtti_naming_strategy_class_name
{
    static constexpr string_view get_name(string_view svName) noexcept
    {
        return svName;
    }
};

} // namespace qx
