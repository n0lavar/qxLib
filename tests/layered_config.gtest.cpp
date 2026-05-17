/**

    @file      layered_config.gtest.cpp
    @author    Khrapov
    @date      12.05.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

#include <qx/layered_config/layered_config_variable.h>

#include <cstdlib>

const qx::cstring k_sExeName = "app";

constexpr qx::cstring_view k_svIntRuntimeName    = "layered_config_test_int";
constexpr qx::cstring_view k_svSizeRuntimeName   = "layered_config_test_size";
constexpr qx::cstring_view k_svFloatRuntimeName  = "layered_config_test_float";
constexpr qx::cstring_view k_svStringRuntimeName = "layered_config_test_string";
constexpr qx::cstring_view k_svBoolRuntimeName   = "layered_config_test_bool";

constexpr qx::cstring_view k_svIntEnvName    = "QX_LAYERED_CONFIG_TEST_INT";
constexpr qx::cstring_view k_svSizeEnvName   = "QX_LAYERED_CONFIG_TEST_SIZE";
constexpr qx::cstring_view k_svFloatEnvName  = "QX_LAYERED_CONFIG_TEST_FLOAT";
constexpr qx::cstring_view k_svStringEnvName = "QX_LAYERED_CONFIG_TEST_STRING";
constexpr qx::cstring_view k_svBoolEnvName   = "QX_LAYERED_CONFIG_TEST_BOOL";

constexpr qx::cstring_view k_svIntCommandLineFullName    = "--layered-config-test-int";
constexpr qx::cstring_view k_svSizeCommandLineFullName   = "--layered-config-test-size";
constexpr qx::cstring_view k_svFloatCommandLineFullName  = "--layered-config-test-float";
constexpr qx::cstring_view k_svStringCommandLineFullName = "--layered-config-test-string";
constexpr qx::cstring_view k_svBoolCommandLineFullName   = "--layered-config-test-bool";

constexpr qx::cstring_view k_svIntCommandLineShortName    = "-i";
constexpr qx::cstring_view k_svSizeCommandLineShortName   = "-s";
constexpr qx::cstring_view k_svFloatCommandLineShortName  = "-f";
constexpr qx::cstring_view k_svStringCommandLineShortName = "-t";
constexpr qx::cstring_view k_svBoolCommandLineShortName   = "-b";

const std::map<qx::cstring_view, qx::cstring_view> k_RuntimeToEnv { { k_svIntRuntimeName, k_svIntEnvName },
                                                                    { k_svSizeRuntimeName, k_svSizeEnvName },
                                                                    { k_svFloatRuntimeName, k_svFloatEnvName },
                                                                    { k_svStringRuntimeName, k_svStringEnvName },
                                                                    { k_svBoolRuntimeName, k_svBoolEnvName } };

const std::map<qx::cstring_view, qx::cstring_view> k_RuntimeToCommandLineFull {
    { k_svIntRuntimeName, k_svIntCommandLineFullName },
    { k_svSizeRuntimeName, k_svSizeCommandLineFullName },
    { k_svFloatRuntimeName, k_svFloatCommandLineFullName },
    { k_svStringRuntimeName, k_svStringCommandLineFullName },
    { k_svBoolRuntimeName, k_svBoolCommandLineFullName }
};

const std::map<qx::cstring_view, qx::cstring_view> k_RuntimeToCommandLineShort {
    { k_svIntRuntimeName, k_svIntCommandLineShortName },
    { k_svSizeRuntimeName, k_svSizeCommandLineShortName },
    { k_svFloatRuntimeName, k_svFloatCommandLineShortName },
    { k_svStringRuntimeName, k_svStringCommandLineShortName },
    { k_svBoolRuntimeName, k_svBoolCommandLineShortName }
};

constexpr int              k_nDefaultIntValue     = -10;
constexpr size_t           k_nDefaultSizeValue    = 20;
constexpr float            k_fDefaultFloatValue   = 3.5f;
constexpr qx::cstring_view k_svDefaultStringValue = "default";
constexpr bool             k_bDefaultBoolValue    = false;

static void unset_env(const qx::cstring_view svKey)
{
    qx::cstring sKey = svKey;
#ifdef _WIN32
    _putenv_s(sKey.c_str(), "");
#else
    unsetenv(sKey.c_str());
#endif
}

static void set_env(qx::cstring_view svKey, qx::cstring_view svValue)
{
    qx::cstring sKey   = svKey;
    qx::cstring sValue = svValue;

#ifdef _WIN32
    ASSERT_EQ(_putenv_s(sKey.c_str(), sValue.c_str()), 0);
#else
    ASSERT_EQ(setenv(sKey.c_str(), sValue.c_str(), 1), 0);
#endif
}


qx::layered_config_variable g_lcInt = qx::layered_config_variable_builder(k_svIntRuntimeName, k_nDefaultIntValue)
                                          .env(k_svIntEnvName)
                                          .command_line(k_svIntCommandLineFullName, k_svIntCommandLineShortName)
                                          .build();

qx::layered_config_variable g_lcSize = qx::layered_config_variable_builder(k_svSizeRuntimeName, k_nDefaultSizeValue)
                                           .env(k_svSizeEnvName)
                                           .command_line(k_svSizeCommandLineFullName, k_svSizeCommandLineShortName)
                                           .build();

qx::layered_config_variable g_lcFloat = qx::layered_config_variable_builder(k_svFloatRuntimeName, k_fDefaultFloatValue)
                                            .env(k_svFloatEnvName)
                                            .command_line(k_svFloatCommandLineFullName, k_svFloatCommandLineShortName)
                                            .build();

qx::layered_config_variable g_lcString =
    qx::layered_config_variable_builder(k_svStringRuntimeName, k_svDefaultStringValue)
        .env(k_svStringEnvName)
        .command_line(k_svStringCommandLineFullName, k_svStringCommandLineShortName)
        .build();

qx::layered_config_variable g_lcBool = qx::layered_config_variable_builder(k_svBoolRuntimeName, k_bDefaultBoolValue)
                                           .env(k_svBoolEnvName)
                                           .command_line(k_svBoolCommandLineFullName, k_svBoolCommandLineShortName)
                                           .build();

char* g_Argv[3] = { const_cast<char*>(k_sExeName.c_str()), nullptr, nullptr };
int   g_Argc    = 1;

struct set_command_line_space_trait
{
    template<class T>
    static void set_value(qx::cstring_view svRuntimeName, T value)
    {
        qx::cstring_view svCommandLineName = k_RuntimeToCommandLineFull.at(svRuntimeName);

        static qx::cstring sKey;
        sKey = svCommandLineName;

        static qx::cstring sValue;
        sValue = qx::convert_to_string<T, char>(value);

        g_Argv[0] = const_cast<char*>(k_sExeName.c_str());
        g_Argv[1] = sKey.data();
        g_Argv[2] = sValue.data();
        g_Argc    = 3;
    }

    template<class T>
    static constexpr bool is_enabled()
    {
        return true;
    }
};

struct set_command_line_equal_trait
{
    template<class T>
    static void set_value(qx::cstring_view svRuntimeName, T value)
    {
        qx::cstring_view svCommandLineName = k_RuntimeToCommandLineFull.at(svRuntimeName);

        static qx::cstring sValue;
        sValue = qx::cstring(svCommandLineName) + "=" + qx::convert_to_string<T, char>(value);

        g_Argv[0] = const_cast<char*>(k_sExeName.c_str());
        g_Argv[1] = sValue.data();
        g_Argc    = 2;
    }

    template<class T>
    static constexpr bool is_enabled()
    {
        return true;
    }
};

struct set_command_line_flag_trait
{
    template<class T>
    static void set_value(qx::cstring_view svRuntimeName, T value)
    {
        qx::cstring_view svCommandLineName = k_RuntimeToCommandLineFull.at(svRuntimeName);

        static qx::cstring sValue;
        if constexpr (std::is_same_v<T, bool>)
        {
            sValue = value ? qx::cstring(svCommandLineName)
                           : qx::cstring(svCommandLineName) + "=" + qx::convert_to_string<T, char>(value);
        }
        else
        {
            sValue = qx::cstring(svCommandLineName) + "=" + qx::convert_to_string<T, char>(value);
        }

        g_Argv[0] = const_cast<char*>(k_sExeName.c_str());
        g_Argv[1] = sValue.data();
        g_Argc    = 2;
    }

    template<class T>
    static constexpr bool is_enabled()
    {
        return std::is_same_v<T, bool>;
    }
};

struct set_env_trait
{
    template<class T>
    static void set_value(qx::cstring_view svRuntimeName, T value)
    {
        set_env(k_RuntimeToEnv.at(svRuntimeName), qx::convert_to_string<T, char>(value));
    }

    template<class T>
    static constexpr bool is_enabled()
    {
        return true;
    }
};

struct set_runtime_trait
{
    template<class T>
    static void set_value(qx::cstring_view svRuntimeName, T value)
    {
        ASSERT_TRUE(qx::layered_configs_manager::get_instance().set(svRuntimeName, value));
    }

    template<class T>
    static constexpr bool is_enabled()
    {
        return true;
    }
};

template<class set_value_t>
struct test_layered_config_set_value_traits
{
    using set_value_type = set_value_t;
};

template<class test_layered_config_set_value_traits_t>
class test_layered_config_set_value : public ::testing::Test
{
protected:
    virtual void TearDown() override
    {
        auto& manager = qx::layered_configs_manager::get_instance();
        manager.set_args(g_Argc, g_Argv);
        ASSERT_TRUE(manager.parse());

        m_bPreTearDown = false;
        TestBody();

        reset();
    }

    template<class T>
    void set_value(qx::cstring_view svName, T value)
    {
        test_layered_config_set_value_traits_t::set_value_type::set_value(svName, std::move(value));
    }

    template<class T>
    void test_layered_config_set_value_check_type(T defaultValue, T newValue, qx::cstring_view svRuntimeName)
    {
        if constexpr (!test_layered_config_set_value_traits_t::set_value_type::template is_enabled<T>())
            GTEST_SKIP();

        EXPECT_NE(defaultValue, newValue);

        std::optional<T> optValue = qx::layered_configs_manager::get_instance().get<T>(svRuntimeName);
        ASSERT_TRUE(optValue);

        if (m_bPreTearDown)
        {
            EXPECT_EQ(*optValue, defaultValue);
            set_value(svRuntimeName, newValue);
        }
        else
        {
            EXPECT_EQ(*optValue, newValue);
        }
    }


    bool m_bPreTearDown = true;

private:
    void TestBody() override
    {
    }

    void reset()
    {
        g_Argc = 0;

        unset_env(k_svIntEnvName);
        unset_env(k_svSizeEnvName);
        unset_env(k_svFloatEnvName);
        unset_env(k_svStringEnvName);
        unset_env(k_svBoolEnvName);

        qx::layered_configs_manager::get_instance().reset();
    }
};

using implementations_type = ::testing::Types<
    test_layered_config_set_value_traits<set_command_line_space_trait>,
    test_layered_config_set_value_traits<set_command_line_equal_trait>,
    test_layered_config_set_value_traits<set_command_line_flag_trait>,
    test_layered_config_set_value_traits<set_env_trait>,
    test_layered_config_set_value_traits<set_runtime_trait>>;

TYPED_TEST_SUITE(test_layered_config_set_value, implementations_type);

TYPED_TEST(test_layered_config_set_value, int)
{
    this->template test_layered_config_set_value_check_type<int>(k_nDefaultIntValue, 42, k_svIntRuntimeName);
}

TYPED_TEST(test_layered_config_set_value, size_t)
{
    this->template test_layered_config_set_value_check_type<size_t>(k_nDefaultSizeValue, 43ull, k_svSizeRuntimeName);
}

TYPED_TEST(test_layered_config_set_value, float)
{
    this->template test_layered_config_set_value_check_type<float>(k_fDefaultFloatValue, 44.f, k_svFloatRuntimeName);
}

TYPED_TEST(test_layered_config_set_value, string)
{
    this->template test_layered_config_set_value_check_type<qx::cstring_view>(
        k_svDefaultStringValue,
        "not default",
        k_svStringRuntimeName);
}

TYPED_TEST(test_layered_config_set_value, bool)
{
    this->template test_layered_config_set_value_check_type<bool>(k_bDefaultBoolValue, true, k_svBoolRuntimeName);
}
