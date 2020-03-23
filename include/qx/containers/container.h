//============================================================================
//
//!\file                         container.h
//
//!\brief       Container
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
                                                                                                                                \
    using iterator                  = qx::iterator<container>;                                                                  \
    using const_iterator            = qx::const_iterator<container>;                                                            \
    using reverse_iterator          = qx::reverse_iterator<container>;                                                          \
    using const_reverse_iterator    = qx::const_reverse_iterator<container>;                                                    \
                                                                                                                                \
    iterator                begin           (void)                      { return iterator(this, 0);                         }   \
    iterator                end             (void)                      { return iterator(this, size());                    }   \
    const_iterator          cbegin          (void)              const   { return const_iterator(this, 0);                   }   \
    const_iterator          cend            (void)              const   { return const_iterator(this, size());              }   \
    reverse_iterator        rbegin          (void)                      { return reverse_iterator(this, size() - 1);        }   \
    reverse_iterator        rend            (void)                      { return reverse_iterator(this, -1);                }   \
    const_reverse_iterator  crbegin         (void)              const   { return const_reverse_iterator(this, size() - 1);  }   \
    const_reverse_iterator  crend           (void)              const   { return const_reverse_iterator(this, -1);          }   \
                                                                                                                                \
    size_type               size            (void)              const;  /* implement */                                         \
    bool                    empty           (void)              const   { return size() == 0;                               }   \
    pointer                 data            (void);                     /* implement */                                         \
    const_pointer           data            (void)              const   { return const_cast<container*>(this)->data();      }   \
    reference               at              (size_type  ind);           /* implement */                                         \
    const_reference         at              (size_type  ind)    const   { return const_cast<container*>(this)->at(ind);     }   \
    void                    clear           (void);                     /* implement */


namespace qx::detail
{

//============================================================================
//!\fn                   destruct<T, iterator>
//
//!\brief  Call destructors
//!\param  start - start iterator
//!\param  end   - end iterator
//!\author Khrapov
//!\date   29.02.2020
//============================================================================
template<class T, class iterator>
inline void destruct(iterator start, iterator end = start++)
{
    if constexpr (std::is_compound<T>::value)
    {
        for (auto it = start; it < end; ++it)
            static_cast<T>((*it)).~T();
    }
}

}