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
protected:
    using StringType = qx::basic_string<StringTraits>;
};


using Implementations = ::testing::Types
<
    qx::char_traits<char>,
    qx::char_traits<wchar_t>
>;

TYPED_TEST_SUITE(TestQxString, Implementations);

TYPED_TEST(TestQxString, construct)
{
    // empty
    StringType str0;
    EXPECT_TRUE(str0.empty());
    EXPECT_EQ(str0.size(), 0);

    // from literal string
    StringType str1(STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_STREQ(str1.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(str1.size(), 11);

    // from string
    StringType str2(str1);
    EXPECT_STREQ(str1.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(str1.size(), 11);
    EXPECT_STREQ(str2.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(str2.size(), 11);

    // move from string
    StringType str3(std::move(str1));
    EXPECT_STREQ(str3.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str3.empty());
    EXPECT_EQ(str3.size(), 11);
    EXPECT_TRUE(str1.empty());
    EXPECT_EQ(str1.size(), 0);

    // from char
    StringType str4(CHAR_PREFIX(TypeParam::value_type, 'q'));
    EXPECT_STREQ(str4.data(), STR_PREFIX(TypeParam::value_type, "q"));
    EXPECT_FALSE(str4.empty());
    EXPECT_EQ(str4.size(), 1);

    // from multiple chars
    StringType str5(10, CHAR_PREFIX(TypeParam::value_type, 'q'));
    EXPECT_STREQ(str5.data(), STR_PREFIX(TypeParam::value_type, "qqqqqqqqqq"));
    EXPECT_FALSE(str5.empty());
    EXPECT_EQ(str5.size(), 10);

    // from literal string N chars
    StringType str6(STR_PREFIX(TypeParam::value_type, "Hello world"), 6);
    EXPECT_STREQ(str6.data(), STR_PREFIX(TypeParam::value_type, "Hello "));
    EXPECT_FALSE(str6.empty());
    EXPECT_EQ(str6.size(), 6);

    // from iterators
    StringType iterStr(STR_PREFIX(TypeParam::value_type, "aurora"));

    StringType str7(iterStr.begin(), iterStr.end());
    EXPECT_STREQ(str7.data(), STR_PREFIX(TypeParam::value_type, "aurora"));
    EXPECT_FALSE(str7.empty());
    EXPECT_EQ(str7.size(), 6);

    StringType str8(iterStr.cbegin(), iterStr.cend());
    EXPECT_STREQ(str8.data(), STR_PREFIX(TypeParam::value_type, "aurora"));
    EXPECT_FALSE(str8.empty());
    EXPECT_EQ(str8.size(), 6);

    StringType str9(iterStr.rbegin(), iterStr.rend());
    EXPECT_STREQ(str9.data(), STR_PREFIX(TypeParam::value_type, "arorua"));
    EXPECT_FALSE(str9.empty());
    EXPECT_EQ(str9.size(), 6);

    StringType str10(iterStr.crbegin(), iterStr.crend());
    EXPECT_STREQ(str10.data(), STR_PREFIX(TypeParam::value_type, "arorua"));
    EXPECT_FALSE(str10.empty());
    EXPECT_EQ(str10.size(), 6);

    // from std string
    StringType str11(TypeParam::std_string_type(STR_PREFIX(TypeParam::value_type, "Hello world")));
    EXPECT_STREQ(str11.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str11.empty());
    EXPECT_EQ(str11.size(), 11);
}

TYPED_TEST(TestQxString, assign)
{
    // from literal string
    StringType str1;
    str1.assign(STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_STREQ(str1.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(str1.size(), 11);

    // from string
    StringType str2;
    str2.assign(str1);
    EXPECT_STREQ(str1.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(str1.size(), 11);
    EXPECT_STREQ(str2.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(str2.size(), 11);

    // move from string
    StringType str3;
    str3.assign(std::move(str1));
    EXPECT_STREQ(str3.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str3.empty());
    EXPECT_EQ(str3.size(), 11);
    EXPECT_TRUE(str1.empty());
    EXPECT_EQ(str1.size(), 0);

    // from char
    StringType str4;
    str4.assign(CHAR_PREFIX(TypeParam::value_type, 'q'));
    EXPECT_STREQ(str4.data(), STR_PREFIX(TypeParam::value_type, "q"));
    EXPECT_FALSE(str4.empty());
    EXPECT_EQ(str4.size(), 1);

    // from multiple chars
    StringType str5;
    str5.assign(10, CHAR_PREFIX(TypeParam::value_type, 'q'));
    EXPECT_STREQ(str5.data(), STR_PREFIX(TypeParam::value_type, "qqqqqqqqqq"));
    EXPECT_FALSE(str5.empty());
    EXPECT_EQ(str5.size(), 10);

    // from literal string N chars
    StringType str6;
    str6.assign(STR_PREFIX(TypeParam::value_type, "Hello world"), 6);
    EXPECT_STREQ(str6.data(), STR_PREFIX(TypeParam::value_type, "Hello "));
    EXPECT_FALSE(str6.empty());
    EXPECT_EQ(str6.size(), 6);

    // iterators
    StringType iterStr(STR_PREFIX(TypeParam::value_type, "aurora"));

    StringType str7;
    str7.assign(iterStr.begin(), iterStr.end());
    EXPECT_STREQ(str7.data(), STR_PREFIX(TypeParam::value_type, "aurora"));
    EXPECT_FALSE(str7.empty());
    EXPECT_EQ(str7.size(), 6);

    StringType str8;
    str8.assign(iterStr.cbegin(), iterStr.cend());
    EXPECT_STREQ(str8.data(), STR_PREFIX(TypeParam::value_type, "aurora"));
    EXPECT_FALSE(str8.empty());
    EXPECT_EQ(str8.size(), 6);

    StringType str9;
    str9.assign(iterStr.rbegin(), iterStr.rend());
    EXPECT_STREQ(str9.data(), STR_PREFIX(TypeParam::value_type, "arorua"));
    EXPECT_FALSE(str9.empty());
    EXPECT_EQ(str9.size(), 6);

    StringType str10;
    str10.assign(iterStr.crbegin(), iterStr.crend());
    EXPECT_STREQ(str10.data(), STR_PREFIX(TypeParam::value_type, "arorua"));
    EXPECT_FALSE(str10.empty());
    EXPECT_EQ(str10.size(), 6);

    // from std string
    StringType str11;
    str11.assign(TypeParam::std_string_type(STR_PREFIX(TypeParam::value_type, "Hello world")));
    EXPECT_STREQ(str11.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str11.empty());
    EXPECT_EQ(str11.size(), 11);
}

TYPED_TEST(TestQxString, operator_assign)
{
    StringType str;

    str = STR_PREFIX(TypeParam::value_type, "Hello world");
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);

    str = CHAR_PREFIX(TypeParam::value_type, 'q');
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "q"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 1);

    StringType tmpStr(STR_PREFIX(TypeParam::value_type, "Hello world"));
    str = tmpStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);

    str.clear();
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(str.size(), 0);

    str = std::move(tmpStr);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);
    EXPECT_TRUE(tmpStr.empty());
    EXPECT_EQ(tmpStr.size(), 0);

    str = TypeParam::std_string_type(STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);
}

TYPED_TEST(TestQxString, format)
{
    StringType str0;
    str0.format(STR_PREFIX(TypeParam::value_type, "The half of %d is %f"), 75, 75.f / 2);
    EXPECT_STREQ(str0.data(), STR_PREFIX(TypeParam::value_type, "The half of 75 is 37.500000"));
    EXPECT_FALSE(str0.empty());
    EXPECT_EQ(str0.size(), 27);

    StringType str1 = StringType::sformat(STR_PREFIX(TypeParam::value_type, "The half of %d is %f"), 75, 75.f / 2);
    EXPECT_STREQ(str1.data(), STR_PREFIX(TypeParam::value_type, "The half of 75 is 37.500000"));
    EXPECT_FALSE(str0.empty());
    EXPECT_EQ(str1.size(), 27);
}

TYPED_TEST(TestQxString, size)
{
    StringType str0;
    EXPECT_TRUE(str0.empty());
    EXPECT_EQ(str0.size(), 0);
    EXPECT_EQ(str0.capacity(), 0);

    StringType::size_type nCapacity = str0.reserve(20);
    EXPECT_EQ(str0.size(), 0);
    EXPECT_TRUE(str0.empty());
    EXPECT_TRUE(nCapacity > 0);
    EXPECT_EQ(nCapacity % TypeParam::talign(), 0);

    str0 = STR_PREFIX(TypeParam::value_type, "some short sentence");
    EXPECT_TRUE(str0.size() > 0);
    EXPECT_TRUE(str0.capacity() > 0);
    EXPECT_TRUE(str0.size() <= str0.capacity());

    str0 = STR_PREFIX(TypeParam::value_type, "some long long long long long sentence");
    EXPECT_EQ(str0.size(), 38);
    EXPECT_TRUE(str0.capacity() > nCapacity);
    nCapacity = str0.capacity();
    EXPECT_TRUE(str0.size() <= nCapacity);
    EXPECT_EQ(nCapacity % TypeParam::talign(), 0);

    StringType::size_type nNewCapacity = str0.reserve(10);
    EXPECT_EQ(nNewCapacity, nCapacity);

    str0.fit();
    EXPECT_EQ(str0.size(), 38);
    EXPECT_EQ(str0.size() + 1, str0.capacity());
    EXPECT_TRUE(str0.capacity() < nNewCapacity);
}

TYPED_TEST(TestQxString, erase)
{
    StringType wholeStr = STR_PREFIX(TypeParam::value_type, "you can erase some of these words");

    StringType erasingStr = wholeStr;
    erasingStr.erase(erasingStr.begin());
    EXPECT_EQ(erasingStr.size(), 32);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "ou can erase some of these words"));
    erasingStr.erase(erasingStr.begin() + 5);
    EXPECT_EQ(erasingStr.size(), 31);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "ou ca erase some of these words"));
    erasingStr.erase(erasingStr.begin() + 15);
    EXPECT_EQ(erasingStr.size(), 30);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "ou ca erase som of these words"));
    erasingStr.erase(erasingStr.begin() + erasingStr.size() - 1);
    EXPECT_EQ(erasingStr.size(), 29);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "ou ca erase som of these word"));

    erasingStr = wholeStr;
    erasingStr.erase(erasingStr.begin(), erasingStr.begin() + 4);
    EXPECT_EQ(erasingStr.size(), 29);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "can erase some of these words"));
    erasingStr.erase(erasingStr.begin() + 4, erasingStr.begin() + 10);
    EXPECT_EQ(erasingStr.size(), 23);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "can some of these words"));
    erasingStr.erase(erasingStr.begin() + 12, erasingStr.begin() + 18);
    EXPECT_EQ(erasingStr.size(), 17);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "can some of words"));
    erasingStr.erase(erasingStr.begin() + 11, erasingStr.begin() + 17);
    EXPECT_EQ(erasingStr.size(), 11);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "can some of"));

    erasingStr = wholeStr;
    erasingStr.erase(0);
    EXPECT_EQ(erasingStr.size(), 32);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "ou can erase some of these words"));
    erasingStr.erase(5);
    EXPECT_EQ(erasingStr.size(), 31);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "ou ca erase some of these words"));
    erasingStr.erase(15);
    EXPECT_EQ(erasingStr.size(), 30);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "ou ca erase som of these words"));
    erasingStr.erase(erasingStr.size() - 1);
    EXPECT_EQ(erasingStr.size(), 29);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "ou ca erase som of these word"));

    erasingStr = wholeStr;
    erasingStr.erase(0, 4);
    EXPECT_EQ(erasingStr.size(), 29);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "can erase some of these words"));
    erasingStr.erase(4, 6);
    EXPECT_EQ(erasingStr.size(), 23);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "can some of these words"));
    erasingStr.erase(12, 6);
    EXPECT_EQ(erasingStr.size(), 17);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "can some of words"));
    erasingStr.erase(11, 6);
    EXPECT_EQ(erasingStr.size(), 11);
    EXPECT_STREQ(erasingStr.data(), STR_PREFIX(TypeParam::value_type, "can some of"));
}

