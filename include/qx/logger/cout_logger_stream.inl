/**

    @file      cout_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline cout_logger_stream::cout_logger_stream(
    bool bAlwaysFlush,
    bool bUseColors,
    bool bDisableStdioSync,
    bool bUntieCin)
    : base_logger_stream(bAlwaysFlush)
    , m_bUsingColors(bUseColors)
{
    if (bDisableStdioSync)
    {
        // Optimization
        // Don't synchronize to the standard C streams after each input/output operation
        std::ios_base::sync_with_stdio(false);
    }

    if (bUntieCin)
    {
        // This unties cin from cout.
        // Tied streams ensure that one stream is flushed automatically
        // before each I/O operation on the other stream
        std::cin.tie(nullptr);
        std::wcin.tie(nullptr);
        std::cout.tie(nullptr);
        std::wcout.tie(nullptr);
    }
}

inline void cout_logger_stream::flush()
{
    QX_PERF_SCOPE(CatLogger, "Flush to cout");

    std::cout << std::flush;
    std::wcout << std::flush;
}

inline void cout_logger_stream::do_log(
    std::string_view                       svMessage,
    const log_unit&                        logUnit,
    const std::vector<logger_color_range>& colors,
    log_level                              eLogLevel)
{
    log_cout(svMessage, logUnit, colors, eLogLevel);
}

inline void cout_logger_stream::do_log(
    std::wstring_view                      svMessage,
    const log_unit&                        logUnit,
    const std::vector<logger_color_range>& colors,
    log_level                              eLogLevel)
{
    log_cout(svMessage, logUnit, colors, eLogLevel);
}

inline void cout_logger_stream::set_using_colors(bool bUsingColors) noexcept
{
    m_bUsingColors = bUsingColors;
}

template<class char_type>
inline std::basic_ostream<char_type>& cout_logger_stream::get_cout() noexcept
{
    if constexpr (std::is_same_v<char_type, char>)
        return std::cout;
    else
        return std::wcout;
}

template<class char_type>
inline void cout_logger_stream::log_cout(
    std::basic_string_view<char_type>      svMessage,
    const log_unit&                        logUnit,
    const std::vector<logger_color_range>& colors,
    log_level                              eLogLevel)
{
    QX_PERF_SCOPE(CatLogger, "Log to cout");

    auto& cout = get_cout<char_type>();

    if (m_bUsingColors)
    {
        color commonColor = color::white();
        switch (eLogLevel)
        {
        case log_level::very_verbose:
        case log_level::verbose:
            commonColor = color::gray();
            break;

        case log_level::log:
            commonColor = color::white();
            break;

        case log_level::important:
            commonColor = color::khaki();
            break;

        case log_level::warning:
            commonColor = color::orange();
            break;

        case log_level::error:
            commonColor = color::crimson();
            break;

        case log_level::critical:
            commonColor = color::dark_red();
            break;
        }

        auto cout_colorized = [&cout, svMessage](size_t nStart, size_t nEnd, const color& rangeColor)
        {
            cout << terminal_color::font(rangeColor)
                 << std::basic_string_view<char_type> { svMessage.data() + nStart, nEnd - nStart }
                 << terminal_color::reset();
        };

        cout_colorized(0, colors.empty() ? svMessage.size() : colors.front().range.first, commonColor);

        for (size_t i = 0; i < colors.size(); ++i)
        {
            cout_colorized(colors[i].range.first, colors[i].range.second, colors[i].rangeColor);
            cout_colorized(
                colors[i].range.second,
                i + 1 < colors.size() ? colors[i + 1].range.first : svMessage.size(),
                commonColor);
        }
    }
    else
    {
        cout << svMessage;
    }
}

} // namespace qx
