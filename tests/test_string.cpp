//============================================================================
//
//!\file                       test_string.cpp
//
//!\brief       test qx::string
//!\details     ~
//
//!\author      Khrapov
//!\date        15.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#include <config.h>

//V_EXCLUDE_PATH *test_string.cpp

#if QX_TEST_STRING

#include <qx/containers/string.h>
#include <unordered_map>
#include <gtest/gtest.h>

//============================================================================
//
//!\class                 TestQxString<StringTraits>
//
//!\brief   Test class for qx::string and qx::wstring
//!\details ~
//
//!\author  Khrapov
//!\date    24.03.2020
//
//============================================================================
template <typename StringTraits>
class TestQxString : public ::testing::Test
{
};

#define StringTypeTn typename qx::basic_string<TypeParam>
#define StringType qx::basic_string<TypeParam>
#define ValueType typename TypeParam::value_type
#define STR(str) STR_PREFIX(ValueType, str)
#define CH(str) CHAR_PREFIX(ValueType, str)

using Implementations = ::testing::Types
<
    qx::char_traits<16>,
    qx::wchar_traits<16>,
    qx::char_traits<1>,
    qx::wchar_traits<1>
>;

TYPED_TEST_SUITE(TestQxString, Implementations);

TYPED_TEST(TestQxString, construct)
{
    // empty
    StringTypeTn str0;
    EXPECT_TRUE(str0.empty());
    EXPECT_EQ(str0.size(), 0);

    // from literal string
    StringTypeTn str1(STR("Hello world"));
    EXPECT_STREQ(str1.data(), STR("Hello world"));
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(str1.size(), 11);

    // from string
    StringTypeTn str2(str1);
    EXPECT_STREQ(str1.data(), STR("Hello world"));
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(str1.size(), 11);
    EXPECT_STREQ(str2.data(), STR("Hello world"));
    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(str2.size(), 11);

    // move from string
    StringTypeTn str3(std::move(str1));
    EXPECT_STREQ(str3.data(), STR("Hello world"));
    EXPECT_FALSE(str3.empty());
    EXPECT_EQ(str3.size(), 11);
    EXPECT_TRUE(str1.empty());
    EXPECT_EQ(str1.size(), 0);

    // from char
    StringTypeTn str4(CH('q'));
    EXPECT_STREQ(str4.data(), STR("q"));
    EXPECT_FALSE(str4.empty());
    EXPECT_EQ(str4.size(), 1);

    // from multiple chars
    StringTypeTn str5(10, CH('q'));
    EXPECT_STREQ(str5.data(), STR("qqqqqqqqqq"));
    EXPECT_FALSE(str5.empty());
    EXPECT_EQ(str5.size(), 10);

    // from literal string N chars
    StringTypeTn str6(STR("Hello world"), 6);
    EXPECT_STREQ(str6.data(), STR("Hello "));
    EXPECT_FALSE(str6.empty());
    EXPECT_EQ(str6.size(), 6);

    // from iterators
    StringTypeTn iterStr(STR("aurora"));

    StringTypeTn str7(iterStr.begin(), iterStr.end());
    EXPECT_STREQ(str7.data(), STR("aurora"));
    EXPECT_FALSE(str7.empty());
    EXPECT_EQ(str7.size(), 6);

    StringTypeTn str8(iterStr.cbegin(), iterStr.cend());
    EXPECT_STREQ(str8.data(), STR("aurora"));
    EXPECT_FALSE(str8.empty());
    EXPECT_EQ(str8.size(), 6);

    StringTypeTn str9(iterStr.rbegin(), iterStr.rend());
    EXPECT_STREQ(str9.data(), STR("arorua"));
    EXPECT_FALSE(str9.empty());
    EXPECT_EQ(str9.size(), 6);

    StringTypeTn str10(iterStr.crbegin(), iterStr.crend());
    EXPECT_STREQ(str10.data(), STR("arorua"));
    EXPECT_FALSE(str10.empty());
    EXPECT_EQ(str10.size(), 6);

    // from std string
    StringTypeTn str11(typename TypeParam::std_string_type(STR("Hello world")));
    EXPECT_STREQ(str11.data(), STR("Hello world"));
    EXPECT_FALSE(str11.empty());
    EXPECT_EQ(str11.size(), 11);
}

