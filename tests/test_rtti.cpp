//==============================================================================
//
//!\file                          test_rtti.cpp
//
//!\brief       Tests for qx RTTI
//!\details     ~
//
//!\author      Khrapov
//!\date        26.08.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_rtti.cpp

#if QX_TEST_RTTI

#include <qx/rtti.h>
#include <qx/useful_macros.h>
#include <memory>


#define IS_CONSTEXPR(a) static_assert((a) || !(a));

class CClass1
{
};

class CClass2
{
};


class CBase1 : public qx::rtti_base
{
    QX_RTTI_CLASS_DERIVED(CBase1, qx::rtti_base)
}

class CDerived1_1 : public CBase1
{
    QX_RTTI_CLASS_DERIVED(CDerived1_1, CBase1)
}

class CDerived1_2 : public CBase1
{
    QX_RTTI_CLASS_DERIVED(CDerived1_2, CBase1)
}

class CDerived1_21 : public CDerived1_2
{
    QX_RTTI_CLASS_DERIVED(CDerived1_21, CDerived1_2)
}

class CDerived1_22 : public CDerived1_2
{
    QX_RTTI_CLASS_DERIVED(CDerived1_22, CDerived1_2)
}

class CDerived1_221 : public CDerived1_22
{
    QX_RTTI_CLASS_DERIVED(CDerived1_221, CDerived1_22)
}

class CDerived1_222 : public CDerived1_22
{
    QX_RTTI_CLASS_DERIVED(CDerived1_222, CDerived1_22)
}

class CDerived1_3 : public CBase1
{
    QX_RTTI_CLASS_DERIVED(CDerived1_3, CBase1)
}


class CBase2 : public qx::rtti_base
{
    QX_RTTI_CLASS_DERIVED(CBase2, qx::rtti_base)
}

class CDerived2_1 : public CBase2
{
    QX_RTTI_CLASS_DERIVED(CDerived2_1, CBase2)
}

class CDerived2_2 : public CBase2
{
    QX_RTTI_CLASS_DERIVED(CDerived2_2, CBase2)
}

class CDerived2_3 : public CBase2
{
    QX_RTTI_CLASS_DERIVED(CDerived2_3, CBase2)
}

class CDerived2_31 : public CDerived2_3
{
    QX_RTTI_CLASS_DERIVED(CDerived2_31, CDerived2_3)
}

class CDerived2_32 : public CDerived2_3
{
    QX_RTTI_CLASS_DERIVED(CDerived2_32, CDerived2_3)
}



//--------------------------------- is_derived ---------------------------------

static_assert( qx::is_derived<CDerived1_1> ::from<CBase1>());
static_assert( qx::is_derived<CDerived1_2> ::from<CBase1>());
static_assert( qx::is_derived<CDerived1_21>::from<CDerived1_2>());
static_assert( qx::is_derived<CDerived1_22>::from<CDerived1_2>());
static_assert( qx::is_derived<CDerived1_21>::from<CBase1>());
static_assert( qx::is_derived<CDerived1_22>::from<CBase1>());
static_assert( qx::is_derived<CDerived1_3> ::from<CBase1>());
static_assert(!qx::is_derived<CDerived1_1> ::from<CClass1>());
static_assert(!qx::is_derived<CDerived1_1> ::from<CClass2>());

static_assert( qx::is_derived<CDerived2_1> ::from<CBase2>());
static_assert( qx::is_derived<CDerived2_2> ::from<CBase2>());
static_assert( qx::is_derived<CDerived2_3> ::from<CBase2>());
static_assert( qx::is_derived<CDerived2_31>::from<CDerived2_3>());
static_assert( qx::is_derived<CDerived2_32>::from<CDerived2_3>());
static_assert( qx::is_derived<CDerived2_31>::from<CBase2>());
static_assert( qx::is_derived<CDerived2_32>::from<CBase2>());
static_assert(!qx::is_derived<CDerived2_1> ::from<CClass1>());
static_assert(!qx::is_derived<CDerived2_1> ::from<CClass2>());

static_assert(!qx::is_derived<CDerived1_1> ::from<CBase2>());
static_assert(!qx::is_derived<CDerived1_2> ::from<CBase2>());
static_assert(!qx::is_derived<CDerived1_21>::from<CDerived2_2>());
static_assert(!qx::is_derived<CDerived1_22>::from<CDerived2_2>());
static_assert(!qx::is_derived<CDerived1_21>::from<CBase2>());
static_assert(!qx::is_derived<CDerived1_22>::from<CBase2>());
static_assert(!qx::is_derived<CDerived1_3> ::from<CBase2>());

