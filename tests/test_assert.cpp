//==============================================================================
//
//!\file                        test_assert.cpp
//
//!\brief       Tests for assert macros
//!\details     ~
//
//!\author      Khrapov
//!\date        29.10.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_assert.cpp

#if QX_TEST_ASSERT

#define QX_ENABLE_ASSERTS 1
#define QX_ENABLE_DEBUG_BREAK 1

#include <qx/assert.h>

QX_PUSH_SUPPRESS_MSVC_WARNINGS(4702)

void Foo()
{
}

TEST(qx_assert, assert_macro)
{
    // we only want to check compilation
    // and dont want out test to be failed in SIGTRAP
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


TEST(qx_assert, assert_mgs_macro)
{
    // we only want to check compilation
    // and dont want out test to be failed in SIGTRAP
    return;

    QX_ASSERT_MSG(false, "msg");

    if (false)
        QX_ASSERT_MSG(false, "msg");

    if (false)
        QX_ASSERT_MSG(false, "msg");
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_MSG(false, "msg");

    if (false)
    {
        QX_ASSERT_MSG(false, "msg");
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_MSG(false, "msg");
        Foo();
    }
}

TEST(qx_assert, assert_not_impl_macro)
{
    // we only want to check compilation
    // and dont want out test to be failed in SIGTRAP
    return;

    QX_ASSERT_NOT_IMPL;

    if (false)
        QX_ASSERT_NOT_IMPL;

    if (false)
        QX_ASSERT_NOT_IMPL;
    else
        Foo();

    if (false)
        Foo();
    else
        QX_ASSERT_NOT_IMPL;

    if (false)
    {
        QX_ASSERT_NOT_IMPL;
        Foo();
    }

    if (false)
        Foo();
    else
    {
        QX_ASSERT_NOT_IMPL;
        Foo();
    }
}

QX_POP_SUPPRESS_WARNINGS

#endif
