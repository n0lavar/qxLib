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
        std::wcin.tie(nullptr);
        std::wcout.tie(nullptr);
    }
}

inline void cout_logger_stream::flush()
{
    QX_PERF_SCOPE(CatLogger, "Flush to cout");

    std::wcout << std::flush;
}

inline void cout_logger_stream::do_log(
    string_view                            svMessage,
    const log_unit&                        logUnit,
    const std::vector<logger_color_range>& colors,
    verbosity                              eVerbosity)
{
    QX_PERF_SCOPE(CatLogger, "Log to cout");

    wstring sWideMessage = to_wstring(svMessage);

    if (m_bUsingColors)
    {
        color commonColor = color::white();
        switch (eVerbosity)
        {
        case verbosity::very_verbose:
        case verbosity::verbose:
            commonColor = color::gray();
            break;

        case verbosity::log:
            commonColor = color::white();
            break;

        case verbosity::important:
            commonColor = color::khaki();
            break;

        case verbosity::warning:
            commonColor = color::orange();
            break;

        case verbosity::error:
            commonColor = color::crimson();
            break;

        case verbosity::critical:
            commonColor = color::dark_red();
            break;
        }

        auto cout_colorized = [&sWideMessage](size_t nStart, size_t nEnd, const color& rangeColor)
        {
            std::wcout << terminal_color::font(rangeColor)
                       << qx::wstring_view { sWideMessage.data() + nStart, nEnd - nStart } << terminal_color::reset();
        };

        cout_colorized(0, colors.empty() ? sWideMessage.size() : colors.front().range.first, commonColor);

        for (size_t i = 0; i < colors.size(); ++i)
        {
            cout_colorized(colors[i].range.first, colors[i].range.second, colors[i].rangeColor);
            cout_colorized(
                colors[i].range.second,
                i + 1 < colors.size() ? colors[i + 1].range.first : sWideMessage.size(),
                commonColor);
        }
    }
    else
    {
        std::wcout << sWideMessage;
    }
}

inline void cout_logger_stream::set_using_colors(bool bUsingColors) noexcept
{
    m_bUsingColors = bUsingColors;
}

} // namespace qx
