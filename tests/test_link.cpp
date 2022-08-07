/**

    @file      test_link.cpp
    @author    Khrapov
    @date      18.07.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

#include <common.h>

//V_EXCLUDE_PATH *test_link.cpp

#include <qx/link.h>

struct STest
{
    STest(int _nValue) : nValue(_nValue)
    {
    }

    int nValue = 6;
};

TEST(link, main)
{
    std::shared_ptr<STest> pShared = std::make_shared<STest>(6);
    qx::link<STest>        pLink1;
    EXPECT_TRUE(pShared);
    EXPECT_FALSE(pLink1);
    EXPECT_TRUE(pLink1.expired());

    pLink1 = pShared;
    EXPECT_TRUE(pShared);
    EXPECT_TRUE(pLink1);
    EXPECT_FALSE(pLink1.expired());

    auto Test6 = [](const auto& pLink)
    {
        if (const qx::link<STest>::lock_ptr pLock = pLink.lock())
        {
            EXPECT_EQ(pLock->nValue, 6);
            EXPECT_EQ((*pLock).nValue, 6);
            EXPECT_EQ(pLock.get()->nValue, 6);
        }
        else
        {
            EXPECT_TRUE(false);
        }
    };
    Test6(pLink1);

    EXPECT_TRUE(pShared);
    EXPECT_TRUE(pLink1);
    EXPECT_FALSE(pLink1.expired());

    qx::link<STest> pLink2 = pLink1;
    EXPECT_TRUE(pShared);
    EXPECT_TRUE(pLink1);
    EXPECT_TRUE(pLink2);
    EXPECT_FALSE(pLink1.expired());
    EXPECT_FALSE(pLink2.expired());
    Test6(pLink1);
    Test6(pLink2);

    pLink1.reset();
    EXPECT_TRUE(pShared);
    EXPECT_FALSE(pLink1);
    EXPECT_TRUE(pLink2);
    EXPECT_TRUE(pLink1.expired());
    EXPECT_FALSE(pLink2.expired());
    Test6(pLink2);

    qx::link<STest> pLink3 = pLink2;
    EXPECT_TRUE(pShared);
    EXPECT_TRUE(pLink2);
    EXPECT_TRUE(pLink3);
    EXPECT_FALSE(pLink2.expired());
    EXPECT_FALSE(pLink3.expired());
    Test6(pLink2);
    Test6(pLink3);

    pLink3 = nullptr;
    EXPECT_TRUE(pShared);
    EXPECT_FALSE(pLink3);
    EXPECT_TRUE(pLink2);
    EXPECT_TRUE(pLink3.expired());
    EXPECT_FALSE(pLink2.expired());
    Test6(pLink2);

    pShared.reset();
    EXPECT_FALSE(pShared);
    EXPECT_FALSE(pLink2);
    EXPECT_TRUE(pLink2.expired());
    EXPECT_FALSE(pLink2.lock());
}
