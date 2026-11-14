/**

    @file      delegate.inl
    @author    Khrapov
    @date      7.01.2024
    @copyright (c) Nick Khrapov, 2024. All right reserved.

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
    virtual return_t invoke(const function_t& function) noexcept override;

private:
    const invoke_function_t& m_InvokeFunction;
};

template<class return_t, class function_t, class invoke_function_t>
inline return_t invoker<return_t, function_t, invoke_function_t>::invoke(const function_t& function) noexcept
{
    return m_InvokeFunction(function);
}

template<class derived_t, class return_t, class... args_t>
base_delegate<derived_t, return_t, args_t...>::base_delegate(base_delegate&& other) noexcept
{
    *this = std::move(other);
}

template<class derived_t, class return_t, class... args_t>
typename base_delegate<derived_t, return_t, args_t...>::base_delegate& base_delegate<derived_t, return_t, args_t...>::
    operator=(base_delegate&& other) noexcept
{
    std::swap(m_optFunctions, other.m_optFunctions);
    std::swap(m_WeakSubscriptions, other.m_WeakSubscriptions);
    std::swap(m_pDelegateAliveMarker, other.m_pDelegateAliveMarker);

    if (m_pDelegateAliveMarker)
        *m_pDelegateAliveMarker = this;

    if (other.m_pDelegateAliveMarker)
        *other.m_pDelegateAliveMarker = &other;

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
    // SSO depends on the size of the input callable
    add_function(key, std::move(callable));
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
        // 2 pointers, SOO on all compilers
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
    // SSO depends on the size of the input callable
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
        // 2 pointers, SOO on all compilers
        [&object, pMethod](args_t... args)
        {
            return (object.*pMethod)(std::forward<args_t>(args)...);
        });
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
        // SSO depends on the size of the input callable
        [callable_ = std::move(callable)](object_t*, args_t... args)
        {
            return callable_(std::forward<args_t>(args)...);
        });
    return key;
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
        // 1 pointer, SOO on all compilers
        [pMethod](object_t* pObject, args_t... args)
        {
            return (pObject->*pMethod)(std::forward<args_t>(args)...);
        });
    return key;
}

template<class derived_t, class return_t, class... args_t>
bool base_delegate<derived_t, return_t, args_t...>::remove(delegate_token_type token) noexcept
{
    m_WeakSubscriptions.erase(token);
    return remove_function(token);
}

template<class derived_t, class return_t, class... args_t>
bool base_delegate<derived_t, return_t, args_t...>::remove_function(delegate_token_type token) noexcept
{
    return m_optFunctions
           && std::visit(
               [this, token]<class T>(T& value)
               {
                   if constexpr (std::is_same_v<T, single_value_type>)
                   {
                       if (value.first == token)
                       {
                           m_optFunctions.reset();
                           return true;
                       }
                       else
                       {
                           return false;
                       }
                   }
                   else if constexpr (std::is_same_v<T, container_type>)
                   {
                       return value.erase(token) == 1;
                   }
                   else
                   {
                       QX_STATIC_ASSERT_NO_INSTANTIATION("Invalid type");
                       return false;
                   }
               },
               *m_optFunctions);
}

template<class derived_t, class return_t, class... args_t>
void base_delegate<derived_t, return_t, args_t...>::clear() noexcept
{
    m_optFunctions.reset();
    m_WeakSubscriptions.clear();
}

template<class derived_t, class return_t, class... args_t>
void base_delegate<derived_t, return_t, args_t...>::clear_dead() noexcept
{
    for (auto it = m_WeakSubscriptions.begin(); it != m_WeakSubscriptions.end();)
    {
        if (it->second.expired())
        {
            const delegate_token_type token = it->first;
            it                              = m_WeakSubscriptions.erase(it);
            remove_function(token);
        }
        else
        {
            ++it;
        }
    }
}

template<class derived_t, class return_t, class... args_t>
size_t base_delegate<derived_t, return_t, args_t...>::size() const noexcept
{
    if (!m_optFunctions)
        return 0;

    return std::visit(
        []<class T>(const T& value) -> size_t
        {
            if constexpr (std::is_same_v<T, single_value_type>)
            {
                return 1;
            }
            else if constexpr (std::is_same_v<T, container_type>)
            {
                return value.size();
            }
            else
            {
                QX_STATIC_ASSERT_NO_INSTANTIATION("Invalid type");
                return 0;
            }
        },
        *m_optFunctions);
}

template<class derived_t, class return_t, class... args_t>
bool base_delegate<derived_t, return_t, args_t...>::is_singlecast() const noexcept
{
    return size() == 1;
}

template<class derived_t, class return_t, class... args_t>
bool base_delegate<derived_t, return_t, args_t...>::empty() const noexcept
{
    return size() == 0;
}

template<class derived_t, class return_t, class... args_t>
template<class invoke_single_t, class invoke_multiple_t>
return_t base_delegate<derived_t, return_t, args_t...>::execute_internal(
    const invoke_single_t&   invokeSingle,
    const invoke_multiple_t& invokeMultiple) noexcept
{
    clear_dead();
    if (!m_optFunctions)
    {
        if constexpr (std::is_void_v<return_t>)
            return;
        else
            return return_t {};
    }

#if (QX_CLANG || QX_APPLE_CLANG) && QX_LIBCPP
    // Work around recursive constraint evaluation in Bloomberg clang/libc++ when delegate arguments include
    // std::expected: copying the map or comparing its iterators can trigger an invalid operator== lookup.

    // modifying during iteration protection
    thread_local variant_type tempFunctions;
    if (std::holds_alternative<single_value_type>(*m_optFunctions))
    {
        tempFunctions.template emplace<single_value_type>(std::get<single_value_type>(*m_optFunctions));
        return invokeSingle(std::get<single_value_type>(tempFunctions).second);
    }
    else
    {
        const container_type& source = std::get<container_type>(*m_optFunctions);
        if (!std::holds_alternative<container_type>(tempFunctions))
            tempFunctions.template emplace<container_type>();
        container_type& container = std::get<container_type>(tempFunctions);
        bool            sameKeys  = source.size() == container.size();
        if (sameKeys)
        {
            auto sourceIt = source.begin();
            auto targetIt = container.begin();
            for (size_t i = 0; i < source.size(); ++i, ++sourceIt, ++targetIt)
                if (!(sourceIt->first == targetIt->first))
                {
                    sameKeys = false;
                    break;
                }
        }

        auto sourceIt = source.begin();
        if (sameKeys)
        {
            auto targetIt = container.begin();
            for (size_t i = 0; i < source.size(); ++i, ++sourceIt, ++targetIt)
                targetIt->second = sourceIt->second;
        }
        else
        {
            container.clear();
            for (size_t i = 0; i < source.size(); ++i, ++sourceIt)
                container.try_emplace(sourceIt->first, sourceIt->second);
        }

        invoker<return_t, function_type, invoke_single_t>   invokerSingle(invokeSingle);
        invoker<return_t, function_type, invoke_multiple_t> invokerMultiple(invokeMultiple);
        base_invoker<return_t, function_type>*              invoker = nullptr;
        if (container.size() == 1)
            invoker = &invokerSingle;
        else
            invoker = &invokerMultiple;
        if constexpr (std::is_void_v<return_t>)
        {
            size_t index = 0;
            for (auto it = container.begin(); index < container.size(); ++it, ++index)
                invoker->invoke(it->second);

            return;
        }
        else if constexpr (delegate_pipe_c<return_t>)
        {
            return_t result {};
            size_t   index = 0;
            for (auto it = container.begin(); index < container.size(); ++it, ++index)
                result = result | invoker->invoke(it->second);

            return result;
        }
        else
        {
            return_t result {};
            size_t   index = 0;
            for (auto it = container.begin(); index < container.size(); ++it, ++index)
                result = invoker->invoke(it->second);

            return result;
        }
    }
#else
    // modifying during iteration protection
    thread_local variant_type tempFunctions;
    tempFunctions = *m_optFunctions;

    if (std::holds_alternative<single_value_type>(tempFunctions))
    {
        const auto& [_, function] = std::get<single_value_type>(tempFunctions);
        return invokeSingle(function);
    }
    else
    {
        const container_type& container = std::get<container_type>(tempFunctions);

        invoker<return_t, function_type, invoke_single_t>   invokerSingle(invokeSingle);
        invoker<return_t, function_type, invoke_multiple_t> invokerMultiple(invokeMultiple);
        base_invoker<return_t, function_type>*              invoker = nullptr;
        if (container.size() == 1)
            invoker = &invokerSingle;
        else
            invoker = &invokerMultiple;

        if constexpr (std::is_void_v<return_t>)
        {
            for (const auto& [_, function] : container)
                invoker->invoke(function);

            return;
        }
        else if constexpr (delegate_pipe_c<return_t>)
        {
            return_t result {};
            for (const auto& [_, function] : container)
                result = result | invoker->invoke(function);

            return result;
        }
        else
        {
            return_t result {};
            for (const auto& [_, function] : container)
                result = invoker->invoke(function);

            return result;
        }
    }
#endif
}

template<class derived_t, class return_t, class... args_t>
template<class object_t, callable_c<return_t, object_t*, args_t...> callable_t>
void base_delegate<derived_t, return_t, args_t...>::add_weak(
    time_ordered_priority_key key,
    std::weak_ptr<object_t>   pWeakObject,
    callable_t                callable) noexcept
{
    m_WeakSubscriptions.emplace(key, pWeakObject);
    add_function(
        key,
        [pWeakObject, callable_ = std::move(callable)](args_t... args)
        {
            if (std::shared_ptr<object_t> pObject = pWeakObject.lock())
                return callable_(pObject.get(), std::forward<args_t>(args)...);

            return return_t();
        });
}

template<class derived_t, class return_t, class... args_t>
destruction_callback base_delegate<derived_t, return_t, args_t...>::add_destruction_callback(
    time_ordered_priority_key key,
    function_type             value) noexcept
{
    add_function(key, std::move(value));

    if (!m_pDelegateAliveMarker)
        m_pDelegateAliveMarker = std::make_shared<base_delegate*>(this);

    return [key, pDelegateAliveMarker = std::weak_ptr(m_pDelegateAliveMarker)]()
    {
        if (const auto pDelegate = pDelegateAliveMarker.lock())
            (*pDelegate)->remove(key);
    };
}

template<class derived_t, class return_t, class... args_t>
void base_delegate<derived_t, return_t, args_t...>::add_function(
    time_ordered_priority_key key,
    function_type             function) noexcept
{
    if (!m_optFunctions)
    {
        m_optFunctions = variant_type(single_value_type(key, std::move(function)));
    }
    else if (std::holds_alternative<single_value_type>(*m_optFunctions))
    {
        single_value_type first = std::get<single_value_type>(std::move(*m_optFunctions));
        container_type    container;
        container.try_emplace(first.first, std::move(first.second));
        container.try_emplace(key, std::move(function));
        m_optFunctions = std::move(container);
    }
    else
    {
        std::get<container_type>(*m_optFunctions).try_emplace(key, std::move(function));
    }
}

} // namespace details

template<class return_t, class... args_t>
    requires(sizeof...(args_t) > 0 && (!std::is_void_v<args_t> && ...))
return_t delegate<return_t(args_t...)>::execute(args_t... args) noexcept
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
return_t delegate<return_t(void)>::execute() noexcept
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
