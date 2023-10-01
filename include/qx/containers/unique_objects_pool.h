/**

    @file      unique_objects_pool.h
    @author    Khrapov
    @date      11.02.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/internal/perf_scope.h>
#include <qx/macros/suppress_warnings.h>
#include <qx/typedefs.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index_container.hpp>
QX_POP_SUPPRESS_WARNINGS();

#include <algorithm>
#include <mutex>
#include <shared_mutex>

QX_DEFINE_CATEGORY(CatUniqueObjectsPool, qx::color::honeydew());

namespace qx
{

/**

    @class   unique_objects_pool
    @brief   Class stores unique objects and allows access to them through tokens
    @details Class is thread safe
    @tparam  T - object type
    @author  Khrapov
    @date    11.02.2023

**/
template<class T>
class unique_objects_pool
{
    struct data
    {
        T   value;
        u64 nId      = 0;
        u64 nCounter = 0;
    };

    struct value_tag;
    struct id_tag;

    using values_set = boost::multi_index_container<
        data,
        boost::multi_index::indexed_by<
            boost::multi_index::
                hashed_unique<boost::multi_index::tag<value_tag>, boost::multi_index::member<data, T, &data::value> >,
            boost::multi_index::
                hashed_unique<boost::multi_index::tag<id_tag>, boost::multi_index::member<data, u64, &data::nId> > > >;

    using data_by_value = typename boost::multi_index::index<values_set, value_tag>::type;
    using data_by_id    = typename boost::multi_index::index<values_set, id_tag>::type;

public:
    /**

        @class   token
        @brief   The token is used for distributed access to a unique object in the pool
        @details Class is thread safe
        @author  Khrapov
        @date    11.02.2023

    **/
    class token
    {
        friend unique_objects_pool;

        static constexpr u64 kInvalidId = static_cast<u64>(-1);

    public:
        token() noexcept = default;
        token(const token& otherToken) noexcept;
        token(token&& otherToken) noexcept;

        token& operator=(const token& otherToken) noexcept;
        token& operator=(token&& otherToken) noexcept;

        ~token() noexcept;

        /**
            @brief   Is this token have been set (not default)
            @warning This method does not check if the pool of this object is alive
            @retval  - true if this object is valid
        **/
        bool is_valid() const noexcept;

        /**
            @brief  Same as is_valid()
            @retval  - true if this object is valid
        **/
        explicit operator bool() const noexcept;

        const T& operator*() const noexcept;
        const T* operator->() const noexcept;
        bool     operator==(const token& other) const noexcept;

    private:
        /**
            @brief token object constructor
            @param nId   - object id
            @param pPool - pool pointer
        **/
        token(u64 nId, unique_objects_pool* pPool) noexcept;

    private:
        u64                  m_nId   = kInvalidId;
        unique_objects_pool* m_pPool = nullptr;
    };

public:
    /**
        @brief unique_objects_pool object constructor
        @param bAutoCleanup - if true, objects will be deleted when usages count reaches 0, otherwise you should use shrink()
    **/
    unique_objects_pool(bool bAutoCleanup = true) noexcept;

    /**
        @brief  Get or create object
        @tparam U     - value type
        @param  value - object to search and to construct if wasn't able to find
        @retval       - token to existing or constructed object
    **/
    template<class U>
    token get_or_create(U&& value) noexcept;

    /**
        @brief Remove unused (with counter = 0) objects
    **/
    void shrink();

    /**
        @brief  Get number of objects stored
        @retval  - number of objects stored
    **/
    size_t size() const;

    /**
        @brief  Is pool empty
        @retval  - true if pool is empty
    **/
    bool empty() const;

private:
    /**
        @brief Increase the usage counter of the object with the specified id
        @param nId - object id
    **/
    void increase_counter(u64 nId) noexcept;

    /**
        @brief Decrease the usage counter of the object with the specified id
        @param nId - object id
    **/
    void decrease_counter(u64 nId) noexcept;

    /**
        @brief  Get value of the object with the specified id
        @param  nId - object id
        @retval     - object value
    **/
    const T& get_value(u64 nId) noexcept;

private:
    const bool m_bAutoShrink = true;

    QX_PERF_SHARED_MUTEX(m_UniqueObjectsPoolMutex);
    values_set m_Pool;
    u64        m_nCurrentId = 1;
};

} // namespace qx

#include <qx/containers/unique_objects_pool.inl>
