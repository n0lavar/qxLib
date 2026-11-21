/**

    @file      suppress_warnings.h
    @author    Khrapov
    @date      11.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/common.h>

#if QX_MSVC

    #define QX_DETAILS_PUSH_SUPPRESS_ALL_WARNINGS() __pragma(warning(push, 0))
    #define QX_DETAILS_POP_SUPPRESS_ALL_WARNINGS()  __pragma(warning(pop))
    #define QX_DETAILS_PUSH_SUPPRESS_MSVC_WARNINGS(warnings) \
        __pragma(warning(push)) __pragma(warning(disable : warnings))
    #define QX_DETAILS_POP_SUPPRESS_MSVC_WARNINGS() __pragma(warning(pop))
    #define QX_DETAILS_PUSH_SUPPRESS_CLANG_WARNINGS(warnings)
    #define QX_DETAILS_POP_SUPPRESS_CLANG_WARNINGS()

#elif QX_CLANG || QX_APPLE_CLANG || QX_GNU

    // clang and GCC share the pragmas; each compiler silently skips the other's warning names
    #define QX_DETAILS_PRAGMA(x)                _Pragma(#x)
    #define QX_DETAILS_PRAGMA_WARNING(warnings) QX_DETAILS_PRAGMA(GCC diagnostic ignored warnings)
    #define QX_DETAILS_PUSH_IGNORE_UNKNOWN_WARNINGS()                                  \
        _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wpragmas\"") \
            _Pragma("GCC diagnostic ignored \"-Wunknown-warning-option\"")
    #define QX_DETAILS_PUSH_SUPPRESS_ALL_WARNINGS()                                       \
        QX_DETAILS_PUSH_IGNORE_UNKNOWN_WARNINGS();                                        \
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
        _Pragma("GCC diagnostic ignored \"-Wcast-align\"");                               \
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
        _Pragma("GCC diagnostic ignored \"-Wdouble-promotion\"");                         \
        _Pragma("GCC diagnostic ignored \"-Wduplicate-enum\"");                           \
        _Pragma("GCC diagnostic ignored \"-Wformat-nonliteral\"");                        \
        _Pragma("GCC diagnostic ignored \"-Wdangling-else\"");                            \
        /* GCC names of the same warnings and GCC-only ones */                            \
        _Pragma("GCC diagnostic ignored \"-Wpedantic\"");                                 \
        _Pragma("GCC diagnostic ignored \"-Wshadow\"");                                   \
        _Pragma("GCC diagnostic ignored \"-Wsign-conversion\"");                          \
        _Pragma("GCC diagnostic ignored \"-Wsign-compare\"");                             \
        _Pragma("GCC diagnostic ignored \"-Wparentheses\"");                              \
        _Pragma("GCC diagnostic ignored \"-Wempty-body\"");                               \
        _Pragma("GCC diagnostic ignored \"-Wformat-security\"");                          \
        _Pragma("GCC diagnostic ignored \"-Wmissing-field-initializers\"");               \
        _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"");                      \
        _Pragma("GCC diagnostic ignored \"-Wclass-memaccess\"");                          \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-copy\"");                          \
        _Pragma("GCC diagnostic ignored \"-Wcast-function-type\"");                       \
        _Pragma("GCC diagnostic ignored \"-Wredundant-move\"");                           \
        _Pragma("GCC diagnostic ignored \"-Wpessimizing-move\"")
    #define QX_DETAILS_POP_SUPPRESS_ALL_WARNINGS()           _Pragma("GCC diagnostic pop") QX_EMPTY_MACRO
    #define QX_DETAILS_PUSH_SUPPRESS_MSVC_WARNINGS(warnings) QX_EMPTY_MACRO
    #define QX_DETAILS_POP_SUPPRESS_MSVC_WARNINGS()          QX_EMPTY_MACRO
    #define QX_DETAILS_PUSH_SUPPRESS_CLANG_WARNINGS(warnings) \
        QX_DETAILS_PUSH_IGNORE_UNKNOWN_WARNINGS() QX_DETAILS_PRAGMA_WARNING(warnings) QX_EMPTY_MACRO
    #define QX_DETAILS_POP_SUPPRESS_CLANG_WARNINGS() _Pragma("GCC diagnostic pop") QX_EMPTY_MACRO

#else

    #define QX_DETAILS_PUSH_SUPPRESS_ALL_WARNINGS()           QX_EMPTY_MACRO
    #define QX_DETAILS_POP_SUPPRESS_ALL_WARNINGS()            QX_EMPTY_MACRO
    #define QX_DETAILS_PUSH_SUPPRESS_MSVC_WARNINGS(warnings)  QX_EMPTY_MACRO
    #define QX_DETAILS_POP_SUPPRESS_MSVC_WARNINGS()           QX_EMPTY_MACRO
    #define QX_DETAILS_PUSH_SUPPRESS_CLANG_WARNINGS(warnings) QX_EMPTY_MACRO
    #define QX_DETAILS_POP_SUPPRESS_CLANG_WARNINGS()          QX_EMPTY_MACRO

#endif

/**
    @def   QX_PUSH_SUPPRESS_ALL_WARNINGS
    @brief Disable all warnings
**/

#define QX_PUSH_SUPPRESS_ALL_WARNINGS() QX_DETAILS_PUSH_SUPPRESS_ALL_WARNINGS()

/**
    @def   QX_POP_SUPPRESS_ALL_WARNINGS
    @brief Enable all warnings after QX_PUSH_SUPPRESS_ALL_WARNINGS
**/

#define QX_POP_SUPPRESS_ALL_WARNINGS() QX_DETAILS_POP_SUPPRESS_ALL_WARNINGS()

/**
    @def   QX_PUSH_SUPPRESS_MSVC_WARNINGS
    @brief Disable specified MSVC warnings
    @param warnings - MSVC warnings numbers separated by space
**/
#define QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings) QX_DETAILS_PUSH_SUPPRESS_MSVC_WARNINGS(warnings)

/**
    @def   QX_POP_SUPPRESS_MSVC_WARNINGS
    @brief Restore warnings after QX_PUSH_SUPPRESS_MSVC_WARNINGS
**/
#define QX_POP_SUPPRESS_MSVC_WARNINGS() QX_DETAILS_POP_SUPPRESS_MSVC_WARNINGS()

/**
    @def   QX_PUSH_SUPPRESS_CLANG_WARNINGS
    @brief Disable a specific clang or GCC warning, empty on MSVC
    @param warnings - clang or GCC warning name as a string, e.g. "-Wshadow"
**/
#define QX_PUSH_SUPPRESS_CLANG_WARNINGS(warnings) QX_DETAILS_PUSH_SUPPRESS_CLANG_WARNINGS(warnings)

/**
    @def   QX_POP_SUPPRESS_CLANG_WARNINGS
    @brief Enable warnings after QX_PUSH_SUPPRESS_CLANG_WARNINGS, empty on MSVC
**/
#define QX_POP_SUPPRESS_CLANG_WARNINGS() QX_DETAILS_POP_SUPPRESS_CLANG_WARNINGS()
