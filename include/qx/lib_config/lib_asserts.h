/**

    @file      lib_asserts.h
    @brief     Contains lib assert macros
    @details   These macros should be used in lib only
    @details   ~
    @author    Khrapov
    @date      21.07.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/macros/assert.h>

#ifndef QX_LIB_EXPECT_MSG
    #define QX_LIB_EXPECT_MSG QX_EXPECT_MSG
#endif

#ifndef QX_LIB_ASSERT_MSG
    #define QX_LIB_ASSERT_MSG QX_ASSERT_MSG
#endif

#ifndef QX_LIB_EXPECT
    #define QX_LIB_EXPECT QX_EXPECT
#endif

#ifndef QX_LIB_ASSERT
    #define QX_LIB_ASSERT QX_ASSERT
#endif

#ifndef QX_LIB_EXPECT_NO_ENTRY
    #define QX_LIB_EXPECT_NO_ENTRY QX_EXPECT_NO_ENTRY
#endif

#ifndef QX_LIB_ASSERT_NO_ENTRY
    #define QX_LIB_ASSERT_NO_ENTRY QX_ASSERT_NO_ENTRY
#endif

#ifndef QX_LIB_EXPECT_RETURN
    #define QX_LIB_EXPECT_RETURN QX_EXPECT_RETURN
#endif

#ifndef QX_LIB_EXPECT_CONTINUE
    #define QX_LIB_EXPECT_CONTINUE QX_EXPECT_CONTINUE
#endif

#ifndef QX_LIB_EXPECT_BREAK
    #define QX_LIB_EXPECT_BREAK QX_EXPECT_BREAK
#endif
