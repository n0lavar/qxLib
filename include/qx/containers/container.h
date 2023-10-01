/**

    @file      container.h
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
    iterator begin() noexcept                                             \
    {                                                                     \
        return iterator(this, 0);                                         \
    }                                                                     \
                                                                          \
    iterator end() noexcept                                               \
    {                                                                     \
        return iterator(this, size());                                    \
    }                                                                     \
                                                                          \
    const_iterator begin() const noexcept                                 \
    {                                                                     \
        return const_iterator(this, 0);                                   \
    }                                                                     \
                                                                          \
    const_iterator end() const noexcept                                   \
    {                                                                     \
        return const_iterator(this, size());                              \
    }                                                                     \
                                                                          \
    const_iterator cbegin() const noexcept                                \
    {                                                                     \
        return const_iterator(this, 0);                                   \
    }                                                                     \
                                                                          \
    const_iterator cend() const noexcept                                  \
    {                                                                     \
        return const_iterator(this, size());                              \
    }                                                                     \
                                                                          \
    reverse_iterator rbegin() noexcept                                    \
    {                                                                     \
        return reverse_iterator(this, size() - 1);                        \
    }                                                                     \
                                                                          \
    reverse_iterator rend() noexcept                                      \
    {                                                                     \
        return reverse_iterator(this, static_cast<size_type>(-1));        \
    }                                                                     \
                                                                          \
    const_reverse_iterator crbegin() const noexcept                       \
    {                                                                     \
        return const_reverse_iterator(this, size() - 1);                  \
    }                                                                     \
                                                                          \
    const_reverse_iterator crend() const noexcept                         \
    {                                                                     \
        return const_reverse_iterator(this, static_cast<size_type>(-1));  \
    }                                                                     \
                                                                          \
    const_reverse_iterator rbegin() const noexcept                        \
    {                                                                     \
        return const_reverse_iterator(this, size() - 1);                  \
    }                                                                     \
                                                                          \
    const_reverse_iterator rend() const noexcept                          \
    {                                                                     \
        return const_reverse_iterator(this, static_cast<size_type>(-1));  \
    }                                                                     \
                                                                          \
    /* implement */ size_type size() const noexcept;                      \
                                                                          \
    bool empty() const noexcept                                           \
    {                                                                     \
        return size() == 0;                                               \
    }                                                                     \
                                                                          \
    /* implement */ pointer data() noexcept;                              \
                                                                          \
    const_pointer data() const noexcept                                   \
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
    /* implement */ void clear() noexcept;
