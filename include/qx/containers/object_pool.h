//============================================================================
//
//!\file                        object_pool.h
//
//!\brief       Contains object_pool class
//!\details     ~
//
//!\author      Khrapov
//!\date        27.07.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <vector>

#include <qx/containers/container.h>
#include <qx/other/useful_macros.h>

namespace qx
{

//============================================================================
//
//!\class                       object_pool<T>
//
//!\brief   The pool contains a collection of reusable objects
//!\details When the pool is initialized, it immediately creates
//          the entire collection of objects
//          (allocating one consecutive chunk of memory)
//          and initializes them all with the “not used” state.
//          When you need a new object, you request it from the pool.
//          It searches for an accessible object, initializes it with the value "used"
//          and returns. When the object is no longer needed,
//          it returns to the "unused" state again.
//          In this way, objects can be freely created
//          and deleted without having to allocate memory or other resources.
//
//!\author  Khrapov
//!\date    27.07.2019
//
//============================================================================
template <class T>
class object_pool
{
public:

    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;

    IMPL_CONTAINER(object_pool)

public:
                                object_pool (void) { };
                                object_pool (size_type              startSize   = 0,
                                             size_type              incSize     = 10);

    template<class ... Args>
    size_type                   Emplace     (Args&&...              args);
    void                        Delete      (size_type              id);
    const std::vector<size_type> & GetIdsArray (void);

private:
    size_t                      GetId       (size_type              ind);

private:
    std::vector<T>          m_Pool;
    std::vector<size_type>  m_Indexes;
    std::vector<size_type>  m_Ids;

    size_type               m_nFirstFreeObjInd  = 0;
    size_type               m_nIncreaceSizeStep = 0;
};

}

#include <qx/containers/object_pool.inl>
