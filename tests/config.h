//============================================================================
//
//!\file                           config.h
//
//!\brief       configure testing
//!\details     ~
//
//!\author      Khrapov
//!\date        8.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#define QX_TEST_SORT 0
#define QX_TEST_NUMERICAL 0
#define QX_TEST_FUNCTIONAL 1

#define QX_BENCH_SORT 0

#include <qx/other/logger.h>
#define PROCESS_ASSERT(statement) _TR_ASSERT(STRINGIFY(statement), "")
#define PROCESS_ASSERT_MSG(statement, msg, ...) _TR_ASSERT(STRINGIFY(statement), msg, # __VA_ARGS__)
