/**

    @file      moving_average.inl
    @author    Khrapov
    @date      20.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<typename T>
inline std::vector<T> get_moving_average_simple_weights(size_t nEntries)
{
    return std::vector<T>(nEntries, T(1.f) / static_cast<T>(nEntries));
}

template<typename T>
inline std::vector<T> get_moving_average_linear_weights(size_t nEntries)
{
    std::vector<T> weights(nEntries, 0.f);

    const T fDenominator = static_cast<T>(nEntries * (nEntries + 1)) / T(2.f);

    for (size_t i = 0; i < nEntries; ++i)
        weights[i] = static_cast<T>(i + 1) / fDenominator;

    return weights;
}

template<typename T>
inline std::vector<T> get_moving_average_exp_weights(size_t nEntries)
{
    std::vector<T> weights(nEntries, 0.f);

    // the degree of weighting decrease, a constant smoothing
    // factor between 0 and 1. A higher alpha discounts
    // older observations faster
    constexpr T fAlpha = T(0.8f);

    for (size_t i = 0; i < nEntries; ++i)
        weights[i] = fAlpha * std::pow(1 - fAlpha, static_cast<T>(nEntries - i - 1));

    return weights;
}

template<typename T>
inline moving_average<T>::moving_average(size_t nEntries, T startValue, moving_average_weights_func<T> func)
    : m_Value(startValue)
    , m_Entries(nEntries, startValue)
    , m_Weights(func(m_Entries.size()))
{
}

template<typename T>
inline T moving_average<T>::update(T value)
{
    m_Entries.pop_front();

    T fSumm = T(0.f);
    for (size_t i = 0; i < m_Entries.size(); ++i)
        fSumm += m_Entries[i] * m_Weights[i];

    m_Value = fSumm / static_cast<T>(m_Entries.size());
    m_Entries.push_back(value);
    return m_Value;
}

template<typename T>
inline T moving_average<T>::get() const
{
    return m_Value;
}

template<typename T>
inline size_t moving_average<T>::get_num_entries() const
{
    return m_Entries.size();
}

} // namespace qx
