/**

    @file      generic_span.h
    @brief     Contains qx::generic_span class
    @details   ~
    @author    Khrapov
    @date      20.11.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <functional>

namespace qx
{

struct default_generic_span_traits
{
    template<class... Args>
    using function_type = std::function<Args...>;
};

/**

    @class   generic_span
    @brief   Same as std::span, but may be used with containers with forward iterators
    @details The class can be used to use any container to iterate over its elements
             Useful when used in virtual methods
             Does not own the container
             The container should not be changed until the end of the iteration
             May be much slower then std::span
    @tparam  T - container value type
    @author  Khrapov
    @date    20.11.2022

**/
template<class T, class Traits = default_generic_span_traits>
class generic_span
{
public:
    using traits_type = Traits;
    template<class... Args>
    using function_type  = typename Traits::template function_type<Args...>;
    using generator_type = function_type<T*()>;

    template<class Container>
    using container_value = decltype(*std::declval<Container>().begin());

    using element_type    = T;
    using value_type      = std::remove_cv_t<T>;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;

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
        constexpr iterator(generator_type generator) noexcept;
        [[nodiscard]] constexpr reference operator*() const noexcept;
        [[nodiscard]] constexpr pointer   operator->() const noexcept;
        constexpr iterator&               operator++() noexcept;
        [[nodiscard]] constexpr iterator  operator++(int) noexcept;
        constexpr bool                    operator!=(const iterator& r) const noexcept;
        constexpr bool                    operator==(const iterator& r) const noexcept;
        constexpr                         operator void*() noexcept;

    private:
        generator_type m_Generator;
    };

public:
    /**
        @brief generic_span object constructor
    **/
    generic_span() noexcept = default;

    /**
        @brief generic_span object constructor
        @param  - other span
    **/
    generic_span(generic_span&&) noexcept = default;

    /**
        @brief generic_span object constructor
        @param  - other span
    **/
    generic_span(const generic_span&) noexcept = default;

    /**
        @brief  generic_span object constructor
        @tparam Container - any container, which adapter satisfies forward iterator concept
        @param  container - container instance. container must not be edited until adapter death
    **/
    template<class Container>
    generic_span(Container& container) noexcept;

    /**
        @brief  generic_span object constructor
        @tparam Container    - any container, which adapter satisfies forward iterator concept
        @param  container    - container instance. container must not be edited until adapter death
        @param  valueAdapter - function which transforms Container::value_type to T*
    **/
    template<class Container>
    generic_span(Container& container, function_type<pointer(container_value<Container>&)> valueAdapter) noexcept;

    /**
        @brief  generic_span object constructor
        @tparam Container    - any container, which adapter satisfies forward iterator concept
        @param  container    - container instance. container must not be edited until adapter death
        @param  valueAdapter - function which transforms Container::value_type to T*
    **/
    template<class Container>
    generic_span(const Container& container, function_type<pointer(container_value<Container>&)> valueAdapter) noexcept;

    /**
        @brief  operator=
        @tparam Container - any container, which adapter satisfies forward iterator concept
        @param  container - container instance. container must not be edited until adapter death
        @retval           - this object reference
    **/
    template<class Container>
    generic_span& operator=(Container& container) noexcept;

    /**
        @brief  operator=
        @param   - other span
        @retval  - this object reference
    **/
    generic_span& operator=(generic_span&&) noexcept = default;

    /**
        @brief  operator=
        @param   - other span
        @retval  - this object reference
    **/
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
        @tparam Container - any container, which adapter satisfies forward iterator concept
        @tparam Adapter   - adapter callable type
        @param  container - container instance. container must not be edited until adapter death
        @param  adapter   - function which transforms Container::value_type to T*
        @retval           - values generator
    **/
    template<class Container, class Adapter>
    static generator_type create_initial_generator(Container&& container, Adapter adapter) noexcept;

private:
    generator_type m_InitialGenerator;
};

} // namespace qx

#include <qx/patterns/generic_span.inl>
