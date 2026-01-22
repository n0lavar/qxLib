/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline logger::logger()
{
    add_stream(fwrite_logger_stream());
}

inline logger::~logger() noexcept
{
    logger::flush();
}

template<sbo_poly_assignable_c<base_logger_stream> stream_t>
inline void logger::add_stream(stream_t stream) noexcept
{
    std::unique_lock _(m_StreamsMutex);
    m_Streams.emplace_back(std::move(stream));
}

inline void logger::register_category(const category& category, category_data data) noexcept
{
    register_category(category.get_name(), std::move(data));
}

inline void logger::register_category(string_view svCategoryName, category_data data) noexcept
{
    std::unique_lock _(m_RegisteredCategoriesMutex);
    m_RegisteredCategories.emplace(svCategoryName, std::move(data));
}

inline void logger::log(
    const category&          category,
    verbosity                eVerbosity,
    string_view              svFile,
    string_view              svFunction,
    int                      nLine,
    logger_string_pool::item message)
{
    string sMessage   = std::move(message.sValue);
    bool   bFormatted = false;
    {
        std::shared_lock _(m_RegisteredCategoriesMutex);
        if (auto itRegisteredCategory = m_RegisteredCategories.find(category.get_name());
            itRegisteredCategory != m_RegisteredCategories.end())
        {
            const category_data& data = itRegisteredCategory->second;
            sMessage   = data.formatFunction(category, eVerbosity, svFile, svFunction, nLine, std::move(sMessage));
            bFormatted = true;
        }
    }

    if (!bFormatted)
        sMessage = default_formatter(category, eVerbosity, svFile, svFunction, nLine, std::move(sMessage));

    {
        std::shared_lock _(m_StreamsMutex);
        for (auto& stream : m_Streams)
            stream->log(category, eVerbosity, sMessage);
    }

    m_StringsPool.release(std::move(sMessage), message.nIndex);
}

inline void logger::flush()
{
    std::shared_lock _(m_StreamsMutex);
    for (auto& stream : m_Streams)
        stream->flush();
}

inline void logger::reset() noexcept
{
    flush();

    std::unique_lock _(m_StreamsMutex);
    m_Streams.clear();
}

inline bool logger::log_required(const category& category, verbosity eVerbosity) const noexcept
{
    std::shared_lock _(m_RegisteredCategoriesMutex);

    if (auto itRegisteredCategory = m_RegisteredCategories.find(category.get_name());
        itRegisteredCategory != m_RegisteredCategories.end())
    {
        const category_data& data = itRegisteredCategory->second;
        return eVerbosity >= data.eRuntimeVerbosity;
    }

    // compile time check is in macros
    return true;
}

inline logger::logger_string_pool* logger::_get_string_pool() noexcept
{
    return &m_StringsPool;
}

inline string logger::default_formatter(
    const category& category,
    verbosity       eVerbosity,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    string          sMessage) noexcept
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

    append_time_string(sMessage.data() + nPos, QXT('.'), QXT(':'));
    nPos += nTimeSize;

    std::memcpy(sMessage.data() + nPos, QXT("]"), 1 * sizeof(string::value_type));
    nPos += 1;

    if (bAddCategory)
    {
        std::memcpy(sMessage.data() + nPos, QXT("["), 1 * sizeof(string::value_type));
        nPos += 1;

        std::memcpy(sMessage.data() + nPos, svCategory.data(), svCategory.size() * sizeof(string::value_type));
        nPos += svCategory.size();

        std::memcpy(sMessage.data() + nPos, QXT("]"), 1 * sizeof(string::value_type));
        nPos += 1;
    }

    std::memcpy(sMessage.data() + nPos, QXT(" "), 1 * sizeof(string::value_type));
    nPos += 1;

    sMessage += QXT('\n');

    return sMessage;
}

constexpr string_view logger::get_verbosity_prefix(verbosity eVerbosity) noexcept
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

} // namespace qx
