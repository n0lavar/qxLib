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



//-------------------------------- is_iterator -------------------------------

template<class T>
using iterator_category = typename T::iterator_category;

template<typename T, typename = void>
struct is_iterator
{
    static constexpr bool value = false;
};

// check if T is iterator (all iterators must contain iterator_category def
// important! some iterators are implemented as value_type* (see libstdc++ and std::array)
// in this case check will fail
template<typename T>
struct is_iterator<T, typename std::enable_if<is_detected<iterator_category, T>::value>::type>
{
    static constexpr bool value = true;
};

template< class T >
constexpr bool is_iterator_v = is_iterator<T>::value;

//--------------------------------- are_same ---------------------------------

template <typename ...>
struct are_same : std::true_type { };

template <typename S, typename T, typename ... Ts>
struct are_same <S, T, Ts...> : std::false_type { };

// check if all of variadic arguments are same type
template <typename T, typename ... Ts>
struct are_same <T, T, Ts...> : are_same<T, Ts...> { };

template <typename ... Ts>
inline constexpr bool are_same_v = are_same<Ts...>::value;

}
