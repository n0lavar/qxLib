//==============================================================================
//
//!\file                       test_string.cpp
//
//!\brief       Tests for qx::basic_string
//!\details     ~
//
//!\author      Khrapov
//!\date        15.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_string.cpp

#if QX_TEST_STRING

#include <qx/containers/string.h>
#include <unordered_map>
#include <list>

template<typename Char>
inline constexpr auto get_string_format_specifier(void)
{
    if constexpr (std::is_same_v<Char, char>)
        return "%s";
    else if constexpr (std::is_same_v<Char, wchar_t>)
        return L"%ls";
}

//==============================================================================
//
//!\class                 TestQxString<StringTraits>
//
//!\brief   Test class for qx::string and qx::wstring
//!\details ~
//
//!\author  Khrapov
//!\date    24.03.2020
//
//==============================================================================
template <typename StringTraits>
class TestQxString : public ::testing::Test
{
};

#define ValueType       typename TypeParam::value_type
#define ConstPointer    typename TypeParam::const_pointer
#define StringTypeTn    typename qx::basic_string<TypeParam>
#define StringType      qx::basic_string<TypeParam>
#define StdString       typename std::basic_string<ValueType, std::char_traits<ValueType>, std::allocator<ValueType>>
#define StdStringArg    QX_SINGLE_ARGUMENT(typename std::basic_string<ValueType, std::char_traits<ValueType>, std::allocator<ValueType>>)
#define STR(str)        QX_STR_PREFIX(ValueType, str)
#define CH(str)         QX_CHAR_PREFIX(ValueType, str)

using Implementations = ::testing::Types
<
    qx::char_traits<char>,
    qx::char_traits<wchar_t>
>;

TYPED_TEST_SUITE(TestQxString, Implementations);

