/**

    @file      asserts.inl
    @author    Khrapov
    @date      7.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

#if QX_WITH_DEBUG_ASSERTS
    #define _QX_ASSERT_C(condition, category, ...) \
        _QX_COMMON_ASSERT(                         \
            condition,                             \
            category,                              \
            qx::assert_type::assert,               \
            _QX_ASSERT_AFTER_DEBUG_BREAK_FATAL,    \
            void,                                  \
            ##__VA_ARGS__)
#else
    #define _QX_ASSERT_C(condition, category, ...) QX_EMPTY_MACRO
#endif

#define _QX_EXPECT_ACTION(condition, category, action, ...)            \
    if (!QX_EXPECT_C(condition, category, ##__VA_ARGS__)) [[unlikely]] \
        action;                                                        \
    else                                                               \
        QX_EMPTY_MACRO


#if QX_WITH_DEBUG_ASSERTS
    #define _QX_ENSURE_C(condition, category, ...)  \
        _QX_COMMON_ASSERT(                          \
            condition,                              \
            category,                               \
            qx::assert_type::ensure,                \
            _QX_ASSERT_AFTER_DEBUG_BREAK_NON_FATAL, \
            void,                                   \
            ##__VA_ARGS__)
#else
    #define _QX_ENSURE_C(condition, category, ...) QX_EMPTY_MACRO
#endif
