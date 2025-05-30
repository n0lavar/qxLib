/**

    @file      link.h
    @author    Khrapov
    @date      21.11.2021
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/copyable_movable.h>

#include <cstddef>
#include <memory>

namespace qx
{

/**

    @class   link
    @brief   std::weak_ptr wrapper that do not allow you 
             to create strong pointer (std::shared_ptr)
    @tparam  T - pointer class type
    @author  Khrapov
    @date    21.11.2021

**/
template<class T>
class link
{
    // friend templated link class
    friend class link;

public:
    /**

        @class   lock_ptr
        @brief   std::shared_ptr wrapper 
        @author  Khrapov
        @date    23.11.2021

    **/
    class lock_ptr
    {
        // private constructor
        friend class link;

        // friend templated lock_ptr class
        friend class lock_ptr;

    public:
        QX_NONCOPYMOVABLE(lock_ptr);

        T* operator->() const noexcept;
        T& operator*() const noexcept;

        /**
            @brief  Get object pointer
            @retval - T object pointer
        **/
        T* get() const noexcept;

        /**
            @brief  Is object presents
            @retval - true if object presents
        **/
        explicit operator bool() const noexcept;

        /**
            @brief  operator==
            @tparam U     - lock_ptr with pointer convertible to T
            @param  other - other link_ptr
            @retval       - true, if objects are equal
        **/
        template<class U>
        bool operator==(const U& other) const noexcept;

        /**
            @brief  operator<=>
            @tparam U     - lock_ptr with pointer convertible to T
            @param  other - other link_ptr
            @retval       - three-way comparison result
        **/
        template<class U>
        std::strong_ordering operator<=>(const U& other) const noexcept;

    private:
        /**
            @brief lock_ptr object constructor
            @param pShared - object strong pointer
        **/
        lock_ptr(std::shared_ptr<T> pShared) noexcept;

    private:
        std::shared_ptr<T> m_pRaw;
    };

public:
    link() noexcept = default;

    /**
        @brief  link object constructor
        @tparam U     - T or type convertible to T
        @param  pWeak - weak object pointer
    **/
    template<class U>
    link(const std::weak_ptr<U>& pWeak) noexcept;

    /**
        @brief link object constructor
        @param pWeak - weak object pointer
    **/
    link(std::weak_ptr<T> pWeak) noexcept;

    /**
        @brief  link object constructor
        @tparam U       - T or type convertible to T
        @param  pStrong - strong object pointer
    **/
    template<class U>
    link(const std::shared_ptr<U>& pStrong) noexcept;

    // I don't want to take the ownership. What if it's the last shared ptr alive?
    // Use std::as_const(pStrong) if you are sure it's not.
    template<class U>
    link(std::shared_ptr<U>&& pStrong) noexcept = delete;

    /**
        @brief  link object constructor
        @tparam U     - T or type convertible to T
        @param  pLink - other link
    **/
    template<class U>
    link(const link<U>& pLink) noexcept;

    /**
        @brief  operator=
        @tparam U     - T or type convertible to T
        @param  pLink - other link 
        @retval       - this object reference
    **/
    template<class U>
    link& operator=(const link<U>& pLink) noexcept;

    /**
        @brief  link object constructor
        @tparam U     - T or type convertible to T
        @param  pLink - other link rvalue ref
    **/
    template<class U>
    link(link<U>&& pLink) noexcept;

    /**
        @brief  operator=
        @tparam U     - T or type convertible to T
        @param  pLink - other link rvalue ref
        @retval       - this object reference
    **/
    template<class U>
    link& operator=(link<U>&& pLink) noexcept;

    /**
        @brief link object constructor
        @param  - nullptr
    **/
    link(std::nullptr_t) noexcept;

    /**
        @brief  Lock and return strong pointer
        @retval - strong pointer
    **/
    lock_ptr lock() const noexcept;

    /**
        @brief Reset weak pointer
    **/
    void reset() noexcept;

    /**
        @brief  If pointer is expired
        @retval - true if pointer is expired
    **/
    bool expired() const noexcept;

    /**
        @brief  If pointer is expired
        @retval - true if pointer is expired
    **/
    explicit operator bool() const noexcept;

    template<class U>
    bool operator==(const link<U>&) const noexcept = delete;
    template<class U>
    bool operator!=(const link<U>&) const noexcept = delete;

private:
    std::weak_ptr<T> m_pWeak;
};

} // namespace qx

#include <qx/smart_ptr/link.inl>
