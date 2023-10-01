/**

    @file      apply.h
    @details   Initially taken from https://github.com/swansontec/map-macro
    @author    Khrapov
    @date      24.09.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#define _QX_APPLY_EVAL0(...) __VA_ARGS__
#define _QX_APPLY_EVAL1(...) _QX_APPLY_EVAL0(_QX_APPLY_EVAL0(_QX_APPLY_EVAL0(__VA_ARGS__)))
#define _QX_APPLY_EVAL2(...) _QX_APPLY_EVAL1(_QX_APPLY_EVAL1(_QX_APPLY_EVAL1(__VA_ARGS__)))
#define _QX_APPLY_EVAL3(...) _QX_APPLY_EVAL2(_QX_APPLY_EVAL2(_QX_APPLY_EVAL2(__VA_ARGS__)))
#define _QX_APPLY_EVAL4(...) _QX_APPLY_EVAL3(_QX_APPLY_EVAL3(_QX_APPLY_EVAL3(__VA_ARGS__)))
#define _QX_APPLY_EVAL5(...) _QX_APPLY_EVAL4(_QX_APPLY_EVAL4(_QX_APPLY_EVAL4(__VA_ARGS__)))

#ifdef _MSC_VER
    // MSVC needs more evaluations
    #define _QX_APPLY_EVAL6(...) _QX_APPLY_EVAL5(_QX_APPLY_EVAL5(_QX_APPLY_EVAL5(__VA_ARGS__)))
    #define _QX_APPLY_EVAL(...)  _QX_APPLY_EVAL6(_QX_APPLY_EVAL6(__VA_ARGS__))
#else
    #define _QX_APPLY_EVAL(...) _QX_APPLY_EVAL5(__VA_ARGS__)
#endif

#define _QX_APPLY_MAP_END(...)
#define _QX_APPLY_MAP_OUT

#define _QX_APPLY_EMPTY()
#define _QX_APPLY_DEFER(id) id _QX_APPLY_EMPTY()

#define _QX_APPLY_MAP_GET_END2()             0, _QX_APPLY_MAP_END
#define _QX_APPLY_MAP_GET_END1(...)          _QX_APPLY_MAP_GET_END2
#define _QX_APPLY_MAP_GET_END(...)           _QX_APPLY_MAP_GET_END1
#define _QX_APPLY_MAP_NEXT0(test, next, ...) next _QX_APPLY_MAP_OUT
#define _QX_APPLY_MAP_NEXT1(test, next)      _QX_APPLY_DEFER(_QX_APPLY_MAP_NEXT0)(test, next, 0)
#define _QX_APPLY_MAP_NEXT(test, next)       _QX_APPLY_MAP_NEXT1(_QX_APPLY_MAP_GET_END test, next)

#define _QX_APPLY_MAP_COMMA0(f, x, peek, ...) \
    , f(x) _QX_APPLY_DEFER(_QX_APPLY_MAP_NEXT(peek, _QX_APPLY_MAP_COMMA1))(f, peek, __VA_ARGS__)
#define _QX_APPLY_MAP_COMMA1(f, x, peek, ...) \
    , f(x) _QX_APPLY_DEFER(_QX_APPLY_MAP_NEXT(peek, _QX_APPLY_MAP_COMMA0))(f, peek, __VA_ARGS__)
#define _QX_APPLY_MAP_COMMA2(f, x, peek, ...) \
    f(x) _QX_APPLY_DEFER(_QX_APPLY_MAP_NEXT(peek, _QX_APPLY_MAP_COMMA1))(f, peek, __VA_ARGS__)

#define _QX_APPLY_MAP_SEMICOLON0(f, x, peek, ...) \
    ;                                             \
    f(x) _QX_APPLY_DEFER(_QX_APPLY_MAP_NEXT(peek, _QX_APPLY_MAP_SEMICOLON1))(f, peek, __VA_ARGS__)
#define _QX_APPLY_MAP_SEMICOLON1(f, x, peek, ...) \
    ;                                             \
    f(x) _QX_APPLY_DEFER(_QX_APPLY_MAP_NEXT(peek, _QX_APPLY_MAP_SEMICOLON0))(f, peek, __VA_ARGS__)
#define _QX_APPLY_MAP_SEMICOLON2(f, x, peek, ...) \
    f(x) _QX_APPLY_DEFER(_QX_APPLY_MAP_NEXT(peek, _QX_APPLY_MAP_SEMICOLON1))(f, peek, __VA_ARGS__)

/**
    @def   QX_APPLY_COMMA
    @brief Applies the function macro `f` to each of the remaining parameters and inserts commas between the results:
           QX_APPLY_SPACE(foo, 1, 2, 3) -> foo(1), foo(2), foo(3)
    @param f   - function macro
    @param ... - parameters to apply
**/
#define QX_APPLY_COMMA(f, ...) _QX_APPLY_EVAL(_QX_APPLY_MAP_COMMA2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
    @def   QX_APPLY_SEMICOLON
    @brief Applies the function macro `f` to each of the remaining parameters and inserts semicolons between the results:
           QX_APPLY_SPACE(foo, 1, 2, 3) -> foo(1); foo(2); foo(3)
    @param f   - function macro
    @param ... - parameters to apply
**/
#define QX_APPLY_SEMICOLON(f, ...) _QX_APPLY_EVAL(_QX_APPLY_MAP_SEMICOLON2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
