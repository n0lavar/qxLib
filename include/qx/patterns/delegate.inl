/**

    @file      delegate.inl
    @author    Khrapov
    @date      7.01.2024
    @copyright © Nick Khrapov, 2024. All right reserved.

**/

namespace qx
{

namespace details
{

template<class return_t, class function_t>
class base_invoker
{
public:
    virtual ~base_invoker() noexcept                             = default;
    virtual return_t invoke(const function_t& function) noexcept = 0;
};

template<class return_t, class function_t, class invoke_function_t>
class invoker : public base_invoker<return_t, function_t>
{
public:
    invoker(const invoke_function_t& invoke) noexcept : m_InvokeFunction(invoke)
    {
    }

private:
    virtual return_t invoke(const function_t& function) noexcept override
    {
        return m_InvokeFunction(function);
    }

private:
    const invoke_function_t& m_InvokeFunction;
};

template<class derived_t, class return_t, class... args_t>
base_delegate<derived_t, return_t, args_t...>::base_delegate(base_delegate&& other) noexcept
{
    std::swap(m_Functions, other.m_Functions);
    std::swap(m_pDelegateAliveMarker, other.m_pDelegateAliveMarker);
}

template<class derived_t, class return_t, class... args_t>
typename base_delegate<derived_t, return_t, args_t...>::base_delegate& base_delegate<derived_t, return_t, args_t...>::
    operator=(base_delegate&& other) noexcept
{
    std::swap(m_Functions, other.m_Functions);
    std::swap(m_pDelegateAliveMarker, other.m_pDelegateAliveMarker);
    return *this;
}

template<class derived_t, class return_t, class... args_t>
template<class... creation_args_t>
derived_t base_delegate<derived_t, return_t, args_t...>::create_singlecast(creation_args_t... args) noexcept
{
    derived_t delegate;
    if constexpr (requires(derived_t d) { d.add_weak(args...); })
        delegate.add_weak(args...);
    if constexpr (requires(derived_t d) { d.add_token(args...); })
        delegate.add_token(args...);
    else
        QX_STATIC_ASSERT_NO_INSTANTIATION("No overload that takes these args");

    return delegate;
}

template<class derived_t, class return_t, class... args_t>
template<callable_c<return_t, args_t...> callable_t>
delegate_token_type base_delegate<derived_t, return_t, args_t...>::add_token(
    callable_t callable,
    priority   ePriority) noexcept
{
    time_ordered_priority_key key(ePriority);
    m_Functions.emplace(key, std::move(callable));
    return key;
}

template<class derived_t, class return_t, class... args_t>
template<class object_t>
delegate_token_type base_delegate<derived_t, return_t, args_t...>::add_token(
    object_t& object,
    return_t (object_t::*pMethod)(args_t...),
    priority ePriority) noexcept
{
    return add_token(
        [pMethod, &object](args_t... args)
        {
            return (object.*pMethod)(std::forward<args_t>(args)...);
        },
        ePriority);
}

template<class derived_t, class return_t, class... args_t>
template<callable_c<return_t, args_t...> callable_t>
destruction_callback base_delegate<derived_t, return_t, args_t...>::add_destruction_callback(
    callable_t callable,
    priority   ePriority) noexcept
{
    return add_destruction_callback(time_ordered_priority_key(ePriority), function_type(std::move(callable)));
}

template<class derived_t, class return_t, class... args_t>
template<class object_t>
destruction_callback base_delegate<derived_t, return_t, args_t...>::add_destruction_callback(
    object_t& object,
    return_t (object_t::*pMethod)(args_t...),
    priority ePriority) noexcept
{
    return add_destruction_callback(
        time_ordered_priority_key(ePriority),
        [&object, pMethod](args_t... args)
        {
            return (object.*pMethod)(std::forward<args_t>(args)...);
        });
}

template<class derived_t, class return_t, class... args_t>
template<class object_t>
delegate_token_type base_delegate<derived_t, return_t, args_t...>::add_weak(
    std::weak_ptr<object_t> pWeakObject,
    return_t (object_t::*pMethod)(args_t...),
    priority ePriority) noexcept
{
    time_ordered_priority_key key(ePriority);
    add_weak(
        key,
        std::move(pWeakObject),
        [pMethod](object_t* pObject, args_t... args)
        {
            return (pObject->*pMethod)(std::forward<args_t>(args)...);
        });
    return key;
}

template<class derived_t, class return_t, class... args_t>
template<class object_t, callable_c<return_t, args_t...> callable_t>
delegate_token_type base_delegate<derived_t, return_t, args_t...>::add_weak(
    std::weak_ptr<object_t> pWeakObject,
    callable_t              callable,
    priority                ePriority) noexcept
{
    time_ordered_priority_key key(ePriority);
    add_weak(
        key,
        std::move(pWeakObject),
        [callable_ = std::move(callable)](object_t*, args_t... args)
        {
            return callable_(std::forward<args_t>(args)...);
        });
    return key;
}

template<class derived_t, class return_t, class... args_t>
bool base_delegate<derived_t, return_t, args_t...>::remove(delegate_token_type token) noexcept
{
    return m_Functions.erase(token) == 1;
}

template<class derived_t, class return_t, class... args_t>
void base_delegate<derived_t, return_t, args_t...>::clear() noexcept
{
    m_Functions.clear();
}

template<class derived_t, class return_t, class... args_t>
template<class invoke_single_t, class invoke_multiple_t>
return_t base_delegate<derived_t, return_t, args_t...>::execute_internal(
    const invoke_single_t&   invokeSingle,
    const invoke_multiple_t& invokeMultiple) const noexcept
{
    if (m_Functions.empty())
    {
        if constexpr (std::is_void_v<return_t>)
            return;
        else
            return return_t();
    }

    // modifying during iteration protection
    thread_local container_type tempFunctions;
    tempFunctions = m_Functions;

    details::invoker<return_t, function_type, invoke_single_t>   invokerSingle(invokeSingle);
    details::invoker<return_t, function_type, invoke_multiple_t> invokerMultiple(invokeMultiple);
    details::base_invoker<return_t, function_type>*              invoker = nullptr;
    if (tempFunctions.size() == 1)
        invoker = &invokerSingle;
    else
        invoker = &invokerMultiple;

    if constexpr (std::is_void_v<return_t>)
    {
        for (const auto& [_, function] : tempFunctions)
            invoker->invoke(function);

        return;
    }
    else if constexpr (delegate_pipe_c<return_t>)
    {
        return_t result {};
        for (const auto& [_, function] : tempFunctions)
            result = result | invoker->invoke(function);

        return result;
    }
    else
    {
        return_t result {};
        for (const auto& [_, function] : tempFunctions)
            result = invoker->invoke(function);

        return result;
    }
}

template<class derived_t, class return_t, class... args_t>
template<class object_t, callable_c<return_t, object_t*, args_t...> callable_t>
void base_delegate<derived_t, return_t, args_t...>::add_weak(
    time_ordered_priority_key key,
    std::weak_ptr<object_t>   pWeakObject,
    callable_t                callable) noexcept
{
    m_Functions.emplace(
        key,
        [this, key, pWeakObject, callable_ = std::move(callable)](args_t... args)
        {
            if (std::shared_ptr<object_t> pObject = pWeakObject.lock())
            {
                return callable_(pObject.get(), std::forward<args_t>(args)...);
            }
            else
            {
                remove(key);
                return return_t();
            }
        });
}

template<class derived_t, class return_t, class... args_t>
destruction_callback base_delegate<derived_t, return_t, args_t...>::add_destruction_callback(
    time_ordered_priority_key key,
    function_type             value) noexcept
{
    m_Functions.emplace(key, std::move(value));
    return [this, key, pDelegateAliveMarker = std::weak_ptr(m_pDelegateAliveMarker)]()
    {
        if (!pDelegateAliveMarker.expired())
            remove(key);
    };
}

} // namespace details

template<class return_t, class... args_t>
    requires(sizeof...(args_t) > 0 && (!std::is_void_v<args_t> && ...))
return_t delegate<return_t(args_t...)>::execute(args_t... args) const noexcept
{
    return this->execute_internal(
        [&args...](const typename super_type::function_type& function)
        {
            return function(std::forward<args_t>(args)...);
        },
        [&args...](const typename super_type::function_type& function)
        {
            return function(args...);
        });
}

template<class return_t>
return_t delegate<return_t(void)>::execute() const noexcept
{
    return this->execute_internal(
        [](const typename super_type::function_type& function)
        {
            return function();
        },
        [](const typename super_type::function_type& function)
        {
            return function();
        });
}

} // namespace qx
