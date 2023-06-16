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

QX_PUSH_SUPPRESS_MSVC_WARNINGS(4702);

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

    QX_EXPECT(false, QX_TEXT("msg {}"), 41);

    if (false)
        QX_EXPECT(false, QX_TEXT("msg {}"), 41);

    if (false)
        QX_EXPECT(false, QX_TEXT("msg {}"), 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT(false, QX_TEXT("msg {}"), 41);

    if (false)
    {
        QX_EXPECT(false, QX_TEXT("msg {}"), 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT(false, QX_TEXT("msg {}"), 41);
        Foo();
    }
}

TEST(qx_assert, expect_cf_macro_compilation)
{
    return;

    QX_EXPECT(false, CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
        QX_EXPECT(false, CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
        QX_EXPECT(false, CatDefault, QX_TEXT("msg {}"), 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT(false, CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
    {
        QX_EXPECT(false, CatDefault, QX_TEXT("msg {}"), 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT(false, CatDefault, QX_TEXT("msg {}"), 41);
        Foo();
    }
}

TEST(qx_assert, expect_c_macro_compilation)
{
    return;

    QX_EXPECT(false, CatDefault);

    if (false)
        QX_EXPECT(false, CatDefault);

    if (false)
        QX_EXPECT(false, CatDefault);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT(false, CatDefault);

    if (false)
    {
        QX_EXPECT(false, CatDefault);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT(false, CatDefault);
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

    QX_EXPECT_NO_ENTRY(QX_TEXT("msg {}"), 41);

    if (false)
        QX_EXPECT_NO_ENTRY(QX_TEXT("msg {}"), 41);

    if (false)
        QX_EXPECT_NO_ENTRY(QX_TEXT("msg {}"), 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_NO_ENTRY(QX_TEXT("msg {}"), 41);

    if (false)
    {
        QX_EXPECT_NO_ENTRY(QX_TEXT("msg {}"), 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_NO_ENTRY(QX_TEXT("msg {}"), 41);
        Foo();
    }
}

TEST(qx_assert, expect_no_entry_cf_macro_compilation)
{
    return;

    QX_EXPECT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
        QX_EXPECT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
        QX_EXPECT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
    {
        QX_EXPECT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);
        Foo();
    }
}

TEST(qx_assert, expect_no_entry_c_macro_compilation)
{
    return;

    QX_EXPECT_NO_ENTRY(CatDefault);

    if (false)
        QX_EXPECT_NO_ENTRY(CatDefault);

    if (false)
        QX_EXPECT_NO_ENTRY(CatDefault);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_EXPECT_NO_ENTRY(CatDefault);

    if (false)
    {
        QX_EXPECT_NO_ENTRY(CatDefault);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_NO_ENTRY(CatDefault);
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
        QX_EXPECT_CONTINUE(false, QX_TEXT("msg {}"), 41);

        if (false)
            QX_EXPECT_CONTINUE(false, QX_TEXT("msg {}"), 41);

        if (false)
            QX_EXPECT_CONTINUE(false, QX_TEXT("msg {}"), 41);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_CONTINUE(false, QX_TEXT("msg {}"), 41);

        if (false)
        {
            QX_EXPECT_CONTINUE(false, QX_TEXT("msg {}"), 41);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_CONTINUE(false, QX_TEXT("msg {}"), 41);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_continue_cf_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_CONTINUE(false, CatDefault, QX_TEXT("msg {}"), 41);

        if (false)
            QX_EXPECT_CONTINUE(false, CatDefault, QX_TEXT("msg {}"), 41);

        if (false)
            QX_EXPECT_CONTINUE(false, CatDefault, QX_TEXT("msg {}"), 41);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_CONTINUE(false, CatDefault, QX_TEXT("msg {}"), 41);

        if (false)
        {
            QX_EXPECT_CONTINUE(false, CatDefault, QX_TEXT("msg {}"), 41);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_CONTINUE(false, CatDefault, QX_TEXT("msg {}"), 41);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_continue_c_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_CONTINUE(false, CatDefault);

        if (false)
            QX_EXPECT_CONTINUE(false, CatDefault);

        if (false)
            QX_EXPECT_CONTINUE(false, CatDefault);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_CONTINUE(false, CatDefault);

        if (false)
        {
            QX_EXPECT_CONTINUE(false, CatDefault);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_CONTINUE(false, CatDefault);
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
        QX_EXPECT_BREAK(false, QX_TEXT("msg {}"), 41);

        if (false)
            QX_EXPECT_BREAK(false, QX_TEXT("msg {}"), 41);

        if (false)
            QX_EXPECT_BREAK(false, QX_TEXT("msg {}"), 41);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_BREAK(false, QX_TEXT("msg {}"), 41);

        if (false)
        {
            QX_EXPECT_BREAK(false, QX_TEXT("msg {}"), 41);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_BREAK(false, QX_TEXT("msg {}"), 41);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_break_cf_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_BREAK(false, CatDefault, QX_TEXT("msg {}"), 41);

        if (false)
            QX_EXPECT_BREAK(false, CatDefault, QX_TEXT("msg {}"), 41);

        if (false)
            QX_EXPECT_BREAK(false, CatDefault, QX_TEXT("msg {}"), 41);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_BREAK(false, CatDefault, QX_TEXT("msg {}"), 41);

        if (false)
        {
            QX_EXPECT_BREAK(false, CatDefault, QX_TEXT("msg {}"), 41);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_BREAK(false, CatDefault, QX_TEXT("msg {}"), 41);
            Foo();
        }
    } while (false);
}

TEST(qx_assert, expect_break_c_macro_compilation)
{
    return;

    do
    {
        QX_EXPECT_BREAK(false, CatDefault);

        if (false)
            QX_EXPECT_BREAK(false, CatDefault);

        if (false)
            QX_EXPECT_BREAK(false, CatDefault);
        else
            Foo();

        if (false)
            Foo();
        else
            QX_EXPECT_BREAK(false, CatDefault);

        if (false)
        {
            QX_EXPECT_BREAK(false, CatDefault);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_BREAK(false, CatDefault);
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

    QX_ASSERT(false, QX_TEXT("msg {}"), 41);

    if (false)
        QX_ASSERT(false, QX_TEXT("msg {}"), 41);

    if (false)
        QX_ASSERT(false, QX_TEXT("msg {}"), 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT(false, QX_TEXT("msg {}"), 41);

    if (false)
    {
        QX_ASSERT(false, QX_TEXT("msg {}"), 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT(false, QX_TEXT("msg {}"), 41);
        Foo();
    }
}

TEST(qx_assert, assert_cf_macro_compilation)
{
    return;

    QX_ASSERT(false, CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
        QX_ASSERT(false, CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
        QX_ASSERT(false, CatDefault, QX_TEXT("msg {}"), 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT(false, CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
    {
        QX_ASSERT(false, CatDefault, QX_TEXT("msg {}"), 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT(false, CatDefault, QX_TEXT("msg {}"), 41);
        Foo();
    }
}

TEST(qx_assert, assert_c_macro_compilation)
{
    return;

    QX_ASSERT(false, CatDefault);

    if (false)
        QX_ASSERT(false, CatDefault);

    if (false)
        QX_ASSERT(false, CatDefault);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT(false, CatDefault);

    if (false)
    {
        QX_ASSERT(false, CatDefault);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT(false, CatDefault);
        Foo();
    }
}

TEST(qx_assert, assert_no_entry_f_macro_compilation)
{
    return;

    QX_ASSERT_NO_ENTRY(QX_TEXT("msg {}"), 41);

    if (false)
        QX_ASSERT_NO_ENTRY(QX_TEXT("msg {}"), 41);

    if (false)
        QX_ASSERT_NO_ENTRY(QX_TEXT("msg {}"), 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_NO_ENTRY(QX_TEXT("msg {}"), 41);

    if (false)
    {
        QX_ASSERT_NO_ENTRY(QX_TEXT("msg {}"), 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_NO_ENTRY(QX_TEXT("msg {}"), 41);
        Foo();
    }
}

TEST(qx_assert, assert_no_entry_cf_macro_compilation)
{
    return;

    QX_ASSERT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
        QX_ASSERT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
        QX_ASSERT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);

    if (false)
    {
        QX_ASSERT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_NO_ENTRY(CatDefault, QX_TEXT("msg {}"), 41);
        Foo();
    }
}

TEST(qx_assert, assert_no_entry_c_macro_compilation)
{
    return;

    QX_ASSERT_NO_ENTRY(CatDefault);

    if (false)
        QX_ASSERT_NO_ENTRY(CatDefault);

    if (false)
        QX_ASSERT_NO_ENTRY(CatDefault);
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_NO_ENTRY(CatDefault);

    if (false)
    {
        QX_ASSERT_NO_ENTRY(CatDefault);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_NO_ENTRY(CatDefault);
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

TEST(qx_assert, expect_return_void_macro_compilation)
{
    return;

    QX_EXPECT_RETURN_VOID(false);

    if (false)
        QX_EXPECT_RETURN_VOID(false);

    if (false)
        Foo();
    else
        QX_EXPECT_RETURN_VOID(false);

    if (false)
        QX_EXPECT_RETURN_VOID(false);
    else
        Foo();

    if (false)
    {
        QX_EXPECT_RETURN_VOID(false);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_RETURN_VOID(false);
        Foo();
    }
}

TEST(qx_assert, expect_return_cf_void_macro_compilation)
{
    return;

    QX_EXPECT_RETURN_VOID(false, CatDefault, QX_TEXT(""));

    if (false)
        QX_EXPECT_RETURN_VOID(false, CatDefault, QX_TEXT(""));

    if (false)
        Foo();
    else
        QX_EXPECT_RETURN_VOID(false, CatDefault, QX_TEXT(""));

    if (false)
        QX_EXPECT_RETURN_VOID(false, CatDefault, QX_TEXT(""));
    else
        Foo();

    if (false)
    {
        QX_EXPECT_RETURN_VOID(false, CatDefault, QX_TEXT(""));
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_RETURN_VOID(false, CatDefault, QX_TEXT(""));
        Foo();
    }
}

TEST(qx_assert, expect_return_f_void_macro_compilation)
{
    return;

    QX_EXPECT_RETURN_VOID(false, QX_TEXT(""));

    if (false)
        QX_EXPECT_RETURN_VOID(false, QX_TEXT(""));

    if (false)
        Foo();
    else
        QX_EXPECT_RETURN_VOID(false, QX_TEXT(""));

    if (false)
        QX_EXPECT_RETURN_VOID(false, QX_TEXT(""));
    else
        Foo();

    if (false)
    {
        QX_EXPECT_RETURN_VOID(false, QX_TEXT(""));
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_RETURN_VOID(false, QX_TEXT(""));
        Foo();
    }
}

TEST(qx_assert, expect_return_c_void_macro_compilation)
{
    return;

    QX_EXPECT_RETURN_VOID(false, CatDefault);

    if (false)
        QX_EXPECT_RETURN_VOID(false, CatDefault);

    if (false)
        Foo();
    else
        QX_EXPECT_RETURN_VOID(false, CatDefault);

    if (false)
        QX_EXPECT_RETURN_VOID(false, CatDefault);
    else
        Foo();

    if (false)
    {
        QX_EXPECT_RETURN_VOID(false, CatDefault);
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_EXPECT_RETURN_VOID(false, CatDefault);
        Foo();
    }
}

TEST(qx_assert, expect_return_macro_compilation)
{
    return;

    auto Check = []()
    {
        QX_EXPECT_RETURN(false, 1);

        if (false)
            QX_EXPECT_RETURN(false, 1);

        if (false)
            Foo();
        else
            QX_EXPECT_RETURN(false, 1);

        if (false)
            QX_EXPECT_RETURN(false, 1);
        else
            Foo();

        if (false)
        {
            QX_EXPECT_RETURN(false, 1);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_RETURN(false, 1);
            Foo();
        }

        return 0;
    };

    Check();
}

TEST(qx_assert, expect_return_cf_macro_compilation)
{
    return;

    auto Check = []()
    {
        QX_EXPECT_RETURN(false, 1, CatDefault, QX_TEXT(""));

        if (false)
            QX_EXPECT_RETURN(false, 1, CatDefault, QX_TEXT(""));

        if (false)
            Foo();
        else
            QX_EXPECT_RETURN(false, 1, CatDefault, QX_TEXT(""));

        if (false)
            QX_EXPECT_RETURN(false, 1, CatDefault, QX_TEXT(""));
        else
            Foo();

        if (false)
        {
            QX_EXPECT_RETURN(false, 1, CatDefault, QX_TEXT(""));
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_RETURN(false, 1, CatDefault, QX_TEXT(""));
            Foo();
        }

        return 0;
    };

    Check();
}

TEST(qx_assert, expect_return_f_macro_compilation)
{
    return;

    auto Check = []()
    {
        QX_EXPECT_RETURN(false, 1, QX_TEXT(""));

        if (false)
            QX_EXPECT_RETURN(false, 1, QX_TEXT(""));

        if (false)
            Foo();
        else
            QX_EXPECT_RETURN(false, 1, QX_TEXT(""));

        if (false)
            QX_EXPECT_RETURN(false, 1, QX_TEXT(""));
        else
            Foo();

        if (false)
        {
            QX_EXPECT_RETURN(false, 1, QX_TEXT(""));
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_RETURN(false, 1, QX_TEXT(""));
            Foo();
        }

        return 0;
    };

    Check();
}

TEST(qx_assert, expect_return_c_macro_compilation)
{
    return;

    auto Check = []()
    {
        QX_EXPECT_RETURN(false, 1, CatDefault);

        if (false)
            QX_EXPECT_RETURN(false, 1, CatDefault);

        if (false)
            Foo();
        else
            QX_EXPECT_RETURN(false, 1, CatDefault);

        if (false)
            QX_EXPECT_RETURN(false, 1, CatDefault);
        else
            Foo();

        if (false)
        {
            QX_EXPECT_RETURN(false, 1, CatDefault);
            Foo();
        }

        if (false)
            Foo();
        else
        {
            QX_EXPECT_RETURN(false, 1, CatDefault);
            Foo();
        }

        return 0;
    };

    Check();
}

QX_POP_SUPPRESS_WARNINGS();

TEST(qx_assert, assert_macros)
{
    EXPECT_DEATH({ QX_ASSERT(0); }, "");
    EXPECT_DEATH({ QX_ASSERT(0, QX_TEXT("")); }, "");
    EXPECT_DEATH({ QX_ASSERT(0, CatDefault); }, "");
    EXPECT_DEATH({ QX_ASSERT(0, CatDefault, QX_TEXT("")); }, "");
    EXPECT_DEATH({ QX_ASSERT_NO_ENTRY(); }, "");
    EXPECT_DEATH({ QX_ASSERT_NO_ENTRY(QX_TEXT("{}"), 42); }, "");
    EXPECT_DEATH({ QX_ASSERT_NO_ENTRY(CatDefault); }, "");
    EXPECT_DEATH({ QX_ASSERT_NO_ENTRY(CatDefault, QX_TEXT("{}"), 42); }, "");
}
