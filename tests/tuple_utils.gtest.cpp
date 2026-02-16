/**

    @file      tuple_utils.gtest.cpp
    @author    Khrapov
    @date      16.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

#include <qx/meta/tuple_utils.h>

using TTuple0 = std::tuple<>;
using TTuple1 = std::tuple<int>;
using TTuple2 = std::tuple<float, std::tuple<int>>;
using TTuple3 = std::tuple<float, float, std::string>;

class A
{
};
class B
{
};
class C
{
};
class D
{
};
class E
{
};
class F
{
};
class G
{
};




// -------------------------------------------------- qx::tuple_utils::join --------------------------------------------------

using TJoin00 = qx::tuple_utils::join_t<TTuple0, TTuple0>;
using TJoin01 = qx::tuple_utils::join_t<TTuple0, TTuple1>;
using TJoin02 = qx::tuple_utils::join_t<TTuple0, TTuple2>;
using TJoin03 = qx::tuple_utils::join_t<TTuple0, TTuple3>;
static_assert(std::is_same_v<TJoin00, std::tuple<>>);
static_assert(std::is_same_v<TJoin01, std::tuple<int>>);
static_assert(std::is_same_v<TJoin02, std::tuple<float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin03, std::tuple<float, float, std::string>>);

using TJoin10 = qx::tuple_utils::join_t<TTuple1, TTuple0>;
using TJoin11 = qx::tuple_utils::join_t<TTuple1, TTuple1>;
using TJoin12 = qx::tuple_utils::join_t<TTuple1, TTuple2>;
using TJoin13 = qx::tuple_utils::join_t<TTuple1, TTuple3>;
static_assert(std::is_same_v<TJoin10, std::tuple<int>>);
static_assert(std::is_same_v<TJoin11, std::tuple<int, int>>);
static_assert(std::is_same_v<TJoin12, std::tuple<int, float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin13, std::tuple<int, float, float, std::string>>);

using TJoin20 = qx::tuple_utils::join_t<TTuple2, TTuple0>;
using TJoin21 = qx::tuple_utils::join_t<TTuple2, TTuple1>;
using TJoin22 = qx::tuple_utils::join_t<TTuple2, TTuple2>;
using TJoin23 = qx::tuple_utils::join_t<TTuple2, TTuple3>;
static_assert(std::is_same_v<TJoin20, std::tuple<float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin21, std::tuple<float, std::tuple<int>, int>>);
static_assert(std::is_same_v<TJoin22, std::tuple<float, std::tuple<int>, float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin23, std::tuple<float, std::tuple<int>, float, float, std::string>>);

using TJoin30 = qx::tuple_utils::join_t<TTuple3, TTuple0>;
using TJoin31 = qx::tuple_utils::join_t<TTuple3, TTuple1>;
using TJoin32 = qx::tuple_utils::join_t<TTuple3, TTuple2>;
using TJoin33 = qx::tuple_utils::join_t<TTuple3, TTuple3>;
static_assert(std::is_same_v<TJoin30, std::tuple<float, float, std::string>>);
static_assert(std::is_same_v<TJoin31, std::tuple<float, float, std::string, int>>);
static_assert(std::is_same_v<TJoin32, std::tuple<float, float, std::string, float, std::tuple<int>>>);
static_assert(std::is_same_v<TJoin33, std::tuple<float, float, std::string, float, float, std::string>>);

using TJoin3t0 = qx::tuple_utils::join_t<TTuple3, int>;
using TJoin3t1 = qx::tuple_utils::join_t<TTuple3, float>;
using TJoin3t2 = qx::tuple_utils::join_t<TTuple3, int, int>;
using TJoin3t3 = qx::tuple_utils::join_t<TTuple3, std::string>;
static_assert(std::is_same_v<TJoin3t0, std::tuple<float, float, std::string, int>>);
static_assert(std::is_same_v<TJoin3t1, std::tuple<float, float, std::string, float>>);
static_assert(std::is_same_v<TJoin3t2, std::tuple<float, float, std::string, int, int>>);
static_assert(std::is_same_v<TJoin3t3, std::tuple<float, float, std::string, std::string>>);




// ------------------------------------------------- qx::tuple_utils::remove -------------------------------------------------

using TRemove00 = qx::tuple_utils::remove_t<TTuple0, TTuple0>;
using TRemove01 = qx::tuple_utils::remove_t<TTuple0, TTuple1>;
using TRemove02 = qx::tuple_utils::remove_t<TTuple0, TTuple2>;
using TRemove03 = qx::tuple_utils::remove_t<TTuple0, TTuple3>;
static_assert(std::is_same_v<TRemove00, std::tuple<>>);
static_assert(std::is_same_v<TRemove01, std::tuple<>>);
static_assert(std::is_same_v<TRemove02, std::tuple<>>);
static_assert(std::is_same_v<TRemove03, std::tuple<>>);

using TRemove10 = qx::tuple_utils::remove_t<TTuple1, TTuple0>;
using TRemove11 = qx::tuple_utils::remove_t<TTuple1, TTuple1>;
using TRemove12 = qx::tuple_utils::remove_t<TTuple1, TTuple2>;
using TRemove13 = qx::tuple_utils::remove_t<TTuple1, TTuple3>;
static_assert(std::is_same_v<TRemove10, std::tuple<int>>);
static_assert(std::is_same_v<TRemove11, std::tuple<>>);
static_assert(std::is_same_v<TRemove12, std::tuple<int>>);
static_assert(std::is_same_v<TRemove13, std::tuple<int>>);

using TRemove20 = qx::tuple_utils::remove_t<TTuple2, TTuple0>;
using TRemove21 = qx::tuple_utils::remove_t<TTuple2, TTuple1>;
using TRemove22 = qx::tuple_utils::remove_t<TTuple2, TTuple2>;
using TRemove23 = qx::tuple_utils::remove_t<TTuple2, TTuple3>;
static_assert(std::is_same_v<TRemove20, std::tuple<float, std::tuple<int>>>);
static_assert(std::is_same_v<TRemove21, std::tuple<float, std::tuple<int>>>);
static_assert(std::is_same_v<TRemove22, std::tuple<>>);
static_assert(std::is_same_v<TRemove23, std::tuple<std::tuple<int>>>);

using TRemove30 = qx::tuple_utils::remove_t<TTuple3, TTuple0>;
using TRemove31 = qx::tuple_utils::remove_t<TTuple3, TTuple1>;
using TRemove32 = qx::tuple_utils::remove_t<TTuple3, TTuple2>;
using TRemove33 = qx::tuple_utils::remove_t<TTuple3, TTuple3>;
static_assert(std::is_same_v<TRemove30, std::tuple<float, float, std::string>>);
static_assert(std::is_same_v<TRemove31, std::tuple<float, float, std::string>>);
static_assert(std::is_same_v<TRemove32, std::tuple<std::string>>);
static_assert(std::is_same_v<TRemove33, std::tuple<>>);




// ------------------------------------------------ qx::tuple_utils::contains ------------------------------------------------

static_assert(!qx::tuple_utils::contains_v<TTuple0, int>);
static_assert(!qx::tuple_utils::contains_v<TTuple0, float>);
static_assert(!qx::tuple_utils::contains_v<TTuple0, std::tuple<int>>);
static_assert(!qx::tuple_utils::contains_v<TTuple0, std::string>);
static_assert(!qx::tuple_utils::contains_v<TTuple0, size_t>);

static_assert(qx::tuple_utils::contains_v<TTuple1, int>);
static_assert(!qx::tuple_utils::contains_v<TTuple1, float>);
static_assert(!qx::tuple_utils::contains_v<TTuple1, std::tuple<int>>);
static_assert(!qx::tuple_utils::contains_v<TTuple1, std::string>);
static_assert(!qx::tuple_utils::contains_v<TTuple1, size_t>);

static_assert(!qx::tuple_utils::contains_v<TTuple2, int>);
static_assert(qx::tuple_utils::contains_v<TTuple2, float>);
static_assert(qx::tuple_utils::contains_v<TTuple2, std::tuple<int>>);
static_assert(!qx::tuple_utils::contains_v<TTuple2, std::string>);
static_assert(!qx::tuple_utils::contains_v<TTuple2, size_t>);

static_assert(!qx::tuple_utils::contains_v<TTuple3, int>);
static_assert(qx::tuple_utils::contains_v<TTuple3, float>);
static_assert(!qx::tuple_utils::contains_v<TTuple3, std::tuple<int>>);
static_assert(qx::tuple_utils::contains_v<TTuple3, std::string>);
static_assert(!qx::tuple_utils::contains_v<TTuple3, size_t>);




// ------------------------------------------------ qx::tuple_utils::transform -----------------------------------------------

using TTransformAddPointer0 = qx::tuple_utils::transform_t<TTuple0, std::add_pointer>;
using TTransformAddPointer1 = qx::tuple_utils::transform_t<TTuple1, std::add_pointer>;
using TTransformAddPointer2 = qx::tuple_utils::transform_t<TTuple2, std::add_pointer>;
using TTransformAddPointer3 = qx::tuple_utils::transform_t<TTuple3, std::add_pointer>;
static_assert(std::is_same_v<TTransformAddPointer0, std::tuple<>>);
static_assert(std::is_same_v<TTransformAddPointer1, std::tuple<int*>>);
static_assert(std::is_same_v<TTransformAddPointer2, std::tuple<float*, std::tuple<int>*>>);
static_assert(std::is_same_v<TTransformAddPointer3, std::tuple<float*, float*, std::string*>>);

using TTransformAddLRef0 = qx::tuple_utils::transform_t<TTuple0, std::add_lvalue_reference>;
using TTransformAddLRef1 = qx::tuple_utils::transform_t<TTuple1, std::add_lvalue_reference>;
using TTransformAddLRef2 = qx::tuple_utils::transform_t<TTuple2, std::add_lvalue_reference>;
using TTransformAddLRef3 = qx::tuple_utils::transform_t<TTuple3, std::add_lvalue_reference>;
static_assert(std::is_same_v<TTransformAddLRef0, std::tuple<>>);
static_assert(std::is_same_v<TTransformAddLRef1, std::tuple<int&>>);
static_assert(std::is_same_v<TTransformAddLRef2, std::tuple<float&, std::tuple<int>&>>);
static_assert(std::is_same_v<TTransformAddLRef3, std::tuple<float&, float&, std::string&>>);

using TTransformAddConst0 = qx::tuple_utils::transform_t<TTuple0, std::add_const>;
using TTransformAddConst1 = qx::tuple_utils::transform_t<TTuple1, std::add_const>;
using TTransformAddConst2 = qx::tuple_utils::transform_t<TTuple2, std::add_const>;
using TTransformAddConst3 = qx::tuple_utils::transform_t<TTuple3, std::add_const>;
static_assert(std::is_same_v<TTransformAddConst0, std::tuple<>>);
static_assert(std::is_same_v<TTransformAddConst1, std::tuple<const int>>);
static_assert(std::is_same_v<TTransformAddConst2, std::tuple<const float, const std::tuple<int>>>);
static_assert(std::is_same_v<TTransformAddConst3, std::tuple<const float, const float, const std::string>>);

using TTransformAddVolatile0 = qx::tuple_utils::transform_t<TTuple0, std::add_volatile>;
using TTransformAddVolatile1 = qx::tuple_utils::transform_t<TTuple1, std::add_volatile>;
using TTransformAddVolatile2 = qx::tuple_utils::transform_t<TTuple2, std::add_volatile>;
using TTransformAddVolatile3 = qx::tuple_utils::transform_t<TTuple3, std::add_volatile>;
static_assert(std::is_same_v<TTransformAddVolatile0, std::tuple<>>);
static_assert(std::is_same_v<TTransformAddVolatile1, std::tuple<volatile int>>);
static_assert(std::is_same_v<TTransformAddVolatile2, std::tuple<volatile float, volatile std::tuple<int>>>);
static_assert(std::is_same_v<TTransformAddVolatile3, std::tuple<volatile float, volatile float, volatile std::string>>);




// -------------------------------------------------- qx::tuple_utils::index -------------------------------------------------

static_assert(qx::tuple_utils::index_v<TTuple1, int> == 0);
static_assert(qx::tuple_utils::index_v<TTuple2, float> == 0);
static_assert(qx::tuple_utils::index_v<TTuple3, std::string> == 2);




// ------------------------------------------------- qx::tuple_utils::iterate ------------------------------------------------

TEST(tuple, iterate)
{
    using TTuple        = std::tuple<float, int, std::string, unsigned, size_t>;
    size_t nInvocations = 0;
    qx::tuple_utils::iterate<TTuple>(
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




// ---------------------------------------------- qx::tuple_utils::permutations ----------------------------------------------

using permutationsAB = qx::tuple_utils::permutations_t<A, B>;
static_assert(std::tuple_size_v<permutationsAB> == 6);
static_assert(std::is_same_v<std::tuple_element_t<0, permutationsAB>, std::tuple<A>>);
static_assert(std::is_same_v<std::tuple_element_t<1, permutationsAB>, std::tuple<B>>);
static_assert(std::is_same_v<std::tuple_element_t<2, permutationsAB>, std::tuple<A, A>>);
static_assert(std::is_same_v<std::tuple_element_t<3, permutationsAB>, std::tuple<A, B>>);
static_assert(std::is_same_v<std::tuple_element_t<4, permutationsAB>, std::tuple<B, A>>);
static_assert(std::is_same_v<std::tuple_element_t<5, permutationsAB>, std::tuple<B, B>>);

using permutationsABC = qx::tuple_utils::permutations_t<A, B, C>;
static_assert(std::tuple_size_v<permutationsABC> == 39);
static_assert(std::is_same_v<std::tuple_element_t<0, permutationsABC>, std::tuple<A>>);
static_assert(std::is_same_v<std::tuple_element_t<1, permutationsABC>, std::tuple<B>>);
static_assert(std::is_same_v<std::tuple_element_t<2, permutationsABC>, std::tuple<C>>);
static_assert(std::is_same_v<std::tuple_element_t<3, permutationsABC>, std::tuple<A, A>>);
static_assert(std::is_same_v<std::tuple_element_t<4, permutationsABC>, std::tuple<A, B>>);
static_assert(std::is_same_v<std::tuple_element_t<5, permutationsABC>, std::tuple<A, C>>);
static_assert(std::is_same_v<std::tuple_element_t<6, permutationsABC>, std::tuple<B, A>>);
static_assert(std::is_same_v<std::tuple_element_t<7, permutationsABC>, std::tuple<B, B>>);
static_assert(std::is_same_v<std::tuple_element_t<8, permutationsABC>, std::tuple<B, C>>);
static_assert(std::is_same_v<std::tuple_element_t<9, permutationsABC>, std::tuple<C, A>>);
static_assert(std::is_same_v<std::tuple_element_t<10, permutationsABC>, std::tuple<C, B>>);
static_assert(std::is_same_v<std::tuple_element_t<11, permutationsABC>, std::tuple<C, C>>);
static_assert(std::is_same_v<std::tuple_element_t<12, permutationsABC>, std::tuple<A, A, A>>);
static_assert(std::is_same_v<std::tuple_element_t<13, permutationsABC>, std::tuple<A, A, B>>);
static_assert(std::is_same_v<std::tuple_element_t<14, permutationsABC>, std::tuple<A, A, C>>);
static_assert(std::is_same_v<std::tuple_element_t<15, permutationsABC>, std::tuple<A, B, A>>);
static_assert(std::is_same_v<std::tuple_element_t<16, permutationsABC>, std::tuple<A, B, B>>);
static_assert(std::is_same_v<std::tuple_element_t<17, permutationsABC>, std::tuple<A, B, C>>);
static_assert(std::is_same_v<std::tuple_element_t<18, permutationsABC>, std::tuple<A, C, A>>);
static_assert(std::is_same_v<std::tuple_element_t<19, permutationsABC>, std::tuple<A, C, B>>);
static_assert(std::is_same_v<std::tuple_element_t<20, permutationsABC>, std::tuple<A, C, C>>);
static_assert(std::is_same_v<std::tuple_element_t<21, permutationsABC>, std::tuple<B, A, A>>);
static_assert(std::is_same_v<std::tuple_element_t<22, permutationsABC>, std::tuple<B, A, B>>);
static_assert(std::is_same_v<std::tuple_element_t<23, permutationsABC>, std::tuple<B, A, C>>);
static_assert(std::is_same_v<std::tuple_element_t<24, permutationsABC>, std::tuple<B, B, A>>);
static_assert(std::is_same_v<std::tuple_element_t<25, permutationsABC>, std::tuple<B, B, B>>);
static_assert(std::is_same_v<std::tuple_element_t<26, permutationsABC>, std::tuple<B, B, C>>);
static_assert(std::is_same_v<std::tuple_element_t<27, permutationsABC>, std::tuple<B, C, A>>);
static_assert(std::is_same_v<std::tuple_element_t<28, permutationsABC>, std::tuple<B, C, B>>);
static_assert(std::is_same_v<std::tuple_element_t<29, permutationsABC>, std::tuple<B, C, C>>);
static_assert(std::is_same_v<std::tuple_element_t<30, permutationsABC>, std::tuple<C, A, A>>);
static_assert(std::is_same_v<std::tuple_element_t<31, permutationsABC>, std::tuple<C, A, B>>);
static_assert(std::is_same_v<std::tuple_element_t<32, permutationsABC>, std::tuple<C, A, C>>);
static_assert(std::is_same_v<std::tuple_element_t<33, permutationsABC>, std::tuple<C, B, A>>);
static_assert(std::is_same_v<std::tuple_element_t<34, permutationsABC>, std::tuple<C, B, B>>);
static_assert(std::is_same_v<std::tuple_element_t<35, permutationsABC>, std::tuple<C, B, C>>);
static_assert(std::is_same_v<std::tuple_element_t<36, permutationsABC>, std::tuple<C, C, A>>);
static_assert(std::is_same_v<std::tuple_element_t<37, permutationsABC>, std::tuple<C, C, B>>);
static_assert(std::is_same_v<std::tuple_element_t<38, permutationsABC>, std::tuple<C, C, C>>);




// ----------------------------------------- qx::tuple_utils::cartesian_product ----------------------------------------

using cartesian_product1 =
    qx::tuple_utils::cartesian_product_t<std::tuple<A, B, C>, std::tuple<E, D>, std::tuple<F, G>>;
static_assert(std::tuple_size_v<cartesian_product1> == 12);
static_assert(std::is_same_v<std::tuple_element_t<0, cartesian_product1>, std::tuple<A, E, F>>);
static_assert(std::is_same_v<std::tuple_element_t<1, cartesian_product1>, std::tuple<A, E, G>>);
static_assert(std::is_same_v<std::tuple_element_t<2, cartesian_product1>, std::tuple<A, D, F>>);
static_assert(std::is_same_v<std::tuple_element_t<3, cartesian_product1>, std::tuple<A, D, G>>);
static_assert(std::is_same_v<std::tuple_element_t<4, cartesian_product1>, std::tuple<B, E, F>>);
static_assert(std::is_same_v<std::tuple_element_t<5, cartesian_product1>, std::tuple<B, E, G>>);
static_assert(std::is_same_v<std::tuple_element_t<6, cartesian_product1>, std::tuple<B, D, F>>);
static_assert(std::is_same_v<std::tuple_element_t<7, cartesian_product1>, std::tuple<B, D, G>>);
static_assert(std::is_same_v<std::tuple_element_t<8, cartesian_product1>, std::tuple<C, E, F>>);
static_assert(std::is_same_v<std::tuple_element_t<9, cartesian_product1>, std::tuple<C, E, G>>);
static_assert(std::is_same_v<std::tuple_element_t<10, cartesian_product1>, std::tuple<C, D, F>>);
static_assert(std::is_same_v<std::tuple_element_t<11, cartesian_product1>, std::tuple<C, D, G>>);

using cartesian_product2 =
    qx::tuple_utils::cartesian_product_t<std::tuple<A, B, C, D>, std::tuple<E>, std::tuple<F, G>>;
static_assert(std::tuple_size_v<cartesian_product2> == 8);
static_assert(std::is_same_v<std::tuple_element_t<0, cartesian_product2>, std::tuple<A, E, F>>);
static_assert(std::is_same_v<std::tuple_element_t<1, cartesian_product2>, std::tuple<A, E, G>>);
static_assert(std::is_same_v<std::tuple_element_t<2, cartesian_product2>, std::tuple<B, E, F>>);
static_assert(std::is_same_v<std::tuple_element_t<3, cartesian_product2>, std::tuple<B, E, G>>);
static_assert(std::is_same_v<std::tuple_element_t<4, cartesian_product2>, std::tuple<C, E, F>>);
static_assert(std::is_same_v<std::tuple_element_t<5, cartesian_product2>, std::tuple<C, E, G>>);
static_assert(std::is_same_v<std::tuple_element_t<6, cartesian_product2>, std::tuple<D, E, F>>);
static_assert(std::is_same_v<std::tuple_element_t<7, cartesian_product2>, std::tuple<D, E, G>>);




// --------------------------------------------- qx::tuple_utils::all_of_v ---------------------------------------------

static_assert(qx::tuple_utils::all_of_v<std::is_void, std::tuple<>>);
static_assert(qx::tuple_utils::all_of_v<std::is_void, std::tuple<void>>);
static_assert(qx::tuple_utils::all_of_v<std::is_void, std::tuple<void, void, void>>);
static_assert(qx::tuple_utils::all_of_v<std::is_void, std::tuple<void, void, void, void>>);

static_assert(!qx::tuple_utils::all_of_v<std::is_void, std::tuple<void, int>>);
static_assert(!qx::tuple_utils::all_of_v<std::is_void, std::tuple<int, void>>);
static_assert(!qx::tuple_utils::all_of_v<std::is_void, std::tuple<int>>);
static_assert(!qx::tuple_utils::all_of_v<std::is_void, std::tuple<void, int, void, int*>>);
