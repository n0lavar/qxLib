/**

    @file      sbo_bytes.gtest.cpp
    @author    Khrapov
    @date      20.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *sbo_bytes.gtest.cpp

#include <qx/sbo/sbo_bytes.h>



template<size_t nSize, size_t nStartSeed>
static constexpr std::array<std::byte, nSize> get_bytes()
{
    std::array<std::byte, nSize> result;
    size_t                       nState = nStartSeed;

    for (size_t i = 0; i < nSize; ++i)
    {
        nState    = nState * 6364136223846793005ULL + 1;
        result[i] = static_cast<std::byte>(nState >> 56);
    }

    return result;
}

static constexpr size_t k_nSBOSize = 32;

static constexpr auto k_SmallBytesBlock1 = get_bytes<15, 0>();
static constexpr auto k_SmallBytesBlock2 = get_bytes<10, 1>();
static constexpr auto k_BigBytesBlock1   = get_bytes<40, 2>();
static constexpr auto k_BigBytesBlock2   = get_bytes<45, 3>();


template<size_t nSBOSize_, bool bShrinkToFitWhenSmall_, size_t nAlignment_>
struct test_sbo_bytes_traits
{
    using size_type                                  = size_t;
    static constexpr size_type nSBOSize              = nSBOSize_;
    static constexpr bool      bShrinkToFitWhenSmall = bShrinkToFitWhenSmall_;
    static constexpr size_type nAlignment            = nAlignment_;
};

static void set_block(auto& SBO, const auto& block, size_t nAlignment)
{
    SBO.resize(block.size(), nAlignment, qx::sbo_resize_type::common, true);
    EXPECT_EQ(SBO.size(), block.size());
    EXPECT_EQ(SBO.capacity() % nAlignment, 0);
}

static void check_block(auto& SBO, const auto& block)
{
    std::memmove(SBO.data(), block.data(), block.size());
    EXPECT_EQ(std::memcmp(std::as_const(SBO).data(), block.data(), block.size()), 0);
}

template<class traits_t>
class test_sbo_bytes_resize : public ::testing::Test
{
protected:
    using sbo_type = qx::sbo_bytes<traits_t>;

protected:
    void set_and_check_block(const auto& block)
    {
        set_block(m_SBO, block, traits_t::nAlignment);
        check_block(m_SBO, block);
    }

    void test_small() const
    {
        if constexpr (traits_t::nAlignment <= sbo_type::nBufferSize)
            EXPECT_TRUE(this->m_SBO.is_small());
    }

    void test_big() const
    {
        EXPECT_FALSE(this->m_SBO.is_small());
    }

protected:
    sbo_type m_SBO;
};

using implementations_type = ::testing::Types<
    test_sbo_bytes_traits<k_nSBOSize, true, 4>,
    test_sbo_bytes_traits<k_nSBOSize, true, 8>,
    test_sbo_bytes_traits<k_nSBOSize, true, 16>,
    test_sbo_bytes_traits<k_nSBOSize, true, 32>,
    test_sbo_bytes_traits<k_nSBOSize, true, 64>,
    test_sbo_bytes_traits<k_nSBOSize, false, 4>,
    test_sbo_bytes_traits<k_nSBOSize, false, 8>,
    test_sbo_bytes_traits<k_nSBOSize, false, 16>,
    test_sbo_bytes_traits<k_nSBOSize, false, 32>,
    test_sbo_bytes_traits<k_nSBOSize, false, 64>>;

TYPED_TEST_SUITE(test_sbo_bytes_resize, implementations_type);



TYPED_TEST(test_sbo_bytes_resize, small_to_small)
{
    this->test_small();

    this->set_and_check_block(k_SmallBytesBlock1);
    this->test_small();

    this->set_and_check_block(k_SmallBytesBlock2);
    this->test_small();
}

TYPED_TEST(test_sbo_bytes_resize, small_to_big)
{
    this->test_small();

    this->set_and_check_block(k_SmallBytesBlock1);
    this->test_small();

    this->set_and_check_block(k_BigBytesBlock1);
    this->test_big();
}

TYPED_TEST(test_sbo_bytes_resize, big_to_small)
{
    this->test_small();

    this->set_and_check_block(k_BigBytesBlock1);
    this->test_big();

    this->set_and_check_block(k_SmallBytesBlock1);
    if constexpr (TypeParam::bShrinkToFitWhenSmall)
        this->test_small();
    else
        this->test_big();
}

TYPED_TEST(test_sbo_bytes_resize, big_to_big)
{
    this->test_small();

    this->set_and_check_block(k_BigBytesBlock1);
    this->test_big();

    this->set_and_check_block(k_BigBytesBlock2);
    this->test_big();
}

TYPED_TEST(test_sbo_bytes_resize, shrink_to_fit)
{
    if constexpr (TypeParam::bShrinkToFitWhenSmall)
        return;

    this->set_and_check_block(k_BigBytesBlock1);
    this->set_and_check_block(k_SmallBytesBlock1);

    this->m_SBO.resize(this->m_SBO.size(), TypeParam::nAlignment, qx::sbo_resize_type::shrink_to_fit, true);
    this->test_small();
}

using sbo_bytes_move = qx::sbo_bytes<test_sbo_bytes_traits<k_nSBOSize, false, 8>>;

TEST(test_sbo_bytes_move, small_to_small)
{
    sbo_bytes_move from;
    set_block(from, k_SmallBytesBlock1, 8);

    sbo_bytes_move to;
    set_block(to, k_SmallBytesBlock2, 8);

    to = std::move(from);
    check_block(to, k_SmallBytesBlock1);
}

TEST(test_sbo_bytes_move, big_to_small)
{
    sbo_bytes_move from;
    set_block(from, k_BigBytesBlock1, 8);

    sbo_bytes_move to;
    set_block(to, k_SmallBytesBlock2, 8);

    to = std::move(from);
    check_block(to, k_BigBytesBlock1);
}

TEST(test_sbo_bytes_move, small_to_big)
{
    sbo_bytes_move from;
    set_block(from, k_SmallBytesBlock1, 8);

    sbo_bytes_move to;
    set_block(to, k_BigBytesBlock1, 8);

    to = std::move(from);
    check_block(to, k_SmallBytesBlock1);
}

TEST(test_sbo_bytes_move, big_to_big)
{
    sbo_bytes_move from;
    set_block(from, k_BigBytesBlock1, 8);

    sbo_bytes_move to;
    set_block(to, k_BigBytesBlock2, 8);

    to = std::move(from);
    check_block(to, k_BigBytesBlock1);
}