TYPED_TEST(TestQxString, insert)
{
    StringType sourceStr = STR_PREFIX(TypeParam::value_type, "can you ");
    auto pSource1 = STR_PREFIX(TypeParam::value_type, "can ");
    auto pSource2 = STR_PREFIX(TypeParam::value_type, "some ");
    auto pSource3 = STR_PREFIX(TypeParam::value_type, " here! really");
    auto pSource4 = STR_PREFIX(TypeParam::value_type, "nice niiiice");

    StringType insertingStr = STR_PREFIX(TypeParam::value_type, "insert words");
    insertingStr.insert(insertingStr.begin(), sourceStr.begin() + 4, sourceStr.begin() + 8);
    EXPECT_EQ(insertingStr.size(), 16);
    EXPECT_STREQ(insertingStr.data(), STR_PREFIX(TypeParam::value_type, "you insert words"));

    insertingStr.insert(insertingStr.begin() + 4, pSource1);
    EXPECT_EQ(insertingStr.size(), 20);
    EXPECT_STREQ(insertingStr.data(), STR_PREFIX(TypeParam::value_type, "you can insert words"));

    insertingStr.insert(15, pSource2);
    EXPECT_EQ(insertingStr.size(), 25);
    EXPECT_STREQ(insertingStr.data(), STR_PREFIX(TypeParam::value_type, "you can insert some words"));

    insertingStr.insert(25, pSource3, 5);
    EXPECT_EQ(insertingStr.size(), 30);
    EXPECT_STREQ(insertingStr.data(), STR_PREFIX(TypeParam::value_type, "you can insert some words here"));

    insertingStr.insert(insertingStr.begin() + 20, pSource4, 5);
    EXPECT_EQ(insertingStr.size(), 35);
    EXPECT_STREQ(insertingStr.data(), STR_PREFIX(TypeParam::value_type, "you can insert some nice words here"));

    insertingStr.push_back('\"');
    EXPECT_EQ(insertingStr.size(), 36);
    EXPECT_STREQ(insertingStr.data(), STR_PREFIX(TypeParam::value_type, "you can insert some nice words here\""));

    insertingStr.push_front('\"');
    EXPECT_EQ(insertingStr.size(), 37);
    EXPECT_STREQ(insertingStr.data(), STR_PREFIX(TypeParam::value_type, "\"you can insert some nice words here\""));
}