TYPED_TEST(TestQxString, assign)
{
    // from literal string
    StringTypeTn str1;
    str1.assign(STR("Hello world"));
    EXPECT_STREQ(str1.data(), STR("Hello world"));
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(str1.size(), 11);

    // from string
    StringTypeTn str2;
    str2.assign(str1);
    EXPECT_STREQ(str1.data(), STR("Hello world"));
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(str1.size(), 11);
    EXPECT_STREQ(str2.data(), STR("Hello world"));
    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(str2.size(), 11);

    // move from string
    StringTypeTn str3;
    str3.assign(std::move(str1));
    EXPECT_STREQ(str3.data(), STR("Hello world"));
    EXPECT_FALSE(str3.empty());
    EXPECT_EQ(str3.size(), 11);
    EXPECT_TRUE(str1.empty());
    EXPECT_EQ(str1.size(), 0);

    // from char
    StringTypeTn str4;
    str4.assign(CH('q'));
    EXPECT_STREQ(str4.data(), STR("q"));
    EXPECT_FALSE(str4.empty());
    EXPECT_EQ(str4.size(), 1);

    // from multiple chars
    StringTypeTn str5;
    str5.assign(10, CH('q'));
    EXPECT_STREQ(str5.data(), STR("qqqqqqqqqq"));
    EXPECT_FALSE(str5.empty());
    EXPECT_EQ(str5.size(), 10);

    // from literal string N chars
    StringTypeTn str6;
    str6.assign(STR("Hello world"), 6);
    EXPECT_STREQ(str6.data(), STR("Hello "));
    EXPECT_FALSE(str6.empty());
    EXPECT_EQ(str6.size(), 6);

    // iterators
    StringTypeTn iterStr(STR("aurora"));

    StringTypeTn str7;
    str7.assign(iterStr.begin(), iterStr.end());
    EXPECT_STREQ(str7.data(), STR("aurora"));
    EXPECT_FALSE(str7.empty());
    EXPECT_EQ(str7.size(), 6);

    StringTypeTn str8;
    str8.assign(iterStr.cbegin(), iterStr.cend());
    EXPECT_STREQ(str8.data(), STR("aurora"));
    EXPECT_FALSE(str8.empty());
    EXPECT_EQ(str8.size(), 6);

    StringTypeTn str9;
    str9.assign(iterStr.rbegin(), iterStr.rend());
    EXPECT_STREQ(str9.data(), STR("arorua"));
    EXPECT_FALSE(str9.empty());
    EXPECT_EQ(str9.size(), 6);

    StringTypeTn str10;
    str10.assign(iterStr.crbegin(), iterStr.crend());
    EXPECT_STREQ(str10.data(), STR("arorua"));
    EXPECT_FALSE(str10.empty());
    EXPECT_EQ(str10.size(), 6);

    // from std string
    StringTypeTn str11;
    str11.assign(typename TypeParam::std_string_type(STR("Hello world")));
    EXPECT_STREQ(str11.data(), STR("Hello world"));
    EXPECT_FALSE(str11.empty());
    EXPECT_EQ(str11.size(), 11);
}

