/**

    @file      common.inl
    @author    Khrapov
    @date      19.09.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/

namespace qx::details
{

constexpr const char_type* last_slash(const char_type* str)
{
    const char_type* pszLastSlash = str;
    while (str && *str != QXT('\0'))
    {
        if (*str == QXT('\\') || *str == QXT('/'))
            pszLastSlash = str;

        ++str;
    }
    return pszLastSlash + 1;
}

template<class lambda_t>
class call_before_main_invoker
{
public:
    constexpr call_before_main_invoker(lambda_t lambda) : m_Lambda(std::move(lambda))
    {
        m_Lambda();
    }

private:
    lambda_t m_Lambda;
};

} // namespace qx::details

#define _QX_DO_JOIN(symbol1, symbol2) symbol1##symbol2

#if !QX_RELEASE && QX_MSVC
    #define _QX_DISABLE_OPTIMIZATIONS() __pragma(optimize("", off))
    #define _QX_ENABLE_OPTIMIZATIONS()  __pragma(optimize("", on))
#else
    #define _QX_DISABLE_OPTIMIZATIONS()
    #define _QX_ENABLE_OPTIMIZATIONS()
#endif

#if !QX_DEBUG && QX_MSVC
    #define _QX_FORCE_INLINE __forceinline
#elif !QX_DEBUG && (QX_GNU || QX_CLANG || QX_APPLE_CLANG)
    #define _QX_FORCE_INLINE inline __attribute__((always_inline))
#else
    #define _QX_FORCE_INLINE inline
#endif

// clang-format off
#define _QX_PRIVATE_APPEND_VA_ARG_COUNT(prefix, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, count, ...) prefix##count

#if !defined(_MSVC_TRADITIONAL) || !_MSVC_TRADITIONAL
    #define _QX_APPEND_VA_ARG_COUNT(prefix, ...) _QX_PRIVATE_APPEND_VA_ARG_COUNT(prefix, ##__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#else
    #define _QX_APPEND_VA_ARG_COUNT_INVOKE(macro, args_in_parens) QX_EXPAND(macro##args_in_parens)
	#define _QX_APPEND_VA_ARG_COUNT(prefix, ...) _QX_APPEND_VA_ARG_COUNT_INVOKE(_QX_PRIVATE_APPEND_VA_ARG_COUNT, (prefix, ##__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#endif
// clang-format on
