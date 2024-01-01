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

#include <qx/containers/string/string_literal.h>

namespace qx
{

/**

    @class   rtti_naming_strategy_nullptr
    @brief   Returns null string_view in get_name
    @details Does not lead to storing the string in static memory in the release build,
             even if it is specified in the template argument
    @tparam  ClassName - class name literal
    @author  Khrapov
    @date    10.09.2021

**/
template<string_literal ClassName>
class rtti_naming_strategy_nullptr
{
public:
    static constexpr string_view get_name() noexcept
    {
        return nullptr;
    }
};

/**

    @class   rtti_naming_strategy_empty
    @brief   Returns empty string_view in get_name: { '\0' }
    @details Does not lead to storing the string in static memory in the release build,
             even if it is specified in the template argument
    @tparam  ClassName - class name literal
    @author  Khrapov
    @date    10.09.2021

**/
template<string_literal ClassName>
class rtti_naming_strategy_empty
{
public:
    static constexpr string_view get_name() noexcept
    {
        return QX_TEXT("");
    }
};

/**

    @class   rtti_naming_strategy_class_name
    @brief   Returns class name string_view in get_name
    @details ~
    @tparam  ClassName - class name literal
    @author  Khrapov
    @date    10.09.2021

**/
template<string_literal ClassName>
class rtti_naming_strategy_class_name
{
public:
    static constexpr string_view get_name() noexcept
    {
        return ClassName.view();
    }
};

} // namespace qx
