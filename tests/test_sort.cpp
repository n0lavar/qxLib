//==============================================================================
//
//!\file                        test_sort.cpp
//
//!\brief       Tests for sort algorithms
//!\details     ~
//
//!\author      Khrapov
//!\date        7.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_sort.cpp

#if QX_TEST_SORT

#include <array>
#include <limits>
#include <random>
#include <qx/alg/sort.h>


#undef INT_MAX
#undef INT_MIN
constexpr int INT_MAX = std::numeric_limits<int>::max();
constexpr int INT_MIN = std::numeric_limits<int>::min();

//==============================================================================
//
//!\class   TestTraits<Compare, minElement, maxElement, arraySize>
//
//!\brief   Test traits for TestQxSort
//!\details ~
//
//!\author  Khrapov
//!\date    9.03.2020
//
//==============================================================================
template <typename Compare, int64_t minElement, int64_t maxElement, size_t arraySize>
struct TestTraits
{
    static constexpr Compare compare()     { return Compare();  }
    static constexpr int64_t min_element() { return minElement; }
    static constexpr int64_t max_element() { return maxElement; }
    static constexpr size_t  array_size()  { return arraySize;  }
};

//==============================================================================
//
//!\class                     TestQxSort<Traits>
//
//!\brief   Test class for sorting
//!\details ~
//
//!\author  Khrapov
//!\date    9.03.2020
//
//==============================================================================
template <typename Traits>
class TestQxSort : public ::testing::Test
{
protected:

    /* init protected members here */
    TestQxSort()
    {
        std::default_random_engine generator(static_cast<unsigned>(time(0)));
        std::uniform_int_distribution<int64_t> fillDistribution(Traits::min_element(), Traits::max_element());

        for (size_t i = 0; i < m_Unsorted.size(); i++)
            m_Unsorted[i] = fillDistribution(generator);

        // assume std::sort always right
        m_SortedStd = m_Unsorted;
        std::sort(m_SortedStd.begin(), m_SortedStd.end(), Traits::compare());
    }

    /* called before every test */
    void SetUp()
    {
        m_SortedTest = m_Unsorted;
    }

    /* called after every test */
    void TearDown()
    {
        ASSERT_EQ(m_SortedStd, m_SortedTest);
    }

    std::array<int64_t, Traits::array_size()> m_Unsorted   { };
    std::array<int64_t, Traits::array_size()> m_SortedStd  { };
    std::array<int64_t, Traits::array_size()> m_SortedTest { };
};

//---------------------------- small signed range ----------------------------

using TestQxSort_less_0_elements_small_signed_range            = TestTraits<std::less<>,    -100, 100, 0>;
using TestQxSort_greater_0_elements_small_signed_range         = TestTraits<std::greater<>, -100, 100, 0>;
using TestQxSort_less_1_elements_small_signed_range            = TestTraits<std::less<>,    -100, 100, 1>;
using TestQxSort_greater_1_elements_small_signed_range         = TestTraits<std::greater<>, -100, 100, 1>;
using TestQxSort_less_10_elements_small_signed_range           = TestTraits<std::less<>,    -100, 100, 10>;
using TestQxSort_greater_10_elements_small_signed_range        = TestTraits<std::greater<>, -100, 100, 10>;
using TestQxSort_less_1000_elements_small_signed_range         = TestTraits<std::less<>,    -100, 100, 1000>;
using TestQxSort_greater_1000_elements_small_signed_range      = TestTraits<std::greater<>, -100, 100, 1000>;
using TestQxSort_less_100000_elements_small_signed_range       = TestTraits<std::less<>,    -100, 100, 100000>;
using TestQxSort_greater_100000_elements_small_signed_range    = TestTraits<std::greater<>, -100, 100, 100000>;

//---------------------------- medium signed range ---------------------------

