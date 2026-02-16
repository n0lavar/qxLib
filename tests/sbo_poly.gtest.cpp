/**

    @file      sbo_poly.gtest.cpp
    @author    Khrapov
    @date      22.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#include <common.h>

#include <qx/sbo/sbo_poly.h>

//V_EXCLUDE_PATH *.gtest.cpp

static int k_nObjectsCounter             = 0;
static int k_nDerivedSmallObjectsCounter = 0;
static int k_nDerivedBigObjectsCounter   = 0;

class base
{
public:
    base(int nIntData, std::string sString) : m_nIntData(nIntData), m_sStringData(std::move(sString)), m_SavedThis(this)
    {
        ++k_nObjectsCounter;
    }

    base(base&& other) noexcept
    {
        ++k_nObjectsCounter;
        std::swap(m_nIntData, other.m_nIntData);
        std::swap(m_sStringData, other.m_sStringData);
        m_SavedThis = this;
    }

    virtual ~base()
    {
        --k_nObjectsCounter;
    }

    int get_int_data() const
    {
        return m_nIntData;
    }

    std::string_view get_string_data() const
    {
        return m_sStringData;
    }

    base* get_saved_this() const
    {
        return m_SavedThis;
    }

    const base* get_this() const
    {
        return this;
    }

private:
    int         m_nIntData = 0;
    std::string m_sStringData;
    base*       m_SavedThis = nullptr;
};

using sbo_type = qx::sbo_poly<base, 128>;

class derived_small : public base
{
public:
    derived_small(int nIntData, std::string sStringData) : base(nIntData, std::move(sStringData))
    {
        ++k_nDerivedSmallObjectsCounter;
    }

    derived_small(derived_small&& other) noexcept : base(std::move(other))
    {
        ++k_nDerivedSmallObjectsCounter;
    }

    virtual ~derived_small() override
    {
        --k_nDerivedSmallObjectsCounter;
    }
};
QX_STATIC_ASSERT_LE(sizeof(derived_small), sbo_type::sbo_bytes_type::nBufferSize);

class derived_big : public base
{
public:
    derived_big(int nIntData, std::string sString, const std::array<size_t, 8>& arrayData)
        : base(nIntData, std::move(sString))
        , m_ArrayData(arrayData)
    {
        ++k_nDerivedBigObjectsCounter;
    }

    derived_big(derived_big&& other) noexcept : base(std::move(other))
    {
        ++k_nDerivedBigObjectsCounter;
        std::swap(m_ArrayData, other.m_ArrayData);
    }

    virtual ~derived_big() override
    {
        --k_nDerivedBigObjectsCounter;
    }

    const std::array<size_t, 8>& get_array_data() const
    {
        return m_ArrayData;
    }

private:
    std::array<size_t, 8> m_ArrayData;
};
QX_STATIC_ASSERT_LT(sbo_type::sbo_bytes_type::nBufferSize, sizeof(derived_big));

constexpr int k_nSmallIntData = QX_LINE;

static void check_small(const sbo_type& sbo, int nIntData)
{
    EXPECT_EQ(sbo->get_int_data(), nIntData);
    EXPECT_EQ(sbo->get_string_data(), std::to_string(nIntData));
    EXPECT_EQ(sbo->get_saved_this(), sbo->get_this());
}

static sbo_type create_small(int nIntData = k_nSmallIntData)
{
    sbo_type sbo(derived_small(nIntData, std::to_string(nIntData)));
    check_small(sbo, nIntData);
    return sbo;
}

constexpr int                   k_nBigIntData   = QX_LINE;
constexpr std::array<size_t, 8> k_sBigArrayData = { 4, 5, 6, 7, 8, 9, 0, 1 };

static void check_big(const sbo_type& sbo, int nIntData)
{
    EXPECT_EQ(sbo->get_int_data(), nIntData);
    EXPECT_EQ(sbo->get_string_data(), std::to_string(nIntData));
    EXPECT_EQ(sbo->get_saved_this(), sbo->get_this());
    EXPECT_EQ(static_cast<const derived_big&>(sbo.get()).get_array_data(), k_sBigArrayData);
}

static sbo_type create_big(int nIntData = k_nBigIntData)
{
    sbo_type sbo(derived_big(nIntData, std::to_string(nIntData), k_sBigArrayData));
    check_big(sbo, nIntData);
    return sbo;
}

TEST(sbo_poly, lifetime_small)
{
    EXPECT_EQ(k_nObjectsCounter, 0);
    EXPECT_EQ(k_nDerivedSmallObjectsCounter, 0);
    {
        sbo_type sbo = create_small();
        EXPECT_EQ(k_nObjectsCounter, 1);
        EXPECT_EQ(k_nDerivedSmallObjectsCounter, 1);
    }
    EXPECT_EQ(k_nObjectsCounter, 0);
    EXPECT_EQ(k_nDerivedSmallObjectsCounter, 0);
}

TEST(sbo_poly, lifetime_big)
{
    EXPECT_EQ(k_nObjectsCounter, 0);
    EXPECT_EQ(k_nDerivedBigObjectsCounter, 0);
    {
        sbo_type sbo = create_big();
        EXPECT_EQ(k_nObjectsCounter, 1);
        EXPECT_EQ(k_nDerivedBigObjectsCounter, 1);
    }
    EXPECT_EQ(k_nObjectsCounter, 0);
    EXPECT_EQ(k_nDerivedBigObjectsCounter, 0);
}

TEST(sbo_poly, move_small_to_small)
{
    sbo_type small1 = create_small(33);
    sbo_type small2 = create_small(44);
    small2          = std::move(small1);
    check_small(small2, 33);
}

TEST(sbo_poly, move_small_to_big)
{
    sbo_type small = create_small(33);
    sbo_type big   = create_big(44);
    big            = std::move(small);
    check_small(big, 33);
}

TEST(sbo_poly, move_big_to_small)
{
    sbo_type big   = create_big(33);
    sbo_type small = create_small(44);
    small          = std::move(big);
    check_big(small, 33);
}

TEST(sbo_poly, move_big_to_big)
{
    sbo_type big1 = create_big(33);
    sbo_type big2 = create_big(44);
    big2          = std::move(big1);
    check_big(big2, 33);
}