TYPED_TEST(TestQxString, find)
{
    StringType str(STR_PREFIX(TypeParam::value_type, "for string for words and for searching"));
    auto test = [str] (auto toSearch)
    {
        StringType::size_type pos0 = str.find(toSearch);
        EXPECT_EQ(pos0, 0);

        StringType::size_type pos1 = str.find(toSearch, 15);
        EXPECT_EQ(pos1, 25);

        StringType::size_type pos2 = str.find(toSearch, 4, 14);
        EXPECT_EQ(pos2, 11);

        StringType::size_type pos3 = str.find(toSearch, 30);
        EXPECT_EQ(pos3, StringType::npos);
    };

    test(STR_PREFIX(TypeParam::value_type, "for"));
    test(StringType(STR_PREFIX(TypeParam::value_type, "for")));
    test(CHAR_PREFIX(TypeParam::value_type, 'f'));
}

TYPED_TEST(TestQxString, substr)
{
    StringType str(STR_PREFIX(TypeParam::value_type, "many different words placed here"));

    StringType str0 = str.substr(0, 4);
    EXPECT_EQ(str0.size(), 4);
    EXPECT_STREQ(str0.data(), STR_PREFIX(TypeParam::value_type, "many"));

    StringType str1 = str.substr(5, 9);
    EXPECT_EQ(str1.size(), 9);
    EXPECT_STREQ(str1.data(), STR_PREFIX(TypeParam::value_type, "different"));

    StringType str2 = str.substr(15, 5);
    EXPECT_EQ(str2.size(), 5);
    EXPECT_STREQ(str2.data(), STR_PREFIX(TypeParam::value_type, "words"));

    StringType str3 = str.substr(21, 6);
    EXPECT_EQ(str3.size(), 6);
    EXPECT_STREQ(str3.data(), STR_PREFIX(TypeParam::value_type, "placed"));

    StringType str4 = str.substr(28);
    EXPECT_EQ(str4.size(), 4);
    EXPECT_STREQ(str4.data(), STR_PREFIX(TypeParam::value_type, "here"));
}

