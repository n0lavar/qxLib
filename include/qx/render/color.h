//==============================================================================
//
//!\file                            color.h
//
//!\brief       Contains qx::color class
//!\details     ~
//
//!\author      Khrapov
//!\date        2.11.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace qx
{

//==============================================================================
//
//!\class                          qx::color
//
//!\brief   RGBA color
//!\details ~
//
//!\author  Khrapov
//!\date    10.04.2021
//
//==============================================================================
class color
{
public:

    constexpr           color       (void)          noexcept = default;
    constexpr           color       (color&&)       noexcept = default;
    constexpr           color       (const color&)  noexcept = default;
    constexpr color&    operator=   (color&&)       noexcept = default;
    constexpr color&    operator=   (const color&)  noexcept = default;

    constexpr           color       (float          fRed,
                                     float          fGreen,
                                     float          fBlue,
                                     float          fAlpha = 1.f)   noexcept;
    constexpr           color       (int            nRed,
                                     int            nGreen,
                                     int            nBlue,
                                     int            nAlpha = 255)   noexcept;

    constexpr float     r           (void)                  const   noexcept;
    constexpr float     g           (void)                  const   noexcept;
    constexpr float     b           (void)                  const   noexcept;
    constexpr float     a           (void)                  const   noexcept;
    constexpr const float* data     (void)                  const   noexcept;
    constexpr bool      operator==  (const color  & other)  const   noexcept;
    constexpr operator glm::vec3    (void)                  const   noexcept;
    constexpr operator glm::vec4    (void)                  const   noexcept;

    constexpr void      update_r    (float          fDeltaValue)    noexcept;
    constexpr void      update_g    (float          fDeltaValue)    noexcept;
    constexpr void      update_b    (float          fDeltaValue)    noexcept;
    constexpr void      update_a    (float          fDeltaValue)    noexcept;
    constexpr void      update_r_dec(int            nDeltaValue)    noexcept;
    constexpr void      update_g_dec(int            nDeltaValue)    noexcept;
    constexpr void      update_b_dec(int            nDeltaValue)    noexcept;
    constexpr void      update_a_dec(int            nDeltaValue)    noexcept;
    constexpr void      set_r       (float          fValue)         noexcept;
    constexpr void      set_g       (float          fValue)         noexcept;
    constexpr void      set_b       (float          fValue)         noexcept;
    constexpr void      set_a       (float          fValue)         noexcept;
    constexpr void      set_r_dec   (int            nValue)         noexcept;
    constexpr void      set_g_dec   (int            nValue)         noexcept;
    constexpr void      set_b_dec   (int            nValue)         noexcept;
    constexpr void      set_a_dec   (int            nValue)         noexcept;

    static constexpr color aqua     (void) noexcept { return color(000, 255, 255); }
    static constexpr color black    (void) noexcept { return color(000, 000, 000); }
    static constexpr color blue     (void) noexcept { return color(000, 000, 255); }
    static constexpr color fuchsia  (void) noexcept { return color(255, 000, 255); }
    static constexpr color gray     (void) noexcept { return color(128, 128, 128); }
    static constexpr color green    (void) noexcept { return color(000, 128, 000); }
    static constexpr color lime     (void) noexcept { return color(000, 255, 000); }
    static constexpr color maroon   (void) noexcept { return color(128, 000, 000); }
    static constexpr color navy     (void) noexcept { return color(000, 000, 128); }
    static constexpr color olive    (void) noexcept { return color(128, 128, 000); }
    static constexpr color purple   (void) noexcept { return color(128, 000, 128); }
    static constexpr color red      (void) noexcept { return color(255, 000, 000); }
    static constexpr color silver   (void) noexcept { return color(192, 192, 192); }
    static constexpr color teal     (void) noexcept { return color(000, 128, 128); }
    static constexpr color white    (void) noexcept { return color(255, 255, 255); }
    static constexpr color yellow   (void) noexcept { return color(255, 255, 000); }

private:

    static constexpr float clamp_value  (float          fValue)         noexcept;
    static constexpr float dec_to_float (int            nValue)         noexcept;

    constexpr void  assign_checked  (const glm::vec4  & other)          noexcept;
    constexpr void  assign_r_checked(float              fValue)         noexcept;
    constexpr void  assign_g_checked(float              fValue)         noexcept;
    constexpr void  assign_b_checked(float              fValue)         noexcept;
    constexpr void  assign_a_checked(float              fValue)         noexcept;

private:

    glm::vec4 m_Color = glm::vec4(1.f);
};

}

#include <qx/render/color.inl>