static_assert(!qx::is_derived<CDerived2_1> ::from<CBase1>());
static_assert(!qx::is_derived<CDerived2_2> ::from<CBase1>());
static_assert(!qx::is_derived<CDerived2_3> ::from<CBase1>());
static_assert(!qx::is_derived<CDerived2_31>::from<CDerived1_3>());
static_assert(!qx::is_derived<CDerived2_32>::from<CDerived1_3>());
static_assert(!qx::is_derived<CDerived2_31>::from<CBase1>());
static_assert(!qx::is_derived<CDerived2_32>::from<CBase1>());



//---------------------------------- class id ----------------------------------

IS_CONSTEXPR(qx::get_class_id<CDerived1_1>());
IS_CONSTEXPR(qx::get_class_id<CDerived1_2>());
IS_CONSTEXPR(qx::get_class_id<CDerived1_21>());
IS_CONSTEXPR(qx::get_class_id<CDerived1_22>());
IS_CONSTEXPR(qx::get_class_id<CDerived1_221>());
IS_CONSTEXPR(qx::get_class_id<CDerived1_222>());
IS_CONSTEXPR(qx::get_class_id<CDerived1_3>());

IS_CONSTEXPR(qx::get_class_id<CDerived2_1>());
IS_CONSTEXPR(qx::get_class_id<CDerived2_2>());
IS_CONSTEXPR(qx::get_class_id<CDerived2_3>());
IS_CONSTEXPR(qx::get_class_id<CDerived2_31>());
IS_CONSTEXPR(qx::get_class_id<CDerived2_32>());

static_assert(qx::get_class_id<CClass1>() == -1);
static_assert(qx::get_class_id<CClass2>() == -1);



//----------------------------------- usings -----------------------------------

static_assert(std::is_same_v<CDerived1_1::BaseClass,  qx::rtti_base>);
static_assert(std::is_same_v<CDerived1_2::BaseClass,  qx::rtti_base>);
static_assert(std::is_same_v<CDerived1_21::BaseClass, qx::rtti_base>);
static_assert(std::is_same_v<CDerived1_22::BaseClass, qx::rtti_base>);
static_assert(std::is_same_v<CDerived1_3::BaseClass,  qx::rtti_base>);

static_assert(std::is_same_v<CDerived2_1::BaseClass,  qx::rtti_base>);
static_assert(std::is_same_v<CDerived2_2::BaseClass,  qx::rtti_base>);
static_assert(std::is_same_v<CDerived2_3::BaseClass,  qx::rtti_base>);
static_assert(std::is_same_v<CDerived2_31::BaseClass, qx::rtti_base>);
static_assert(std::is_same_v<CDerived2_32::BaseClass, qx::rtti_base>);

static_assert(std::is_same_v<CDerived1_1::SuperClass,  CBase1>);
static_assert(std::is_same_v<CDerived1_2::SuperClass,  CBase1>);
static_assert(std::is_same_v<CDerived1_21::SuperClass, CDerived1_2>);
static_assert(std::is_same_v<CDerived1_22::SuperClass, CDerived1_2>);
static_assert(std::is_same_v<CDerived1_3::SuperClass,  CBase1>);

static_assert(std::is_same_v<CDerived2_1::SuperClass,  CBase2>);
static_assert(std::is_same_v<CDerived2_2::SuperClass,  CBase2>);
static_assert(std::is_same_v<CDerived2_3::SuperClass,  CBase2>);
static_assert(std::is_same_v<CDerived2_31::SuperClass, CDerived2_3>);
static_assert(std::is_same_v<CDerived2_32::SuperClass, CDerived2_3>);

static_assert(std::is_same_v<CDerived1_1::ThisClass,  CDerived1_1>);
static_assert(std::is_same_v<CDerived1_2::ThisClass,  CDerived1_2>);
static_assert(std::is_same_v<CDerived1_21::ThisClass, CDerived1_21>);
static_assert(std::is_same_v<CDerived1_22::ThisClass, CDerived1_22>);
static_assert(std::is_same_v<CDerived1_3::ThisClass,  CDerived1_3>);

