/**

    @file      sort.h
    @author    Khrapov
    @date      1.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/typedefs.h>

#include <qx/meta/type_traits.h>
#include <algorithm>
#include <functional>
#include <vector>

namespace qx
{

constexpr size_t SORT_COUNTING_MAX_BUFFER_SIZE = 100000;

//!< vector of iterator value
template<class it_t>
using vector_of_values = std::vector<iterator_value_t<it_t>>;

/**
    @brief      Check if sort really needed
    @complexity O(1)
    @tparam     random_it_t - random access iterator
    @param      begin       - begin iterator 
    @param      end         - end iterator 
    @retval                 - false if [begin, end) already sorted 
**/
template<class random_it_t>
inline bool sort_required(random_it_t begin, random_it_t end);

/**
    @brief      Insertion sort
    @details    Stable
    @complexity O(N^2)
    @tparam     random_it_t - random access iterator
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      begin       - begin iterator 
    @param      end         - end iterator 
    @param      compare     - comparison function 
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort_insertion(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief      Insertion sort
    @details    Stable
    @complexity O(N^2)
    @tparam     container_t - container type
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      cont        - container ref
    @param      compare     - comparison function
**/
template<class container_t, class compare_t = std::less<>>
inline void sort_insertion(container_t& cont, compare_t compare = compare_t());

/**
    @brief      Selection sort
    @details    Unstable
    @complexity O(N^2)
    @tparam     random_it_t - random access iterator
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      begin       - begin iterator
    @param      end         - end iterator
    @param      compare     - comparison function
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort_selection(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief      Selection sort
    @details    Unstable
    @complexity O(N^2)
    @tparam     container_t - container type
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      cont        - container ref
    @param      compare     - comparison function
**/
template<class container_t, class compare_t = std::less<>>
inline void sort_selection(container_t& cont, compare_t compare = compare_t());

/**
    @brief      Bubble sort
    @details    Stable
    @complexity O(N^2)
    @tparam     random_it_t - random access iterator
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      begin       - begin iterator
    @param      end         - end iterator
    @param      compare     - comparison function
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort_bubble(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief      Bubble sort
    @details    Stable
    @complexity O(N^2)
    @tparam     container_t - container type
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      cont        - container ref
    @param      compare     - comparison function
**/
template<class container_t, class compare_t = std::less<>>
inline void sort_bubble(container_t& cont, compare_t compare = compare_t());

/**
    @brief      Adjust heap
    @complexity O(log(N))
    @tparam     random_it_t  - random access iterator
    @tparam     compare_t    - function object type satisfying binary predicate requirements
    @param      begin        - whole heap root random_it_type
    @param      nHeapSize    - whole heap size for out of range check 
    @param      nPosition    - current root nPosition 
    @param      compare      - comparison function 
**/
template<class random_it_t, class compare_t>
inline void adjust_heap(random_it_t begin, size_t nHeapSize, size_t nPosition, compare_t compare = compare_t());

