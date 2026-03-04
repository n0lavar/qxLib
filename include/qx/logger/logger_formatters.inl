/**

    @file      logger_formatters.inl
    @author    Khrapov
    @date      13.02.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

template<class out_it_t>
inline void append_time_string(
    out_it_t                              it,
    char_type                             chDateDelimiter,
    char_type                             chTimeDelimiter,
    std::chrono::system_clock::time_point time) noexcept
{
    auto timeSeconds = floor<std::chrono::seconds>(time);

    std::format_to(
        it,
        QXT("{:%d}{}{:%m}{}{:%Y}_{:%H}{}{:%M}{}{:%S}"),
        timeSeconds,
        chDateDelimiter,
        timeSeconds,
        chDateDelimiter,
        timeSeconds,
        timeSeconds,
        chTimeDelimiter,
        timeSeconds,
        chTimeDelimiter,
        timeSeconds);
}

constexpr string_view get_verbosity_prefix(verbosity eVerbosity) noexcept
{
    switch (eVerbosity)
    {
    case verbosity::detailed:
        return QXT("[D][");

    case verbosity::verbose:
        return QXT("[V][");

    case verbosity::important:
        return QXT("[I][");

    case verbosity::warning:
        return QXT("[W][");

    case verbosity::error:
        return QXT("[E][");

    case verbosity::critical:
        return QXT("[C][");

    default:
        return QXT("   [");
    }
}

inline string format_message_qx(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string                                sMessage) noexcept
{
    // avoid extra allocation, insert prefix inplace

    const string_view svVerbosityPrefix = get_verbosity_prefix(eVerbosity);
    const string_view svCategory        = category.get_name();
    const bool        bAddCategory      = !svCategory.empty() && svCategory != CatDefault.get_name();

    constexpr size_t nTimeSize     = 19;
    const size_t     nCategorySize = bAddCategory ? svCategory.size() + 2 : 0;
    const size_t     nPrefixSize   = svVerbosityPrefix.size() + nTimeSize + 2 + nCategorySize;

    sMessage.insert(0, QXT("\0"), nPrefixSize);
    size_t nPos = 0;

    std::memcpy(
        sMessage.data() + nPos,
        svVerbosityPrefix.data(),
        svVerbosityPrefix.size() * sizeof(string_view::value_type));
    nPos += svVerbosityPrefix.size();

    append_time_string(sMessage.data() + nPos, QXT('.'), QXT(':'), messageTime);
    nPos += nTimeSize;

    sMessage[nPos] = QXT(']');
    nPos += 1;

    if (bAddCategory)
    {
        sMessage[nPos] = QXT('[');
        nPos += 1;

        std::memcpy(sMessage.data() + nPos, svCategory.data(), svCategory.size() * sizeof(string::value_type));
        nPos += svCategory.size();

        sMessage[nPos] = QXT(']');
        nPos += 1;
    }

    sMessage[nPos] = QXT(' ');
    nPos += 1;

    sMessage += QXT('\n');

    return sMessage;
}


} // namespace qx
