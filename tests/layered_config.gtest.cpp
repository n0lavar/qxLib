/**

    @file      layered_config.gtest.cpp
    @author    Khrapov
    @date      12.05.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

#include <qx/layered_config/layered_config_variable.h>

#include <array>
#include <cstdlib>

const qx::cstring k_sExeName = "app";

constexpr qx::string_view k_svIntRuntimeName    = QXT("layered_config_test_int");
constexpr qx::string_view k_svSizeRuntimeName   = QXT("layered_config_test_size");
constexpr qx::string_view k_svFloatRuntimeName  = QXT("layered_config_test_float");
constexpr qx::string_view k_svStringRuntimeName = QXT("layered_config_test_string");
constexpr qx::string_view k_svBoolRuntimeName   = QXT("layered_config_test_bool");

constexpr qx::string_view k_svNumericGroup = QXT("Numeric");
constexpr qx::string_view k_svFloatGroup   = QXT("Floating point");

constexpr qx::string_view k_svIntEnvName    = QXT("QX_LAYERED_CONFIG_TEST_INT");
constexpr qx::string_view k_svSizeEnvName   = QXT("QX_LAYERED_CONFIG_TEST_SIZE");
constexpr qx::string_view k_svFloatEnvName  = QXT("QX_LAYERED_CONFIG_TEST_FLOAT");
constexpr qx::string_view k_svStringEnvName = QXT("QX_LAYERED_CONFIG_TEST_STRING");
constexpr qx::string_view k_svBoolEnvName   = QXT("QX_LAYERED_CONFIG_TEST_BOOL");

constexpr qx::string_view k_svIntCommandLineFullName    = QXT("--layered-config-test-int");
constexpr qx::string_view k_svSizeCommandLineFullName   = QXT("--layered-config-test-size");
constexpr qx::string_view k_svFloatCommandLineFullName  = QXT("--layered-config-test-float");
constexpr qx::string_view k_svStringCommandLineFullName = QXT("--layered-config-test-string");
constexpr qx::string_view k_svBoolCommandLineFullName   = QXT("--layered-config-test-bool");

constexpr qx::string_view k_svIntCommandLineShortName    = QXT("-i");
constexpr qx::string_view k_svSizeCommandLineShortName   = QXT("-s");
constexpr qx::string_view k_svFloatCommandLineShortName  = QXT("-f");
constexpr qx::string_view k_svStringCommandLineShortName = QXT("-t");
constexpr qx::string_view k_svBoolCommandLineShortName   = QXT("-b");

const std::map<qx::string_view, qx::string_view> k_RuntimeToEnv { { k_svIntRuntimeName, k_svIntEnvName },
                                                                  { k_svSizeRuntimeName, k_svSizeEnvName },
                                                                  { k_svFloatRuntimeName, k_svFloatEnvName },
                                                                  { k_svStringRuntimeName, k_svStringEnvName },
                                                                  { k_svBoolRuntimeName, k_svBoolEnvName } };

const std::map<qx::string_view, qx::string_view> k_RuntimeToCommandLineFull {
    { k_svIntRuntimeName, k_svIntCommandLineFullName },
    { k_svSizeRuntimeName, k_svSizeCommandLineFullName },
    { k_svFloatRuntimeName, k_svFloatCommandLineFullName },
    { k_svStringRuntimeName, k_svStringCommandLineFullName },
    { k_svBoolRuntimeName, k_svBoolCommandLineFullName }
};

const std::map<qx::string_view, qx::string_view> k_RuntimeToCommandLineShort {
    { k_svIntRuntimeName, k_svIntCommandLineShortName },
    { k_svSizeRuntimeName, k_svSizeCommandLineShortName },
    { k_svFloatRuntimeName, k_svFloatCommandLineShortName },
    { k_svStringRuntimeName, k_svStringCommandLineShortName },
    { k_svBoolRuntimeName, k_svBoolCommandLineShortName }
};

constexpr int             k_nDefaultIntValue     = -10;
constexpr size_t          k_nDefaultSizeValue    = 20;
constexpr float           k_fDefaultFloatValue   = 3.5f;
constexpr qx::string_view k_svDefaultStringValue = QXT("default");
constexpr bool            k_bDefaultBoolValue    = false;

static void unset_env(const qx::string_view svKey)
{
    qx::cstring sKey = qx::to_cstring(svKey);
#ifdef _WIN32
    _putenv_s(sKey.c_str(), "");
#else
    unsetenv(sKey.c_str());
#endif
}

static void set_env(qx::string_view svKey, qx::string_view svValue)
{
    qx::cstring sKey   = qx::to_cstring(svKey);
    qx::cstring sValue = qx::to_cstring(svValue);

#ifdef _WIN32
    ASSERT_EQ(_putenv_s(sKey.c_str(), sValue.c_str()), 0);
#else
    ASSERT_EQ(setenv(sKey.c_str(), sValue.c_str(), 1), 0);
#endif
}


qx::layered_config_variable g_lcInt = qx::layered_config_variable_builder(k_svIntRuntimeName, k_nDefaultIntValue)
                                          .env(k_svIntEnvName)
                                          .command_line(k_svIntCommandLineFullName, k_svIntCommandLineShortName)
                                          .group(k_svNumericGroup)
                                          .build();

qx::layered_config_variable g_lcSize = qx::layered_config_variable_builder(k_svSizeRuntimeName, k_nDefaultSizeValue)
                                           .env(k_svSizeEnvName)
                                           .command_line(k_svSizeCommandLineFullName, k_svSizeCommandLineShortName)
                                           .group(k_svNumericGroup)
                                           .build();

qx::layered_config_variable g_lcFloat = qx::layered_config_variable_builder(k_svFloatRuntimeName, k_fDefaultFloatValue)
                                            .env(k_svFloatEnvName)
                                            .command_line(k_svFloatCommandLineFullName, k_svFloatCommandLineShortName)
                                            .group(k_svFloatGroup)
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
    static void set_value(qx::string_view svRuntimeName, T value)
    {
        qx::string_view svCommandLineName = k_RuntimeToCommandLineFull.at(svRuntimeName);

        static qx::cstring sKey;
        sKey = qx::to_cstring(svCommandLineName);

        static qx::cstring sValue;
        sValue = qx::to_cstring(qx::convert_to_string<T, qx::char_type>(value));

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
    static void set_value(qx::string_view svRuntimeName, T value)
    {
        qx::string_view svCommandLineName = k_RuntimeToCommandLineFull.at(svRuntimeName);

        static qx::cstring sValue;
        sValue =
            qx::to_cstring(svCommandLineName) + "=" + qx::to_cstring(qx::convert_to_string<T, qx::char_type>(value));

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
    static void set_value(qx::string_view svRuntimeName, T value)
    {
        qx::string_view svCommandLineName = k_RuntimeToCommandLineFull.at(svRuntimeName);

        static qx::cstring sValue;
        if constexpr (std::is_same_v<T, bool>)
        {
            sValue = value ? qx::to_cstring(svCommandLineName)
                           : qx::to_cstring(svCommandLineName) + "="
                                 + qx::to_cstring(qx::convert_to_string<T, qx::char_type>(value));
        }
        else
        {
            sValue = qx::to_cstring(svCommandLineName) + "="
                     + qx::to_cstring(qx::convert_to_string<T, qx::char_type>(value));
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
    static void set_value(qx::string_view svRuntimeName, T value)
    {
        set_env(k_RuntimeToEnv.at(svRuntimeName), qx::convert_to_string<T, qx::char_type>(value));
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
    static void set_value(qx::string_view svRuntimeName, T value)
    {
        ASSERT_TRUE(qx::layered_configs_manager::get_instance().set(svRuntimeName, value));
    }

    template<class T>
    static constexpr bool is_enabled()
    {
        return true;
    }
};

struct set_runtime_any_trait
{
    template<class T>
    static void set_value(qx::string_view svName, T value)
    {
        using stored_type = typename qx::details::layered_config_variable_type<T>::type;
        EXPECT_TRUE(qx::layered_configs_manager::get_instance().set(svName, std::any(stored_type(value))));
    }

    template<class T>
    static constexpr bool is_enabled()
    {
        return true;
    }
};

struct set_runtime_string_trait
{
    template<class T>
    static void set_value(qx::string_view svRuntimeName, T value)
    {
        const auto sValue = qx::convert_to_string<T, qx::char_type>(value);
        ASSERT_TRUE(qx::layered_configs_manager::get_instance().set_string(svRuntimeName, sValue));
    }

    template<class T>
    static constexpr bool is_enabled() noexcept
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
    virtual void TearDown() override;

    template<class T>
    void set_value(qx::string_view svName, T value);

    template<class T>
    void test_layered_config_set_value_check_type(T defaultValue, T newValue, qx::string_view svRuntimeName);

    bool m_bPreTearDown = true;

private:
    void TestBody() override
    {
    }

    void reset();
};

template<class test_layered_config_set_value_traits_t>
inline void test_layered_config_set_value<test_layered_config_set_value_traits_t>::TearDown()
{
    auto& manager = qx::layered_configs_manager::get_instance();
    manager.set_args(g_Argc, g_Argv);
    ASSERT_TRUE(manager.parse());

    m_bPreTearDown = false;
    TestBody();

    reset();
}

template<class test_layered_config_set_value_traits_t>
template<class T>
inline void test_layered_config_set_value<test_layered_config_set_value_traits_t>::set_value(
    qx::string_view svName,
    T               value)
{
    test_layered_config_set_value_traits_t::set_value_type::set_value(svName, std::move(value));
}

template<class test_layered_config_set_value_traits_t>
template<class T>
inline void test_layered_config_set_value<test_layered_config_set_value_traits_t>::
    test_layered_config_set_value_check_type(T defaultValue, T newValue, qx::string_view svRuntimeName)
{
    if constexpr (!test_layered_config_set_value_traits_t::set_value_type::template is_enabled<T>())
        GTEST_SKIP();

    EXPECT_NE(defaultValue, newValue);

    qx::layered_configs_manager&                             manager = qx::layered_configs_manager::get_instance();
    std::expected<T, qx::layered_configs_manager::get_error> value   = manager.get<T>(svRuntimeName);
    ASSERT_TRUE(value);

    const auto anyValue = manager.get(svRuntimeName);
    ASSERT_TRUE(anyValue);

    using stored_type               = typename qx::details::layered_config_variable_type<T>::type;
    const stored_type* pStoredValue = std::any_cast<stored_type>(&anyValue->get());
    ASSERT_NE(pStoredValue, nullptr);
    EXPECT_EQ(*pStoredValue, m_bPreTearDown ? defaultValue : newValue);

    const auto sameValue = manager.get(svRuntimeName);
    ASSERT_TRUE(sameValue);
    EXPECT_EQ(&anyValue->get(), &sameValue->get());
    using get_error = qx::layered_configs_manager::get_error;
    using set_error = qx::layered_configs_manager::set_error;
    EXPECT_EQ(manager.get<T>(QXT("unknown_variable")), std::unexpected(get_error::unknown_variable));
    EXPECT_EQ(manager.get<double>(svRuntimeName), std::unexpected(get_error::type_mismatch));
    EXPECT_EQ(manager.get(QXT("unknown_variable")), std::unexpected(get_error::unknown_variable));
    EXPECT_EQ(manager.get_string(QXT("unknown_variable")), std::unexpected(get_error::unknown_variable));

    EXPECT_EQ(manager.set(QXT("unknown_variable"), newValue), std::unexpected(set_error::unknown_variable));
    EXPECT_EQ(
        manager.set(QXT("unknown_variable"), std::any(stored_type(newValue))),
        std::unexpected(set_error::unknown_variable));
    EXPECT_EQ(manager.set_string(QXT("unknown_variable"), QXT("42")), std::unexpected(set_error::unknown_variable));

    EXPECT_EQ(manager.set(svRuntimeName, 12.5), std::unexpected(set_error::type_mismatch));
    EXPECT_EQ(manager.set(svRuntimeName, std::any(12.5)), std::unexpected(set_error::type_mismatch));
    EXPECT_EQ(manager.set(svRuntimeName, std::any()), std::unexpected(set_error::type_mismatch));
    if constexpr (!std::is_same_v<T, bool>)
        EXPECT_EQ(manager.set(svRuntimeName, std::any(true)), std::unexpected(set_error::type_mismatch));
    if constexpr (!std::is_same_v<T, qx::string_view>)
        EXPECT_EQ(manager.set_string(svRuntimeName, QXT("invalid")), std::unexpected(set_error::invalid_value));

    const std::expected<T, qx::layered_configs_manager::get_error> unchangedValue = manager.get<T>(svRuntimeName);
    ASSERT_TRUE(unchangedValue);
    EXPECT_EQ(*unchangedValue, m_bPreTearDown ? defaultValue : newValue);

    const auto stringValue = manager.get_string(svRuntimeName);
    ASSERT_TRUE(stringValue);

    const auto sExpected = qx::convert_to_string<T, qx::char_type>(m_bPreTearDown ? defaultValue : newValue);
    EXPECT_EQ(*stringValue, sExpected);

    if (m_bPreTearDown)
    {
        EXPECT_EQ(*value, defaultValue);
        set_value(svRuntimeName, newValue);
    }
    else
    {
        EXPECT_EQ(*value, newValue);
    }
}

template<class test_layered_config_set_value_traits_t>
inline void test_layered_config_set_value<test_layered_config_set_value_traits_t>::reset()
{
    g_Argc = 0;

    unset_env(k_svIntEnvName);
    unset_env(k_svSizeEnvName);
    unset_env(k_svFloatEnvName);
    unset_env(k_svStringEnvName);
    unset_env(k_svBoolEnvName);

    qx::layered_configs_manager::get_instance().reset();
}

using implementations_type = ::testing::Types<
    test_layered_config_set_value_traits<set_command_line_space_trait>,
    test_layered_config_set_value_traits<set_command_line_equal_trait>,
    test_layered_config_set_value_traits<set_command_line_flag_trait>,
    test_layered_config_set_value_traits<set_env_trait>,
    test_layered_config_set_value_traits<set_runtime_trait>,
    test_layered_config_set_value_traits<set_runtime_string_trait>,
    test_layered_config_set_value_traits<set_runtime_any_trait>>;

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
    this->template test_layered_config_set_value_check_type<qx::string_view>(
        k_svDefaultStringValue,
        QXT("not default"),
        k_svStringRuntimeName);
}

TYPED_TEST(test_layered_config_set_value, bool)
{
    this->template test_layered_config_set_value_check_type<bool>(k_bDefaultBoolValue, true, k_svBoolRuntimeName);
}

TEST(layered_config, empty_or_invalid_args)
{
    auto& manager = qx::layered_configs_manager::get_instance();
    char  sHelp[] = "--help";
    char* argv[]  = { sHelp };

    for (const int argc : { 0, -1 })
    {
        manager.set_args(argc, argv);
        EXPECT_FALSE(manager.show_help());
        EXPECT_TRUE(manager.parse());
    }

    manager.set_args(1, nullptr);
    EXPECT_FALSE(manager.show_help());
    EXPECT_TRUE(manager.parse());
    manager.reset();
}

TEST(layered_config, get_variables)
{
    constexpr auto expected = std::to_array<qx::layered_config_variable_info>(
        { { k_svIntRuntimeName, {}, qx::type_strings<int, qx::char_type>::get_signature(), k_svNumericGroup },
          { k_svSizeRuntimeName, {}, qx::type_strings<size_t, qx::char_type>::get_signature(), k_svNumericGroup },
          { k_svFloatRuntimeName, {}, QXT("float"), k_svFloatGroup },
          { k_svStringRuntimeName, {}, QXT("string"), {} },
          { k_svBoolRuntimeName, {}, QXT("bool"), {} } });

    const auto variables = qx::layered_configs_manager::get_instance().get_variables();
    ASSERT_EQ(variables.size(), expected.size());
    EXPECT_TRUE(std::ranges::is_sorted(variables, {}, &qx::layered_config_variable_info::svName));

    for (const auto& info : expected)
    {
        const auto it = std::ranges::find(variables, info.svName, &qx::layered_config_variable_info::svName);
        ASSERT_NE(it, variables.end());
        EXPECT_EQ(it->svDescription, info.svDescription);
        EXPECT_EQ(it->svTypeName, info.svTypeName);
        EXPECT_EQ(it->svGroupName, info.svGroupName);
    }
}

TEST(layered_config, type_erased_string_set_preserves_embedded_nulls)
{
    qx::layered_configs_manager& manager = qx::layered_configs_manager::get_instance();
    struct reset_guard
    {
        ~reset_guard()
        {
            qx::layered_configs_manager::get_instance().reset();
        }
    } guard;
    const qx::string text(QXT("A\0B with spaces"), 15);
    const std::any   value(text);
    ASSERT_TRUE(manager.set(k_svStringRuntimeName, value));
    const std::expected<std::reference_wrapper<const std::any>, qx::layered_configs_manager::get_error> stored =
        manager.get(k_svStringRuntimeName);
    ASSERT_TRUE(stored);
    const qx::string* pText = std::any_cast<qx::string>(&stored->get());
    ASSERT_NE(pText, nullptr);
    EXPECT_EQ(pText->size(), text.size());
    EXPECT_EQ(*pText, text);
}