TYPED_TEST(TestQxString, class_size)
{
    QX_STATIC_ASSERT_EQ(sizeof(StringType), 64u);
}

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
    StringTypeTn str11(StdString(STR("Hello world")));
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
    str11.assign(StdString(STR("Hello world")));
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

    str = tmpStr;

    str.free();
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(str.size(), 0);
    EXPECT_EQ(str.capacity(), TypeParam::small_string_size());

    str = std::move(tmpStr);
    EXPECT_STREQ(str.data(), STR("Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);
    EXPECT_TRUE(tmpStr.empty());
    EXPECT_EQ(tmpStr.size(), 0);

    str = StdString(STR("Hello world"));
    EXPECT_STREQ(str.data(), STR("Hello world"));
    EXPECT_FALSE(str.empty());
    EXPECT_EQ(str.size(), 11);
}

TYPED_TEST(TestQxString, format)
{
    StringTypeTn str0;
    str0.printf(STR("The half of %d is %f"), 75, 75.f / 2);
    EXPECT_STREQ(str0.data(), STR("The half of 75 is 37.500000"));
    EXPECT_FALSE(str0.empty());
    EXPECT_EQ(str0.size(), 27);

    StringTypeTn str1 = StringType::sprintf(STR("The half of %d is %f"), 75, 75.f / 2);
    EXPECT_STREQ(str1.data(), STR("The half of 75 is 37.500000"));
    EXPECT_FALSE(str0.empty());
    EXPECT_EQ(str1.size(), 27);

    StringTypeTn str2;
    StringTypeTn format;

    str2.printf(STR("%f"), 1.f);
    EXPECT_STREQ(str2.data(), STR("1.000000"));
    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(str2.size(), 8);

    str2.printf(STR("%f %d"), 1.f, 2);
    EXPECT_STREQ(str2.data(), STR("1.000000 2"));
    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(str2.size(), 10);

    format += STR("%f %d ");
    format += get_string_format_specifier<typename TypeParam::value_type>();
    str2.printf(format.data(), 1.f, 2, STR("three"));
    EXPECT_STREQ(str2.data(), STR("1.000000 2 three"));
    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(str2.size(), 16);

    format += STR(" %u");
    str2.printf(format.data(), 1.f, 2, STR("three"), 4u);
    EXPECT_STREQ(str2.data(), STR("1.000000 2 three 4"));
    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(str2.size(), 18);
}

TYPED_TEST(TestQxString, size)
{
    StringTypeTn str0;
    EXPECT_TRUE(str0.empty());
    EXPECT_EQ(str0.size(), 0);
    EXPECT_EQ(str0.capacity(), TypeParam::small_string_size());

    typename TypeParam::size_type nCapacity = str0.reserve(20);
    EXPECT_EQ(str0.size(), 0);
    EXPECT_TRUE(str0.empty());
    EXPECT_TRUE(nCapacity > 0);
    EXPECT_EQ(nCapacity % TypeParam::align(), 0);

    str0 = STR("some short sentence");
    EXPECT_TRUE(str0.size() > 0);
    EXPECT_TRUE(str0.capacity() > 0);
    EXPECT_TRUE(str0.size() <= str0.capacity());

    str0 = STR("some long long long long long long long long long sentence");
    EXPECT_EQ(str0.size(), 58);
    EXPECT_TRUE(str0.capacity() >= nCapacity);
    nCapacity = str0.capacity();
    EXPECT_TRUE(str0.size() <= nCapacity);
    EXPECT_EQ(nCapacity % TypeParam::align(), 0);

    typename TypeParam::size_type nNewCapacity = str0.reserve(10);
    EXPECT_EQ(nNewCapacity, nCapacity);

    str0.shrink_to_fit();
    EXPECT_EQ(str0.size(), 58);
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

template<typename Arg>
auto insert = [](auto& str, auto pos, auto pszStr)
{
    using TChar = std::remove_const_t<std::remove_pointer_t<decltype(pszStr)>>;

    if constexpr (qx::is_random_access_iterator_v<Arg>)
    {
        // random access iterator
        std::basic_string<TChar> iter_str = pszStr;
        return str.insert(pos, iter_str.begin(), iter_str.end());
    }
    else if constexpr (qx::is_specialization_of<Arg, std::list>::value)
    {
        // forward iterator
        std::list<TChar> iter_str;
        while (*pszStr != '\0')
        {
            iter_str.push_back(*pszStr);
            pszStr++;
        }

        return str.insert(pos, iter_str.cbegin(), iter_str.cend());
    }
    else
    {
        // other types
        return str.insert(pos, Arg(pszStr));
    }
};

TYPED_TEST(TestQxString, insert)
{
    StringTypeTn str;
    str.reserve(100);   // cbegin() must be valid

    {
        str = STR("0123456789");

        EXPECT_EQ(str.insert(0, CH(';')), 1);
        EXPECT_EQ(str.size(), 11);
        EXPECT_STREQ(str.data(), STR(";0123456789"));

        EXPECT_EQ(str.insert(6, CH('!')), 7);
        EXPECT_EQ(str.size(), 12);
        EXPECT_STREQ(str.data(), STR(";01234!56789"));

        EXPECT_EQ(str.insert(12, CH('&')), 13);
        EXPECT_EQ(str.size(), 13);
        EXPECT_STREQ(str.data(), STR(";01234!56789&"));
    }

    auto test_continuous = [&str](auto type_var, auto start)
    {
        using type = decltype(type_var);

        str = STR("be careful with that butter knife");

        EXPECT_EQ(insert<type>(str, start + 0u, STR("you ")), 4);
        EXPECT_EQ(str.size(), 37);
        EXPECT_STREQ(str.data(), STR("you be careful with that butter knife"));

        EXPECT_EQ(insert<type>(str, start + 25u, STR("big ")), 29);
        EXPECT_EQ(str.size(), 41);
        EXPECT_STREQ(str.data(), STR("you be careful with that big butter knife"));

        EXPECT_EQ(insert<type>(str, start + 41u, STR(", mate!")), 48);
        EXPECT_EQ(str.size(), 48);
        EXPECT_STREQ(str.data(), STR("you be careful with that big butter knife, mate!"));
    };

    test_continuous(StringType(), 0u);
    test_continuous(StdString(), 0u);
    test_continuous(STR(""), 0u);
    test_continuous(StringTypeTn::iterator(), 0u);
    test_continuous(std::list<ValueType>(), 0u);

    test_continuous(StringType(), str.cbegin());
    test_continuous(StdString(), str.cbegin());
    test_continuous(STR(""), str.cbegin());
    test_continuous(StringTypeTn::iterator(), str.cbegin());
    test_continuous(std::list<ValueType>(), str.cbegin());
}

TYPED_TEST(TestQxString, find)
{
    StringTypeTn str(STR("for string for words and for searching"));

    EXPECT_EQ(str.find(STR("for")), 0);
    EXPECT_EQ(str.find(STR("for"), 15), 25);
    EXPECT_EQ(str.find(STR("for"), 4, StringType::npos, 14), 11);
    EXPECT_EQ(str.find(STR("for"), 30), StringType::npos);
    EXPECT_EQ(str.find(STR("kek")), StringType::npos);

    auto test = [&str] (auto... toSearch)
    {
        EXPECT_EQ(str.find(toSearch...), 0);
        EXPECT_EQ(str.find(toSearch..., 15), 25);
        EXPECT_EQ(str.find(toSearch..., 4, 14), 11);
        EXPECT_EQ(str.find(toSearch..., 30), StringType::npos);
        EXPECT_EQ(str.find(STR("kek")), StringType::npos);
    };

    test(StringTypeTn(STR("for")));
    test(CH('f'));

    auto sStdStr = StdString(STR("for"));
    test(sStdStr);
    test(sStdStr.cbegin(), sStdStr.cend());
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

TYPED_TEST(TestQxString, find_first_of)
{
    StringTypeTn str(STR("many different words placed here"));

    EXPECT_EQ(str.find_first_of(CH('m')), 0);
    EXPECT_EQ(str.find_first_of(CH('a')), 1);
    EXPECT_EQ(str.find_first_of(CH('n')), 2);
    EXPECT_EQ(str.find_first_of(CH(' ')), 4);
    EXPECT_EQ(str.find_first_of(CH('x')), StringType::npos);

    EXPECT_EQ(str.find_first_of(STR("kek"), 0, 3), 9);
    EXPECT_EQ(str.find_first_of(STR("abc"), 0, 3), 1);
    EXPECT_EQ(str.find_first_of(STR("ecc"), 0, 3), 9);
    EXPECT_EQ(str.find_first_of(STR("x"), 0, 1), StringType::npos);
    EXPECT_EQ(str.find_first_of(STR("m"), 0, 1), 0);

    auto test = [&str](auto type_var)
    {
        using type = decltype(type_var);

        EXPECT_EQ(str.find_first_of(type(STR("kek"))), 9);
        EXPECT_EQ(str.find_first_of(type(STR("abc"))), 1);
        EXPECT_EQ(str.find_first_of(type(STR("ecc"))), 9);
        EXPECT_EQ(str.find_first_of(type(STR("x"))), StringType::npos);
        EXPECT_EQ(str.find_first_of(type(STR("m"))), 0);
    };

    test(StringTypeTn());
    test(STR(""));
    test(StdString());
}

TYPED_TEST(TestQxString, find_last_of)
{
    StringTypeTn str(STR("many different words placed here"));

    EXPECT_EQ(str.find_last_of(CH('e')), 31);
    EXPECT_EQ(str.find_last_of(CH('d')), 26);
    EXPECT_EQ(str.find_last_of(CH('p')), 21);
    EXPECT_EQ(str.find_last_of(CH(' ')), 27);
    EXPECT_EQ(str.find_last_of(CH('x')), StringType::npos);

    EXPECT_EQ(str.find_last_of(STR("kek"), 0, 3), 31);
    EXPECT_EQ(str.find_last_of(STR("abc"), 0, 3), 24);
    EXPECT_EQ(str.find_last_of(STR("ecc"), 0, 3), 31);
    EXPECT_EQ(str.find_last_of(STR("x"), 0, 1), StringType::npos);
    EXPECT_EQ(str.find_last_of(STR("m"), 0, 1), 0);

    auto test = [&str](auto type_var)
    {
        using type = decltype(type_var);

        EXPECT_EQ(str.find_last_of(type(STR("kek"))), 31);
        EXPECT_EQ(str.find_last_of(type(STR("abc"))), 24);
        EXPECT_EQ(str.find_last_of(type(STR("ecc"))), 31);
        EXPECT_EQ(str.find_last_of(type(STR("x"))), StringType::npos);
        EXPECT_EQ(str.find_last_of(type(STR("m"))), 0);
    };

    test(StringTypeTn());
    test(STR(""));
    test(StdString());
}

TYPED_TEST(TestQxString, find_first_not_of)
{
    StringTypeTn str(STR("e many different words placed here"));

    EXPECT_EQ(str.find_first_not_of(CH('e')), 1);
    EXPECT_EQ(str.find_first_not_of(CH('a')), 0);
    EXPECT_EQ(str.find_first_not_of(CH('n')), 0);
    EXPECT_EQ(str.find_first_not_of(CH(' ')), 0);
    EXPECT_EQ(str.find_first_not_of(CH('x')), 0);

    EXPECT_EQ(str.find_first_not_of(STR("kek"), 0, 3), 1);
    EXPECT_EQ(str.find_first_not_of(STR("abc"), 0, 3), 0);
    EXPECT_EQ(str.find_first_not_of(STR("ecc"), 0, 3), 1);
    EXPECT_EQ(str.find_first_not_of(STR("x"), 0, 1), 0);
    EXPECT_EQ(str.find_first_not_of(STR("m"), 0, 1), 0);

    auto test = [&str](auto type_var)
    {
        using type = decltype(type_var);

        EXPECT_EQ(str.find_first_not_of(type(STR("kek"))), 1);
        EXPECT_EQ(str.find_first_not_of(type(STR("abc"))), 0);
        EXPECT_EQ(str.find_first_not_of(type(STR("ecc"))), 1);
        EXPECT_EQ(str.find_first_not_of(type(STR("x"))), 0);
        EXPECT_EQ(str.find_first_not_of(type(STR("m"))), 0);
    };

    test(StringTypeTn());
    test(STR(""));
    test(StdString());
}

TYPED_TEST(TestQxString, find_last_not_of)
{
    StringTypeTn str(STR("many different words placed here"));

    EXPECT_EQ(str.find_last_not_of(CH('m')), 31);
    EXPECT_EQ(str.find_last_not_of(CH('a')), 31);
    EXPECT_EQ(str.find_last_not_of(CH('n')), 31);
    EXPECT_EQ(str.find_last_not_of(CH(' ')), 31);
    EXPECT_EQ(str.find_last_not_of(CH('x')), 31);
    EXPECT_EQ(str.find_last_not_of(CH('e')), 30);

    EXPECT_EQ(str.find_last_not_of(STR("kek"), 0, 3), 30);
    EXPECT_EQ(str.find_last_not_of(STR("abc"), 0, 3), 31);
    EXPECT_EQ(str.find_last_not_of(STR("ecr"), 0, 3), 28);
    EXPECT_EQ(str.find_last_not_of(STR("x"), 0, 1), 31);
    EXPECT_EQ(str.find_last_not_of(STR("m"), 0, 1), 31);

    auto test = [&str](auto type_var)
    {
        using type = decltype(type_var);

        EXPECT_EQ(str.find_last_not_of(type(STR("kek"))), 30);
        EXPECT_EQ(str.find_last_not_of(type(STR("abc"))), 31);
        EXPECT_EQ(str.find_last_not_of(type(STR("ecr"))), 28);
        EXPECT_EQ(str.find_last_not_of(type(STR("x"))), 31);
        EXPECT_EQ(str.find_last_not_of(type(STR("m"))), 31);
    };

    test(StringTypeTn());
    test(STR(""));
    test(StdString());
}

TYPED_TEST(TestQxString, split)
{
    StringTypeTn str1(STR("many different words placed here"));

    auto words1 = str1.split(CH(' '));
    EXPECT_EQ(words1.size(), 5);
    EXPECT_STREQ(words1[0].data(), STR("many"));
    EXPECT_STREQ(words1[1].data(), STR("different"));
    EXPECT_STREQ(words1[2].data(), STR("words"));
    EXPECT_STREQ(words1[3].data(), STR("placed"));
    EXPECT_STREQ(words1[4].data(), STR("here"));

    auto check_comma_split = [](auto... splitter)
    {
        StringTypeTn str(STR("some, long, long, long, long, long, sentence"));
        auto words = str.split(splitter...);
        EXPECT_EQ(words.size(), 7);
        EXPECT_STREQ(words[0].data(), STR("some"));
        EXPECT_STREQ(words[1].data(), STR("long"));
        EXPECT_STREQ(words[2].data(), STR("long"));
        EXPECT_STREQ(words[3].data(), STR("long"));
        EXPECT_STREQ(words[4].data(), STR("long"));
        EXPECT_STREQ(words[5].data(), STR("long"));
        EXPECT_STREQ(words[6].data(), STR("sentence"));
    };

    check_comma_split(STR(", "));
    check_comma_split(StringTypeTn(STR(", ")));

    auto sStdString = StdString(STR(", "));
    check_comma_split(sStdString.cbegin(), sStdString.cend());
    check_comma_split(sStdString);
}

TYPED_TEST(TestQxString, remove)
{
    constexpr auto STRING = STR("000110000222345666");

    // value_type
    {
        StringTypeTn str = STRING;

        auto ret1 = str.remove(CH('1'));
        EXPECT_EQ(ret1, 3);
        EXPECT_STREQ(str.data(), STR("00010000222345666"));

        auto ret2 = str.remove(CH('0'));
        EXPECT_EQ(ret2, 0);
        EXPECT_STREQ(str.data(), STR("0010000222345666"));

        auto ret4 = str.remove(CH('4'));
        EXPECT_EQ(ret4, 11);
        EXPECT_STREQ(str.data(), STR("001000022235666"));

        auto ret5 = str.remove(CH('7'));
        EXPECT_EQ(ret5, StringType::npos);
        EXPECT_STREQ(str.data(), STR("001000022235666"));

        auto ret6 = str.remove(CH('0'), 2);
        EXPECT_EQ(ret6, 3);
        EXPECT_STREQ(str.data(), STR("00100022235666"));

        auto ret7 = str.remove(CH('3'), 6, 10);
        EXPECT_EQ(ret7, 9);
        EXPECT_STREQ(str.data(), STR("0010002225666"));

        auto ret8 = str.remove(CH('0'), 6, 10);
        EXPECT_EQ(ret8, StringType::npos);
        EXPECT_STREQ(str.data(), STR("0010002225666"));
    }

    auto check_remove = [STRING](
        auto& str,
        auto expected_ret,
        auto expected_str,
        auto... remove_args)
    {
        auto ret = str.remove(remove_args...);
        EXPECT_EQ(ret, expected_ret);
        EXPECT_STREQ(str.data(), expected_str);
    };

    auto check_remove_type = [&check_remove, STRING](auto type_var)
    {
        using type = decltype(type_var);
        StringTypeTn str = STRING;

        check_remove(
            str,
            5,
            STR("00011222345666"),
            type(STR("0000")));

        check_remove(
            str,
            9,
            STR("0001122235666"),
            type(STR("4")));

        check_remove(
            str,
            StringType::npos,
            STR("0001122235666"),
            type(STR("7")));

        check_remove(
            str,
            1,
            STR("01122235666"),
            type(STR("00")),
            static_cast<StringTypeTn::size_type>(1));

        check_remove(
            str,
            StringType::npos,
            STR("01122235666"),
            type(STR("6")),
            static_cast<StringTypeTn::size_type>(2),
            static_cast<StringTypeTn::size_type>(6));
    };

    check_remove_type(STRING);
    check_remove_type(StringTypeTn());
    check_remove_type(StdString());
}

TYPED_TEST(TestQxString, remove_all)
{
    constexpr auto STRING = STR("000011112222333987");

    {
        StringTypeTn str = STRING;
        StringTypeTn::size_type nOccurrences = 0;

        nOccurrences = str.remove_all('0');
        EXPECT_EQ(nOccurrences, 4);
        EXPECT_STREQ(str.data(), STR("11112222333987"));

        nOccurrences = str.remove_all('9', 0, 5);
        EXPECT_EQ(nOccurrences, 0);
        EXPECT_STREQ(str.data(), STR("11112222333987"));

        nOccurrences = str.remove_all('2', 5, 9);
        EXPECT_EQ(nOccurrences, 3);
        EXPECT_STREQ(str.data(), STR("11112333987"));

        nOccurrences = str.remove_all('7', 9);
        EXPECT_EQ(nOccurrences, 1);
        EXPECT_STREQ(str.data(), STR("1111233398"));
    }

    auto check_remove_all = [STRING](
        auto& str,
        auto expected_ret,
        auto expected_str,
        auto... remove_args)
    {
        auto ret = str.remove_all(remove_args...);
        EXPECT_EQ(ret, expected_ret);
        EXPECT_STREQ(str.data(), expected_str);
    };

    auto check_remove_all_type = [&check_remove_all, STRING](auto type_var)
    {
        using type = decltype(type_var);
        StringTypeTn str = STRING;

        check_remove_all(
            str,
            0,
            STR("000011112222333987"),
            type(STR("00000")));

        check_remove_all(
            str,
            2,
            STR("11112222333987"),
            type(STR("00")));

        check_remove_all(
            str,
            4,
            STR("2222333987"),
            type(STR("1")));

        check_remove_all(
            str,
            1,
            STR("22333987"),
            type(STR("22")),
            static_cast<StringTypeTn::size_type>(2));

        check_remove_all(
            str,
            0,
            STR("22333987"),
            type(STR("22")),
            static_cast<StringTypeTn::size_type>(2),
            static_cast<StringTypeTn::size_type>(5));
    };

    check_remove_all_type(STRING);
    check_remove_all_type(StringTypeTn());
    check_remove_all_type(StdString());
}

TYPED_TEST(TestQxString, apply_case)
{
    StringTypeTn str(STR("maNy diffeRent words placEd Here. yoU can test,iT. really"));

    StringTypeTn str0(str);
    str0.apply_case(qx::case_type::lower);
    EXPECT_EQ(str0.size(), str.size());
    EXPECT_STREQ(str0.data(), STR("many different words placed here. you can test,it. really"));

    StringTypeTn str1(str);
    str1.apply_case(qx::case_type::upper);
    EXPECT_EQ(str1.size(), str.size());
    EXPECT_STREQ(str1.data(), STR("MANY DIFFERENT WORDS PLACED HERE. YOU CAN TEST,IT. REALLY"));
}

// type and operator>> overloading for basic_string::to
struct SNotPod
{
    SNotPod() = default;
    SNotPod(int n) : nData(n) { }
    int nData = 42;
};

template<typename TChar>
std::basic_istream<TChar, std::char_traits<TChar>>& operator>> (std::basic_istream<TChar, std::char_traits<TChar>>& is, SNotPod& obj)
{
    obj = SNotPod(128);
    return is;
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
        EXPECT_TRUE(n2.has_value());
        EXPECT_EQ(n2.value(), 4294967246);
    }

    {
        StringTypeTn str(STR("nullptr"));

        auto n0 = str.template to<std::nullptr_t>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), nullptr);

        auto n1 = str.template to<float>();
        EXPECT_FALSE(n1.has_value());

        auto n2 = str.template to<unsigned>();
        EXPECT_FALSE(n2.has_value());
    }

    {
        StringTypeTn str(STR("true"));

        auto n0 = str.template to<bool>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), true);

        auto n1 = str.template to<float>();
        EXPECT_FALSE(n1.has_value());

        auto n2 = str.template to<unsigned>();
        EXPECT_FALSE(n2.has_value());
    }

    {
        StringTypeTn str(STR("false"));

        auto n0 = str.template to<bool>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value(), false);

        auto n1 = str.template to<float>();
        EXPECT_FALSE(n1.has_value());

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

    {
        StringTypeTn str(STR("nomatterwhat"));

        auto n0 = str.template to<SNotPod>();
        EXPECT_TRUE(n0.has_value());
        EXPECT_EQ(n0.value().nData, 128);

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
    str += StdString(STR("word3"));
    str += CH('!');

    EXPECT_STREQ(str.data(), STR("word0 word1 word2 word3!"));
}

