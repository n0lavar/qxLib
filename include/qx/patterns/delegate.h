/**

    @file      delegate.h
    @author    Khrapov
    @date      7.01.2024
    @copyright © Nick Khrapov, 2024. All right reserved.

**/
#pragma once

#include <qx/destruction_callback.h>
#include <qx/macros/static_assert.h>
#include <qx/meta/concepts.h>
#include <qx/priority.h>

#include <concepts>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <variant>

namespace qx
{

template<class T>
concept delegate_pipe_c = std::default_initializable<T> && requires(T t) {
    { t | t } -> std::convertible_to<T>;
};

using delegate_token_type = time_ordered_priority_key;

/**

    @class   delegate
    @brief   Single or multicast delegate.

    @details For a singlecast version:
             1. Create with qx::delegate<...>::create_singlecast(...);
             2. Call delegate.execute(...).

             For a multicast version:
             1. Default construct;
             2. All various callbacks with delegate.add_xxx(...);
             2. Call delegate.execute(...).

             If a delegate has only one function inside (i.e. singlecast delegate),
             it's stored inplace without a container allocation.
             If a function is small enough (token overload with max 2 bytes captured,
             object + method pointer overload, weak overload with 1 byte max captured),
             there will be no allocations at all.
             The destruction callback overloads require 1 allocation for the alive marker (1 per delegate),
             because they need to unsubscribe safely.

    @tparam  signature_t - std::function-like signature of the delegate. For example: void(size_t, const qx::string&).
                           If the result type satisfies qx::delegate_pipe_c,
                           the result of each callable will be piped into the next one,
                           and the final result will be returned by execute().
                           Otherwise, the result of the last callable will be returned by execute(),
                           and the results of the previous callables will be ignored.
    @author  Khrapov
    @date    4.07.2025

**/
template<class signature_t>
class delegate;

namespace details
{

/**

    @class   base_delegate
    @brief   Base delegate type
    @tparam  derived_t - CRTP derived class type
    @tparam  return_t  - the exact type that all the passed callables and execute() should return
    @tparam  args_t    - the exact type that all the passed callables and execute() should take
    @author  Khrapov
    @date    17.02.2026

**/
template<class derived_t, class return_t, class... args_t>
class base_delegate
{
    friend derived_t;

    base_delegate() noexcept = default;
    base_delegate(base_delegate&& other) noexcept;
    base_delegate(const base_delegate& other) noexcept = delete;

public:
    using function_type = std::function<return_t(args_t...)>;

private:
    using single_value_type = std::pair<time_ordered_priority_key, function_type>;
    using container_type    = std::map<time_ordered_priority_key, function_type>;
    using variant_type      = std::variant<single_value_type, container_type>;
    using data_type         = std::optional<variant_type>;

public:
    base_delegate& operator=(base_delegate&& other) noexcept;
    base_delegate& operator=(const base_delegate& other) noexcept = delete;

    /**
        @brief  Create a singlecast delegate
        @tparam creation_args_t - any arguments that can be used in add_weak or add_token
        @param  args            - template parameter pack
        @retval                 - created delegate
    **/
    template<class... creation_args_t>
    static derived_t create_singlecast(creation_args_t... args) noexcept;

    /**
        @brief   Add a callable using a token with manual unsubscribing.
        @warning If you capture `this` in the lambda passed and the object becomes invalid, it'll crash.
                 You must unsubscribe manually using remove()
                 Consider using add_destruction_callback or add_weak.
        @tparam  callable_t - any callable type: lambda, function, static method pointer, ect
        @param   callable   - callable object
        @param   ePriority  - callable priority. Callables will be called in order of priority,
                              from highest to lowest, and in the order they were added.
        @retval             - a token that can be used to remove this callable from the delegate
    **/
    template<callable_c<return_t, args_t...> callable_t>
    [[maybe_unused]] delegate_token_type add_token(callable_t callable, priority ePriority = priority::normal) noexcept;

    /**
        @brief   Add a callable using a token with manual unsubscribing.
        @warning If you capture `this` in the lambda passed and the object becomes invalid, it'll crash.
                 You must unsubscribe manually using remove()
                 Consider using add_destruction_callback or add_weak.
        @tparam  object_t  - object type
        @param   object    - object reference
        @param   pMethod   - object's method pointer
        @param   ePriority - callable priority. Callables will be called in order of priority,
                             from highest to lowest, and in the order they were added.
        @retval            - a token that can be used to remove this callable from the delegate
    **/
    template<class object_t>
    [[maybe_unused]] delegate_token_type add_token(
        object_t& object,
        return_t (object_t::*pMethod)(args_t...),
        priority ePriority = priority::normal) noexcept;

    /**
        @brief  Add a callable that will be removed from the delegate when its destruction callback is destroyed
        @tparam callable_t - any callable type: lambda, function, static method pointer, ect
        @param  callable   - callable object
        @param  ePriority  - callable priority. Callables will be called in order of priority,
                             from highest to lowest, and in the order they were added.
        @retval            - an object that removes this callable from the delegate on its destruction
    **/
    template<callable_c<return_t, args_t...> callable_t>
    [[nodiscard]] destruction_callback add_destruction_callback(
        callable_t callable,
        priority   ePriority = priority::normal) noexcept;

