/**

    @file      test_state.cpp
    @author    Khrapov
    @date      27.04.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_state.cpp

#include <qx/state.h>

#include <unordered_map>

class CNonZeroInt
{
public:
    CNonZeroInt(void) = default;

    CNonZeroInt(int nValue) : m_nValue(nValue)
    {
    }

    auto operator<=>(const CNonZeroInt&) const = default;

private:
    int m_nValue = 0;
};

using TState = qx::state<CNonZeroInt>;

TEST(state, construct)
{
    TState state1;
    EXPECT_TRUE(state1.is_default());

    TState state2(state1);
    EXPECT_TRUE(state2.is_default());

    TState state3(std::move(state2));
    EXPECT_TRUE(state3.is_default());

    TState state4(1);
    EXPECT_FALSE(state4.is_default());
}

TEST(state, assign)
{
    TState state1 = TState();
    TState state2 = state1;
    EXPECT_TRUE(state2.is_default());

    TState state3 = std::move(state2);
    EXPECT_TRUE(state3.is_default());

    TState state4 = CNonZeroInt(1);
    EXPECT_FALSE(state4.is_default());
}

TEST(state, equal)
{
    TState state11(1);
    TState state12(1);
    TState state2(2);

    EXPECT_EQ(state11, state12);
    EXPECT_NE(state11, state2);
    EXPECT_NE(state12, state2);

    EXPECT_EQ(state11, 1);
    EXPECT_EQ(state12, 1);
    EXPECT_EQ(state2, 2);
}

TEST(state, reset_is_default)
{
    TState state;
    EXPECT_TRUE(state.is_default());

    state = 1;
    EXPECT_FALSE(state.is_default());

    state.reset();
    EXPECT_TRUE(state.is_default());
}

TEST(state, hash)
{
    std::unordered_map<TState, int> map;
}
