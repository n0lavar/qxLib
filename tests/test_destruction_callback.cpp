/**

    @file      test_destruction_callback.cpp
    @author    Khrapov
    @date      26.06.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

#include <test_config.h>

//V_EXCLUDE_PATH *test_destruction_callback.cpp

#if QX_TEST_DESTRUCTION_CALLBACK

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

#endif