TYPED_TEST(TestQxString, operator_equal)
{
    StringTypeTn str(STR("e"));
    EXPECT_TRUE(str == StringTypeTn(STR("e")));
    EXPECT_TRUE(str == CH('e'));
    EXPECT_TRUE(str == STR("e"));
    EXPECT_TRUE(str == StdStringArg(STR("e")));
    EXPECT_FALSE(str == StringTypeTn(STR("r")));
    EXPECT_FALSE(str == CH('r'));
    EXPECT_FALSE(str == STR("r"));
    EXPECT_FALSE(str == StdStringArg(STR("r")));

    StringTypeTn str2(STR("word"));
    EXPECT_TRUE(str2 == STR("word"));
    EXPECT_FALSE(str2 == STR("dowr"));
    EXPECT_FALSE(str2 == STR("wor"));
    EXPECT_FALSE(str2 == STR("word1"));
}

TYPED_TEST(TestQxString, operator_not_equal)
{
    StringTypeTn str(STR("e"));
    EXPECT_FALSE(str != StringTypeTn(STR("e")));
    EXPECT_FALSE(str != CH('e'));
    EXPECT_FALSE(str != STR("e"));
    EXPECT_FALSE(str != StdStringArg(STR("e")));
    EXPECT_TRUE(str != StringTypeTn(STR("r")));
    EXPECT_TRUE(str != CH('r'));
    EXPECT_TRUE(str != STR("r"));
    EXPECT_TRUE(str != StdStringArg(STR("r")));

    StringTypeTn str2(STR("word"));
    EXPECT_FALSE(str2 != STR("word"));
    EXPECT_TRUE(str2 != STR("dowr"));
    EXPECT_TRUE(str2 != STR("wor"));
    EXPECT_TRUE(str2 != STR("word1"));
}

