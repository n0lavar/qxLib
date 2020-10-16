//==============================================================================
//
//!\file                           main.cpp
//
//!\brief       Entry point for tests
//!\details     ~
//
//!\author      Khrapov
//!\date        8.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

//V_EXCLUDE_PATH *main.cpp

#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
