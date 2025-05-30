/**

    @file      test_rtti.cpp
    @author    Khrapov
    @date      26.08.2020
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_rtti.cpp

#include <qx/containers/string/string_utils.h>
#include <qx/rtti/rtti.h>
#include <qx/rtti/rtti_cast.h>

#include <memory>
#include <source_location>

class CRttiBase : public qx::rtti_root<>
{
    QX_RTTI_CLASS(CRttiBase, qx::rtti_root<>);
};

class CBase1 : public CRttiBase
{
    QX_RTTI_CLASS(CBase1, CRttiBase);
};

class CDerived1_1 : public CBase1
{
    QX_RTTI_CLASS(CDerived1_1, CBase1);
};

class CDerived1_2 : public CBase1
{
    QX_RTTI_CLASS(CDerived1_2, CBase1);
};

class CDerived1_21 : public CDerived1_2
{
    QX_RTTI_CLASS(CDerived1_21, CDerived1_2);
};

class CDerived1_22 : public CDerived1_2
{
    QX_RTTI_CLASS(CDerived1_22, CDerived1_2);
};

class CDerived1_221 : public CDerived1_22
{
    QX_RTTI_CLASS(CDerived1_221, CDerived1_22);
};

class CDerived1_222 : public CDerived1_22
{
    QX_RTTI_CLASS(CDerived1_222, CDerived1_22);
};

class CDerived1_3 : public CBase1
{
    QX_RTTI_CLASS(CDerived1_3, CBase1);
};


class CBase2 : public CRttiBase
{
    QX_RTTI_CLASS(CBase2, CRttiBase);
};

class CDerived2_1 : public CBase2
{
    QX_RTTI_CLASS(CDerived2_1, CBase2);
};

class CDerived2_2 : public CBase2
{
    QX_RTTI_CLASS(CDerived2_2, CBase2);
};

class CDerived2_3 : public CBase2
{
    QX_RTTI_CLASS(CDerived2_3, CBase2);
};

class CDerived2_31 : public CDerived2_3
{
    QX_RTTI_CLASS(CDerived2_31, CDerived2_3);
};

class CDerived2_32 : public CDerived2_3
{
    QX_RTTI_CLASS(CDerived2_32, CDerived2_3);
};

const std::unique_ptr<CBase1>        p1     = std::make_unique<CBase1>();
const std::unique_ptr<CDerived1_1>   p1_1   = std::make_unique<CDerived1_1>();
const std::unique_ptr<CDerived1_2>   p1_2   = std::make_unique<CDerived1_2>();
const std::unique_ptr<CDerived1_21>  p1_21  = std::make_unique<CDerived1_21>();
const std::unique_ptr<CDerived1_22>  p1_22  = std::make_unique<CDerived1_22>();
const std::unique_ptr<CDerived1_221> p1_221 = std::make_unique<CDerived1_221>();
const std::unique_ptr<CDerived1_222> p1_222 = std::make_unique<CDerived1_222>();
const std::unique_ptr<CDerived1_3>   p1_3   = std::make_unique<CDerived1_3>();


//----------------------------------- usings -----------------------------------

static_assert(std::is_same_v<CDerived1_1::base_class_type, qx::rtti_root<>>);
static_assert(std::is_same_v<CDerived1_2::base_class_type, qx::rtti_root<>>);
static_assert(std::is_same_v<CDerived1_21::base_class_type, qx::rtti_root<>>);
static_assert(std::is_same_v<CDerived1_22::base_class_type, qx::rtti_root<>>);
static_assert(std::is_same_v<CDerived1_3::base_class_type, qx::rtti_root<>>);

static_assert(std::is_same_v<CDerived2_1::base_class_type, qx::rtti_root<>>);
static_assert(std::is_same_v<CDerived2_2::base_class_type, qx::rtti_root<>>);
static_assert(std::is_same_v<CDerived2_3::base_class_type, qx::rtti_root<>>);
static_assert(std::is_same_v<CDerived2_31::base_class_type, qx::rtti_root<>>);
static_assert(std::is_same_v<CDerived2_32::base_class_type, qx::rtti_root<>>);

static_assert(std::is_same_v<CDerived1_1::super_class_type, CBase1>);
static_assert(std::is_same_v<CDerived1_2::super_class_type, CBase1>);
static_assert(std::is_same_v<CDerived1_21::super_class_type, CDerived1_2>);
static_assert(std::is_same_v<CDerived1_22::super_class_type, CDerived1_2>);
static_assert(std::is_same_v<CDerived1_3::super_class_type, CBase1>);

static_assert(std::is_same_v<CDerived2_1::super_class_type, CBase2>);
static_assert(std::is_same_v<CDerived2_2::super_class_type, CBase2>);
static_assert(std::is_same_v<CDerived2_3::super_class_type, CBase2>);
static_assert(std::is_same_v<CDerived2_31::super_class_type, CDerived2_3>);
static_assert(std::is_same_v<CDerived2_32::super_class_type, CDerived2_3>);

static_assert(std::is_same_v<CDerived1_1::this_class_type, CDerived1_1>);
static_assert(std::is_same_v<CDerived1_2::this_class_type, CDerived1_2>);
static_assert(std::is_same_v<CDerived1_21::this_class_type, CDerived1_21>);
static_assert(std::is_same_v<CDerived1_22::this_class_type, CDerived1_22>);
static_assert(std::is_same_v<CDerived1_3::this_class_type, CDerived1_3>);

static_assert(std::is_same_v<CDerived2_1::this_class_type, CDerived2_1>);
static_assert(std::is_same_v<CDerived2_2::this_class_type, CDerived2_2>);
static_assert(std::is_same_v<CDerived2_3::this_class_type, CDerived2_3>);
static_assert(std::is_same_v<CDerived2_31::this_class_type, CDerived2_31>);
static_assert(std::is_same_v<CDerived2_32::this_class_type, CDerived2_32>);



//---------------------------- get_class_name_static ---------------------------

static_assert(CBase1::get_class_name_static() == QX_TEXT("CBase1"));
static_assert(CDerived1_1::get_class_name_static() == QX_TEXT("CDerived1_1"));
static_assert(CDerived1_2::get_class_name_static() == QX_TEXT("CDerived1_2"));
static_assert(CDerived1_21::get_class_name_static() == QX_TEXT("CDerived1_21"));
static_assert(CDerived1_22::get_class_name_static() == QX_TEXT("CDerived1_22"));
static_assert(CDerived1_221::get_class_name_static() == QX_TEXT("CDerived1_221"));
static_assert(CDerived1_222::get_class_name_static() == QX_TEXT("CDerived1_222"));
static_assert(CDerived1_3::get_class_name_static() == QX_TEXT("CDerived1_3"));

// ------------------------------------ RTTI -----------------------------------

TEST(rtti, class_id)
{
    EXPECT_TRUE(static_cast<CBase1*>(p1_21.get())->get_class_id() == CDerived1_21::get_class_id_static());
    EXPECT_TRUE(static_cast<CDerived1_2*>(p1_21.get())->get_class_id() == CDerived1_21::get_class_id_static());
    EXPECT_TRUE(p1_21->get_class_id() == CDerived1_21::get_class_id_static());

    std::set<qx::class_id> ids;
    auto                   CheckId = [&ids](qx::class_id id)
    {
        auto ret = ids.insert(id);
        EXPECT_TRUE(ret.second) << "existing id must be unique";
    };

    CheckId(CDerived1_1::get_class_id_static());
    CheckId(CDerived1_2::get_class_id_static());
    CheckId(CDerived1_21::get_class_id_static());
    CheckId(CDerived1_22::get_class_id_static());
    CheckId(CDerived1_221::get_class_id_static());
    CheckId(CDerived1_222::get_class_id_static());
    CheckId(CDerived1_3::get_class_id_static());

    CheckId(CDerived2_1::get_class_id_static());
    CheckId(CDerived2_2::get_class_id_static());
    CheckId(CDerived2_3::get_class_id_static());
    CheckId(CDerived2_31::get_class_id_static());
    CheckId(CDerived2_32::get_class_id_static());
}

template<class T>
void TestDerivedFrom(const auto& pClass, bool bExpect, std::source_location sr = std::source_location::current())
{
    EXPECT_EQ(pClass->template is_derived_from<T>(), bExpect);
    EXPECT_EQ(pClass->is_derived_from_id(T::get_class_id_static()), bExpect);
}

TEST(rtti, is_derived_from)
{
    TestDerivedFrom<CBase1>(p1, true);
    TestDerivedFrom<CBase1>(p1_1, true);
    TestDerivedFrom<CBase1>(p1_2, true);
    TestDerivedFrom<CBase1>(p1_21, true);
    TestDerivedFrom<CBase1>(p1_22, true);
    TestDerivedFrom<CBase1>(p1_221, true);
    TestDerivedFrom<CBase1>(p1_222, true);
    TestDerivedFrom<CBase1>(p1_3, true);

    TestDerivedFrom<CDerived1_1>(p1, false);
    TestDerivedFrom<CDerived1_1>(p1_1, true);
    TestDerivedFrom<CDerived1_1>(p1_2, false);
    TestDerivedFrom<CDerived1_1>(p1_21, false);
    TestDerivedFrom<CDerived1_1>(p1_22, false);
    TestDerivedFrom<CDerived1_1>(p1_221, false);
    TestDerivedFrom<CDerived1_1>(p1_222, false);
    TestDerivedFrom<CDerived1_1>(p1_3, false);

    TestDerivedFrom<CDerived1_2>(p1, false);
    TestDerivedFrom<CDerived1_2>(p1_1, false);
    TestDerivedFrom<CDerived1_2>(p1_2, true);
    TestDerivedFrom<CDerived1_2>(p1_21, true);
    TestDerivedFrom<CDerived1_2>(p1_22, true);
    TestDerivedFrom<CDerived1_2>(p1_221, true);
    TestDerivedFrom<CDerived1_2>(p1_222, true);
    TestDerivedFrom<CDerived1_2>(p1_3, false);

    TestDerivedFrom<CDerived1_21>(p1, false);
    TestDerivedFrom<CDerived1_21>(p1_1, false);
    TestDerivedFrom<CDerived1_21>(p1_2, false);
    TestDerivedFrom<CDerived1_21>(p1_21, true);
    TestDerivedFrom<CDerived1_21>(p1_22, false);
    TestDerivedFrom<CDerived1_21>(p1_221, false);
    TestDerivedFrom<CDerived1_21>(p1_222, false);
    TestDerivedFrom<CDerived1_21>(p1_3, false);

    TestDerivedFrom<CDerived1_22>(p1, false);
    TestDerivedFrom<CDerived1_22>(p1_1, false);
    TestDerivedFrom<CDerived1_22>(p1_2, false);
    TestDerivedFrom<CDerived1_22>(p1_21, false);
    TestDerivedFrom<CDerived1_22>(p1_22, true);
    TestDerivedFrom<CDerived1_22>(p1_221, true);
    TestDerivedFrom<CDerived1_22>(p1_222, true);
    TestDerivedFrom<CDerived1_22>(p1_3, false);

    TestDerivedFrom<CDerived1_3>(p1, false);
    TestDerivedFrom<CDerived1_3>(p1_1, false);
    TestDerivedFrom<CDerived1_3>(p1_2, false);
    TestDerivedFrom<CDerived1_3>(p1_21, false);
    TestDerivedFrom<CDerived1_3>(p1_22, false);
    TestDerivedFrom<CDerived1_3>(p1_221, false);
    TestDerivedFrom<CDerived1_3>(p1_222, false);
    TestDerivedFrom<CDerived1_3>(p1_3, true);



    TestDerivedFrom<CBase2>(p1, false);
    TestDerivedFrom<CBase2>(p1_1, false);
    TestDerivedFrom<CBase2>(p1_2, false);
    TestDerivedFrom<CBase2>(p1_21, false);
    TestDerivedFrom<CBase2>(p1_22, false);
    TestDerivedFrom<CBase2>(p1_221, false);
    TestDerivedFrom<CBase2>(p1_222, false);
    TestDerivedFrom<CBase2>(p1_3, false);

    TestDerivedFrom<CDerived2_1>(p1, false);
    TestDerivedFrom<CDerived2_1>(p1_1, false);
    TestDerivedFrom<CDerived2_1>(p1_2, false);
    TestDerivedFrom<CDerived2_1>(p1_21, false);
    TestDerivedFrom<CDerived2_1>(p1_22, false);
    TestDerivedFrom<CDerived2_1>(p1_221, false);
    TestDerivedFrom<CDerived2_1>(p1_222, false);
    TestDerivedFrom<CDerived2_1>(p1_3, false);

    TestDerivedFrom<CDerived2_2>(p1, false);
    TestDerivedFrom<CDerived2_2>(p1_1, false);
    TestDerivedFrom<CDerived2_2>(p1_2, false);
    TestDerivedFrom<CDerived2_2>(p1_21, false);
    TestDerivedFrom<CDerived2_2>(p1_22, false);
    TestDerivedFrom<CDerived2_2>(p1_221, false);
    TestDerivedFrom<CDerived2_2>(p1_222, false);
    TestDerivedFrom<CDerived2_2>(p1_3, false);

    TestDerivedFrom<CDerived2_3>(p1, false);
    TestDerivedFrom<CDerived2_3>(p1_1, false);
    TestDerivedFrom<CDerived2_3>(p1_2, false);
    TestDerivedFrom<CDerived2_3>(p1_21, false);
    TestDerivedFrom<CDerived2_3>(p1_22, false);
    TestDerivedFrom<CDerived2_3>(p1_221, false);
    TestDerivedFrom<CDerived2_3>(p1_222, false);
    TestDerivedFrom<CDerived2_3>(p1_3, false);

    TestDerivedFrom<CDerived2_31>(p1, false);
    TestDerivedFrom<CDerived2_31>(p1_1, false);
    TestDerivedFrom<CDerived2_31>(p1_2, false);
    TestDerivedFrom<CDerived2_31>(p1_21, false);
    TestDerivedFrom<CDerived2_31>(p1_22, false);
    TestDerivedFrom<CDerived2_31>(p1_221, false);
    TestDerivedFrom<CDerived2_31>(p1_222, false);
    TestDerivedFrom<CDerived2_31>(p1_3, false);

    TestDerivedFrom<CDerived2_32>(p1, false);
    TestDerivedFrom<CDerived2_32>(p1_1, false);
    TestDerivedFrom<CDerived2_32>(p1_2, false);
    TestDerivedFrom<CDerived2_32>(p1_21, false);
    TestDerivedFrom<CDerived2_32>(p1_22, false);
    TestDerivedFrom<CDerived2_32>(p1_221, false);
    TestDerivedFrom<CDerived2_32>(p1_222, false);
    TestDerivedFrom<CDerived2_32>(p1_3, false);
}

TEST(rtti, get_class_name)
{
    EXPECT_EQ(p1->get_class_name(), QX_TEXT("CBase1"));

    EXPECT_EQ(static_cast<CBase1*>(p1_2.get())->get_class_name(), QX_TEXT("CDerived1_2"));
    EXPECT_EQ(p1_2->get_class_name(), QX_TEXT("CDerived1_2"));

    EXPECT_EQ(static_cast<CBase1*>(p1_22.get())->get_class_name(), QX_TEXT("CDerived1_22"));
    EXPECT_EQ(static_cast<CDerived1_2*>(p1_22.get())->get_class_name(), QX_TEXT("CDerived1_22"));
    EXPECT_EQ(p1_22->get_class_name(), QX_TEXT("CDerived1_22"));

    EXPECT_EQ(static_cast<CBase1*>(p1_222.get())->get_class_name(), QX_TEXT("CDerived1_222"));
    EXPECT_EQ(static_cast<CDerived1_2*>(p1_222.get())->get_class_name(), QX_TEXT("CDerived1_222"));
    EXPECT_EQ(static_cast<CDerived1_22*>(p1_222.get())->get_class_name(), QX_TEXT("CDerived1_222"));
    EXPECT_EQ(p1_222->get_class_name(), QX_TEXT("CDerived1_222"));
}

TEST(rtti, rtti_cast)
{
    auto sharedPtr = std::make_shared<CBase1>();
    auto rawPtr    = sharedPtr.get();

    EXPECT_TRUE(qx::rtti_cast<CBase1>(sharedPtr));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(rawPtr));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(sharedPtr.get()));

    EXPECT_TRUE(qx::rtti_cast<CBase1>(p1));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(p1_1));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(p1_2));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(p1_21));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(p1_22));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(p1_221));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(p1_222));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(p1_3));

    EXPECT_FALSE(qx::rtti_cast<CDerived1_1>(p1));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_1>(p1_1));

    EXPECT_FALSE(qx::rtti_cast<CDerived1_2>(p1));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_2>(p1_2));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_2>(p1_21));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_2>(p1_22));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_2>(p1_221));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_2>(p1_222));

    EXPECT_FALSE(qx::rtti_cast<CDerived1_21>(p1));
    EXPECT_FALSE(qx::rtti_cast<CDerived1_21>(p1_2));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_21>(p1_21));

    EXPECT_FALSE(qx::rtti_cast<CDerived1_22>(p1));
    EXPECT_FALSE(qx::rtti_cast<CDerived1_22>(p1_2));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_22>(p1_22));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_22>(p1_221));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_22>(p1_222));

    EXPECT_FALSE(qx::rtti_cast<CDerived1_3>(p1));
    EXPECT_TRUE(qx::rtti_cast<CDerived1_3>(p1_3));
}

TEST(rtti, is)
{
    EXPECT_TRUE(p1->is<CBase1>());
    EXPECT_FALSE(p1->is<CDerived1_1>());
    EXPECT_FALSE(p1->is<CDerived1_2>());
    EXPECT_FALSE(p1->is<CDerived1_21>());
    EXPECT_FALSE(p1->is<CDerived1_22>());
    EXPECT_FALSE(p1->is<CDerived1_221>());
    EXPECT_FALSE(p1->is<CDerived1_222>());
    EXPECT_FALSE(p1->is<CDerived1_3>());
    EXPECT_FALSE(p1->is<CDerived2_1>());
    EXPECT_FALSE(p1->is<CDerived2_2>());
    EXPECT_FALSE(p1->is<CDerived2_3>());
    EXPECT_FALSE(p1->is<CDerived2_31>());
    EXPECT_FALSE(p1->is<CDerived2_32>());
}
