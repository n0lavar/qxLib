//==============================================================================
//
//!\file                         test_state.cpp
//
//!\brief       Tests for qx::state
//!\details     ~
//
//!\author      Khrapov
//!\date        27.04.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_state.cpp

#if QX_TEST_STATE

#include <qx/state.h>

#include <unordered_map>

TEST(state, construct)
{
    qx::state state1;
    EXPECT_TRUE(state1.is_default());

    qx::state state2(state1);
    EXPECT_TRUE(state2.is_default());

    qx::state state3(std::move(state2));
    EXPECT_TRUE(state3.is_default());

    qx::state state4(1);
    EXPECT_FALSE(state4.is_default());
}

TEST(state, assign)
{
    qx::state state1;
    qx::state state2 = state1;
    EXPECT_TRUE(state2.is_default());

    qx::state state3 = std::move(state2);
    EXPECT_TRUE(state3.is_default());

    qx::state state4 = 1;
    EXPECT_FALSE(state4.is_default());
}

TEST(state, equal)
{
    qx::state state11(1);
    qx::state state12(1);
    qx::state state2(2);

    EXPECT_EQ(state11, state12);
    EXPECT_NE(state11, state2);
    EXPECT_NE(state12, state2);

    EXPECT_EQ(state11, 1);
    EXPECT_EQ(state12, 1);
    EXPECT_EQ(state2, 2);
}

TEST(state, reset_is_default)
{
    qx::state state;
    EXPECT_TRUE(state.is_default());

    state = 1;
    EXPECT_FALSE(state.is_default());

    state.reset();
    EXPECT_TRUE(state.is_default());
}

TEST(state, hash)
{
    std::unordered_map<qx::state, int> map;
}

#endif