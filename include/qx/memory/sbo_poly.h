/**

    @file      sbo_poly.h
    @author    Khrapov
    @date      20.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/memory/sbo_bytes.h>

#include <type_traits>

namespace qx
{

// Check that the derived type is suitable for storing in sbo_poly
template<class T, class base_t>
concept sbo_poly_assignable_c =
    std::is_base_of_v<base_t, T> && std::is_move_constructible_v<T> && std::is_destructible_v<T>;

// Check that the derived type fits into the SBO buffer
template<class sbo_poly_t, sbo_poly_assignable_c<typename sbo_poly_t::base_type> derived_t>
struct sbo_poly_fittable_type
{
    static constexpr bool value = sizeof(derived_t) <= sbo_poly_t::sbo_bytes_type::nBufferSize;
};

template<class sbo_poly_t, sbo_poly_assignable_c<typename sbo_poly_t::base_type> derived_t>
constexpr bool sbo_poly_fittable_type_v = sbo_poly_fittable_type<sbo_poly_t, derived_t>::value;

// If you have several inheritors, you can check that they all fit into your SBO
template<class sbo_poly_t, class... args_t>
struct sbo_poly_fittable_types
{
    static constexpr bool value = ((sbo_poly_fittable_type_v<sbo_poly_t, args_t>) && ...);
};

template<class sbo_poly_t, class... args_t>
constexpr bool sbo_poly_fittable_types_v = sbo_poly_fittable_types<sbo_poly_t, args_t...>::value;

/**

    @class   sbo_poly
    @brief   Small Buffer Object for polymorphic classes.
    @details If the inherited class fits into the specified buffer, it stores it in place;
             if not, it allocates memory for it.
             Allows you to increase cache locality when storing in containers.
    @tparam  base_t    - base class type, you'll be able to work with each element through its interface
    @tparam  nSBOSize_ - the size of the whole SBO type, including internal data
    @author  Khrapov
    @date    24.12.2025

**/
template<class base_t, size_t nSBOSize_>
class sbo_poly
{
    struct sbo_poly_traits
    {
        using size_type = size_t;
        static_assert(nSBOSize_ > sizeof(void*));
        static constexpr size_type nSBOSize              = nSBOSize_ - 2 * sizeof(void*);
        static constexpr bool      bShrinkToFitWhenSmall = true;
    };

public:
    using sbo_bytes_type = sbo_bytes<sbo_poly_traits>;
    using base_type      = base_t;

public:
    /**
        @brief  sbo_poly object constructor
        @tparam derived_t - type inherited from base_t
        @param  object    - an object to store
    **/
    template<sbo_poly_assignable_c<base_t> derived_t>
    sbo_poly(derived_t object) noexcept;

    sbo_poly(sbo_poly&& other) noexcept;
    ~sbo_poly() noexcept;

    /**
        @brief  operator=
        @tparam derived_t - type inherited from base_t
        @param  object    - an object to store
        @retval           - this object reference
    **/
    template<sbo_poly_assignable_c<base_t> derived_t>
    sbo_poly& operator=(derived_t object) noexcept;

    sbo_poly& operator=(sbo_poly&& other) noexcept;

    /**
        @brief  Assign a new object to this SBO
        @tparam derived_t - type inherited from base_t
        @param  object    - an object to store
    **/
    template<sbo_poly_assignable_c<base_t> derived_t>
    void assign(derived_t object) noexcept;


    base_t*       operator->() noexcept;
    const base_t* operator->() const noexcept;

    /**
        @brief  Get object reference. Always valid.
        @retval  - object reference
    **/
    base_t& get() noexcept;

    /**
        @brief  Get object reference. Always valid.
        @retval  - object reference
    **/
    const base_t& get() const noexcept;

private:
    sbo_bytes_type m_Data;
    void (*m_Assigner)(sbo_bytes_type& from, sbo_bytes_type& to) = nullptr;
    void (*m_Deleter)(sbo_bytes_type& object)                    = nullptr;
};

} // namespace qx

#include <qx/memory/sbo_poly.inl>