TYPED_TEST(TestQxString, find_last_of)
{
    StringType str(STR_PREFIX(TypeParam::value_type, "many different words placed here"));
    EXPECT_EQ(str.find_last_of(CHAR_PREFIX(TypeParam::value_type, 'e')), 31);
    EXPECT_EQ(str.find_last_of(CHAR_PREFIX(TypeParam::value_type, 'd')), 26);
    EXPECT_EQ(str.find_last_of(CHAR_PREFIX(TypeParam::value_type, 'p')), 21);
    EXPECT_EQ(str.find_last_of(CHAR_PREFIX(TypeParam::value_type, ' ')), 27);
}

TYPED_TEST(TestQxString, split)
{
    StringType str1(STR_PREFIX(TypeParam::value_type, "many different words placed here"));
    StringType str2(STR_PREFIX(TypeParam::value_type, "some, long, long, long, long, long, sentence"));

    auto words1 = str1.split(CHAR_PREFIX(TypeParam::value_type, ' '));
    EXPECT_EQ(words1.size(), 5);
    EXPECT_STREQ(words1[0].data(), STR_PREFIX(TypeParam::value_type, "many"));
    EXPECT_STREQ(words1[1].data(), STR_PREFIX(TypeParam::value_type, "different"));
    EXPECT_STREQ(words1[2].data(), STR_PREFIX(TypeParam::value_type, "words"));
    EXPECT_STREQ(words1[3].data(), STR_PREFIX(TypeParam::value_type, "placed"));
    EXPECT_STREQ(words1[4].data(), STR_PREFIX(TypeParam::value_type, "here"));

    auto words2 = str2.split(STR_PREFIX(TypeParam::value_type, ", "));
    EXPECT_EQ(words2.size(), 7);
    EXPECT_STREQ(words2[0].data(), STR_PREFIX(TypeParam::value_type, "some"));
    EXPECT_STREQ(words2[1].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words2[2].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words2[3].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words2[4].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words2[5].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words2[6].data(), STR_PREFIX(TypeParam::value_type, "sentence"));

    auto words3 = str2.split(StringType(STR_PREFIX(TypeParam::value_type, ", ")));
    EXPECT_EQ(words3.size(), 7);
    EXPECT_STREQ(words3[0].data(), STR_PREFIX(TypeParam::value_type, "some"));
    EXPECT_STREQ(words3[1].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words3[2].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words3[3].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words3[4].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words3[5].data(), STR_PREFIX(TypeParam::value_type, "long"));
    EXPECT_STREQ(words3[6].data(), STR_PREFIX(TypeParam::value_type, "sentence"));
}

