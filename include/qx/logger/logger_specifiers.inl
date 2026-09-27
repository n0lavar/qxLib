/**

    @file      logger_specifiers.inl
    @author    Khrapov
    @date      9.09.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

namespace details
{

constexpr std::optional<logger_specifiers> get_log_specifier(string_view svName) noexcept
{
    if (svName == QXT("category"))
        return logger_specifiers::category;

    if (svName == QXT("verbosity"))
        return logger_specifiers::verbosity;

    if (svName == QXT("thread_id"))
        return logger_specifiers::thread_id;

    if (svName == QXT("time"))
        return logger_specifiers::time;

    if (svName == QXT("file"))
        return logger_specifiers::file;

    if (svName == QXT("function"))
        return logger_specifiers::function;

    if (svName == QXT("line"))
        return logger_specifiers::line;

    if (svName == QXT("message"))
        return logger_specifiers::message;

    return std::nullopt;
}

} // namespace details

inline compile_pattern_result compile_pattern(string& sPattern) noexcept
{
    char_type* const pData = sPattern.data();
    const size_t     nSize = sPattern.size();

    size_t nRead  = 0;
    size_t nWrite = 0;
    size_t nDepth = 0;

    while (nRead < nSize)
    {
        const char_type ch = pData[nRead];

        if (ch == QXT('{'))
        {
            // Escaped opening brace.
            //
            // "{{tid}}" must remain "{{tid}}" and must not become "{{0}}".
            if (nDepth == 0 && nRead + 1 < nSize && pData[nRead + 1] == QXT('{'))
            {
                pData[nWrite++] = QXT('{');
                pData[nWrite++] = QXT('{');

                nRead += 2;
                continue;
            }

            pData[nWrite++] = QXT('{');
            ++nRead;
            ++nDepth;

            const size_t nNameBegin = nRead;

            // Parse only arg-id:
            //
            // {time}
            //  ^^^^
            //
            // {time:%H:%M:%S}
            //  ^^^^
            while (nRead < nSize && pData[nRead] != QXT(':') && pData[nRead] != QXT('}') && pData[nRead] != QXT('{'))
            {
                ++nRead;
            }

            if (nRead == nSize)
                return compile_pattern_result::unclosed_field;

            // '{' cannot occur inside arg-id.
            if (pData[nRead] == QXT('{'))
                return compile_pattern_result::invalid_field;

            const string_view svName { pData + nNameBegin, nRead - nNameBegin };

            if (const auto eSpecifier = details::get_log_specifier(svName))
            {
                const auto nSpecifier = static_cast<size_t>(*eSpecifier);

                pData[nWrite++] = static_cast<char_type>(QXT('0') + nSpecifier);
            }
            else
            {
                // Keep standard positional arguments intact:
                //
                // {}
                // {0}
                // {123}
                bool bNumeric = svName.empty();

                if (!svName.empty())
                {
                    bNumeric = true;

                    for (const char_type chName : svName)
                    {
                        if (chName < QXT('0') || chName > QXT('9'))
                        {
                            bNumeric = false;
                            break;
                        }
                    }
                }

                if (!bNumeric)
                    return compile_pattern_result::unknown_specifier;

                for (const char_type chName : svName)
                    pData[nWrite++] = chName;
            }

            // ':' or '}' is intentionally not consumed.
            continue;
        }

        if (ch == QXT('}'))
        {
            if (nDepth != 0)
            {
                // Close current replacement field.
                pData[nWrite++] = ch;
                ++nRead;
                --nDepth;
                continue;
            }

            // Escaped closing brace.
            if (nRead + 1 < nSize && pData[nRead + 1] == QXT('}'))
            {
                pData[nWrite++] = QXT('}');
                pData[nWrite++] = QXT('}');

                nRead += 2;
                continue;
            }

            return compile_pattern_result::unmatched_closing_brace;
        }

        pData[nWrite++] = ch;
        ++nRead;
    }

    if (nDepth != 0)
        return compile_pattern_result::unclosed_field;

    sPattern.resize(nWrite);

    return compile_pattern_result::ok;
}

inline void format_log_specifiers(
    string&                               sStorage,
    string_view                           svPattern,
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage)
{
    // must be kept in line with logger_specifiers indices
    sStorage.vformat(
        svPattern,
        category,
        eVerbosity,
        0,
        std::chrono::floor<std::chrono::seconds>(messageTime),
        svFile,
        svFunction,
        nLine,
        svMessage);
}

} // namespace qx
