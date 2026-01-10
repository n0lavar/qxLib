/**

    @file      macro_user_message.h
    @author    Khrapov
    @date      4.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_converters.h>

namespace qx
{

template<class... args_t>
concept log_acceptable_args_c = (sizeof...(args_t) > 0 && format_acceptable_args_c<char_type, args_t...>);

namespace details
{

inline string format_macro_user_message()
{
    return QXT("");
}

inline string format_macro_user_message(const char* pszUserMessage)
{
    return to_string(pszUserMessage);
}

inline string format_macro_user_message(string sUserMessage)
{
    return sUserMessage;
}

template<class first_arg_t, class... rest_args_t>
    requires(log_acceptable_args_c<first_arg_t, rest_args_t...>)
string format_macro_user_message(
    const format_string_strong_checks<first_arg_t, rest_args_t...> sFormat,
    first_arg_t&&                                                  firstArg,
    rest_args_t&&... restArgs)
{
    return string::static_format(sFormat, std::forward<first_arg_t>(firstArg), std::forward<rest_args_t>(restArgs)...);
}

} // namespace details
} // namespace qx

// clang-format off
#define _QX_MACRO_USER_MESSAGE_0()
#define _QX_MACRO_USER_MESSAGE_1(a1) a1
#define _QX_MACRO_USER_MESSAGE_2(a1, a2) QXT(a1), a2
#define _QX_MACRO_USER_MESSAGE_3(a1, a2, a3) QXT(a1), a2, a3
#define _QX_MACRO_USER_MESSAGE_4(a1, a2, a3, a4) QXT(a1), a2, a3, a4
#define _QX_MACRO_USER_MESSAGE_5(a1, a2, a3, a4, a5) QXT(a1), a2, a3, a4, a5
#define _QX_MACRO_USER_MESSAGE_6(a1, a2, a3, a4, a5, a6) QXT(a1), a2, a3, a4, a5, a6
#define _QX_MACRO_USER_MESSAGE_7(a1, a2, a3, a4, a5, a6, a7) QXT(a1), a2, a3, a4, a5, a6, a7
#define _QX_MACRO_USER_MESSAGE_8(a1, a2, a3, a4, a5, a6, a7, a8) QXT(a1), a2, a3, a4, a5, a6, a7, a8
#define _QX_MACRO_USER_MESSAGE_9(a1, a2, a3, a4, a5, a6, a7, a8, a9) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9
#define _QX_MACRO_USER_MESSAGE_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10
#define _QX_MACRO_USER_MESSAGE_11(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11
#define _QX_MACRO_USER_MESSAGE_12(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12
#define _QX_MACRO_USER_MESSAGE_13(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13
#define _QX_MACRO_USER_MESSAGE_14(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14
#define _QX_MACRO_USER_MESSAGE_15(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15
#define _QX_MACRO_USER_MESSAGE_16(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16
#define _QX_MACRO_USER_MESSAGE_17(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17
#define _QX_MACRO_USER_MESSAGE_18(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18
#define _QX_MACRO_USER_MESSAGE_19(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19
#define _QX_MACRO_USER_MESSAGE_20(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20
#define _QX_MACRO_USER_MESSAGE_21(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21
#define _QX_MACRO_USER_MESSAGE_22(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22
#define _QX_MACRO_USER_MESSAGE_23(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23
#define _QX_MACRO_USER_MESSAGE_24(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24
#define _QX_MACRO_USER_MESSAGE_25(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25
#define _QX_MACRO_USER_MESSAGE_26(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26
#define _QX_MACRO_USER_MESSAGE_27(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27
#define _QX_MACRO_USER_MESSAGE_28(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28
#define _QX_MACRO_USER_MESSAGE_29(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29
#define _QX_MACRO_USER_MESSAGE_30(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30
#define _QX_MACRO_USER_MESSAGE_31(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31
#define _QX_MACRO_USER_MESSAGE_32(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32) QXT(a1), a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32
// clang-format on

#define _QX_MACRO_USER_MESSAGE(...)         \
    qx::details::format_macro_user_message( \
        QX_EXPAND(QX_APPEND_VA_ARG_COUNT(_QX_MACRO_USER_MESSAGE_, __VA_ARGS__)(__VA_ARGS__)))
