//==============================================================================
//
//!\file                            sort.h
//
//!\brief       Sorting algorithms
//!\details     ~
//
//!\author      Khrapov
//!\date        1.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All mid reserved.
//
//==============================================================================
#pragma once

#include <qx/typedefs.h>

#include <vector>
#include <algorithm>
#include <functional>
#include <qx/type_traits.h>

namespace qx
{

constexpr size_t SORT_COUNTING_MAX_BUFFER_SIZE = 100000;

// vector of iterator value
template<class It>
using vector_of_values = std::vector<iterator_value_t<It>>;

//==============================================================================
//!\fn                   qx::sort_required<RandomIt>
//
//!\brief       check if sort really needed
//!\property    O(1)
//!\param       begin   - begin iterator
//!\param       end     - end iterator
//!\retval              - false if [begin, end) already sorted
//!\author Khrapov
//!\date   9.09.2020
//==============================================================================
template <typename RandomIt>
inline bool sort_required(RandomIt begin, RandomIt end)
{
    if (end - begin < 2)
        return false;
    else
        return true;
}

//==============================================================================
//!\fn               qx::sort_insertion<RandomIt, Compare>
//
//!\brief       Insertion sort
//!\details     stable
//!\property    O(n^2)
//!\param       begin   - begin iterator
//!\param       end     - end iterator
//!\param       compare - comparison function
//!\author      Khrapov
//!\date        1.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_insertion(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    for (RandomIt i = begin + 1; i != end; ++i) //-V756
        for (RandomIt j = i; j != begin && compare(*j, *(j - 1)); --j)
            std::iter_swap(j - 1, j);
}
template <typename Container, typename Compare = std::less<>>
inline void sort_insertion(Container& cont, Compare compare = Compare())
{
    sort_insertion(cont.begin(), cont.end(), compare);
}

//==============================================================================
//!\fn               qx::sort_selection<RandomIt, Compare>
//
//!\brief       Selection sort
//!\details     unstable
//!\property    O(n^2)
//!\param       begin   - begin iterator
//!\param       end     - end iterator
//!\param       compare - comparison function
//!\author      Khrapov
//!\date        1.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_selection(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    for (RandomIt i = begin; i != end; ++i)
    {
        RandomIt itr_min = i;
        for (RandomIt j = i + 1; j != end; ++j)
            if (compare(*j, *itr_min))
                itr_min = j;

        std::iter_swap(i, itr_min);
    }
}
template <typename Container, typename Compare = std::less<>>
inline void sort_selection(Container& cont, Compare compare = Compare())
{
    sort_selection(cont.begin(), cont.end(), compare);
}

//==============================================================================
//!\fn                 qx::sort_bubble<RandomIt, Compare>
//
//!\brief       Bubble sort
//!\details     stable
//!\property    O(n^2)
//!\param       begin   - begin iterator
//!\param       end     - end iterator
//!\param       compare - comparison function
//!\author      Khrapov
//!\date        1.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_bubble(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    bool bSorted = false;
    while (!bSorted)
    {
        bSorted = true;
        for (RandomIt i = begin, i_end = end - 1; i != i_end; ++i)
        {
            if (compare(*(i + 1), *i))
            {
                std::iter_swap(i, i + 1);
                bSorted = false;
            }
        }
    }
}
template <typename Container, typename Compare = std::less<>>
inline void sort_bubble(Container& cont, Compare compare = Compare())
{
    sort_bubble(cont.begin(), cont.end(), compare);
}

