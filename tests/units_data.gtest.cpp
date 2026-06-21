/**

    @file      units_data.gtest.cpp
    @author    Khrapov
    @date      11.08.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/
#include <common.h>

#include <qx/containers/string/format.h>
#include <qx/containers/string/string.h>
#include <qx/math/units/data.h>

//V_EXCLUDE_PATH *.gtest.cpp

template<class value_t>
class test_convert_integral : public ::testing::Test
{
};

using implementations_integral_type = ::testing::Types<int, long, long long>;

TYPED_TEST_SUITE(test_convert_integral, implementations_integral_type);

template<class T>
static void test_binary_binary_signed(int nSign)
{
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::bits), nSign * T(8));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::nibbles), nSign * T(2));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::bytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::pebibytes), nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::bits), nSign * T(4));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::nibbles), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::bits), nSign * T(16));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::nibbles), nSign * T(4));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::bytes), nSign * T(2));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::pebibytes), nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::bits), nSign * T(8));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::nibbles), nSign * T(2));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::bytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1024), qx::units::data::bytes).to(qx::units::data::bits), nSign * T(8192));
    expect_equal<T>(qx::convert(nSign * T(1024), qx::units::data::bytes).to(qx::units::data::nibbles), nSign * T(2048));
    expect_equal<T>(qx::convert(nSign * T(1024), qx::units::data::bytes).to(qx::units::data::bytes), nSign * T(1024));
    expect_equal<T>(qx::convert(nSign * T(1024), qx::units::data::bytes).to(qx::units::data::kibibytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1024), qx::units::data::bytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1024), qx::units::data::bytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1024), qx::units::data::bytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1024), qx::units::data::bytes).to(qx::units::data::pebibytes), nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::bits), nSign * T(8192));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::nibbles),
        nSign * T(2048));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::bytes), nSign * T(1024));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::kibibytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::bits),
        nSign * T(8'388'608));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::nibbles),
        nSign * T(2'097'152));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::bytes),
        nSign * T(1'048'576));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::kibibytes),
        nSign * T(1024));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::mebibytes),
        nSign * T(1));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::gibibytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::tebibytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::pebibytes),
        nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::bits),
        nSign * T(8'388'608));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::nibbles),
        nSign * T(2'097'152));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::bytes),
        nSign * T(1'048'576));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::kibibytes),
        nSign * T(1024));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::mebibytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::kibibytes),
        nSign * T(1'048'576));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::mebibytes),
        nSign * T(1024));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::gibibytes),
        nSign * T(1));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::tebibytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::pebibytes),
        nSign * T(0));
}

TYPED_TEST(test_convert_integral, binary_binary)
{
    test_binary_binary_signed<TypeParam>(1);
    test_binary_binary_signed<TypeParam>(-1);
}

template<class T>
static void test_multiplicative_multiplicative_signed(int nSign)
{
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::kilobytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::kilobytes).to(qx::units::data::kilobytes),
        nSign * T(1000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::kilobytes).to(qx::units::data::megabytes),
        nSign * T(1));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::kilobytes).to(qx::units::data::gigabytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::kilobytes).to(qx::units::data::terabytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::kilobytes).to(qx::units::data::petabytes),
        nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::kilobytes),
        nSign * T(1000));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::megabytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::megabytes).to(qx::units::data::kilobytes),
        nSign * T(1'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::megabytes).to(qx::units::data::megabytes),
        nSign * T(1000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::megabytes).to(qx::units::data::gigabytes),
        nSign * T(1));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::megabytes).to(qx::units::data::terabytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::megabytes).to(qx::units::data::petabytes),
        nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::kilobytes),
        nSign * T(1'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::megabytes),
        nSign * T(1000));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::gigabytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::kilobytes),
        nSign * T(1'000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::megabytes),
        nSign * T(1000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::gigabytes),
        nSign * T(1000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::terabytes),
        nSign * T(1));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::petabytes),
        nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::kilobytes),
        nSign * T(1'000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::megabytes),
        nSign * T(1'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::gigabytes),
        nSign * T(1000));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::terabytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::petabytes), nSign * T(0));

    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::kilobytes),
    //     nSign * T(1'000'000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::megabytes),
        nSign * T(1000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::gigabytes),
        nSign * T(1'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::terabytes),
        nSign * T(1000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::petabytes),
        nSign * T(1));
}

TYPED_TEST(test_convert_integral, multiplicative_multiplicative)
{
    test_multiplicative_multiplicative_signed<TypeParam>(1);
    test_multiplicative_multiplicative_signed<TypeParam>(-1);
}

template<class T>
static void test_binary_multiplicative_signed(int nSign)
{
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bits).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(8), qx::units::data::bits).to(qx::units::data::petabytes), nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::nibbles).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::nibbles).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::nibbles).to(qx::units::data::petabytes), nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::bytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::bytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1000), qx::units::data::bytes).to(qx::units::data::kilobytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1000), qx::units::data::bytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1000), qx::units::data::bytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1000), qx::units::data::bytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1000), qx::units::data::bytes).to(qx::units::data::petabytes), nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kibibytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::kilobytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kibibytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::kilobytes),
        nSign * T(1048));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::megabytes),
        nSign * T(1));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::gigabytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::terabytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::kibibytes).to(qx::units::data::petabytes),
        nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::kilobytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::megabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::mebibytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::kilobytes),
        nSign * T(1048));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::megabytes), nSign * T(1));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::gigabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::terabytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::mebibytes).to(qx::units::data::petabytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::kilobytes),
        nSign * T(1'073'741));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::megabytes),
        nSign * T(1073));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::gigabytes),
        nSign * T(1));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::terabytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1024), qx::units::data::mebibytes).to(qx::units::data::petabytes),
        nSign * T(0));
}

TYPED_TEST(test_convert_integral, binary_multiplicative)
{
    test_binary_multiplicative_signed<TypeParam>(1);
    test_binary_multiplicative_signed<TypeParam>(-1);
}

template<class T>
static void test_multiplicative_binary_signed(int nSign)
{
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::kilobytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::bits), nSign * T(8000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::nibbles),
        nSign * T(2000));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::bytes), nSign * T(1000));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::kilobytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::kilobytes).to(qx::units::data::bits), nSign * T(32000));
    expect_equal<T>(
        qx::convert(nSign * T(4), qx::units::data::kilobytes).to(qx::units::data::nibbles),
        nSign * T(8000));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::kilobytes).to(qx::units::data::bytes), nSign * T(4000));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::kilobytes).to(qx::units::data::kibibytes), nSign * T(3));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::kilobytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::kilobytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::kilobytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::kilobytes).to(qx::units::data::pebibytes), nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::megabytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::bits),
        nSign * T(8'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::nibbles),
        nSign * T(2'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::bytes),
        nSign * T(1'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::kibibytes),
        nSign * T(976));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::megabytes).to(qx::units::data::pebibytes), nSign * T(0));

    expect_equal<T>(
        qx::convert(nSign * T(4), qx::units::data::megabytes).to(qx::units::data::bits),
        nSign * T(32'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(4), qx::units::data::megabytes).to(qx::units::data::nibbles),
        nSign * T(8'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(4), qx::units::data::megabytes).to(qx::units::data::bytes),
        nSign * T(4'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(4), qx::units::data::megabytes).to(qx::units::data::kibibytes),
        nSign * T(3906));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::megabytes).to(qx::units::data::mebibytes), nSign * T(3));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::megabytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::megabytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(4), qx::units::data::megabytes).to(qx::units::data::pebibytes), nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::gigabytes).to(qx::units::data::pebibytes), nSign * T(0));

    // expect_equal<T>(
    //     qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::bits),
    //     nSign * T(8'000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::nibbles),
        nSign * T(2'000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::bytes),
        nSign * T(1'000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::kibibytes),
        nSign * T(976'562));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::mebibytes),
        nSign * T(953));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::gigabytes).to(qx::units::data::pebibytes), nSign * T(0));

    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::bits),
    //     nSign * T(8'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::nibbles),
    //     nSign * T(2'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::bytes),
    //     nSign * T(1'000'000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::kibibytes),
        nSign * T(976'562'500));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::mebibytes),
        nSign * T(953'674));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::gibibytes),
        nSign * T(931));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::tebibytes),
        nSign * T(0));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::gigabytes).to(qx::units::data::pebibytes),
        nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::terabytes).to(qx::units::data::pebibytes), nSign * T(0));

    // expect_equal<T>(
    //     qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::bits),
    //     nSign * T(8'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::nibbles),
    //     nSign * T(2'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::bytes),
    //     nSign * T(1'000'000'000'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::kibibytes),
        nSign * T(976'562'500));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::mebibytes),
        nSign * T(953'674));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::gibibytes),
        nSign * T(931));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::terabytes).to(qx::units::data::pebibytes), nSign * T(0));

    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::bits),
    //     nSign * T(8'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::nibbles),
    //     nSign * T(2'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::bytes),
    //     nSign * T(1'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::kibibytes),
    //     nSign * T(976'562'500'000));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::mebibytes),
        nSign * T(953'674'316));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::gibibytes),
        nSign * T(931'322));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::tebibytes),
        nSign * T(909));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::terabytes).to(qx::units::data::pebibytes),
        nSign * T(0));


    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::petabytes).to(qx::units::data::bits), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::petabytes).to(qx::units::data::nibbles), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::petabytes).to(qx::units::data::bytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::petabytes).to(qx::units::data::kibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::petabytes).to(qx::units::data::mebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::petabytes).to(qx::units::data::gibibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::petabytes).to(qx::units::data::tebibytes), nSign * T(0));
    expect_equal<T>(qx::convert(nSign * T(0), qx::units::data::petabytes).to(qx::units::data::pebibytes), nSign * T(0));

    // expect_equal<T>(
    //     qx::convert(nSign * T(1), qx::units::data::petabytes).to(qx::units::data::bits),
    //     nSign * T(8'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1), qx::units::data::petabytes).to(qx::units::data::nibbles),
    //     nSign * T(2'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1), qx::units::data::petabytes).to(qx::units::data::bytes),
    //     nSign * T(1'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1), qx::units::data::petabytes).to(qx::units::data::kibibytes),
    //     nSign * T(976'562'500'000));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::petabytes).to(qx::units::data::mebibytes),
        nSign * T(953'674'316));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::petabytes).to(qx::units::data::gibibytes),
        nSign * T(931'322));
    expect_equal<T>(
        qx::convert(nSign * T(1), qx::units::data::petabytes).to(qx::units::data::tebibytes),
        nSign * T(909));
    expect_equal<T>(qx::convert(nSign * T(1), qx::units::data::petabytes).to(qx::units::data::pebibytes), nSign * T(0));

    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::petabytes).to(qx::units::data::bits),
    //     nSign * T(8'000'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::petabytes).to(qx::units::data::nibbles),
    //     nSign * T(2'000'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::petabytes).to(qx::units::data::bytes),
    //     nSign * T(1'000'000'000'000'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::petabytes).to(qx::units::data::kibibytes),
    //     nSign * T(976'562'500'000'000));
    // expect_equal<T>(
    //     qx::convert(nSign * T(1000), qx::units::data::petabytes).to(qx::units::data::mebibytes),
    //     nSign * T(953'674'316'406));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::petabytes).to(qx::units::data::gibibytes),
        nSign * T(931'322'574));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::petabytes).to(qx::units::data::tebibytes),
        nSign * T(909'494));
    expect_equal<T>(
        qx::convert(nSign * T(1000), qx::units::data::petabytes).to(qx::units::data::pebibytes),
        nSign * T(888));
}

TYPED_TEST(test_convert_integral, multiplicative_binary)
{
    test_multiplicative_binary_signed<TypeParam>(1);
    test_multiplicative_binary_signed<TypeParam>(-1);
}

// template<class value_t>
// class test_convert_floating_point : public ::testing::Test
// {
// };
//
// using implementations_floating_point_type = ::testing::Types<float, double, long double>;
//
// TYPED_TEST_SUITE(test_convert_floating_point, implementations_floating_point_type);
//
// TYPED_TEST(test_convert_floating_point, binary_binary)
// {
// }
//
// TYPED_TEST(test_convert_floating_point, multiplicative_multiplicative)
// {
// }
//
// TYPED_TEST(test_convert_floating_point, binary_multiplicative)
// {
// }
//
// TYPED_TEST(test_convert_floating_point, multiplicative_binary)
// {
// }

TEST(data, normalize)
{
    expect_equal(qx::normalize_unit(5.f, qx::units::data::bits), qx::unit(5.f, qx::units::data::bits));
    expect_equal(qx::normalize_unit(13.f, qx::units::data::bits), qx::unit(1.625f, qx::units::data::bytes));
    expect_equal(qx::normalize_unit(10240.f, qx::units::data::bits), qx::unit(1.25f, qx::units::data::kibibytes));

    expect_equal(qx::normalize_unit(800.f, qx::units::data::bytes), qx::unit(800.f, qx::units::data::bytes));
    expect_equal(qx::normalize_unit(1536.f, qx::units::data::bytes), qx::unit(1.5f, qx::units::data::kibibytes));
    expect_equal(qx::normalize_unit(1'572'864.f, qx::units::data::bytes), qx::unit(1.5f, qx::units::data::mebibytes));

    expect_equal(qx::normalize_unit(800.f, qx::units::data::kibibytes), qx::unit(800.f, qx::units::data::kibibytes));
    expect_equal(qx::normalize_unit(1536.f, qx::units::data::kibibytes), qx::unit(1.5f, qx::units::data::mebibytes));
    expect_equal(
        qx::normalize_unit(1'572'864.f, qx::units::data::kibibytes),
        qx::unit(1.5f, qx::units::data::gibibytes));
}

TEST(data, format)
{
    expect_equal(qx::convert_to_string(qx::unit(200.f, qx::units::data::bits)), QXT("200b"));
    expect_equal(
        qx::string::static_format(QXT("{:.2f}"), qx::unit(2.12345f, qx::units::data::kibibytes)),
        QXT("2.12KiB"));
}

TEST(data, from_string)
{
    expect_equal(*qx::unit_from_string<int, qx::units::data>(QXT("128b")), qx::unit(128, qx::units::data::bits));

    expect_equal(*qx::unit_from_string<int, qx::units::data>(QXT("20KiB")), qx::unit(20, qx::units::data::kibibytes));

    expect_equal(*qx::unit_from_string<int, qx::units::data>(QXT("666PiB")), qx::unit(666, qx::units::data::pebibytes));

    expect_equal(
        *qx::unit_from_string<int, qx::units::data>(QXT("1000MB")),
        qx::unit(1000, qx::units::data::megabytes));

    expect_equal(*qx::unit_from_string<int, qx::units::data>(QXT("2828nib")), qx::unit(2828, qx::units::data::nibbles));
}
