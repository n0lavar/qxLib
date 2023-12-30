/**

    @file      iterator.h
    @author    Khrapov
    @date      2.12.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/patterns/contiguous_iterator/base_iterator.h>

namespace qx
{

template<class container_t, class derived_t = void>
class const_iterator;

/**

    @class   iterator
    @brief   Non-const random access iterator type
    @details Use it for range-based loops and std algorithms
             container_t have to provide at(size_t)
    @tparam  container_t - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class container_t, class derived_t = void>
class iterator
    : public base_forward_iterator<
          container_t,
          std::conditional_t<std::same_as<derived_t, void>, iterator<container_t>, derived_t>>
{
    friend class const_iterator<container_t, derived_t>;

    using super_type =
        base_forward_iterator<container_t, std::conditional_t<std::same_as<derived_t, void>, iterator, derived_t>>;

public:
    using super_type::super_type;

    [[nodiscard]] constexpr typename super_type::reference operator*() const noexcept
    {
        return super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::pointer operator->() const noexcept
    {
        return &super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::reference operator[](typename super_type::size_type i) const noexcept
    {
        return super_type::get(i);
    }
};

/**

    @class   const_iterator
    @brief   Const random access iterator type
    @details Use it for range-based loops and std algorithms
             container_t have to provide at(size_t)
    @tparam  container_t - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class container_t, class derived_t>
class const_iterator
    : public base_forward_iterator<
          const container_t,
          std::conditional_t<std::same_as<derived_t, void>, const const_iterator<container_t>, derived_t>>
{
    using super_type = base_forward_iterator<
        const container_t,
        std::conditional_t<std::same_as<derived_t, void>, const const_iterator, derived_t>>;

public:
    using super_type::super_type;

    constexpr const_iterator(const iterator<container_t>& it) noexcept : super_type(it.m_pContainer, it.m_nIndex)
    {
    }
    [[nodiscard]] constexpr typename super_type::const_reference operator*() const noexcept
    {
        return super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::const_pointer operator->() const noexcept
    {
        return &super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::const_reference operator[](
        typename super_type::size_type m) const noexcept
    {
        return super_type::get(m);
    }
};

template<class container_t, class derived_t = void>
class const_reverse_iterator;

/**

    @class   reverse_iterator
    @brief   Non-const random access reverse iterator type
    @details Use it for range-based loops and std algorithms
             container_t have to provide at(size_t)
    @tparam  container_t - container type
    @author  Khrapov
    @date    27.07.2019

**/
template<class container_t, class derived_t = void>
class reverse_iterator
    : public base_reverse_iterator<
          container_t,
          std::conditional_t<std::same_as<derived_t, void>, reverse_iterator<container_t>, derived_t>>
{
    friend class const_reverse_iterator<container_t>;

    using super_type = base_reverse_iterator<
        container_t,
        std::conditional_t<std::same_as<derived_t, void>, reverse_iterator, derived_t>>;

public:
    using super_type::super_type;

    [[nodiscard]] constexpr typename super_type::reference operator*() const noexcept
    {
        return super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::pointer operator->() const noexcept
    {
        return &super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::reference operator[](typename super_type::size_type m) const noexcept
    {
        return super_type::get(m);
    }
};

/**

    @class   const_reverse_iterator
    @brief   Const reverse random access iterator type
    @details Use it for range-based loops and std algorithms
             container_t have to provide at(size_t)
    @tparam  container_t - container type
    @author  Khrapov
    @date    19.03.2020

**/
template<class container_t, class derived_t>
class const_reverse_iterator
    : public base_reverse_iterator<
          const container_t,
          std::conditional_t<std::same_as<derived_t, void>, const const_reverse_iterator<container_t>, derived_t>>
{
    using super_type = base_reverse_iterator<
        const container_t,
        std::conditional_t<std::same_as<derived_t, void>, const const_reverse_iterator, derived_t>>;

public:
    using super_type::super_type;

    constexpr const_reverse_iterator(const reverse_iterator<container_t>& it) noexcept
        : super_type(it.m_pContainer, it.m_nIndex)
    {
    }
    [[nodiscard]] constexpr typename super_type::const_reference operator*() const noexcept
    {
        return super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::const_pointer operator->() const noexcept
    {
        return &super_type::get();
    }
    [[nodiscard]] constexpr typename super_type::const_reference operator[](
        typename super_type::size_type m) const noexcept
    {
        return super_type::get(m);
    }
};

} // namespace qx
