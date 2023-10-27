/**

    @file      format_string.inl
    @author    Khrapov
    @date      16.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class char_t, class... args_t>
template<class T>
    requires std::convertible_to<const T&, qx::basic_string_view<char_t>>
consteval basic_format_string_strong_checks<char_t, args_t...>::basic_format_string_strong_checks(const T& value)
    : std::basic_format_string<char_t, args_t...>(parse_format_string(value))
{
}

template<class char_t, class... args_t>
template<class T>
consteval const T& basic_format_string_strong_checks<char_t, args_t...>::parse_format_string(const T& value)
{
    int                       nBracesBalance  = 0;
    size_t                    nNumBracesPairs = 0;
    basic_string_view<char_t> svFormatString  = value;

    for (size_t i = 0; i < svFormatString.size(); ++i)
    {
        if (svFormatString[i] == QX_CHAR_PREFIX(char_t, '{'))
        {
            if (i + 1 < svFormatString.size() && svFormatString[i + 1] == QX_CHAR_PREFIX(char_t, '{'))
            {
                ++i;
                continue;
            }

            ++nBracesBalance;
        }
        else if (svFormatString[i] == QX_CHAR_PREFIX(char_t, '}'))
        {
            if (i + 1 < svFormatString.size() && svFormatString[i + 1] == QX_CHAR_PREFIX(char_t, '}'))
            {
                ++i;
                continue;
            }

            ++nNumBracesPairs;
            --nBracesBalance;

            if (nBracesBalance < 0)
            {
                throw std::format_error(
                    "Format string error: num of closing braces > num of opening braces at some point of the format "
                    "string");
            }
        }
    }

    if (nBracesBalance > 0)
    {
        throw std::format_error(
            "Format string error: num of opening braces > num of closing braces at the end of the format string");
    }

    if (sizeof...(args_t) != nNumBracesPairs)
        throw std::format_error("Format string error: num of args != num of braces pairs");

    return value;
}

} // namespace qx
