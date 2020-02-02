//============================================================================
//
//!\file                         IContainer.h
//
//!\brief       Container interface
//!\details     ~
//
//!\author      Khrapov
//!\date        26.10.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <qx/containers/iterator.h>

#define IMPL_CONTAINER(container)                                                                                               \
public:                                                                                                                         \
    using iterator          = qx::iterator<container, T>;                                                                       \
    using const_iterator    = qx::iterator<const container, const T>;                                                           \
                                                                                                                                \
public:                                                                                                                         \
    iterator            begin           (void)                      { return iterator(this, 0);             }                   \
    iterator            end             (void)                      { return iterator(this, size());        }                   \
    const_iterator      cbegin          (void)              const   { return const_iterator(this, 0);       }                   \
    const_iterator      cend            (void)              const   { return const_iterator(this, size());  }                   \
                                                                                                                                \
    size_type           size            (void)              const;                                              /* implement */ \
    bool                empty           (void)              const   { return size() == 0;                   }                   \
    const_pointer       data            (void)              const;                                              /* implement */ \
    pointer             data            (void);                                                                                 \
    reference           operator[]      (size_type  ind);                                                       /* implement */ \
    const_reference     operator[]      (size_type  ind)    const   { return operator[](ind);               }                   \
                                                                                                                                \
    void                clear           (void);                                                                                 \
                                                                                                                                \
private:
