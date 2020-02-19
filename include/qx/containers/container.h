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

#define IMPL_CONTAINER(container)                                                                               \
                                                                                                                \
    using iterator       = qx::iterator<container, value_type>;                                                 \
    using const_iterator = qx::iterator<const container, const value_type>;                                     \
                                                                                                                \
    iterator            begin           (void)                      { return iterator(this, 0);             }   \
    iterator            end             (void)                      { return iterator(this, size());        }   \
    const_iterator      cbegin          (void)              const   { return const_iterator(this, 0);       }   \
    const_iterator      cend            (void)              const   { return const_iterator(this, size());  }   \
                                                                                                                \
    size_type           size            (void)              const;  /* implement */                             \
    bool                empty           (void)              const   { return size() == 0;                   }   \
    pointer             data            (void);                     /* implement */                             \
    const_pointer       data            (void)              const;  /* implement */                             \
    reference           at              (size_type  ind);           /* implement */                             \
    const_reference     at              (size_type  ind)    const   { return at(ind);                       }   \
    void                clear           (void);                     /* implement */