using TestQxSort_less_0_elements_medium_signed_range           = TestTraits<std::less<>,    -100000, 100000, 0>;
using TestQxSort_greater_0_elements_medium_signed_range        = TestTraits<std::greater<>, -100000, 100000, 0>;
using TestQxSort_less_1_medium_signed_range                    = TestTraits<std::less<>,    -100000, 100000, 1>;
using TestQxSort_greater_1_elements_medium_signed_range        = TestTraits<std::greater<>, -100000, 100000, 1>;
using TestQxSort_less_10_elements_medium_signed_range          = TestTraits<std::less<>,    -100000, 100000, 10>;
using TestQxSort_greater_10_elements_medium_signed_range       = TestTraits<std::greater<>, -100000, 100000, 10>;
using TestQxSort_less_1000_elements_medium_signed_range        = TestTraits<std::less<>,    -100000, 100000, 1000>;
using TestQxSort_greater_1000_elements_medium_signed_range     = TestTraits<std::greater<>, -100000, 100000, 1000>;
using TestQxSort_less_100000_elements_medium_signed_range      = TestTraits<std::less<>,    -100000, 100000, 100000>;
using TestQxSort_greater_100000_elements_medium_signed_range   = TestTraits<std::greater<>, -100000, 100000, 100000>;

//---------------------------- big signed range ---------------------------

using TestQxSort_less_0_elements_big_signed_range              = TestTraits<std::less<>,    INT_MIN, INT_MAX, 0>;
using TestQxSort_greater_0_elements_big_signed_range           = TestTraits<std::greater<>, INT_MIN, INT_MAX, 0>;
using TestQxSort_less_1_elements_big_signed_range              = TestTraits<std::less<>,    INT_MIN, INT_MAX, 1>;
using TestQxSort_greater_1_elements_big_signed_range           = TestTraits<std::greater<>, INT_MIN, INT_MAX, 1>;
using TestQxSort_less_10_elements_big_signed_range             = TestTraits<std::less<>,    INT_MIN, INT_MAX, 10>;
using TestQxSort_greater_10_elements_big_signed_range          = TestTraits<std::greater<>, INT_MIN, INT_MAX, 10>;
using TestQxSort_less_1000_elements_big_signed_range           = TestTraits<std::less<>,    INT_MIN, INT_MAX, 1000>;
using TestQxSort_greater_1000_elements_big_signed_range        = TestTraits<std::greater<>, INT_MIN, INT_MAX, 1000>;
using TestQxSort_less_100000_elements_big_signed_range         = TestTraits<std::less<>,    INT_MIN, INT_MAX, 100000>;
using TestQxSort_greater_100000_elements_big_signed_range      = TestTraits<std::greater<>, INT_MIN, INT_MAX, 100000>;

//---------------------------- small unsigned range ----------------------------

using TestQxSort_less_0_elements_small_unsigned_range          = TestTraits<std::less<>,    0, 100, 0>;
using TestQxSort_greater_0_elements_small_unsigned_range       = TestTraits<std::greater<>, 0, 100, 0>;
using TestQxSort_less_1_elements_small_unsigned_range          = TestTraits<std::less<>,    0, 100, 1>;
using TestQxSort_greater_1_elements_small_unsigned_range       = TestTraits<std::greater<>, 0, 100, 1>;
using TestQxSort_less_10_elements_small_unsigned_range         = TestTraits<std::less<>,    0, 100, 10>;
using TestQxSort_greater_10_elements_small_unsigned_range      = TestTraits<std::greater<>, 0, 100, 10>;
using TestQxSort_less_1000_elements_small_unsigned_range       = TestTraits<std::less<>,    0, 100, 1000>;
using TestQxSort_greater_1000_elements_small_unsigned_range    = TestTraits<std::greater<>, 0, 100, 1000>;
using TestQxSort_less_100000_elements_small_unsigned_range     = TestTraits<std::less<>,    0, 100, 100000>;
using TestQxSort_greater_100000_elements_small_unsigned_range  = TestTraits<std::greater<>, 0, 100, 100000>;

//---------------------------- medium unsigned range ---------------------------

