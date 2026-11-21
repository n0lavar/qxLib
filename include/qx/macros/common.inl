/**

    @file      common.inl
    @author    Khrapov
    @date      19.09.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx::details
{

template<class lambda_t>
class call_before_main_invoker
{
public:
    constexpr call_before_main_invoker(lambda_t lambda);

private:
    lambda_t m_Lambda;
};

template<class lambda_t>
constexpr call_before_main_invoker<lambda_t>::call_before_main_invoker(lambda_t lambda) : m_Lambda(std::move(lambda))
{
    m_Lambda();
}

} // namespace qx::details

#define QX_DETAILS_DO_JOIN(symbol1, symbol2) symbol1##symbol2

#if !QX_RELEASE && QX_MSVC_COMPATIBLE
    #define QX_DETAILS_DISABLE_OPTIMIZATIONS() __pragma(optimize("", off))
    #define QX_DETAILS_ENABLE_OPTIMIZATIONS()  __pragma(optimize("", on))
#else
    #define QX_DETAILS_DISABLE_OPTIMIZATIONS()
    #define QX_DETAILS_ENABLE_OPTIMIZATIONS()
#endif

#if !QX_DEBUG && QX_MSVC_COMPATIBLE
    #define QX_DETAILS_FORCE_INLINE __forceinline
#elif !QX_DEBUG && (QX_GNU || QX_CLANG || QX_APPLE_CLANG)
    #define QX_DETAILS_FORCE_INLINE inline __attribute__((always_inline))
#else
    #define QX_DETAILS_FORCE_INLINE inline
#endif

// clang-format off
#define QX_DETAILS_PRIVATE_APPEND_VA_ARG_COUNT(prefix, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, count, ...) prefix##count

#if !defined(_MSVC_TRADITIONAL) || !_MSVC_TRADITIONAL
    #define QX_DETAILS_APPEND_VA_ARG_COUNT(prefix, ...) QX_DETAILS_PRIVATE_APPEND_VA_ARG_COUNT(prefix __VA_OPT__(,) __VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#else
    #define QX_DETAILS_APPEND_VA_ARG_COUNT_INVOKE(macro, args_in_parens) QX_EXPAND(macro##args_in_parens)
	#define QX_DETAILS_APPEND_VA_ARG_COUNT(prefix, ...) QX_DETAILS_APPEND_VA_ARG_COUNT_INVOKE(QX_DETAILS_PRIVATE_APPEND_VA_ARG_COUNT, (prefix __VA_OPT__(,) __VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#endif
// clang-format on

#if QX_MSVC_COMPATIBLE
    #define QX_DETAILS_EMPTY_BASES __declspec(empty_bases)
#else
    #define QX_DETAILS_EMPTY_BASES
#endif
