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
    constexpr size_t nVerbositySize = 4;
    constexpr size_t nTimeSize      = 19;

    const string_view svCategory    = category.get_name();
    const size_t      nCategorySize = !svCategory.empty() ? svCategory.size() + 2 : 0;

    constexpr auto get_num_digits = [](int nValue)
    {
        int nDigits = 0;
        int x       = qx::abs(nValue);

        do
        {
            nDigits++;
            x /= 10;
        } while (x != 0);

        return nDigits;
    };

    const size_t nLocationSize = svFile.size() + 2 + svFunction.size() + 2 + get_num_digits(nLine) + 2;
    const size_t nPrefixSize   = nVerbositySize + nTimeSize + 2 + nCategorySize + nLocationSize;

    sMessage.insert(0, QXT("\0"), nPrefixSize);
    size_t nPos = 0;

    const char_type* pszVerbosity = nullptr;
    switch (eVerbosity)
    {
    case verbosity::very_verbose:
        pszVerbosity = QXT("[W][");
        break;

    case verbosity::verbose:
        pszVerbosity = QXT("[V][");
        break;

    case verbosity::important:
        pszVerbosity = QXT("[I][");
        break;

    case verbosity::warning:
        pszVerbosity = QXT("[W][");
        break;

    case verbosity::error:
        pszVerbosity = QXT("[E][");
        break;

    case verbosity::critical:
        pszVerbosity = QXT("[C][");
        break;

    default:
        pszVerbosity = QXT("   [");
        break;
    }
    if (pszVerbosity)
    {
        std::memcpy(sMessage.data() + nPos, pszVerbosity, nVerbositySize * sizeof(string::value_type));
        nPos += nVerbositySize;
    }

    append_time_string(sMessage.data() + nPos, QXT('.'), QXT(':'));
    nPos += nTimeSize;

    std::memcpy(sMessage.data() + nPos, QXT("]["), 2 * sizeof(string::value_type));
    nPos += 2;

    if (!svCategory.empty())
    {
        std::memcpy(sMessage.data() + nPos, svCategory.data(), svCategory.size() * sizeof(string::value_type));
        nPos += svCategory.size();

        std::memcpy(sMessage.data() + nPos, QXT("]["), 2 * sizeof(string::value_type));
        nPos += 2;
    }

    string_traits::format_traits<char_type, string_traits::usings_traits<char_type>>::format_to(
        sMessage.data() + nPos,
        QXT("{}::{}::{}] "),
        svFile,
        svFunction,
        nLine);

    sMessage += QXT('\n');

    return sMessage;
}

} // namespace qx
