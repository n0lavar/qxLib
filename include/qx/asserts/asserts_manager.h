/**

    @file      asserts_manager.h
    @author    Khrapov
    @date      27.12.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/algo/predicates.h>
#include <qx/asserts/assert_compare.h>
#include <qx/asserts/error_context_stream.h>
#include <qx/containers/string/format_string.h>
#include <qx/logger/logger.h>
#include <qx/macros/details/macro_user_message.h>
#include <qx/windows.h>

#include <shared_mutex>
#include <vector>

#if QX_LINUX
    #include <cstdio>
#elif QX_MACOS && (QX_WITH_DEBUG_INFO)
    #include <sys/sysctl.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

namespace qx
{

/**
    @brief   Check whether the current process or thread is being traced by a debugger.
    @details Detection is supported on Windows, Linux and debug-info builds on macOS. Linux uses procfs;
             a non-debugger tracer also counts. An unavailable query or unsupported platform returns false.
    @return  - true when tracing is detected, otherwise false
**/
bool is_debugger_present() noexcept;

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
    using exit_func      = std::function<void(const category& category, assert_type eAssertType)>;
    using verbosity_func = std::function<verbosity(assert_type eAssertType)>;
    using assertion_func = std::function<void(
        string_view     svCondition,
        const category& category,
        assert_type     eAssertType,
        string_view     svUserMessage,
        string_view     svFunction,
        string_view     svFile,
        i32             nLine)>;

    struct config
    {
        exit_func onExit = [](const category& category, assert_type eAssertType)
        {
            // Configurable fatal-assertion handler exits normally to avoid a second report.
            std::exit(0); //-V2014
        };

        verbosity_func getVerbosity = [](assert_type eAssertType)
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

        assertion_func onAssertion;

        bool bLogAssertion = true;
    };

    using interceptor_func = std::function<bool(
        string_view     svCondition,
        const category& category,
        assert_type     eAssertType,
        string_view     svUserMessage,
        string_view     svFunction,
        string_view     svFile,
        i32             nLine)>;

    struct interceptor_entry
    {
        const void*      pOwner;
        interceptor_func callback;
    };

public:
    /**
        @brief  An entry point for all assertions
        @param  svCondition   - a string representation of the condition
        @param  category      - a category of the assertion (file wide or manually specified)
        @param  eAssertType   - an assertion type
        @param  sUserMessage  - formatted user message, if specified
        @param  svFunction    - assert location function
        @param  svFile        - assert location file
        @param  nLine         - assert location line number
        @return               - true if debug break is required
    **/
    bool do_assert(
        string_view     svCondition,
        const category& category,
        assert_type     eAssertType,
        string          sUserMessage,
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
        @return  - a thread-safe copy of the current configuration
    **/
    config get_config() const;

    /**
        @brief Set config
        @param config - new config
    **/
    void set_config(config config);

    /**
        @brief   Register an assertion interceptor.
        @details Interceptors are tried in registration order before normal assertion handling. A matching
                 interceptor suppresses logging, the callback and debug break. Fatal assertions still call onExit. It must not
                 modify the interceptor list or the manager configuration from its callback.
        @param   pOwner      - unique identity used to remove the interceptor
        @param   interceptor - returns true when the assertion is handled
    **/
    void add_interceptor(const void* pOwner, interceptor_func interceptor);

    /**
        @brief  Remove an interceptor, waiting for callbacks already in progress.
        @param  pOwner - identity supplied when registering the interceptor
    **/
    void remove_interceptor(const void* pOwner);

private:
    mutable std::shared_mutex      m_Mutex;
    config                         m_Config;
    std::vector<interceptor_entry> m_Interceptors;
};

} // namespace qx

#if QX_MSVC
    #define _QX_DEBUG_BREAK() __debugbreak()
#elif QX_CLANG
    #define _QX_DEBUG_BREAK() __builtin_debugtrap()
#elif QX_GNU
    #include <signal.h>
    #define _QX_DEBUG_BREAK() static_cast<void>(raise(SIGTRAP))
#else
    #define _QX_DEBUG_BREAK() QX_EMPTY_MACRO
#endif

#ifndef QX_DEBUG_BREAK
    /**
        @brief Interrupt execution for a debugger using the platform's debug trap.
    **/
    #define QX_DEBUG_BREAK() _QX_DEBUG_BREAK()
#endif

#define _QX_COMMON_ASSERT(condition, category, assert_type, after_debug_break, result_t, ...)                      \
    static_cast<result_t>(                                                                                         \
        qx::predicates::is_valid(condition)                                                                        \
        || (qx::asserts_manager::get_instance().do_assert(                                                         \
                qx::details::get_assert_condition_string<QXT(#condition)>(condition),                              \
                category,                                                                                          \
                assert_type,                                                                                       \
                std::move(_QX_MACRO_USER_MESSAGE(static_cast<qx::string_pool<>*>(nullptr), ##__VA_ARGS__).sValue), \
                qx::convert_string_literal<qx::char_type, __FUNCTION__>(),                                         \
                QXT(__FILE__),                                                                                     \
                QX_LINE)                                                                                           \
                ? QX_DEBUG_BREAK()                                                                                 \
                : (void)0,                                                                                         \
            after_debug_break(category, assert_type),                                                              \
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

template<class char_t>
struct QX_FMT_NS::formatter<qx::assert_type, char_t> : qx::basic_formatter<char_t>
{
    template<class format_context_t>
    constexpr auto format(qx::assert_type eType, format_context_t& ctx) const -> decltype(ctx.out())
    {
        qx::basic_string_view<char_t> svName;
        switch (eType)
        {
        case qx::assert_type::assert:
            svName = QX_STR_PREFIX(char_t, "assert");
            break;

        case qx::assert_type::verify:
            svName = QX_STR_PREFIX(char_t, "verify");
            break;

        case qx::assert_type::expect:
            svName = QX_STR_PREFIX(char_t, "expect");
            break;

        case qx::assert_type::ensure:
            svName = QX_STR_PREFIX(char_t, "ensure");
            break;
        }

        return QX_FMT_NS::format_to(ctx.out(), QX_STR_PREFIX(char_t, "{}"), svName);
    }
};

#include <qx/asserts/asserts_manager.inl>
