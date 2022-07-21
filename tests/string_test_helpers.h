/**

    @file      string_test_helpers.h
    @brief     
    @details   ~
    @author    Khrapov
    @date      17.04.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

template<typename Char>
constexpr auto get_string_format_specifier(void)
{
    if constexpr (std::is_same_v<Char, char>)
        return "%s";
    else if constexpr (std::is_same_v<Char, wchar_t>)
        return L"%ls";
}

#define ValueType      typename TypeParam::value_type
#define ConstPointer   typename TypeParam::const_pointer
#define StringTypeTn   typename qx::basic_string<TypeParam>
#define StringType     qx::basic_string<TypeParam>
#define StringHashType qx::basic_string_hash<TypeParam>
#define StdString      typename std::basic_string<ValueType, std::char_traits<ValueType>, std::allocator<ValueType>>
#define StdStringArg \
    GTEST_SINGLE_ARGUMENT(typename std::basic_string<ValueType, std::char_traits<ValueType>, std::allocator<ValueType>>)
#define STR(str) QX_STR_PREFIX(ValueType, str)
#define CH(str)  QX_CHAR_PREFIX(ValueType, str)
