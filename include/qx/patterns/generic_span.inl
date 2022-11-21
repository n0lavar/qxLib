/**

    @file      generic_span.inl
    @author    Khrapov
    @date      20.11.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

namespace qx
{
template<class T, class Traits>
constexpr generic_span<T, Traits>::iterator::iterator(generator_type generator) noexcept
    : m_Generator(std::move(generator))
{
}

template<class T, class Traits>
constexpr typename generic_span<T, Traits>::iterator::reference generic_span<T, Traits>::iterator::operator*()
    const noexcept
{
    auto generator = m_Generator;
    return *generator();
}

template<class T, class Traits>
constexpr typename generic_span<T, Traits>::iterator::pointer generic_span<T, Traits>::iterator::operator->()
    const noexcept
{
    auto generator = m_Generator;
    return generator();
}

template<class T, class Traits>
constexpr typename generic_span<T, Traits>::iterator& generic_span<T, Traits>::iterator::operator++() noexcept
{
    m_Generator();

    if (operator->() == nullptr)
        m_Generator = nullptr;

    return *this;
}

template<class T, class Traits>
constexpr typename generic_span<T, Traits>::iterator generic_span<T, Traits>::iterator::operator++(int) noexcept
{
    iterator r(*this);

    if (operator->() == nullptr)
        m_Generator = nullptr;

    return r;
}

template<class T, class Traits>
constexpr bool generic_span<T, Traits>::iterator::operator!=(const iterator& r) const noexcept
{
    return !operator==(r);
}

template<class T, class Traits>
constexpr bool generic_span<T, Traits>::iterator::operator==(const iterator& r) const noexcept
{
    return m_Generator && r.m_Generator || !m_Generator && !r.m_Generator;
}

template<class T, class Traits>
constexpr generic_span<T, Traits>::iterator::operator void*() noexcept
{
    auto generator = m_Generator;
    return generator();
}

template<class T, class Traits>
template<class Container>
inline generic_span<T, Traits>::generic_span(Container& container) noexcept
    : m_InitialGenerator(
        [it = container.begin(), &container]() mutable
        {
            T* pRet = nullptr;

            if (it != container.end())
            {
                pRet = it.operator->();
                ++it;
            }

            return pRet;
        })
{
}

template<class T, class Traits>
template<class Container>
inline generic_span<T, Traits>::generic_span(
    Container&                                                        container,
    function_type<T*(typename Container::value_type& containerValue)> valueAdapter) noexcept
    : m_InitialGenerator(
        [it = container.begin(), end = container.end(), _adapter = std::move(valueAdapter)]() mutable
        {
            T* pRet = nullptr;

            if (it != end)
            {
                pRet = _adapter(*it);
                ++it;
            }

            return pRet;
        })
{
}

template<class T, class Traits>
inline typename generic_span<T, Traits>::iterator generic_span<T, Traits>::begin() const noexcept
{
    return iterator(m_InitialGenerator);
}

template<class T, class Traits>
inline typename generic_span<T, Traits>::iterator generic_span<T, Traits>::end() const noexcept
{
    return iterator(nullptr);
}

template<class T, class Traits>
inline typename generic_span<T, Traits>::iterator generic_span<T, Traits>::cbegin() const noexcept
{
    return begin();
}

template<class T, class Traits>
inline typename generic_span<T, Traits>::iterator generic_span<T, Traits>::cend() const noexcept
{
    return end();
}

} // namespace qx
