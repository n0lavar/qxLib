/**

    @file      type_strings.inl
    @author    Khrapov
    @date      24.09.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

namespace qx
{

template<class T>
constexpr std::string_view type_strings<T>::create_full_signature()
{
#if defined(_MSC_VER)
    return __FUNCSIG__;
#elif defined(__clang__) || defined(__GNUG__)
    return __PRETTY_FUNCTION__;
#endif
}

template<class T>
constexpr size_t type_strings<T>::get_num_template_parameters()
{
    const std::string_view svSignature = create_signature();

    size_t nBraceCounter = 0;
    size_t nParams       = 0;
    bool   bLambda       = false;

    for (size_t i = 0; i < svSignature.size(); ++i)
    {
        switch (svSignature[i])
        {
        case '<':
            if (!bLambda)
            {
                ++nBraceCounter;

                if (svSignature.find(lambdaMarker, i + 1) == i + 1)
                    bLambda = true;
                else if (nParams == 0 && nBraceCounter == 1)
                    ++nParams;
            }
            break;

        case '>':
            --nBraceCounter;

            if (bLambda)
                bLambda = false;

            break;

        case ',':
            if (nBraceCounter == 1)
                ++nParams;

            break;
        }
    }

    return nParams;
}

template<class T>
constexpr std::string_view type_strings<T>::create_signature()
{
    std::string_view svFuncSignature = create_full_signature();

#if defined(_MSC_VER)
    constexpr char startMarker[] = "type_strings<";
    constexpr char endMarker[]   = ">::create_full_signature(";
#elif defined(__clang__)
    constexpr char startMarker[] = "T = ";
    constexpr char endMarker[]   = "]";
#elif defined(__GNUG__)
    constexpr char startMarker[] = "T = ";
    constexpr char endMarker[]   = ";";
#endif

    size_t nStartMarker = svFuncSignature.find(startMarker);
    size_t nStart       = nStartMarker != std::string_view::npos ? (nStartMarker + sizeof(startMarker) - 1) : 0;

    constexpr char classMarker[] = "class ";
    size_t         nClassMarker  = svFuncSignature.find(classMarker, nStart);
    if (nClassMarker != std::string_view::npos)
        nStart = nClassMarker + sizeof(classMarker) - 1;

    size_t nEndMarker = svFuncSignature.find(endMarker, nStart);
    size_t nEnd       = nEndMarker != std::string_view::npos ? nEndMarker : svFuncSignature.size();

    return std::string_view(svFuncSignature.data() + nStart, svFuncSignature.data() + nEnd);
}

template<class T>
constexpr std::string_view type_strings<T>::create_name()
{
    constexpr char         startMarker[] = "<";
    const std::string_view svSignature   = create_signature();
    size_t                 nStartMarker  = svSignature.find(startMarker);

    if (nStartMarker != std::string_view::npos && svSignature.find(lambdaMarker, nStartMarker) == nStartMarker + 1)
        nStartMarker = std::string_view::npos;

    return std::string_view(
        svSignature.data(),
        svSignature.data() + (nStartMarker != std::string_view::npos ? nStartMarker : svSignature.size()));
}

template<class T>
constexpr typename type_strings<T>::TemplateParametersContainer type_strings<T>::create_template_parameters()
{
    TemplateParametersContainer tokens;

    const std::string_view svSignature = create_signature();

    size_t nTokenStart   = 0;
    size_t nBraceCounter = 0;
    size_t nParam        = 0;

    const auto add_token = [&tokens, &svSignature](size_t nToken, size_t nStart, size_t nEnd)
    {
        while (svSignature[nStart] == ' ')
            ++nStart;

        while (svSignature[nEnd] == ' ')
            --nEnd;

        constexpr char classMarker[] = "class ";
        if (std::string_view(svSignature.data() + nStart, svSignature.data() + nEnd).starts_with(classMarker))
            nStart += sizeof(classMarker) - 1;

        tokens[nToken] = std::string_view(svSignature.data() + nStart, svSignature.data() + nEnd + 1);
    };

    bool bLambda = false;

    for (size_t i = 0; i < svSignature.size(); ++i)
    {
        switch (svSignature[i])
        {
        case '<':
            ++nBraceCounter;

            if (nTokenStart == 0)
                nTokenStart = i + 1;
            else if (!bLambda && svSignature.find(lambdaMarker, i + 1) == i + 1)
                bLambda = true;

            break;

        case '>':
            --nBraceCounter;
            if (bLambda)
                bLambda = false;

            break;

        case ',':
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

        if (svSignature[nTokenEnd] == ' ')
            --nTokenEnd;

        if (svSignature[nTokenEnd] == '>')
            --nTokenEnd;

        add_token(nParam, nTokenStart, nTokenEnd);
    }

    return tokens;
}

template<class T>
constexpr std::string_view type_strings<T>::get_signature()
{
    return m_kSignature;
}

template<class T>
constexpr std::string_view type_strings<T>::get_name()
{
    return m_kName;
}

template<class T>
constexpr typename type_strings<T>::TemplateParametersContainer type_strings<T>::get_template_parameters()
{
    return m_kTemplateParameters;
}

} // namespace qx
