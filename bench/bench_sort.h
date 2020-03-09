//============================================================================
//
//!\file                         bench_sort.h
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        9.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <qx/alg/sort.h>
#include <qx/other/benchmark.h>
#include <random>

using _b_vec = std::vector<i64>;

//============================================================================
//!\fn                         bench_func<Func>
//
//!\brief  Run function benchmark
//!\param  sorting - vector for sorting
//!\param  func    - sorting function
//!\retval         - execution time (sec)
//!\author Khrapov
//!\date   10.03.2020
//============================================================================
template<typename Func>
inline double bench_func(_b_vec& sorting, const Func& func)
{
    qx::benchmark bench;
    func(sorting);
    return bench.End();
}

//============================================================================
//!\fn                        bench_sort_n<Func>
//
//!\brief  Run function benchmark n times and calc avarage time
//!\param  unsorted       - randomly generated unsorted vector
//!\param  func           - sorting function
//!\param  num_iterations - number of iterations. figher is more precisely
//!\retval                - avarage execution time
//!\author Khrapov
//!\date   10.03.2020
//============================================================================
template<typename Func>
inline double bench_sort_n(const _b_vec& unsorted, const Func& func, const size_t num_iterations)
{
    _b_vec sorting;
    double fTotal = 0.0;
    for (size_t i = 0; i < num_iterations; i++)
    {
        sorting = unsorted;
        fTotal += bench_func(sorting, func);
    }

    return fTotal / static_cast<double>(num_iterations);
}

//============================================================================
//!\fn                           bench_sort_v
//
//!\brief  Run function benchmark with different sort functions and print results
//!\param  min_element    - min element for gererating unsorted vector
//!\param  max_element    - max element for gererating unsorted vector
//!\param  vector_size    - unsorted vector size
//!\param  num_iterations - number of iterations. figher is more precisely
//!\author Khrapov
//!\date   10.03.2020
//============================================================================
inline void bench_sort_v(i64 min_element, i64 max_element, size_t vector_size, size_t num_iterations)
{
    std::default_random_engine generator(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<i64> fillDistribution(min_element, max_element);

    _b_vec unsorted(vector_size);
    for (size_t i = 0; i < unsorted.size(); i++)
        unsorted[i] = fillDistribution(generator);

    printf("%-26.10lf", bench_sort_n(unsorted, [] (_b_vec& vec) { std::sort                 (vec.begin(), vec.end(), std::less<>()); }, num_iterations));
    printf("%-26.10lf", bench_sort_n(unsorted, [] (_b_vec& vec) { qx::sort_heap             (vec.begin(), vec.end(), std::less<>()); }, num_iterations));
    printf("%-26.10lf", bench_sort_n(unsorted, [] (_b_vec& vec) { qx::sort_quick_hoare      (vec.begin(), vec.end(), std::less<>()); }, num_iterations));
    printf("%-26.10lf", bench_sort_n(unsorted, [] (_b_vec& vec) { qx::sort_quick_three_way  (vec.begin(), vec.end(), std::less<>()); }, num_iterations));
    printf("%-26.10lf", bench_sort_n(unsorted, [] (_b_vec& vec) { qx::sort_quick_dual_pivot (vec.begin(), vec.end(), std::less<>()); }, num_iterations));
    printf("%-26.10lf", bench_sort_n(unsorted, [] (_b_vec& vec) { qx::sort_merge            (vec.begin(), vec.end(), std::less<>()); }, num_iterations));
    printf("%-26.10lf", bench_sort_n(unsorted, [] (_b_vec& vec) { bool b = qx::sort_counting(vec.begin(), vec.end(), std::less<>()); }, num_iterations));
    printf("\n");
}

//============================================================================
//!\fn                            bench_sort
//
//!\brief  Run sort functions benchmark and print results
//!\author Khrapov
//!\date   10.03.2020
//============================================================================
inline void bench_sort()
{
    printf("std::sort                 "
           "qx::sort_heap             "
           "qx::sort_quick_hoare      "
           "qx::sort_quick_three_way  "
           "qx::sort_quick_dual_pivot "
           "qx::sort_merge            "
           "qx::sort_counting\n\n"
    );

    constexpr size_t NUM_ITERS = 1000;

    bench_sort_v(-100, 100, 10,       NUM_ITERS);
    bench_sort_v(-100, 100, 100,      NUM_ITERS);
    bench_sort_v(-100, 100, 1000,     NUM_ITERS);
    bench_sort_v(-100, 100, 10000,    NUM_ITERS);
    bench_sort_v(-100, 100, 100000,   NUM_ITERS);
    bench_sort_v(-100, 100, 1000000,  NUM_ITERS);
    bench_sort_v(-100, 100, 10000000, NUM_ITERS);
    printf("\n");

    bench_sort_v(-100000, 100000, 10,       NUM_ITERS);
    bench_sort_v(-100000, 100000, 100,      NUM_ITERS);
    bench_sort_v(-100000, 100000, 1000,     NUM_ITERS);
    bench_sort_v(-100000, 100000, 10000,    NUM_ITERS);
    bench_sort_v(-100000, 100000, 100000,   NUM_ITERS);
    bench_sort_v(-100000, 100000, 1000000,  NUM_ITERS);
    bench_sort_v(-100000, 100000, 10000000, NUM_ITERS);
    printf("\n");

    bench_sort_v(INT_MIN, INT_MAX, 10,       NUM_ITERS);
    bench_sort_v(INT_MIN, INT_MAX, 100,      NUM_ITERS);
    bench_sort_v(INT_MIN, INT_MAX, 1000,     NUM_ITERS);
    bench_sort_v(INT_MIN, INT_MAX, 10000,    NUM_ITERS);
    bench_sort_v(INT_MIN, INT_MAX, 100000,   NUM_ITERS);
    bench_sort_v(INT_MIN, INT_MAX, 1000000,  NUM_ITERS);
    bench_sort_v(INT_MIN, INT_MAX, 10000000, NUM_ITERS);
    printf("\n");

}