/**
    @brief  Make heap at range
    @tparam random_it_t - random access iterator
    @tparam compare_t   - function object type satisfying binary predicate requirements
    @param  begin       - begin iterator
    @param  end         - end iterator 
    @param  compare     - comparison function 
**/
template<class random_it_t, class compare_t>
inline void make_heap(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief      Heap sort
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     random_it_t - random access iterator
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      begin       - begin iterator
    @param      end         - end iterator
    @param      compare     - comparison function
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort_heap(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief      Heap sort
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     container_t - container type
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      cont        - container ref
    @param      compare     - comparison function
**/
template<class container_t, class compare_t = std::less<>>
inline void sort_heap(container_t& cont, compare_t compare = compare_t());

/**
    @brief      Quick sort based on Hoare partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     random_it_t - random access iterator
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      begin       - begin iterator
    @param      end         - end iterator
    @param      compare     - comparison function
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort_quick_hoare(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief      Quick sort based on Hoare partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     container_t - container type
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      cont        - container ref
    @param      compare     - comparison function
**/
template<class container_t, class compare_t = std::less<>>
inline void sort_quick_hoare(container_t& cont, compare_t compare = compare_t());

/**
    @brief      Quick sort based on three-way partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     random_it_t - random access iterator
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      begin       - begin iterator
    @param      end         - end iterator
    @param      compare     - comparison function
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort_quick_three_way(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief      Quick sort based on three-way partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     container_t - container type
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      cont        - container ref
    @param      compare     - comparison function
**/
template<class container_t, class compare_t = std::less<>>
inline void sort_quick_three_way(container_t& cont, compare_t compare = compare_t());

/**
    @brief      Quick sort based on dual-pivot partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     random_it_t - random access iterator
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      begin       - begin iterator
    @param      end         - end iterator
    @param      compare     - comparison function
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort_quick_dual_pivot(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief      Quick sort based on dual-pivot partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     container_t - container type
    @tparam     compare_t   - function object type satisfying binary predicate requirements
    @param      cont        - container ref
    @param      compare     - comparison function
**/
template<class container_t, class compare_t = std::less<>>
inline void sort_quick_dual_pivot(container_t& cont, compare_t compare = compare_t());

/**
    @brief      Merge with temp vector
    @complexity O(N), O(N) memory
    @tparam     random_it_t         - random access iterator
    @tparam     compare_t           - function object type satisfying binary predicate requirements
    @param      begin               - begin iterator
    @param      end                 - end iterator 
    @param      compare             - comparison function 
    @param      pPreallocatedBuffer - preallocated buffer. default value will allocate a new one 
**/
template<class random_it_t, class compare_t = std::less<>>
inline void merge(
    random_it_t                    begin,
    random_it_t                    end,
    compare_t                      compare             = compare_t(),
    vector_of_values<random_it_t>* pPreallocatedBuffer = nullptr);

/**
    @brief      Merge sort based on merge with temp vector
    @details    Stable
    @complexity O(Nlog(N)), O(N) memory
    @tparam     random_it_t         - random access iterator
    @tparam     compare_t           - function object type satisfying binary predicate requirements
    @param      begin               - begin iterator
    @param      end                 - end iterator
    @param      pPreallocatedBuffer - preallocated buffer. default value will allocate a new one
    @param      compare             - comparison function
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort_merge(
    random_it_t                    begin,
    random_it_t                    end,
    compare_t                      compare             = compare_t(),
    vector_of_values<random_it_t>* pPreallocatedBuffer = nullptr);

/**
    @brief      Merge sort based on merge with temp vector
    @details    Stable
    @complexity O(Nlog(N)), O(N) memory
    @tparam     container_t         - container type
    @tparam     compare_t           - function object type satisfying binary predicate requirements
    @param      cont                - container ref
    @param      compare             - comparison function
    @param      pPreallocatedBuffer - preallocated buffer. default value will allocate a new one
**/
template<class container_t, class compare_t = std::less<>>
inline void sort_merge(
    container_t&                                      cont,
    compare_t                                         compare             = compare_t(),
    vector_of_values<typename container_t::iterator>* pPreallocatedBuffer = nullptr);

/**
    @brief      Counting sort for integral values
    @complexity O(M + 2 * N), O(M) memory, where M = max - min + 1
    @tparam     random_it_t    - random access iterator
    @tparam     compare_t      - function object type satisfying binary predicate requirements
    @param      begin          - begin iterator
    @param      end            - end iterator
    @param      compare        - comparison function
    @param      nMaxBufferSize - max buffer size. if required size is bigger than this value, sorting will fail
    @retval                    - true if sorted, false if required buffer size is greather then max
**/
template<class random_it_t, class compare_t = std::less<>>
[[nodiscard]] inline bool sort_counting(
    random_it_t begin,
    random_it_t end,
    compare_t   compare        = compare_t(),
    size_t      nMaxBufferSize = SORT_COUNTING_MAX_BUFFER_SIZE);

/**
    @brief      Counting sort for integral values
    @complexity O(M + 2 * N), O(M) memory, where M = max - min + 1
    @tparam     container_t    - container type
    @tparam     compare_t      - function object type satisfying binary predicate requirements
    @param      cont           - container ref
    @param      compare        - comparison function
    @param      nMaxBufferSize - max buffer size. if required size is bigger than this value, sorting will fail
    @retval                    - true if sorted, false if required buffer size is greather then max
**/
template<class container_t, class compare_t = std::less<>>
[[nodiscard]] inline bool sort_counting(
    container_t& cont,
    compare_t    compare        = compare_t(),
    size_t       nMaxBufferSize = SORT_COUNTING_MAX_BUFFER_SIZE);

/** 
    @brief  Sort by the most suitable algorithm
    @tparam random_it_t - random access iterator
    @tparam compare_t   - function object type satisfying binary predicate requirements
    @param  begin       - begin iterator
    @param  end         - end iterator
    @param  compare     - comparison function
**/
template<class random_it_t, class compare_t = std::less<>>
inline void sort(random_it_t begin, random_it_t end, compare_t compare = compare_t());

/**
    @brief  Sort by the most suitable algorithm
    @tparam container_t - container type
    @tparam compare_t   - function object type satisfying binary predicate requirements
    @param  cont        - container ref
    @param  compare     - comparison function
**/
template<class container_t, class compare_t = std::less<>>
inline void sort(container_t& cont, compare_t compare = compare_t());

} // namespace qx

#include <qx/algo/sort.inl>
