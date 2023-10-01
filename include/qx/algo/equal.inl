/**

    @file      equal.inl
    @author    Khrapov
    @date      20.08.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class it_1_t, class it_2_t, class pred_t>
inline bool equal_rotated(
    it_1_t        range1Begin,
    it_1_t        range1End,
    it_2_t        range2Begin,
    it_2_t        range2End,
    const pred_t& pred) noexcept
{
    auto increment_range_1_it = [range1Begin, range1End](it_1_t itCurrent)
    {
        it_1_t itNext = ++itCurrent;
        return itNext != range1End ? itNext : range1Begin;
    };

    auto compare_starting_with_it = [increment_range_1_it, &pred, range2Begin, range2End](it_1_t range1Start)
    {
        it_1_t range1Current = range1Start;
        for (it_2_t it = range2Begin; it != range2End; ++it)
        {
            if (!pred(*range1Current, *it))
                return false;

            range1Current = increment_range_1_it(range1Current);
        }

        return range1Current == range1Start;
    };

    for (it_1_t it = range1Begin; it != range1End; ++it)
        if (compare_starting_with_it(it))
            return true;

    return false;
}

template<class range_1_t, class range_2_t, class pred_t>
inline bool equal_rotated(const range_1_t& range1, const range_2_t& range2, const pred_t& pred) noexcept
{
    return equal_rotated(range1.begin(), range1.end(), range2.begin(), range2.end(), pred);
}

template<class it_1_t, class it_2_t>
inline bool equal_rotated(it_1_t range1Begin, it_1_t range1End, it_2_t range2Begin, it_2_t range2End) noexcept
{
    return equal_rotated(
        range1Begin,
        range1End,
        range2Begin,
        range2End,
        [](const auto& value1, const auto& value2)
        {
            return value1 == value2;
        });
}

template<class range_1_t, class range_2_t>
inline bool equal_rotated(const range_1_t& range1, const range_2_t& range2) noexcept
{
    return equal_rotated(range1.begin(), range1.end(), range2.begin(), range2.end());
}

} // namespace qx
