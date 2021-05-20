//==============================================================================
//
//!\file                       test_components.cpp
//
//!\brief       Tests for qx::components
//!\details     ~
//
//!\author      Khrapov
//!\date        7.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_components.cpp

#if QX_TEST_COMPONENTS

#include <qx/containers/components.h>

#include <string>

class BaseTestComponent
{
    QX_RTTI_BASE_CLASS(BaseTestComponent)

public:

    virtual ~BaseTestComponent(void) = default;

    bool GetConst() const { return true; }
    bool GetNonConst() { return true; }
};
QX_RTTI_BASE_CLASS_IMPL(BaseTestComponent)

class TestComponent : public BaseTestComponent
{
    QX_RTTI_CLASS(TestComponent, BaseTestComponent)

public:

    explicit TestComponent(char ch) : m_TestData(ch) {}
    char GetTestComponentData() const { return m_TestData; }

private:

    char m_TestData = 'x';
};

class ITestComponent : public BaseTestComponent
{
    QX_RTTI_CLASS(ITestComponent, BaseTestComponent)
};

class TestComponent1 : public ITestComponent
{
    QX_RTTI_CLASS(TestComponent1, ITestComponent)

public:

    explicit TestComponent1(int nTestData) : m_nTestData(nTestData) {}
    int GetTestComponent1Data() const { return m_nTestData; }

private:

    int m_nTestData = 0;
};

class TestComponent2 : public ITestComponent
{
    QX_RTTI_CLASS(TestComponent2, ITestComponent)

public:

    explicit TestComponent2(double fTestData) : m_fTestData(fTestData) {}
    double GetTestComponent2Data() const { return m_fTestData; }

private:

    double m_fTestData = 0.0;
};

class TestComponent3 : public ITestComponent
{
    QX_RTTI_CLASS(TestComponent3, ITestComponent)

public:

    explicit TestComponent3(std::string sTestData) : m_sTestData(sTestData) {}
    std::string GetTestComponent3Data() const { return m_sTestData; }

private:

    std::string m_sTestData;
};

TEST(components, main)
{
    qx::components<BaseTestComponent> container;
    EXPECT_EQ(container.size(), 0);
    EXPECT_TRUE(container.empty());

    container.add<TestComponent>('y');
    container.add<TestComponent>('t');
    EXPECT_EQ(container.size(), 2);
    EXPECT_FALSE(container.empty());
    container.clear();
    EXPECT_EQ(container.size(), 0);
    EXPECT_TRUE(container.empty());

    // variadic arguments add
    TestComponent* pTestComponentAdd1 = container.add<TestComponent>('a');
    EXPECT_TRUE(pTestComponentAdd1);
    EXPECT_EQ(container.size(), 1);
    EXPECT_FALSE(container.empty());

    // unique ptr add
    TestComponent* pTestComponentAdd2 = container.add(std::make_unique<TestComponent>('b'));
    EXPECT_TRUE(pTestComponentAdd2);
    EXPECT_EQ(container.size(), 2);

    // add first with own key "ITestComponent"
    ITestComponent* pTestComponent1Add = container.add_to<ITestComponent>(std::make_unique<TestComponent1>(4));
    EXPECT_TRUE(pTestComponent1Add);
    EXPECT_EQ(container.size(), 3);

    // add second with own key "ITestComponent"
    ITestComponent* pTestComponent2Add = container.add_to<ITestComponent>(std::make_unique<TestComponent2>(5.0));
    EXPECT_TRUE(pTestComponent2Add);
    EXPECT_EQ(container.size(), 4);

    ITestComponent* pTestComponent3Add = container.add_to<ITestComponent>(std::make_unique<TestComponent2>(2.0));
    EXPECT_TRUE(pTestComponent3Add);
    EXPECT_EQ(container.size(), 5);

    // get
    TestComponent* pTestComponent = container.get<TestComponent>();
    EXPECT_TRUE(pTestComponentAdd1 == pTestComponent || pTestComponentAdd2 == pTestComponent);
    EXPECT_EQ(pTestComponentAdd1->GetTestComponentData(), 'a');
    EXPECT_EQ(container.size(), 5);

    // get_all
    auto range = container.get_all<ITestComponent>();
    EXPECT_EQ(std::distance(range.first, range.second), 3);
    for (auto it = range.first; it != range.second; ++it)
    {
        EXPECT_TRUE(
            it->second.get() == pTestComponent1Add
            || it->second.get() == pTestComponent2Add
            || it->second.get() == pTestComponent3Add);
    }
    EXPECT_EQ(container.size(), 5);

    // iterators
    for (auto it = container.begin(); it != container.end(); ++it)
        EXPECT_TRUE(it->GetNonConst());

    for (auto it = container.cbegin(); it != container.cend(); ++it)
        EXPECT_TRUE(it->GetConst());

    for (auto& it : container)
        EXPECT_TRUE(it.GetNonConst());

    for (const auto& it : container)
        EXPECT_TRUE(it.GetConst());

    // extract
    qx::components<BaseTestComponent>::pointer pTestComponentOwner
        = container.extract<TestComponent>();

    EXPECT_EQ(pTestComponentOwner.get(), pTestComponent);
    EXPECT_EQ(container.size(), 4);

    // remove
    EXPECT_TRUE(container.remove<TestComponent>());
    EXPECT_EQ(container.size(), 3);

    EXPECT_FALSE(container.remove<TestComponent>());
    EXPECT_EQ(container.size(), 3);

    // remove_all
    container.remove_all<ITestComponent>();
    EXPECT_EQ(container.size(), 0);
    EXPECT_TRUE(container.empty());
}

#endif
