/**

    @file      destruction_callback.gtest.cpp
    @author    Khrapov
    @date      26.06.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

**/

#include <common.h>

#include <qx/destruction_callback.h>

TEST(destruction_callback, main)
{
    {
        // destroyed successfully
        const qx::destruction_callback callback;
    }

    int num = 0;
    {
        const qx::destruction_callback callback(
            [&num]()
            {
                num = 1;
            });
    }
    EXPECT_EQ(num, 1);
}
