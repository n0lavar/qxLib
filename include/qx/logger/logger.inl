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
    m_RegisteredCategories.emplace(svCategoryName, std::move(data));
}

inline void logger::set_default_formatter(format_function_pointer pFormatter) noexcept
{
    m_DefaultFormatFunction = pFormatter;
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
    string sMessage = std::move(message.sValue);

    const flags<message_necessity_type> eMessageNecessity =
        get_message_necessity_type(category, eVerbosity, threadId, messageTime, svFile, svFunction, nLine);
    if (eMessageNecessity != message_necessity_type::not_required)
    {
        bool bFormatted = false;
        {
            std::shared_lock _(m_RegisteredCategoriesMutex);
            if (auto itRegisteredCategory = m_RegisteredCategories.find(category.get_name());
                itRegisteredCategory != m_RegisteredCategories.end())
            {
                const category_data& data = itRegisteredCategory->second;
                if (data.formatFunction)
                {
                    sMessage = data.formatFunction(
                        category,
                        eVerbosity,
                        threadId,
                        messageTime,
                        svFile,
                        svFunction,
                        nLine,
                        std::move(sMessage));

                    bFormatted = true;
                }
            }
        }

        if (!bFormatted)
        {
            sMessage = m_DefaultFormatFunction.load()(
                category,
                eVerbosity,
                threadId,
                messageTime,
                svFile,
                svFunction,
                nLine,
                std::move(sMessage));
        }

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
                    stream->log(category, eVerbosity, threadId, messageTime, svFile, svFunction, nLine, sMessage);
                }
            }
        }
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

    {
        std::unique_lock _(m_StreamsMutex);
        m_Streams.clear();
    }

    {
        std::unique_lock _(m_RegisteredCategoriesMutex);
        m_RegisteredCategories.clear();
    }

    m_DefaultFormatFunction = format_message_qx;
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