//==============================================================================
//!\fn                 qx::adjust_heap<RandomIt, Compare>
//
//!\brief       Adjust heap
//!\property    O(log(N))
//!\param       begin    - whole heap root RandomIt
//!\param       heapSize - whole heap size for out of range check
//!\param       position - current root position
//!\param       compare  - comparison function
//!\author      Khrapov
//!\date        2.03.2020
//==============================================================================
template <typename RandomIt, typename Compare>
inline void adjust_heap(
    RandomIt begin,
    size_t   heapSize,
    size_t   position,
    Compare  compare = Compare())
{
    using iter_diff = decltype(RandomIt() - RandomIt());

    while (position < heapSize)
    {
        size_t childpos = position * 2 + 1;
        if (childpos < heapSize)
        {
            if ((childpos + 1 < heapSize)
                && compare(
                    *(begin + static_cast<iter_diff>(childpos)),
                    *(begin + static_cast<iter_diff>(childpos) + 1)))
            {
                childpos += 1;
            }

            if (compare(
                *(begin + static_cast<iter_diff>(childpos)),
                *(begin + static_cast<iter_diff>(position))))
            {
                return;
            }
            else
            {
                std::iter_swap(
                    begin + static_cast<iter_diff>(position),
                    begin + static_cast<iter_diff>(childpos));
            }
        }
        position = childpos;
    }
}

//==============================================================================
//!\fn                  qx::make_heap<RandomIt, Compare>
//
//!\brief  Make heap at range
//!\param  begin   - begin iterator
//!\param  end     - end iterator
//!\param  compare - comparison function
//!\author Khrapov
//!\date   2.03.2020
//==============================================================================
template <typename RandomIt, typename Compare>
inline void make_heap(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    auto max = end - begin;
    for (int i = static_cast<int>(max) / 2; i >= 0; i--)
        adjust_heap(begin, static_cast<size_t>(max), static_cast<size_t>(i), compare);
}

//==============================================================================
//!\fn                  qx::sort_heap<RandomIt, Compare>
//
//!\brief       heap sort
//!\details     unstable
//!\property    O(nlog(N))
//!\param       begin   - begin iterator
//!\param       end     - end iterator
//!\param       compare - comparison function
//!\author      Khrapov
//!\date        2.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_heap(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    qx::make_heap(begin, end, compare);

    auto lastPosition = end - begin - 1;
    while (lastPosition > 0)
    {
        std::iter_swap(begin, begin + lastPosition);
        adjust_heap(begin, static_cast<size_t>(lastPosition), 0u, compare);
        lastPosition--;
    }
}
template <typename Container, typename Compare = std::less<>>
inline void sort_heap(Container& cont, Compare compare = Compare())
{
    qx::sort_heap(cont.begin(), cont.end(), compare);
}

//==============================================================================
//!\fn              qx::sort_quick_hoare<RandomIt, Compare>
//
//!\brief       quick sort based on Hoare partitioning
//!\details     unstable
//!\property    O(nlog(N))
//!\param       begin   - begin iterator
//!\param       end     - end iterator
//!\param       compare - comparison function
//!\author      Khrapov
//!\date        4.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_hoare(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    i64 right = (end - begin) - 1;
    i64 left  = 0;

    if (right > left)
    {
        auto pivot = *(begin + left + (right - left) / 2);

        while (left <= right)
        {
            while (compare(*(begin + left), pivot))
                ++left;

            while (compare(pivot, *(begin + right)))
                --right;

            if (left <= right)
                std::iter_swap(begin + left++, begin + right--);
        }

        sort_quick_hoare(begin, begin + (right + 1), compare);
        sort_quick_hoare(begin + left, end, compare);
    }
}
template <typename Container, typename Compare = std::less<>>
inline void sort_quick_hoare(Container& cont, Compare compare = Compare())
{
    sort_quick_hoare(cont.begin(), cont.end(), compare);
}

