/**

    @file      cout_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline cout_logger_stream::cout_logger_stream(cout_logger_config config)
    : base_logger_stream(config.bAlwaysFlush)
    , m_bUsingColors(config.bUseColors)
{
    if (config.bDisableStdioSync)
    {
        // Optimization
        // Don't synchronize to the standard C streams after each input/output operation
        std::ios_base::sync_with_stdio(false);
    }

    if (config.bUntieCin)
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

inline void cout_logger_stream::do_log(const category& category, verbosity eVerbosity, string_view svMessage)
{
    QX_PERF_SCOPE(CatLogger, "Log to cout");

    // allocation
    wstring sWideMessage = to_wstring(svMessage);

    std::wostream& outputStream = eVerbosity < verbosity::error ? std::wcout : std::wcerr;

    if (m_bUsingColors)
    {
        color lineColor = color::white();
        switch (eVerbosity)
        {
        case verbosity::very_verbose:
        case verbosity::verbose:
            lineColor = color::gray();
            break;

        case verbosity::log:
            lineColor = color::white();
            break;

        case verbosity::important:
            lineColor = color::khaki();
            break;

        case verbosity::warning:
            lineColor = color::orange();
            break;

        case verbosity::error:
            lineColor = color::crimson();
            break;

        case verbosity::critical:
            lineColor = color::dark_red();
            break;
        }

        auto cout_colorized = [&outputStream, &sWideMessage](size_t nStart, size_t nEnd, const color& rangeColor)
        {
            outputStream << terminal_color::font(rangeColor)
                         << qx::wstring_view { sWideMessage.data() + nStart, nEnd - nStart } << terminal_color::reset();
        };

        struct logger_color_range
        {
            std::pair<size_t, size_t> range { 0, 0 };
            color                     rangeColor = color::white();
        };

        // currently only one color range (category name) is supported
        // loop is left, so it can be extended later if needed
        std::array<logger_color_range, 1> colors;
        size_t                            colorsCount = 0;

        if (auto nPos = svMessage.find(category.get_name()); nPos != string::npos)
        {
            colors[0]   = { .range = { nPos, nPos + category.get_name().size() }, .rangeColor = category.get_color() };
            colorsCount = 1;
        }

        cout_colorized(0, colorsCount == 0 ? sWideMessage.size() : colors.front().range.first, lineColor);

        for (size_t i = 0; i < colorsCount; ++i)
        {
            cout_colorized(colors[i].range.first, colors[i].range.second, colors[i].rangeColor);
            cout_colorized(
                colors[i].range.second,
                i + 1 < colorsCount ? colors[i + 1].range.first : sWideMessage.size(),
                lineColor);
        }
    }
    else
    {
        outputStream << sWideMessage;
    }
}

inline void cout_logger_stream::set_using_colors(bool bUsingColors) noexcept
{
    m_bUsingColors = bUsingColors;
}

} // namespace qx
