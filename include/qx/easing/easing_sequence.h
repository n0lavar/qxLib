/**

    @file      easing_sequence.h
    @author    Khrapov
    @date      4.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/easing/easing_element.h>

#include <vector>

namespace qx
{

/**

    @class   base_easing_sequence
    @brief   qx::base_easing_element queue
    @details ~
    @tparam  T - floating point ish value
    @author  Khrapov
    @date    04.05.2021

**/
template<class T>
class base_easing_sequence
{
public:
    using easing_element_type = base_easing_element<T>;
    using type                = T;

public:
    /**
        @brief Add easing element to queue
        @param element - easing element
    **/
    void push_back(easing_element_type element) noexcept;

    /**
        @brief  Add easing element to queue by constructing in-place
        @tparam args_t - template parameter pack type
        @param  args   - arguments for constructing
    **/
    template<class... args_t>
    void emplace_back(args_t&&... args) noexcept;

    /**
        @brief Clear elements queue
    **/
    void clear() noexcept;

    /**
        @brief Start easing element sequence playing
    **/
    void start() noexcept;

    /**
        @brief Pause easing element sequence playing
    **/
    void pause() noexcept;

    /**
        @brief Resume easing element sequence playing
    **/
    void resume() noexcept;

    /**
        @brief Skip current element
    **/
    void skip() noexcept;

    /**
        @brief Reset sequence
    **/
    void reset() noexcept;

    /**
        @brief Update easing element sequence
        @param fDeltaTime - delta time
    **/
    void update(T fDeltaTime) noexcept;

    /**
        @brief Set loop state
        @param bLooped - true if loop
    **/
    void set_looped(bool bLooped) noexcept;

    /**
        @brief Set updating speed value
        @param fSpeed - speed
    **/
    void set_speed(T fSpeed) noexcept;

    /**
        @brief  Get value of current sequence element
        @retval - value of current sequence element
    **/
    T get() const noexcept;

    /**
        @brief  Get a fraction indicating how much of the sequence has played
        @retval - fraction [0.0, 1.0]
    **/
    T get_fraction() const noexcept;

    /**
        @brief  Get updating speed value
        @retval - speed
    **/
    T get_speed() const noexcept;

    /**
        @brief  Is sequence not started
        @retval - true if sequence is not started
    **/
    bool is_not_started() const noexcept;

    /**
        @brief  Is sequence started
        @retval - true if sequence is started
    **/
    bool is_started() const noexcept;

    /**
        @brief  Is sequence paused
        @retval - true if sequence is paused
    **/
    bool is_paused() const noexcept;

    /**
        @brief  Is sequence finished
        @retval - true if sequence is finished
    **/
    bool is_finished() const noexcept;

    /**
        @brief  Is sequence looped
        @retval - true if sequence is looped
    **/
    bool is_looped() const noexcept;

private:
    /**
        @brief  Get current element pointer or nullptr if no elements
        @retval - current element pointer or nullptr if no elements
    **/
    easing_element_type* get_current_element() noexcept;

    /**
        @brief  Get current element pointer or nullptr if no elements
        @retval - current element pointer or nullptr if no elements
    **/
    const easing_element_type* get_current_element() const noexcept;

    /**
        @brief Update total time by adding time from last element
    **/
    void update_total_time() noexcept;

private:
    std::vector<easing_element_type> m_ElementsSequence;
    size_t                           m_nCurrentElement = 0;
    T                                m_fTotalTime      = T(0.f);
    T                                m_fCurrentTime    = T(0.f);
    T                                m_fSpeed          = T(1.f);
    bool                             m_bLoop           = false;
};

using easing_sequence = base_easing_sequence<float>;

} // namespace qx

#include <qx/easing/easing_sequence.inl>
