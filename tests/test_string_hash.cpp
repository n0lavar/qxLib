/**

    @file      test_string_hash.cpp
    @author    Khrapov
    @date      17.04.2022
    @copyright � Nick Khrapov, 2022. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_string_hash.cpp

#if QX_TEST_STRING_HASH

#include <qx/containers/string/string.h>
#include <qx/containers/string/string_hash.h>
#include <string_test_helpers.h>

template<typename StringTraits>
class TestStringHashTyped : public ::testing::Test
{
};

using Implementations = ::testing::Types<
    qx::char_traits<char>,
    qx::char_traits<wchar_t>,
    qx::fast_hash_string_traits<char>,
    qx::fast_hash_string_traits<wchar_t>>;

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

    const bool bAllDifferent = std::all_of(
        hashes.cbegin() + 1,
        hashes.cend(),
        [](const auto& hash)
        {
            return hash != hashes[0];
        });

    EXPECT_TRUE(bAllDifferent);
}

TEST(TestStringHash, operator_)
{
    using namespace qx::literals;

    {
        qx::fast_string_hash hash0("Hello world");
        qx::fast_string_hash hash1 = "Hello world"_sh;
        EXPECT_EQ(hash0, hash1);
    }

    {
        qx::fast_wstring_hash hash0(L"Hello world");
        qx::fast_wstring_hash hash1 = L"Hello world"_sh;
        EXPECT_EQ(hash0, hash1);
    }
}

#endif