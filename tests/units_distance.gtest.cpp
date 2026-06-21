/**

    @file      units_distance.gtest.cpp
    @author    Khrapov
    @date      25.09.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/
#include <common.h>

#include <qx/containers/string/format.h>
#include <qx/math/units/distance.h>

template<class value_t>
class test_units_distance : public ::testing::Test
{
};

using implementations_type = ::testing::Types<long long, float, double>;
TYPED_TEST_SUITE(test_units_distance, implementations_type);

TYPED_TEST(test_units_distance, nanometers)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::nanometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::nanometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.000000001));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::nanometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.000000001));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::nanometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.000000005));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::nanometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.000000005));
}

TYPED_TEST(test_units_distance, micrometers)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::micrometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::micrometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.000001));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::micrometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.000001));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::micrometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.000005));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::micrometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.000005));
}

TYPED_TEST(test_units_distance, millimeters)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::millimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::millimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.001));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::millimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.001));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::millimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.005));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::millimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.005));
}

TYPED_TEST(test_units_distance, centimeters)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::centimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::centimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.01));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::centimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.01));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::centimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.05));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::centimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.05));
}

TYPED_TEST(test_units_distance, decimeters)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::decimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::decimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.1));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::decimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.1));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::decimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.5));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::decimeters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.5));
}

TYPED_TEST(test_units_distance, decameters)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::decameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::decameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(10.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::decameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-10.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::decameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(50.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::decameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-50.0));
}

TYPED_TEST(test_units_distance, hectometers)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::hectometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::hectometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(100.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::hectometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(-100.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::hectometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(500.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::hectometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(-500.0));
}

TYPED_TEST(test_units_distance, kilometers)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::kilometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::kilometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(1000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::kilometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::kilometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(5000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::kilometers).to(qx::units::distance::meters),
        static_cast<TypeParam>(-5000.0));
}

TYPED_TEST(test_units_distance, megameters)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::megameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::megameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(1000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::megameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::megameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(5000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::megameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-5000000.0));
}

TYPED_TEST(test_units_distance, gigameters)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::gigameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::gigameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(1000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::gigameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::gigameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(5000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::gigameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-5000000000.0));
}

TYPED_TEST(test_units_distance, terameters)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::terameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::terameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(1000000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::terameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1000000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::terameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(5000000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::terameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-5000000000000.0));
}

TYPED_TEST(test_units_distance, petameters)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::petameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::petameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(1000000000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::petameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1000000000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::petameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(5000000000000000.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::petameters).to(qx::units::distance::meters),
        static_cast<TypeParam>(-5000000000000000.0));
}

TYPED_TEST(test_units_distance, mils)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::mils).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::mils).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0000254));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::mils).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.0000254));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::mils).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.000127));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::mils).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.000127));
}

TYPED_TEST(test_units_distance, inches)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::inches).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::inches).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0254));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::inches).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.0254));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::inches).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.127));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::inches).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.127));
}

TYPED_TEST(test_units_distance, hands)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::hands).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::hands).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.1016));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::hands).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.1016));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::hands).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.508));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::hands).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.508));
}

TYPED_TEST(test_units_distance, links)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::links).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::links).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.201168));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::links).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.201168));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::links).to(qx::units::distance::meters),
        static_cast<TypeParam>(1.00584));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::links).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1.00584));
}

TYPED_TEST(test_units_distance, feet)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::feet).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::feet).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.3048));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::feet).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.3048));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::feet).to(qx::units::distance::meters),
        static_cast<TypeParam>(1.524));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::feet).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1.524));
}

TYPED_TEST(test_units_distance, yards)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::yards).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::yards).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.9144));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::yards).to(qx::units::distance::meters),
        static_cast<TypeParam>(-0.9144));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::yards).to(qx::units::distance::meters),
        static_cast<TypeParam>(4.572));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::yards).to(qx::units::distance::meters),
        static_cast<TypeParam>(-4.572));
}

TYPED_TEST(test_units_distance, rods)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::rods).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::rods).to(qx::units::distance::meters),
        static_cast<TypeParam>(5.0292));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::rods).to(qx::units::distance::meters),
        static_cast<TypeParam>(-5.0292));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::rods).to(qx::units::distance::meters),
        static_cast<TypeParam>(25.146));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::rods).to(qx::units::distance::meters),
        static_cast<TypeParam>(-25.146));
}

TYPED_TEST(test_units_distance, chains)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::chains).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::chains).to(qx::units::distance::meters),
        static_cast<TypeParam>(20.1168));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::chains).to(qx::units::distance::meters),
        static_cast<TypeParam>(-20.1168));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::chains).to(qx::units::distance::meters),
        static_cast<TypeParam>(100.584));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::chains).to(qx::units::distance::meters),
        static_cast<TypeParam>(-100.584));
}

TYPED_TEST(test_units_distance, furlongs)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::furlongs).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::furlongs).to(qx::units::distance::meters),
        static_cast<TypeParam>(201.168));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::furlongs).to(qx::units::distance::meters),
        static_cast<TypeParam>(-201.168));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::furlongs).to(qx::units::distance::meters),
        static_cast<TypeParam>(1005.84));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::furlongs).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1005.84));
}

TYPED_TEST(test_units_distance, miles)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(1609.344));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1609.344));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(8046.72));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(-8046.72));
}

TYPED_TEST(test_units_distance, leagues)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::leagues).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::leagues).to(qx::units::distance::meters),
        static_cast<TypeParam>(4828.032));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::leagues).to(qx::units::distance::meters),
        static_cast<TypeParam>(-4828.032));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::leagues).to(qx::units::distance::meters),
        static_cast<TypeParam>(24140.16));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::leagues).to(qx::units::distance::meters),
        static_cast<TypeParam>(-24140.16));
}

TYPED_TEST(test_units_distance, fathoms)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::fathoms).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::fathoms).to(qx::units::distance::meters),
        static_cast<TypeParam>(1.8288));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::fathoms).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1.8288));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::fathoms).to(qx::units::distance::meters),
        static_cast<TypeParam>(9.144));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::fathoms).to(qx::units::distance::meters),
        static_cast<TypeParam>(-9.144));
}

TYPED_TEST(test_units_distance, cables)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::cables).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::cables).to(qx::units::distance::meters),
        static_cast<TypeParam>(185.2));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::cables).to(qx::units::distance::meters),
        static_cast<TypeParam>(-185.2));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::cables).to(qx::units::distance::meters),
        static_cast<TypeParam>(926.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::cables).to(qx::units::distance::meters),
        static_cast<TypeParam>(-926.0));
}

TYPED_TEST(test_units_distance, nautical_miles)
{
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(0.0), qx::units::distance::nautical_miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(0.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(1.0), qx::units::distance::nautical_miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(1852.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-1.0), qx::units::distance::nautical_miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(-1852.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(5.0), qx::units::distance::nautical_miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(9260.0));
    expect_equal<TypeParam>(
        qx::convert(static_cast<TypeParam>(-5.0), qx::units::distance::nautical_miles).to(qx::units::distance::meters),
        static_cast<TypeParam>(-9260.0));
}

TEST(units_distance, astronomical_units)
{
    expect_equal<double>(
        qx::convert(0.0, qx::units::distance::astronomical_units).to(qx::units::distance::meters),
        0.0);
    expect_equal<double>(
        qx::convert(1.0, qx::units::distance::astronomical_units).to(qx::units::distance::meters),
        149597870700.0);
    expect_equal<double>(
        qx::convert(-1.0, qx::units::distance::astronomical_units).to(qx::units::distance::meters),
        -149597870700.0);
    expect_equal<double>(
        qx::convert(5.0, qx::units::distance::astronomical_units).to(qx::units::distance::meters),
        747989353500.0);
    expect_equal<double>(
        qx::convert(-5.0, qx::units::distance::astronomical_units).to(qx::units::distance::meters),
        -747989353500.0);
}

TEST(units_distance, light_years)
{
    expect_equal<double>(qx::convert(0.0, qx::units::distance::light_years).to(qx::units::distance::meters), 0.0);
    expect_equal<double>(
        qx::convert(1.0, qx::units::distance::light_years).to(qx::units::distance::meters),
        9460730472580800.0);
    expect_equal<double>(
        qx::convert(-1.0, qx::units::distance::light_years).to(qx::units::distance::meters),
        -9460730472580800.0);
    expect_equal<double>(
        qx::convert(5.0, qx::units::distance::light_years).to(qx::units::distance::meters),
        47303652362904000.0);
    expect_equal<double>(
        qx::convert(-5.0, qx::units::distance::light_years).to(qx::units::distance::meters),
        -47303652362904000.0);
}

TEST(units_distance, parsecs)
{
    expect_equal<double>(qx::convert(0.0, qx::units::distance::parsecs).to(qx::units::distance::meters), 0.0);
    expect_equal<double>(
        qx::convert(1.0, qx::units::distance::parsecs).to(qx::units::distance::meters),
        30856775814913673.0);
    expect_equal<double>(
        qx::convert(-1.0, qx::units::distance::parsecs).to(qx::units::distance::meters),
        -30856775814913673.0);
    expect_equal<double>(
        qx::convert(5.0, qx::units::distance::parsecs).to(qx::units::distance::meters),
        154283879074568365.0);
    expect_equal<double>(
        qx::convert(-5.0, qx::units::distance::parsecs).to(qx::units::distance::meters),
        -154283879074568365.0);
}

TEST(units_distance, normalize_unit)
{
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::nanometers),
        qx::unit(5.0, qx::units::distance::nanometers));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::micrometers),
        qx::unit(5.0, qx::units::distance::micrometers));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::millimeters),
        qx::unit(5.0, qx::units::distance::millimeters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::centimeters),
        qx::unit(5.0, qx::units::distance::centimeters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::decimeters),
        qx::unit(50.0, qx::units::distance::centimeters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::meters), qx::unit(5.0, qx::units::distance::meters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::decameters), qx::unit(50.0, qx::units::distance::meters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::hectometers),
        qx::unit(500.0, qx::units::distance::meters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::kilometers),
        qx::unit(5.0, qx::units::distance::kilometers));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::megameters),
        qx::unit(5.0, qx::units::distance::megameters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::gigameters),
        qx::unit(5.0, qx::units::distance::gigameters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::terameters),
        qx::unit(5.0, qx::units::distance::terameters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::petameters),
        qx::unit(5.0, qx::units::distance::petameters));

    expect_equal(qx::normalize_unit(5.0, qx::units::distance::mils), qx::unit(127.0, qx::units::distance::micrometers));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::inches),
        qx::unit(12.7, qx::units::distance::centimeters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::hands), qx::unit(50.8, qx::units::distance::centimeters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::links), qx::unit(1.00584, qx::units::distance::meters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::feet), qx::unit(1.524, qx::units::distance::meters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::yards), qx::unit(4.572, qx::units::distance::meters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::rods), qx::unit(25.146, qx::units::distance::meters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::chains), qx::unit(100.584, qx::units::distance::meters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::furlongs),
        qx::unit(1.00584, qx::units::distance::kilometers));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::miles),
        qx::unit(8.04672, qx::units::distance::kilometers));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::leagues),
        qx::unit(24.14016, qx::units::distance::kilometers));

    expect_equal(qx::normalize_unit(5.0, qx::units::distance::fathoms), qx::unit(9.144, qx::units::distance::meters));
    expect_equal(qx::normalize_unit(5.0, qx::units::distance::cables), qx::unit(926.0, qx::units::distance::meters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::nautical_miles),
        qx::unit(9.260, qx::units::distance::kilometers));

    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::astronomical_units),
        qx::unit(747.9893535000, qx::units::distance::gigameters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::light_years),
        qx::unit(47.303652362904000, qx::units::distance::petameters));
    expect_equal(
        qx::normalize_unit(5.0, qx::units::distance::parsecs),
        qx::unit(154.283879074568365, qx::units::distance::petameters));
}

TEST(units_distance, format)
{
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::nanometers)), QXT("42nm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::micrometers)), QXT("42um"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::millimeters)), QXT("42mm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::centimeters)), QXT("42cm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::decimeters)), QXT("42dm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::meters)), QXT("42m"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::decameters)), QXT("42dam"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::hectometers)), QXT("42hm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::kilometers)), QXT("42km"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::megameters)), QXT("42Mm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::gigameters)), QXT("42Gm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::terameters)), QXT("42Tm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::petameters)), QXT("42Pm"));

    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::mils)), QXT("42mil"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::inches)), QXT("42in"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::hands)), QXT("42hh"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::links)), QXT("42li"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::feet)), QXT("42ft"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::yards)), QXT("42yd"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::rods)), QXT("42rd"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::chains)), QXT("42ch"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::furlongs)), QXT("42fur"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::miles)), QXT("42mi"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::leagues)), QXT("42lea"));

    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::fathoms)), QXT("42fm"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::cables)), QXT("42cables"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::nautical_miles)), QXT("42nmi"));

    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::astronomical_units)), QXT("42AU"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::light_years)), QXT("42ly"));
    expect_equal(qx::convert_to_string(qx::unit(42, qx::units::distance::parsecs)), QXT("42pc"));
}

TEST(units_distance, from_string)
{
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42nm")),
        qx::unit(42, qx::units::distance::nanometers));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42um")),
        qx::unit(42, qx::units::distance::micrometers));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42mm")),
        qx::unit(42, qx::units::distance::millimeters));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42cm")),
        qx::unit(42, qx::units::distance::centimeters));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42dm")),
        qx::unit(42, qx::units::distance::decimeters));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42m")),
        qx::unit(42, qx::units::distance::meters));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42dam")),
        qx::unit(42, qx::units::distance::decameters));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42hm")),
        qx::unit(42, qx::units::distance::hectometers));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42km")),
        qx::unit(42, qx::units::distance::kilometers));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42Mm")),
        qx::unit(42, qx::units::distance::megameters));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42Gm")),
        qx::unit(42, qx::units::distance::gigameters));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42Tm")),
        qx::unit(42, qx::units::distance::terameters));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42Pm")),
        qx::unit(42, qx::units::distance::petameters));

    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42mil")),
        qx::unit(42, qx::units::distance::mils));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42in")),
        qx::unit(42, qx::units::distance::inches));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42hh")),
        qx::unit(42, qx::units::distance::hands));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42li")),
        qx::unit(42, qx::units::distance::links));
    expect_equal(*qx::unit_from_string<int, qx::units::distance>(QXT("42ft")), qx::unit(42, qx::units::distance::feet));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42yd")),
        qx::unit(42, qx::units::distance::yards));
    expect_equal(*qx::unit_from_string<int, qx::units::distance>(QXT("42rd")), qx::unit(42, qx::units::distance::rods));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42ch")),
        qx::unit(42, qx::units::distance::chains));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42fur")),
        qx::unit(42, qx::units::distance::furlongs));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42mi")),
        qx::unit(42, qx::units::distance::miles));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42lea")),
        qx::unit(42, qx::units::distance::leagues));

    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42fm")),
        qx::unit(42, qx::units::distance::fathoms));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42cables")),
        qx::unit(42, qx::units::distance::cables));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42nmi")),
        qx::unit(42, qx::units::distance::nautical_miles));

    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42AU")),
        qx::unit(42, qx::units::distance::astronomical_units));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42ly")),
        qx::unit(42, qx::units::distance::light_years));
    expect_equal(
        *qx::unit_from_string<int, qx::units::distance>(QXT("42pc")),
        qx::unit(42, qx::units::distance::parsecs));
}