//==============================================================================
//!\fn            qx::sort_quick_three_way<RandomIt, Compare>
//
//!\brief       quick sort based on three-way partitioning
//!\details     unstable
//!\property    O(nlog(N))
//!\param       begin   - begin iterator
//!\param       end     - end iterator
//!\param       compare - comparison function
//!\author      Khrapov
//!\date        4.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_three_way(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    i64 right = (end - begin) - 1;
    i64 left  = 0;

    if (right > 0)
    {
        auto pivot = *(begin + left + (right - left) / 2);

        i64 i = left;
        i64 j = right;

        i64 index1 = left  - 1;
        i64 index2 = right + 1;

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
                        // left[i] != pivot and left[j] != pivot
                        std::swap(*(begin + i), *(begin + j));
                    }
                    else
                    {
                        // left[i] != pivot and left[j] == pivot
                        std::swap(*(begin + i), *(begin + j));
                        std::swap(*(begin + ++index1), *(begin + i));
                    }
                }
                else if (compare(*(begin + j), pivot))
                {
                    // left[i] == pivot left[j] != pivot
                    std::iter_swap(begin + i, begin + j);
                    std::iter_swap(begin + j, begin + --index2);
                }
                else
                {
                    // left[i] == pivot and left[j] == pivot
                    std::iter_swap(begin + ++index1, begin + i);
                    std::iter_swap(begin + j, begin + --index2);
                }

                ++i;
                --j;
            }
            else if (i == j)
            {
                j = i - 1;
                i++;
                break;
            }
        }

        for (i64 k = left; k <= index1; k++)
            std::iter_swap(begin + k, begin + j--);

        for (i64 k = right; k >= index2; k--)
            std::iter_swap(begin + i++, begin + k);

        sort_quick_three_way(begin, begin + (j + 1), compare);
        sort_quick_three_way(begin + i, end, compare);
    }
}
template <typename Container, typename Compare = std::less<>>
inline void sort_quick_three_way(Container& cont, Compare compare = Compare())
{
    sort_quick_three_way(cont.begin(), cont.end(), compare);
}

//==============================================================================
//!\fn            qx::sort_quick_dual_pivot<RandomIt, Compare>
//
//!\brief       quick sort based on dual-pivot partitioning
//!\details     unstable
//!\property    O(nlog(N))
//!\param       begin   - begin iterator
//!\param       end     - end iterator
//!\param       compare - comparison function
//!\author      Khrapov
//!\date        4.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_dual_pivot(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end))
        return;

    i64 right = (end - begin) - 1;
    i64 left  = 0;

    if (right > left)
    {
        std::iter_swap(begin + left + (right - left) / 3,  begin+ left);
        std::iter_swap(begin + right - (right - left) / 3, begin+ right);

        if (compare(*(begin + right), *(begin + left)))
            std::iter_swap(begin + left, begin + right);

        if (right - left == 1)
            return;

        auto pivot1 = *(begin + left);
        auto pivot2 = *(begin + right);

        if (compare(pivot1, pivot2))
        {
            i64 less    = left + 1;
            i64 greater = right - 1;

            while (!compare(*(begin + greater), pivot2))
                greater--;

            while (!compare(pivot1, *(begin + less)))
                less++;

            i64 k = less;
            while (k <= greater)
            {
                if (!compare(pivot1, *(begin + k)))
                {
                    std::iter_swap(begin + k, begin + less++);
                }
                else if (!compare(*(begin + k), pivot2))
                {
                    std::iter_swap(begin + k, begin + greater--);
                    while (!compare(*(begin + greater), pivot2))
                        greater--;

                    if (!compare(pivot1, *(begin + k)))
                        std::iter_swap(begin + k, begin + less++);
                }

                k++;
            }

            std::iter_swap(begin + less - 1,    begin + left);
            std::iter_swap(begin + greater + 1, begin + right);

            sort_quick_dual_pivot(begin, begin + less - 1, compare);
            sort_quick_dual_pivot(begin + greater + 2, end, compare);
            sort_quick_dual_pivot(begin + less, begin + greater + 1, compare);
        }
        else
        {
            // pivot1 == pivot2
            i64 less    = left + 1;
            i64 greater = right - 1;

            while (compare(pivot1, *(begin + greater)))
                greater--;

            while (compare(*(begin + less), pivot1))
                less++;

            i64 k = less;
            while (k <= greater)
            {
                if (compare(*(begin + k), pivot1))
                {
                    std::iter_swap(begin + k, begin + less++);
                }
                else if (compare(pivot1, *(begin + k)))
                {
                    std::iter_swap(begin + k, begin + greater--);
                    while (compare(pivot1, *(begin + greater)))
                        greater--;

                    if (compare(*(begin + k), pivot1))
                        std::iter_swap(begin + k, begin + less++);
                }

                k++;
            }

            std::iter_swap(begin + less - 1,    begin + left);
            std::iter_swap(begin + greater + 1, begin + right);

            sort_quick_dual_pivot(begin, begin + less - 1, compare);
            sort_quick_dual_pivot(begin + greater + 2, end, compare);
        }
    }
}
template <typename Container, typename Compare = std::less<>>
inline void sort_quick_dual_pivot(Container& cont, Compare compare = Compare())
{
    sort_quick_dual_pivot(cont.begin(), cont.end(), compare);
}

