/**

    @file      sort.h
    @brief     Sorting algorithms
    @author    Khrapov
    @date      1.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/typedefs.h>

#include <qx/type_traits.h>
#include <algorithm>
#include <functional>
#include <vector>

namespace qx
{

constexpr size_t SORT_COUNTING_MAX_BUFFER_SIZE = 100000;

//!< vector of iterator value
template<class It>
using vector_of_values = std::vector<iterator_value_t<It>>;

/**
    @brief      Check if sort really needed
    @complexity O(1)
    @tparam     RandomIt - random access iterator
    @param      begin    - begin iterator 
    @param      end      - end iterator 
    @retval              - false if [begin, end) already sorted 
**/
template<typename RandomIt>
inline bool sort_required(RandomIt begin, RandomIt end)
{
    if (end - begin < 2)
        return false;
    else
        return true;
}

/**
    @brief      Insertion sort
    @details    Stable
    @complexity O(N^2)
    @tparam     RandomIt - random access iterator
    @tparam     Compare  - function object type satisfying binary predicate requirements
    @param      begin    - begin iterator 
    @param      end      - end iterator 
    @param      compare  - comparison function 
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort_insertion(
    RandomIt begin,
    RandomIt end,
    Compare  compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    for (RandomIt i = begin + 1; i != end; ++i) //-V756
        for (RandomIt j = i; j != begin && compare(*j, *(j - 1)); --j)
            std::iter_swap(j - 1, j);
}

/**
    @brief      Insertion sort
    @details    Stable
    @complexity O(N^2)
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
**/
template<typename Container, typename Compare = std::less<>>
inline void sort_insertion(Container& cont, Compare compare = Compare())
{
    sort_insertion(cont.begin(), cont.end(), compare);
}

/**
    @brief      Selection sort
    @details    Unstable
    @complexity O(N^2)
    @tparam     RandomIt - random access iterator
    @tparam     Compare  - function object type satisfying binary predicate requirements
    @param      begin    - begin iterator
    @param      end      - end iterator
    @param      compare  - comparison function
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort_selection(
    RandomIt begin,
    RandomIt end,
    Compare  compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    for (RandomIt it = begin; it != end; ++it)
    {
        RandomIt itMin = it;
        for (RandomIt j = it + 1; j != end; ++j)
            if (compare(*j, *itMin))
                itMin = j;

        std::iter_swap(it, itMin);
    }
}

/**
    @brief      Selection sort
    @details    Unstable
    @complexity O(N^2)
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
**/
template<typename Container, typename Compare = std::less<>>
inline void sort_selection(Container& cont, Compare compare = Compare())
{
    sort_selection(cont.begin(), cont.end(), compare);
}

/**
    @brief      Bubble sort
    @details    Stable
    @complexity O(N^2)
    @tparam     RandomIt - random access iterator
    @tparam     Compare  - function object type satisfying binary predicate requirements
    @param      begin    - begin iterator
    @param      end      - end iterator
    @param      compare  - comparison function
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort_bubble(
    RandomIt begin,
    RandomIt end,
    Compare  compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    bool bSorted = false;
    while (!bSorted)
    {
        bSorted = true;
        for (RandomIt it = begin, itEnd = end - 1; it != itEnd; ++it)
        {
            if (compare(*(it + 1), *it))
            {
                std::iter_swap(it, it + 1);
                bSorted = false;
            }
        }
    }
}

/**
    @brief      Bubble sort
    @details    Stable
    @complexity O(N^2)
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
**/
template<typename Container, typename Compare = std::less<>>
inline void sort_bubble(Container& cont, Compare compare = Compare())
{
    sort_bubble(cont.begin(), cont.end(), compare);
}

/**
    @brief      Adjust heap
    @complexity O(log(N))
    @tparam     RandomIt  - random access iterator
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      begin     - whole heap root RandomIt
    @param      nHeapSize - whole heap size for out of range check 
    @param      nPosition - current root nPosition 
    @param      compare   - comparison function 
**/
template<typename RandomIt, typename Compare>
inline void adjust_heap(
    RandomIt begin,
    size_t   nHeapSize,
    size_t   nPosition,
    Compare  compare = Compare())
{
    using iter_diff = decltype(RandomIt() - RandomIt());

    while (nPosition < nHeapSize)
    {
        size_t nChildPos = nPosition * 2 + 1;
        if (nChildPos < nHeapSize)
        {
            if ((nChildPos + 1 < nHeapSize)
                && compare(
                    *(begin + static_cast<iter_diff>(nChildPos)),
                    *(begin + static_cast<iter_diff>(nChildPos) + 1)))
            {
                nChildPos += 1;
            }

            if (compare(
                    *(begin + static_cast<iter_diff>(nChildPos)),
                    *(begin + static_cast<iter_diff>(nPosition))))
            {
                return;
            }
            else
            {
                std::iter_swap(
                    begin + static_cast<iter_diff>(nPosition),
                    begin + static_cast<iter_diff>(nChildPos));
            }
        }
        nPosition = nChildPos;
    }
}

