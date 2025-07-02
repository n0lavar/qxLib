/**

    @file      test_delegate.cpp
    @author    Khrapov
    @date      7.01.2024
    @copyright © Nick Khrapov, 2024. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_delegate.cpp

#include <qx/patterns/delegate.h>

#include <qx/containers/string/string.h>
#include <qx/meta/type_strings.h>

#include <span>




struct sum_pipe
{
    sum_pipe operator|(const sum_pipe& pipe) const
    {
        return { .nData = nData + pipe.nData, .sData = sData + pipe.sData };
    }

    int        nData = 0;
    qx::string sData;
};




class tracker
{
public:
    void add_name(std::string_view svName)
    {
        m_Names.emplace_back(svName);
    }

    std::span<const std::string> get_names() const
    {
        return m_Names;
    }

    void clear()
    {
        m_Names.clear();
    }

private:
    std::vector<std::string> m_Names;
};
static tracker g_Tracker;

template<class return_t, class... args_t>
qx::cstring get_callable_name(qx::cstring_view svFunctionName)
{
    qx::cstring sResult = qx::cstring(qx::type_strings<return_t, char>::get_signature()) + " " + svFunctionName + "(";
    bool        bFirst  = true;
    ((sResult += qx::cstring(bFirst ? "" : ", ") + qx::type_strings<args_t, char>::get_signature(), bFirst = false),
     ...);
    sResult += ")";
    return sResult;
}




// ------------------------------------------------------ function -----------------------------------------------------

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
static return_t function(args_t... args)
{
    g_Tracker.add_name(get_callable_name<return_t, args_t...>(QX_STRINGIFY(function)));
    return get_get_result_t::value(args...);
}

// ------------------------------------------------------- lambda ------------------------------------------------------

#if 1

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
static auto get_lambda()
{
    if constexpr (sizeof...(args_t) == 0 || (std::is_void_v<args_t> && ...))
    {
        return []()
        {
            g_Tracker.add_name(get_callable_name<return_t, args_t...>("lambda"));
            return get_get_result_t::value();
        };
    }
    else
    {
        return [](args_t... args)
        {
            g_Tracker.add_name(get_callable_name<return_t, args_t...>("lambda"));
            return get_get_result_t::value(args...);
        };
    }
}

#elif 0

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
    requires(sizeof...(args_t) > 0 && (!std::is_void_v<args_t> && ...))
static auto get_lambda()
{
    return [](args_t... args)
    {
        g_Tracker.add_name(get_callable_name<return_t, args_t...>("lambda"));
        return get_get_result_t::value(args...);
    };
}

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
    requires(sizeof...(args_t) == 0 || (std::is_void_v<args_t> && ...))
static auto get_lambda()
{
    return []()
    {
        g_Tracker.add_name(get_callable_name<return_t>("lambda"));
        return get_get_result_t::value();
    };
}

#else

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct lambda_getter
{
    static auto get()
    {
        return [](args_t... args)
        {
            g_Tracker.add_name(get_callable_name<return_t, args_t...>("lambda"));
            return get_get_result_t::value(args...);
        };
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t>
struct lambda_getter<get_get_result_t::value, return_t, void>
{
    static auto get()
    {
        return []()
        {
            g_Tracker.add_name(get_callable_name<return_t>("lambda"));
            return get_get_result_t::value();
        };
    }
};

template<class get_get_result_t, class... args_t>
struct lambda_getter<get_get_result_t::value, void, args_t...>
{
    static auto get()
    {
        return [](args_t... args)
        {
            g_Tracker.add_name(get_callable_name<void, args_t...>("lambda"));
            get_get_result_t::value(args...);
        };
    }
};

template<class get_get_result_t>
struct lambda_getter<get_get_result_t::value, void, void>
{
    static auto get()
    {
        return []()
        {
            g_Tracker.add_name(get_callable_name<void>("lambda"));
            get_get_result_t::value();
        };
    }
};

#endif


// ----------------------------------------------------- component -----------------------------------------------------

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
class method_component
{
public:
    return_t callback(args_t... args)
    {
        g_Tracker.add_name(get_callable_name<return_t, args_t...>(QX_STRINGIFY(callback)));
        return get_get_result_t::value(args...);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
class static_method_component
{
public:
    static return_t callback(args_t... args)
    {
        g_Tracker.add_name(get_callable_name<return_t, args_t...>(QX_STRINGIFY(callback)));
        return get_get_result_t::value(args...);
    }
};




template<qx::delegate_return_c return_t, class... args_t>
struct base_delegate_token_strategy
{
    void remove(qx::delegate<return_t, args_t...>& delegate)
    {
        delegate.remove(delegateToken);
    }

    qx::delegate_token_type delegateToken;
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct free_lambda_strategy : base_delegate_token_strategy<return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateToken = delegate.add_free(get_lambda<get_get_result_t, return_t, args_t...>(), ePriority);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct free_function_strategy : base_delegate_token_strategy<return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateToken = delegate.add_free(&function<get_get_result_t, return_t, args_t...>, ePriority);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct free_static_function_strategy : base_delegate_token_strategy<return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateToken =
            delegate.add_free(&static_method_component<get_get_result_t, return_t, args_t...>::callback, ePriority);
    }
};

template<qx::delegate_return_c return_t, class... args_t>
struct base_destruction_callback_strategy
{
    void remove(qx::delegate<return_t, args_t...>& delegate)
    {
        delegateDestructionCallback = qx::destruction_callback();
    }

    qx::destruction_callback delegateDestructionCallback;
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct destruction_callback_lambda_strategy : base_destruction_callback_strategy<return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateDestructionCallback =
            delegate.add_destruction_callback(get_lambda<get_get_result_t, return_t, args_t...>(), ePriority);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct destruction_callback_function_strategy : base_destruction_callback_strategy<return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateDestructionCallback =
            delegate.add_destruction_callback(&function<get_get_result_t, return_t, args_t...>, ePriority);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct destruction_callback_static_function_strategy : base_destruction_callback_strategy<return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateDestructionCallback = delegate.add_destruction_callback(
            &static_method_component<get_get_result_t, return_t, args_t...>::callback,
            ePriority);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct destruction_callback_method_strategy : base_destruction_callback_strategy<return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateDestructionCallback = delegate.add_destruction_callback(
            component,
            &method_component<get_get_result_t, return_t, args_t...>::callback,
            ePriority);
    }

    method_component<get_get_result_t, return_t, args_t...> component;
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct base_weak_strategy : base_delegate_token_strategy<return_t, args_t...>
{
    std::shared_ptr<method_component<get_get_result_t, return_t, args_t...>> pComponent =
        std::make_shared<method_component<get_get_result_t, return_t, args_t...>>();
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct weak_lambda_strategy : base_weak_strategy<get_get_result_t, return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateToken = delegate.add_weak(
            std::weak_ptr<method_component<get_get_result_t, return_t, args_t...>>(this->pComponent),
            get_lambda<get_get_result_t, return_t, args_t...>(),
            ePriority);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct weak_function_strategy : base_weak_strategy<get_get_result_t, return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateToken = delegate.add_weak(
            std::weak_ptr<method_component<get_get_result_t, return_t, args_t...>>(this->pComponent),
            &function<get_get_result_t, return_t, args_t...>,
            ePriority);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct weak_static_function_strategy : base_weak_strategy<get_get_result_t, return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateToken = delegate.add_weak(
            std::weak_ptr<method_component<get_get_result_t, return_t, args_t...>>(this->pComponent),
            &static_method_component<get_get_result_t, return_t, args_t...>::callback,
            ePriority);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct weak_method_strategy : base_weak_strategy<get_get_result_t, return_t, args_t...>
{
    void add(qx::delegate<return_t, args_t...>& delegate, qx::priority ePriority)
    {
        this->delegateToken = delegate.add_weak(
            std::weak_ptr<method_component<get_get_result_t, return_t, args_t...>>(this->pComponent),
            &method_component<get_get_result_t, return_t, args_t...>::callback,
            ePriority);
    }
};




template<qx::delegate_return_c return_t, class... args_t>
struct get_get_result
{
    static sum_pipe call(args_t... args)
    {
        return sum_pipe { args... };
    }
    static constexpr auto value = &call;
};

template<>
struct get_get_result<void, void>
{
    static constexpr void call()
    {
    }
    static constexpr auto value = &call;
};

template<class... args_t>
struct get_get_result<void, args_t...>
{
    static constexpr void call(args_t...)
    {
    }
    static constexpr auto value = &call;
};

template<qx::delegate_return_c return_t>
struct get_get_result<return_t, void>
{
    static sum_pipe call()
    {
        return sum_pipe {};
    }
    static constexpr auto value = &call;
};




template<template<class, qx::delegate_return_c, class...> class... test_case_strategies_t>
struct strategies_list
{
};




template<class strategies_list_t, qx::delegate_return_c return_t, class... args_t>
struct test_case_traits;

template<
    template<class, qx::delegate_return_c, class...> class... test_case_strategies_t,
    qx::delegate_return_c return_t,
    class... args_t>
struct test_case_traits<strategies_list<test_case_strategies_t...>, return_t, args_t...>
{
    using delegate_type = qx::delegate<return_t, args_t...>;
    using strategies_type =
        std::tuple<test_case_strategies_t<get_get_result<return_t, args_t...>, return_t, args_t...>...>;
};

// using T               = test_case_traits<strategies_list<weak_lambda_strategy>, sum_pipe, void>;
// using delegate_type   = T::delegate_type;
// using strategies_type = T::strategies_type;



template<class StrategiesList, class ArgsTuplesList>
struct cartesian_product;

template<template<class, qx::delegate_return_c, class...> class... Strategies, class... ArgsTuples>
struct cartesian_product<strategies_list<Strategies...>, std::tuple<ArgsTuples...>>
{
    using type = std::tuple<test_case_traits<
        strategies_list<Strategies>,
        std::tuple_element_t<0, ArgsTuples>,
        std::tuple_element_t<1, ArgsTuples>...>...>;
};

template<class StrategiesList, class ReturnArgsTuples>
struct inner_traits_generator;

template<template<class, qx::delegate_return_c, class...> class... Strategies, class... ReturnArgsTuples>
struct inner_traits_generator<strategies_list<Strategies...>, std::tuple<ReturnArgsTuples...>>
{
private:
    template<template<class, qx::delegate_return_c, class...> class Strategy>
    struct expand_strategy
    {
        template<class ArgsTuple>
        struct expand_args_tuple;

        template<class Return, class... Args>
        struct expand_args_tuple<std::tuple<Return, std::tuple<Args...>>>
        {
            using type = test_case_traits<strategies_list<Strategy>, Return, Args...>;
        };

        using type = std::tuple<typename expand_args_tuple<ReturnArgsTuples>::type...>;
    };

    using nested = std::tuple<typename expand_strategy<Strategies>::type...>;

    template<class... Lists>
    struct flatten;

    template<class... Ts>
    struct flatten<std::tuple<Ts...>>
    {
        using type = ::testing::Types<Ts...>;
    };

    template<class... Ts, class... Us, class... Rest>
    struct flatten<std::tuple<Ts...>, std::tuple<Us...>, Rest...>
    {
        using type = typename flatten<std::tuple<Ts..., Us...>, Rest...>::type;
    };

public:
    using type = typename flatten<typename expand_strategy<Strategies>::type...>::type;
};

template<class strategies_list_t, class return_values_tuple_t, class args_values_tuples_tuple_t>
struct traits_generator;

template<
    template<class, qx::delegate_return_c, class...> class... all_strategies_t,
    class... return_values_t,
    class... args_values_tuples_t>
struct traits_generator<
    strategies_list<all_strategies_t...>,
    std::tuple<return_values_t...>,
    std::tuple<args_values_tuples_t...>>
{
    using return_args_combinations =
        qx::tuple_utils::cartesian_product_t<std::tuple<return_values_t...>, std::tuple<args_values_tuples_t...>>;
    using type = typename inner_traits_generator<strategies_list<all_strategies_t...>, return_args_combinations>::type;
};

using implementations_type = traits_generator<
    strategies_list<
        free_lambda_strategy,
        free_function_strategy,
        free_static_function_strategy,
        destruction_callback_lambda_strategy,
        destruction_callback_function_strategy,
        destruction_callback_static_function_strategy,
        destruction_callback_method_strategy,
        weak_lambda_strategy,
        weak_function_strategy,
        weak_static_function_strategy>,
    std::tuple<void, sum_pipe>,
    std::tuple<std::tuple<void>, std::tuple<int>, std::tuple<int, qx::string>>>::type;

template<class traits_t>
class test_delegate : public ::testing::Test
{
protected:
    typename traits_t::delegate_type   m_Delegate;
    typename traits_t::strategies_type m_Strategies;
};

TYPED_TEST_SUITE(test_delegate, implementations_type);


template<typename T>
struct CPrintType
{
    // Always triggers, embedding the full type in the function signature
    static void print()
    {
        static_assert(std::is_same_v<T, void>, __FUNCSIG__);
    }
};

TYPED_TEST(test_delegate, construct)
{
    // CPrintType<implementations_type>::print();
    auto add = [this](auto& strategy)
    {
        strategy.add(this->m_Delegate, qx::priority::normal);
    };

    std::apply(
        [&add](auto&&... args)
        {
            ((add(args)), ...);
        },
        this->m_Strategies);

    //this->m_Delegate.broadcast();

    using T = testing::internal::ProxyTypeList<
        test_case_traits<strategies_list<free_lambda_strategy>, void, void>,
        test_case_traits<strategies_list<free_lambda_strategy>, void, int>,
        test_case_traits<strategies_list<free_lambda_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<free_lambda_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<free_lambda_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<free_lambda_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<free_function_strategy>, void, void>,
        test_case_traits<strategies_list<free_function_strategy>, void, int>,
        test_case_traits<strategies_list<free_function_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<free_function_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<free_function_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<free_function_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<free_static_function_strategy>, void, void>,
        test_case_traits<strategies_list<free_static_function_strategy>, void, int>,
        test_case_traits<strategies_list<free_static_function_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<free_static_function_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<free_static_function_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<free_static_function_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<destruction_callback_lambda_strategy>, void, void>,
        test_case_traits<strategies_list<destruction_callback_lambda_strategy>, void, int>,
        test_case_traits<strategies_list<destruction_callback_lambda_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<destruction_callback_lambda_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<destruction_callback_lambda_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<destruction_callback_lambda_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<destruction_callback_function_strategy>, void, void>,
        test_case_traits<strategies_list<destruction_callback_function_strategy>, void, int>,
        test_case_traits<strategies_list<destruction_callback_function_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<destruction_callback_function_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<destruction_callback_function_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<destruction_callback_function_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<destruction_callback_static_function_strategy>, void, void>,
        test_case_traits<strategies_list<destruction_callback_static_function_strategy>, void, int>,
        test_case_traits<strategies_list<destruction_callback_static_function_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<destruction_callback_static_function_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<destruction_callback_static_function_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<destruction_callback_static_function_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<destruction_callback_method_strategy>, void, void>,
        test_case_traits<strategies_list<destruction_callback_method_strategy>, void, int>,
        test_case_traits<strategies_list<destruction_callback_method_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<destruction_callback_method_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<destruction_callback_method_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<destruction_callback_method_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<weak_lambda_strategy>, void, void>,
        test_case_traits<strategies_list<weak_lambda_strategy>, void, int>,
        test_case_traits<strategies_list<weak_lambda_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<weak_lambda_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<weak_lambda_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<weak_lambda_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<weak_function_strategy>, void, void>,
        test_case_traits<strategies_list<weak_function_strategy>, void, int>,
        test_case_traits<strategies_list<weak_function_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<weak_function_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<weak_function_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<weak_function_strategy>, sum_pipe, int, qx::string>,
        test_case_traits<strategies_list<weak_static_function_strategy>, void, void>,
        test_case_traits<strategies_list<weak_static_function_strategy>, void, int>,
        test_case_traits<strategies_list<weak_static_function_strategy>, void, int, qx::string>,
        test_case_traits<strategies_list<weak_static_function_strategy>, sum_pipe, void>,
        test_case_traits<strategies_list<weak_static_function_strategy>, sum_pipe, int>,
        test_case_traits<strategies_list<weak_static_function_strategy>, sum_pipe, int, qx::string>>;
    g_Tracker.clear();
}
