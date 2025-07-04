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

    bool operator==(const sum_pipe&) const = default;

    size_t     nData = 0;
    qx::string sData;
};

enum class callable_type
{
    lambda,
    function,
    static_method,
    method
};

static std::vector<callable_type> g_Tracker;




// ----------------------------------------------------- callables -----------------------------------------------------

template<class get_get_result_t, qx::delegate_return_c return_t, class args_tuple_t>
struct get_lambda;

template<class get_get_result_t, qx::delegate_return_c return_t>
struct get_lambda<get_get_result_t, return_t, std::tuple<void>>
{
    static constexpr auto value = []()
    {
        g_Tracker.push_back(callable_type::lambda);
        return get_get_result_t::value();
    };
};

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct get_lambda<get_get_result_t, return_t, std::tuple<args_t...>>
{
    static constexpr auto value = [](args_t... args)
    {
        g_Tracker.push_back(callable_type::lambda);
        return get_get_result_t::value(args...);
    };
};




template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
static return_t function(args_t... args)
{
    g_Tracker.push_back(callable_type::function);
    return get_get_result_t::value(args...);
}

template<class get_get_result_t, qx::delegate_return_c return_t, class args_tuple_t>
struct get_function;

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct get_function<get_get_result_t, return_t, std::tuple<args_t...>>
{
    static constexpr auto value = function<get_get_result_t, return_t, args_t...>;
};

template<class get_get_result_t, qx::delegate_return_c return_t>
struct get_function<get_get_result_t, return_t, std::tuple<void>>
{
    static constexpr auto value = function<get_get_result_t, return_t>;
};




