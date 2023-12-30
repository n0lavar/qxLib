/**

    @file      dereference_iterator.h
    @author    Khrapov
    @date      2.12.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/patterns/contiguous_iterator/iterator.h>

namespace qx
{

/**

    @class   base_dereference_iterator
    @brief   
    @details ~
    @tparam  base_iterator_t - 
    @author  Khrapov
    @date    2.12.2023

**/
template<class base_iterator_t>
    requires std::is_pointer_v<typename base_iterator_t::value_type>
class base_dereference_iterator : public base_iterator_t
{
    using super_type = base_iterator_t;

public:
    using value_type      = std::remove_pointer_t<typename base_iterator_t::value_type>;
    using pointer         = value_type*;
    using const_pointer   = const value_type;
    using reference       = value_type&;
    using const_reference = const value_type&;

public:
    using super_type::super_type;

    [[nodiscard]] constexpr reference operator*() const noexcept
    {
        return *super_type::get();
    }
    [[nodiscard]] constexpr pointer operator->() const noexcept
    {
        return super_type::get();
    }
    [[nodiscard]] constexpr reference operator[](typename super_type::size_type m) const noexcept
    {
        return *super_type::get(m);
    }
};

template<class container_t>
class dereference_iterator : public base_dereference_iterator<iterator<container_t, dereference_iterator<container_t>>>
{
    using super_type = base_dereference_iterator<iterator<container_t, dereference_iterator>>;

public:
    using super_type::super_type;
};

template<class container_t>
class const_dereference_iterator
    : public base_dereference_iterator<const_iterator<container_t, const_dereference_iterator<container_t>>>
{
    using super_type = base_dereference_iterator<const_iterator<container_t, const_dereference_iterator>>;

public:
    using super_type::super_type;
};

template<class container_t>
class reverse_dereference_iterator
    : public base_dereference_iterator<reverse_iterator<container_t, reverse_dereference_iterator<container_t>>>
{
    using super_type = base_dereference_iterator<reverse_iterator<container_t, reverse_dereference_iterator>>;

public:
    using super_type::super_type;
};

template<class container_t>
class const_reverse_dereference_iterator
    : public base_dereference_iterator<
          const_reverse_iterator<container_t, const_reverse_dereference_iterator<container_t>>>
{
    using super_type =
        base_dereference_iterator<const_reverse_iterator<container_t, const_reverse_dereference_iterator>>;

public:
    using super_type::super_type;
};

} // namespace qx