TYPED_TEST(TestQxString, operator_less)
{
    StringTypeTn str(STR("5"));

    EXPECT_FALSE(str < StringTypeTn(STR("4")));
    EXPECT_FALSE(str < StringTypeTn(STR("5")));
    EXPECT_TRUE(str < StringTypeTn(STR("6")));

    EXPECT_FALSE(str < CH('4'));
    EXPECT_FALSE(str < CH('5'));
    EXPECT_TRUE(str < CH('6'));

    EXPECT_FALSE(str < STR("4"));
    EXPECT_FALSE(str < STR("5"));
    EXPECT_TRUE(str < STR("6"));

    EXPECT_FALSE(str < StdStringArg(STR("4")));
    EXPECT_FALSE(str < StdStringArg(STR("5")));
    EXPECT_TRUE(str < StdStringArg(STR("6")));
}

TYPED_TEST(TestQxString, operator_less_equal)
{
    StringTypeTn str(STR("5"));

    EXPECT_FALSE(str <= StringTypeTn(STR("4")));
    EXPECT_TRUE(str <= StringTypeTn(STR("5")));
    EXPECT_TRUE(str <= StringTypeTn(STR("6")));

    EXPECT_FALSE(str <= CH('4'));
    EXPECT_TRUE(str <= CH('5'));
    EXPECT_TRUE(str <= CH('6'));

    EXPECT_FALSE(str <= STR("4"));
    EXPECT_TRUE(str <= STR("5"));
    EXPECT_TRUE(str <= STR("6"));

    EXPECT_FALSE(str <= StdStringArg(STR("4")));
    EXPECT_TRUE(str <= StdStringArg(STR("5")));
    EXPECT_TRUE(str <= StdStringArg(STR("6")));
}

TYPED_TEST(TestQxString, operator_greater)
{
    StringTypeTn str(STR("5"));

    EXPECT_TRUE(str > StringTypeTn(STR("4")));
    EXPECT_FALSE(str > StringTypeTn(STR("5")));
    EXPECT_FALSE(str > StringTypeTn(STR("6")));

    EXPECT_TRUE(str > CH('4'));
    EXPECT_FALSE(str > CH('5'));
    EXPECT_FALSE(str > CH('6'));

    EXPECT_TRUE(str > STR("4"));
    EXPECT_FALSE(str > STR("5"));
    EXPECT_FALSE(str > STR("6"));

    EXPECT_TRUE(str > StdStringArg(STR("4")));
    EXPECT_FALSE(str > StdStringArg(STR("5")));
    EXPECT_FALSE(str > StdStringArg(STR("6")));
}

TYPED_TEST(TestQxString, operator_greater_equal)
{
    StringTypeTn str(STR("5"));

    EXPECT_TRUE(str >= StringTypeTn(STR("4")));
    EXPECT_TRUE(str >= StringTypeTn(STR("5")));
    EXPECT_FALSE(str >= StringTypeTn(STR("6")));

    EXPECT_TRUE(str >= CH('4'));
    EXPECT_TRUE(str >= CH('5'));
    EXPECT_FALSE(str >= CH('6'));

    EXPECT_TRUE(str >= STR("4"));
    EXPECT_TRUE(str >= STR("5"));
    EXPECT_FALSE(str >= STR("6"));

    EXPECT_TRUE(str >= StdStringArg(STR("4")));
    EXPECT_TRUE(str >= StdStringArg(STR("5")));
    EXPECT_FALSE(str >= StdStringArg(STR("6")));
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

    StdString stdStr(STR("word_std "));
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
    bool bFormatCase1 = str == STR("0x000000004128FF44");
    bool bFormatCase2 = str == STR("0x000000004128ff44");
    bool bFormatCase3 = str == STR("0x4128ff44");
    bool bFormatCase4 = str == STR("0x4128FF44");
    EXPECT_TRUE(bFormatCase1 || bFormatCase2 || bFormatCase3 || bFormatCase4);

    str.from(true);
    EXPECT_STREQ(str.data(), STR("true"));

    str.from(false);
    EXPECT_STREQ(str.data(), STR("false"));

    // std strings have operator<<
    str.from(StdString(STR("some string")));
    EXPECT_STREQ(str.data(), STR("some string"));
}

