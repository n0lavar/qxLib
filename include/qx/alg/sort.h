//============================================================================
//
//!\file                            sort.h
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        1.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All mid reserved.
//
//============================================================================
#pragma once

#include <qx/other/typedefs.h>

#include <vector>
#include <array>

namespace qx
{

constexpr size_t SORT_COUNTING_MAX_BUFFER_SIZE = 100000;

//============================================================================
//!\fn                     sort_required<RandomIt>
//
//!\brief       Check if sort really needed
//!\property    O(n)
//!\param       begin - begin iterator
//!\param       end   - end iterator
//!\retval            - false if [begin, end) already sorted
//!\author      Khrapov
//!\date        9.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline bool sort_required(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (end - begin < 2)
        return false;
#if 1
    else
        return true;
#else
    // decreases performance
    for (RandomIt prev = begin, curr = begin + 1; curr < end; prev = curr, ++curr)
        if (compare(*curr, *prev))
            return true;

    return false;
#endif
}

//============================================================================
//!\fn                     sort_insertion<RandomIt>
//
//!\brief       Insertion sort
//!\details     stable
//!\property    O(n^2)
//!\author      Khrapov
//!\date        1.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_insertion(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end, compare))
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

//============================================================================
//!\fn                     sort_selection<RandomIt>
//
//!\brief       Selection sort
//!\details     unstable
//!\property    O(n^2)
//!\author      Khrapov
//!\date        1.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_selection(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end, compare))
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

//============================================================================
//!\fn                      sort_bubble<RandomIt>
//
//!\brief       Bubble sort
//!\details     stable
//!\property    O(n^2)
//!\author      Khrapov
//!\date        1.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_bubble(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end, compare))
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

//============================================================================
//!\fn                      adjust_heap<RandomIt>
//
//!\brief       Adjust heap
//!\property    O(log(N))
//!\param       left    - whole heap root RandomIt
//!\param       heapSize - whole heap size for out of range check
//!\param       position - current root position
//!\author      Khrapov
//!\date        2.03.2020
//============================================================================
template <typename RandomIt, typename Compare>
inline void adjust_heap(RandomIt begin, size_t heapSize, size_t position, Compare compare = Compare())
{
    while (position < heapSize)
    {
        size_t childpos = position * 2 + 1;
        if (childpos < heapSize)
        {
            if ((childpos + 1 < heapSize) && compare(*(begin + childpos), *(begin + childpos + 1)))
                childpos += 1;

            if (compare(*(begin + childpos), *(begin + position)))
                return;
            else
                std::iter_swap(begin + position, begin + childpos);
        }
        position = childpos;
    }
}

//============================================================================
//!\fn                       make_heap<RandomIt>
//
//!\brief  Make heap at range
//!\author Khrapov
//!\date   2.03.2020
//============================================================================
template <typename RandomIt, typename Compare>
inline void make_heap(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    size_t max = end - begin;
    for (int i = static_cast<int>(max) / 2; i >= 0; i--)
        adjust_heap(begin, max, static_cast<size_t>(i), compare);
}

//============================================================================
//!\fn                       sort_heap<RandomIt>
//
//!\brief       heap sort
//!\details     unstable
//!\property    O(nlog(N))
//!\author      Khrapov
//!\date        2.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_heap(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end, compare))
        return;

    qx::make_heap(begin, end, compare);

    size_t lastPosition = end - begin - 1;
    while (lastPosition > 0)
    {
        std::iter_swap(begin, begin + lastPosition);
        adjust_heap(begin, lastPosition, 0, compare);
        lastPosition--;
    }
}
template <typename Container, typename Compare = std::less<>>
inline void sort_heap(Container& cont, Compare compare = Compare())
{
    qx::sort_heap(cont.begin(), cont.end(), compare);
}

//============================================================================
//!\fn               sort_quick_hoare<RandomIt, Compare>
//
//!\brief       quick sort based on Hoare partitioning
//!\details     unstable
//!\property    O(nlog(N))
//!\author      Khrapov
//!\date        4.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_hoare(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end, compare))
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

//============================================================================
//!\fn             sort_quick_three_way<RandomIt, Compare>
//
//!\brief       quick sort based on three-way partitioning
//!\details     unstable
//!\property    O(nlog(N))
//!\author      Khrapov
//!\date        4.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_three_way(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end, compare))
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

//============================================================================
//!\fn             sort_quick_dual_pivot<RandomIt, Compare>
//
//!\brief       quick sort based on dual-pivot partitioning
//!\details     unstable
//!\property    O(nlog(N))
//!\author      Khrapov
//!\date        4.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_quick_dual_pivot(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    if (!sort_required(begin, end, compare))
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

//============================================================================
//!\fn                     merge<RandomIt, Compare>
//
//!\brief       merge with temp vector
//!\property    O(N), O(N) memory
//!\author      Khrapov
//!\date        4.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void merge
    (RandomIt                                     begin,
     RandomIt                                     end, 
     Compare                                      compare             = Compare(),
     std::vector<typename RandomIt::value_type> & preallocatedBuffer  = std::vector<typename RandomIt::value_type>())
{
    i64 ind1 = 0;
    i64 ind2 = 0;
    RandomIt mid = begin + (end - begin) / 2;
    preallocatedBuffer.resize(end - begin);

    // merge
    while ((begin + ind1 < mid) && (mid + ind2 < end))
    {
        if (compare(*(begin + ind1), *(mid + ind2)))
        {
            preallocatedBuffer[ind1 + ind2] = *(begin + ind1);
            ind1++;
        }
        else
        {
            preallocatedBuffer[ind1 + ind2] = *(mid + ind2);
            ind2++;
        }
    }

    // append tails
    while (begin + ind1 < mid)
    {
        preallocatedBuffer[ind1 + ind2] = *(begin + ind1);
        ind1++;
    }
    while (mid + ind2 < end)
    {
        preallocatedBuffer[ind1 + ind2] = *(mid + ind2);
        ind2++;
    }

    // copy to source
    for (auto it = begin; it < end; ++it)
        *it = preallocatedBuffer[it - begin];
}

