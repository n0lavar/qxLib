/**

    @file      test_iterate.cpp
    @author    Khrapov
    @date      23.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_iterate.cpp

#include <qx/algo/iterate.h>

#include <vector>

struct MyStruct
{
    int  integer;
    char character;
};

class MyClass
{
public:
    MyClass(std::vector<MyStruct> vector) : m_Vector(std::move(vector))
    {
    }

    template<class callable_t, class filter_t = decltype(qx::iterate_filters::always_true)>
    void Iterate(const callable_t& callable, const filter_t& filter = qx::iterate_filters::always_true) const
    {
        qx::iterate(m_Vector, callable, filter);
    }

    template<class callable_t, class filter_t = decltype(qx::iterate_filters::always_true)>
    void IterateInteger(const callable_t& callable, const filter_t& filter = qx::iterate_filters::always_true) const
    {
        qx::iterate(
            m_Vector,
            callable,
            filter,
            [](const MyStruct& myStruct)
            {
                return myStruct.integer;
            });
    }

private:
    std::vector<MyStruct> m_Vector;
};

TEST(iterate, main)
{
    const MyClass myClass({ { -2, 'a' }, { -1, 'b' }, { 0, 'c' }, { 1, 'd' }, { 2, 'e' }, { 4, 'f' }, { 1, 'u' } });

    {
        std::string str;
        myClass.Iterate(
            [&str](const MyStruct& myStruct)
            {
                str += myStruct.character;
                return false;
            });

        EXPECT_STREQ(str.data(), "abcdefu");
    }

    {
        int sum = 0;
        myClass.IterateInteger(
            [&sum](int integer)
            {
                sum += integer;
                return false;
            },
            [](int integer)
            {
                return integer > 0;
            });

        EXPECT_EQ(sum, 8);
    }

    {
        int sum = 0;
        myClass.IterateInteger(
            [&sum](int integer)
            {
                sum += integer;
                return true;
            },
            [](int integer)
            {
                return integer > 0;
            });

        EXPECT_EQ(sum, 1);
    }

    {
        int sum = 0;
        myClass.IterateInteger(
            [&sum](int integer)
            {
                sum += integer;
                return false;
            },
            [](int integer)
            {
                return integer != 0;
            });

        EXPECT_EQ(sum, 5);
    }

    {
        int sum = 0;
        myClass.IterateInteger(
            [&sum](int integer)
            {
                sum += integer;
                return true;
            },
            [](int integer)
            {
                return integer != 0;
            });

        EXPECT_EQ(sum, -2);
    }
}
