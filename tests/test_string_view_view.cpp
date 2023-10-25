/**

    @file      test_string_view_view.cpp
    @author    Khrapov
    @date      24.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_string_view_view.cpp

#include <qx/containers/string/string_utils.h>
#include <qx/containers/string/string_view_view.h>

#include <array>
#include <span>

template<class string_traits_t>
class test_string_view_view : public ::testing::Test
{
};

using Implementations = ::testing::Types<QX_ALL_CHAR_TYPES>;

TYPED_TEST_SUITE(test_string_view_view, Implementations);

template<class char_t>
void TestPart(
    qx::basic_string_view<char_t>            svFull,
    char_t                                   chDelimiter,
    qx::flags<qx::delimiter_inclusion_flags> eDelimiterInclusionFlags,
    qx::basic_string_view<char_t>            svPart,
    qx::basic_string_view<char_t>            svExpectedPart)
{
    EXPECT_TRUE(
        !eDelimiterInclusionFlags.contains(qx::delimiter_inclusion_flags::begin) || svPart.starts_with(chDelimiter)
        || svFull.starts_with(svPart));
    EXPECT_TRUE(
        !eDelimiterInclusionFlags.contains(qx::delimiter_inclusion_flags::end) || svPart.ends_with(chDelimiter)
        || svFull.ends_with(svPart));

    if (eDelimiterInclusionFlags.contains(qx::delimiter_inclusion_flags::begin) && svPart.starts_with(chDelimiter))
        svPart.remove_prefix(1);
    if (eDelimiterInclusionFlags.contains(qx::delimiter_inclusion_flags::end) && svPart.ends_with(chDelimiter))
        svPart.remove_suffix(1);
    EXPECT_EQ(svPart, svExpectedPart);
}

template<class char_t>
void TestIterator(
    qx::basic_string_view<char_t>                  svFull,
    char_t                                         chDelimiter,
    qx::flags<qx::delimiter_inclusion_flags>       eDelimiterInclusionFlags,
    std::span<const qx::basic_string_view<char_t>> parts)
{
    size_t i = 0;
    for (auto it = qx::string_view_iterator<char_t>::begin(svFull, chDelimiter, eDelimiterInclusionFlags);
         it != qx::string_view_iterator<char_t>::end();
         ++it)
    {
        TestPart(svFull, chDelimiter, eDelimiterInclusionFlags, *it, parts[i]);
        ++i;
    }
}

template<class char_t>
void TestView(
    qx::basic_string_view<char_t>                  svFull,
    char_t                                         chDelimiter,
    qx::flags<qx::delimiter_inclusion_flags>       eDelimiterInclusionFlags,
    std::span<const qx::basic_string_view<char_t>> parts)
{
    size_t i = 0;
    for (qx::basic_string_view<char_t> svPart : qx::string_view_view(svFull, chDelimiter, eDelimiterInclusionFlags))
    {
        TestPart(svFull, chDelimiter, eDelimiterInclusionFlags, svPart, parts[i]);
        ++i;
    }
}

template<class char_t>
void TestCases(qx::basic_string_view<char_t> svFull, char_t chDelimiter, std::span<qx::basic_string_view<char_t>> parts)
{
    TestIterator<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::none, parts);
    TestIterator<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::begin, parts);
    TestIterator<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::end, parts);
    TestIterator<char_t>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end,
        parts);

    TestView<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::none, parts);
    TestView<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::begin, parts);
    TestView<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::end, parts);
    TestView<char_t>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end,
        parts);
}

TYPED_TEST(test_string_view_view, main)
{
    qx::basic_string_view<TypeParam> svFull0     = QX_STR_PREFIX(TypeParam, "/a/bb/ccc/dddd/");
    qx::basic_string_view<TypeParam> svFull1     = QX_STR_PREFIX(TypeParam, "a/bb/ccc/dddd/");
    qx::basic_string_view<TypeParam> svFull2     = QX_STR_PREFIX(TypeParam, "/a/bb/ccc/dddd");
    qx::basic_string_view<TypeParam> svFull3     = QX_STR_PREFIX(TypeParam, "a/bb/ccc/dddd");
    TypeParam                        chDelimiter = QX_CHAR_PREFIX(TypeParam, '/');

    std::array<qx::basic_string_view<TypeParam>, 4> parts { QX_STR_PREFIX(TypeParam, "a"),
                                                            QX_STR_PREFIX(TypeParam, "bb"),
                                                            QX_STR_PREFIX(TypeParam, "ccc"),
                                                            QX_STR_PREFIX(TypeParam, "dddd") };

    TestCases<TypeParam>(svFull0, chDelimiter, parts);
    TestCases<TypeParam>(svFull1, chDelimiter, parts);
    TestCases<TypeParam>(svFull2, chDelimiter, parts);
    TestCases<TypeParam>(svFull3, chDelimiter, parts);
}