static_assert(std::is_same_v<CDerived2_1::ThisClass,  CDerived2_1>);
static_assert(std::is_same_v<CDerived2_2::ThisClass,  CDerived2_2>);
static_assert(std::is_same_v<CDerived2_3::ThisClass,  CDerived2_3>);
static_assert(std::is_same_v<CDerived2_31::ThisClass, CDerived2_31>);
static_assert(std::is_same_v<CDerived2_32::ThisClass, CDerived2_32>);



//---------------------------- get_class_name_static ---------------------------

QX_STATIC_ASSERT_STR_EQ(CBase1::get_class_name_static().data(),        "CBase1");
QX_STATIC_ASSERT_STR_EQ(CDerived1_1::get_class_name_static().data(),   "CDerived1_1");
QX_STATIC_ASSERT_STR_EQ(CDerived1_2::get_class_name_static().data(),   "CDerived1_2");
QX_STATIC_ASSERT_STR_EQ(CDerived1_21::get_class_name_static().data(),  "CDerived1_21");
QX_STATIC_ASSERT_STR_EQ(CDerived1_22::get_class_name_static().data(),  "CDerived1_22");
QX_STATIC_ASSERT_STR_EQ(CDerived1_221::get_class_name_static().data(), "CDerived1_221");
QX_STATIC_ASSERT_STR_EQ(CDerived1_222::get_class_name_static().data(), "CDerived1_222");
QX_STATIC_ASSERT_STR_EQ(CDerived1_3::get_class_name_static().data(),   "CDerived1_3");



