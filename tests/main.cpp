//==============================================================================
//
//!\file                           main.cpp
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        8.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <config.h>
#include <gtest/gtest.h>

#if QX_BENCH_SORT
    #include <bench_sort.h>
#endif

int main(int argc, char** argv)
{
#if QX_BENCH_SORT
    bench_sort();
#endif

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
