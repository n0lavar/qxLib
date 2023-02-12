/**

    @file      test_unique_objects_pool.cpp
    @author    Khrapov
    @date      11.02.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_unique_objects_pool.cpp

#include <qx/containers/unique_objects_pool.h>
#include <string>

void test_pool(bool bAutoShrink)
{
    qx::unique_objects_pool<std::string> pool(bAutoShrink);

    EXPECT_EQ(pool.size(), 0);
    EXPECT_TRUE(pool.empty());

    qx::unique_objects_pool<std::string>::token str1Token = pool.get_or_create("str1");

    EXPECT_EQ(pool.size(), 1);
    EXPECT_FALSE(pool.empty());
    EXPECT_EQ(*str1Token, "str1");
    EXPECT_TRUE(str1Token);

    {
        qx::unique_objects_pool<std::string>::token str2Token1 = pool.get_or_create("str2");

        EXPECT_EQ(pool.size(), 2);
        EXPECT_FALSE(pool.empty());
        EXPECT_EQ(*str2Token1, "str2");
        EXPECT_TRUE(str2Token1);

        qx::unique_objects_pool<std::string>::token str2Token2 = pool.get_or_create("str2");

        EXPECT_EQ(pool.size(), 2);
        EXPECT_FALSE(pool.empty());
        EXPECT_EQ(*str2Token2, "str2");
        EXPECT_EQ(str2Token1, str2Token2);
        EXPECT_TRUE(str2Token2);
    }

    EXPECT_EQ(pool.size(), bAutoShrink ? 1 : 2);
    EXPECT_FALSE(pool.empty());
    EXPECT_EQ(*str1Token, "str1");
    EXPECT_TRUE(str1Token);
    pool.shrink();

    EXPECT_EQ(pool.size(), 1);
    EXPECT_FALSE(pool.empty());
    EXPECT_EQ(*str1Token, "str1");
    EXPECT_TRUE(str1Token);
}

TEST(unique_objects_pool, main)
{
    test_pool(true);
    test_pool(false);
}