TYPED_TEST(TestQxString, erase_all_of)
{
    StringType str0(STR_PREFIX(TypeParam::value_type, "multi\nline\nstring"));
    str0.erase_line_breaks();
    EXPECT_EQ(str0.size(), 15);
    EXPECT_STREQ(str0.data(), STR_PREFIX(TypeParam::value_type, "multilinestring"));

    StringType str1(STR_PREFIX(TypeParam::value_type, "multi\n\rline\n\rstring"));
    str1.erase_line_breaks();
    EXPECT_EQ(str1.size(), 15);
    EXPECT_STREQ(str1.data(), STR_PREFIX(TypeParam::value_type, "multilinestring"));

    StringType str2(STR_PREFIX(TypeParam::value_type, "aaaaabbbcccccd"));
    str2.erase_all_of(CHAR_PREFIX(TypeParam::value_type, 'c'));
    EXPECT_EQ(str2.size(), 9);
    EXPECT_STREQ(str2.data(), STR_PREFIX(TypeParam::value_type, "aaaaabbbd"));

    StringType str3(STR_PREFIX(TypeParam::value_type, "aaaaabbbcccccd"));
    str3.erase_all_of(CHAR_PREFIX(TypeParam::value_type, 'c'), CHAR_PREFIX(TypeParam::value_type, 'a'));
    EXPECT_EQ(str3.size(), 4);
    EXPECT_STREQ(str3.data(), STR_PREFIX(TypeParam::value_type, "bbbd"));

    StringType str4(STR_PREFIX(TypeParam::value_type, "aaaaabbbcccccd"));
    std::array toErase { CHAR_PREFIX(TypeParam::value_type, 'c'), CHAR_PREFIX(TypeParam::value_type, 'a') };
    str4.erase_all_of(toErase.begin(), toErase.end());
    EXPECT_EQ(str4.size(), 4);
    EXPECT_STREQ(str4.data(), STR_PREFIX(TypeParam::value_type, "bbbd"));
}