using TestQxSort_less_0_elements_medium_unsigned_range         = TestTraits<std::less<>,    0, 100000, 0>;
using TestQxSort_greater_0_elements_medium_unsigned_range      = TestTraits<std::greater<>, 0, 100000, 0>;
using TestQxSort_less_1_elements_medium_unsigned_range         = TestTraits<std::less<>,    0, 100000, 1>;
using TestQxSort_greater_1_elements_medium_unsigned_range      = TestTraits<std::greater<>, 0, 100000, 1>;
using TestQxSort_less_10_elements_medium_unsigned_range        = TestTraits<std::less<>,    0, 100000, 10>;
using TestQxSort_greater_10_elements_medium_unsigned_range     = TestTraits<std::greater<>, 0, 100000, 10>;
using TestQxSort_less_1000_elements_medium_unsigned_range      = TestTraits<std::less<>,    0, 100000, 1000>;
using TestQxSort_greater_1000_elements_medium_unsigned_range   = TestTraits<std::greater<>, 0, 100000, 1000>;
using TestQxSort_less_100000_elements_medium_unsigned_range    = TestTraits<std::less<>,    0, 100000, 100000>;
using TestQxSort_greater_100000_elements_medium_unsigned_range = TestTraits<std::greater<>, 0, 100000, 100000>;

//---------------------------- big unsigned range ---------------------------

using TestQxSort_less_0_elements_big_unsigned_range            = TestTraits<std::less<>,    0, INT_MAX, 0>;
using TestQxSort_greater_0_elements_big_unsigned_range         = TestTraits<std::greater<>, 0, INT_MAX, 0>;
using TestQxSort_less_1_elements_big_unsigned_range            = TestTraits<std::less<>,    0, INT_MAX, 1>;
using TestQxSort_greater_1_elements_big_unsigned_range         = TestTraits<std::greater<>, 0, INT_MAX, 1>;
using TestQxSort_less_10_elements_big_unsigned_range           = TestTraits<std::less<>,    0, INT_MAX, 10>;
using TestQxSort_greater_10_elements_big_unsigned_range        = TestTraits<std::greater<>, 0, INT_MAX, 10>;
using TestQxSort_less_1000_elements_big_unsigned_range         = TestTraits<std::less<>,    0, INT_MAX, 1000>;
using TestQxSort_greater_1000_elements_big_unsigned_range      = TestTraits<std::greater<>, 0, INT_MAX, 1000>;
using TestQxSort_less_100000_elements_big_unsigned_range       = TestTraits<std::less<>,    0, INT_MAX, 100000>;
using TestQxSort_greater_100000_elements_big_unsigned_range    = TestTraits<std::greater<>, 0, INT_MAX, 100000>;


using Implementations = ::testing::Types
<
    TestQxSort_less_0_elements_small_signed_range,
    TestQxSort_greater_0_elements_small_signed_range,
    TestQxSort_less_1_elements_small_signed_range,
    TestQxSort_greater_1_elements_small_signed_range,
    TestQxSort_less_10_elements_small_signed_range,
    TestQxSort_greater_10_elements_small_signed_range,
    TestQxSort_less_1000_elements_small_signed_range,
    TestQxSort_greater_1000_elements_small_signed_range,
    //TestQxSort_less_100000_elements_small_signed_range,
    //TestQxSort_greater_100000_elements_small_signed_range,

    TestQxSort_less_0_elements_medium_signed_range,
    TestQxSort_greater_0_elements_medium_signed_range,
    TestQxSort_less_1_medium_signed_range,
    TestQxSort_greater_1_elements_medium_signed_range,
    TestQxSort_less_10_elements_medium_signed_range,
    TestQxSort_greater_10_elements_medium_signed_range,
    TestQxSort_less_1000_elements_medium_signed_range,
    TestQxSort_greater_1000_elements_medium_signed_range,
    //TestQxSort_less_100000_elements_medium_signed_range,
    //TestQxSort_greater_100000_elements_medium_signed_range,

    TestQxSort_less_0_elements_big_signed_range,
    TestQxSort_greater_0_elements_big_signed_range,
    TestQxSort_less_1_elements_big_signed_range,
    TestQxSort_greater_1_elements_big_signed_range,
    TestQxSort_less_10_elements_big_signed_range,
    TestQxSort_greater_10_elements_big_signed_range,
    TestQxSort_less_1000_elements_big_signed_range,
    TestQxSort_greater_1000_elements_big_signed_range,
    //TestQxSort_less_100000_elements_big_signed_range,
    //TestQxSort_greater_100000_elements_big_signed_range,

    TestQxSort_less_0_elements_small_unsigned_range,
    TestQxSort_greater_0_elements_small_unsigned_range,
    TestQxSort_less_1_elements_small_unsigned_range,
    TestQxSort_greater_1_elements_small_unsigned_range,
    TestQxSort_less_10_elements_small_unsigned_range,
    TestQxSort_greater_10_elements_small_unsigned_range,
    TestQxSort_less_1000_elements_small_unsigned_range,
    TestQxSort_greater_1000_elements_small_unsigned_range,
    //TestQxSort_less_100000_elements_small_unsigned_range,
    //TestQxSort_greater_100000_elements_small_unsigned_range,

    TestQxSort_less_0_elements_medium_unsigned_range,
    TestQxSort_greater_0_elements_medium_unsigned_range,
    TestQxSort_less_1_elements_medium_unsigned_range,
    TestQxSort_greater_1_elements_medium_unsigned_range,
    TestQxSort_less_10_elements_medium_unsigned_range,
    TestQxSort_greater_10_elements_medium_unsigned_range,
    TestQxSort_less_1000_elements_medium_unsigned_range,
    TestQxSort_greater_1000_elements_medium_unsigned_range,
    //TestQxSort_less_100000_elements_medium_unsigned_range,
    //TestQxSort_greater_100000_elements_medium_unsigned_range,

    TestQxSort_less_0_elements_big_unsigned_range,
    TestQxSort_greater_0_elements_big_unsigned_range,
    TestQxSort_less_1_elements_big_unsigned_range,
    TestQxSort_greater_1_elements_big_unsigned_range,
    TestQxSort_less_10_elements_big_unsigned_range,
    TestQxSort_greater_10_elements_big_unsigned_range,
    TestQxSort_less_1000_elements_big_unsigned_range,
    TestQxSort_greater_1000_elements_big_unsigned_range
    //TestQxSort_less_100000_elements_big_unsigned_range,
    //TestQxSort_greater_100000_elements_big_unsigned_range
