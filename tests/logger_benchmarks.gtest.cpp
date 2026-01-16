/**

    @file      logger_benchmarks.gtest.cpp
    @brief     Tests for qx::logger
    @author    Khrapov
    @date      27.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *logger_benchmarks.gtest.cpp

#include <qx/logger/logger.h>

#include <qx/logger/base_file_logger_stream.h>
#include <qx/logger/cout_logger_stream.h>
#include <qx/logger/debugger_logger_stream.h>
#include <qx/logger/file_logger_stream_fopen.h>
#include <qx/logger/file_logger_stream_mapping.h>
#include <qx/logger/file_logger_stream_ofstream.h>
#include <qx/stat/benchmark.h>

#include <random>

std::vector<qx::string> generateStrings(size_t count, uint32_t seed)
{
    static constexpr char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::mt19937                       rng(seed);
    std::uniform_int_distribution<int> lenDist(10, 130);
    std::uniform_int_distribution<int> charDist(0, sizeof(charset) - 2);

    std::vector<qx::string> result;
    result.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        int        len = lenDist(rng);
        qx::string s;
        s.reserve(len);

        for (int j = 0; j < len; ++j)
            s += charset[charDist(rng)];

        result.emplace_back(std::move(s));
    }

    return result;
}

static const std::vector<qx::string> k_RandomStrings = generateStrings(10000, 12345);

class LoggerBenchmark : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        m_sLogFileName = qx::string(QXT("logger_benchmark_"))
                         + qx::to_string(testing::UnitTest::GetInstance()->current_test_info()->name());
    }

    virtual void TearDown() override
    {
        m_Benchmark.start();

        for (qx::string_view svMessage : k_RandomStrings)
            QX_LOG(qx::verbosity::log, svMessage);

        double fTime = m_Benchmark.end();

        std::cout << ::testing::UnitTest::GetInstance()->current_test_info()->name() << std::endl;
        std::cout << "Benchmark time: " << fTime << " seconds." << std::endl;

        qx::logger_singleton::get_instance().get_logger().reset();
        // std::filesystem::remove((m_sLogFileName + QXT(".log")).data());
    }

protected:
    qx::string m_sLogFileName;

private:
    qx::benchmark m_Benchmark;
};

TEST_F(LoggerBenchmark, file_logger_stream_ostream_default_buffer)
{
    qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_ofstream(
        { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = m_sLogFileName },
        qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
}

TEST_F(LoggerBenchmark, file_logger_stream_ostream)
{
    qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_ofstream(
        { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = m_sLogFileName }));
}

TEST_F(LoggerBenchmark, file_logger_stream_fopen_default_buffer)
{
    qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_fopen(
        { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = m_sLogFileName },
        qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
}

TEST_F(LoggerBenchmark, file_logger_stream_fopen)
{
    qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_fopen(
        { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = m_sLogFileName }));
}

TEST_F(LoggerBenchmark, file_logger_stream_mapping_default_initial_size)
{
    qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_mapping(
        { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = m_sLogFileName },
        qx::unit<size_t, qx::units::data> { 0, qx::units::data::bytes }));
}

TEST_F(LoggerBenchmark, file_logger_stream_mapping)
{
    qx::logger_singleton::get_instance().get_logger().add_stream(qx::file_logger_stream_mapping(
        { .eLogFilePolicy = qx::log_file_policy::clear_then_uppend, .svFileName = m_sLogFileName }));
}

/*
TEST_F(LoggerBenchmark, cout_logger_stream)
{
    qx::logger_singleton::get_instance().get_logger().add_stream(qx::cout_logger_stream());
}

TEST_F(LoggerBenchmark, debugger_logger_stream)
{
    qx::logger_singleton::get_instance().get_logger().add_stream(qx::debugger_logger_stream());
}
*/