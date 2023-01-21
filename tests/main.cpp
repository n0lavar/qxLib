/**

    @file      main.cpp
    @author    Khrapov
    @date      8.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

//V_EXCLUDE_PATH *main.cpp

#include <qx/macros/suppress_warnings.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <gtest/gtest.h>
QX_POP_SUPPRESS_WARNINGS();

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
