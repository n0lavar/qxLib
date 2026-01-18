/**

    @file      base_standard_streams_stream.inl
    @author    Khrapov
    @date      18.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline base_standard_streams_stream::base_standard_streams_stream(const config& streamConfig)
    : base_logger_stream(streamConfig)
    , m_bUsingColors(streamConfig.bUseColors)
{
}

inline void base_standard_streams_stream::do_log(const category& category, verbosity eVerbosity, string_view svMessage)
{
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

        cout_colorized(
            eVerbosity,
            string_view(svMessage.data(), colorsCount == 0 ? svMessage.size() : colors.front().range.first),
            lineColor);

        for (size_t i = 0; i < colorsCount; ++i)
        {
            cout_colorized(
                eVerbosity,
                string_view(svMessage.data() + colors[i].range.first, colors[i].range.second - colors[i].range.first),
                colors[i].rangeColor);
            cout_colorized(
                eVerbosity,
                string_view(
                    svMessage.data() + colors[i].range.second,
                    (i + 1 < colorsCount ? colors[i + 1].range.first : svMessage.size()) - colors[i].range.second),
                lineColor);
        }
    }
    else
    {
        cout_common(eVerbosity, svMessage);
    }
}

} // namespace qx