template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
class static_method_component
{
public:
    static return_t callback(args_t... args)
    {
        g_Tracker.push_back(callable_type::static_method);
        return get_get_result_t::value(args...);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t>
class static_method_component<get_get_result_t, return_t, void>
{
public:
    static return_t callback()
    {
        g_Tracker.push_back(callable_type::static_method);
        return get_get_result_t::value();
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t, class args_tuple_t>
struct get_static_method;

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
struct get_static_method<get_get_result_t, return_t, std::tuple<args_t...>>
{
    static constexpr auto value = static_method_component<get_get_result_t, return_t, args_t...>::callback;
};




template<class get_get_result_t, qx::delegate_return_c return_t, class args_tuple_t>
class method_component;

template<class get_get_result_t, qx::delegate_return_c return_t, class... args_t>
class method_component<get_get_result_t, return_t, std::tuple<args_t...>>
{
public:
    return_t callback(args_t... args)
    {
        g_Tracker.push_back(callable_type::method);
        return get_get_result_t::value(args...);
    }
};

template<class get_get_result_t, qx::delegate_return_c return_t>
class method_component<get_get_result_t, return_t, std::tuple<std::type_identity<void>>>
{
public:
    return_t callback()
    {
        g_Tracker.push_back(callable_type::method);
        return get_get_result_t::value();
    }
};




// ---------------------------------------------- execute args generator ---------------------------------------------

static size_t get_next_value(size_t nValue)
{
    return (nValue + 1) * 2;
}

template<qx::delegate_return_c return_t, class... args_t>
struct execute_generator;

template<>
struct execute_generator<void, void>
{
    static void execute(qx::delegate<void, void>& delegate, size_t)
    {
        delegate.execute();
    }
};

template<>
struct execute_generator<void, size_t>
{
    static void execute(qx::delegate<void, size_t>& delegate, size_t nBroadcast)
    {
        delegate.execute(get_next_value(nBroadcast));
    }
};

template<>
struct execute_generator<void, size_t, const qx::string&>
{
    static void execute(qx::delegate<void, size_t, const qx::string&>& delegate, size_t nBroadcast)
    {
        size_t nNextValue = get_next_value(nBroadcast);
        delegate.execute(nNextValue, qx::string::static_from(nNextValue));
    }
};

template<>
struct execute_generator<sum_pipe, void>
{
    static sum_pipe execute(qx::delegate<sum_pipe, void>& delegate, size_t)
    {
        return delegate.execute();
    }
};

template<>
struct execute_generator<sum_pipe, size_t>
{
    static sum_pipe execute(qx::delegate<sum_pipe, size_t>& delegate, size_t nBroadcast)
    {
        return delegate.execute(get_next_value(nBroadcast));
    }
};

template<>
struct execute_generator<sum_pipe, size_t, const qx::string&>
{
    static sum_pipe execute(qx::delegate<sum_pipe, size_t, const qx::string&>& delegate, size_t nBroadcast)
    {
        size_t nNextValue = get_next_value(nBroadcast);
        return delegate.execute(nNextValue, qx::string::static_from(nNextValue));
    }
};




// --------------------------------------------- callable result generator ---------------------------------------------

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




// ------------------------------------------------------- traits ------------------------------------------------------

// gcc and clang have a compiler bug not allowing to compile std::shared_ptr<T<std::tuple<void>>>
template<class T>
struct replace_void
{
    using type = T;
};

template<>
struct replace_void<void>
{
    using type = std::type_identity<void>;
};

template<qx::delegate_return_c return_t, class... args_t>
struct delegate_fixture_traits
{
    using return_type         = return_t;
    using args_tuple_type     = std::tuple<args_t...>;
    using delegate_type       = qx::delegate<return_t, args_t...>;
    using get_get_result_type = get_get_result<return_t, args_t...>;
    using method_component_type =
        method_component<get_get_result_type, return_type, std::tuple<typename replace_void<args_t>::type...>>;
    using execute_generator = execute_generator<return_t, args_t...>;
};

using implementations_type = ::testing::Types<
    delegate_fixture_traits<void, void>,
    delegate_fixture_traits<void, size_t>,
    delegate_fixture_traits<void, size_t, const qx::string&>,
    delegate_fixture_traits<sum_pipe, void>,
    delegate_fixture_traits<sum_pipe, size_t>,
    delegate_fixture_traits<sum_pipe, size_t, const qx::string&>>;

template<class traits_t>
class delegate_base_fixture : public ::testing::Test
{
protected:
    void TearDown() override
    {
        Test::TearDown();
        check_execute(true);
    }

    void check_execute(bool bExpectFilled)
        requires(std::is_void_v<typename traits_t::return_type>)
    {
        size_t nBroadcast = 0;

        traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 1 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 2 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 3 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        g_Tracker.clear();
    }

    void check_execute(bool bExpectFilled)
        requires(
            !std::is_void_v<typename traits_t::return_type>
            && std::tuple_size_v<typename traits_t::args_tuple_type> == 1
            && std::is_same_v<std::tuple_element_t<0, typename traits_t::args_tuple_type>, void>)
    {
        size_t nBroadcast = 0;

        sum_pipe result1 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result1, sum_pipe());
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 1 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        sum_pipe result2 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result2, sum_pipe());
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 2 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        sum_pipe result3 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result3, sum_pipe());
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 3 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        g_Tracker.clear();
    }

    void check_execute(bool bExpectFilled)
        requires(
            !std::is_void_v<typename traits_t::return_type>
            && std::tuple_size_v<typename traits_t::args_tuple_type> == 1
            && std::is_same_v<std::tuple_element_t<0, typename traits_t::args_tuple_type>, size_t>)
    {
        size_t nBroadcast = 0;

        sum_pipe result1 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result1.nData, bExpectFilled ? 2 : 0);
        EXPECT_EQ(result1.sData, QX_TEXT(""));
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 1 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        sum_pipe result2 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result2.nData, bExpectFilled ? 4 : 0);
        EXPECT_EQ(result2.sData, QX_TEXT(""));
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 2 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        sum_pipe result3 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result3.nData, bExpectFilled ? 6 : 0);
        EXPECT_EQ(result3.sData, QX_TEXT(""));
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 3 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        g_Tracker.clear();
    }

    void check_execute(bool bExpectFilled)
        requires(
            !std::is_void_v<typename traits_t::return_type>
            && std::tuple_size_v<typename traits_t::args_tuple_type> == 2)
    {
        size_t nBroadcast = 0;

        sum_pipe result1 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result1.nData, bExpectFilled ? 2 : 0);
        EXPECT_EQ(result1.sData, bExpectFilled ? QX_TEXT("2") : QX_TEXT(""));
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 1 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        sum_pipe result2 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result2.nData, bExpectFilled ? 4 : 0);
        EXPECT_EQ(result2.sData, bExpectFilled ? QX_TEXT("4") : QX_TEXT(""));
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 2 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        sum_pipe result3 = traits_t::execute_generator::execute(m_Delegate, nBroadcast++);
        EXPECT_EQ(result3.nData, bExpectFilled ? 6 : 0);
        EXPECT_EQ(result3.sData, bExpectFilled ? QX_TEXT("6") : QX_TEXT(""));
        EXPECT_EQ(g_Tracker.size(), bExpectFilled ? 3 : 0);
        if (bExpectFilled)
            EXPECT_EQ(g_Tracker.back(), *m_optCallableType);

        g_Tracker.clear();
    }

