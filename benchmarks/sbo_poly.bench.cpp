/**

    @file      sbo_poly.bench.cpp
    @author    Khrapov
    @date      10.05.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#include "benchmark/benchmark.h"

#include <qx/hash.h>
#include <qx/memory/sbo_poly.h>

#include <random>

//V_EXCLUDE_PATH *.bench.cpp

BENCHMARK_MAIN();

class base_test_class
{
public:
    base_test_class()                       = default;
    base_test_class(const base_test_class&) = default;
    virtual ~base_test_class()              = default;

    virtual size_t get_hash() const = 0;
};

constexpr size_t k_nSmallDataSize = 32;
constexpr size_t k_nSBOSize       = 64;
constexpr size_t k_nBigDataSize   = 128;
using sbo_type                    = qx::sbo_poly<base_test_class, k_nSBOSize>;

class small_test_class : public base_test_class
{
public:
    small_test_class(std::array<char, k_nSmallDataSize> data) : m_Data(data)
    {
    }

    virtual size_t get_hash() const override
    {
        size_t nHash = 0;
        for (char c : m_Data)
            qx::hash_combine(nHash, c);

        return nHash;
    }

private:
    std::array<char, k_nSmallDataSize> m_Data;
};
static_assert(qx::sbo_poly_fittable_type_v<sbo_type, small_test_class>);

class big_test_class : public base_test_class
{
public:
    big_test_class(std::array<char, k_nBigDataSize> data) : m_Data(data)
    {
    }

    virtual size_t get_hash() const override
    {
        // use the same number of elements as in small_test_class,
        // so that the time of hashing is the same for both classes,
        // and the difference in performance will be only because of SBO
        size_t nHash = 0;
        for (size_t i = 0; i < k_nSmallDataSize; ++i)
            qx::hash_combine(nHash, m_Data[i]);

        return nHash;
    }

private:
    std::array<char, k_nBigDataSize> m_Data;
};
static_assert(!qx::sbo_poly_fittable_type_v<sbo_type, big_test_class>);

template<size_t nSize>
static std::array<char, nSize> generate_random_data(std::mt19937& randomEngine)
{
    static constexpr char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::uniform_int_distribution<int> charDist(0, sizeof(charset) - 2);

    std::array<char, nSize> data;
    for (size_t i = 0; i < nSize; ++i)
        data[i] = charset[charDist(randomEngine)];

    return data;
}

namespace traits
{

template<bool bRandomLocation>
struct base_traits
{
    // Simulate random memory locations (fragmentation + shuffling)
    static constexpr bool k_bRandomLocation = bRandomLocation;
};

template<bool bRandomLocation>
struct unique_ptr_traits : base_traits<bRandomLocation>
{
    using data_type = std::unique_ptr<base_test_class>;

    static data_type create_small(std::mt19937& randomEngine)
    {
        return std::make_unique<small_test_class>(generate_random_data<k_nSmallDataSize>(randomEngine));
    }

    static data_type create_big(std::mt19937& randomEngine)
    {
        return std::make_unique<big_test_class>(generate_random_data<k_nBigDataSize>(randomEngine));
    }
};

template<bool bRandomLocation>
struct sbo_poly_traits : base_traits<bRandomLocation>
{
    using data_type = sbo_type;

    static data_type create_small(std::mt19937& randomEngine)
    {
        return small_test_class(generate_random_data<k_nSmallDataSize>(randomEngine));
    }

    static data_type create_big(std::mt19937& randomEngine)
    {
        return big_test_class(generate_random_data<k_nBigDataSize>(randomEngine));
    }
};

} // namespace traits

template<class data_traits_t>
class data_vector_fixture : public benchmark::Fixture
{
    using data_type                         = typename data_traits_t::data_type;
    static constexpr bool k_bRandomLocation = data_traits_t::k_bRandomLocation;

public:
    virtual void SetUp(::benchmark::State& state) override
    {
        m_FakeData.clear();
        m_RealData.clear();

        constexpr size_t nSeed = 0;
        std::mt19937     randomEngine(nSeed);

        // assume that in live scenarios we use an SBO size that way that most of the data is small
        constexpr double            fSmallProbability = 0.9;
        std::bernoulli_distribution IsSmall(fSmallProbability);

        constexpr double            fFakeDataProbability = 0.8;
        std::bernoulli_distribution IsFake(fFakeDataProbability);

        for (int i = 0; i < state.range(0);)
        {
            const bool bFake = k_bRandomLocation && IsFake(randomEngine);

            std::vector<data_type>& container = bFake ? m_FakeData : m_RealData;
            if (IsSmall(randomEngine))
                container.emplace_back(data_traits_t::create_small(randomEngine));
            else
                container.emplace_back(data_traits_t::create_big(randomEngine));

            if (!bFake)
                ++i;
        }

        if constexpr (k_bRandomLocation)
        {
            // shuffle the data to simulate random memory locations
            std::shuffle(m_RealData.begin(), m_RealData.end(), randomEngine);
        }
    }

protected:
    std::vector<data_type> m_FakeData;
    std::vector<data_type> m_RealData;
};

BENCHMARK_TEMPLATE_METHOD_F(data_vector_fixture, bench)(benchmark::State& st)
{
    for (auto _ : st)
        for (auto& item : this->m_RealData)
            benchmark::DoNotOptimize(item->get_hash());
}

BENCHMARK_TEMPLATE_INSTANTIATE_F(data_vector_fixture, bench, traits::unique_ptr_traits<false>)->Arg(100000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(data_vector_fixture, bench, traits::sbo_poly_traits<false>)->Arg(100000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(data_vector_fixture, bench, traits::unique_ptr_traits<true>)->Arg(100000);
BENCHMARK_TEMPLATE_INSTANTIATE_F(data_vector_fixture, bench, traits::sbo_poly_traits<true>)->Arg(100000);