TYPED_TEST(TestQxString, operator_assign)
{
    StringTypeTn str;

    str = STR("Hello world");
    EXPECT_STREQ(str.data(), STR("Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);

    str = CH('q');
    EXPECT_STREQ(str.data(), STR("q"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 1);

    StringTypeTn tmpStr(STR("Hello world"));
    str = tmpStr;
    EXPECT_STREQ(str.data(), STR("Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);

    str.clear();
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(str.size(), 0);

    str = std::move(tmpStr);
    EXPECT_STREQ(str.data(), STR("Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);
    EXPECT_TRUE(tmpStr.empty());
    EXPECT_EQ(tmpStr.size(), 0);

    str = typename TypeParam::std_string_type(STR("Hello world"));
    EXPECT_STREQ(str.data(), STR("Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);
}

TYPED_TEST(TestQxString, format)
{
    StringTypeTn str0;
    str0.format(STR("The half of %d is %f"), 75, 75.f / 2);
    EXPECT_STREQ(str0.data(), STR("The half of 75 is 37.500000"));
    EXPECT_FALSE(str0.empty());
    EXPECT_EQ(str0.size(), 27);

    StringTypeTn str1 = StringType::sformat(STR("The half of %d is %f"), 75, 75.f / 2);
    EXPECT_STREQ(str1.data(), STR("The half of 75 is 37.500000"));
    EXPECT_FALSE(str0.empty());
    EXPECT_EQ(str1.size(), 27);
}

TYPED_TEST(TestQxString, size)
{
    StringTypeTn str0;
    EXPECT_TRUE(str0.empty());
    EXPECT_EQ(str0.size(), 0);
    EXPECT_EQ(str0.capacity(), 0);

    typename TypeParam::size_type nCapacity = str0.reserve(20);
    EXPECT_EQ(str0.size(), 0);
    EXPECT_TRUE(str0.empty());
    EXPECT_TRUE(nCapacity > 0);
    EXPECT_EQ(nCapacity % TypeParam::talign(), 0);

    str0 = STR("some short sentence");
    EXPECT_TRUE(str0.size() > 0);
    EXPECT_TRUE(str0.capacity() > 0);
    EXPECT_TRUE(str0.size() <= str0.capacity());

    str0 = STR("some long long long long long sentence");
    EXPECT_EQ(str0.size(), 38);
    EXPECT_TRUE(str0.capacity() > nCapacity);
    nCapacity = str0.capacity();
    EXPECT_TRUE(str0.size() <= nCapacity);
    EXPECT_EQ(nCapacity % TypeParam::talign(), 0);

    typename TypeParam::size_type nNewCapacity = str0.reserve(10);
    EXPECT_EQ(nNewCapacity, nCapacity);

    str0.fit();
    EXPECT_EQ(str0.size(), 38);
    EXPECT_EQ(str0.size() + 1, str0.capacity());
    EXPECT_TRUE(str0.capacity() < nNewCapacity);
}

TYPED_TEST(TestQxString, erase)
{
    StringTypeTn wholeStr = STR("you can erase some of these words");

    StringTypeTn erasingStr = wholeStr;
    erasingStr.erase(erasingStr.begin());
    EXPECT_EQ(erasingStr.size(), 32);
    EXPECT_STREQ(erasingStr.data(), STR("ou can erase some of these words"));
    erasingStr.erase(erasingStr.begin() + 5);
    EXPECT_EQ(erasingStr.size(), 31);
    EXPECT_STREQ(erasingStr.data(), STR("ou ca erase some of these words"));
    erasingStr.erase(erasingStr.begin() + 15);
    EXPECT_EQ(erasingStr.size(), 30);
    EXPECT_STREQ(erasingStr.data(), STR("ou ca erase som of these words"));
    erasingStr.erase(erasingStr.begin() + erasingStr.size() - 1);
    EXPECT_EQ(erasingStr.size(), 29);
    EXPECT_STREQ(erasingStr.data(), STR("ou ca erase som of these word"));

    erasingStr = wholeStr;
    erasingStr.erase(erasingStr.begin(), erasingStr.begin() + 4);
    EXPECT_EQ(erasingStr.size(), 29);
    EXPECT_STREQ(erasingStr.data(), STR("can erase some of these words"));
    erasingStr.erase(erasingStr.begin() + 4, erasingStr.begin() + 10);
    EXPECT_EQ(erasingStr.size(), 23);
    EXPECT_STREQ(erasingStr.data(), STR("can some of these words"));
    erasingStr.erase(erasingStr.begin() + 12, erasingStr.begin() + 18);
    EXPECT_EQ(erasingStr.size(), 17);
    EXPECT_STREQ(erasingStr.data(), STR("can some of words"));
    erasingStr.erase(erasingStr.begin() + 11, erasingStr.begin() + 17);
    EXPECT_EQ(erasingStr.size(), 11);
    EXPECT_STREQ(erasingStr.data(), STR("can some of"));

    erasingStr = wholeStr;
    erasingStr.erase(0);
    EXPECT_EQ(erasingStr.size(), 32);
    EXPECT_STREQ(erasingStr.data(), STR("ou can erase some of these words"));
    erasingStr.erase(5);
    EXPECT_EQ(erasingStr.size(), 31);
    EXPECT_STREQ(erasingStr.data(), STR("ou ca erase some of these words"));
    erasingStr.erase(15);
    EXPECT_EQ(erasingStr.size(), 30);
    EXPECT_STREQ(erasingStr.data(), STR("ou ca erase som of these words"));
    erasingStr.erase(erasingStr.size() - 1);
    EXPECT_EQ(erasingStr.size(), 29);
    EXPECT_STREQ(erasingStr.data(), STR("ou ca erase som of these word"));

    erasingStr = wholeStr;
    erasingStr.erase(0, 4);
    EXPECT_EQ(erasingStr.size(), 29);
    EXPECT_STREQ(erasingStr.data(), STR("can erase some of these words"));
    erasingStr.erase(4, 6);
    EXPECT_EQ(erasingStr.size(), 23);
    EXPECT_STREQ(erasingStr.data(), STR("can some of these words"));
    erasingStr.erase(12, 6);
    EXPECT_EQ(erasingStr.size(), 17);
    EXPECT_STREQ(erasingStr.data(), STR("can some of words"));
    erasingStr.erase(11, 6);
    EXPECT_EQ(erasingStr.size(), 11);
    EXPECT_STREQ(erasingStr.data(), STR("can some of"));
}

TYPED_TEST(TestQxString, insert)
{
    StringTypeTn sourceStr = STR("can you ");
    auto pSource1 = STR("can ");
    auto pSource2 = STR("some ");
    auto pSource3 = STR(" here! really");
    auto pSource4 = STR("nice niiiice");

    StringTypeTn insertingStr = STR("insert words");
    insertingStr.insert(insertingStr.begin(), sourceStr.begin() + 4, sourceStr.begin() + 8);
    EXPECT_EQ(insertingStr.size(), 16);
    EXPECT_STREQ(insertingStr.data(), STR("you insert words"));

    insertingStr.insert(insertingStr.begin() + 4, pSource1);
    EXPECT_EQ(insertingStr.size(), 20);
    EXPECT_STREQ(insertingStr.data(), STR("you can insert words"));

    insertingStr.insert(15, pSource2);
    EXPECT_EQ(insertingStr.size(), 25);
    EXPECT_STREQ(insertingStr.data(), STR("you can insert some words"));

    insertingStr.insert(25, pSource3, 5);
    EXPECT_EQ(insertingStr.size(), 30);
    EXPECT_STREQ(insertingStr.data(), STR("you can insert some words here"));

    insertingStr.insert(insertingStr.begin() + 20, pSource4, 5);
    EXPECT_EQ(insertingStr.size(), 35);
    EXPECT_STREQ(insertingStr.data(), STR("you can insert some nice words here"));

    insertingStr.push_back('\"');
    EXPECT_EQ(insertingStr.size(), 36);
    EXPECT_STREQ(insertingStr.data(), STR("you can insert some nice words here\""));

    insertingStr.push_front('\"');
    EXPECT_EQ(insertingStr.size(), 37);
    EXPECT_STREQ(insertingStr.data(), STR("\"you can insert some nice words here\""));
}

TYPED_TEST(TestQxString, find)
{
    StringTypeTn str(STR("for string for words and for searching"));
    auto test = [str] (auto toSearch)
    {
        typename TypeParam::size_type pos0 = str.find(toSearch);
        EXPECT_EQ(pos0, 0);

        typename TypeParam::size_type pos1 = str.find(toSearch, 15);
        EXPECT_EQ(pos1, 25);

        typename TypeParam::size_type pos2 = str.find(toSearch, 4, 14);
        EXPECT_EQ(pos2, 11);

        typename TypeParam::size_type pos3 = str.find(toSearch, 30);
        EXPECT_EQ(pos3, StringType::npos);
    };

    test(STR("for"));
    test(StringTypeTn(STR("for")));
    test(CH('f'));
}

TYPED_TEST(TestQxString, substr)
{
    StringTypeTn str(STR("many different words placed here"));

    StringTypeTn str0 = str.substr(0, 4);
    EXPECT_EQ(str0.size(), 4);
    EXPECT_STREQ(str0.data(), STR("many"));

    StringTypeTn str1 = str.substr(5, 9);
    EXPECT_EQ(str1.size(), 9);
    EXPECT_STREQ(str1.data(), STR("different"));

    StringTypeTn str2 = str.substr(15, 5);
    EXPECT_EQ(str2.size(), 5);
    EXPECT_STREQ(str2.data(), STR("words"));

    StringTypeTn str3 = str.substr(21, 6);
    EXPECT_EQ(str3.size(), 6);
    EXPECT_STREQ(str3.data(), STR("placed"));

    StringTypeTn str4 = str.substr(28);
    EXPECT_EQ(str4.size(), 4);
    EXPECT_STREQ(str4.data(), STR("here"));
}

TYPED_TEST(TestQxString, find_last_of)
{
    StringTypeTn str(STR("many different words placed here"));
    EXPECT_EQ(str.find_last_of(CH('e')), 31);
    EXPECT_EQ(str.find_last_of(CH('d')), 26);
    EXPECT_EQ(str.find_last_of(CH('p')), 21);
    EXPECT_EQ(str.find_last_of(CH(' ')), 27);
}

TYPED_TEST(TestQxString, split)
{
    StringTypeTn str1(STR("many different words placed here"));
    StringTypeTn str2(STR("some, long, long, long, long, long, sentence"));

    auto words1 = str1.split(CH(' '));
    EXPECT_EQ(words1.size(), 5);
    EXPECT_STREQ(words1[0].data(), STR("many"));
    EXPECT_STREQ(words1[1].data(), STR("different"));
    EXPECT_STREQ(words1[2].data(), STR("words"));
    EXPECT_STREQ(words1[3].data(), STR("placed"));
    EXPECT_STREQ(words1[4].data(), STR("here"));

    auto words2 = str2.split(STR(", "));
    EXPECT_EQ(words2.size(), 7);
    EXPECT_STREQ(words2[0].data(), STR("some"));
    EXPECT_STREQ(words2[1].data(), STR("long"));
    EXPECT_STREQ(words2[2].data(), STR("long"));
    EXPECT_STREQ(words2[3].data(), STR("long"));
    EXPECT_STREQ(words2[4].data(), STR("long"));
    EXPECT_STREQ(words2[5].data(), STR("long"));
    EXPECT_STREQ(words2[6].data(), STR("sentence"));

    auto words3 = str2.split(StringTypeTn(STR(", ")));
    EXPECT_EQ(words3.size(), 7);
    EXPECT_STREQ(words3[0].data(), STR("some"));
    EXPECT_STREQ(words3[1].data(), STR("long"));
    EXPECT_STREQ(words3[2].data(), STR("long"));
    EXPECT_STREQ(words3[3].data(), STR("long"));
    EXPECT_STREQ(words3[4].data(), STR("long"));
    EXPECT_STREQ(words3[5].data(), STR("long"));
    EXPECT_STREQ(words3[6].data(), STR("sentence"));
}

TYPED_TEST(TestQxString, erase_all_of)
{
    StringTypeTn str0(STR("multi\nline\nstring"));
    str0.erase_line_breaks();
    EXPECT_EQ(str0.size(), 15);
    EXPECT_STREQ(str0.data(), STR("multilinestring"));

    StringTypeTn str1(STR("multi\n\rline\n\rstring"));
    str1.erase_line_breaks();
    EXPECT_EQ(str1.size(), 15);
    EXPECT_STREQ(str1.data(), STR("multilinestring"));

    StringTypeTn str2(STR("aaaaabbbcccccd"));
    str2.erase_all_of(CH('c'));
    EXPECT_EQ(str2.size(), 9);
    EXPECT_STREQ(str2.data(), STR("aaaaabbbd"));

    StringTypeTn str3(STR("aaaaabbbcccccd"));
    str3.erase_all_of(CH('c'), CH('a'));
    EXPECT_EQ(str3.size(), 4);
    EXPECT_STREQ(str3.data(), STR("bbbd"));

    StringTypeTn str4(STR("aaaaabbbcccccd"));
    std::array toErase { CH('c'), CH('a') };
    str4.erase_all_of(toErase.begin(), toErase.end());
    EXPECT_EQ(str4.size(), 4);
    EXPECT_STREQ(str4.data(), STR("bbbd"));
}

TYPED_TEST(TestQxString, apply_case)
{
    StringTypeTn str(STR("maNy diffeRent words placEd Here. yoU can test,iT. really"));

    StringTypeTn str0(str);
    str0.apply_case(qx::eCaseType::lower);
    EXPECT_EQ(str0.size(), str.size());
    EXPECT_STREQ(str0.data(), STR("many different words placed here. you can test,it. really"));

    StringTypeTn str1(str);
    str1.apply_case(qx::eCaseType::upper);
    EXPECT_EQ(str1.size(), str.size());
    EXPECT_STREQ(str1.data(), STR("MANY DIFFERENT WORDS PLACED HERE. YOU CAN TEST,IT. REALLY"));

    StringTypeTn str2(str);
    str2.apply_case(qx::eCaseType::random);
    EXPECT_EQ(str2.size(), str.size());
}

TYPED_TEST(TestQxString, to)
{
    // clang requires to use 'template' keyword to treat 'to' as a dependent template name
    // you can drop this with MVSC
    {
        StringTypeTn str(STR("50"));

        auto n0 = str.template to<int>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), 50);

        auto n1 = str.template to<float>();
        EXPECT_TRUE(n1.has_value());
        EXPECT_FLOAT_EQ(n1.value(), 50.f);

        auto n2 = str.template to<unsigned>();
        EXPECT_TRUE(n2.has_value());
        EXPECT_EQ(n2.value(), 50u);
    }

    {
        StringTypeTn str(STR("50.f"));

        auto n0 = str.template to<int>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), 50);

        auto n1 = str.template to<float>();
        EXPECT_TRUE(n1.has_value());
        EXPECT_FLOAT_EQ(n1.value(), 50.f);

        auto n2 = str.template to<unsigned>();
        EXPECT_TRUE(n2.has_value());
        EXPECT_EQ(n2.value(), 50u);
    }

    {
        StringTypeTn str(STR("-50"));

        auto n0 = str.template to<int>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), -50);

        auto n1 = str.template to<float>();
        EXPECT_TRUE(n1.has_value());
        EXPECT_FLOAT_EQ(n1.value(), -50.f);

        auto n2 = str.template to<unsigned>();
        EXPECT_FALSE(n2.has_value());
    }

    {
        StringTypeTn str(STR("trash"));

        auto n0 = str.template to<int>();
        EXPECT_FALSE(n0.has_value());

        auto n1 = str.template to<float>();
        EXPECT_FALSE(n1.has_value());

        auto n2 = str.template to<unsigned>();
        EXPECT_FALSE(n2.has_value());
    }
}

TYPED_TEST(TestQxString, operator_plus_equal)
{
    StringTypeTn str(STR("word0 "));
    str += StringTypeTn(STR("word1 "));
    str += STR("word2 ");
    str += typename TypeParam::std_string_type(STR("word3"));
    str += CH('!');

    EXPECT_STREQ(str.data(), STR("word0 word1 word2 word3!"));
}

TYPED_TEST(TestQxString, operator_equal)
{
    StringTypeTn str(STR("e"));
    EXPECT_TRUE(str == StringTypeTn(STR("e")));
    EXPECT_TRUE(str == CH('e'));
    EXPECT_TRUE(str == STR("e"));
    EXPECT_TRUE(str == typename TypeParam::std_string_type(STR("e")));
    EXPECT_FALSE(str == StringTypeTn(STR("r")));
    EXPECT_FALSE(str == CH('r'));
    EXPECT_FALSE(str == STR("r"));
    EXPECT_FALSE(str == typename TypeParam::std_string_type(STR("r")));
}

TYPED_TEST(TestQxString, operator_braces)
{
    StringTypeTn str = STR("Hello world");
    EXPECT_EQ(str[0], CH('H'));
    EXPECT_EQ(str[1], CH('e'));
    EXPECT_EQ(str[2], CH('l'));
    EXPECT_EQ(str[3], CH('l'));
    EXPECT_EQ(str[4], CH('o'));
    EXPECT_EQ(str[5], CH(' '));
    EXPECT_EQ(str[6], CH('w'));
    EXPECT_EQ(str[7], CH('o'));
    EXPECT_EQ(str[8], CH('r'));
    EXPECT_EQ(str[9], CH('l'));
    EXPECT_EQ(str[10], CH('d'));
}

TYPED_TEST(TestQxString, operator_plus)
{
    StringTypeTn str;

    StringTypeTn refStr(STR("word_ref "));
    str = refStr + refStr;
    EXPECT_STREQ(str.data(), STR("word_ref word_ref "));
    str = StringTypeTn(STR("word_move ")) + StringTypeTn(STR("word_move "));
    EXPECT_STREQ(str.data(), STR("word_move word_move "));
    str = StringTypeTn(STR("word_move ")) + refStr;
    EXPECT_STREQ(str.data(), STR("word_move word_ref "));
    str = refStr + StringTypeTn(STR("word_move "));
    EXPECT_STREQ(str.data(), STR("word_ref word_move "));

    typename TypeParam::const_pointer pStr = STR("word_const_ptr ");
    str = refStr + pStr;
    EXPECT_STREQ(str.data(), STR("word_ref word_const_ptr "));
    str = StringTypeTn(STR("word_move ")) + pStr;
    EXPECT_STREQ(str.data(), STR("word_move word_const_ptr "));
    str = pStr + refStr;
    EXPECT_STREQ(str.data(), STR("word_const_ptr word_ref "));
    str = pStr + StringTypeTn(STR("word_move "));
    EXPECT_STREQ(str.data(), STR("word_const_ptr word_move "));

    ValueType ch = CH('w');
    str = refStr + ch;
    EXPECT_STREQ(str.data(), STR("word_ref w"));
    str = StringTypeTn(STR("word_move ")) + ch;
    EXPECT_STREQ(str.data(), STR("word_move w"));
    str = ch + refStr;
    EXPECT_STREQ(str.data(), STR("wword_ref "));
    str = ch + StringTypeTn(STR("word_move "));
    EXPECT_STREQ(str.data(), STR("wword_move "));

    typename TypeParam::std_string_type stdStr(STR("word_std "));
    str = refStr + stdStr;
    EXPECT_STREQ(str.data(), STR("word_ref word_std "));
    str = StringTypeTn(STR("word_move ")) + stdStr;
    EXPECT_STREQ(str.data(), STR("word_move word_std "));
    str = stdStr + refStr;
    EXPECT_STREQ(str.data(), STR("word_std word_ref "));
    str = stdStr + StringTypeTn(STR("word_move "));
    EXPECT_STREQ(str.data(), STR("word_std word_move "));
}

TYPED_TEST(TestQxString, hashes)
{
    std::unordered_map<StringTypeTn, int> map;
    EXPECT_EQ(map.size(), 0);

    map[StringTypeTn(STR("Hello world"))] = 0;
    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map[STR("Hello world")], 0);
}

TYPED_TEST(TestQxString, at)
{
    StringTypeTn str(STR("Hello world!"));
    EXPECT_EQ(str[0], CH('H'));
    EXPECT_EQ(str[2], CH('l'));
    EXPECT_EQ(str[6], CH('w'));
    EXPECT_EQ(str[11], CH('!'));
    EXPECT_EQ(str.back(), CH('!'));
    EXPECT_EQ(str.front(), CH('H'));
}

TYPED_TEST(TestQxString, from)
{
    StringTypeTn str;

    str.from((char)10);
    EXPECT_STREQ(str.data(), STR("10"));

    str.from((unsigned char)20);
    EXPECT_STREQ(str.data(), STR("20"));

    str.from((short)30);
    EXPECT_STREQ(str.data(), STR("30"));

    str.from((unsigned short)40);
    EXPECT_STREQ(str.data(), STR("40"));

    str.from(50);
    EXPECT_STREQ(str.data(), STR("50"));

    str.from(60u);
    EXPECT_STREQ(str.data(), STR("60"));

    str.from(70l);
    EXPECT_STREQ(str.data(), STR("70"));

    str.from(80ul);
    EXPECT_STREQ(str.data(), STR("80"));

    str.from(90ll);
    EXPECT_STREQ(str.data(), STR("90"));

    str.from(100ull);
    EXPECT_STREQ(str.data(), STR("100"));

    str.from(110.f);
    EXPECT_STREQ(str.data(), STR("110.000000"));

    str.from(120.0);
    EXPECT_STREQ(str.data(), STR("120.000000"));

    str.from((long double)130.0);
    EXPECT_STREQ(str.data(), STR("130.000000"));

    str.from(nullptr);
    EXPECT_STREQ(str.data(), STR("nullptr"));

    str.from((void*)0x000000004128FF44);
    bool bFormatCase1 = (0 == TypeParam::tstrcmp(str.data(), STR("0x000000004128FF44")));
    bool bFormatCase2 = (0 == TypeParam::tstrcmp(str.data(), STR("0x000000004128ff44")));
    bool bFormatCase3 = (0 == TypeParam::tstrcmp(str.data(), STR("0x4128ff44")));
    bool bFormatCase4 = (0 == TypeParam::tstrcmp(str.data(), STR("0x4128FF44")));
    EXPECT_TRUE(bFormatCase1 || bFormatCase2 || bFormatCase3 || bFormatCase4);
    if (!(bFormatCase1 || bFormatCase2 || bFormatCase3 || bFormatCase4))
        EXPECT_STREQ(str.data(), STR("string to check str.data()"));

    str.from(true);
    EXPECT_STREQ(str.data(), STR("true"));

    str.from(false);
    EXPECT_STREQ(str.data(), STR("false"));

    // std strings have operator<<
    str.from(typename TypeParam::std_string_type(STR("some string")));
    EXPECT_STREQ(str.data(), STR("some string"));
}

#endif