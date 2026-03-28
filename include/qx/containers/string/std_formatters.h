/**

    @file      std_formatters.h
    @details   The content of the file extends QX_FMT_NS::formatter to let it support some std classes.
               It may break a compilation if someone already did it or some of the realisations were added to std.
               Include it on your own risk.
    @author    Khrapov
    @date      26.08.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/macros/static_assert.h>

#include <format>
#include <type_traits>
#include <variant>

namespace qx
{

template<class T, class char_t>
concept formattable_c = requires(T& value, QX_FMT_NS::basic_format_context<std::add_pointer_t<char_t>, char_t>& ctx) {
    QX_FMT_NS::formatter<T, char_t>().format(value, ctx);
};

} // namespace qx

template<class char_t, class... args_t>
struct QX_FMT_NS::formatter<std::variant<args_t...>, char_t> : qx::basic_formatter<char_t>
{
    template<class context_t>
    constexpr auto format(const std::variant<args_t...>& variant, context_t& ctx) const
    {
        return std::visit(
            [&ctx]<class T>(const T& value)
            {
                if constexpr (qx::formattable_c<T, char_t>)
                    return QX_FMT_NS::format_to(ctx.out(), QX_STR_PREFIX(char_t, "{}"), value);
                else
                    QX_STATIC_ASSERT_NO_INSTANTIATION("No formatter for this type");
            },
            variant);
    }
};
