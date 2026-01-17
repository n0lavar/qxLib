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
#include <qx/logger/logger.h>

#include <random>

BENCHMARK_MAIN();

constexpr qx::string_view k_svLogFileName = QXT("logger_benchmark");

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

} // namespace traits

template<class setup_function_t>
class logger_stream_fixture : public benchmark::Fixture
{
public:
    size_t m_nStrings = 0;

    virtual void SetUp(::benchmark::State& state) override
    {
        m_nStrings = state.range(0);

        m_RandomStrings = generate_strings(m_nStrings, 0);
        setup_function_t::set_up();
    }

    virtual void TearDown(::benchmark::State& state) override
    {
        qx::logger_singleton::get_instance().get_logger().reset();
        std::filesystem::remove((qx::string(k_svLogFileName) + QXT(".log")).data());
    }

protected:
    std::vector<qx::string> m_RandomStrings;
};

BENCHMARK_TEMPLATE_METHOD_F(logger_stream_fixture, Test)(benchmark::State& st)
{
    for (auto _ : st)
        for (qx::string_view svMessage : this->m_RandomStrings)
            QX_LOG(qx::verbosity::log, svMessage);
}

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream_default_buffer)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen_default_buffer)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping_default_initial_size)->Arg(1000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping)->Arg(1000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream_default_buffer)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen_default_buffer)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping_default_initial_size)->Arg(5000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping)->Arg(5000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream_default_buffer)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen_default_buffer)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping_default_initial_size)->Arg(10000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping)->Arg(10000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream_default_buffer)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen_default_buffer)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping_default_initial_size)->Arg(20000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping)->Arg(20000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream_default_buffer)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen_default_buffer)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping_default_initial_size)->Arg(40000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping)->Arg(40000);

BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream_default_buffer)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::ostream)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen_default_buffer)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::fopen)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping_default_initial_size)->Arg(80000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(logger_stream_fixture, Test, traits::mapping)->Arg(80000);
