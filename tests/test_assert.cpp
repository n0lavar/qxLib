/**

    @file      test_assert.cpp
    @author    Khrapov
    @date      29.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_assert.cpp

#define QX_ENABLE_ASSERTS     1
#define QX_ENABLE_DEBUG_BREAK 1

#include <qx/macros/assert.h>

QX_PUSH_SUPPRESS_MSVC_WARNINGS(4702)

void Foo()
{
}

TEST(qx_assert, expect_macro_compilation)
{
    return;

    QX_EXPECT(false);

    if (false)
        QX_EXPECT(false);

    if (false)
        QX_EXPECT(false);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT(false);

    if (false)
    {
        QX_EXPECT(false);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT(false);
        Foo();
    }
}


TEST(qx_assert, expect_f_macro_compilation)
{
    return;

    QX_EXPECT_F(false, "msg %d", 41);

    if (false)
        QX_EXPECT_F(false, "msg %d", 41);

    if (false)
        QX_EXPECT_F(false, "msg %d", 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_F(false, "msg %d", 41);

    if (false)
    {
        QX_EXPECT_F(false, "msg %d", 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_F(false, "msg %d", 41);
        Foo();
    }
}

TEST(qx_assert, expect_cf_macro_compilation)
{
    return;

    QX_EXPECT_CF(false, CatAssert, "msg %d", 41);

    if (false)
        QX_EXPECT_CF(false, CatAssert, "msg %d", 41);

    if (false)
        QX_EXPECT_CF(false, CatAssert, "msg %d", 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_CF(false, CatAssert, "msg %d", 41);

    if (false)
    {
        QX_EXPECT_CF(false, CatAssert, "msg %d", 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_CF(false, CatAssert, "msg %d", 41);
        Foo();
    }
}

TEST(qx_assert, expect_c_macro_compilation)
{
    return;

    QX_EXPECT_C(false, CatAssert);

    if (false)
        QX_EXPECT_C(false, CatAssert);

    if (false)
        QX_EXPECT_C(false, CatAssert);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_C(false, CatAssert);

    if (false)
    {
        QX_EXPECT_C(false, CatAssert);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_C(false, CatAssert);
        Foo();
    }
}

TEST(qx_assert, expect_no_entry_macro_compilation)
{
    return;

    QX_EXPECT_NO_ENTRY();

    if (false)
        QX_EXPECT_NO_ENTRY();

    if (false)
        QX_EXPECT_NO_ENTRY();
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_NO_ENTRY();

    if (false)
    {
        QX_EXPECT_NO_ENTRY();
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_NO_ENTRY();
        Foo();
    }
}

TEST(qx_assert, expect_no_entry_f_macro_compilation)
{
    return;

    QX_EXPECT_NO_ENTRY_F("msg %d", 41);

    if (false)
        QX_EXPECT_NO_ENTRY_F("msg %d", 41);

    if (false)
        QX_EXPECT_NO_ENTRY_F("msg %d", 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_NO_ENTRY_F("msg %d", 41);

    if (false)
    {
        QX_EXPECT_NO_ENTRY_F("msg %d", 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_NO_ENTRY_F("msg %d", 41);
        Foo();
    }
}

TEST(qx_assert, expect_no_entry_Cf_macro_compilation)
{
    return;

    QX_EXPECT_NO_ENTRY_CF(CatAssert, "msg %d", 41);

    if (false)
        QX_EXPECT_NO_ENTRY_CF(CatAssert, "msg %d", 41);

    if (false)
        QX_EXPECT_NO_ENTRY_CF(CatAssert, "msg %d", 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_NO_ENTRY_CF(CatAssert, "msg %d", 41);

    if (false)
    {
        QX_EXPECT_NO_ENTRY_CF(CatAssert, "msg %d", 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_NO_ENTRY_CF(CatAssert, "msg %d", 41);
        Foo();
    }
}

TEST(qx_assert, expect_no_entry_C_macro_compilation)
{
    return;

    QX_EXPECT_NO_ENTRY_C(CatAssert);

    if (false)
        QX_EXPECT_NO_ENTRY_C(CatAssert);

    if (false)
        QX_EXPECT_NO_ENTRY_C(CatAssert);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_NO_ENTRY_C(CatAssert);

    if (false)
    {
        QX_EXPECT_NO_ENTRY_C(CatAssert);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_NO_ENTRY_C(CatAssert);
        Foo();
    }
}

TEST(qx_assert, expect_continue_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_CONTINUE(false);

        if (false)
            QX_EXPECT_CONTINUE(false);

        if (false)
            QX_EXPECT_CONTINUE(false);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_CONTINUE(false);

        if (false)
        {
            QX_EXPECT_CONTINUE(false);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_CONTINUE(false);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_continue_f_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_CONTINUE_F(false, "msg %d", 41);

        if (false)
            QX_EXPECT_CONTINUE_F(false, "msg %d", 41);

        if (false)
            QX_EXPECT_CONTINUE_F(false, "msg %d", 41);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_CONTINUE_F(false, "msg %d", 41);

        if (false)
        {
            QX_EXPECT_CONTINUE_F(false, "msg %d", 41);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_CONTINUE_F(false, "msg %d", 41);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_continue_cf_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_CONTINUE_CF(false, CatAssert, "msg %d", 41);

        if (false)
            QX_EXPECT_CONTINUE_CF(false, CatAssert, "msg %d", 41);

        if (false)
            QX_EXPECT_CONTINUE_CF(false, CatAssert, "msg %d", 41);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_CONTINUE_CF(false, CatAssert, "msg %d", 41);

        if (false)
        {
            QX_EXPECT_CONTINUE_CF(false, CatAssert, "msg %d", 41);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_CONTINUE_CF(false, CatAssert, "msg %d", 41);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_continue_c_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_CONTINUE_C(false, CatAssert);

        if (false)
            QX_EXPECT_CONTINUE_C(false, CatAssert);

        if (false)
            QX_EXPECT_CONTINUE_C(false, CatAssert);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_CONTINUE_C(false, CatAssert);

        if (false)
        {
            QX_EXPECT_CONTINUE_C(false, CatAssert);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_CONTINUE_C(false, CatAssert);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_break_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_BREAK(false);

        if (false)
            QX_EXPECT_BREAK(false);

        if (false)
            QX_EXPECT_BREAK(false);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_BREAK(false);

        if (false)
        {
            QX_EXPECT_BREAK(false);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_BREAK(false);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_break_f_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_BREAK_F(false, "msg %d", 41);

        if (false)
            QX_EXPECT_BREAK_F(false, "msg %d", 41);

        if (false)
            QX_EXPECT_BREAK_F(false, "msg %d", 41);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_BREAK_F(false, "msg %d", 41);

        if (false)
        {
            QX_EXPECT_BREAK_F(false, "msg %d", 41);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_BREAK_F(false, "msg %d", 41);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_break_cf_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_BREAK_CF(false, CatAssert, "msg %d", 41);

        if (false)
            QX_EXPECT_BREAK_CF(false, CatAssert, "msg %d", 41);

        if (false)
            QX_EXPECT_BREAK_CF(false, CatAssert, "msg %d", 41);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_BREAK_CF(false, CatAssert, "msg %d", 41);

        if (false)
        {
            QX_EXPECT_BREAK_CF(false, CatAssert, "msg %d", 41);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_BREAK_CF(false, CatAssert, "msg %d", 41);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_break_c_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_BREAK_C(false, CatAssert);

        if (false)
            QX_EXPECT_BREAK_C(false, CatAssert);

        if (false)
            QX_EXPECT_BREAK_C(false, CatAssert);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_BREAK_C(false, CatAssert);

        if (false)
        {
            QX_EXPECT_BREAK_C(false, CatAssert);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_BREAK_C(false, CatAssert);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, assert_macro_compilation)
{
    return;

    QX_ASSERT(false);

    if (false)
        QX_ASSERT(false);

    if (false)
        QX_ASSERT(false);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT(false);

    if (false)
    {
        QX_ASSERT(false);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT(false);
        Foo();
    }
}

TEST(qx_assert, assert_f_macro_compilation)
{
    return;

    QX_ASSERT_F(false, "msg %d", 41);

    if (false)
        QX_ASSERT_F(false, "msg %d", 41);

    if (false)
        QX_ASSERT_F(false, "msg %d", 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_F(false, "msg %d", 41);

    if (false)
    {
        QX_ASSERT_F(false, "msg %d", 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_F(false, "msg %d", 41);
        Foo();
    }
}

TEST(qx_assert, assert_cf_macro_compilation)
{
    return;

    QX_ASSERT_CF(false, CatAssert, "msg %d", 41);

    if (false)
        QX_ASSERT_CF(false, CatAssert, "msg %d", 41);

    if (false)
        QX_ASSERT_CF(false, CatAssert, "msg %d", 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_CF(false, CatAssert, "msg %d", 41);

    if (false)
    {
        QX_ASSERT_CF(false, CatAssert, "msg %d", 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_CF(false, CatAssert, "msg %d", 41);
        Foo();
    }
}

TEST(qx_assert, assert_c_macro_compilation)
{
    return;

    QX_ASSERT_C(false, CatAssert);

    if (false)
        QX_ASSERT_C(false, CatAssert);

    if (false)
        QX_ASSERT_C(false, CatAssert);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_C(false, CatAssert);

    if (false)
    {
        QX_ASSERT_C(false, CatAssert);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_C(false, CatAssert);
        Foo();
    }
}

TEST(qx_assert, assert_no_entry_f_macro_compilation)
{
    return;

    QX_ASSERT_NO_ENTRY_F("msg %d", 41);

    if (false)
        QX_ASSERT_NO_ENTRY_F("msg %d", 41);

    if (false)
        QX_ASSERT_NO_ENTRY_F("msg %d", 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_NO_ENTRY_F("msg %d", 41);

    if (false)
    {
        QX_ASSERT_NO_ENTRY_F("msg %d", 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_NO_ENTRY_F("msg %d", 41);
        Foo();
    }
}

TEST(qx_assert, assert_no_entry_cf_macro_compilation)
{
    return;

    QX_ASSERT_NO_ENTRY_CF(CatAssert, "msg %d", 41);

    if (false)
        QX_ASSERT_NO_ENTRY_CF(CatAssert, "msg %d", 41);

    if (false)
        QX_ASSERT_NO_ENTRY_CF(CatAssert, "msg %d", 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_NO_ENTRY_CF(CatAssert, "msg %d", 41);

    if (false)
    {
        QX_ASSERT_NO_ENTRY_CF(CatAssert, "msg %d", 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_NO_ENTRY_CF(CatAssert, "msg %d", 41);
        Foo();
    }
}

TEST(qx_assert, assert_no_entry_c_macro_compilation)
{
    return;

    QX_ASSERT_NO_ENTRY_C(CatAssert);

    if (false)
        QX_ASSERT_NO_ENTRY_C(CatAssert);

    if (false)
        QX_ASSERT_NO_ENTRY_C(CatAssert);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_NO_ENTRY_C(CatAssert);

    if (false)
    {
        QX_ASSERT_NO_ENTRY_C(CatAssert);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_NO_ENTRY_C(CatAssert);
        Foo();
    }
}

TEST(qx_assert, assert_no_entry_macro_compilation)
{
    return;

    QX_ASSERT_NO_ENTRY();

    if (false)
        QX_ASSERT_NO_ENTRY();

    if (false)
        QX_ASSERT_NO_ENTRY();
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_NO_ENTRY();

    if (false)
    {
        QX_ASSERT_NO_ENTRY();
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_NO_ENTRY();
        Foo();
    }
}

TEST(qx_assert, expect_return_macro_compilation)
{
    return;

    QX_EXPECT_RETURN(false);

    if (false)
        QX_EXPECT_RETURN(false);

    if (false)
        Foo();
    else
        QX_EXPECT_RETURN(false);

    if (false)
        QX_EXPECT_RETURN(false);
    else
        Foo();

    if (false)
    {
        QX_EXPECT_RETURN(false);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_RETURN(false);
        Foo();
    }
}

TEST(qx_assert, expect_return_cf_macro_compilation)
{
    return;

    QX_EXPECT_RETURN_CF(false, CatAssert, "");

    if (false)
        QX_EXPECT_RETURN_CF(false, CatAssert, "");

    if (false)
        Foo();
    else
        QX_EXPECT_RETURN_CF(false, CatAssert, "");

    if (false)
        QX_EXPECT_RETURN_CF(false, CatAssert, "");
    else
        Foo();

    if (false)
    {
        QX_EXPECT_RETURN_CF(false, CatAssert, "");
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_RETURN_CF(false, CatAssert, "");
        Foo();
    }
}

TEST(qx_assert, expect_return_f_macro_compilation)
{
    return;

    QX_EXPECT_RETURN_F(false, "");

    if (false)
        QX_EXPECT_RETURN_F(false, "");

    if (false)
        Foo();
    else
        QX_EXPECT_RETURN_F(false, "");

    if (false)
        QX_EXPECT_RETURN_F(false, "");
    else
        Foo();

    if (false)
    {
        QX_EXPECT_RETURN_F(false, "");
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_RETURN_F(false, "");
        Foo();
    }
}

TEST(qx_assert, expect_return_c_macro_compilation)
{
    return;

    QX_EXPECT_RETURN_C(false, CatAssert);

    if (false)
        QX_EXPECT_RETURN_C(false, CatAssert);

    if (false)
        Foo();
    else
        QX_EXPECT_RETURN_C(false, CatAssert);

    if (false)
        QX_EXPECT_RETURN_C(false, CatAssert);
    else
        Foo();

    if (false)
    {
        QX_EXPECT_RETURN_C(false, CatAssert);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_RETURN_C(false, CatAssert);
        Foo();
    }
}

QX_POP_SUPPRESS_WARNINGS

TEST(qx_assert, assert_macros)
{
    EXPECT_DEATH({ QX_ASSERT(0); }, "");
    EXPECT_DEATH({ QX_ASSERT_F(0, ""); }, "");
    EXPECT_DEATH({ QX_ASSERT_C(0, CatAssert); }, "");
    EXPECT_DEATH({ QX_ASSERT_CF(0, CatAssert, ""); }, "");
    EXPECT_DEATH({ QX_ASSERT_NO_ENTRY(); }, "");
    EXPECT_DEATH({ QX_ASSERT_NO_ENTRY_F("%d", 42); }, "");
    EXPECT_DEATH({ QX_ASSERT_NO_ENTRY_C(CatAssert); }, "");
    EXPECT_DEATH({ QX_ASSERT_NO_ENTRY_CF(CatAssert, "%d", 42); }, "");
}