TYPED_TEST(TestQxString, apply_case)
{
    StringType str(STR_PREFIX(TypeParam::value_type, "maNy diffeRent words placEd Here. yoU can test,iT. really"));

    StringType str0(str);
    str0.apply_case(qx::eCaseType::lower);
    EXPECT_EQ(str0.size(), str.size());
    EXPECT_STREQ(str0.data(), STR_PREFIX(TypeParam::value_type, "many different words placed here. you can test,it. really"));

    StringType str1(str);
    str1.apply_case(qx::eCaseType::upper);
    EXPECT_EQ(str1.size(), str.size());
    EXPECT_STREQ(str1.data(), STR_PREFIX(TypeParam::value_type, "MANY DIFFERENT WORDS PLACED HERE. YOU CAN TEST,IT. REALLY"));

    StringType str2(str);
    str2.apply_case(qx::eCaseType::random);
    EXPECT_EQ(str2.size(), str.size());
}

TYPED_TEST(TestQxString, to)
{
    {
        StringType str(STR_PREFIX(TypeParam::value_type, "50"));

        auto n0 = str.to<int>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), 50);

        auto n1 = str.to<float>();
        EXPECT_TRUE(n1.has_value());
        EXPECT_FLOAT_EQ(n1.value(), 50.f);

        auto n2 = str.to<unsigned>();
        EXPECT_TRUE(n2.has_value());
        EXPECT_EQ(n2.value(), 50u);
    }

    {
        StringType str(STR_PREFIX(TypeParam::value_type, "50.f"));

        auto n0 = str.to<int>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), 50);

        auto n1 = str.to<float>();
        EXPECT_TRUE(n1.has_value());
        EXPECT_FLOAT_EQ(n1.value(), 50.f);

        auto n2 = str.to<unsigned>();
        EXPECT_TRUE(n2.has_value());
        EXPECT_EQ(n2.value(), 50u);
    }

    {
        StringType str(STR_PREFIX(TypeParam::value_type, "-50"));

        auto n0 = str.to<int>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), -50);

        auto n1 = str.to<float>();
        EXPECT_TRUE(n1.has_value());
        EXPECT_FLOAT_EQ(n1.value(), -50.f);

        auto n2 = str.to<unsigned>();
        EXPECT_FALSE(n2.has_value());
    }

    {
        StringType str(STR_PREFIX(TypeParam::value_type, "trash"));

        auto n0 = str.to<int>();
        EXPECT_FALSE(n0.has_value());

        auto n1 = str.to<float>();
        EXPECT_FALSE(n1.has_value());

        auto n2 = str.to<unsigned>();
        EXPECT_FALSE(n2.has_value());
    }
}