>;


TYPED_TEST_SUITE(TestQxSort, Implementations);


TYPED_TEST(TestQxSort, sort_insertion_it)
{
    qx::sort_insertion(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_insertion)
{
    qx::sort_insertion(TestFixture::m_SortedTest, TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_selection_it)
{
    qx::sort_selection(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_selection)
{
    qx::sort_selection(TestFixture::m_SortedTest, TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_bubble_it)
{
    qx::sort_bubble(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_bubble)
{
    qx::sort_bubble(TestFixture::m_SortedTest, TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_heap_it)
{
    qx::sort_heap(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_heap)
{
    qx::sort_heap(TestFixture::m_SortedTest, TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_quick_hoare_it)
{
    qx::sort_quick_hoare(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_quick_hoare)
{
    qx::sort_quick_hoare(TestFixture::m_SortedTest, TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_quick_three_way_it)
{
    qx::sort_quick_three_way(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_quick_three_way)
{
    qx::sort_quick_three_way(TestFixture::m_SortedTest, TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_quick_dual_pivot_it)
{
    qx::sort_quick_dual_pivot(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_quick_dual_pivot)
{
    qx::sort_quick_dual_pivot(TestFixture::m_SortedTest, TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_merge_it)
{
    qx::sort_merge(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_merge)
{
    qx::sort_merge(TestFixture::m_SortedTest, TypeParam::compare());
}
TYPED_TEST(TestQxSort, sort_counting_it)
{
    bool bSucc = qx::sort_counting(TestFixture::m_SortedTest.begin(), TestFixture::m_SortedTest.end(), TypeParam::compare());
    if constexpr (TypeParam::max_element() - TypeParam::min_element() + 1 > qx::SORT_COUNTING_MAX_BUFFER_SIZE)
    {
        if (!bSucc)
        {
            /* too mush memory required. let test pass */
            bSucc = true;
            TestFixture::m_SortedTest = TestFixture::m_SortedStd;
        }
    }
    ASSERT_TRUE(bSucc);
}
TYPED_TEST(TestQxSort, sort_counting)
{
    bool bSucc = qx::sort_counting(TestFixture::m_SortedTest, TypeParam::compare());
    if constexpr (TypeParam::max_element() - TypeParam::min_element() + 1 > qx::SORT_COUNTING_MAX_BUFFER_SIZE)
    {
        if (!bSucc)
        {
            /* too mush memory required. let test pass */
            bSucc = true;
            TestFixture::m_SortedTest = TestFixture::m_SortedStd;
        }
    }
    ASSERT_TRUE(bSucc);
}

#endif
