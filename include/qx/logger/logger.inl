//==============================================================================
//
//!\file                          logger.inl
//
//!\brief       Console tracing and creating of logs
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================

namespace qx
{

//================================================================================
//!\fn                            qx::logger::output
//
//!\brief  Process tracings
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  svTag                - tracing tag
//!\param  svFile               - file name string
//!\param  svFunction           - function name string
//!\param  nLine                - code line number
//!\param  ...                  - additional args for format
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::output(
    log_level           eLogLevel,
    const char        * pszFormat,
    const char        * pszAssertExpression,
    std::string_view    svTag,
    std::string_view    svFile,
    std::string_view    svFunction,
    int                 nLine,
    ...)
{
    va_list args;
    va_start(args, nLine);

    for (auto& stream : *this)
    {
        stream.output(
            eLogLevel,
            pszFormat,
            pszAssertExpression,
            svTag,
            svFile,
            svFunction,
            nLine,
            args);
    }

    va_end(args);
}

}
