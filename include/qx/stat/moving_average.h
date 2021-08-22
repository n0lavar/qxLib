/**

    @file      moving_average.h
    @brief     Contains qx::moving_average class
    @author    Khrapov
    @date      1.06.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/easing/easing_functions.h>

#include <deque>
#include <vector>

namespace qx
{

template<typename T>
using moving_average_weights_func =
    std::function<std::vector<T>(size_t nEntries)>;

/**
    @brief  Generate weights for moving_average as arithmetic mean
    @tparam T        - 
    @param  nEntries - number of entries in moving_average
    @retval          - weights
**/
template<typename T>
inline std::vector<T> get_moving_average_simple_weights(size_t nEntries);

/**
    @brief  Generate weights for moving_average with linearly decrease,
            from highest weight for the most recent data, down to zero
    @tparam T        - 
    @param  nEntries - number of entries in moving_average
    @retval          - weights
**/
template<typename T>
inline std::vector<T> get_moving_average_linear_weights(size_t nEntries);

/**
    @brief  Generate weights for moving_average with exponential decrease,
            from highest weight for the most recent data, down to zero
    @tparam T        - 
    @param  nEntries - number of entries in moving_average
    @retval          - weights
**/
template<typename T>
inline std::vector<T> get_moving_average_exp_weights(size_t nEntries);

/**

    @class   moving_average
    @brief   Moving average is the unweighted mean of the previous K entries
    @details \see https://tinyurl.com/d3nfcaca to compare weights filling funcs
             blue    - random numbers [-5, 5]
             green   - get_moving_average_simple_weights
             yellow  - get_moving_average_linear_weights
             red     - get_moving_average_exp_weights with ALPHA = 0.8f
    @tparam  T - 
    @author  Khrapov
    @date    1.06.2021

**/
template<typename T>
class moving_average
{
public:
    /**
        @brief moving_average object constructor
        @param nEntries   - number of entries in average calc
        @param startValue - start value
        @param func       - weights func
    **/
    moving_average(
        size_t                         nEntries,
        T                              startValue,
        moving_average_weights_func<T> func =
            get_moving_average_simple_weights<T>);

    /**
        @brief  Update moving average
        @param  value - new value
        @retval       - new moving average
    **/
    T update(T value);

    /**
        @brief  Get current moving average
        @retval - current moving average
    **/
    T get(void) const;

    /**
        @brief  Get number of entries in average calc
        @retval - number of entries in average calc
    **/
    size_t get_num_entries(void) const;

private:
    T              m_Value;
    std::deque<T>  m_Entries;
    std::vector<T> m_Weights;
};

} // namespace qx

#include <qx/stat/moving_average.inl>
