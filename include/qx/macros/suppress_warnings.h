/**

    @file      suppress_warnings.h
    @author    Khrapov
    @date      11.11.2020
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/config.h>

#if QX_MSVC

    #define _QX_PUSH_SUPPRESS_ALL_WARNINGS()          __pragma(warning(push, 0))
    #define _QX_POP_SUPPRESS_WARNINGS()               __pragma(warning(pop))
    #define _QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings) __pragma(warning(push)) __pragma(warning(disable : warnings))
    #define _QX_DISABLE_MSVC_WARNINGS(warnings)       __pragma(warning(disable : warnings))
    #define _QX_RESTORE_MSVC_WARNINGS(warnings)       __pragma(warning(default : warnings))

#elif QX_CLANG

    // clang-cl ignores __pragma(warning(push, 0)), so all warnings are disabled by name:
    // "all" (the -Wall group) plus the warnings and groups that it does not cover
    #define _QX_PUSH_SUPPRESS_ALL_WARNINGS()                                              \
        _Pragma("GCC diagnostic push");                                                   \
        _Pragma("GCC diagnostic ignored \"-Wall\"");                                      \
        _Pragma("GCC diagnostic ignored \"-Wc++98-compat-pedantic\"");                    \
        _Pragma("GCC diagnostic ignored \"-Wc++11-extensions\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wc++14-extensions\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wc++17-extensions\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wc++20-extensions\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wc++23-extensions\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wextra\"");                                    \
        _Pragma("GCC diagnostic ignored \"-Wswitch-default\"");                           \
        _Pragma("GCC diagnostic ignored \"-Wswitch-enum\"");                              \
        _Pragma("GCC diagnostic ignored \"-Wcovered-switch-default\"");                   \
        _Pragma("GCC diagnostic ignored \"-Wdocumentation\"");                            \
        _Pragma("GCC diagnostic ignored \"-Wdocumentation-unknown-command\"");            \
        _Pragma("GCC diagnostic ignored \"-Wdocumentation-pedantic\"");                   \
        _Pragma("GCC diagnostic ignored \"-Wreserved-identifier\"");                      \
        _Pragma("GCC diagnostic ignored \"-Wreserved-macro-identifier\"");                \
        _Pragma("GCC diagnostic ignored \"-Wunsafe-buffer-usage\"");                      \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated\"");                               \
        _Pragma("GCC diagnostic ignored \"-Wmicrosoft\"");                                \
        _Pragma("GCC diagnostic ignored \"-Wmicrosoft-template-shadow\"");                \
        _Pragma("GCC diagnostic ignored \"-Wpadded\"");                                   \
        _Pragma("GCC diagnostic ignored \"-Wshadow-all\"");                               \
        _Pragma("GCC diagnostic ignored \"-Wextra-semi\"");                               \
        _Pragma("GCC diagnostic ignored \"-Wextra-semi-stmt\"");                          \
        _Pragma("GCC diagnostic ignored \"-Wgnu\"");                                      \
        _Pragma("GCC diagnostic ignored \"-Wconversion\"");                               \
        _Pragma("GCC diagnostic ignored \"-Wunused\"");                                   \
        _Pragma("GCC diagnostic ignored \"-Wimplicit-fallthrough\"");                     \
        _Pragma("GCC diagnostic ignored \"-Wunreachable-code\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"");                              \
        _Pragma("GCC diagnostic ignored \"-Wnrvo\"");                                     \
        _Pragma("GCC diagnostic ignored \"-Winvalid-utf8\"");                             \
        _Pragma("GCC diagnostic ignored \"-Wzero-as-null-pointer-constant\"");            \
        _Pragma("GCC diagnostic ignored \"-Wold-style-cast\"");                           \
        _Pragma("GCC diagnostic ignored \"-Wdisabled-macro-expansion\"");                 \
        _Pragma("GCC diagnostic ignored \"-Wmissing-noreturn\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wused-but-marked-unused\"");                   \
        _Pragma("GCC diagnostic ignored \"-Wglobal-constructors\"");                      \
        _Pragma("GCC diagnostic ignored \"-Wexit-time-destructors\"");                    \
        _Pragma("GCC diagnostic ignored \"-Wctad-maybe-unsupported\"");                   \
        _Pragma("GCC diagnostic ignored \"-Wunique-object-duplication\"");                \
        _Pragma("GCC diagnostic ignored \"-Wnewline-eof\"");                              \
        _Pragma("GCC diagnostic ignored \"-Wundef\"");                                    \
        _Pragma("GCC diagnostic ignored \"-Wnonportable-include-path\"");                 \
        _Pragma("GCC diagnostic ignored \"-Wnonportable-system-include-path\"");          \
        _Pragma("GCC diagnostic ignored \"-Wcompound-token-split-by-space\"");            \
        _Pragma("GCC diagnostic ignored \"-Wredundant-parens\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wcomma\"");                                    \
        _Pragma("GCC diagnostic ignored \"-Winjected-class-name\"");                      \
        _Pragma("GCC diagnostic ignored \"-Wunused-macros\"");                            \
        _Pragma("GCC diagnostic ignored \"-Wlanguage-extension-token\"");                 \
        _Pragma("GCC diagnostic ignored \"-Wmissing-prototypes\"");                       \
        _Pragma("GCC diagnostic ignored \"-Wshorten-64-to-32\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wcast-qual\"");                                \
        _Pragma("GCC diagnostic ignored \"-Winvalid-offsetof\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wunused-template\"");                          \
        _Pragma("GCC diagnostic ignored \"-Wmissing-designated-field-initializers\"");    \
        _Pragma("GCC diagnostic ignored \"-Winconsistent-missing-override\"");            \
        _Pragma("GCC diagnostic ignored \"-Winconsistent-missing-destructor-override\""); \
        _Pragma("GCC diagnostic ignored \"-Wsuggest-override\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wsuggest-destructor-override\"");              \
        _Pragma("GCC diagnostic ignored \"-Wunused-const-variable\"");                    \
        _Pragma("GCC diagnostic ignored \"-Wnested-anon-types\"");                        \
        _Pragma("GCC diagnostic ignored \"-Wms-bitfield-padding\"");                      \
        _Pragma("GCC diagnostic ignored \"-Wdouble-promotion\"")
    #define _QX_POP_SUPPRESS_WARNINGS() _Pragma("GCC diagnostic pop")
    #define _QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings)
    #define _QX_DISABLE_MSVC_WARNINGS(warnings)
    #define _QX_RESTORE_MSVC_WARNINGS(warnings)

#else

    #define _QX_PUSH_SUPPRESS_ALL_WARNINGS()
    #define _QX_POP_SUPPRESS_WARNINGS()
    #define _QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings)
    #define _QX_DISABLE_MSVC_WARNINGS(warnings)
    #define _QX_RESTORE_MSVC_WARNINGS(warnings)

#endif

/**
    @def   QX_PUSH_SUPPRESS_ALL_WARNINGS
    @brief Disable all warnings
**/

