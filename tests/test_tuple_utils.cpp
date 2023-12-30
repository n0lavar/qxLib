/**

    @file      test_tuple_utils.cpp
    @author    Khrapov
    @date      16.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_tuple_utils.cpp

#include <qx/meta/tuple_utils.h>

using TTuple0 = std::tuple<>;
using TTuple1 = std::tuple<int>;
using TTuple2 = std::tuple<float, std::tuple<int>>;
using TTuple3 = std::tuple<float, float, std::string>;



// -------------------------------------------------- qx::tuple::join --------------------------------------------------

using TJoin00 = qx::tuple::join_t<TTuple0, TTuple0>;
using TJoin01 = qx::tuple::join_t<TTuple0, TTuple1>;
using TJoin02 = qx::tuple::join_t<TTuple0, TTuple2>;
using TJoin03 = qx::tuple::join_t<TTuple0, TTuple3>;
static_assert(std::is_same_v<TJoin00, std::tuple<>>);
static_assert(std::is_same_v<TJoin01, std::tuple<int>>);
static_assert(std::is_same_v<TJoin02, std::tuple<float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin03, std::tuple<float, float, std::string>>);

using TJoin10 = qx::tuple::join_t<TTuple1, TTuple0>;
using TJoin11 = qx::tuple::join_t<TTuple1, TTuple1>;
using TJoin12 = qx::tuple::join_t<TTuple1, TTuple2>;
using TJoin13 = qx::tuple::join_t<TTuple1, TTuple3>;
static_assert(std::is_same_v<TJoin10, std::tuple<int>>);
static_assert(std::is_same_v<TJoin11, std::tuple<int, int>>);
static_assert(std::is_same_v<TJoin12, std::tuple<int, float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin13, std::tuple<int, float, float, std::string>>);

using TJoin20 = qx::tuple::join_t<TTuple2, TTuple0>;
using TJoin21 = qx::tuple::join_t<TTuple2, TTuple1>;
using TJoin22 = qx::tuple::join_t<TTuple2, TTuple2>;
using TJoin23 = qx::tuple::join_t<TTuple2, TTuple3>;
static_assert(std::is_same_v<TJoin20, std::tuple<float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin21, std::tuple<float, std::tuple<int>, int>>);
static_assert(std::is_same_v<TJoin22, std::tuple<float, std::tuple<int>, float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin23, std::tuple<float, std::tuple<int>, float, float, std::string>>);

using TJoin30 = qx::tuple::join_t<TTuple3, TTuple0>;
using TJoin31 = qx::tuple::join_t<TTuple3, TTuple1>;
using TJoin32 = qx::tuple::join_t<TTuple3, TTuple2>;
using TJoin33 = qx::tuple::join_t<TTuple3, TTuple3>;
static_assert(std::is_same_v<TJoin30, std::tuple<float, float, std::string>>);
static_assert(std::is_same_v<TJoin31, std::tuple<float, float, std::string, int>>);
static_assert(std::is_same_v<TJoin32, std::tuple<float, float, std::string, float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin33, std::tuple<float, float, std::string, float, float, std::string>>);

using TJoin3t0 = qx::tuple::join_t<TTuple3, int>;
using TJoin3t1 = qx::tuple::join_t<TTuple3, float>;
using TJoin3t2 = qx::tuple::join_t<TTuple3, int, int>;
using TJoin3t3 = qx::tuple::join_t<TTuple3, std::string>;
static_assert(std::is_same_v<TJoin3t0, std::tuple<float, float, std::string, int>>);
static_assert(std::is_same_v<TJoin3t1, std::tuple<float, float, std::string, float>>);
static_assert(std::is_same_v<TJoin3t2, std::tuple<float, float, std::string, int, int>>);
static_assert(std::is_same_v<TJoin3t3, std::tuple<float, float, std::string, std::string>>);



// ------------------------------------------------- qx::tuple::remove -------------------------------------------------

using TRemove00 = qx::tuple::remove_t<TTuple0, TTuple0>;
using TRemove01 = qx::tuple::remove_t<TTuple0, TTuple1>;
using TRemove02 = qx::tuple::remove_t<TTuple0, TTuple2>;
using TRemove03 = qx::tuple::remove_t<TTuple0, TTuple3>;
static_assert(std::is_same_v<TRemove00, std::tuple<>>);
static_assert(std::is_same_v<TRemove01, std::tuple<>>);
static_assert(std::is_same_v<TRemove02, std::tuple<>>);
static_assert(std::is_same_v<TRemove03, std::tuple<>>);

using TRemove10 = qx::tuple::remove_t<TTuple1, TTuple0>;
using TRemove11 = qx::tuple::remove_t<TTuple1, TTuple1>;
using TRemove12 = qx::tuple::remove_t<TTuple1, TTuple2>;
using TRemove13 = qx::tuple::remove_t<TTuple1, TTuple3>;
static_assert(std::is_same_v<TRemove10, std::tuple<int>>);
static_assert(std::is_same_v<TRemove11, std::tuple<>>);
static_assert(std::is_same_v<TRemove12, std::tuple<int>>);
static_assert(std::is_same_v<TRemove13, std::tuple<int>>);

using TRemove20 = qx::tuple::remove_t<TTuple2, TTuple0>;
using TRemove21 = qx::tuple::remove_t<TTuple2, TTuple1>;
using TRemove22 = qx::tuple::remove_t<TTuple2, TTuple2>;
using TRemove23 = qx::tuple::remove_t<TTuple2, TTuple3>;
static_assert(std::is_same_v<TRemove20, std::tuple<float, std::tuple<int>>>);
static_assert(std::is_same_v<TRemove21, std::tuple<float, std::tuple<int>>>);
static_assert(std::is_same_v<TRemove22, std::tuple<>>);
static_assert(std::is_same_v<TRemove23, std::tuple<std::tuple<int>>>);

using TRemove30 = qx::tuple::remove_t<TTuple3, TTuple0>;
using TRemove31 = qx::tuple::remove_t<TTuple3, TTuple1>;
using TRemove32 = qx::tuple::remove_t<TTuple3, TTuple2>;
using TRemove33 = qx::tuple::remove_t<TTuple3, TTuple3>;
static_assert(std::is_same_v<TRemove30, std::tuple<float, float, std::string>>);
static_assert(std::is_same_v<TRemove31, std::tuple<float, float, std::string>>);
static_assert(std::is_same_v<TRemove32, std::tuple<std::string>>);
static_assert(std::is_same_v<TRemove33, std::tuple<>>);



// ------------------------------------------------ qx::tuple::contains ------------------------------------------------

static_assert(!qx::tuple::contains_v<TTuple0, int>);
static_assert(!qx::tuple::contains_v<TTuple0, float>);
static_assert(!qx::tuple::contains_v<TTuple0, std::tuple<int>>);
static_assert(!qx::tuple::contains_v<TTuple0, std::string>);
static_assert(!qx::tuple::contains_v<TTuple0, size_t>);

static_assert(qx::tuple::contains_v<TTuple1, int>);
static_assert(!qx::tuple::contains_v<TTuple1, float>);
static_assert(!qx::tuple::contains_v<TTuple1, std::tuple<int>>);
static_assert(!qx::tuple::contains_v<TTuple1, std::string>);
static_assert(!qx::tuple::contains_v<TTuple1, size_t>);

static_assert(!qx::tuple::contains_v<TTuple2, int>);
static_assert(qx::tuple::contains_v<TTuple2, float>);
static_assert(qx::tuple::contains_v<TTuple2, std::tuple<int>>);
static_assert(!qx::tuple::contains_v<TTuple2, std::string>);
static_assert(!qx::tuple::contains_v<TTuple2, size_t>);

static_assert(!qx::tuple::contains_v<TTuple3, int>);
static_assert(qx::tuple::contains_v<TTuple3, float>);
static_assert(!qx::tuple::contains_v<TTuple3, std::tuple<int>>);
static_assert(qx::tuple::contains_v<TTuple3, std::string>);
static_assert(!qx::tuple::contains_v<TTuple3, size_t>);



// ------------------------------------------------ qx::tuple::transform -----------------------------------------------

using TTransformAddPointer0 = qx::tuple::transform_t<TTuple0, std::add_pointer>;
using TTransformAddPointer1 = qx::tuple::transform_t<TTuple1, std::add_pointer>;
using TTransformAddPointer2 = qx::tuple::transform_t<TTuple2, std::add_pointer>;
using TTransformAddPointer3 = qx::tuple::transform_t<TTuple3, std::add_pointer>;
static_assert(std::is_same_v<TTransformAddPointer0, std::tuple<>>);
static_assert(std::is_same_v<TTransformAddPointer1, std::tuple<int*>>);
static_assert(std::is_same_v<TTransformAddPointer2, std::tuple<float*, std::tuple<int>*>>);
static_assert(std::is_same_v<TTransformAddPointer3, std::tuple<float*, float*, std::string*>>);

using TTransformAddLRef0 = qx::tuple::transform_t<TTuple0, std::add_lvalue_reference>;
using TTransformAddLRef1 = qx::tuple::transform_t<TTuple1, std::add_lvalue_reference>;
using TTransformAddLRef2 = qx::tuple::transform_t<TTuple2, std::add_lvalue_reference>;
using TTransformAddLRef3 = qx::tuple::transform_t<TTuple3, std::add_lvalue_reference>;
static_assert(std::is_same_v<TTransformAddLRef0, std::tuple<>>);
static_assert(std::is_same_v<TTransformAddLRef1, std::tuple<int&>>);
static_assert(std::is_same_v<TTransformAddLRef2, std::tuple<float&, std::tuple<int>&>>);
static_assert(std::is_same_v<TTransformAddLRef3, std::tuple<float&, float&, std::string&>>);

using TTransformAddConst0 = qx::tuple::transform_t<TTuple0, std::add_const>;
using TTransformAddConst1 = qx::tuple::transform_t<TTuple1, std::add_const>;
using TTransformAddConst2 = qx::tuple::transform_t<TTuple2, std::add_const>;
using TTransformAddConst3 = qx::tuple::transform_t<TTuple3, std::add_const>;
static_assert(std::is_same_v<TTransformAddConst0, std::tuple<>>);
static_assert(std::is_same_v<TTransformAddConst1, std::tuple<const int>>);
static_assert(std::is_same_v<TTransformAddConst2, std::tuple<const float, const std::tuple<int>>>);
static_assert(std::is_same_v<TTransformAddConst3, std::tuple<const float, const float, const std::string>>);

using TTransformAddVolatile0 = qx::tuple::transform_t<TTuple0, std::add_volatile>;
using TTransformAddVolatile1 = qx::tuple::transform_t<TTuple1, std::add_volatile>;
using TTransformAddVolatile2 = qx::tuple::transform_t<TTuple2, std::add_volatile>;
using TTransformAddVolatile3 = qx::tuple::transform_t<TTuple3, std::add_volatile>;
static_assert(std::is_same_v<TTransformAddVolatile0, std::tuple<>>);
static_assert(std::is_same_v<TTransformAddVolatile1, std::tuple<volatile int>>);
static_assert(std::is_same_v<TTransformAddVolatile2, std::tuple<volatile float, volatile std::tuple<int>>>);
static_assert(std::is_same_v<TTransformAddVolatile3, std::tuple<volatile float, volatile float, volatile std::string>>);



// -------------------------------------------------- qx::tuple::index -------------------------------------------------

static_assert(qx::tuple::index_v<TTuple1, int> == 0);
static_assert(qx::tuple::index_v<TTuple2, float> == 0);
static_assert(qx::tuple::index_v<TTuple3, std::string> == 2);



// ------------------------------------------------- qx::tuple::iterate ------------------------------------------------

TEST(tuple, iterate)
{
    using TTuple        = std::tuple<float, int, std::string, unsigned, size_t>;
    size_t nInvocations = 0;
    qx::tuple::iterate<TTuple>(
        [&nInvocations]<class T, size_t I>()
        {
            static_assert(I != 0 || std::is_same_v<T, float>);
            static_assert(I != 1 || std::is_same_v<T, int>);
            static_assert(I != 2 || std::is_same_v<T, std::string>);
            static_assert(I != 3 || std::is_same_v<T, unsigned>);
            static_assert(I != 4 || std::is_same_v<T, size_t>);
            static_assert(I < 5);
            ++nInvocations;
        });

    EXPECT_EQ(nInvocations, 5);
}