protected:
    typename traits_t::delegate_type m_Delegate;
    std::optional<callable_type>     m_optCallableType;
};




// ---------------------------------------------------- free fixture ---------------------------------------------------

template<class traits_t>
class delegate_free_fixture : public delegate_base_fixture<traits_t>
{
};

TYPED_TEST_SUITE(delegate_free_fixture, implementations_type);

TYPED_TEST(delegate_free_fixture, free_lambda)
{
    this->m_optCallableType = callable_type::lambda;
    this->m_Delegate.add_free(get_lambda<
                              typename TypeParam::get_get_result_type,
                              typename TypeParam::return_type,
                              typename TypeParam::args_tuple_type>::value);
}

TYPED_TEST(delegate_free_fixture, free_function)
{
    this->m_optCallableType = callable_type::function;
    this->m_Delegate.add_free(get_function<
                              typename TypeParam::get_get_result_type,
                              typename TypeParam::return_type,
                              typename TypeParam::args_tuple_type>::value);
}

TYPED_TEST(delegate_free_fixture, free_static_method)
{
    this->m_optCallableType = callable_type::static_method;
    this->m_Delegate.add_free(get_static_method<
                              typename TypeParam::get_get_result_type,
                              typename TypeParam::return_type,
                              typename TypeParam::args_tuple_type>::value);
}




// -------------------------------------------- destruction callback fixture -------------------------------------------

template<class traits_t>
class delegate_destruction_callback_fixture : public delegate_base_fixture<traits_t>
{
protected:
    void TearDown() override
    {
        delegate_base_fixture<traits_t>::TearDown();

        m_DelegateDestructionCallback = qx::destruction_callback();
        delegate_base_fixture<traits_t>::check_execute(false);
    }

protected:
    qx::destruction_callback m_DelegateDestructionCallback;
};

TYPED_TEST_SUITE(delegate_destruction_callback_fixture, implementations_type);

TYPED_TEST(delegate_destruction_callback_fixture, destruction_callback_lambda)
{
    this->m_optCallableType = callable_type::lambda;
    this->m_DelegateDestructionCallback =
        this->m_Delegate.add_destruction_callback(get_lambda<
                                                  typename TypeParam::get_get_result_type,
                                                  typename TypeParam::return_type,
                                                  typename TypeParam::args_tuple_type>::value);
}

TYPED_TEST(delegate_destruction_callback_fixture, destruction_callback_function)
{
    this->m_optCallableType = callable_type::function;
    this->m_DelegateDestructionCallback =
        this->m_Delegate.add_destruction_callback(get_function<
                                                  typename TypeParam::get_get_result_type,
                                                  typename TypeParam::return_type,
                                                  typename TypeParam::args_tuple_type>::value);
}

TYPED_TEST(delegate_destruction_callback_fixture, destruction_callback_static_method)
{
    this->m_optCallableType = callable_type::static_method;
    this->m_DelegateDestructionCallback =
        this->m_Delegate.add_destruction_callback(get_static_method<
                                                  typename TypeParam::get_get_result_type,
                                                  typename TypeParam::return_type,
                                                  typename TypeParam::args_tuple_type>::value);
}

TYPED_TEST(delegate_destruction_callback_fixture, destruction_callback_method)
{
    this->m_optCallableType = callable_type::method;
    typename TypeParam::method_component_type component;
    this->m_DelegateDestructionCallback =
        this->m_Delegate.add_destruction_callback(component, &TypeParam::method_component_type::callback);
}




// ---------------------------------------------------- weak fixture ---------------------------------------------------

template<class traits_t>
class delegate_weak_fixture : public delegate_base_fixture<traits_t>
{
protected:
    void TearDown() override
    {
        delegate_base_fixture<traits_t>::TearDown();

        m_pComponent.reset();
        delegate_base_fixture<traits_t>::check_execute(false);
    }

protected:
    std::shared_ptr<typename traits_t::method_component_type> m_pComponent =
        std::make_shared<typename traits_t::method_component_type>();
    qx::delegate_token_type m_DelegateToken;
};

