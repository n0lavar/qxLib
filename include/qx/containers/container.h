/**

    @file      container.h
    @brief     Contains macro for random access containers with common functions
    @author    Khrapov
    @date      8.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/patterns/iterator.h>

/**
    @def   QX_IMPL_CONTAINER
    @brief Macro for random access containers with common functions
    @param container - container type
**/
#define QX_IMPL_CONTAINER(container)                                      \
                                                                          \
    using iterator               = qx::iterator<container>;               \
    using const_iterator         = qx::const_iterator<container>;         \
    using reverse_iterator       = qx::reverse_iterator<container>;       \
    using const_reverse_iterator = qx::const_reverse_iterator<container>; \
                                                                          \
    iterator begin(void) noexcept                                         \
    {                                                                     \
        return iterator(this, 0);                                         \
    }                                                                     \
                                                                          \
    iterator end(void) noexcept                                           \
    {                                                                     \
        return iterator(this, size());                                    \
    }                                                                     \
                                                                          \
    const_iterator cbegin(void) const noexcept                            \
    {                                                                     \
        return const_iterator(this, 0);                                   \
    }                                                                     \
                                                                          \
    const_iterator cend(void) const noexcept                              \
    {                                                                     \
        return const_iterator(this, size());                              \
    }                                                                     \
                                                                          \
    reverse_iterator rbegin(void) noexcept                                \
    {                                                                     \
        return reverse_iterator(this, size() - 1);                        \
    }                                                                     \
                                                                          \
    reverse_iterator rend(void) noexcept                                  \
    {                                                                     \
        return reverse_iterator(this, static_cast<size_type>(-1));        \
    }                                                                     \
                                                                          \
    const_reverse_iterator crbegin(void) const noexcept                   \
    {                                                                     \
        return const_reverse_iterator(this, size() - 1);                  \
    }                                                                     \
                                                                          \
    const_reverse_iterator crend(void) const noexcept                     \
    {                                                                     \
        return const_reverse_iterator(this, static_cast<size_type>(-1));  \
    }                                                                     \
                                                                          \
    /* implement */ size_type size(void) const noexcept;                  \
                                                                          \
    bool empty(void) const noexcept                                       \
    {                                                                     \
        return size() == 0;                                               \
    }                                                                     \
                                                                          \
    /* implement */ pointer data(void) noexcept;                          \
                                                                          \
    const_pointer data(void) const noexcept                               \
    {                                                                     \
        return const_cast<container*>(this)->data();                      \
    }                                                                     \
                                                                          \
    /* implement */ reference at(size_type ind) noexcept;                 \
                                                                          \
    const_reference at(size_type ind) const noexcept                      \
    {                                                                     \
        return const_cast<container*>(this)->at(ind);                     \
    }                                                                     \
                                                                          \
    /* implement */ void clear(void) noexcept;
