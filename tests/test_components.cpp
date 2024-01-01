/**

    @file      test_components.cpp
    @author    Khrapov
    @date      7.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_components.cpp

#include <qx/containers/components.h>

#include <array>
#include <string>

class ABaseTestComponent : public qx::rtti_root<ABaseTestComponent>
{
    QX_RTTI_CLASS(ABaseTestComponent, qx::rtti_root<ABaseTestComponent>);

public:
    virtual int GetData() const = 0;
    virtual int GetData()       = 0;
};

class CTestComponent1 : public ABaseTestComponent
{
    QX_RTTI_CLASS(CTestComponent1, ABaseTestComponent)

public:
    explicit CTestComponent1(char ch) : m_TestData(ch)
    {
    }
    virtual int GetData() const override
    {
        return m_TestData;
    }
    virtual int GetData() override
    {
        return m_TestData;
    }

private:
    char m_TestData = 'x';
};

class ATestComponent2 : public ABaseTestComponent
{
    QX_RTTI_CLASS(ATestComponent2, ABaseTestComponent)
};

class CTestComponent21 : public ATestComponent2
{
    QX_RTTI_CLASS(CTestComponent21, ATestComponent2)

public:
    explicit CTestComponent21(int nTestData) : m_nTestData(nTestData)
    {
    }
    virtual int GetData() const override
    {
        return m_nTestData;
    }
    virtual int GetData() override
    {
        return m_nTestData;
    }

private:
    int m_nTestData = 0;
};

class CTestComponent22 : public ATestComponent2
{
    QX_RTTI_CLASS(CTestComponent22, ATestComponent2)

public:
    explicit CTestComponent22(double fTestData) : m_fTestData(fTestData)
    {
    }
    virtual int GetData() const override
    {
        return static_cast<int>(m_fTestData);
    }
    virtual int GetData() override
    {
        return static_cast<int>(m_fTestData);
    }

private:
    double m_fTestData = 0.0;
};

class CTestComponent23 : public ATestComponent2
{
    QX_RTTI_CLASS(CTestComponent23, ATestComponent2)

public:
    explicit CTestComponent23(std::string sTestData) : m_sTestData(std::move(sTestData))
    {
    }
    virtual int GetData() const override
    {
        return std::stoi(m_sTestData);
    }
    virtual int GetData() override
    {
        return std::stoi(m_sTestData);
    }

private:
    std::string m_sTestData;
};

struct SComponents
{
    qx::components<ABaseTestComponent> components;

    CTestComponent1* pComponent1 = nullptr;

    CTestComponent21* pComponent21_1 = nullptr;
    CTestComponent21* pComponent21_2 = nullptr;

    CTestComponent22* pComponent22_1 = nullptr;
    CTestComponent22* pComponent22_2 = nullptr;

    CTestComponent23* pComponent23_1 = nullptr;
    CTestComponent23* pComponent23_2 = nullptr;
    CTestComponent23* pComponent23_3 = nullptr;
};

SComponents CreateComponents()
{
    SComponents components;

    components.pComponent1 = components.components.add(std::make_unique<CTestComponent1>('0'), qx::priority::normal);

    components.pComponent21_1 = components.components.add(std::make_unique<CTestComponent21>(1), qx::priority::low);
    components.pComponent21_2 = components.components.add(std::make_unique<CTestComponent21>(2), qx::priority::high);

    components.pComponent22_1 =
        components.components.add(std::make_unique<CTestComponent22>(3.0), qx::priority::very_low);
    components.pComponent22_2 =
        components.components.add(std::make_unique<CTestComponent22>(4.0), qx::priority::normal);

    components.pComponent23_1 =
        components.components.add(std::make_unique<CTestComponent23>("5"), qx::priority::normal);
    components.pComponent23_2 =
        components.components.add(std::make_unique<CTestComponent23>("6"), qx::priority::very_high);
    components.pComponent23_3 =
        components.components.add(std::make_unique<CTestComponent23>("7"), qx::priority::normal, qx::status::disabled);

    return components;
}

TEST(components, remove)
{
    SComponents components = CreateComponents();

    auto pRawComponent1 = components.components.try_get<CTestComponent1>();
    EXPECT_EQ(pRawComponent1, components.pComponent1);

    const auto pComponent1 = components.components.remove(components.pComponent1);
    EXPECT_EQ(pComponent1.get(), components.pComponent1);

    pRawComponent1 = components.components.try_get<CTestComponent1>();
    EXPECT_EQ(pRawComponent1, nullptr);
}

static void TestTryGetTemplate(auto&& components)
{
    EXPECT_EQ(components.components.template try_get<ABaseTestComponent>(), components.pComponent23_2);
    EXPECT_EQ(components.components.template try_get<CTestComponent1>(), components.pComponent1);
    EXPECT_EQ(components.components.template try_get<ATestComponent2>(), components.pComponent23_2);
    EXPECT_EQ(components.components.template try_get<CTestComponent21>(), components.pComponent21_2);
    EXPECT_EQ(components.components.template try_get<CTestComponent22>(), components.pComponent22_2);
    EXPECT_EQ(components.components.template try_get<CTestComponent23>(), components.pComponent23_2);
};

TEST(components, try_get_template)
{
    SComponents components = CreateComponents();
    TestTryGetTemplate(components);
    TestTryGetTemplate(std::as_const(components));
}

TEST(components, get_template)
{
    constexpr auto Test = [](auto&& components)
    {
        EXPECT_EQ(components.components.template get<ABaseTestComponent>(), *components.pComponent23_2);
        EXPECT_EQ(components.components.template get<CTestComponent1>(), *components.pComponent1);
        EXPECT_EQ(components.components.template get<ATestComponent2>(), *components.pComponent23_2);
        EXPECT_EQ(components.components.template get<CTestComponent21>(), *components.pComponent21_2);
        EXPECT_EQ(components.components.template get<CTestComponent22>(), *components.pComponent22_2);
        EXPECT_EQ(components.components.template get<CTestComponent23>(), *components.pComponent23_2);
    };

    SComponents components = CreateComponents();
    Test(components);
    Test(std::as_const(components));
}

TEST(components, try_get_id)
{
    constexpr auto Test = [](auto&& components)
    {
        EXPECT_EQ(components.components.try_get(ABaseTestComponent::get_class_id_static()), components.pComponent23_2);
        EXPECT_EQ(components.components.try_get(CTestComponent1::get_class_id_static()), components.pComponent1);
        EXPECT_EQ(components.components.try_get(ATestComponent2::get_class_id_static()), components.pComponent23_2);
        EXPECT_EQ(components.components.try_get(CTestComponent21::get_class_id_static()), components.pComponent21_2);
        EXPECT_EQ(components.components.try_get(CTestComponent22::get_class_id_static()), components.pComponent22_2);
        EXPECT_EQ(components.components.try_get(CTestComponent23::get_class_id_static()), components.pComponent23_2);
    };

    SComponents components = CreateComponents();
    Test(components);
    Test(std::as_const(components));
}

constexpr bool RefPointerComparator(const ABaseTestComponent* pLeft, const ABaseTestComponent& right)
{
    return pLeft == &right;
}

TEST(components, view)
{
    constexpr auto Test = [](auto&& components)
    {
        const std::array<ABaseTestComponent*, 7> ABaseTestComponent_objects {
            components.pComponent23_2, components.pComponent21_2, components.pComponent1,   components.pComponent22_2,
            components.pComponent23_1, components.pComponent21_1, components.pComponent22_1
        };
        EXPECT_TRUE(std::ranges::equal(ABaseTestComponent_objects, components.components.view(), RefPointerComparator));
        EXPECT_TRUE(std::ranges::equal(
            ABaseTestComponent_objects,
            components.components.template view<ABaseTestComponent>(),
            RefPointerComparator));

        const std::array<CTestComponent1*, 1> CTestComponent1_objects { components.pComponent1 };
        EXPECT_TRUE(std::ranges::equal(
            CTestComponent1_objects,
            components.components.template view<CTestComponent1>(),
            RefPointerComparator));

        const std::array<ATestComponent2*, 6> ATestComponent2_objects {
            components.pComponent23_2, components.pComponent21_2, components.pComponent22_2,
            components.pComponent23_1, components.pComponent21_1, components.pComponent22_1
        };
        EXPECT_TRUE(std::ranges::equal(
            ATestComponent2_objects,
            components.components.template view<ATestComponent2>(),
            RefPointerComparator));

        const std::array<CTestComponent21*, 2> CTestComponent21_objects { components.pComponent21_2,
                                                                          components.pComponent21_1 };
        EXPECT_TRUE(std::ranges::equal(
            CTestComponent21_objects,
            components.components.template view<CTestComponent21>(),
            RefPointerComparator));

        const std::array<CTestComponent22*, 2> CTestComponent22_objects { components.pComponent22_2,
                                                                          components.pComponent22_1 };
        EXPECT_TRUE(std::ranges::equal(
            CTestComponent22_objects,
            components.components.template view<CTestComponent22>(),
            RefPointerComparator));

        const std::array<CTestComponent23*, 2> CTestComponent23_objects { components.pComponent23_2,
                                                                          components.pComponent23_1 };
        EXPECT_TRUE(std::ranges::equal(
            CTestComponent23_objects,
            components.components.template view<CTestComponent23>(),
            RefPointerComparator));
    };

    SComponents components = CreateComponents();
    Test(components);
    Test(std::as_const(components));
}

TEST(components, priority)
{
    SComponents components = CreateComponents();

    components.components.set_priority(components.pComponent22_2, qx::priority::lowest);
    const std::optional<qx::flags<qx::priority>> ePriority =
        components.components.get_priority(components.pComponent22_2);
    ASSERT_TRUE(ePriority);
    EXPECT_EQ(*ePriority, qx::priority::lowest);

    const std::array<ABaseTestComponent*, 7> ABaseTestComponent_objects {
        components.pComponent23_2, components.pComponent21_2, components.pComponent1,   components.pComponent23_1,
        components.pComponent21_1, components.pComponent22_1, components.pComponent22_2
    };
    EXPECT_TRUE(std::ranges::equal(ABaseTestComponent_objects, components.components.view(), RefPointerComparator));
}

TEST(components, status)
{
    SComponents components = CreateComponents();

    EXPECT_EQ(components.components.get_status(components.pComponent23_3), qx::status::disabled);
    const std::array<ABaseTestComponent*, 7> ABaseTestComponent_objectsBefore {
        components.pComponent23_2, components.pComponent21_2, components.pComponent1,   components.pComponent22_2,
        components.pComponent23_1, components.pComponent21_1, components.pComponent22_1
    };
    EXPECT_TRUE(
        std::ranges::equal(ABaseTestComponent_objectsBefore, components.components.view(), RefPointerComparator));

    components.components.set_status(components.pComponent23_3, qx::status::default_value);
    EXPECT_EQ(components.components.get_status(components.pComponent23_3), qx::status::default_value);
    const std::array<ABaseTestComponent*, 8> ABaseTestComponent_objectsAfter {
        components.pComponent23_2, components.pComponent21_2, components.pComponent1,    components.pComponent22_2,
        components.pComponent23_1, components.pComponent23_3, components.pComponent21_1, components.pComponent22_1
    };
    EXPECT_TRUE(
        std::ranges::equal(ABaseTestComponent_objectsAfter, components.components.view(), RefPointerComparator));
}

TEST(components, clear)
{
    SComponents components = CreateComponents();
    EXPECT_FALSE(components.components.empty());
    components.components.clear();
    EXPECT_TRUE(components.components.empty());
    components.pComponent1    = nullptr;
    components.pComponent21_1 = nullptr;
    components.pComponent21_2 = nullptr;
    components.pComponent22_1 = nullptr;
    components.pComponent22_2 = nullptr;
    components.pComponent23_1 = nullptr;
    components.pComponent23_2 = nullptr;
    components.pComponent23_3 = nullptr;
    TestTryGetTemplate(components);
}
