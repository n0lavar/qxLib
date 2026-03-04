/**

    @file      file_logger_stream_mapping.inl
    @author    Khrapov
    @date      15.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline file_logger_stream_mapping::file_logger_stream_mapping(
    const config&             streamConfig,
    unit<size_t, units::data> initialMapSize) noexcept
    : base_file_logger_stream(streamConfig)
{
    const std::filesystem::path path = prepare_folder_and_get_log_file_path(streamConfig);

#if QX_WIN
    SYSTEM_INFO si {};
    GetSystemInfo(&si);
    m_nGranularity = si.dwAllocationGranularity ? si.dwAllocationGranularity : 65536;

    m_hFile = CreateFileW(
        path.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        nullptr,
        streamConfig.eLogFilePolicy == log_file_policy::clear_then_uppend ? CREATE_ALWAYS : OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    if (m_hFile == INVALID_HANDLE_VALUE)
        return;

    LARGE_INTEGER sz {};
    if (!GetFileSizeEx(m_hFile, &sz))
        return;

    m_nSize = static_cast<size_t>(sz.QuadPart);
#else
    const long ps  = ::sysconf(_SC_PAGESIZE);
    m_nGranularity = ps > 0 ? static_cast<size_t>(ps) : 4096ull;

    int flags = O_RDWR | O_CREAT;
    if (streamConfig.eLogFilePolicy == log_file_policy::clear_then_uppend)
        flags |= O_TRUNC;

    m_Fd = ::open(path.c_str(), flags, 0644);
    if (m_Fd < 0)
        return;

    struct stat st {};
    if (::fstat(m_Fd, &st) != 0)
        return;

    m_nSize = static_cast<size_t>(st.st_size);
#endif

    const size_t nDefaultStartSize = initialMapSize ? convert(initialMapSize).to(units::data::bytes) : m_nGranularity;
    size_t       nInitialSize      = m_nSize < nDefaultStartSize ? nDefaultStartSize : m_nSize;
    nInitialSize                   = align_up_u64(nInitialSize, m_nGranularity);

    remap_to_capacity(nInitialSize);
}

inline file_logger_stream_mapping::file_logger_stream_mapping(file_logger_stream_mapping&& other) noexcept
    : base_file_logger_stream(std::move(other))
{
#if QX_WIN
    std::swap(m_hFile, other.m_hFile);
    std::swap(m_hMap, other.m_hMap);
#else
    std::swap(m_Fd, other.m_Fd);
#endif
    std::swap(m_pData, other.m_pData);
    std::swap(m_nSize, other.m_nSize);
    std::swap(m_nCapacity, other.m_nCapacity);
    std::swap(m_nGranularity, other.m_nGranularity);
}

inline file_logger_stream_mapping::~file_logger_stream_mapping() noexcept
{
#if QX_WIN
    if (m_hFile == INVALID_HANDLE_VALUE)
        return;
#else
    if (m_Fd < 0)
        return;
#endif

    file_logger_stream_mapping::do_flush();

    if (m_pData)
    {
#if QX_WIN
        UnmapViewOfFile(m_pData);
#else
        ::munmap(m_pData, static_cast<size_t>(m_nCapacity));
#endif
        m_pData = nullptr;
    }

#if QX_WIN
    if (m_hMap)
    {
        CloseHandle(m_hMap);
        m_hMap = nullptr;
    }
#endif

#if QX_WIN
    LARGE_INTEGER li {};
    li.QuadPart = static_cast<LONGLONG>(m_nSize);

    if (!SetFilePointerEx(m_hFile, li, nullptr, FILE_BEGIN))
        return;

    if (!SetEndOfFile(m_hFile))
        return;

    if (!FlushFileBuffers(m_hFile))
        return;

    CloseHandle(m_hFile);
    m_hFile = INVALID_HANDLE_VALUE;
#else
    ::ftruncate(m_Fd, static_cast<off_t>(m_nSize));
    ::fsync(m_Fd);
    ::close(m_Fd);
    m_Fd = -1;
#endif

    m_nCapacity = 0;
    m_nSize     = 0;
}

inline void file_logger_stream_mapping::do_log(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage)
{
    const size_t nRequiredSize = svMessage.size() * std::min(sizeof(char_type), sizeof(char16_t));
    if (!ensure_capacity(nRequiredSize))
        return;

#if QX_WIN || QX_CONF_USE_CHAR
    std::memcpy(m_pData + m_nSize, svMessage.data(), nRequiredSize);
    m_nSize += nRequiredSize;
#else
    std::array<char16_t, 2048> chunk;

    const char_type* pData           = svMessage.data();
    size_t           nCharsRemaining = svMessage.size();

    while (nCharsRemaining > 0)
    {
        size_t nCharsToTake = std::min(nCharsRemaining, chunk.size());
        for (size_t i = 0; i < nCharsToTake; ++i)
        {
            chunk[i] = static_cast<char16_t>(static_cast<char16_t>(pData[i]) & 0xFFFFu);
        }

        std::memcpy(m_pData + m_nSize, chunk.data(), nCharsToTake * sizeof(char16_t));

        m_nSize += nCharsToTake * sizeof(char16_t);
        pData += nCharsToTake;
        nCharsRemaining -= nCharsToTake;
    }
#endif
}

inline void file_logger_stream_mapping::do_flush()
{
    if (!m_pData || m_nSize == 0)
        return;

    // flush memory mapped data to the file
#if QX_WIN
    if (!FlushViewOfFile(m_pData, m_nSize))
        return;
#else
    ::msync(m_pData, static_cast<size_t>(m_nSize), MS_SYNC);
#endif

#if QX_WIN
    if (m_hFile != INVALID_HANDLE_VALUE)
#else
    if (m_Fd >= 0)
#endif
    {
        // update the file on disc
#if QX_WIN
        FlushFileBuffers(m_hFile);
#else
        ::fsync(m_Fd);
#endif

        // notify the OS that file changed (makes editors such as VS Code to reload it)
#if QX_WIN
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);
        SetFileTime(m_hFile, nullptr, nullptr, &ft);
#else
        struct timespec ts[2];
        clock_gettime(CLOCK_REALTIME, &ts[0]);
        ts[1] = ts[0];

        futimens(m_Fd, ts);
#endif
    }
}

inline bool file_logger_stream_mapping::remap_to_capacity(size_t nNewCapacity) noexcept
{
    if (m_pData)
    {
#if QX_WIN
        UnmapViewOfFile(m_pData);
#else
        ::munmap(m_pData, static_cast<size_t>(m_nCapacity));
#endif
        m_pData = nullptr;
    }

#if QX_WIN
    if (m_hMap)
    {
        CloseHandle(m_hMap);
        m_hMap = nullptr;
    }
#endif

#if QX_WIN
    LARGE_INTEGER li {};
    li.QuadPart = static_cast<LONGLONG>(nNewCapacity);
    if (!SetFilePointerEx(m_hFile, li, nullptr, FILE_BEGIN))
        return false;
    if (!SetEndOfFile(m_hFile))
        return false;
#else
    if (::ftruncate(m_Fd, static_cast<off_t>(nNewCapacity)) != 0)
        return false;
#endif

#if QX_WIN
    DWORD hi = static_cast<DWORD>((nNewCapacity >> 32) & 0xFFFFFFFFu);
    DWORD lo = static_cast<DWORD>(nNewCapacity & 0xFFFFFFFFu);

    m_hMap = CreateFileMappingW(m_hFile, nullptr, PAGE_READWRITE, hi, lo, nullptr);
    if (!m_hMap)
        return false;

    void* p = MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, nNewCapacity);
    if (!p)
        return false;
#else
    void* p = ::mmap(nullptr, static_cast<size_t>(nNewCapacity), PROT_READ | PROT_WRITE, MAP_SHARED, m_Fd, 0);
    if (p == MAP_FAILED)
        return false;
#endif

    m_pData     = static_cast<std::byte*>(p);
    m_nCapacity = nNewCapacity;

    return true;
}

inline bool file_logger_stream_mapping::ensure_capacity(size_t nAdditionalBytes) noexcept
{
    if (m_nSize + nAdditionalBytes <= m_nCapacity)
        return true;

    // grow: double until enough (with alignment)
    size_t nRequiredSize = m_nSize + nAdditionalBytes;
    size_t nNewCapacity  = m_nCapacity ? m_nCapacity : m_nGranularity;
    while (nNewCapacity < nRequiredSize)
        nNewCapacity *= 2;

    nNewCapacity = align_up_u64(nNewCapacity, m_nGranularity);
    return remap_to_capacity(nNewCapacity);
}

inline size_t file_logger_stream_mapping::align_up_u64(size_t nValue, size_t nAlignment) noexcept
{
    if (nAlignment == 0)
        return nValue;

    const size_t nResult = nValue % nAlignment;
    return nResult ? (nValue + (nAlignment - nResult)) : nValue;
}

} // namespace qx
