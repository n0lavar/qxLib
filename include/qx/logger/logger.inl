/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void logger::log(
    const category& category,
    verbosity       eVerbosity,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    string          sMessage)
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

    for (auto& stream : m_Streams)
        stream->log(category, eVerbosity, sMessage);
}

inline void logger::flush()
{
    for (auto& stream : m_Streams)
        stream->flush();
}

template<sbo_poly_assignable_c<base_logger_stream> stream_t>
inline void logger::add_stream(stream_t stream) noexcept
{
    m_Streams.emplace_back(std::move(stream));
}

inline void logger::reset() noexcept
{
    m_Streams.clear();
}

inline bool logger::will_any_stream_accept(
    const category& category,
    verbosity       eVerbosity,
    string_view     svFile,
    cstring_view    svFunction) const noexcept
{
#if 0
    string sFunction = to_string(svFunction);
    for (const auto& stream : m_Streams)
        if (stream->get_unit_info(category, eVerbosity, svFile, sFunction))
            return true;

    return false;
#endif
    return true;
}

} // namespace qx