    /**
        @brief  Add a callable that will be removed from the delegate when its destruction callback is destroyed
        @tparam object_t  - object type
        @param  object    - object reference
        @param  pMethod   - object's method pointer
        @param  ePriority - callable priority. Callables will be called in order of priority,
                            from highest to lowest, and in the order they were added.
        @retval           - an object that removes this callable from the delegate on its destruction
    **/
    template<class object_t>
    [[nodiscard]] destruction_callback add_destruction_callback(
        object_t& object,
        return_t (object_t::*pMethod)(args_t...),
        priority ePriority = priority::normal) noexcept;

    /**
        @brief  Add a callable that will be executed only if the appropriate weak object is valid
        @tparam object_t    - object type
        @tparam callable_t  - any callable type: lambda, function, static method pointer, ect
        @param  pWeakObject - an object to track
        @param  callable    - callable object
        @param  ePriority   - callable priority. Callables will be called in order of priority,
                              from highest to lowest, and in the order they were added.
        @retval             - a token that can be used to remove this callable from the delegate
    **/
    template<class object_t, callable_c<return_t, args_t...> callable_t>
    [[maybe_unused]] delegate_token_type add_weak(
        std::weak_ptr<object_t> pWeakObject,
        callable_t              callable,
        priority                ePriority = priority::normal) noexcept;

    /**
        @brief  Add a callable that will be executed only if the appropriate weak object is valid
        @tparam object_t    - object type
        @param  pWeakObject - an object to track and to apply the method to
        @param  pMethod     - object's method pointer
        @param  ePriority   - callable priority. Callables will be called in order of priority,
                              from highest to lowest, and in the order they were added.
        @retval             - a token that can be used to remove this callable from the delegate
    **/
    template<class object_t>
    [[maybe_unused]] delegate_token_type add_weak(
        std::weak_ptr<object_t> pWeakObject,
        return_t (object_t::*pMethod)(args_t...),
        priority ePriority = priority::normal) noexcept;

    /**
        @brief  Remove a callable using its token
        @param  token - callable token
        @retval       - true is a callable was deleted
    **/
    bool remove(delegate_token_type token) noexcept;

    /**
        @brief Clear all the callables in this delegate
    **/
    void clear() noexcept;

    /**
        @brief  Get the number of functions bound to this delegate
        @retval  - the number of functions bound to this delegate
    **/
    size_t size() const noexcept;

    /**
        @brief  Check if this delegate is empty
        @retval  - true if this delegate is empty
    **/
    bool empty() const noexcept;

protected:
    /**
        @brief  Execute all callables
        @tparam invoke_single_t   - a callable type that executes a delegate callable by moving args into it
        @tparam invoke_multiple_t - a callable type that executes a delegate callable by copying args into it
        @param  invokeSingle      - invoke_single_t object
        @param  invokeMultiple    - invoke_multiple_t object
        @retval                   - void or piping result of all delegate callables 
    **/
    template<class invoke_single_t, class invoke_multiple_t>
    return_t execute_internal(const invoke_single_t& invokeSingle, const invoke_multiple_t& invokeMultiple)
        const noexcept;

private:
    /**
        @brief  Add a value using the destruction callback strategy
        @param  key   - priority + time key
        @param  value - a function to add
        @retval       - a destruction callback
    **/
    destruction_callback add_destruction_callback(time_ordered_priority_key key, function_type value) noexcept;

    /**
        @brief Add a delegate entity
        @param key      - priority + time key
        @param function - a function to add
    **/
    void add_function(time_ordered_priority_key key, function_type function) noexcept;

    /**
        @brief  Add a value using the weak object strategy
        @tparam object_t    - weak object type
        @tparam callable_t  - a callable to execute if the weak is alive
        @param  key         - priority + time key
        @param  pWeakObject - weak object to track
        @param  callable    - callable_t object
    **/
    template<class object_t, callable_c<return_t, object_t*, args_t...> callable_t>
    void add_weak(time_ordered_priority_key key, std::weak_ptr<object_t> pWeakObject, callable_t callable) noexcept;

private:
    data_type m_optFunctions;

    // in case a delegate was destroyed before a destruction callback
    std::shared_ptr<bool> m_pDelegateAliveMarker;
};

} // namespace details

// @copydoc delegate
template<class return_t, class... args_t>
    requires(sizeof...(args_t) > 0 && (!std::is_void_v<args_t> && ...))
class delegate<return_t(args_t...)> final
    : public details::base_delegate<delegate<return_t(args_t...)>, return_t, args_t...>
{
    using super_type = details::base_delegate<delegate, return_t, args_t...>;

public:
    /**
        @brief  Execute all the callables the delegate has
        @param  args - arguments to pass to all the callbacks
        @retval      - void or piping result of all delegate callables
    **/
    return_t execute(args_t... args) const noexcept;
};

// @copydoc delegate
template<class return_t>
class delegate<return_t()> final : public details::base_delegate<delegate<return_t()>, return_t>
{
    using super_type = details::base_delegate<delegate, return_t>;

public:
    /**
        @brief  Execute all the callables the delegate has
        @retval  - void or piping result of all delegate callables
    **/
    return_t execute() const noexcept;
};

} // namespace qx

#include <qx/patterns/delegate.inl>