TYPED_TEST(TestQxString, operator_plus_equal)
{
    StringType str(STR_PREFIX(TypeParam::value_type, "word0 "));
    str += StringType(STR_PREFIX(TypeParam::value_type, "word1 "));
    str += STR_PREFIX(TypeParam::value_type, "word2 ");
    str += TypeParam::std_string_type(STR_PREFIX(TypeParam::value_type, "word3"));
    str += CHAR_PREFIX(TypeParam::value_type, '!');

    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word0 word1 word2 word3!"));
}

TYPED_TEST(TestQxString, operator_equal)
{
    StringType str(STR_PREFIX(TypeParam::value_type, "e"));
    EXPECT_TRUE(str == StringType(STR_PREFIX(TypeParam::value_type, "e")));
    EXPECT_TRUE(str == CHAR_PREFIX(TypeParam::value_type, 'e'));
    EXPECT_TRUE(str == STR_PREFIX(TypeParam::value_type, "e"));
    EXPECT_TRUE(str == TypeParam::std_string_type(STR_PREFIX(TypeParam::value_type, "e")));
    EXPECT_FALSE(str == StringType(STR_PREFIX(TypeParam::value_type, "r")));
    EXPECT_FALSE(str == CHAR_PREFIX(TypeParam::value_type, 'r'));
    EXPECT_FALSE(str == STR_PREFIX(TypeParam::value_type, "r"));
    EXPECT_FALSE(str == TypeParam::std_string_type(STR_PREFIX(TypeParam::value_type, "r")));
}

TYPED_TEST(TestQxString, operator_braces)
{
    StringType str = STR_PREFIX(TypeParam::value_type, "Hello world");
    EXPECT_EQ(str[0], CHAR_PREFIX(TypeParam::value_type, 'H'));
    EXPECT_EQ(str[1], CHAR_PREFIX(TypeParam::value_type, 'e'));
    EXPECT_EQ(str[2], CHAR_PREFIX(TypeParam::value_type, 'l'));
    EXPECT_EQ(str[3], CHAR_PREFIX(TypeParam::value_type, 'l'));
    EXPECT_EQ(str[4], CHAR_PREFIX(TypeParam::value_type, 'o'));
    EXPECT_EQ(str[5], CHAR_PREFIX(TypeParam::value_type, ' '));
    EXPECT_EQ(str[6], CHAR_PREFIX(TypeParam::value_type, 'w'));
    EXPECT_EQ(str[7], CHAR_PREFIX(TypeParam::value_type, 'o'));
    EXPECT_EQ(str[8], CHAR_PREFIX(TypeParam::value_type, 'r'));
    EXPECT_EQ(str[9], CHAR_PREFIX(TypeParam::value_type, 'l'));
    EXPECT_EQ(str[10], CHAR_PREFIX(TypeParam::value_type, 'd'));
}

