//==============================================================================
//
//!\file                         container.h
//
//!\brief       Contains macro for sequence containers with common functions
//!\details     ~
//
//!\author      Khrapov
//!\date        26.10.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/containers/iterator.h>

#define IMPL_CONTAINER(container)                                                                                                       \
                                                                                                                                        \
    using iterator                  = qx::iterator<container>;                                                                          \
    using const_iterator            = qx::const_iterator<container>;                                                                    \
    using reverse_iterator          = qx::reverse_iterator<container>;                                                                  \
    using const_reverse_iterator    = qx::const_reverse_iterator<container>;                                                            \
                                                                                                                                        \
    iterator                begin   (void)                noexcept { return iterator(this, 0);                                        } \
    iterator                end     (void)                noexcept { return iterator(this, size());                                   } \
    const_iterator          cbegin  (void)          const noexcept { return const_iterator(this, 0);                                  } \
    const_iterator          cend    (void)          const noexcept { return const_iterator(this, size());                             } \
    reverse_iterator        rbegin  (void)                noexcept { return reverse_iterator(this, size() - 1);                       } \
    reverse_iterator        rend    (void)                noexcept { return reverse_iterator(this, static_cast<size_type>(-1));       } \
    const_reverse_iterator  crbegin (void)          const noexcept { return const_reverse_iterator(this, size() - 1);                 } \
    const_reverse_iterator  crend   (void)          const noexcept { return const_reverse_iterator(this, static_cast<size_type>(-1)); } \
                                                                                                                                        \
    size_type               size    (void)          const noexcept;/* implement */                                                      \
    bool                    empty   (void)          const noexcept { return size() == 0;                                              } \
    pointer                 data    (void)                noexcept; /* implement */                                                     \
    const_pointer           data    (void)          const noexcept { return const_cast<container*>(this)->data();                     } \
    reference               at      (size_type ind)       noexcept; /* implement */                                                     \
    const_reference         at      (size_type ind) const noexcept { return const_cast<container*>(this)->at(ind);                    } \
    void                    clear   (void)                noexcept; /* implement */
 