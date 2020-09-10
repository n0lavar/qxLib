//==============================================================================
//
//!\file                        type_traits.h
//
//!\brief       Detectors templates
//!\details     ~
//
//!\author      Khrapov
//!\date        22.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <type_traits>

namespace qx
{

// https://en.cppreference.com/w/cpp/experimental/nonesuch
// library fundamentals TS v2

struct nonesuch
{
    ~nonesuch() = delete;
    nonesuch(nonesuch const&) = delete;
    void operator=(nonesuch const&) = delete;
};

//--------------------------------- detectors --------------------------------
// https://en.cppreference.com/w/cpp/experimental/is_detected
// library fundamentals TS v2

namespace detail
{
    template <class Default, class AlwaysVoid,
        template<class...> class Op, class... Args>
    struct detector
    {
        using value_t = std::false_type;
        using type = Default;
    };

    template <class Default, template<class...> class Op, class... Args>
    struct detector<Default, std::void_t<Op<Args...>>, Op, Args...>
    {
        using value_t = std::true_type;
        using type = Op<Args...>;
    };
}

template <template<class...> class Op, class... Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template <template<class...> class Op, class... Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template<class...> class Op, class... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

}