/**
    @brief  Make heap at range
    @tparam RandomIt - random access iterator
    @tparam Compare  - function object type satisfying binary predicate requirements
    @param  begin    - begin iterator
    @param  end      - end iterator 
    @param  compare  - comparison function 
**/
template<typename RandomIt, typename Compare>
inline void make_heap(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    auto max = end - begin;
    for (int i = static_cast<int>(max) / 2; i >= 0; --i)
    {
        adjust_heap(
            begin,
            static_cast<size_t>(max),
            static_cast<size_t>(i),
            compare);
    }
}

/**
    @brief      Heap sort
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     RandomIt - random access iterator
    @tparam     Compare  - function object type satisfying binary predicate requirements
    @param      begin    - begin iterator
    @param      end      - end iterator
    @param      compare  - comparison function
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort_heap(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    qx::make_heap(begin, end, compare);

    auto nLastPosition = end - begin - 1;
    while (nLastPosition > 0)
    {
        std::iter_swap(begin, begin + nLastPosition);
        adjust_heap(begin, static_cast<size_t>(nLastPosition), 0u, compare);
        --nLastPosition;
    }
}

/**
    @brief      Heap sort
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
**/
template<typename Container, typename Compare = std::less<>>
inline void sort_heap(Container& cont, Compare compare = Compare())
{
    qx::sort_heap(cont.begin(), cont.end(), compare);
}

/**
    @brief      Quick sort based on Hoare partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     RandomIt - random access iterator
    @tparam     Compare  - function object type satisfying binary predicate requirements
    @param      begin    - begin iterator
    @param      end      - end iterator
    @param      compare  - comparison function
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_hoare(
    RandomIt begin,
    RandomIt end,
    Compare  compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    i64 nRight = (end - begin) - 1;
    i64 nLeft  = 0;

    if (nRight > nLeft)
    {
        auto nPivot = *(begin + nLeft + (nRight - nLeft) / 2);

        while (nLeft <= nRight)
        {
            while (compare(*(begin + nLeft), nPivot))
                ++nLeft;

            while (compare(nPivot, *(begin + nRight)))
                --nRight;

            if (nLeft <= nRight)
                std::iter_swap(begin + nLeft++, begin + nRight--);
        }

        sort_quick_hoare(begin, begin + (nRight + 1), compare);
        sort_quick_hoare(begin + nLeft, end, compare);
    }
}

/**
    @brief      Quick sort based on Hoare partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
**/
template<typename Container, typename Compare = std::less<>>
inline void sort_quick_hoare(Container& cont, Compare compare = Compare())
{
    sort_quick_hoare(cont.begin(), cont.end(), compare);
}