TEST(rtti, class_id)
{
    std::shared_ptr<CDerived1_21> p1 = std::make_shared<CDerived1_21>();

    EXPECT_TRUE(static_cast<CBase1*>(p1.get())->get_class_id()      == qx::get_class_id<CDerived1_21>());
    EXPECT_TRUE(static_cast<CDerived1_2*>(p1.get())->get_class_id() == qx::get_class_id<CDerived1_21>());
    EXPECT_TRUE(p1->get_class_id()                                  == qx::get_class_id<CDerived1_21>());

    std::set<int> ids;
    auto CheckId = [&ids] (int id)
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

TEST(rtti, is_derived_from)
{
    std::shared_ptr<CBase1>         p1      = std::make_shared<CBase1>();
    std::shared_ptr<CDerived1_1>    p1_1    = std::make_shared<CDerived1_1>();
    std::shared_ptr<CDerived1_2>    p1_2    = std::make_shared<CDerived1_2>();
    std::shared_ptr<CDerived1_21>   p1_21   = std::make_shared<CDerived1_21>();
    std::shared_ptr<CDerived1_22>   p1_22   = std::make_shared<CDerived1_22>();
    std::shared_ptr<CDerived1_221>  p1_221  = std::make_shared<CDerived1_221>();
    std::shared_ptr<CDerived1_222>  p1_222  = std::make_shared<CDerived1_222>();
    std::shared_ptr<CDerived1_3>    p1_3    = std::make_shared<CDerived1_3>();



    EXPECT_TRUE (p1     ->is_derived_from<CBase1>());
    EXPECT_TRUE (p1_1   ->is_derived_from<CBase1>());
    EXPECT_TRUE (p1_2   ->is_derived_from<CBase1>());
    EXPECT_TRUE (p1_21  ->is_derived_from<CBase1>());
    EXPECT_TRUE (p1_22  ->is_derived_from<CBase1>());
    EXPECT_TRUE (p1_221 ->is_derived_from<CBase1>());
    EXPECT_TRUE (p1_222 ->is_derived_from<CBase1>());
    EXPECT_TRUE (p1_3   ->is_derived_from<CBase1>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived1_1>());
    EXPECT_TRUE (p1_1   ->is_derived_from<CDerived1_1>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived1_1>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CDerived1_1>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CDerived1_1>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CDerived1_1>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CDerived1_1>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived1_1>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived1_2>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived1_2>());
    EXPECT_TRUE (p1_2   ->is_derived_from<CDerived1_2>());
    EXPECT_TRUE (p1_21  ->is_derived_from<CDerived1_2>());
    EXPECT_TRUE (p1_22  ->is_derived_from<CDerived1_2>());
    EXPECT_TRUE (p1_221 ->is_derived_from<CDerived1_2>());
    EXPECT_TRUE (p1_222 ->is_derived_from<CDerived1_2>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived1_2>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived1_21>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived1_21>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived1_21>());
    EXPECT_TRUE (p1_21  ->is_derived_from<CDerived1_21>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CDerived1_21>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CDerived1_21>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CDerived1_21>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived1_21>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived1_22>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived1_22>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived1_22>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CDerived1_22>());
    EXPECT_TRUE (p1_22  ->is_derived_from<CDerived1_22>());
    EXPECT_TRUE (p1_221 ->is_derived_from<CDerived1_22>());
    EXPECT_TRUE (p1_222 ->is_derived_from<CDerived1_22>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived1_22>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived1_3>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived1_3>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived1_3>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CDerived1_3>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CDerived1_3>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CDerived1_3>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CDerived1_3>());
    EXPECT_TRUE (p1_3   ->is_derived_from<CDerived1_3>());



    EXPECT_FALSE(p1     ->is_derived_from<CBase2>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CBase2>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CBase2>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CBase2>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CBase2>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CBase2>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CBase2>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CBase2>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived2_1>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived2_1>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived2_1>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CDerived2_1>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CDerived2_1>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CDerived2_1>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CDerived2_1>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived2_1>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived2_2>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived2_2>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived2_2>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CDerived2_2>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CDerived2_2>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CDerived2_2>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CDerived2_2>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived2_2>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived2_3>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived2_3>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived2_3>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CDerived2_3>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CDerived2_3>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CDerived2_3>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CDerived2_3>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived2_3>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived2_31>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived2_31>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived2_31>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CDerived2_31>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CDerived2_31>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CDerived2_31>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CDerived2_31>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived2_31>());

    EXPECT_FALSE(p1     ->is_derived_from<CDerived2_32>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CDerived2_32>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CDerived2_32>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CDerived2_32>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CDerived2_32>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CDerived2_32>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CDerived2_32>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CDerived2_32>());



    EXPECT_FALSE(p1     ->is_derived_from<CClass1>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CClass1>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CClass1>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CClass1>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CClass1>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CClass1>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CClass1>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CClass1>());

    EXPECT_FALSE(p1     ->is_derived_from<CClass2>());
    EXPECT_FALSE(p1_1   ->is_derived_from<CClass2>());
    EXPECT_FALSE(p1_2   ->is_derived_from<CClass2>());
    EXPECT_FALSE(p1_21  ->is_derived_from<CClass2>());
    EXPECT_FALSE(p1_22  ->is_derived_from<CClass2>());
    EXPECT_FALSE(p1_221 ->is_derived_from<CClass2>());
    EXPECT_FALSE(p1_222 ->is_derived_from<CClass2>());
    EXPECT_FALSE(p1_3   ->is_derived_from<CClass2>());
}

TEST(rtti, get_class_name)
{
    std::shared_ptr<CBase1>         p1      = std::make_shared<CBase1>();
    std::shared_ptr<CDerived1_2>    p1_2    = std::make_shared<CDerived1_2>();
    std::shared_ptr<CDerived1_22>   p1_21   = std::make_shared<CDerived1_22>();
    std::shared_ptr<CDerived1_222>  p1_221  = std::make_shared<CDerived1_222>();

    EXPECT_STREQ(p1->get_class_name().data(),                                       "CBase1");

    EXPECT_STREQ(static_cast<CBase1*>(p1_2.get())->get_class_name().data(),         "CDerived1_2");
    EXPECT_STREQ(p1_2->get_class_name().data(),                                     "CDerived1_2");

    EXPECT_STREQ(static_cast<CBase1*>(p1_21.get())->get_class_name().data(),        "CDerived1_22");
    EXPECT_STREQ(static_cast<CDerived1_2*>(p1_21.get())->get_class_name().data(),   "CDerived1_22");
    EXPECT_STREQ(p1_21->get_class_name().data(),                                    "CDerived1_22");

    EXPECT_STREQ(static_cast<CBase1*>(p1_221.get())->get_class_name().data(),       "CDerived1_222");
    EXPECT_STREQ(static_cast<CDerived1_2*>(p1_221.get())->get_class_name().data(),  "CDerived1_222");
    EXPECT_STREQ(static_cast<CDerived1_22*>(p1_221.get())->get_class_name().data(), "CDerived1_222");
    EXPECT_STREQ(p1_221->get_class_name().data(),                                   "CDerived1_222");
}

#endif