#define QX_PUSH_SUPPRESS_ALL_WARNINGS() _QX_PUSH_SUPPRESS_ALL_WARNINGS()

/**
    @def   QX_POP_SUPPRESS_WARNINGS
    @brief Enable all warnings
**/

#define QX_POP_SUPPRESS_WARNINGS() _QX_POP_SUPPRESS_WARNINGS()

/**
    @def   QX_PUSH_SUPPRESS_MSVC_WARNINGS
    @brief Disable specified MSVC warnings
    @param warnings - MSVC warnings numbers separated by space
**/
#define QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings) _QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings)

/**
    @brief Force disable MSVC warnings, including all nested header includes
    @note  Prefer using QX_PUSH_SUPPRESS_MSVC_WARNINGS and QX_POP_SUPPRESS_WARNINGS
    @param warnings - MSVC warnings numbers separated by space
**/
#define QX_DISABLE_MSVC_WARNINGS(warnings) _QX_DISABLE_MSVC_WARNINGS(warnings)

/**
    @brief Enable warnings after QX_DISABLE_MSVC_WARNINGS
    @param warnings - MSVC warnings numbers separated by space
**/
#define QX_RESTORE_MSVC_WARNINGS(warnings) _QX_RESTORE_MSVC_WARNINGS(warnings)
