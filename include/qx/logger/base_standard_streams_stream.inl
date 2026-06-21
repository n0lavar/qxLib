/**

    @file      base_standard_streams_stream.inl
    @author    Khrapov
    @date      18.01.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline base_standard_streams_stream::base_standard_streams_stream(const config& streamConfig) noexcept
    : base_logger_stream(streamConfig)
    , m_bUsingColors(streamConfig.bUseColors)
    , m_bSyncUsualAndErrorMessages(streamConfig.bSyncUsualAndErrorMessages)
{
}

inline void base_standard_streams_stream::do_log(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage)
{
    if (m_bUsingColors)
    {
        color lineColor = color::white();
        switch (eVerbosity)
        {
        case verbosity::detailed:
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
            string_view svPart;
            color       partColor = color::white();
        };

        std::array<logger_color_range, 16> colors;
        size_t                             nColorsCount = 0;

        if (const size_t nPos = svMessage.find(category.get_name()); nPos != string::npos)
        {
            colors[0] = { .svPart = { svMessage.begin(), svMessage.begin() + nPos }, .partColor = lineColor };
            ++nColorsCount;

            colors[1] = { .svPart = { svMessage.begin() + nPos, svMessage.begin() + nPos + category.get_name().size() },
                          .partColor = category.get_color() };
            ++nColorsCount;

            // exclude \n
            colors[2] = { .svPart    = { svMessage.begin() + nPos + category.get_name().size(),
                                         svMessage.begin() + svMessage.size() - 1 },
                          .partColor = lineColor };
            ++nColorsCount;
        }
        else
        {
            // exclude \n
            colors[0] = { .svPart    = { svMessage.begin(), svMessage.begin() + svMessage.size() - 1 },
                          .partColor = lineColor };
            ++nColorsCount;
        }

        for (size_t i = 0; i < nColorsCount; ++i)
        {
            cout_colorized(eVerbosity, colors[i].svPart, colors[i].partColor);
        }

        // cout \n
        cout_common(eVerbosity, { &svMessage.back(), 1 });
    }
    else
    {
        cout_common(eVerbosity, svMessage);
    }
}

inline void base_standard_streams_stream::check_previous_message(verbosity eCurrentMessageVerbosity)
{
    if (m_bSyncUsualAndErrorMessages)
    {
        const bool bCurrentMessageIsError = is_error(eCurrentMessageVerbosity);

        if (bCurrentMessageIsError != m_bPrevMessageWasError)
            flush();

        m_bPrevMessageWasError = bCurrentMessageIsError;
    }
}

} // namespace qx
