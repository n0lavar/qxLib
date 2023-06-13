/**

    @file      type_strings.inl
    @author    Khrapov
    @date      24.09.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

namespace qx
{

template<class T>
constexpr string_view type_strings<T>::create_full_signature()
{
#if QX_MSVC
    return QX_TEXT(__FUNCSIG__);
#elif QX_CLANG || QX_GNU
    return QX_TEXT(__PRETTY_FUNCTION__);
#endif
}

template<class T>
constexpr string_view type_strings<T>::create_signature()
{
    auto functionSignature = create_full_signature();

#if QX_MSVC
    constexpr char_type startMarker[] = QX_TEXT("type_strings<");
    constexpr char_type endMarker[]   = QX_TEXT(">::create_full_signature(");
#elif QX_CLANG
    constexpr char_type startMarker[] = QX_TEXT("T = ");
    constexpr char_type endMarker[]   = QX_TEXT("]");
#elif QX_GNU
    constexpr char_type startMarker[] = QX_TEXT("T = ");
    constexpr char_type endMarker[]   = QX_TEXT(";");
#endif

    size_t nStartMarker = functionSignature.find(startMarker);
    size_t nStart       = nStartMarker != string_view::npos ? (nStartMarker + qx::strlen(startMarker)) : 0;

    constexpr char_type classMarker[] = QX_TEXT("class ");
    size_t              nClassMarker  = functionSignature.find(classMarker, nStart);
    if (nClassMarker != string_view::npos)
        nStart = nClassMarker + qx::strlen(classMarker);

    size_t nEndMarker = functionSignature.find(endMarker, nStart);
    size_t nEnd       = nEndMarker != string_view::npos ? nEndMarker : functionSignature.size();

    return string_view(functionSignature.data() + nStart, nEnd - nStart);
}

template<class T>
constexpr size_t type_strings<T>::get_num_template_parameters()
{
    const string_view svSignature = create_signature();

    size_t nBraceCounter = 0;
    size_t nParams       = 0;
    bool   bLambda       = false;

    for (size_t i = 0; i < svSignature.size(); ++i)
    {
        switch (svSignature[i])
        {
        case QX_TEXT('<'):
            if (!bLambda)
            {
                ++nBraceCounter;

                if (svSignature.find(lambdaMarker, i + 1) == i + 1)
                    bLambda = true;
                else if (nParams == 0 && nBraceCounter == 1)
                    ++nParams;
            }
            break;

        case QX_TEXT('>'):
            --nBraceCounter;

            if (bLambda)
                bLambda = false;

            break;

        case QX_TEXT(','):
            if (nBraceCounter == 1)
                ++nParams;

            break;
        }
    }

    return nParams;
}

template<class T>
constexpr string_view type_strings<T>::get_signature()
{
    return create_signature();
}

template<class T>
constexpr string_view type_strings<T>::get_name()
{
    constexpr char_type startMarker[] = QX_TEXT("<");
    const string_view   svSignature   = create_signature();
    size_t              nStartMarker  = svSignature.find(startMarker);

    if (nStartMarker != string_view::npos && svSignature.find(lambdaMarker, nStartMarker) == nStartMarker + 1)
        nStartMarker = string_view::npos;

    return string_view(svSignature.data(), nStartMarker != string_view::npos ? nStartMarker : svSignature.size());
}

template<class T>
constexpr auto type_strings<T>::get_template_parameters()
{
    std::array<string_view, get_num_template_parameters()> tokens;

    const string_view svSignature = create_signature();

    size_t nTokenStart   = 0;
    size_t nBraceCounter = 0;
    size_t nParam        = 0;

    const auto add_token = [&tokens, &svSignature](size_t nToken, size_t nStart, size_t nEnd)
    {
        while (svSignature[nStart] == QX_TEXT(' '))
            ++nStart;

        while (svSignature[nEnd] == QX_TEXT(' '))
            --nEnd;

        constexpr char_type classMarker[] = QX_TEXT("class ");
        if (string_view(svSignature.data() + nStart, nEnd - nStart).starts_with(classMarker))
            nStart += qx::strlen(classMarker);

        tokens[nToken] = string_view(svSignature.data() + nStart, nEnd + 1 - nStart);
    };

    bool bLambda = false;

    for (size_t i = 0; i < svSignature.size(); ++i)
    {
        switch (svSignature[i])
        {
        case QX_TEXT('<'):
            ++nBraceCounter;

            if (nTokenStart == 0)
                nTokenStart = i + 1;
            else if (!bLambda && svSignature.find(lambdaMarker, i + 1) == i + 1)
                bLambda = true;

            break;

        case QX_TEXT('>'):
            --nBraceCounter;
            if (bLambda)
                bLambda = false;

            break;

        case QX_TEXT(','):
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

        if (svSignature[nTokenEnd] == QX_TEXT(' '))
            --nTokenEnd;

        if (svSignature[nTokenEnd] == QX_TEXT('>'))
            --nTokenEnd;

        add_token(nParam, nTokenStart, nTokenEnd);
    }

    return tokens;
}

} // namespace qx
