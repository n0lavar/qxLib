/**

    @file      test_is_array_of_t.cpp
    @author    Khrapov
    @date      22.12.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

//V_EXCLUDE_PATH *test_is_array_of_t.cpp

#include <qx/meta/is_array_of_t.h>

#include <string>

static_assert(!qx::is_array_of_t_v<char, char>);
static_assert(!qx::is_array_of_t_v<float, char>);
static_assert(!qx::is_array_of_t_v<std::string, char>);
static_assert(!qx::is_array_of_t_v<void, char>);
static_assert(!qx::is_array_of_t_v<char, void>);

static_assert(!qx::is_array_of_t_v<char[], void>);
static_assert(!qx::is_array_of_t_v<char[], float>);
static_assert(!qx::is_array_of_t_v<const char[], float>);
static_assert(!qx::is_array_of_t_v<volatile char[], float>);
static_assert(!qx::is_array_of_t_v<const volatile char[], float>);

static_assert(!qx::is_array_of_t_v<char[42], float>);
static_assert(!qx::is_array_of_t_v<const char[42], float>);
static_assert(!qx::is_array_of_t_v<volatile char[42], float>);
static_assert(!qx::is_array_of_t_v<const volatile char[42], float>);

static_assert(!qx::is_array_of_t_v<char (&)[42], float>);
static_assert(!qx::is_array_of_t_v<const char (&)[42], float>);
static_assert(!qx::is_array_of_t_v<volatile char (&)[42], float>);
static_assert(!qx::is_array_of_t_v<const volatile char (&)[42], float>);

static_assert(qx::is_array_of_t_v<char[], char>);
static_assert(qx::is_array_of_t_v<const char[], char>);
static_assert(qx::is_array_of_t_v<volatile char[], char>);
static_assert(qx::is_array_of_t_v<const volatile char[], char>);

static_assert(qx::is_array_of_t_v<char[42], char>);
static_assert(qx::is_array_of_t_v<const char[42], char>);
static_assert(qx::is_array_of_t_v<volatile char[42], char>);
static_assert(qx::is_array_of_t_v<const volatile char[42], char>);

static_assert(qx::is_array_of_t_v<char (&)[42], char>);
static_assert(qx::is_array_of_t_v<const char (&)[42], char>);
static_assert(qx::is_array_of_t_v<volatile char (&)[42], char>);
static_assert(qx::is_array_of_t_v<const volatile char (&)[42], char>);