/**
    @brief      Quick sort based on three-way partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     RandomIt - random access iterator
    @tparam     Compare  - function object type satisfying binary predicate requirements
    @param      begin    - begin iterator
    @param      end      - end iterator
    @param      compare  - comparison function
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_three_way(
    RandomIt begin,
    RandomIt end,
    Compare  compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    const i64 nRight = (end - begin) - 1;
    i64       nLeft  = 0;

    if (nRight > 0)
    {
        auto pivot = *(begin + nLeft + (nRight - nLeft) / 2);

        i64 i = nLeft;
        i64 j = nRight;

        i64 nIndex1 = nLeft - 1;
        i64 nIndex2 = nRight + 1;

        while (i <= j)
        {
            while (compare(*(begin + i), pivot))
                ++i;

            while (compare(pivot, *(begin + j)))
                --j;

            if (i < j)
            {
                if (compare(pivot, *(begin + i)))
                {
                    if (compare(*(begin + j), pivot))
                    {
                        // nLeft[i] != nPivot and nLeft[j] != nPivot
                        std::swap(*(begin + i), *(begin + j));
                    }
                    else
                    {
                        // nLeft[i] != nPivot and nLeft[j] == nPivot
                        std::swap(*(begin + i), *(begin + j));
                        std::swap(*(begin + ++nIndex1), *(begin + i));
                    }
                }
                else if (compare(*(begin + j), pivot))
                {
                    // nLeft[i] == nPivot nLeft[j] != nPivot
                    std::iter_swap(begin + i, begin + j);
                    std::iter_swap(begin + j, begin + --nIndex2);
                }
                else
                {
                    // nLeft[i] == nPivot and nLeft[j] == nPivot
                    std::iter_swap(begin + ++nIndex1, begin + i);
                    std::iter_swap(begin + j, begin + --nIndex2);
                }

                ++i;
                --j;
            }
            else if (i == j)
            {
                j = i - 1;
                ++i;
                break;
            }
        }

        for (i64 k = nLeft; k <= nIndex1; ++k)
            std::iter_swap(begin + k, begin + j--);

        for (i64 k = nRight; k >= nIndex2; --k)
            std::iter_swap(begin + i++, begin + k);

        sort_quick_three_way(begin, begin + (j + 1), compare);
        sort_quick_three_way(begin + i, end, compare);
    }
}

/**
    @brief      Quick sort based on three-way partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
**/
template<typename Container, typename Compare = std::less<>>
inline void sort_quick_three_way(Container& cont, Compare compare = Compare())
{
    sort_quick_three_way(cont.begin(), cont.end(), compare);
}

/**
    @brief      Quick sort based on dual-pivot partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     RandomIt - random access iterator
    @tparam     Compare  - function object type satisfying binary predicate requirements
    @param      begin    - begin iterator
    @param      end      - end iterator
    @param      compare  - comparison function
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_dual_pivot(
    RandomIt begin,
    RandomIt end,
    Compare  compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    i64 nRight = (end - begin) - 1;
    i64 nLeft  = 0;

    if (nRight > nLeft)
    {
        std::iter_swap(begin + nLeft + (nRight - nLeft) / 3, begin + nLeft);
        std::iter_swap(begin + nRight - (nRight - nLeft) / 3, begin + nRight);

        if (compare(*(begin + nRight), *(begin + nLeft)))
            std::iter_swap(begin + nLeft, begin + nRight);

        if (nRight - nLeft == 1)
            return;

        auto pivot1 = *(begin + nLeft);
        auto pivot2 = *(begin + nRight);

        if (compare(pivot1, pivot2))
        {
            i64 nLess    = nLeft + 1;
            i64 nGreater = nRight - 1;

            while (!compare(*(begin + nGreater), pivot2))
                --nGreater;

            while (!compare(pivot1, *(begin + nLess)))
                ++nLess;

            i64 k = nLess;
            while (k <= nGreater)
            {
                if (!compare(pivot1, *(begin + k)))
                {
                    std::iter_swap(begin + k, begin + nLess++);
                }
                else if (!compare(*(begin + k), pivot2))
                {
                    std::iter_swap(begin + k, begin + nGreater--);
                    while (!compare(*(begin + nGreater), pivot2))
                        --nGreater;

                    if (!compare(pivot1, *(begin + k)))
                        std::iter_swap(begin + k, begin + nLess++);
                }

                k++;
            }

            std::iter_swap(begin + nLess - 1, begin + nLeft);
            std::iter_swap(begin + nGreater + 1, begin + nRight);

            sort_quick_dual_pivot(begin, begin + nLess - 1, compare);
            sort_quick_dual_pivot(begin + nGreater + 2, end, compare);
            sort_quick_dual_pivot(begin + nLess, begin + nGreater + 1, compare);
        }
        else
        {
            // pivot1 == pivot2
            i64 nLess    = nLeft + 1;
            i64 nGreater = nRight - 1;

            while (compare(pivot1, *(begin + nGreater)))
                --nGreater;

            while (compare(*(begin + nLess), pivot1))
                ++nLess;

            i64 k = nLess;
            while (k <= nGreater)
            {
                if (compare(*(begin + k), pivot1))
                {
                    std::iter_swap(begin + k, begin + nLess++);
                }
                else if (compare(pivot1, *(begin + k)))
                {
                    std::iter_swap(begin + k, begin + nGreater--);
                    while (compare(pivot1, *(begin + nGreater)))
                        --nGreater;

                    if (compare(*(begin + k), pivot1))
                        std::iter_swap(begin + k, begin + nLess++);
                }

                k++;
            }

            std::iter_swap(begin + nLess - 1, begin + nLeft);
            std::iter_swap(begin + nGreater + 1, begin + nRight);

            sort_quick_dual_pivot(begin, begin + nLess - 1, compare);
            sort_quick_dual_pivot(begin + nGreater + 2, end, compare);
        }
    }
}

/**
    @brief      Quick sort based on dual-pivot partitioning
    @details    Unstable
    @complexity O(Nlog(N))
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
**/
template<typename Container, typename Compare = std::less<>>
inline void sort_quick_dual_pivot(Container& cont, Compare compare = Compare())
{
    sort_quick_dual_pivot(cont.begin(), cont.end(), compare);
}

