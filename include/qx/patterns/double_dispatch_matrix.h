/**

    @file      double_dispatch_matrix.h
    @author    Khrapov
    @date      17.01.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/patterns/singleton.h>
#include <qx/rtti/rtti.h>
#include <qx/rtti/rtti_cast.h>
#include "qx/meta/type_traits.h"

#include <algorithm>
#include <concepts>
#include <functional>
#include <optional>

namespace qx
{

template<auto method_ptr_t>
struct double_dispatch_class_method_ptr_traits;

template<class class_t, class return_t, return_t (class_t::*method_ptr_t)(const class_t&) const>
struct double_dispatch_class_method_ptr_traits<method_ptr_t>
{
    using class_type  = class_t;
    using return_type = return_t;
};

/**

    @class   double_dispatch_matrix
    @brief   A class that implements the double dispatch mechanism in C++.
    @details This class allows users to add their classes dynamically,
             so you must call check_matrix_completeness() after register_function()
    @tparam  method_ptr_t - a base class method that takes another object of this class.
                            the class must use QX_OBJECT, e.g. use qx rtti system.
    @code
    class shape : public base
    {
        QX_OBJECT(base, shape);

    public:
        bool intersects(const shape& other) const;
    };

    using shape_intersection_double_dispatch_t = qx::double_dispatch_matrix<&shape::intersects>;

    class circle : public shape
    {
        ...
    };

    class square : public shape
    {
        ...
    };

    QX_CALL_BEFORE_MAIN = []()
    {
        auto& matrix = shape_intersection_double_dispatch_t::get_instance();
        matrix.register_function(...);
        matrix.register_function(...);
        ...
        QXE_EXPECT(matrix.check_matrix_completeness());
    };
    @author  Khrapov
    @date    16.02.2025

**/
template<auto method_ptr_t>
    requires is_specialization_exist_v<double_dispatch_class_method_ptr_traits<method_ptr_t>>
class double_dispatch_matrix
{
    QX_SINGLETON(double_dispatch_matrix);

    using class_method_ptr_traits_type = double_dispatch_class_method_ptr_traits<method_ptr_t>;

public:
    using base_type     = typename class_method_ptr_traits_type::class_type;
    using return_type   = typename class_method_ptr_traits_type::return_type;
    using function_type = std::function<return_type(const base_type& first, const base_type& second)>;

    static_assert(std::derived_from<base_type, rtti_pure_base>);

    /**
        @brief   Add a function to a matrix
        @details If there was a function it will be overriden
        @tparam  first_derived_t  - the first type for a double dispatching
        @tparam  second_derived_t - the second type for a double dispatching, can be same as first_derived_t
        @param   function         - a function that takes objects of types
                                    first_derived_t and second_derived_t and returns return_type
    **/
    template<class first_derived_t, class second_derived_t>
        requires(
            std::is_base_of_v<typename double_dispatch_matrix<method_ptr_t>::base_type, first_derived_t>
            && std::is_base_of_v<typename double_dispatch_matrix<method_ptr_t>::base_type, second_derived_t>)
    void register_function(
        std::function<return_type(const first_derived_t&, const second_derived_t&)> function) noexcept;

    /**
        @brief  Call a function if there is any
        @param  first  - first object
        @param  second - second object
        @retval        - a return value if a function for these types found, std::nullopt otherwise
    **/
    std::optional<return_type> invoke(const base_type& first, const base_type& second);

    /**
        @brief  Check that for each registered type there is a match to all other types,
                including the type itself, and that all these functions are valid. 
        @retval  - true if this symmetric matrix is complete
    **/
    bool check_matrix_completeness() const noexcept;

private:
    /**
        @brief  Get or create a function for two types
        @param  first  - first type
        @param  second - second type (can be same as the first type)
        @retval        - function
    **/
    function_type& get_function(class_id first, class_id second) noexcept;

private:
    std::unordered_map<class_id, std::unordered_map<class_id, function_type>> m_MatrixFunctions;
};

} // namespace qx

#include <qx/patterns/double_dispatch_matrix.inl>
