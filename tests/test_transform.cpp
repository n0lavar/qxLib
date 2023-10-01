/**

    @file      test_transform.cpp
    @author    Khrapov
    @date      1.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_transform.cpp

#include <qx/algo/transform.h>
#include <qx/containers/string/string.h>

#include <algorithm>

TEST(transform, main)
{
    std::vector numbers { 1, 2, 3 };

    std::vector<qx::string> strings1;
    {
        strings1.resize(numbers.size());
        std::transform(
            numbers.begin(),
            numbers.end(),
            strings1.begin(),
            [](int nNumber)
            {
                return qx::string::static_from(nNumber);
            });
    }

    std::vector<qx::string> strings2;
    {
        strings2 = qx::transform_return<std::vector>(
            numbers,
            [](int nNumber)
            {
                return qx::string::static_from(nNumber);
            });
    }

    EXPECT_EQ(strings1, strings2);
}