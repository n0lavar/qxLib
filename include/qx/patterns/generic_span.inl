/**

    @file      generic_span.inl
    @author    Khrapov
    @date      20.11.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

namespace qx
{
template<class T, class traits_t>
constexpr generic_span<T, traits_t>::iterator::iterator(generator_type generator) noexcept
    : m_Generator(std::move(generator))
{
}

template<class T, class traits_t>
constexpr typename generic_span<T, traits_t>::iterator::reference generic_span<T, traits_t>::iterator::operator*()
    const noexcept
{
    auto generator = m_Generator;
    return *generator();
}

template<class T, class traits_t>
constexpr typename generic_span<T, traits_t>::iterator::pointer generic_span<T, traits_t>::iterator::operator->()
    const noexcept
{
    auto generator = m_Generator;
    return generator();
}

template<class T, class traits_t>
constexpr typename generic_span<T, traits_t>::iterator& generic_span<T, traits_t>::iterator::operator++() noexcept
{
    m_Generator();

    if (operator->() == nullptr)
        m_Generator = nullptr;

    return *this;
}

template<class T, class traits_t>
constexpr typename generic_span<T, traits_t>::iterator generic_span<T, traits_t>::iterator::operator++(int) noexcept
{
    iterator r(*this);

    if (operator->() == nullptr)
        m_Generator = nullptr;

    return r;
}

template<class T, class traits_t>
constexpr bool generic_span<T, traits_t>::iterator::operator!=(const iterator& r) const noexcept
{
    return !operator==(r);
}

template<class T, class traits_t>
constexpr bool generic_span<T, traits_t>::iterator::operator==(const iterator& r) const noexcept
{
    return m_Generator && r.m_Generator || !m_Generator && !r.m_Generator;
}

template<class T, class traits_t>
constexpr generic_span<T, traits_t>::iterator::operator void*() const noexcept
{
    auto generator = m_Generator;
    return generator();
}

template<class T, class traits_t>
template<class container_t>
inline generic_span<T, traits_t>::generic_span(container_t& container) noexcept
    : m_InitialGenerator(
        container.begin() != container.end() 
        ? [it = container.begin(), &container]() mutable
          {
              T* pRet = nullptr;
          
              if (it != container.end())
              {
                  pRet = it.operator->();
                  ++it;
              }
          
              return pRet;
          } 
        : generator_type(nullptr))
{
}

template<class T, class traits_t>
template<class container_t>
inline generic_span<T, traits_t>::generic_span(
    container_t&                                          container,
    function_type<pointer(container_value<container_t>&)> valueAdapter) noexcept
    : m_InitialGenerator(create_initial_generator(container, std::move(valueAdapter)))
{
}

template<class T, class traits_t>
template<class container_t>
inline generic_span<T, traits_t>::generic_span(
    const container_t&                                    container,
    function_type<pointer(container_value<container_t>&)> valueAdapter) noexcept
    : m_InitialGenerator(create_initial_generator(container, std::move(valueAdapter)))
{
}

template<class T, class traits_t>
template<class container_t>
inline generic_span<T, traits_t>& generic_span<T, traits_t>::operator=(container_t& container) noexcept
{
    *this = generic_span(container);
    return *this;
}

template<class T, class traits_t>
inline bool generic_span<T, traits_t>::empty() const noexcept
{
    return !static_cast<bool>(m_InitialGenerator);
}

template<class T, class traits_t>
inline typename generic_span<T, traits_t>::iterator generic_span<T, traits_t>::begin() const noexcept
{
    return iterator(m_InitialGenerator);
}

template<class T, class traits_t>
inline typename generic_span<T, traits_t>::iterator generic_span<T, traits_t>::end() const noexcept
{
    return iterator(nullptr);
}

template<class T, class traits_t>
inline typename generic_span<T, traits_t>::iterator generic_span<T, traits_t>::cbegin() const noexcept
{
    return begin();
}

template<class T, class traits_t>
inline typename generic_span<T, traits_t>::iterator generic_span<T, traits_t>::cend() const noexcept
{
    return end();
}

template<class T, class traits_t>
template<class container_t, class adapter_t>
inline typename generic_span<T, traits_t>::generator_type generic_span<T, traits_t>::create_initial_generator(
    container_t&& container,
    adapter_t     adapter) noexcept
{
    return container.begin() != container.end() 
            ? [it = container.begin(), _adapter = std::move(adapter), &container]() mutable
              {
                  T* pRet = nullptr;
          
                  if (it != container.end())
                  {
                      pRet = _adapter(*it);
                      ++it;
                  }
          
                  return pRet;
              } 
            : generator_type(nullptr);
}

} // namespace qx
