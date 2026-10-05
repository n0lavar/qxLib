/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

namespace details
{

template<sbo_poly_assignable_c<base_logger_stream> stream_t>
static constexpr auto logger_stream_filter = [](const logger::logger_sbo& stream)
{
    return stream->is<stream_t>();
};

} // namespace details

inline logger::logger() noexcept
{
    logger::reset();
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

template<sbo_poly_assignable_c<base_logger_stream> stream_t>
inline stream_t* logger::get_stream() noexcept
{
    auto it = std::ranges::find_if(m_Streams, details::logger_stream_filter<stream_t>);
    return it != m_Streams.end() ? static_cast<stream_t*>(&it->get()) : nullptr;
}

template<sbo_poly_assignable_c<base_logger_stream> stream_t>
inline auto logger::get_streams() noexcept
{
    return m_Streams | std::views::filter(details::logger_stream_filter<stream_t>)
           | std::views::transform(
               [](logger_sbo& stream)
               {
                   return static_cast<stream_t*>(&stream.get());
               });
}

inline std::shared_mutex& logger::get_streams_mutex() noexcept
{
    return m_StreamsMutex;
}

template<sbo_poly_assignable_c<base_logger_stream> stream_t>
inline size_t logger::remove_streams() noexcept
{
    std::unique_lock _(m_StreamsMutex);
    return std::erase_if(m_Streams, details::logger_stream_filter<stream_t>);
}

inline void logger::register_category(const category& category, category_data data) noexcept
{
    register_category(category.get_name(), std::move(data));
}

inline void logger::register_category(string_view svCategoryName, category_data data) noexcept
{
    std::unique_lock _(m_RegisteredCategoriesMutex);
    m_RegisteredCategories.try_emplace(svCategoryName, std::move(data));
}

inline compile_pattern_result logger::set_default_pattern(string sPattern) noexcept
{
    const compile_pattern_result eResult = compile_pattern(sPattern);

    if (eResult == compile_pattern_result::ok)
        m_sDefaultPattern = std::move(sPattern);

    return eResult;
}

inline void logger::log_macro(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    logger_string_pool::item              message)
{
    const flags<message_necessity_type> eMessageNecessity =
        get_message_necessity_type(category, eVerbosity, threadId, messageTime, svFile, svFunction, nLine);

    {
        std::shared_lock _(m_RegisteredCategoriesMutex);
        if (auto itRegisteredCategory = m_RegisteredCategories.find(category.get_name());
            itRegisteredCategory != m_RegisteredCategories.end())
        {
            const category_data& data = itRegisteredCategory->second;
            if (data.FormatUserMessage)
            {
                message = data.FormatUserMessage(std::move(message), m_StringsPool);
            }
        }
    }

    if (eMessageNecessity != message_necessity_type::not_required)
    {
        // assume most streams will not have their own pattern and pre-format with the default pattern
        logger_string_pool::item finalLogMessage = m_StringsPool.acquire();
        format_log_specifiers(
            finalLogMessage.sValue,
            m_sDefaultPattern,
            category,
            eVerbosity,
            threadId,
            messageTime,
            svFile,
            svFunction,
            nLine,
            message.sValue);

        {
            std::shared_lock _(m_StreamsMutex);
            for (auto& stream : m_Streams)
            {
                if (eMessageNecessity != message_necessity_type::one_of_streams_requires
                    || stream->log_unconditionally_required(
                        category,
                        eVerbosity,
                        threadId,
                        messageTime,
                        svFile,
                        svFunction,
                        nLine))
                {
                    std::optional<logger_string_pool::item> optStreamLogMessage;
                    if (const std::optional<string_view> optPattern = stream->get_pattern())
                    {
                        optStreamLogMessage = m_StringsPool.acquire();
                        format_log_specifiers(
                            optStreamLogMessage->sValue,
                            *optPattern,
                            category,
                            eVerbosity,
                            threadId,
                            messageTime,
                            svFile,
                            svFunction,
                            nLine,
                            message.sValue);
                    }

                    stream->log(
                        category,
                        eVerbosity,
                        threadId,
                        messageTime,
                        svFile,
                        svFunction,
                        nLine,
                        optStreamLogMessage ? optStreamLogMessage->sValue : finalLogMessage.sValue);

                    if (optStreamLogMessage)
                        m_StringsPool.release(std::move(*optStreamLogMessage));
                }
            }
        }

        m_StringsPool.release(std::move(finalLogMessage));
    }

    m_StringsPool.release(std::move(message));
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

    {
        std::unique_lock _(m_StreamsMutex);
        m_Streams.clear();
    }

    {
        std::unique_lock _(m_RegisteredCategoriesMutex);
        m_RegisteredCategories.clear();
    }

    /*
        Default pattern for the logger. Some examples:

        >   [08.01.2026_23:51:41] Time? Is it really that time again?
        >   [08.01.2026_23:51:41][CatCore] Time? Is it really that time again?
        >[W][08.01.2026_23:51:41] Time? Is it really that time again?
        >[W][08.01.2026_23:51:41][CatCore] Time? Is it really that time again?
    */
    set_default_pattern(QXT("{verbosity:l}[{time:%d.%m.%Y_%H:%M:%S}]{category:l} {message}\n"));
}

inline flags<logger::message_necessity_type> logger::get_message_necessity_type(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine) const noexcept
{
    flags<message_necessity_type> eMessageNecessity;
    {
        std::shared_lock _(m_StreamsMutex);
        const bool       bSomeStreamRequires = std::ranges::any_of(
            m_Streams,
            [&category, eVerbosity, threadId, messageTime, svFile, svFunction, nLine](const auto& stream)
            {
                return stream->log_unconditionally_required(
                    category,
                    eVerbosity,
                    threadId,
                    messageTime,
                    svFile,
                    svFunction,
                    nLine);
            });
        if (bSomeStreamRequires)
            eMessageNecessity |= message_necessity_type::one_of_streams_requires;
    }

    {
        std::shared_lock _(m_RegisteredCategoriesMutex);
        if (auto itRegisteredCategory = m_RegisteredCategories.find(category.get_name());
            itRegisteredCategory != m_RegisteredCategories.end())
        {
            const category_data& data = itRegisteredCategory->second;
            if (eVerbosity >= data.eRuntimeVerbosity)
                eMessageNecessity |= message_necessity_type::category_verbosity;
        }
    }

    if (eVerbosity >= verbosity::log)
        eMessageNecessity |= message_necessity_type::default_verbosity;

    return eMessageNecessity;
}

inline logger::logger_string_pool* logger::_get_string_pool() noexcept
{
    return &m_StringsPool;
}

} // namespace qx
