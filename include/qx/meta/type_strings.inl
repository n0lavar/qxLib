/**

    @file      type_strings.inl
    @author    Khrapov
    @date      24.09.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

namespace qx
{

template<class T, class char_t>
constexpr typename type_strings<T, char_t>::string_view_type type_strings<T, char_t>::create_full_signature()
{
#if QX_MSVC
    return QX_STR_PREFIX(char_t, __FUNCSIG__);
#elif QX_CLANG || QX_GNU
    static_assert(
        std::is_same_v<char_t, char>,
        "Can't use __PRETTY_FUNCTION__ with wchar_t as it is not a macro but a function");

    return __PRETTY_FUNCTION__;
#endif
}

template<class T, class char_t>
constexpr typename type_strings<T, char_t>::string_view_type type_strings<T, char_t>::create_signature()
{
    constexpr string_view_type svFunctionSignature = create_full_signature();

#if QX_MSVC
    constexpr string_view_type svStartMarker = QX_STR_PREFIX(char_t, "type_strings<");
    constexpr string_view_type svEndMarker   = QX_STR_PREFIX(char_t, ">::create_full_signature(");
#elif QX_CLANG
    constexpr string_view_type svStartMarker = QX_STR_PREFIX(char_t, "T = ");
    constexpr string_view_type svEndMarker   = QX_STR_PREFIX(char_t, ", char_t = ");
#elif QX_GNU
    constexpr string_view_type svStartMarker = QX_STR_PREFIX(char_t, "T = ");
    constexpr string_view_type svEndMarker   = QX_STR_PREFIX(char_t, ";");
#endif

    size_t nStartMarker = svFunctionSignature.find(svStartMarker);
    size_t nStart       = nStartMarker != string_view_type::npos ? (nStartMarker + svStartMarker.size()) : 0;

    constexpr string_view_type classMarker  = QX_STR_PREFIX(char_t, "class ");
    size_t                     nClassMarker = svFunctionSignature.find(classMarker, nStart);
    if (nClassMarker != string_view_type::npos)
        nStart = nClassMarker + classMarker.size();

    size_t nEndMarker = svFunctionSignature.find(svEndMarker, nStart);
    size_t nEnd       = nEndMarker != string_view_type::npos ? nEndMarker : svFunctionSignature.size();

#if QX_MSVC
    size_t nCharCommaMarker = svFunctionSignature.rfind(QX_CHAR_PREFIX(char_t, ','), nEnd);
    if (nCharCommaMarker != string_view_type::npos)
        nEnd = nCharCommaMarker;
#endif

    return string_view_type(svFunctionSignature.data() + nStart, nEnd - nStart);
}

template<class T, class char_t>
constexpr size_t type_strings<T, char_t>::get_num_template_parameters()
{
    const string_view_type svSignature = create_signature();

    size_t nBraceCounter = 0;
    size_t nParams       = 0;
    bool   bLambda       = false;

    for (size_t i = 0; i < svSignature.size(); ++i)
    {
        switch (svSignature[i])
        {
        case QX_CHAR_PREFIX(char_t, '<'):
            if (!bLambda)
            {
                ++nBraceCounter;

                if (svSignature.find(lambdaMarker, i + 1) == i + 1)
                    bLambda = true;
                else if (nParams == 0 && nBraceCounter == 1)
                    ++nParams;
            }
            break;

        case QX_CHAR_PREFIX(char_t, '>'):
            --nBraceCounter;

            if (bLambda)
                bLambda = false;

            break;

        case QX_CHAR_PREFIX(char_t, ','):
            if (nBraceCounter == 1)
                ++nParams;

            break;
        }
    }

    return nParams;
}

template<class T, class char_t>
constexpr typename type_strings<T, char_t>::string_view_type type_strings<T, char_t>::get_signature()
{
    return create_signature();
}

template<class T, class char_t>
constexpr typename type_strings<T, char_t>::string_view_type type_strings<T, char_t>::get_name()
{
    constexpr string_view_type svStartMarker = QX_STR_PREFIX(char_t, "<");
    const string_view_type     svSignature   = create_signature();
    size_t                     nStartMarker  = svSignature.find(svStartMarker);

    if (nStartMarker != string_view_type::npos && svSignature.find(lambdaMarker, nStartMarker) == nStartMarker + 1)
        nStartMarker = string_view_type::npos;

    return string_view_type(
        svSignature.data(),
        nStartMarker != string_view_type::npos ? nStartMarker : svSignature.size());
}

template<class T, class char_t>
constexpr auto type_strings<T, char_t>::get_template_parameters()
{
    std::array<string_view_type, get_num_template_parameters()> tokens;

    const string_view_type svSignature = create_signature();

    size_t nTokenStart   = 0;
    size_t nBraceCounter = 0;
    size_t nParam        = 0;

    const auto add_token = [&tokens, &svSignature](size_t nToken, size_t nStart, size_t nEnd)
    {
        while (svSignature[nStart] == QX_CHAR_PREFIX(char_t, ' '))
            ++nStart;

        while (svSignature[nEnd] == QX_CHAR_PREFIX(char_t, ' '))
            --nEnd;

        constexpr string_view_type classMarker = QX_STR_PREFIX(char_t, "class ");
        if (string_view_type(svSignature.data() + nStart, nEnd - nStart).starts_with(classMarker))
            nStart += classMarker.size();

        tokens[nToken] = string_view_type(svSignature.data() + nStart, nEnd + 1 - nStart);
    };

    bool bLambda = false;

    for (size_t i = 0; i < svSignature.size(); ++i)
    {
        switch (svSignature[i])
        {
        case QX_CHAR_PREFIX(char_t, '<'):
            ++nBraceCounter;

            if (nTokenStart == 0)
                nTokenStart = i + 1;
            else if (!bLambda && svSignature.find(lambdaMarker, i + 1) == i + 1)
                bLambda = true;

            break;

        case QX_CHAR_PREFIX(char_t, '>'):
            --nBraceCounter;
            if (bLambda)
                bLambda = false;

            break;

        case QX_CHAR_PREFIX(char_t, ','):
            if (nBraceCounter == 1)
            {
                add_token(nParam, nTokenStart, i - 1);
                nTokenStart = i + 1;
                ++nParam;
            }
            break;
        }
    }

    if (tokens.size() > 0)
    {
        size_t nTokenEnd = svSignature.size() - 1;

        if (svSignature[nTokenEnd] == QX_CHAR_PREFIX(char_t, ' '))
            --nTokenEnd;

        if (svSignature[nTokenEnd] == QX_CHAR_PREFIX(char_t, '>'))
            --nTokenEnd;

        add_token(nParam, nTokenStart, nTokenEnd);
    }

    return tokens;
}

} // namespace qx
