/**

    @file      common.inl
    @author    Khrapov
    @date      19.09.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

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

template<class lambda_type>
class call_before_main_invoker
{
public:
    constexpr call_before_main_invoker(lambda_type lambda) : m_Lambda(std::move(lambda))
    {
        m_Lambda();
    }

private:
    lambda_type m_Lambda;
};

} // namespace qx::details

#define _QX_JOIN(symbol1, symbol2)    _QX_DO_JOIN(symbol1, symbol2)
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