//==============================================================================
//!\fn                    qx::merge<RandomIt, Compare>
//
//!\brief       merge with temp vector
//!\property    O(N), O(N) memory
//!\author      Khrapov
//!\param       begin               - begin iterator
//!\param       end                 - end iterator
//!\param       compare             - comparison function
//!\param       preallocatedBuffer  - preallocated buffer. default value will allocate a new one
//!\author      Khrapov
//!\date        4.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void merge
    (RandomIt                       begin,
     RandomIt                       end,
     Compare                        compare             = Compare(),
     vector_of_values<RandomIt>   * pPreallocatedBuffer = nullptr)
{
    using iter_diff = decltype(RandomIt() - RandomIt());

    u64 ind1 = 0;
    u64 ind2 = 0;
    RandomIt mid = begin + (end - begin) / 2;

    bool bCreateBuffer = !pPreallocatedBuffer;
    if (bCreateBuffer)
        pPreallocatedBuffer = new vector_of_values<RandomIt>;

    pPreallocatedBuffer->resize(static_cast<size_t>(end - begin));

    // merge
    while ((begin + static_cast<iter_diff>(ind1) < mid)
        && (mid + static_cast<iter_diff>(ind2) < end))
    {
        if (compare(
            *(begin + static_cast<iter_diff>(ind1)),
            *(mid + static_cast<iter_diff>(ind2))))
        {
            (*pPreallocatedBuffer)[ind1 + ind2] = *(begin + static_cast<iter_diff>(ind1));
            ind1++;
        }
        else
        {
            (*pPreallocatedBuffer)[ind1 + ind2] = *(mid + static_cast<iter_diff>(ind2));
            ind2++;
        }
    }

    // append tails
    while (begin + static_cast<iter_diff>(ind1) < mid)
    {
        (*pPreallocatedBuffer)[ind1 + ind2] = *(begin + static_cast<iter_diff>(ind1));
        ind1++;
    }

    while (mid + static_cast<iter_diff>(ind2) < end)
    {
        (*pPreallocatedBuffer)[ind1 + ind2] = *(mid + static_cast<iter_diff>(ind2));
        ind2++;
    }

    // copy to source
    for (auto it = begin; it < end; ++it)
        *it = (*pPreallocatedBuffer)[static_cast<size_t>(it - begin)];

    if (bCreateBuffer)
        delete pPreallocatedBuffer;
}

