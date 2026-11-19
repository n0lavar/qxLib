/**

    @file      apply.h
    @details   Initially taken from https://github.com/swansontec/map-macro
    @author    Khrapov
    @date      24.09.2023
    @copyright (c) Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/macros/config.h>

#define QX_DETAILS_APPLY_EVAL0(...) __VA_ARGS__
#define QX_DETAILS_APPLY_EVAL1(...) QX_DETAILS_APPLY_EVAL0(QX_DETAILS_APPLY_EVAL0(QX_DETAILS_APPLY_EVAL0(__VA_ARGS__)))
#define QX_DETAILS_APPLY_EVAL2(...) QX_DETAILS_APPLY_EVAL1(QX_DETAILS_APPLY_EVAL1(QX_DETAILS_APPLY_EVAL1(__VA_ARGS__)))
#define QX_DETAILS_APPLY_EVAL3(...) QX_DETAILS_APPLY_EVAL2(QX_DETAILS_APPLY_EVAL2(QX_DETAILS_APPLY_EVAL2(__VA_ARGS__)))
#define QX_DETAILS_APPLY_EVAL4(...) QX_DETAILS_APPLY_EVAL3(QX_DETAILS_APPLY_EVAL3(QX_DETAILS_APPLY_EVAL3(__VA_ARGS__)))
#define QX_DETAILS_APPLY_EVAL5(...) QX_DETAILS_APPLY_EVAL4(QX_DETAILS_APPLY_EVAL4(QX_DETAILS_APPLY_EVAL4(__VA_ARGS__)))

#if QX_MSVC_COMPATIBLE
    // MSVC needs more evaluations
    #define QX_DETAILS_APPLY_EVAL6(...) \
        QX_DETAILS_APPLY_EVAL5(QX_DETAILS_APPLY_EVAL5(QX_DETAILS_APPLY_EVAL5(__VA_ARGS__)))
    #define QX_DETAILS_APPLY_EVAL(...) QX_DETAILS_APPLY_EVAL6(QX_DETAILS_APPLY_EVAL6(__VA_ARGS__))
#else
    #define QX_DETAILS_APPLY_EVAL(...) QX_DETAILS_APPLY_EVAL5(__VA_ARGS__)
#endif

#define QX_DETAILS_APPLY_MAP_END(...)
#define QX_DETAILS_APPLY_MAP_OUT

#define QX_DETAILS_APPLY_EMPTY()
#define QX_DETAILS_APPLY_DEFER(id) id QX_DETAILS_APPLY_EMPTY()

#define QX_DETAILS_APPLY_MAP_GET_END2()             0, QX_DETAILS_APPLY_MAP_END
#define QX_DETAILS_APPLY_MAP_GET_END1(...)          QX_DETAILS_APPLY_MAP_GET_END2
#define QX_DETAILS_APPLY_MAP_GET_END(...)           QX_DETAILS_APPLY_MAP_GET_END1
#define QX_DETAILS_APPLY_MAP_NEXT0(test, next, ...) next QX_DETAILS_APPLY_MAP_OUT
#define QX_DETAILS_APPLY_MAP_NEXT1(test, next)      QX_DETAILS_APPLY_DEFER(QX_DETAILS_APPLY_MAP_NEXT0)(test, next, 0)
#define QX_DETAILS_APPLY_MAP_NEXT(test, next)       QX_DETAILS_APPLY_MAP_NEXT1(QX_DETAILS_APPLY_MAP_GET_END test, next)

#define QX_DETAILS_APPLY_MAP_COMMA0(f, x, peek, ...) \
    , f(x) QX_DETAILS_APPLY_DEFER(QX_DETAILS_APPLY_MAP_NEXT(peek, QX_DETAILS_APPLY_MAP_COMMA1))(f, peek, __VA_ARGS__)
#define QX_DETAILS_APPLY_MAP_COMMA1(f, x, peek, ...) \
    , f(x) QX_DETAILS_APPLY_DEFER(QX_DETAILS_APPLY_MAP_NEXT(peek, QX_DETAILS_APPLY_MAP_COMMA0))(f, peek, __VA_ARGS__)
#define QX_DETAILS_APPLY_MAP_COMMA2(f, x, peek, ...) \
    f(x) QX_DETAILS_APPLY_DEFER(QX_DETAILS_APPLY_MAP_NEXT(peek, QX_DETAILS_APPLY_MAP_COMMA1))(f, peek, __VA_ARGS__)

#define QX_DETAILS_APPLY_MAP_SEMICOLON0(f, x, peek, ...) \
    ;                                                    \
    f(x) QX_DETAILS_APPLY_DEFER(QX_DETAILS_APPLY_MAP_NEXT(peek, QX_DETAILS_APPLY_MAP_SEMICOLON1))(f, peek, __VA_ARGS__)
#define QX_DETAILS_APPLY_MAP_SEMICOLON1(f, x, peek, ...) \
    ;                                                    \
    f(x) QX_DETAILS_APPLY_DEFER(QX_DETAILS_APPLY_MAP_NEXT(peek, QX_DETAILS_APPLY_MAP_SEMICOLON0))(f, peek, __VA_ARGS__)
#define QX_DETAILS_APPLY_MAP_SEMICOLON2(f, x, peek, ...) \
    f(x) QX_DETAILS_APPLY_DEFER(QX_DETAILS_APPLY_MAP_NEXT(peek, QX_DETAILS_APPLY_MAP_SEMICOLON1))(f, peek, __VA_ARGS__)

/**
    @def   QX_APPLY_COMMA
    @brief Applies the function macro `f` to each of the remaining parameters and inserts commas between the results:
           QX_APPLY_SPACE(foo, 1, 2, 3) -> foo(1), foo(2), foo(3)
    @param f   - function macro
    @param ... - parameters to apply
**/
#define QX_APPLY_COMMA(f, ...) \
    QX_DETAILS_APPLY_EVAL(QX_DETAILS_APPLY_MAP_COMMA2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
    @def   QX_APPLY_SEMICOLON
    @brief Applies the function macro `f` to each of the remaining parameters and inserts semicolons between the results:
           QX_APPLY_SPACE(foo, 1, 2, 3) -> foo(1); foo(2); foo(3)
    @param f   - function macro
    @param ... - parameters to apply
**/
#define QX_APPLY_SEMICOLON(f, ...) \
    QX_DETAILS_APPLY_EVAL(QX_DETAILS_APPLY_MAP_SEMICOLON2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
