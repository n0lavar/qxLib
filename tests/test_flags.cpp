#include <common.h>

//V_EXCLUDE_PATH *test_flags.cpp

#include <qx/containers/flags.h>

enum class EFlags
{
    None   = 0,
    First  = 1 << 0,
    Second = 1 << 1,
    Third  = 1 << 2,
    Fourth = 1 << 3,
};

template<class FirstEnumType, class SecondEnumType>
void Check(FirstEnumType eFlags, SecondEnumType eLess, SecondEnumType eEqual, SecondEnumType eGreater)
{
    EXPECT_LT(eLess, eFlags);
    EXPECT_EQ(eEqual, eFlags);
    EXPECT_GT(eGreater, eFlags);
    EXPECT_NE(eLess, eFlags);
    EXPECT_NE(eGreater, eFlags);
}

TEST(flags, construction_and_comparisons)
{
    {
        qx::flags<EFlags> flags(EFlags::Second);
        Check(flags, EFlags::First, EFlags::Second, EFlags::Third);
    }
    {
        qx::flags<EFlags> flags = EFlags::Second;
        Check(flags, EFlags::First, EFlags::Second, EFlags::Third);
    }
    {
        qx::flags<EFlags> flags1(EFlags::Second);
        qx::flags<EFlags> flags2(flags1);
        Check(flags2, EFlags::First, EFlags::Second, EFlags::Third);
    }
    {
        qx::flags<EFlags> flags1(EFlags::Second);
        qx::flags<EFlags> flags2 = flags1;
        Check(flags2, EFlags::First, EFlags::Second, EFlags::Third);
    }
    {
        qx::flags<EFlags> flags(EFlags::Second);
        Check(flags, qx::flags(EFlags::First), qx::flags(EFlags::Second), qx::flags(EFlags::Third));
    }
    {
        qx::flags<EFlags> flags = EFlags::Second;
        Check(flags, qx::flags(EFlags::First), qx::flags(EFlags::Second), qx::flags(EFlags::Third));
    }
    {
        qx::flags<EFlags> flags1(EFlags::Second);
        qx::flags<EFlags> flags2(flags1);
        Check(flags2, qx::flags(EFlags::First), qx::flags(EFlags::Second), qx::flags(EFlags::Third));
    }
    {
        qx::flags<EFlags> flags1(EFlags::Second);
        qx::flags<EFlags> flags2 = flags1;
        Check(flags2, qx::flags(EFlags::First), qx::flags(EFlags::Second), qx::flags(EFlags::Third));
    }
}

TEST(flags, actions)
{
    qx::flags<EFlags> flags;
    EXPECT_FALSE(flags.contains(EFlags::First));
    EXPECT_FALSE(flags.contains(EFlags::Second));
    EXPECT_FALSE(flags.contains(EFlags::Third));
    EXPECT_FALSE(flags.contains(EFlags::Fourth));
    EXPECT_FALSE(flags.contains_all(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));
    EXPECT_FALSE(flags.contains_any(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));

    flags.add(EFlags::First);
    EXPECT_TRUE(flags.contains(EFlags::First));
    EXPECT_FALSE(flags.contains(EFlags::Second));
    EXPECT_FALSE(flags.contains(EFlags::Third));
    EXPECT_FALSE(flags.contains(EFlags::Fourth));
    EXPECT_FALSE(flags.contains_all(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));
    EXPECT_TRUE(flags.contains_any(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));

    flags.add(EFlags::Second);
    EXPECT_TRUE(flags.contains(EFlags::First));
    EXPECT_TRUE(flags.contains(EFlags::Second));
    EXPECT_FALSE(flags.contains(EFlags::Third));
    EXPECT_FALSE(flags.contains(EFlags::Fourth));
    EXPECT_FALSE(flags.contains_all(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));
    EXPECT_TRUE(flags.contains_any(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));

    flags.add(EFlags::Third, EFlags::Fourth);
    EXPECT_TRUE(flags.contains(EFlags::First));
    EXPECT_TRUE(flags.contains(EFlags::Second));
    EXPECT_TRUE(flags.contains(EFlags::Third));
    EXPECT_TRUE(flags.contains(EFlags::Fourth));
    EXPECT_TRUE(flags.contains_all(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));
    EXPECT_TRUE(flags.contains_any(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));

    flags.remove(EFlags::First);
    EXPECT_FALSE(flags.contains(EFlags::First));
    EXPECT_TRUE(flags.contains(EFlags::Second));
    EXPECT_TRUE(flags.contains(EFlags::Third));
    EXPECT_TRUE(flags.contains(EFlags::Fourth));
    EXPECT_FALSE(flags.contains_all(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));
    EXPECT_TRUE(flags.contains_any(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));

    flags.remove(EFlags::Second);
    EXPECT_FALSE(flags.contains(EFlags::First));
    EXPECT_FALSE(flags.contains(EFlags::Second));
    EXPECT_TRUE(flags.contains(EFlags::Third));
    EXPECT_TRUE(flags.contains(EFlags::Fourth));
    EXPECT_FALSE(flags.contains_all(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));
    EXPECT_TRUE(flags.contains_any(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));

    flags.remove(EFlags::Third, EFlags::Fourth);
    EXPECT_FALSE(flags.contains(EFlags::First));
    EXPECT_FALSE(flags.contains(EFlags::Second));
    EXPECT_FALSE(flags.contains(EFlags::Third));
    EXPECT_FALSE(flags.contains(EFlags::Fourth));
    EXPECT_FALSE(flags.contains_all(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));
    EXPECT_FALSE(flags.contains_any(EFlags::First, EFlags::Second, EFlags::Third, EFlags::Fourth));
}