TYPED_TEST_SUITE(delegate_weak_fixture, implementations_type);

TYPED_TEST(delegate_weak_fixture, weak_lambda)
{
    this->m_optCallableType = callable_type::lambda;
    this->m_DelegateToken   = this->m_Delegate.add_weak(
        std::weak_ptr<typename TypeParam::method_component_type>(this->m_pComponent),
        get_lambda<
              typename TypeParam::get_get_result_type,
              typename TypeParam::return_type,
              typename TypeParam::args_tuple_type>::value);
}

TYPED_TEST(delegate_weak_fixture, weak_function)
{
    this->m_optCallableType = callable_type::function;
    this->m_DelegateToken   = this->m_Delegate.add_weak(
        std::weak_ptr<typename TypeParam::method_component_type>(this->m_pComponent),
        get_function<
              typename TypeParam::get_get_result_type,
              typename TypeParam::return_type,
              typename TypeParam::args_tuple_type>::value);
}

TYPED_TEST(delegate_weak_fixture, weak_static_method)
{
    this->m_optCallableType = callable_type::static_method;
    this->m_DelegateToken   = this->m_Delegate.add_weak(
        std::weak_ptr<typename TypeParam::method_component_type>(this->m_pComponent),
        get_static_method<
              typename TypeParam::get_get_result_type,
              typename TypeParam::return_type,
              typename TypeParam::args_tuple_type>::value);
}




class delegate_common_tests_fixture : public ::testing::Test
{
protected:
    using return_type         = sum_pipe;
    using args_tuple_type     = std::tuple<size_t, const qx::string&>;
    using delegate_type       = qx::delegate<sum_pipe, size_t, const qx::string&>;
    using get_get_result_type = get_get_result<sum_pipe, size_t, const qx::string&>;

protected:
    void SetUp() override
    {
        m_Token1 = m_Delegate.add_free(get_lambda<get_get_result_type, sum_pipe, args_tuple_type>::value);
        m_Token2 = m_Delegate.add_free(get_function<get_get_result_type, sum_pipe, args_tuple_type>::value);
        m_Token3 = m_Delegate.add_free(get_static_method<get_get_result_type, sum_pipe, args_tuple_type>::value);
    }

protected:
    delegate_type           m_Delegate;
    qx::delegate_token_type m_Token1;
    qx::delegate_token_type m_Token2;
    qx::delegate_token_type m_Token3;
};


// ------------------------------------------------- check pipe result -------------------------------------------------

TEST_F(delegate_common_tests_fixture, pipe)
{
    std::vector expectedResult { callable_type::lambda, callable_type::function, callable_type::static_method };

    sum_pipe result1 = m_Delegate.execute(5, QX_TEXT("1"));
    EXPECT_EQ(result1.nData, 15);
    EXPECT_EQ(result1.sData, QX_TEXT("111"));
    EXPECT_EQ(g_Tracker, expectedResult);
    g_Tracker.clear();

    sum_pipe result2 = m_Delegate.execute(2, QX_TEXT("//"));
    EXPECT_EQ(result2.nData, 6);
    EXPECT_EQ(result2.sData, QX_TEXT("//////"));
    EXPECT_EQ(g_Tracker, expectedResult);
    g_Tracker.clear();
    sum_pipe result3 = m_Delegate.execute(0, QX_TEXT("-*/"));
    EXPECT_EQ(result3.nData, 0);
    EXPECT_EQ(result3.sData, QX_TEXT("-*/-*/-*/"));
    EXPECT_EQ(g_Tracker, expectedResult);
    g_Tracker.clear();
}




// ------------------------------------------------ check remove, clear ------------------------------------------------

