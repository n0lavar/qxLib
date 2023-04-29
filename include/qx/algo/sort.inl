/**

    @file      sort.inl
    @author    Khrapov
    @date      29.04.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class random_it_t>
inline bool sort_required(random_it_t begin, random_it_t end)
{
    if (end - begin < 2)
        return false;
    else
        return true;
}

template<class random_it_t, class compare_t>
void sort_insertion(random_it_t begin, random_it_t end, compare_t compare)
{
    if (!sort_required(begin, end))
        return;

    for (random_it_t i = begin + 1; i != end; ++i) //-V756
        for (random_it_t j = i; j != begin && compare(*j, *(j - 1)); --j)
            std::iter_swap(j - 1, j);
}

template<class container_t, class compare_t>
void sort_insertion(container_t& cont, compare_t compare)
{
    sort_insertion(cont.begin(), cont.end(), compare);
}

template<class random_it_t, class compare_t>
void sort_selection(random_it_t begin, random_it_t end, compare_t compare)
{
    if (!sort_required(begin, end))
        return;

    for (random_it_t it = begin; it != end; ++it)
    {
        random_it_t itMin = it;
        for (random_it_t j = it + 1; j != end; ++j)
            if (compare(*j, *itMin))
                itMin = j;

        std::iter_swap(it, itMin);
    }
}

template<class container_t, class compare_t>
void sort_selection(container_t& cont, compare_t compare)
{
    sort_selection(cont.begin(), cont.end(), compare);
}

template<class random_it_t, class compare_t>
void sort_bubble(random_it_t begin, random_it_t end, compare_t compare)
{
    if (!sort_required(begin, end))
        return;

    bool bSorted = false;
    while (!bSorted)
    {
        bSorted = true;
        for (random_it_t it = begin, itEnd = end - 1; it != itEnd; ++it)
        {
            if (compare(*(it + 1), *it))
            {
                std::iter_swap(it, it + 1);
                bSorted = false;
            }
        }
    }
}

template<class container_t, class compare_t>
void sort_bubble(container_t& cont, compare_t compare)
{
    sort_bubble(cont.begin(), cont.end(), compare);
}

template<class random_it_t, class compare_t>
void adjust_heap(random_it_t begin, size_t nHeapSize, size_t nPosition, compare_t compare)
{
    using iter_diff = decltype(random_it_t() - random_it_t());

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

            if (compare(*(begin + static_cast<iter_diff>(nChildPos)), *(begin + static_cast<iter_diff>(nPosition))))
            {
                return;
            }
            else
            {
                std::iter_swap(begin + static_cast<iter_diff>(nPosition), begin + static_cast<iter_diff>(nChildPos));
            }
        }
        nPosition = nChildPos;
    }
}

template<class random_it_t, class compare_t>
void make_heap(random_it_t begin, random_it_t end, compare_t compare)
{
    auto max = end - begin;
    for (int i = static_cast<int>(max) / 2; i >= 0; --i)
    {
        adjust_heap(
            begin,
            static_cast<size_t>(max),
            static_cast<size_t>(i), //-V201
            compare);
    }
}

template<class random_it_t, class compare_t>
void sort_heap(random_it_t begin, random_it_t end, compare_t compare)
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

template<class container_t, class compare_t>
void sort_heap(container_t& cont, compare_t compare)
{
    qx::sort_heap(cont.begin(), cont.end(), compare);
}

template<class random_it_t, class compare_t>
void sort_quick_hoare(random_it_t begin, random_it_t end, compare_t compare)
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

template<class container_t, class compare_t>
void sort_quick_hoare(container_t& cont, compare_t compare)
{
    sort_quick_hoare(cont.begin(), cont.end(), compare);
}

template<class random_it_t, class compare_t>
void sort_quick_three_way(random_it_t begin, random_it_t end, compare_t compare)
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

template<class container_t, class compare_t>
void sort_quick_three_way(container_t& cont, compare_t compare)
{
    sort_quick_three_way(cont.begin(), cont.end(), compare);
}

template<class random_it_t, class compare_t>
void sort_quick_dual_pivot(random_it_t begin, random_it_t end, compare_t compare)
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

template<class container_t, class compare_t>
void sort_quick_dual_pivot(container_t& cont, compare_t compare)
{
    sort_quick_dual_pivot(cont.begin(), cont.end(), compare);
}

template<class random_it_t, class compare_t>
void merge(random_it_t begin, random_it_t end, compare_t compare, vector_of_values<random_it_t>* pPreallocatedBuffer)
{
    using iter_diff = decltype(random_it_t() - random_it_t());

    u64         nInd1 = 0;
    u64         nInd2 = 0;
    random_it_t mid   = begin + (end - begin) / 2;

    const bool bCreateBuffer = !pPreallocatedBuffer;
    if (bCreateBuffer)
        pPreallocatedBuffer = new vector_of_values<random_it_t>;

    pPreallocatedBuffer->resize(static_cast<size_t>(end - begin));

    // merge
    while ((begin + static_cast<iter_diff>(nInd1) < mid) && (mid + static_cast<iter_diff>(nInd2) < end))
    {
        if (compare(*(begin + static_cast<iter_diff>(nInd1)), *(mid + static_cast<iter_diff>(nInd2))))
        {
            (*pPreallocatedBuffer)[nInd1 + nInd2] = *(begin + static_cast<iter_diff>(nInd1));

            nInd1++;
        }
        else
        {
            (*pPreallocatedBuffer)[nInd1 + nInd2] = *(mid + static_cast<iter_diff>(nInd2));

            nInd2++;
        }
    }

    // append tails
    while (begin + static_cast<iter_diff>(nInd1) < mid)
    {
        (*pPreallocatedBuffer)[nInd1 + nInd2] = *(begin + static_cast<iter_diff>(nInd1));

        nInd1++;
    }

    while (mid + static_cast<iter_diff>(nInd2) < end)
    {
        (*pPreallocatedBuffer)[nInd1 + nInd2] = *(mid + static_cast<iter_diff>(nInd2));

        nInd2++;
    }

    // copy to source
    for (auto it = begin; it < end; ++it)
        *it = (*pPreallocatedBuffer)[static_cast<size_t>(it - begin)];

    if (bCreateBuffer)
        delete pPreallocatedBuffer;
}

template<class random_it_t, class compare_t>
void sort_merge(
    random_it_t                    begin,
    random_it_t                    end,
    compare_t                      compare,
    vector_of_values<random_it_t>* pPreallocatedBuffer)
{
    if (!sort_required(begin, end))
        return;

    const bool bCreateBuffer = !pPreallocatedBuffer;
    if (bCreateBuffer)
        pPreallocatedBuffer = new vector_of_values<random_it_t>;

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

template<class container_t, class compare_t>
void sort_merge(
    container_t&                                      cont,
    compare_t                                         compare,
    vector_of_values<typename container_t::iterator>* pPreallocatedBuffer)
{
    sort_merge(cont.begin(), cont.end(), compare, pPreallocatedBuffer);
}

template<class random_it_t, class compare_t>
bool sort_counting(random_it_t begin, random_it_t end, compare_t compare, size_t nMaxBufferSize)
{
    static_assert(std::is_integral_v<iterator_value_t<random_it_t>>, "Integral type required for counting sort");

    if (end - begin < 2)
        return true;

    auto minMax = std::minmax_element(begin, end);
    auto min    = *minMax.first;
    auto max    = *minMax.second;

    const size_t nSizeRequired = static_cast<size_t>(max) - min + 1;
    if (nSizeRequired <= nMaxBufferSize)
    {
        std::vector<size_t> counts(nSizeRequired, 0);

        for (random_it_t it = begin; it < end; ++it)
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
                begin = std::fill_n(begin, counts[nSizeRequired - i - 1], max--);
        }

        return true;
    }
    else
        return false;
}

template<class container_t, class compare_t>
bool sort_counting(container_t& cont, compare_t compare, size_t nMaxBufferSize)
{
    return sort_counting(cont.begin(), cont.end(), compare, nMaxBufferSize);
}

template<class random_it_t, class compare_t>
void sort(random_it_t begin, random_it_t end, compare_t compare)
{
    bool bSorted = false;

    // if sort_counting is available
    if constexpr (std::is_integral_v<iterator_value_t<random_it_t>>)
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

template<class container_t, class compare_t>
void sort(container_t& cont, compare_t compare)
{
    qx::sort(cont.begin(), cont.end(), compare);
}

} // namespace qx
