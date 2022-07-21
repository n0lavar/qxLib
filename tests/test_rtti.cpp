/**

    @file      test_rtti.cpp
    @author    Khrapov
    @date      26.08.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_rtti.cpp

#if QX_TEST_RTTI

    #include <qx/containers/string/string_utils.h>
    #include <qx/rtti/rtti.h>
    #include <qx/rtti/rtti_cast.h>
    #include <qx/useful_macros.h>

    #include <memory>

class CClass1
{
};

class CClass2
{
};

class CRttiBase : public qx::rtti_root<CRttiBase>
{
    QX_RTTI_CLASS(CRttiBase, rtti_root<CRttiBase>);
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

static_assert(std::is_same_v<CDerived1_1::BaseClass, CRttiBase>);
static_assert(std::is_same_v<CDerived1_2::BaseClass, CRttiBase>);
static_assert(std::is_same_v<CDerived1_21::BaseClass, CRttiBase>);
static_assert(std::is_same_v<CDerived1_22::BaseClass, CRttiBase>);
static_assert(std::is_same_v<CDerived1_3::BaseClass, CRttiBase>);

static_assert(std::is_same_v<CDerived2_1::BaseClass, CRttiBase>);
static_assert(std::is_same_v<CDerived2_2::BaseClass, CRttiBase>);
static_assert(std::is_same_v<CDerived2_3::BaseClass, CRttiBase>);
static_assert(std::is_same_v<CDerived2_31::BaseClass, CRttiBase>);
static_assert(std::is_same_v<CDerived2_32::BaseClass, CRttiBase>);

static_assert(std::is_same_v<CDerived1_1::SuperClass, CBase1>);
static_assert(std::is_same_v<CDerived1_2::SuperClass, CBase1>);
static_assert(std::is_same_v<CDerived1_21::SuperClass, CDerived1_2>);
static_assert(std::is_same_v<CDerived1_22::SuperClass, CDerived1_2>);
static_assert(std::is_same_v<CDerived1_3::SuperClass, CBase1>);

static_assert(std::is_same_v<CDerived2_1::SuperClass, CBase2>);
static_assert(std::is_same_v<CDerived2_2::SuperClass, CBase2>);
static_assert(std::is_same_v<CDerived2_3::SuperClass, CBase2>);
static_assert(std::is_same_v<CDerived2_31::SuperClass, CDerived2_3>);
static_assert(std::is_same_v<CDerived2_32::SuperClass, CDerived2_3>);

static_assert(std::is_same_v<CDerived1_1::ThisClass, CDerived1_1>);
static_assert(std::is_same_v<CDerived1_2::ThisClass, CDerived1_2>);
static_assert(std::is_same_v<CDerived1_21::ThisClass, CDerived1_21>);
static_assert(std::is_same_v<CDerived1_22::ThisClass, CDerived1_22>);
static_assert(std::is_same_v<CDerived1_3::ThisClass, CDerived1_3>);

static_assert(std::is_same_v<CDerived2_1::ThisClass, CDerived2_1>);
static_assert(std::is_same_v<CDerived2_2::ThisClass, CDerived2_2>);
static_assert(std::is_same_v<CDerived2_3::ThisClass, CDerived2_3>);
static_assert(std::is_same_v<CDerived2_31::ThisClass, CDerived2_31>);
static_assert(std::is_same_v<CDerived2_32::ThisClass, CDerived2_32>);



//---------------------------- get_class_name_static ---------------------------

QX_STATIC_ASSERT_STR_EQ(CBase1::get_class_name_static().data(), "CBase1");
QX_STATIC_ASSERT_STR_EQ(CDerived1_1::get_class_name_static().data(), "CDerived1_1");
QX_STATIC_ASSERT_STR_EQ(CDerived1_2::get_class_name_static().data(), "CDerived1_2");
QX_STATIC_ASSERT_STR_EQ(CDerived1_21::get_class_name_static().data(), "CDerived1_21");
QX_STATIC_ASSERT_STR_EQ(CDerived1_22::get_class_name_static().data(), "CDerived1_22");
QX_STATIC_ASSERT_STR_EQ(CDerived1_221::get_class_name_static().data(), "CDerived1_221");
QX_STATIC_ASSERT_STR_EQ(CDerived1_222::get_class_name_static().data(), "CDerived1_222");
QX_STATIC_ASSERT_STR_EQ(CDerived1_3::get_class_name_static().data(), "CDerived1_3");

// ------------------------------------ RTTI -----------------------------------

TEST(rtti, class_id)
{
    EXPECT_EQ(qx::get_class_id<CClass1>(), -1);
    EXPECT_EQ(qx::get_class_id<CClass2>(), -1);

    EXPECT_TRUE(static_cast<CBase1*>(p1_21.get())->get_class_id() == qx::get_class_id<CDerived1_21>());
    EXPECT_TRUE(static_cast<CDerived1_2*>(p1_21.get())->get_class_id() == qx::get_class_id<CDerived1_21>());
    EXPECT_TRUE(p1_21->get_class_id() == qx::get_class_id<CDerived1_21>());

    std::set<int> ids;
    auto          CheckId = [&ids](int id)
    {
        EXPECT_GE(id, 0) << "existing id must be greater or equal then 0";
        auto ret = ids.insert(id);
        EXPECT_TRUE(ret.second) << "existing id must be unique";
    };

    CheckId(qx::get_class_id<CDerived1_1>());
    CheckId(qx::get_class_id<CDerived1_2>());
    CheckId(qx::get_class_id<CDerived1_21>());
    CheckId(qx::get_class_id<CDerived1_22>());
    CheckId(qx::get_class_id<CDerived1_221>());
    CheckId(qx::get_class_id<CDerived1_222>());
    CheckId(qx::get_class_id<CDerived1_3>());

    CheckId(qx::get_class_id<CDerived2_1>());
    CheckId(qx::get_class_id<CDerived2_2>());
    CheckId(qx::get_class_id<CDerived2_3>());
    CheckId(qx::get_class_id<CDerived2_31>());
    CheckId(qx::get_class_id<CDerived2_32>());
}

template<class T>
void TestDerivedFrom(const auto& pClass, bool bExpect)
{
    EXPECT_EQ(pClass->template is_derived_from<T>(), bExpect);

    if constexpr (qx::detail::has_get_class_id_static<T>)
    {
        EXPECT_EQ(pClass->is_derived_from_id(T::get_class_id_static()), bExpect);
    }
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



    TestDerivedFrom<CClass1>(p1, false);
    TestDerivedFrom<CClass1>(p1_1, false);
    TestDerivedFrom<CClass1>(p1_2, false);
    TestDerivedFrom<CClass1>(p1_21, false);
    TestDerivedFrom<CClass1>(p1_22, false);
    TestDerivedFrom<CClass1>(p1_221, false);
    TestDerivedFrom<CClass1>(p1_222, false);
    TestDerivedFrom<CClass1>(p1_3, false);

    TestDerivedFrom<CClass2>(p1, false);
    TestDerivedFrom<CClass2>(p1_1, false);
    TestDerivedFrom<CClass2>(p1_2, false);
    TestDerivedFrom<CClass2>(p1_21, false);
    TestDerivedFrom<CClass2>(p1_22, false);
    TestDerivedFrom<CClass2>(p1_221, false);
    TestDerivedFrom<CClass2>(p1_222, false);
    TestDerivedFrom<CClass2>(p1_3, false);
}

TEST(rtti, get_class_name)
{
    EXPECT_STREQ(p1->get_class_name().data(), "CBase1");

    EXPECT_STREQ(static_cast<CBase1*>(p1_2.get())->get_class_name().data(), "CDerived1_2");
    EXPECT_STREQ(p1_2->get_class_name().data(), "CDerived1_2");

    EXPECT_STREQ(static_cast<CBase1*>(p1_22.get())->get_class_name().data(), "CDerived1_22");
    EXPECT_STREQ(static_cast<CDerived1_2*>(p1_22.get())->get_class_name().data(), "CDerived1_22");
    EXPECT_STREQ(p1_22->get_class_name().data(), "CDerived1_22");

    EXPECT_STREQ(static_cast<CBase1*>(p1_222.get())->get_class_name().data(), "CDerived1_222");
    EXPECT_STREQ(static_cast<CDerived1_2*>(p1_222.get())->get_class_name().data(), "CDerived1_222");
    EXPECT_STREQ(static_cast<CDerived1_22*>(p1_222.get())->get_class_name().data(), "CDerived1_222");
    EXPECT_STREQ(p1_222->get_class_name().data(), "CDerived1_222");
}

TEST(rtti, rtti_cast)
{
    auto     sharedPtr = std::make_shared<CBase1>();
    auto     rawPtr    = sharedPtr.get();
    CClass1  c1;
    CClass1* pc1 = nullptr;

    EXPECT_TRUE(qx::rtti_cast<CBase1>(sharedPtr));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(rawPtr));
    EXPECT_TRUE(qx::rtti_cast<CBase1>(sharedPtr.get()));
    EXPECT_FALSE(qx::rtti_cast<CBase1>(&c1));
    EXPECT_FALSE(qx::rtti_cast<CBase1>(pc1));

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

#endif
