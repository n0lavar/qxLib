/**

    @file      coalesce.gtest.cpp
    @author    Khrapov
    @date      27.09.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#include <common.h>

#include <qx/coalesce.h>

//V_EXCLUDE_PATH *.gtest.cpp

TEST(coalesce, return_t)
{
    EXPECT_EQ(qx::coalesce<int>(0, false, 1u), 1);
    EXPECT_EQ(qx::coalesce<int>(0, false, 2u), 2);
    EXPECT_EQ(qx::coalesce<int>(1, false, 2u), 1);
    EXPECT_EQ(qx::coalesce<int>(0, false, 2u, 1ll), 2);
}

TEST(coalesce, same_variadic_args_unique_ptr)
{
    std::unique_ptr<int> pFirst;
    std::unique_ptr<int> pSecond = std::make_unique<int>(2);
    std::unique_ptr<int> pThird  = std::make_unique<int>(3);

    std::unique_ptr<int> pResult = qx::coalesce(std::move(pFirst), std::move(pSecond), std::move(pThird));
    EXPECT_TRUE(pResult);
    EXPECT_EQ(*pResult, 2);
}

TEST(coalesce, same_variadic_args_unique_ptr_ref)
{
    std::unique_ptr<int> pFirst;
    std::unique_ptr<int> pSecond = std::make_unique<int>(2);
    std::unique_ptr<int> pThird  = std::make_unique<int>(3);

    std::unique_ptr<int>& pResult = qx::coalesce(pFirst, pSecond, pThird);
    EXPECT_TRUE(pResult);
    EXPECT_EQ(*pResult, 2);
}

TEST(coalesce, same_variadic_args_shared_ptr)
{
    std::shared_ptr<int> pFirst;
    std::shared_ptr<int> pSecond = std::make_shared<int>(2);
    std::shared_ptr<int> pThird  = std::make_shared<int>(3);

    std::shared_ptr<int> pResult = qx::coalesce(std::move(pFirst), std::move(pSecond), std::move(pThird));
    EXPECT_TRUE(pResult);
    EXPECT_EQ(*pResult, 2);
}

TEST(coalesce, same_variadic_args_shared_ptr_ref)
{
    std::shared_ptr<int> pFirst;
    std::shared_ptr<int> pSecond = std::make_shared<int>(2);
    std::shared_ptr<int> pThird  = std::make_shared<int>(3);

    std::shared_ptr<int>& pResult = qx::coalesce(pFirst, pSecond, pThird);
    EXPECT_TRUE(pResult);
    EXPECT_EQ(*pResult, 2);
}
