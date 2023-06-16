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
