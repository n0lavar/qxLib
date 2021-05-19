//==============================================================================
//
//!\file                          easing_sequence.h
//
//!\brief       Contains qx::base_easing_sequence class
//!\details     ~
//
//!\author      Khrapov
//!\date        4.05.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/easing/easing_element.h>

#include <vector>

namespace qx
{

//==============================================================================
//
//!\class                       qx::base_easing_sequence
//
//!\brief   qx::base_easing_element queue
//!\details ~
//
//!\author  Khrapov
//!\date    04.05.2021
//
//==============================================================================
template<typename T>
class base_easing_sequence
{
public:

    using easing_element_type = base_easing_element<T>;
    using type = T;

    void    push_back       (easing_element_type element)           noexcept;
    template<typename ...Args>
    void    emplace_back    (Args&&...  args)                       noexcept;
    void    clear           (void)                                  noexcept;

    void    start           (void)                                  noexcept;
    void    pause           (void)                                  noexcept;
    void    resume          (void)                                  noexcept;
    void    skip            (void)                                  noexcept;
    void    reset           (void)                                  noexcept;
    void    update          (T          fDeltaTime)                 noexcept;
    void    set_looped      (bool       bLooped)                    noexcept;
    void    set_speed       (T          fSpeed)                     noexcept;

    T       get             (void)                          const   noexcept;
    T       get_fraction    (void)                          const   noexcept;
    T       get_speed       (void)                          const   noexcept;
    bool    is_not_started  (void)                          const   noexcept;
    bool    is_started      (void)                          const   noexcept;
    bool    is_paused       (void)                          const   noexcept;
    bool    is_finished     (void)                          const   noexcept;
    bool    is_looped       (void)                          const   noexcept;

private:

    easing_element_type       * get_current_element (void)          noexcept;
    const easing_element_type * get_current_element (void)  const   noexcept;
    void                        update_total_time   (void)          noexcept;

private:

    std::vector<easing_element_type>    m_ElementsSequence;
    size_t                              m_nCurrentElement   = 0;
    T                                   m_fTotalTime        = T(0.f);
    T                                   m_fCurrentTime      = T(0.f);
    T                                   m_fSpeed            = T(1.f);
    bool                                m_bLoop             = false;
};

using easing_sequence = base_easing_sequence<float>;

}

#include <qx/easing/easing_sequence.inl>
