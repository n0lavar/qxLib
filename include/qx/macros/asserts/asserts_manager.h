/**

    @file      asserts_manager.h
    @author    Khrapov
    @date      27.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/algo/predicates.h>
#include <qx/logger/logger.h>
#include <qx/macros/details/macro_user_message.h>
#include <qx/windows.h>

namespace qx
{

enum class assert_type
{
    assert,
    verify,
    expect,
    ensure
};

/**

    @class   asserts_manager
    @brief   Determines assertions behavior
    @author  Khrapov
    @date    4.01.2026

**/
class asserts_manager final : public singleton<asserts_manager>
{
public:
    struct config
    {
        std::function<void(const category& category, assert_type eAssertType)> onExit =
            [](const category& category, assert_type eAssertType)
        {
            // Normal exit after fatal assertions to avoid the second report
            std::exit(0);
        };

        std::function<verbosity(assert_type eAssertType)> getVerbosity = [](assert_type eAssertType)
        {
            switch (eAssertType)
            {
            case assert_type::assert:
            case assert_type::verify:
                return verbosity::critical;

            case assert_type::expect:
            case assert_type::ensure:
            default:
                return verbosity::error;
            }
        };

        std::function<void(
            string_view     svCondition,
            const category& category,
            assert_type     eAssertType,
            string_view     svUserMessage,
            string_view     svFunction,
            string_view     svFile,
            i32             nLine)>
            onAssertion;

        bool bLogAssertion = true;
    };

public:
    /**
        @brief  An entry point for all assertions
        @param  svCondition   - a string representation of the condition
        @param  category      - a category of the assertion (file wide or manually specified)
        @param  eAssertType   - an assertion type
        @param  svUserMessage - formatted user message, if specified
        @param  svFunction    - assert location function
        @param  svFile        - assert location file
        @param  nLine         - assert location line number
        @retval               - true if debug break is required
    **/
    bool do_assert(
        string_view     svCondition,
        const category& category,
        assert_type     eAssertType,
        string_view     svUserMessage,
        string_view     svFunction,
        string_view     svFile,
        i32             nLine);

    /**
        @brief Called in fatal assertions to exit the application
        @param category    - a category of the assertion (file wide or manually specified)
        @param eAssertType - an assertion type
    **/
    void exit(const category& category, assert_type eAssertType);

    /**
        @brief  Get config
        @retval  - existing config
    **/
    const config& get_config() const;

    /**
        @brief Set config
        @param config - new config
    **/
    void set_config(config config);

private:
    config m_Config;
};

} // namespace qx

#if QX_MSVC
    #define _QX_DEBUG_BREAK() __debugbreak()
#elif QX_CLANG
    #define _QX_DEBUG_BREAK() __builtin_debugtrap()
#elif QX_GNU
    #include <signal.h>
    #define _QX_DEBUG_BREAK() raise(SIGTRAP)
#else
    #define _QX_DEBUG_BREAK() QX_EMPTY_MACRO
#endif

#ifndef QX_DEBUG_BREAK
    #define QX_DEBUG_BREAK() _QX_DEBUG_BREAK()
#endif

#define _QX_COMMON_ASSERT(condition, category, assert_type, after_debug_break, result_t, ...) \
    static_cast<result_t>(                                                                    \
        qx::predicates::is_valid(condition)                                                   \
        || (qx::asserts_manager::get_instance().do_assert(                                    \
                QXT(#condition),                                                              \
                category,                                                                     \
                assert_type,                                                                  \
                _QX_MACRO_USER_MESSAGE(__VA_ARGS__),                                          \
                qx::to_string(__FUNCTION__),                                                  \
                QXT(__FILE__),                                                                \
                QX_LINE)                                                                      \
                ? QX_DEBUG_BREAK()                                                            \
                : (void)0,                                                                    \
            after_debug_break(category, assert_type),                                         \
            false))

#ifndef _QX_ASSERT_AFTER_DEBUG_BREAK_FATAL
    #define _QX_ASSERT_AFTER_DEBUG_BREAK_FATAL(category, assert_type) \
        qx::asserts_manager::get_instance().exit(category, assert_type)
#endif

#ifndef _QX_ASSERT_AFTER_DEBUG_BREAK_NON_FATAL
    #define _QX_ASSERT_AFTER_DEBUG_BREAK_NON_FATAL(category, assert_type) false
#endif

#ifndef QX_WITH_DEBUG_ASSERTS
    #define QX_WITH_DEBUG_ASSERTS QX_WITH_DEBUG_INFO
#endif

#include <qx/macros/asserts/asserts_manager.inl>
