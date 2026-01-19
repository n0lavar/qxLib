/**

    @file      logger_streams.bench.cpp
    @author    Khrapov
    @date      16.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#include <benchmark/benchmark.h>

#include <qx/logger/base_file_logger_stream.h>
#include <qx/logger/cout_logger_stream.h>
#include <qx/logger/debugger_logger_stream.h>
#include <qx/logger/file_logger_stream_fopen.h>
#include <qx/logger/file_logger_stream_mapping.h>
#include <qx/logger/file_logger_stream_ofstream.h>
#include <qx/logger/fwrite_logger_stream.h>
#include <qx/logger/logger.h>

#if QX_WIN
    #include <io.h>
    #define __dup    _dup
    #define __dup2   _dup2
    #define __fileno _fileno
    #define __fdopen _fdopen
#else
    #include <unistd.h>
    #define __dup    dup
    #define __dup2   dup2
    #define __fileno fileno
    #define __fdopen fdopen
#endif

#include <cstdio>
#include <random>

BENCHMARK_MAIN();

constexpr qx::string_view k_svLogFileName = QXT("logger_benchmark.log");

static std::vector<qx::string> generate_strings(size_t nCount, uint32_t nSeed)
{
    static constexpr char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::mt19937                       rng(nSeed);
    std::uniform_int_distribution<int> lenDist(10, 130);
    std::uniform_int_distribution<int> charDist(0, sizeof(charset) - 2);

    std::vector<qx::string> result;
    result.reserve(nCount);

    for (size_t i = 0; i < nCount; ++i)
    {
        int        nLen = lenDist(rng);
        qx::string s;
        s.reserve(nLen);

        for (int j = 0; j < nLen; ++j)
            s += charset[charDist(rng)];

        result.emplace_back(std::move(s));
    }

    return result;
}

namespace traits
{

struct ostream_default_buffer
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_ofstream(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName },
            qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
    }
};

struct ostream
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_ofstream(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName }));
    }
};

struct fopen_default_buffer
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_fopen(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName },
            qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
    }
};

struct fopen
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_fopen(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName }));
    }
};

struct mapping_default_initial_size
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_mapping(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName },
            qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
    }
};

struct mapping
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_mapping(
            { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = k_svLogFileName }));
    }
};

struct cout
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::cout_logger_stream());
    }
};

struct fwrite
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::fwrite_logger_stream());
    }
};

struct debugger
{
    static void set_up()
    {
        qx::logger_singleton::get_instance().get_logger().add_stream(qx::debugger_logger_stream());
    }
};

} // namespace traits

template<class setup_function_t>
class logger_stream_fixture : public benchmark::Fixture
{
public:
    virtual void SetUp(::benchmark::State& state) override
    {
        m_RandomStrings = generate_strings(state.range(0), 0);

        qx::logger_singleton::get_instance().get_logger().reset();
        setup_function_t::set_up();

        // temporarily disable console output so it doesn't interfere with the benchmark results
        m_pOldStdout = __fdopen(__dup(__fileno(stdout)), "w");
        m_pOldStderr = __fdopen(__dup(__fileno(stderr)), "w");

        QX_DISABLE_MSVC_WARNINGS(4996);
        freopen("NUL", "w", stdout);
        freopen("NUL", "w", stderr);
        QX_RESTORE_MSVC_WARNINGS(4996);
    }

    virtual void TearDown(::benchmark::State& state) override
    {
        qx::logger_singleton::get_instance().get_logger().reset();
        std::filesystem::remove(k_svLogFileName);

        fflush(stdout);
        fflush(stderr);

        __dup2(__fileno(m_pOldStdout), __fileno(stdout));
        fclose(m_pOldStdout);
        m_pOldStdout = nullptr;

        __dup2(__fileno(m_pOldStderr), __fileno(stderr));
        fclose(m_pOldStderr);
        m_pOldStderr = nullptr;
    }

protected:
    std::vector<qx::string> m_RandomStrings;

    FILE* m_pOldStdout = nullptr;
    FILE* m_pOldStderr = nullptr;
};

BENCHMARK_TEMPLATE_METHOD_F(logger_stream_fixture, bench)(benchmark::State& st)
{
    for (auto _ : st)
        for (qx::string_view svMessage : this->m_RandomStrings)
            QX_LOG(qx::verbosity::log, svMessage);
}

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::debugger)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::cout)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fwrite)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream_default_buffer)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen_default_buffer)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping_default_initial_size)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping)->Arg(1000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::debugger)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::cout)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fwrite)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream_default_buffer)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen_default_buffer)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping_default_initial_size)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping)->Arg(5000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::debugger)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::cout)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fwrite)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream_default_buffer)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen_default_buffer)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping_default_initial_size)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping)->Arg(10000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::debugger)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::cout)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fwrite)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream_default_buffer)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen_default_buffer)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping_default_initial_size)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping)->Arg(20000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::debugger)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::cout)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fwrite)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream_default_buffer)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen_default_buffer)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping_default_initial_size)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping)->Arg(40000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::debugger)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::cout)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fwrite)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream_default_buffer)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::ostream)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen_default_buffer)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::fopen)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping_default_initial_size)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, bench, traits::mapping)->Arg(80000);