/**
    @brief      Merge with temp vector
    @complexity O(N), O(N) memory
    @tparam     RandomIt - random access iterator
    @tparam     Compare  - function object type satisfying binary predicate requirements
    @param      begin    - begin iterator
    @param      end      - end iterator 
    @param      compare  - comparison function 
    @param      pPreallocatedBuffer - preallocated buffer. default value will allocate a new one 
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void merge(
    RandomIt                    begin,
    RandomIt                    end,
    Compare                     compare             = Compare(),
    vector_of_values<RandomIt>* pPreallocatedBuffer = nullptr)
{
    using iter_diff = decltype(RandomIt() - RandomIt());

    u64      nInd1 = 0;
    u64      nInd2 = 0;
    RandomIt mid   = begin + (end - begin) / 2;

    const bool bCreateBuffer = !pPreallocatedBuffer;
    if (bCreateBuffer)
        pPreallocatedBuffer = new vector_of_values<RandomIt>;

    pPreallocatedBuffer->resize(static_cast<size_t>(end - begin));

    // merge
    while ((begin + static_cast<iter_diff>(nInd1) < mid)
           && (mid + static_cast<iter_diff>(nInd2) < end))
    {
        if (compare(
                *(begin + static_cast<iter_diff>(nInd1)),
                *(mid + static_cast<iter_diff>(nInd2))))
        {
            (*pPreallocatedBuffer)[nInd1 + nInd2] =
                *(begin + static_cast<iter_diff>(nInd1));

            nInd1++;
        }
        else
        {
            (*pPreallocatedBuffer)[nInd1 + nInd2] =
                *(mid + static_cast<iter_diff>(nInd2));

            nInd2++;
        }
    }

    // append tails
    while (begin + static_cast<iter_diff>(nInd1) < mid)
    {
        (*pPreallocatedBuffer)[nInd1 + nInd2] =
            *(begin + static_cast<iter_diff>(nInd1));

        nInd1++;
    }

    while (mid + static_cast<iter_diff>(nInd2) < end)
    {
        (*pPreallocatedBuffer)[nInd1 + nInd2] =
            *(mid + static_cast<iter_diff>(nInd2));

        nInd2++;
    }

    // copy to source
    for (auto it = begin; it < end; ++it)
        *it = (*pPreallocatedBuffer)[static_cast<size_t>(it - begin)];

    if (bCreateBuffer)
        delete pPreallocatedBuffer;
}

/**
    @brief      Merge sort based on merge with temp vector
    @details    Stable
    @complexity O(Nlog(N)), O(N) memory
    @tparam     RandomIt            - random access iterator
    @tparam     Compare             - function object type satisfying binary predicate requirements
    @param      begin               - begin iterator
    @param      end                 - end iterator
    @param      pPreallocatedBuffer - preallocated buffer. default value will allocate a new one
    @param      compare             - comparison function
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort_merge(
    RandomIt                    begin,
    RandomIt                    end,
    Compare                     compare             = Compare(),
    vector_of_values<RandomIt>* pPreallocatedBuffer = nullptr)
{
    if (!sort_required(begin, end))
        return;

    const bool bCreateBuffer = !pPreallocatedBuffer;
    if (bCreateBuffer)
        pPreallocatedBuffer = new vector_of_values<RandomIt>;

    // preallocate max required size and use same vector
    // has no effect in reqursive calls
    auto nLen = end - begin;
    pPreallocatedBuffer->reserve(static_cast<size_t>(nLen));

    sort_merge(begin, begin + nLen / 2, compare, pPreallocatedBuffer);
    sort_merge(begin + nLen / 2, end, compare, pPreallocatedBuffer);
    merge(begin, end, compare, pPreallocatedBuffer);

    if (bCreateBuffer)
        delete pPreallocatedBuffer;
}

/**
    @brief      Merge sort based on merge with temp vector
    @details    Stable
    @complexity O(Nlog(N)), O(N) memory
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
    @param      pPreallocatedBuffer - preallocated buffer. default value will allocate a new one
**/
template<typename Container, typename Compare = std::less<>>
inline void sort_merge(
    Container&                                      cont,
    Compare                                         compare = Compare(),
    vector_of_values<typename Container::iterator>* pPreallocatedBuffer =
        nullptr)
{
    sort_merge(cont.begin(), cont.end(), compare, pPreallocatedBuffer);
}