TYPED_TEST(TestQxString, operator_plus)
{
    StringType str;

    StringType refStr(STR_PREFIX(TypeParam::value_type, "word_ref "));
    str = refStr + refStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_ref word_ref "));
    str = StringType(STR_PREFIX(TypeParam::value_type, "word_move ")) + StringType(STR_PREFIX(TypeParam::value_type, "word_move "));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_move word_move "));
    str = StringType(STR_PREFIX(TypeParam::value_type, "word_move ")) + refStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_move word_ref "));
    str = refStr + StringType(STR_PREFIX(TypeParam::value_type, "word_move "));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_ref word_move "));

    TypeParam::const_pointer pStr = STR_PREFIX(TypeParam::value_type, "word_const_ptr ");
    str = refStr + pStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_ref word_const_ptr "));
    str = StringType(STR_PREFIX(TypeParam::value_type, "word_move ")) + pStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_move word_const_ptr "));
    str = pStr + refStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_const_ptr word_ref "));
    str = pStr + StringType(STR_PREFIX(TypeParam::value_type, "word_move "));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_const_ptr word_move "));

    TypeParam::value_type ch = CHAR_PREFIX(TypeParam::value_type, 'w');
    str = refStr + ch;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_ref w"));
    str = StringType(STR_PREFIX(TypeParam::value_type, "word_move ")) + ch;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_move w"));
    str = ch + refStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "wword_ref "));
    str = ch + StringType(STR_PREFIX(TypeParam::value_type, "word_move "));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "wword_move "));

    TypeParam::std_string_type stdStr(STR_PREFIX(TypeParam::value_type, "word_std "));
    str = refStr + stdStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_ref word_std "));
    str = StringType(STR_PREFIX(TypeParam::value_type, "word_move ")) + stdStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_move word_std "));
    str = stdStr + refStr;
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_std word_ref "));
    str = stdStr + StringType(STR_PREFIX(TypeParam::value_type, "word_move "));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "word_std word_move "));
}

TYPED_TEST(TestQxString, hashes)
{
    std::unordered_map<StringType, int> map;
    EXPECT_EQ(map.size(), 0);

    map[StringType(STR_PREFIX(TypeParam::value_type, "Hello world"))] = 0;
    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map[STR_PREFIX(TypeParam::value_type, "Hello world")], 0);
}

TYPED_TEST(TestQxString, at)
{
    StringType str(STR_PREFIX(TypeParam::value_type, "Hello world!"));
    EXPECT_EQ(str[0], CHAR_PREFIX(TypeParam::value_type, 'H'));
    EXPECT_EQ(str[2], CHAR_PREFIX(TypeParam::value_type, 'l'));
    EXPECT_EQ(str[6], CHAR_PREFIX(TypeParam::value_type, 'w'));
    EXPECT_EQ(str[11], CHAR_PREFIX(TypeParam::value_type, '!'));
    EXPECT_EQ(str.back(), CHAR_PREFIX(TypeParam::value_type, '!'));
    EXPECT_EQ(str.front(), CHAR_PREFIX(TypeParam::value_type, 'H'));
}

TYPED_TEST(TestQxString, from)
{
    StringType str;

    str.from(char(10));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "10"));

    str.from(unsigned char(20));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "20"));

    str.from(short(30));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "30"));

    str.from(unsigned short(40));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "40"));

    str.from(50);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "50"));

    str.from(60u);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "60"));

    str.from(70l);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "70"));

    str.from(80ul);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "80"));

    str.from(90ll);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "90"));

    str.from(100ull);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "100"));

    str.from(110.f);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "110.000000"));

    str.from(120.0);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "120.000000"));

    str.from(long double(130.0));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "130.000000"));

    str.from(nullptr);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "nullptr"));

    str.from((void*)0x000000000028FF44);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "0x000000000028FF44"));

    str.from(true);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "true"));

    str.from(false);
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "false"));

    // std strings have operator<<
    str.from(TypeParam::std_string_type(STR_PREFIX(TypeParam::value_type, "some string")));
    EXPECT_STREQ(str.data(), STR_PREFIX(TypeParam::value_type, "some string"));
}

#endif