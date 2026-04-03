/**

    @file      formatting.bench.cpp
    @author    Khrapov
    @date      11.03.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#include <qx/containers/string/string.h>
#include "benchmark/benchmark.h"

#include <qx/containers/string/string_utils.h>
#include <qx/macros/suppress_warnings.h>

QX_DISABLE_MSVC_WARNINGS(4756);
#include <cstdio>
#include <format>
#include <random>
#include <string>
#include <utility>
QX_RESTORE_MSVC_WARNINGS(4756);

//V_EXCLUDE_PATH *.bench.cpp

BENCHMARK_MAIN();

namespace traits
{

template<class char_t>
struct std_format
{
    using char_type = char_t;

    template<class... args_t>
    static std::basic_string<char_t> format(
        const std::basic_format_string<char_t, std::type_identity_t<args_t>...> sFormat,
        args_t&&... args)
    {
        return std::format(sFormat, std::forward<args_t>(args)...);
    }
};

#if __has_include("fmt/format.h")
template<class char_t>
struct fmt_format
{
    using char_type = char_t;

    template<class... args_t>
    static std::basic_string<char_t> format(
        const fmt::basic_format_string<char_t, std::type_identity_t<args_t>...> sFormat,
        args_t&&... args)
    {
        return fmt::vformat(sFormat.get(), fmt::make_format_args<fmt::buffered_context<char_t>>(args...));
    }
};
#endif

template<class char_t>
struct std_sprintf
{
    using char_type = char_t;

    template<class... args_t>
    static std::basic_string<char_t> format(args_t&&... args)
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS();

        int size = 0;
        if constexpr (std::is_same_v<char_t, char>)
            size = std::snprintf(nullptr, 0, std::forward<args_t>(args)...);
        else
            size = std::swprintf(nullptr, 0, std::forward<args_t>(args)...);

        if (size <= 0)
            return {};

        std::basic_string<char_t> result;
        result.resize(size);
        if constexpr (std::is_same_v<char_t, char>)
            std::snprintf(result.data(), size + 1, std::forward<args_t>(args)...);
        else
            std::swprintf(result.data(), size + 1, std::forward<args_t>(args)...);

        QX_POP_SUPPRESS_WARNINGS();
        return result;
    }
};

template<class char_t>
struct qx_format
{
    using char_type = char_t;

    template<class... args_t>
    static qx::basic_string<char_t> format(
        const QX_FMT_NS::basic_format_string<char_t, std::type_identity_t<args_t>...> sFormat,
        args_t&&... args)
    {
        return qx::basic_string<char_t>::static_format(sFormat, std::forward<args_t>(args)...);
    }
};

} // namespace traits

template<class traits_t>
class formatting_fixture : public benchmark::Fixture
{
public:
    using traits_type = traits_t;
    using char_type   = traits_type::char_type;

public:
    void SetUp(const benchmark::State&) override
    {
        m_randomEngine = std::mt19937(static_cast<unsigned int>(s_nSeed));
    }

protected:
    int random_int()
    {
        std::uniform_int_distribution dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        return dist(m_randomEngine);
    }

    float random_float()
    {
        std::uniform_real_distribution dist(-100000.f, 100000.f);
        return dist(m_randomEngine);
    }

    std::basic_string<char_type> random_string(size_t nMinLength, size_t nMaxLength)
    {
        std::uniform_int_distribution lengthDist(nMinLength, nMaxLength);
        const size_t                  nLength = lengthDist(m_randomEngine);

        static const std::basic_string<char_type> sChars = QX_STR_PREFIX(
            char_type,
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789");

        std::uniform_int_distribution<size_t> charsDist(0, sChars.size() - 1);

        std::basic_string<char_type> sResult;
        sResult.reserve(nLength);

        for (size_t i = 0; i < nLength; ++i)
        {
            sResult += sChars[charsDist(m_randomEngine)];
        }

        return sResult;
    }

private:
    inline static time_t s_nSeed = std::time(nullptr);
    std::mt19937         m_randomEngine;
};

// ------------------------------------------------------------
// std::format / fmt::format cases
// ------------------------------------------------------------

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_0_args)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "hello world")));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_int)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const int int1 = this->random_int();
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "{}"), int1));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_int_int)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const int int1 = this->random_int();
        const int int2 = this->random_int();
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "{} {}"), int1, int2));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_small_string)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const std::basic_string<char_type> str1 =
            this->random_string(0, qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "{}"), str1));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_small_string_string)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const std::basic_string<char_type> str1 =
            this->random_string(0, qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        const std::basic_string<char_type> str2 =
            this->random_string(0, qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "{} {}"), str1, str2));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_big_string)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const std::basic_string<char_type> str1 = this->random_string(
            qx::basic_string<char_type>::traits_type::nMemoryBufferSize,
            2 * qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "{}"), str1));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_big_string_string)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const std::basic_string<char_type> str1 = this->random_string(
            qx::basic_string<char_type>::traits_type::nMemoryBufferSize,
            2 * qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        const std::basic_string<char_type> str2 = this->random_string(
            qx::basic_string<char_type>::traits_type::nMemoryBufferSize,
            2 * qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "{} {}"), str1, str2));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_float)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const float float1 = this->random_float();
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "{}"), float1));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_float_float)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const float float1 = this->random_float();
        const float float2 = this->random_float();
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "{} {}"), float1, float2));
    }
}

// ------------------------------------------------------------
// sprintf-only cases
// ------------------------------------------------------------

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_0_args)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "hello world")));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_int)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const int int1 = this->random_int();
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "%d"), int1));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_int_int)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const int int1 = this->random_int();
        const int int2 = this->random_int();
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "%d %d"), int1, int2));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_small_string)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const std::basic_string<char_type> str1 =
            this->random_string(0, qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(qx::get_format_specifier<char_type, char_type*>(), str1.c_str()));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_small_string_string)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const std::basic_string<char_type> str1 =
            this->random_string(0, qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        const std::basic_string<char_type> str2 =
            this->random_string(0, qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(
            (std::basic_string<char_type>(qx::get_format_specifier<char_type, char_type*>())
             + QX_STR_PREFIX(char_type, " ") + qx::get_format_specifier<char_type, char_type*>())
                .c_str(),
            str1.c_str(),
            str2.c_str()));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_big_string)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const std::basic_string<char_type> str1 = this->random_string(
            qx::basic_string<char_type>::traits_type::nMemoryBufferSize,
            2 * qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(qx::get_format_specifier<char_type, char_type*>(), str1.c_str()));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_big_string_string)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const std::basic_string<char_type> str1 = this->random_string(
            qx::basic_string<char_type>::traits_type::nMemoryBufferSize,
            2 * qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        const std::basic_string<char_type> str2 = this->random_string(
            qx::basic_string<char_type>::traits_type::nMemoryBufferSize,
            2 * qx::basic_string<char_type>::traits_type::nMemoryBufferSize);
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(
            (std::basic_string<char_type>(qx::get_format_specifier<char_type, char_type*>())
             + QX_STR_PREFIX(char_type, " ") + qx::get_format_specifier<char_type, char_type*>())
                .c_str(),
            str1.c_str(),
            str2.c_str()));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_float)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const float float1 = this->random_float();
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "%f"), float1));
    }
}

BENCHMARK_TEMPLATE_METHOD_F(formatting_fixture, bench_printf_float_float)(benchmark::State& st)
{
    using traits_type = Base::traits_type;
    using char_type   = traits_type::char_type;
    for (auto _ : st)
    {
        st.PauseTiming();
        const float float1 = this->random_float();
        const float float2 = this->random_float();
        st.ResumeTiming();

        benchmark::DoNotOptimize(traits_type::format(QX_STR_PREFIX(char_type, "%f %f"), float1, float2));
    }
}

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_0_args, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_0_args, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_0_args, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_0_args, traits::qx_format<char>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_int, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int, traits::qx_format<char>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int_int, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_int_int, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int_int, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int_int, traits::qx_format<char>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_small_string, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string, traits::qx_format<char>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string_string, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_small_string_string, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string_string, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string_string, traits::qx_format<char>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_big_string, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string, traits::qx_format<char>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string_string, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_big_string_string, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string_string, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string_string, traits::qx_format<char>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_float, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float, traits::qx_format<char>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float_float, traits::std_format<char>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_float_float, traits::std_sprintf<char>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float_float, traits::fmt_format<char>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float_float, traits::qx_format<char>);


BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_0_args, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_0_args, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_0_args, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_0_args, traits::qx_format<wchar_t>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_int, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int, traits::qx_format<wchar_t>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int_int, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_int_int, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int_int, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_int_int, traits::qx_format<wchar_t>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_small_string, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string, traits::qx_format<wchar_t>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string_string, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_small_string_string, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string_string, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_small_string_string, traits::qx_format<wchar_t>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_big_string, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string, traits::qx_format<wchar_t>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string_string, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_big_string_string, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string_string, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_big_string_string, traits::qx_format<wchar_t>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_float, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float, traits::qx_format<wchar_t>);

BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float_float, traits::std_format<wchar_t>);
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_printf_float_float, traits::std_sprintf<wchar_t>);
#if __has_include("fmt/format.h")
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float_float, traits::fmt_format<wchar_t>);
#endif
BENCHMARK_TEMPLATE_INSTANTIATE_F(formatting_fixture, bench_float_float, traits::qx_format<wchar_t>);
