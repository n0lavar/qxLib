/**

    @file      link.gtest.cpp
    @author    Khrapov
    @date      18.07.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

**/

#include <common.h>

#include <qx/memory/link.h>

struct STest
{
    STest(int _nValue) : nValue(_nValue)
    {
    }

    int nValue = 6;
};

static void Test6(const qx::link<STest>& pLink)
{
    const qx::link<STest>::lock_ptr pLock = pLink.lock();
    ASSERT_TRUE(pLock);
    EXPECT_EQ(pLock->nValue, 6);
    EXPECT_EQ((*pLock).nValue, 6);
    EXPECT_EQ(pLock.get()->nValue, 6);
}

TEST(link, empty_and_assignment)
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

    Test6(pLink1);

    EXPECT_TRUE(pShared);
    EXPECT_TRUE(pLink1);
    EXPECT_FALSE(pLink1.expired());
}

TEST(link, copy_and_reset)
{
    std::shared_ptr<STest> pShared = std::make_shared<STest>(6);
    qx::link<STest> pLink1 = pShared;

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
}

TEST(link, copy_and_null_assignment)
{
    std::shared_ptr<STest> pShared = std::make_shared<STest>(6);
    qx::link<STest> pLink2 = pShared;

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
}

TEST(link, converting_weak_pointer)
{
    struct derived : STest
    {
        derived() : STest(6) {}
    };

    auto pShared = std::make_shared<derived>();
    std::weak_ptr<derived> pWeak = pShared;
    qx::link<STest> copied(pWeak);
    EXPECT_FALSE(pWeak.expired());
    EXPECT_EQ(pWeak.lock().get(), pShared.get());
    Test6(copied);

    qx::link<STest> moved(std::move(pWeak));
    EXPECT_TRUE(pWeak.expired());
    Test6(moved);
    EXPECT_EQ(pShared.use_count(), 1);

    pShared.reset();
    EXPECT_TRUE(copied.expired());
    EXPECT_TRUE(moved.expired());
}

TEST(link, expiration)
{
    std::shared_ptr<STest> pShared = std::make_shared<STest>(6);
    qx::link<STest> pLink2 = pShared;

    pShared.reset();
    EXPECT_FALSE(pShared);
    EXPECT_FALSE(pLink2);
    EXPECT_TRUE(pLink2.expired());
    EXPECT_FALSE(pLink2.lock());
}
