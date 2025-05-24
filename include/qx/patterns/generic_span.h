/**

    @file      generic_span.h
    @author    Khrapov
    @date      20.11.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/meta/qualifiers.h>

#include <functional>

namespace qx
{

struct default_generic_span_traits
{
    template<class... args_t>
    using function_type = std::function<args_t...>;
};

/**

    @class   generic_span
    @brief   Same as std::span, but may be used with any container with forward iterators
    @details The class can be used to use any container to iterate over its elements
             Useful when used in virtual methods
             Does not own the container
             The container should not be changed until the end of the iteration
             May be much slower then std::span when the size of sbo of std::function
             is smaller then sizeof 2 iterators of this container
             (libcpp: 16, ligcxx: 16, MSVC: 56)
    @tparam  T - container value type
    @author  Khrapov
    @date    20.11.2022

**/
template<class T, class traits_t = default_generic_span_traits>
class generic_span
{
    template<class container_t>
    using container_value = std::remove_reference_t<decltype(*std::declval<container_t>().begin())>;

    template<class target_t>
    using qualified_type = copy_qualifiers_t<std::remove_reference_t<std::remove_pointer_t<T>>, target_t>;

public:
    using traits = traits_t;
    template<class... args_t>
    using function_type  = typename traits_t::template function_type<args_t...>;
    using generator_type = function_type<T*()>;

    using element_type = T;
    using value_type   = std::remove_cv_t<T>;
    using pointer      = T*;
    using reference    = T&;

    class iterator
    {
    public:
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
        using difference_type   = std::ptrdiff_t;
        using size_type         = size_t;
        using iterator_category = std::forward_iterator_tag;
        using iterator_concept  = std::forward_iterator_tag;

    public:
        constexpr iterator() noexcept                = default;
        constexpr iterator(const iterator&) noexcept = default;
        constexpr iterator(generator_type generator, size_type nIndex) noexcept;
        [[nodiscard]] constexpr reference operator*() const noexcept;
        [[nodiscard]] constexpr pointer   operator->() const noexcept;
        constexpr iterator&               operator++() noexcept;
        [[nodiscard]] constexpr iterator  operator++(int) noexcept;
        constexpr bool                    operator!=(const iterator& r) const noexcept;
        constexpr bool                    operator==(const iterator& r) const noexcept;
        constexpr                         operator void*() const noexcept;

    private:
        generator_type m_Generator;
        size_type      m_nIndex = 0;
    };

public:
    generic_span() noexcept                    = default;
    generic_span(generic_span&&) noexcept      = default;
    generic_span(const generic_span&) noexcept = default;

    /**
        @brief  generic_span object constructor
        @tparam container_t - any container, which adapter satisfies forward iterator concept
        @param  container   - container instance. container must not be edited until adapter death
    **/
    template<class container_t>
    generic_span(container_t& container) noexcept;

    /**
        @brief  generic_span object constructor
        @tparam container_t  - any container, which adapter satisfies forward iterator concept
        @param  container    - container instance. container must not be edited until adapter death
        @param  valueAdapter - function which transforms Container::value_type to T*
    **/
    template<class container_t>
    generic_span(
        container_t&                                                            container,
        function_type<reference(qualified_type<container_value<container_t>>&)> valueAdapter) noexcept;

    /**
        @brief  operator=
        @tparam container_t - any container, which adapter satisfies forward iterator concept
        @param  container   - container instance. container must not be edited until adapter death
        @retval             - this object reference
    **/
    template<class container_t>
    generic_span& operator=(container_t& container) noexcept;

    generic_span& operator=(generic_span&&) noexcept      = default;
    generic_span& operator=(const generic_span&) noexcept = default;

    /**
        @brief  Check if span is empty
        @retval  - true if empty
    **/
    bool empty() const noexcept;

    /**
        @brief  Return iterator to beginning
        @retval  - iterator to beginning
    **/
    iterator begin() const noexcept;

    /**
        @brief  Return iterator to end
        @retval  - iterator to end
    **/
    iterator end() const noexcept;

    /**
        @brief  Return const iterator to beginning
        @retval  - const iterator to beginning
    **/
    iterator cbegin() const noexcept;

    /**
        @brief  Return const iterator to end
        @retval  - const iterator to end
    **/
    iterator cend() const noexcept;

private:
    /**
        @brief  Create initial generator
        @tparam container_t - any container, which adapter satisfies forward iterator concept
        @tparam adapter_t   - adapter callable type
        @param  container   - container instance. container must not be edited until adapter death
        @param  adapter     - function which transforms Container::value_type to T*
        @retval             - values generator
    **/
    template<class container_t, class adapter_t>
    static generator_type create_initial_generator(container_t&& container, adapter_t adapter) noexcept;

private:
    generator_type m_InitialGenerator;
};

} // namespace qx

#include <qx/patterns/generic_span.inl>