TEST_F(delegate_common_tests_fixture, remove)
{
    sum_pipe result1 = m_Delegate.execute(5, QX_TEXT("1"));
    EXPECT_EQ(result1.nData, 15);
    EXPECT_EQ(result1.sData, QX_TEXT("111"));
    std::vector expectedResult1 { callable_type::lambda, callable_type::function, callable_type::static_method };
    EXPECT_EQ(g_Tracker, expectedResult1);
    g_Tracker.clear();

    EXPECT_TRUE(m_Delegate.remove(m_Token1));

    sum_pipe result2 = m_Delegate.execute(5, QX_TEXT("1"));
    EXPECT_EQ(result2.nData, 10);
    EXPECT_EQ(result2.sData, QX_TEXT("11"));
    std::vector expectedResult2 { callable_type::function, callable_type::static_method };
    EXPECT_EQ(g_Tracker, expectedResult2);
    g_Tracker.clear();

    EXPECT_TRUE(m_Delegate.remove(m_Token2));

    sum_pipe result3 = m_Delegate.execute(5, QX_TEXT("1"));
    EXPECT_EQ(result3.nData, 5);
    EXPECT_EQ(result3.sData, QX_TEXT("1"));
    std::vector expectedResult3 { callable_type::static_method };
    EXPECT_EQ(g_Tracker, expectedResult3);
    g_Tracker.clear();

    EXPECT_FALSE(m_Delegate.remove(m_Token2));

    sum_pipe result4 = m_Delegate.execute(5, QX_TEXT("1"));
    EXPECT_EQ(result4.nData, 5);
    EXPECT_EQ(result4.sData, QX_TEXT("1"));
    std::vector expectedResult4 { callable_type::static_method };
    EXPECT_EQ(g_Tracker, expectedResult4);
    g_Tracker.clear();

    EXPECT_TRUE(m_Delegate.remove(m_Token3));

    sum_pipe result5 = m_Delegate.execute(5, QX_TEXT("1"));
    EXPECT_EQ(result5.nData, 0);
    EXPECT_EQ(result5.sData, QX_TEXT(""));
    std::vector<callable_type> expectedResult5;
    EXPECT_EQ(g_Tracker, expectedResult5);
    g_Tracker.clear();
}

TEST_F(delegate_common_tests_fixture, clear)
{
    sum_pipe result1 = m_Delegate.execute(5, QX_TEXT("1"));
    EXPECT_EQ(result1.nData, 15);
    EXPECT_EQ(result1.sData, QX_TEXT("111"));
    std::vector expectedResult1 { callable_type::lambda, callable_type::function, callable_type::static_method };
    EXPECT_EQ(g_Tracker, expectedResult1);
    g_Tracker.clear();

    m_Delegate.clear();

    sum_pipe result2 = m_Delegate.execute(5, QX_TEXT("1"));
    EXPECT_EQ(result2.nData, 0);
    EXPECT_EQ(result2.sData, QX_TEXT(""));
    std::vector<callable_type> expectedResult2;
    EXPECT_EQ(g_Tracker, expectedResult2);
    g_Tracker.clear();
}




// ------------------------------------------------------ priority -----------------------------------------------------

TEST_F(delegate_common_tests_fixture, priority)
{
    m_Delegate.add_free(get_static_method<get_get_result_type, sum_pipe, args_tuple_type>::value, qx::priority::high);
    m_Delegate.add_free(get_lambda<get_get_result_type, sum_pipe, args_tuple_type>::value, qx::priority::very_high);
    m_Delegate.add_free(get_function<get_get_result_type, sum_pipe, args_tuple_type>::value, qx::priority::low);
    m_Delegate.add_free(
        get_static_method<get_get_result_type, sum_pipe, args_tuple_type>::value,
        qx::priority::very_low);
    m_Delegate.add_free(get_lambda<get_get_result_type, sum_pipe, args_tuple_type>::value, qx::priority::low);
    m_Delegate.add_free(get_function<get_get_result_type, sum_pipe, args_tuple_type>::value, qx::priority::high);

    m_Delegate.execute(5, QX_TEXT("1"));

    std::vector expectedResult { callable_type::lambda,   callable_type::static_method, callable_type::function,
                                 callable_type::lambda,   callable_type::function,      callable_type::static_method,
                                 callable_type::function, callable_type::lambda,        callable_type::static_method };
    EXPECT_EQ(g_Tracker, expectedResult);
    g_Tracker.clear();
}




// ------------------------------------------------ singlecast delegates -----------------------------------------------

TEST(delegate, singlecast)
{
    qx::delegate<sum_pipe, size_t, const qx::string&> delegate =
        qx::delegate<sum_pipe, size_t, const qx::string&>::create_singlecast(
            [](size_t, const qx::string&)
            {
                return sum_pipe();
            });
}
