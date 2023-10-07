/**

    @file      test_string_hash.cpp
    @author    Khrapov
    @date      17.04.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_string_hash.cpp

#include <qx/containers/string/string.h>
#include <qx/containers/string/string_hash.h>
#include <qx/macros/static_assert.h>
#include <string_test_helpers.h>

#include <algorithm>

QX_PUSH_SUPPRESS_MSVC_WARNINGS(5233);

template<class string_traits_t>
class TestStringHashTyped : public ::testing::Test
{
};

using Implementations = ::testing::Types<qx::string_traits::traits<char>, qx::string_traits::traits<wchar_t>>;

TYPED_TEST_SUITE(TestStringHashTyped, Implementations);

TYPED_TEST(TestStringHashTyped, class_size)
{
    QX_STATIC_ASSERT_EQ(sizeof(StringHashType), sizeof(size_t));
}

TYPED_TEST(TestStringHashTyped, hashes_equality)
{
    const StringTypeTn str = STR("Hello world");

    StringHashType hash0(str.data());
    StringHashType hash1(str.data(), str.size());
    StringHashType hash2(str);

    EXPECT_EQ(hash0, hash1);
    EXPECT_EQ(hash1, hash2);
}

TYPED_TEST(TestStringHashTyped, hashes_inequality)
{
    constexpr std::array hashes { StringHashType(STR("")),
                                  StringHashType(STR("1")),
                                  StringHashType(STR(" ")),
                                  StringHashType(STR("Hello world")),
                                  StringHashType(STR("random string")),
                                  StringHashType(STR("KEKW")) };

    QX_PUSH_SUPPRESS_MSVC_WARNINGS(5258);
    const bool bAllDifferent = std::all_of(
        hashes.cbegin() + 1,
        hashes.cend(),
        [&hashes](const auto& hash)
        {
            return hash != hashes[0];
        });
    QX_POP_SUPPRESS_WARNINGS();

    EXPECT_TRUE(bAllDifferent);
}

TEST(TestStringHash, operator_)
{
    using namespace qx::literals;

    {
        qx::string_hash hash0(QX_TEXT("Hello world"));
        qx::string_hash hash1 = QX_STRING_HASH("Hello world");
        EXPECT_EQ(hash0, hash1);
    }

    {
        qx::cstring_hash hash0("Hello world");
        qx::cstring_hash hash1 = "Hello world"_sh;
        EXPECT_EQ(hash0, hash1);
    }

    {
        qx::wstring_hash hash0(L"Hello world");
        qx::wstring_hash hash1 = L"Hello world"_sh;
        EXPECT_EQ(hash0, hash1);
    }
}

QX_POP_SUPPRESS_WARNINGS();
