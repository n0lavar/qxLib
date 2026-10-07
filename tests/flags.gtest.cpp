#include <common.h>

#include <qx/containers/flags.h>

//V_EXCLUDE_PATH *.gtest.cpp

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

TEST(flags, shifts)
{
    const auto check = []<class integer_t>()
    {
        enum class bits : integer_t
        {
            first = 1
        };
        using unsigned_type              = std::make_unsigned_t<integer_t>;
        constexpr size_t          nWidth = std::numeric_limits<unsigned_type>::digits;
        constexpr qx::flags<bits> initial(bits::first);

        static_assert((initial << 1).to_integer() == 2);
        static_assert(((initial << 1) >> 1).to_integer() == 1);
        static_assert((initial << nWidth).to_integer() == 0);
        static_assert((initial >> nWidth).to_integer() == 0);

        auto value = initial;
        value.shift_left(1);
        EXPECT_EQ(value.to_integer(), 2);
        value.shift_right(1);
        EXPECT_EQ(value, initial);
        value <<= nWidth - 1;
        EXPECT_EQ(static_cast<unsigned_type>(value.to_integer()), unsigned_type { 1 } << (nWidth - 1));
        value >>= nWidth - 1;
        EXPECT_EQ(value, initial);
        EXPECT_EQ(initial.to_integer(), 1);
        EXPECT_EQ((initial << 0), initial);
        EXPECT_EQ((initial >> 0), initial);
        EXPECT_EQ((initial << std::numeric_limits<size_t>::max()).to_integer(), 0);
        EXPECT_EQ((initial >> std::numeric_limits<size_t>::max()).to_integer(), 0);
    };

    check.operator()<int8_t>();
    check.operator()<uint8_t>();
    check.operator()<int32_t>();
    check.operator()<uint32_t>();
    check.operator()<int64_t>();
    check.operator()<uint64_t>();
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