//==============================================================================
//!\fn                 qx::sort_merge<RandomIt, Compare>
//
//!\brief       merge sort based on merge with temp vector
//!\details     stable
//!\property    O(nlog(N)), O(N) memory
//!\param       begin               - begin iterator
//!\param       end                 - end iterator
//!\param       compare             - comparison function
//!\param       pPreallocatedBuffer - preallocated buffer. default value will allocate a new one
//!\author      Khrapov
//!\date        4.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_merge
    (RandomIt                       begin,
     RandomIt                       end,
     Compare                        compare             = Compare(),
     vector_of_values<RandomIt>   * pPreallocatedBuffer = nullptr)
{
    if (!sort_required(begin, end))
        return;

    bool bCreateBuffer = !pPreallocatedBuffer;
    if (bCreateBuffer)
        pPreallocatedBuffer = new vector_of_values<RandomIt>;

    // preallocate max required size and use same vector
    // has no effect in reqursive calls
    auto len = end - begin;
    pPreallocatedBuffer->reserve(static_cast<size_t>(len));

    sort_merge(begin, begin + len / 2, compare, pPreallocatedBuffer);
    sort_merge(begin + len / 2, end, compare, pPreallocatedBuffer);
    merge(begin, end, compare, pPreallocatedBuffer);

    if (bCreateBuffer)
        delete pPreallocatedBuffer;
}
template <typename Container, typename Compare = std::less<>>
inline void sort_merge
    (Container&                                      cont,
     Compare                                         compare             = Compare(),
     vector_of_values<typename Container::iterator>* pPreallocatedBuffer = nullptr)
{
    sort_merge(cont.begin(), cont.end(), compare, pPreallocatedBuffer);
}

//==============================================================================
//!\fn                qx::sort_counting<RandomIt, Compare>
//
//!\brief       counting sort for integral values
//!\details     effective if M is relatively small compared to N (elements are in short range)
//!\property    O(M + 2 * N), O(M) memory, where M = max - min + 1
//!\param       begin           - begin iterator
//!\param       end             - end iterator
//!\param       compare         - comparison function
//!\param       nMaxBufferSize  - max buffer size. if required size is bigger than this value, sorting will fail
//!\retval      true if sorted, false if required buffer size is greather then max
//!\author      Khrapov
//!\date        4.03.2020
//==============================================================================
template <typename RandomIt, typename Compare = std::less<>>
[[nodiscard]] inline bool sort_counting
    (RandomIt       begin,
     RandomIt       end,
     Compare        compare         = Compare(),
     size_t         nMaxBufferSize  = SORT_COUNTING_MAX_BUFFER_SIZE)
{
    static_assert(std::is_integral_v<iterator_value_t<RandomIt>>,
                  "Intergral type required for counting sort");

    if (end - begin < 2)
        return true;

    auto minmax = std::minmax_element(begin, end);
    auto min = *minmax.first;
    auto max = *minmax.second;

    size_t nSizeRequired = static_cast<size_t>(max) - min + 1;
    if (nSizeRequired <= nMaxBufferSize)
    {
        std::vector<size_t> counts(nSizeRequired, 0);

        for (RandomIt it = begin; it < end; ++it)
            counts[static_cast<size_t>(*it) - min]++;

        if constexpr (compare(0, 1))
        {
            // less
            for (size_t i = 0; i < nSizeRequired; i++)
                begin = std::fill_n(begin, counts[i], min++);
        }
        else
        {
            // greater
            for (size_t i = 0; i < nSizeRequired; i++)
                begin = std::fill_n(begin, counts[nSizeRequired - i - 1], max--);
        }

        return true;
    }
    else
        return false;
}
template <typename Container, typename Compare = std::less<>>
[[nodiscard]] inline bool sort_counting
    (Container& cont,
     Compare    compare         = Compare(),
     size_t     nMaxBufferSize  = SORT_COUNTING_MAX_BUFFER_SIZE)
{
    return sort_counting(cont.begin(), cont.end(), compare, nMaxBufferSize);
}

//==============================================================================
//!\fn                    qx::sort<RandomIt, Compare>
//
//!\brief  Sort by the most suitable algorithm
//!\param  begin   - begin iterator
//!\param  end     - end iterator
//!\param  compare - comparison function
//!\author Khrapov
//!\date   4.03.2020
//==============================================================================
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
template <typename Container, typename Compare = std::less<>>
inline void sort(Container& cont, Compare compare = Compare())
{
    qx::sort(cont.begin(), cont.end(), compare);
}

}
