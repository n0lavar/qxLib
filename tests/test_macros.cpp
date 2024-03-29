/**

    @file      test_macros.cpp
    @author    Khrapov
    @date      25.09.2020
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_macros.cpp

#include <qx/containers/string/string_utils.h>
#include <qx/macros/apply.h>
#include <qx/macros/common.h>
#include <qx/macros/static_assert.h>

#include <map>

// --------------------------------------------------- QX_EMPTY_MACRO --------------------------------------------------

#define EMPTY1 QX_EMPTY_MACRO
#define EMPTY2 QX_EMPTY_MACRO

TEST(macros, empty_macro)
{
    // check compilation

    if (1)
        EMPTY1;
    else
        EMPTY2;

    if constexpr (1)
        EMPTY1;
    else
        EMPTY2;
}



// ---------------------------------------------------- QX_STRINGIFY ---------------------------------------------------

constexpr int  val     = 0;
constexpr auto pszName = QX_STRINGIFY(val);
QX_STATIC_ASSERT_STR_EQ(pszName, "val");



// ---------------------------------------------------- QX_LINE_NAME ---------------------------------------------------

constexpr int QX_LINE_NAME(test) = 5;
static_assert(test52 == 5);



// --------------------------------------------------- QX_SHORT_FILE ---------------------------------------------------

constexpr auto pszFileName = QX_SHORT_FILE;
QX_STATIC_ASSERT_STR_EQ(pszFileName, QX_TEXT("test_macros.cpp"));



// ------------------------------------------------- QX_SINGLE_ARGUMENT ------------------------------------------------

#define MACRO_WITH_2_ARGS(a, b) \
    if (a != b)                 \
        throw std::exception();

TEST(macros, single_argument)
{
    // check compilation
    MACRO_WITH_2_ARGS(QX_SINGLE_ARGUMENT(std::map<int, int>().size()), 0);
}



// ------------------------------------------------ QX_STATIC_ASSERT_XX ------------------------------------------------

QX_STATIC_ASSERT_EQ(0, 0);
QX_STATIC_ASSERT_EQ(1, 1);
QX_STATIC_ASSERT_EQ(2, 2);

QX_STATIC_ASSERT_NE(0, 1);
QX_STATIC_ASSERT_NE(1, 2);
QX_STATIC_ASSERT_NE(2, 0);

QX_STATIC_ASSERT_LT(0, 1);
QX_STATIC_ASSERT_LT(1, 2);
QX_STATIC_ASSERT_LT(2, 3);

QX_STATIC_ASSERT_LE(0, 0);
QX_STATIC_ASSERT_LE(0, 1);
QX_STATIC_ASSERT_LE(0, 2);

QX_STATIC_ASSERT_GT(1, 0);
QX_STATIC_ASSERT_GT(2, 1);
QX_STATIC_ASSERT_GT(3, 1);

QX_STATIC_ASSERT_GE(1, 0);
QX_STATIC_ASSERT_GE(1, 1);
QX_STATIC_ASSERT_GE(2, 1);



// ---------------------------------------------- QX_STATIC_ASSERT_STR_XX ----------------------------------------------

QX_STATIC_ASSERT_STR_EQ("", "");
QX_STATIC_ASSERT_STR_EQ("string", "string");
QX_STATIC_ASSERT_STR_EQ("kakaka", "kakaka");

QX_STATIC_ASSERT_STR_NE("string1", "string2");
QX_STATIC_ASSERT_STR_NE("string1", "string");
QX_STATIC_ASSERT_STR_NE("", "string");
QX_STATIC_ASSERT_STR_NE("string", "");

QX_STATIC_ASSERT_STR_LT("1", "2");
QX_STATIC_ASSERT_STR_LT("12", "13");
QX_STATIC_ASSERT_STR_LT("", "1");

QX_STATIC_ASSERT_STR_LE("1", "2");
QX_STATIC_ASSERT_STR_LE("1", "1");
QX_STATIC_ASSERT_STR_LE("", "1");

QX_STATIC_ASSERT_STR_GT("2", "1");
QX_STATIC_ASSERT_STR_GT("12", "11");
QX_STATIC_ASSERT_STR_GT("1", "");

QX_STATIC_ASSERT_STR_GE("2", "1");
QX_STATIC_ASSERT_STR_GE("1", "1");
QX_STATIC_ASSERT_STR_GE("", "");



// ---------------------------------------------- QX_STATIC_ASSERT_BETWEEN ---------------------------------------------

QX_STATIC_ASSERT_BETWEEN(0, 0, 0);
QX_STATIC_ASSERT_BETWEEN(0, 0, 1);
QX_STATIC_ASSERT_BETWEEN(0, 1, 2);
QX_STATIC_ASSERT_BETWEEN(0, 2, 2);



// --------------------------------------------------- QX_STR_PREFIX ---------------------------------------------------

constexpr const char*    psz  = QX_STR_PREFIX(char, "string");
constexpr const wchar_t* pwsz = QX_STR_PREFIX(wchar_t, "wstring");



// --------------------------------------------------- QX_CHAR_PREFIX --------------------------------------------------

constexpr char ch = QX_CHAR_PREFIX(char, 'c');
static_assert(ch == 'c');

constexpr wchar_t wch = QX_CHAR_PREFIX(wchar_t, 'w');
static_assert(wch == L'w');



// ---------------------------------------------------- QX_APPLY_XXX ---------------------------------------------------

static int Foo(int nNumber)
{
    return nNumber;
}

template<class... ArgsType>
int Sum(ArgsType... args)
{
    return (args + ...);
}

TEST(macros, QX_APPLY_COMMA)
{
    EXPECT_EQ(Sum(QX_APPLY_COMMA(Foo, 1, 2, 3)), 6);
}

int         g_nSum = 0;
static void Bar(int nNumber)
{
    g_nSum += nNumber;
}

TEST(macros, QX_APPLY_SEMICOLON)
{
    QX_APPLY_SEMICOLON(Bar, 1, 2, 3);
    EXPECT_EQ(g_nSum, 6);
}