//============================================================================
//!\fn                  sort_merge<RandomIt, Compare>
//
//!\brief       merge sort based on merge with temp vector
//!\details     stable
//!\property    O(nlog(N)), O(N) memory
//!\author      Khrapov
//!\date        4.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
inline void sort_merge
    (RandomIt                                    begin,
     RandomIt                                    end, 
     Compare                                     compare             = Compare(), 
     std::vector<typename RandomIt::value_type>& preallocatedBuffer  = std::vector<typename RandomIt::value_type>())
{
    if (!sort_required(begin, end, compare))
        return;

    i64 len = end - begin;
    if (len > 1)
    {
        // preallocate max required size and use same vector
        // has no effect in reqursive calls
        preallocatedBuffer.reserve(len);

        sort_merge(begin, begin + len / 2, compare, preallocatedBuffer);
        sort_merge(begin + len / 2, end, compare, preallocatedBuffer);
        merge(begin, end, compare, preallocatedBuffer);
    }
}
template <typename Container, typename Compare = std::less<>>
inline void sort_merge
    (Container&                                      cont,
     Compare                                         compare = Compare(), 
     std::vector<typename Container::value_type>&    preallocatedBuffer = std::vector<typename Container::value_type>())
{
    sort_merge(cont.begin(), cont.end(), compare, preallocatedBuffer);
}


//============================================================================
//!\fn                 sort_counting<RandomIt, Compare>
//
//!\brief       counting sort for integral values
//!\details     effective if M is relatively small compared to N (elements are in short range)
//!\property    O(M + 2 * N), O(M) memory, where M = max - min + 1
//!\retval      true if sorted, false if required buffer size is greather then max
//!\author      Khrapov
//!\date        4.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
[[nodiscard]] inline bool sort_counting
    (RandomIt       begin, 
     RandomIt       end, 
     Compare        compare         = Compare(), 
     size_t         nMaxBufferSize  = SORT_COUNTING_MAX_BUFFER_SIZE)
{
    static_assert(std::is_integral_v<RandomIt::value_type>, 
                  "Intergral type required for counting sort");

    if (end - begin < 2)
        return true;

    auto minmax = std::minmax_element(begin, end);
    typename RandomIt::value_type min = *minmax.first;
    typename RandomIt::value_type max = *minmax.second;

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

#if 0
//============================================================================
//!\fn                  sort_bucket<RandomIt, Compare>
//
//!\brief  bucket sort
//!\author Khrapov
//!\date   4.03.2020
//============================================================================
template <typename RandomIt, typename Compare = std::less<>>
void sort_bucket(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    using value_type = typename RandomIt::value_type;
    
    static_assert(std::is_arithmetic_v<value_type>,
                  "Intergral or floating point type required for bucket sort");
    
    auto minmax = std::minmax_element(begin, end);
    value_type min   = *minmax.first;
    value_type max   = *minmax.second;
    value_type range = max - min;

    constexpr size_t NUM_BUCKETS = 10;
    std::array<std::vector<value_type>, NUM_BUCKETS> buckets;

    for (RandomIt it = begin; it != end; ++it)
    {
        size_t nBucket = std::min(static_cast<size_t>((static_cast<double>(*it) - min) / range * NUM_BUCKETS), NUM_BUCKETS - 1);
        buckets[nBucket].push_back(*it);
    }

    for (size_t i = 0, size = buckets.size(); i < size; i++)
    {
        size_t nElements = buckets[i].size();
        if (nElements > 0)
        {
            //if (nElements < 10)
                qx::sort(buckets[i].begin(), buckets[i].end(), compare);
            //else
            //    sort_bucket(buckets[i].begin(), buckets[i].end(), compare);
        }

    }

    RandomIt it = begin;
    if constexpr (compare(0, 1))
    {
        for (size_t i = 0; i < buckets.size(); i++)
            for (size_t j = 0; j < buckets[i].size(); j++)
                *it++ = buckets[i][j];
    }
    else
    {
        for (size_t i = buckets.size(); i > 0; i--)
            for (size_t j = 0; j < buckets[i - 1].size(); j++)
                *it++ = buckets[i - 1][j];
    }
}
template <typename Container, typename Compare = std::less<>>
void sort_bucket(Container& cont, Compare compare = Compare())
{
    sort_bucket(cont.begin(), cont.end(), compare);
}
#endif

//============================================================================
//!\fn                     sort<RandomIt, Compare>
//
//!\brief  Sort by the most suitable algorithm
//!\author Khrapov
//!\date   4.03.2020
//============================================================================
template<typename RandomIt, typename Compare = std::less<>>
inline void sort(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    bool bSorted = false;

    // if sort_counting is available
    if constexpr (std::is_integral_v<RandomIt::value_type>)
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
    sort(cont.begin(), cont.end(), compare);
}

}