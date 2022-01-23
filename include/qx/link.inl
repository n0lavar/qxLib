/**

    @file      link.inl
    @author    Khrapov
    @date      23.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class T>
T* link<T>::lock_ptr::operator->() const noexcept
{
    return m_pRaw.get();
}

template<class T>
T& link<T>::lock_ptr::operator*() const noexcept
{
    return *m_pRaw;
}

template<class T>
T* link<T>::lock_ptr::get() const noexcept
{
    return m_pRaw.get();
}

template<class T>
link<T>::lock_ptr::operator bool() const noexcept
{
    return m_pRaw != nullptr;
}

template<class T>
template<class U>
bool link<T>::lock_ptr::operator==(const U& other) const noexcept
{
    return get() == other.get();
}

template<class T>
template<class U>
std::strong_ordering link<T>::lock_ptr::operator<=>(
    const U& other) const noexcept
{
    return get() <=> other.get();
}

template<class T>
link<T>::lock_ptr::lock_ptr(std::shared_ptr<T> pShared) noexcept
    : m_pRaw(std::move(pShared))
{
}

template<class T>
template<class U>
link<T>::link(const std::weak_ptr<U>& pWeak) noexcept : m_pWeak(pWeak)
{
}

template<class T>
link<T>::link(std::weak_ptr<T> pWeak) noexcept : m_pWeak(std::move(pWeak))
{
}

template<class T>
template<class U>
link<T>::link(const std::shared_ptr<U>& pStrong) noexcept : m_pWeak(pStrong)
{
}

template<class T>
template<class U>
link<T>::link(const link<U>& pLink) noexcept : m_pWeak(pLink.m_pWeak)
{
}

template<class T>
template<class U>
link<T>& link<T>::operator=(const link<U>& pLink) noexcept
{
    m_pWeak = pLink.m_pWeak;
    return *this;
}

template<class T>
template<class U>
link<T>::link(link<U>&& pLink) noexcept : m_pWeak(std::move(pLink.m_pWeak))
{
}

template<class T>
template<class U>
link<T>& link<T>::operator=(link<U>&& pLink) noexcept
{
    m_pWeak = std::move(pLink.m_pWeak);
    return *this;
}

template<class T>
link<T>::link(std::nullptr_t) noexcept
{
}

template<class T>
typename link<T>::lock_ptr link<T>::lock() const noexcept
{
    return lock_ptr(std::move(m_pWeak.lock()));
}

template<class T>
void link<T>::reset() noexcept
{
    m_pWeak.reset();
}

template<class T>
inline bool link<T>::expired() const noexcept
{
    return m_pWeak.expired();
}

template<class T>
link<T>::operator bool() const noexcept
{
    return !m_pWeak.expired();
}

} // namespace qx
