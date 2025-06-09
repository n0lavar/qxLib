/**

    @file      test_string_view_iterator.cpp
    @author    Khrapov
    @date      24.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_string_view_iterator.cpp

#include <qx/containers/string/string_utils.h>
#include <qx/containers/string/string_view_view.h>

#include <array>
#include <span>

template<class string_traits_t>
class test_string_view_iterator : public ::testing::Test
{
};

using implementations_type = ::testing::Types<QX_ALL_CHAR_TYPES>;

TYPED_TEST_SUITE(test_string_view_iterator, implementations_type);

template<class char_t>
static void test_part(
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

template<class char_t, bool bForwardIterator>
static void test_iterator_bool(
    qx::basic_string_view<char_t>                  svFull,
    char_t                                         chDelimiter,
    qx::flags<qx::delimiter_inclusion_flags>       eDelimiterInclusionFlags,
    std::span<const qx::basic_string_view<char_t>> parts)
{
    const size_t nStartI = bForwardIterator ? 0 : parts.size() - 1;
    size_t       i       = nStartI;
    for (auto it =
             qx::base_string_view_iterator<char_t, bForwardIterator>(svFull, chDelimiter, eDelimiterInclusionFlags);
         it;
         ++it)
    {
        qx::basic_string_view<char_t> svPart = *it;
        test_part(svFull, chDelimiter, eDelimiterInclusionFlags, svPart, parts[i]);
        i = bForwardIterator ? i + 1 : i - 1;
    }

    EXPECT_TRUE(i != nStartI || svFull.empty());
}

template<class char_t, bool bForwardIterator>
static void test_iterator_begin_end(
    qx::basic_string_view<char_t>                  svFull,
    char_t                                         chDelimiter,
    qx::flags<qx::delimiter_inclusion_flags>       eDelimiterInclusionFlags,
    std::span<const qx::basic_string_view<char_t>> parts)
{
    const size_t nStartI = bForwardIterator ? 0 : parts.size() - 1;
    size_t       i       = nStartI;

    auto itBegin =
        qx::base_string_view_iterator<char_t, bForwardIterator>::begin(svFull, chDelimiter, eDelimiterInclusionFlags);
    auto itEnd =
        qx::base_string_view_iterator<char_t, bForwardIterator>::end(svFull, chDelimiter, eDelimiterInclusionFlags);
    for (auto it = itBegin; it != itEnd; ++it)
    {
        qx::basic_string_view<char_t> svPart = *it;
        test_part(svFull, chDelimiter, eDelimiterInclusionFlags, svPart, parts[i]);
        i = bForwardIterator ? i + 1 : i - 1;
    }

    EXPECT_TRUE(i != nStartI || svFull.empty());
}

template<class char_t>
static void test_view(
    qx::basic_string_view<char_t>                  svFull,
    char_t                                         chDelimiter,
    qx::flags<qx::delimiter_inclusion_flags>       eDelimiterInclusionFlags,
    std::span<const qx::basic_string_view<char_t>> parts)
{
    size_t i = 0;
    for (qx::basic_string_view<char_t> svPart : qx::string_view_view(svFull, chDelimiter, eDelimiterInclusionFlags))
    {
        test_part(svFull, chDelimiter, eDelimiterInclusionFlags, svPart, parts[i]);
        ++i;
    }

    EXPECT_TRUE(i != 0 || svFull.empty());
}

template<class char_t, bool bForwardIterator>
static void test_inclusion_flags(
    qx::basic_string_view<char_t>                  svFull,
    char_t                                         chDelimiter,
    std::span<const qx::basic_string_view<char_t>> expectedParts)
{
    test_iterator_bool<char_t, bForwardIterator>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::none,
        expectedParts);
    test_iterator_bool<char_t, bForwardIterator>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::begin,
        expectedParts);
    test_iterator_bool<char_t, bForwardIterator>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::end,
        expectedParts);
    test_iterator_bool<char_t, bForwardIterator>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end,
        expectedParts);

    test_iterator_begin_end<char_t, bForwardIterator>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::none,
        expectedParts);
    test_iterator_begin_end<char_t, bForwardIterator>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::begin,
        expectedParts);
    test_iterator_begin_end<char_t, bForwardIterator>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::end,
        expectedParts);
    test_iterator_begin_end<char_t, bForwardIterator>(
        svFull,
        chDelimiter,
        qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end,
        expectedParts);
}

template<class char_t>
static void test_common(
    std::span<const qx::basic_string_view<char_t>> fullStrings,
    char_t                                         chDelimiter,
    std::span<const qx::basic_string_view<char_t>> expectedParts)
{
    for (qx::basic_string_view<char_t> svFull : fullStrings)
    {
        test_inclusion_flags<char_t, true>(svFull, chDelimiter, expectedParts);
        test_inclusion_flags<char_t, false>(svFull, chDelimiter, expectedParts);

        test_view<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::none, expectedParts);
        test_view<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::begin, expectedParts);
        test_view<char_t>(svFull, chDelimiter, qx::delimiter_inclusion_flags::end, expectedParts);
        test_view<char_t>(
            svFull,
            chDelimiter,
            qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end,
            expectedParts);
    }
}

TYPED_TEST(test_string_view_iterator, many_parts)
{
    test_common<TypeParam>(
        std::array<qx::basic_string_view<TypeParam>, 4> { QX_STR_PREFIX(TypeParam, "/a/bb/ccc/dddd/"),
                                                          QX_STR_PREFIX(TypeParam, "a/bb/ccc/dddd/"),
                                                          QX_STR_PREFIX(TypeParam, "/a/bb/ccc/dddd"),
                                                          QX_STR_PREFIX(TypeParam, "a/bb/ccc/dddd") },
        QX_CHAR_PREFIX(TypeParam, '/'),
        std::array<qx::basic_string_view<TypeParam>, 4> { QX_STR_PREFIX(TypeParam, "a"),
                                                          QX_STR_PREFIX(TypeParam, "bb"),
                                                          QX_STR_PREFIX(TypeParam, "ccc"),
                                                          QX_STR_PREFIX(TypeParam, "dddd") });
}

TYPED_TEST(test_string_view_iterator, one_part)
{
    test_common<TypeParam>(
        std::array<qx::basic_string_view<TypeParam>, 4> { QX_STR_PREFIX(TypeParam, "/a"),
                                                          QX_STR_PREFIX(TypeParam, "a/"),
                                                          QX_STR_PREFIX(TypeParam, "/a/"),
                                                          QX_STR_PREFIX(TypeParam, "a") },
        QX_CHAR_PREFIX(TypeParam, '/'),
        std::array<qx::basic_string_view<TypeParam>, 1> { QX_STR_PREFIX(TypeParam, "a") });
}

TYPED_TEST(test_string_view_iterator, zero_parts)
{
    test_common<TypeParam>(
        std::array<qx::basic_string_view<TypeParam>, 1> { QX_STR_PREFIX(TypeParam, "") },
        QX_CHAR_PREFIX(TypeParam, '/'),
        std::array<qx::basic_string_view<TypeParam>, 0> {});
}

TYPED_TEST(test_string_view_iterator, random_directions)
{
    qx::basic_string_view<TypeParam> svValue     = QX_STR_PREFIX(TypeParam, "/a/bb/ccc/dddd/");
    const TypeParam                  chDelimiter = QX_CHAR_PREFIX(TypeParam, '/');

    auto it = qx::string_view_iterator(svValue, chDelimiter);
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "a"));
    ++it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "bb"));
    ++it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "ccc"));
    ++it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "dddd"));
    ++it;
    EXPECT_FALSE(it);
    --it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "dddd"));
    --it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "ccc"));
    --it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "bb"));
    --it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "a"));
    --it;
    EXPECT_FALSE(it);
    ++it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "a"));
    ++it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "bb"));
    --it;
    EXPECT_EQ(*it, QX_STR_PREFIX(TypeParam, "a"));
    --it;
    EXPECT_FALSE(it);
}

#if 0
TYPED_TEST(test_string_view_iterator, print)
{
    if constexpr (std::is_same_v<TypeParam, wchar_t>)
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



        auto iterate_forward =
            [chDelimiter](qx::basic_string_view<TypeParam> svFull, qx::flags<qx::delimiter_inclusion_flags> eFlags)
        {
            std::wcout << L"    " << svFull << std::endl;
            for (auto it = qx::string_view_iterator(svFull, chDelimiter, eFlags); it; ++it)
            {
                std::wcout << L"        " << *it << std::endl;
            }
            std::wcout << std::endl;
        };

        auto iterate_reverse =
            [chDelimiter](qx::basic_string_view<TypeParam> svFull, qx::flags<qx::delimiter_inclusion_flags> eFlags)
        {
            std::wcout << L"    " << svFull << std::endl;
            for (auto it = qx::reverse_string_view_iterator(svFull, chDelimiter, eFlags); it; ++it)
            {
                std::wcout << L"        " << *it << std::endl;
            }
            std::wcout << std::endl;
        };



        std::wcout << L"iterate_forward, none" << std::endl;
        iterate_forward(svFull0, qx::delimiter_inclusion_flags::none);
        iterate_forward(svFull1, qx::delimiter_inclusion_flags::none);
        iterate_forward(svFull2, qx::delimiter_inclusion_flags::none);
        iterate_forward(svFull3, qx::delimiter_inclusion_flags::none);

        std::wcout << L"iterate_forward, begin" << std::endl;
        iterate_forward(svFull0, qx::delimiter_inclusion_flags::begin);
        iterate_forward(svFull1, qx::delimiter_inclusion_flags::begin);
        iterate_forward(svFull2, qx::delimiter_inclusion_flags::begin);
        iterate_forward(svFull3, qx::delimiter_inclusion_flags::begin);

        std::wcout << L"iterate_forward, end" << std::endl;
        iterate_forward(svFull0, qx::delimiter_inclusion_flags::end);
        iterate_forward(svFull1, qx::delimiter_inclusion_flags::end);
        iterate_forward(svFull2, qx::delimiter_inclusion_flags::end);
        iterate_forward(svFull3, qx::delimiter_inclusion_flags::end);

        std::wcout << L"iterate_forward, begin | end" << std::endl;
        iterate_forward(svFull0, qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end);
        iterate_forward(svFull1, qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end);
        iterate_forward(svFull2, qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end);
        iterate_forward(svFull3, qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end);



        std::wcout << L"iterate_reverse, none" << std::endl;
        iterate_reverse(svFull0, qx::delimiter_inclusion_flags::none);
        iterate_reverse(svFull1, qx::delimiter_inclusion_flags::none);
        iterate_reverse(svFull2, qx::delimiter_inclusion_flags::none);
        iterate_reverse(svFull3, qx::delimiter_inclusion_flags::none);

        std::wcout << L"iterate_reverse, begin" << std::endl;
        iterate_reverse(svFull0, qx::delimiter_inclusion_flags::begin);
        iterate_reverse(svFull1, qx::delimiter_inclusion_flags::begin);
        iterate_reverse(svFull2, qx::delimiter_inclusion_flags::begin);
        iterate_reverse(svFull3, qx::delimiter_inclusion_flags::begin);

        std::wcout << L"iterate_reverse, end" << std::endl;
        iterate_reverse(svFull0, qx::delimiter_inclusion_flags::end);
        iterate_reverse(svFull1, qx::delimiter_inclusion_flags::end);
        iterate_reverse(svFull2, qx::delimiter_inclusion_flags::end);
        iterate_reverse(svFull3, qx::delimiter_inclusion_flags::end);

        std::wcout << L"iterate_reverse, begin | end" << std::endl;
        iterate_reverse(svFull0, qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end);
        iterate_reverse(svFull1, qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end);
        iterate_reverse(svFull2, qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end);
        iterate_reverse(svFull3, qx::delimiter_inclusion_flags::begin | qx::delimiter_inclusion_flags::end);
    }
}
#endif
