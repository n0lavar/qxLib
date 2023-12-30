/**

    @file      return_value_iterator.h
    @author    Khrapov
    @date      2.12.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/patterns/contiguous_iterator/iterator.h>

namespace qx
{

/**

    @class   base_return_object_iterator
    @brief   This kind of iterator returns value and not reference in access methods
    @details ~
    @tparam  base_iterator_t - base iterator type
    @author  Khrapov
    @date    28.01.2023

**/
template<class base_iterator_t>
class base_return_object_iterator : public base_iterator_t
{
    using super_type = base_iterator_t;

public:
    using value_type      = typename super_type::value_type;
    using reference       = typename super_type::value_type;
    using const_reference = typename super_type::value_type;

public:
    using super_type::super_type;

    [[nodiscard]] constexpr typename super_type::value_type operator*() const noexcept
    {
        return super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::value_type operator[](typename super_type::size_type m) const noexcept
    {
        return super_type::get(m);
    }
};

template<class container_t>
class return_object_iterator
    : public base_return_object_iterator<iterator<container_t, return_object_iterator<container_t>>>
{
    using super_type = base_return_object_iterator<iterator<container_t, return_object_iterator>>;

public:
    using super_type::super_type;
};

template<class container_t>
class const_return_object_iterator
    : public base_return_object_iterator<const_iterator<container_t, const_return_object_iterator<container_t>>>
{
    using super_type = base_return_object_iterator<const_iterator<container_t, const_return_object_iterator>>;

public:
    using super_type::super_type;
};

template<class container_t>
class reverse_return_object_iterator
    : public base_return_object_iterator<reverse_iterator<container_t, reverse_return_object_iterator<container_t>>>
{
    using super_type = base_return_object_iterator<reverse_iterator<container_t, reverse_return_object_iterator>>;

public:
    using super_type::super_type;
};

template<class container_t>
class const_reverse_return_object_iterator
    : public base_return_object_iterator<
          const_reverse_iterator<container_t, const_reverse_return_object_iterator<container_t>>>
{
    using super_type =
        base_return_object_iterator<const_reverse_iterator<container_t, const_reverse_return_object_iterator>>;

public:
    using super_type::super_type;
};

} // namespace qx
