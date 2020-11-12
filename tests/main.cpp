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

#include <qx/suppress_warnings.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS
#include <gtest/gtest.h>
QX_POP_SUPPRESS_WARNINGS

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