/**
    @brief      Counting sort for integral values
    @complexity O(M + 2 * N), O(M) memory, where M = max - min + 1
    @tparam     RandomIt       - random access iterator
    @tparam     Compare        - function object type satisfying binary predicate requirements
    @param      begin          - begin iterator
    @param      end            - end iterator
    @param      compare        - comparison function
    @param      nMaxBufferSize - max buffer size. if required size is bigger than this value, sorting will fail
    @retval                    - true if sorted, false if required buffer size is greather then max
**/
template<typename RandomIt, typename Compare = std::less<>>
[[nodiscard]] inline bool sort_counting(
    RandomIt begin,
    RandomIt end,
    Compare  compare        = Compare(),
    size_t   nMaxBufferSize = SORT_COUNTING_MAX_BUFFER_SIZE)
{
    static_assert(
        std::is_integral_v<iterator_value_t<RandomIt>>,
        "Integral type required for counting sort");

    if (end - begin < 2)
        return true;

    auto minMax = std::minmax_element(begin, end);
    auto min    = *minMax.first;
    auto max    = *minMax.second;

    const size_t nSizeRequired = static_cast<size_t>(max) - min + 1;
    if (nSizeRequired <= nMaxBufferSize)
    {
        std::vector<size_t> counts(nSizeRequired, 0);

        for (RandomIt it = begin; it < end; ++it)
            ++counts[static_cast<size_t>(*it) - min];

        if constexpr (compare(0, 1))
        {
            // nLess
            for (size_t i = 0; i < nSizeRequired; ++i)
                begin = std::fill_n(begin, counts[i], min++);
        }
        else
        {
            // nGreater
            for (size_t i = 0; i < nSizeRequired; ++i)
                begin =
                    std::fill_n(begin, counts[nSizeRequired - i - 1], max--);
        }

        return true;
    }
    else
        return false;
}

/**
    @brief      Counting sort for integral values
    @complexity O(M + 2 * N), O(M) memory, where M = max - min + 1
    @tparam     Container - container type
    @tparam     Compare   - function object type satisfying binary predicate requirements
    @param      cont      - container ref
    @param      compare   - comparison function
    @param      nMaxBufferSize - max buffer size. if required size is bigger than this value, sorting will fail
    @retval               - true if sorted, false if required buffer size is greather then max
**/
template<typename Container, typename Compare = std::less<>>
[[nodiscard]] inline bool sort_counting(
    Container& cont,
    Compare    compare        = Compare(),
    size_t     nMaxBufferSize = SORT_COUNTING_MAX_BUFFER_SIZE)
{
    return sort_counting(cont.begin(), cont.end(), compare, nMaxBufferSize);
}

/** 
    @brief  Sort by the most suitable algorithm
    @tparam RandomIt - random access iterator
    @tparam Compare  - function object type satisfying binary predicate requirements
    @param  begin    - begin iterator
    @param  end      - end iterator
    @param  compare  - comparison function
**/
template<typename RandomIt, typename Compare = std::less<>>
inline void sort(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    bool bSorted = false;

    // if sort_counting is available
    if constexpr (std::is_integral_v<iterator_value_t<RandomIt>>)
    {
        // with small container size quick is faster
        if (end - begin > 1000)
            bSorted = sort_counting(begin, end, compare);
    }

    // in some cases with small container size std::sort() may be faster,
    // but sort_quick_dual_pivot() faster in general, especially with big sizes
    if (!bSorted)
        sort_quick_dual_pivot(begin, end, compare);
}

/**
    @brief  Sort by the most suitable algorithm
    @tparam Container - container type
    @tparam Compare   - function object type satisfying binary predicate requirements
    @param  cont      - container ref
    @param  compare   - comparison function
**/
template<typename Container, typename Compare = std::less<>>
inline void sort(Container& cont, Compare compare = Compare())
{
    qx::sort(cont.begin(), cont.end(), compare);
}

} // namespace qx
