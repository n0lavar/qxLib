//==============================================================================
//
//!\file                        moving_average.h
//
//!\brief       Contains qx::moving_average class
//!\details     ~
//
//!\author      Khrapov
//!\date        1.06.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/easing/easing_functions.h>

#include <deque>
#include <vector>

namespace qx
{

template <typename T>
using moving_average_weights_func = std::function<std::vector<T>(size_t nEntries)>;

//==============================================================================
//!\fn              qx::get_moving_average_simple_weights<T>
//
//!\brief  Generate weights for moving_average as arithmetic mean
//!\param  nEntries - number of entries in moving_average
//!\retval          - weights
//!\author Khrapov
//!\date   23.06.2021
//==============================================================================
template <typename T>
std::vector<T> get_moving_average_simple_weights(size_t nEntries)
{
    return std::vector<T>(nEntries, T(1.f) / static_cast<T>(nEntries));
}

//==============================================================================
//!\fn              qx::get_moving_average_linear_weights<T>
//
//!\brief  Generate weights for moving_average with linearly decrease,
//         from highest weight for the most recent data, down to zero
//!\param  nEntries - number of entries in moving_average
//!\retval          - weights
//!\author Khrapov
//!\date   23.06.2021
//==============================================================================
template <typename T>
std::vector<T> get_moving_average_linear_weights(size_t nEntries)
{
    std::vector<T> weights(nEntries, 0.f);

    const T fDenominator = static_cast<T>(nEntries * (nEntries + 1)) / T(2.f);

    for (size_t i = 0; i < nEntries; ++i)
        weights[i] = static_cast<T>(i + 1) / fDenominator;

    return weights;
}

//==============================================================================
//!\fn            qx::get_moving_average_exp_weights<T, ALPHA>
//
//!\brief  Generate weights for moving_average with exponential decrease,
//         from highest weight for the most recent data, down to zero
//!\param  nEntries - number of entries in moving_average
//!\retval          - weights
//!\author Khrapov
//!\date   23.06.2021
//==============================================================================
template <typename T>
std::vector<T> get_moving_average_exp_weights(size_t nEntries)
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

//==============================================================================
//
//!\class                     qx::moving_average<T>
//
//!\brief   Moving average is the unweighted mean of the previous K entries
//!\details \see https://tinyurl.com/d3nfcaca to compare weights filling funcs
//          blue    - random numbers [-5, 5]
//          green   - get_moving_average_simple_weights
//          yellow  - get_moving_average_linear_weights
//          red     - get_moving_average_exp_weights with ALPHA = 0.8f
//
//!\author  Khrapov
//!\date    1.06.2021
//
//==============================================================================
template<typename T>
class moving_average
{
public:

    moving_average(
        size_t                      nEntries,
        T                           startValue,
        moving_average_weights_func<T> func = get_moving_average_simple_weights<T>)
        : m_Value                   (startValue)
        , m_Entries                 (nEntries, startValue)
        , m_Weights                 (func(m_Entries.size()))
    {
    }

    T update(T value)
    {
        m_Entries.pop_front();

        T fSumm = T(0.f);
        for (size_t i = 0; i < m_Entries.size(); ++i)
            fSumm += m_Entries[i] * m_Weights[i];

        m_Value = fSumm / static_cast<T>(m_Entries.size());
        m_Entries.push_back(value);
        return m_Value;
    }

    T get(void) const
    {
        return m_Value;
    }

    size_t get_num_entries(void) const
    {
        return m_Entries.size();
    }

private:

    T               m_Value;
    std::deque<T>   m_Entries;
    std::vector<T>  m_Weights;
};

}