TYPED_TEST(TestQxString, ends_with)
{
    StringTypeTn str(STR("0123456789"));

    // char
    EXPECT_TRUE(str.ends_with(CH('9')));
    EXPECT_FALSE(str.ends_with(CH('7')));
    EXPECT_FALSE(str.ends_with(CH('2')));
    EXPECT_FALSE(str.ends_with(CH(';')));

    // const_pointer
    EXPECT_TRUE(str.ends_with(STR("")));
    EXPECT_TRUE(str.ends_with(STR("9")));
    EXPECT_TRUE(str.ends_with(STR("89")));
    EXPECT_TRUE(str.ends_with(STR("789")));
    EXPECT_TRUE(str.ends_with(STR("6789")));
    EXPECT_TRUE(str.ends_with(STR("56789")));
    EXPECT_TRUE(str.ends_with(STR("456789")));
    EXPECT_TRUE(str.ends_with(STR("3456789")));
    EXPECT_TRUE(str.ends_with(STR("23456789")));
    EXPECT_TRUE(str.ends_with(STR("123456789")));
    EXPECT_TRUE(str.ends_with(STR("0123456789")));

    EXPECT_FALSE(str.ends_with(STR(" 0123456789")));
    EXPECT_FALSE(str.ends_with(STR("11")));
    EXPECT_FALSE(str.ends_with(STR("trash")));

    // std::basic_string
    EXPECT_TRUE(str.ends_with(StdStringArg(STR(""))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("9"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("89"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("789"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("6789"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("56789"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("456789"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("3456789"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("23456789"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("123456789"))));
    EXPECT_TRUE(str.ends_with(StdStringArg(STR("0123456789"))));

    EXPECT_FALSE(str.ends_with(StdStringArg(STR(" 0123456789"))));
    EXPECT_FALSE(str.ends_with(StdStringArg(STR("11"))));
    EXPECT_FALSE(str.ends_with(StdStringArg(STR("trash"))));

    // qx::basic_string
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR(""))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("9"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("89"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("789"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("6789"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("56789"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("456789"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("3456789"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("23456789"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("123456789"))));
    EXPECT_TRUE(str.ends_with(StringTypeTn(STR("0123456789"))));

    EXPECT_FALSE(str.ends_with(StringTypeTn(STR(" 0123456789"))));
    EXPECT_FALSE(str.ends_with(StringTypeTn(STR("11"))));
    EXPECT_FALSE(str.ends_with(StringTypeTn(STR("trash"))));
}

TYPED_TEST(TestQxString, starts_with)
{
    StringTypeTn str(STR("0123456789"));

    // char
    EXPECT_TRUE(str.starts_with(CH('0')));
    EXPECT_FALSE(str.starts_with(CH('7')));
    EXPECT_FALSE(str.starts_with(CH('2')));
    EXPECT_FALSE(str.starts_with(CH(';')));

    // const_pointer
    EXPECT_TRUE(str.starts_with(STR("")));
    EXPECT_TRUE(str.starts_with(STR("0")));
    EXPECT_TRUE(str.starts_with(STR("01")));
    EXPECT_TRUE(str.starts_with(STR("012")));
    EXPECT_TRUE(str.starts_with(STR("0123")));
    EXPECT_TRUE(str.starts_with(STR("01234")));
    EXPECT_TRUE(str.starts_with(STR("012345")));
    EXPECT_TRUE(str.starts_with(STR("0123456")));
    EXPECT_TRUE(str.starts_with(STR("01234567")));
    EXPECT_TRUE(str.starts_with(STR("012345678")));
    EXPECT_TRUE(str.starts_with(STR("0123456789")));

    EXPECT_FALSE(str.starts_with(STR(" 0123456789")));
    EXPECT_FALSE(str.starts_with(STR("11")));
    EXPECT_FALSE(str.starts_with(STR("trash")));

    // std::basic_string
    EXPECT_TRUE(str.starts_with(StdStringArg(STR(""))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("0"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("01"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("012"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("0123"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("01234"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("012345"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("0123456"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("01234567"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("012345678"))));
    EXPECT_TRUE(str.starts_with(StdStringArg(STR("0123456789"))));

    EXPECT_FALSE(str.starts_with(StdStringArg(STR(" 0123456789"))));
    EXPECT_FALSE(str.starts_with(StdStringArg(STR("11"))));
    EXPECT_FALSE(str.starts_with(StdStringArg(STR("trash"))));

    // qx::basic_string
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR(""))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("0"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("01"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("012"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("0123"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("01234"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("012345"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("0123456"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("01234567"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("012345678"))));
    EXPECT_TRUE(str.starts_with(StringTypeTn(STR("0123456789"))));

    EXPECT_FALSE(str.starts_with(StringTypeTn(STR(" 0123456789"))));
    EXPECT_FALSE(str.starts_with(StringTypeTn(STR("11"))));
    EXPECT_FALSE(str.starts_with(StringTypeTn(STR("trash"))));
}

TYPED_TEST(TestQxString, contains)
{
    StringTypeTn str(STR("for string for words and for searching"));


    EXPECT_TRUE(str.contains(STR("for")));
    EXPECT_TRUE(str.contains(StringTypeTn(STR("for"))));
    EXPECT_TRUE(str.contains(CH('f')));

    auto sStdStr1 = StdString(STR("for"));
    EXPECT_TRUE(str.contains(sStdStr1));
    EXPECT_TRUE(str.contains(sStdStr1.cbegin(), sStdStr1.cend()));


    EXPECT_FALSE(str.contains(STR("lel")));
    EXPECT_FALSE(str.contains(StringTypeTn(STR("lel"))));
    EXPECT_FALSE(str.contains(CH('l')));

    auto sStdStr2 = StdString(STR("lel"));
    EXPECT_FALSE(str.contains(sStdStr2));
    EXPECT_FALSE(str.contains(sStdStr2.cbegin(), sStdStr2.cend()));

}

TYPED_TEST(TestQxString, operator_stream_out)
{
    StringTypeTn::sstream_type  stream;
    StringTypeTn                in_string(STR("  0 one      two 3 .\t>>\n;;"));
    StdString                   out_string;
    stream << in_string;

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("0"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("one"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("two"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("3"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("."));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR(">>"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR(";;"));
}

TYPED_TEST(TestQxString, operator_stream_in)
{
    StringTypeTn::sstream_type  stream;
    StdString                   in_string(STR("  0 one      two 3 .\t>>\n;;"));
    StringTypeTn                out_string;
    stream << in_string;

    stream >> out_string; // to empty
    EXPECT_STREQ(out_string.data(), STR("0"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("one"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("two"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("3"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR("."));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR(">>"));

    stream >> out_string;
    EXPECT_STREQ(out_string.data(), STR(";;"));
}

TYPED_TEST(TestQxString, string_view)
{
    StringTypeTn qx_str = STR("qx_str");
    std::basic_string_view<ValueType, std::char_traits<ValueType>> view1(qx_str);
    std::basic_string_view<ValueType, std::char_traits<ValueType>> view2 = qx_str;
}

TYPED_TEST(TestQxString, small_string_optimization)
{
    constexpr auto pszSmallString1 = STR("small1");
    constexpr auto nSmallStrSize1 = qx::meta::strlen(pszSmallString1);

    constexpr auto pszSmallString2 = STR("small2");
    constexpr auto nSmallStrSize2 = qx::meta::strlen(pszSmallString2);

    constexpr auto pszBigString1 = STR("biiiiiiig string 1");
    constexpr auto nBigStrSize1 = qx::meta::strlen(pszBigString1);

    constexpr auto pszBigString2 = STR("biiiiiiig string 2 ");
    constexpr auto nBigStrSize2 = qx::meta::strlen(pszBigString2);

    // from small to small
    {
        StringTypeTn str = pszSmallString1;
        EXPECT_EQ(str.size(), nSmallStrSize1);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszSmallString1);

        str = pszSmallString2;
        EXPECT_EQ(str.size(), nSmallStrSize2);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszSmallString2);
    }

    // from small to big
    {
        StringTypeTn str = pszSmallString1;
        EXPECT_EQ(str.size(), nSmallStrSize1);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszSmallString1);

        str = pszBigString1;
        EXPECT_EQ(str.size(), nBigStrSize1);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszBigString1);
    }

    // from big to big
    {
        StringTypeTn str = pszBigString1;
        EXPECT_EQ(str.size(), nBigStrSize1);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszBigString1);

        str = pszBigString2;
        EXPECT_EQ(str.size(), nBigStrSize2);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszBigString2);
    }

    // from big to small
    {
        StringTypeTn str = pszBigString1;
        EXPECT_EQ(str.size(), nBigStrSize1);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszBigString1);

        str = pszSmallString1;
        EXPECT_EQ(str.size(), nSmallStrSize1);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszSmallString1);
    }

    // fit big to small
    {
        StringTypeTn str = pszBigString1;
        EXPECT_EQ(str.size(), nBigStrSize1);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszBigString1);

        str = pszSmallString1;
        EXPECT_EQ(str.size(), nSmallStrSize1);
        EXPECT_EQ(str.capacity() % TypeParam::small_string_size(), 0);
        EXPECT_STREQ(str.data(), pszSmallString1);

        str.shrink_to_fit();
        EXPECT_EQ(str.size(), nSmallStrSize1);
        EXPECT_EQ(str.capacity(), TypeParam::small_string_size());
        EXPECT_STREQ(str.data(), pszSmallString1);
    }
}

TYPED_TEST(TestQxString, replase)
{
    auto test_replace = [](auto type_find_var, auto type_replace_var)
    {
        using type_find = decltype(type_find_var);
        using type_replace = decltype(type_replace_var);

        StringTypeTn str;
        auto pszStartStr = STR("Let me help you with your baggage");

        str = pszStartStr;
        EXPECT_EQ(str.replace(type_find(STR("you")), type_replace(STR("12345"))), 17);
        EXPECT_STREQ(str.data(), STR("Let me help 12345 with your baggage"));
        EXPECT_EQ(str.size(), 35);

        str = pszStartStr;
        EXPECT_EQ(str.replace(type_find(STR("you")), type_replace(STR("123"))), 15);
        EXPECT_STREQ(str.data(), STR("Let me help 123 with your baggage"));
        EXPECT_EQ(str.size(), 33);

        str = pszStartStr;
        EXPECT_EQ(str.replace(type_find(STR("you")), type_replace(STR("12"))), 14);
        EXPECT_STREQ(str.data(), STR("Let me help 12 with your baggage"));
        EXPECT_EQ(str.size(), 32);

        str = pszStartStr;
        EXPECT_EQ(str.replace(type_find(STR("you")), type_replace(STR("12")), 16), 23);
        EXPECT_STREQ(str.data(), STR("Let me help you with 12r baggage"));
        EXPECT_EQ(str.size(), 32);

        str = pszStartStr;
        EXPECT_EQ(str.replace(type_find(STR("you")), type_replace(STR("12")), 26), StringType::npos);
        EXPECT_STREQ(str.data(), STR("Let me help you with your baggage"));
        EXPECT_EQ(str.size(), 33);

        str = pszStartStr;
        EXPECT_EQ(str.replace(type_find(STR("you")), type_replace(STR("12")), 0, 10), StringType::npos);
        EXPECT_STREQ(str.data(), STR("Let me help you with your baggage"));
        EXPECT_EQ(str.size(), 33);
    };

    test_replace(STR(""), STR(""));
    test_replace(STR(""), StringTypeTn());
    test_replace(STR(""), StdString());

    test_replace(StringTypeTn(), STR(""));
    test_replace(StringTypeTn(), StringTypeTn());
    test_replace(StringTypeTn(), StdString());

    test_replace(StdString(), STR(""));
    test_replace(StdString(), StringTypeTn());
    test_replace(StdString(), StdString());
}

TYPED_TEST(TestQxString, replase_all)
{
    auto test_replace_all = [](auto type_find_var, auto type_replace_var)
    {
        using type_find = decltype(type_find_var);
        using type_replace = decltype(type_replace_var);

        StringTypeTn str;
        auto pszStartStr = STR("aa bb cc aaa bbb ccc dddd");

        str = pszStartStr;
        EXPECT_EQ(str.replace_all(type_find(STR("aa")), type_replace(STR("bb"))), 2);
        EXPECT_STREQ(str.data(), STR("bb bb cc bba bbb ccc dddd"));
        EXPECT_EQ(str.size(), 25);

        str = pszStartStr;
        EXPECT_EQ(str.replace_all(type_find(STR("aa")), type_replace(STR("bb")), 4), 1);
        EXPECT_STREQ(str.data(), STR("aa bb cc bba bbb ccc dddd"));
        EXPECT_EQ(str.size(), 25);

        str = pszStartStr;
        EXPECT_EQ(str.replace_all(type_find(STR("fff")), type_replace(STR("bb"))), 0);
        EXPECT_STREQ(str.data(), STR("aa bb cc aaa bbb ccc dddd"));
        EXPECT_EQ(str.size(), 25);

        str = pszStartStr;
        EXPECT_EQ(str.replace_all(type_find(STR("aaa")), type_replace(STR("bbb"))), 1);
        EXPECT_STREQ(str.data(), STR("aa bb cc bbb bbb ccc dddd"));
        EXPECT_EQ(str.size(), 25);

        str = pszStartStr;
        EXPECT_EQ(str.replace_all(type_find(STR("aaa")), type_replace(STR("bbb"))), 1);
        EXPECT_STREQ(str.data(), STR("aa bb cc bbb bbb ccc dddd"));
        EXPECT_EQ(str.size(), 25);

        str = pszStartStr;
        EXPECT_EQ(str.replace_all(type_find(STR("a")), type_replace(STR("b"))), 5);
        EXPECT_STREQ(str.data(), STR("bb bb cc bbb bbb ccc dddd"));
        EXPECT_EQ(str.size(), 25);
    };

    test_replace_all(STR(""), STR(""));
    test_replace_all(STR(""), StringTypeTn());
    test_replace_all(STR(""), StdString());

    test_replace_all(StringTypeTn(), STR(""));
    test_replace_all(StringTypeTn(), StringTypeTn());
    test_replace_all(StringTypeTn(), StdString());

    test_replace_all(StdString(), STR(""));
    test_replace_all(StdString(), StringTypeTn());
    test_replace_all(StdString(), StdString());
}

TYPED_TEST(TestQxString, remove_prefix)
{
    auto pszStr = STR("12345");
    StringTypeTn str;

    str = pszStr;
    EXPECT_TRUE(str.remove_prefix(CH('1')));
    EXPECT_STREQ(str.data(), STR("2345"));
    EXPECT_EQ(str.size(), 4);

    str = pszStr;
    EXPECT_FALSE(str.remove_prefix(CH('2')));
    EXPECT_STREQ(str.data(), STR("12345"));
    EXPECT_EQ(str.size(), 5);

    auto test_remove_prefix = [&str, pszStr](auto type_var)
    {
        using type = decltype(type_var);

        str = pszStr;
        EXPECT_TRUE(str.remove_prefix(type(STR("12"))));
        EXPECT_STREQ(str.data(), STR("345"));
        EXPECT_EQ(str.size(), 3);

        str = pszStr;
        EXPECT_FALSE(str.remove_prefix(type(STR("21"))));
        EXPECT_STREQ(str.data(), STR("12345"));
        EXPECT_EQ(str.size(), 5);
    };

    test_remove_prefix(STR(""));
    test_remove_prefix(StringTypeTn());
    test_remove_prefix(StdString());
}

TYPED_TEST(TestQxString, remove_suffix)
{
    auto pszStr = STR("12345");
    StringTypeTn str;

    str = pszStr;
    EXPECT_TRUE(str.remove_suffix(CH('5')));
    EXPECT_STREQ(str.data(), STR("1234"));
    EXPECT_EQ(str.size(), 4);

    str = pszStr;
    EXPECT_FALSE(str.remove_suffix(CH('2')));
    EXPECT_STREQ(str.data(), STR("12345"));
    EXPECT_EQ(str.size(), 5);

    auto test_remove_suffix = [&str, pszStr](auto type_var)
    {
        using type = decltype(type_var);

        str = pszStr;
        EXPECT_TRUE(str.remove_suffix(type(STR("45"))));
        EXPECT_STREQ(str.data(), STR("123"));
        EXPECT_EQ(str.size(), 3);

        str = pszStr;
        EXPECT_FALSE(str.remove_suffix(type(STR("21"))));
        EXPECT_STREQ(str.data(), STR("12345"));
        EXPECT_EQ(str.size(), 5);
    };

    test_remove_suffix(STR(""));
    test_remove_suffix(StringTypeTn());
    test_remove_suffix(StdString());
}

TYPED_TEST(TestQxString, max_size)
{
    static_assert(StringType::max_size() == 18'446'744'073'709'551'613u);
}

TYPED_TEST(TestQxString, pop_back)
{
    StringTypeTn str;

    str = STR("12345");
    EXPECT_EQ(str.pop_back(), CH('5'));
    EXPECT_STREQ(str.data(), STR("1234"));

    str = STR("1");
    EXPECT_EQ(str.pop_back(), CH('1'));
    EXPECT_STREQ(str.data(), STR(""));
}

TYPED_TEST(TestQxString, pop_front)
{
    StringTypeTn str;

    str = STR("12345");
    EXPECT_EQ(str.pop_front(), CH('1'));
    EXPECT_STREQ(str.data(), STR("2345"));

    str = STR("1");
    EXPECT_EQ(str.pop_front(), CH('1'));
    EXPECT_STREQ(str.data(), STR(""));
}

TYPED_TEST(TestQxString, trim_left)
{
    StringTypeTn str;

    // empty
    str = STR(" \t\n\r 12345");
    EXPECT_EQ(str.trim_left(), 5);
    EXPECT_STREQ(str.data(), STR("12345"));
    EXPECT_EQ(str.size(), 5);

    str = STR(" \t\n\r");
    EXPECT_EQ(str.trim_left(), 4);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // char
    str = STR("1112345");
    EXPECT_EQ(str.trim_left(CH('1')), 3);
    EXPECT_STREQ(str.data(), STR("2345"));
    EXPECT_EQ(str.size(), 4);

    str = STR("    ");
    EXPECT_EQ(str.trim_left(CH(' ')), 4);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // const_pointer
    str = STR("1112345");
    EXPECT_EQ(str.trim_left(STR("12")), 4);
    EXPECT_STREQ(str.data(), STR("345"));
    EXPECT_EQ(str.size(), 3);

    str = STR("1112345");
    EXPECT_EQ(str.trim_left(STR("12"), 1), 3);
    EXPECT_STREQ(str.data(), STR("2345"));
    EXPECT_EQ(str.size(), 4);

    str = STR("    \t");
    EXPECT_EQ(str.trim_left(STR(" \t")), 5);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // qx::string
    str = STR("1112345");
    EXPECT_EQ(str.trim_left(StringTypeTn(STR("12"))), 4);
    EXPECT_STREQ(str.data(), STR("345"));
    EXPECT_EQ(str.size(), 3);

    // iterators
    StdString sStdTrim = STR("12");
    str = STR("1112345");
    EXPECT_EQ(str.trim_left(sStdTrim.cbegin(), sStdTrim.cend()), 4);
    EXPECT_STREQ(str.data(), STR("345"));
    EXPECT_EQ(str.size(), 3);

    // string
    str = STR("1112345");
    EXPECT_EQ(str.trim_left(sStdTrim), 4);
    EXPECT_STREQ(str.data(), STR("345"));
    EXPECT_EQ(str.size(), 3);

    str = STR("    \t");
    EXPECT_EQ(str.trim_left(StdString(STR(" \t"))), 5);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);
}

TYPED_TEST(TestQxString, trim_right)
{
    StringTypeTn str;

    // empty
    str = STR("12345 \t\n\r ");
    EXPECT_EQ(str.trim_right(), 5);
    EXPECT_STREQ(str.data(), STR("12345"));
    EXPECT_EQ(str.size(), 5);

    str = STR(" \t\n\r");
    EXPECT_EQ(str.trim_right(), 4);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // char
    str = STR("12345555");
    EXPECT_EQ(str.trim_right(CH('5')), 4);
    EXPECT_STREQ(str.data(), STR("1234"));
    EXPECT_EQ(str.size(), 4);

    str = STR("    ");
    EXPECT_EQ(str.trim_right(CH(' ')), 4);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // const_pointer
    str = STR("12345555");
    EXPECT_EQ(str.trim_right(STR("45")), 5);
    EXPECT_STREQ(str.data(), STR("123"));
    EXPECT_EQ(str.size(), 3);

    str = STR("12345555");
    EXPECT_EQ(str.trim_right(STR("54"), 1), 4);
    EXPECT_STREQ(str.data(), STR("1234"));
    EXPECT_EQ(str.size(), 4);

    str = STR("    \t");
    EXPECT_EQ(str.trim_right(STR(" \t")), 5);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // qx::string
    str = STR("12345555");
    EXPECT_EQ(str.trim_right(StringTypeTn(STR("54"))), 5);
    EXPECT_STREQ(str.data(), STR("123"));
    EXPECT_EQ(str.size(), 3);

    // iterators
    StdString sStdTrim = STR("45");
    str = STR("12345555");
    EXPECT_EQ(str.trim_right(sStdTrim.cbegin(), sStdTrim.cend()), 5);
    EXPECT_STREQ(str.data(), STR("123"));
    EXPECT_EQ(str.size(), 3);

    // string
    str = STR("12345555");
    EXPECT_EQ(str.trim_right(sStdTrim), 5);
    EXPECT_STREQ(str.data(), STR("123"));
    EXPECT_EQ(str.size(), 3);

    str = STR("    \t");
    EXPECT_EQ(str.trim_right(StdString(STR(" \t"))), 5);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);
}

TYPED_TEST(TestQxString, trim)
{
    StringTypeTn str;

    // empty
    str = STR("     12345 \t\n\r ");
    EXPECT_EQ(str.trim(), 10);
    EXPECT_STREQ(str.data(), STR("12345"));
    EXPECT_EQ(str.size(), 5);

    str = STR(" \t\n\r");
    EXPECT_EQ(str.trim(), 4);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // char
    str = STR("12345555");
    EXPECT_EQ(str.trim(CH('5')), 4);
    EXPECT_STREQ(str.data(), STR("1234"));
    EXPECT_EQ(str.size(), 4);

    str = STR("    ");
    EXPECT_EQ(str.trim(CH(' ')), 4);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // const_pointer
    str = STR("12345555");
    EXPECT_EQ(str.trim(STR("145")), 6);
    EXPECT_STREQ(str.data(), STR("23"));
    EXPECT_EQ(str.size(), 2);

    str = STR("12345555");
    EXPECT_EQ(str.trim(STR("54"), 1), 4);
    EXPECT_STREQ(str.data(), STR("1234"));
    EXPECT_EQ(str.size(), 4);

    str = STR("    \t");
    EXPECT_EQ(str.trim(STR(" \t")), 5);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);

    // qx::string
    str = STR("12345555");
    EXPECT_EQ(str.trim(StringTypeTn(STR("154"))), 6);
    EXPECT_STREQ(str.data(), STR("23"));
    EXPECT_EQ(str.size(), 2);

    // iterators
    StdString sStdTrim = STR("145");
    str = STR("12345555");
    EXPECT_EQ(str.trim(sStdTrim.cbegin(), sStdTrim.cend()), 6);
    EXPECT_STREQ(str.data(), STR("23"));
    EXPECT_EQ(str.size(), 2);

    // string
    str = STR("12345555");
    EXPECT_EQ(str.trim(sStdTrim), 6);
    EXPECT_STREQ(str.data(), STR("23"));
    EXPECT_EQ(str.size(), 2);

    str = STR("    \t");
    EXPECT_EQ(str.trim(StdString(STR(" \t"))), 5);
    EXPECT_STREQ(str.data(), STR(""));
    EXPECT_EQ(str.size(), 0);
}

TYPED_TEST(TestQxString, compare)
{
    StringTypeTn str(CH('5'));

    EXPECT_GT(str.compare(CH('4')), 0);
    EXPECT_EQ(str.compare(CH('5')), 0);
    EXPECT_LT(str.compare(CH('6')), 0);

    auto test_compare_type = [](auto type_var)
    {
        using type = decltype(type_var);

        StringTypeTn str(STR("555"));

        EXPECT_GT(str.compare(type(STR("444"))), 0);
        EXPECT_EQ(str.compare(type(STR("555"))), 0);
        EXPECT_LT(str.compare(type(STR("666"))), 0);
    };

    test_compare_type(STR(""));
    test_compare_type(StringTypeTn(STR("")));
    test_compare_type(StdString(STR("")));
}

TYPED_TEST(TestQxString, append)
{
    StringTypeTn str;

    str.append(CH('1'));
    EXPECT_STREQ(str.data(), STR("1"));
    EXPECT_EQ(str.size(), 1);

    str.append(CH('2'));
    EXPECT_STREQ(str.data(), STR("12"));
    EXPECT_EQ(str.size(), 2);

    str.append(CH('3'));
    EXPECT_STREQ(str.data(), STR("123"));
    EXPECT_EQ(str.size(), 3);

    auto test_append_type = [](auto type_var)
    {
        using type = decltype(type_var);

        StringTypeTn str;

        str.append(type(STR("12")));
        EXPECT_STREQ(str.data(), STR("12"));
        EXPECT_EQ(str.size(), 2);

        str.append(type(STR("34")));
        EXPECT_STREQ(str.data(), STR("1234"));
        EXPECT_EQ(str.size(), 4);

        str.append(type(STR("56")));
        EXPECT_STREQ(str.data(), STR("123456"));
        EXPECT_EQ(str.size(), 6);
    };

    test_append_type(STR(""));
    test_append_type(StringTypeTn(STR("")));
    test_append_type(StdString(STR("")));
}

TYPED_TEST(TestQxString, append_format)
{
    StringTypeTn str;

    str.append_printf(STR("%d"), 99);
    EXPECT_STREQ(str.data(), STR("99"));
    EXPECT_EQ(str.size(), 2);

    str.append_printf(STR(" %f"), 0.f);
    EXPECT_STREQ(str.data(), STR("99 0.000000"));
    EXPECT_EQ(str.size(), 11);

    str.append_printf(STR("%f"), 2.f);
    EXPECT_STREQ(str.data(), STR("99 0.0000002.000000"));
    EXPECT_EQ(str.size(), 19);
}

TYPED_TEST(TestQxString, copy)
{
    std::vector<ValueType> buffer(10);
    StringTypeTn str(STR("0123456789"));

    EXPECT_EQ(str.copy(buffer.data(), 2), 2);
    buffer[2] = CH('\0');
    EXPECT_STREQ(buffer.data(), STR("01"));

    EXPECT_EQ(str.copy(buffer.data(), 5, 7), 3);
    buffer[3] = CH('\0');
    EXPECT_STREQ(buffer.data(), STR("789"));

    EXPECT_EQ(str.copy(buffer.data(), 5, 11), 0);
    EXPECT_STREQ(buffer.data(), STR("789"));

    EXPECT_EQ(str.copy(buffer.data(), 0, 5), 0);
    EXPECT_STREQ(buffer.data(), STR("789"));

    EXPECT_EQ(str.copy(nullptr, 2, 5), 0);
}

TYPED_TEST(TestQxString, swap)
{
    StringTypeTn str1(STR("str1"));
    StringTypeTn str2(STR("str2"));

    str1.swap(str2);
    EXPECT_STREQ(str1.data(), STR("str2"));
    EXPECT_STREQ(str2.data(), STR("str1"));

    std::swap(str1, str2);
    EXPECT_STREQ(str1.data(), STR("str1"));
    EXPECT_STREQ(str2.data(), STR("str2"));
}

TYPED_TEST(TestQxString, rfind)
{
    StringTypeTn str(STR("for string for words and for searching"));

    EXPECT_EQ(str.rfind(STR("for")), 25);
    EXPECT_EQ(str.rfind(STR("for"), 15), 11);
    EXPECT_EQ(str.rfind(STR("for"), 29, StringType::npos, 20), 25);
    EXPECT_EQ(str.rfind(STR("for"), 0), 0);
    EXPECT_EQ(str.rfind(STR("kek")), StringType::npos);

    auto test = [str](auto... toSearch)
    {
        EXPECT_EQ(str.rfind(toSearch...), 25);
        EXPECT_EQ(str.rfind(toSearch..., 15), 11);
        EXPECT_EQ(str.rfind(toSearch..., 29, 20), 25);
        EXPECT_EQ(str.rfind(toSearch..., 0), 0);
        EXPECT_EQ(str.rfind(STR("kek")), StringType::npos);
    };

    test(StringTypeTn(STR("for")));
    test(CH('f'));

    auto sStdStr = StdString(STR("for"));
    test(sStdStr);
    test(sStdStr.cbegin(), sStdStr.cend());
}


#endif
