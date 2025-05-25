/**

    @file      double_dispatch_matrix.inl
    @author    Khrapov
    @date      17.01.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<auto method_ptr_t>
    requires is_specialization_exist_v<double_dispatch_class_method_ptr_traits<method_ptr_t>>
template<class first_derived_t, class second_derived_t>
    requires(
        std::is_base_of_v<typename double_dispatch_matrix<method_ptr_t>::base_type, first_derived_t>
        && std::is_base_of_v<typename double_dispatch_matrix<method_ptr_t>::base_type, second_derived_t>)
void double_dispatch_matrix<method_ptr_t>::register_function(
    std::function<return_type(const first_derived_t&, const second_derived_t&)> function) noexcept
{
    get_function(first_derived_t::get_class_id_static(), second_derived_t::get_class_id_static()) = function_type(
        [function_ = std::move(function)](const base_type& first, const base_type& second)
        {
            const first_derived_t* first_as_first_derived_t = rtti_cast<const first_derived_t>(first);
            if (first_as_first_derived_t)
            {
                return function_(*first_as_first_derived_t, static_cast<const second_derived_t&>(second));
            }

            return function_(static_cast<const first_derived_t&>(second), static_cast<const second_derived_t&>(first));
        });
}

template<auto method_ptr_t>
    requires is_specialization_exist_v<double_dispatch_class_method_ptr_traits<method_ptr_t>>
std::optional<typename double_dispatch_matrix<method_ptr_t>::return_type> double_dispatch_matrix<method_ptr_t>::invoke(
    const base_type& first,
    const base_type& second)
{
    if (function_type& function = get_function(first.get_class_id(), second.get_class_id()))
        return function(first, second);
    else
        return std::nullopt;
}

template<auto method_ptr_t>
    requires is_specialization_exist_v<double_dispatch_class_method_ptr_traits<method_ptr_t>>
bool double_dispatch_matrix<method_ptr_t>::check_matrix_completeness() const noexcept
{
    size_t nTotalElements = 0;
    return std::ranges::all_of(
               m_MatrixFunctions,
               [&nTotalElements](const auto& pair)
               {
                   nTotalElements += pair.second.size();
                   return std::ranges::all_of(
                       pair.second,
                       [](const auto& pair)
                       {
                           return static_cast<bool>(pair.second);
                       });
               })
           && nTotalElements == (m_MatrixFunctions.size() * m_MatrixFunctions.size() + m_MatrixFunctions.size()) / 2;
}

template<auto method_ptr_t>
    requires is_specialization_exist_v<double_dispatch_class_method_ptr_traits<method_ptr_t>>
typename double_dispatch_matrix<method_ptr_t>::function_type& double_dispatch_matrix<method_ptr_t>::get_function(
    class_id first,
    class_id second) noexcept
{
    const class_id first_in_container  = std::min(first, second);
    const class_id second_in_container = std::max(first, second);
    return m_MatrixFunctions[first_in_container][second_in_container];
}

} // namespace qx
