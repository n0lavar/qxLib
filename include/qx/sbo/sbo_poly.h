/**

    @file      sbo_poly.h
    @author    Khrapov
    @date      20.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/sbo/sbo_bytes.h>

#include <type_traits>

namespace qx
{

template<class T, class base_t>
concept sbo_poly_assignable_c = std::is_base_of_v<base_t, T> && std::is_move_constructible_v<T>;

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
        static constexpr size_type nSBOSize              = nSBOSize_ - sizeof(void*);
        static constexpr bool      bShrinkToFitWhenSmall = true;
    };

public:
    using sbo_bytes_type = sbo_bytes<sbo_poly_traits>;

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
};

} // namespace qx

#include <qx/sbo/sbo_poly.inl>
