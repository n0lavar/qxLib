/**

    @file      generic_span.inl
    @author    Khrapov
    @date      20.11.2022
    @copyright � Nick Khrapov, 2022. All right reserved.

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

template<class T, class Traits>
template<class Container>
inline generic_span<T, Traits>::generic_span(
    Container&                                          container,
    function_type<pointer(container_value<Container>&)> valueAdapter) noexcept
    : m_InitialGenerator(create_initial_generator(container, std::move(valueAdapter)))
{
}

template<class T, class Traits>
template<class Container>
inline generic_span<T, Traits>::generic_span(
    const Container&                                    container,
    function_type<pointer(container_value<Container>&)> valueAdapter) noexcept
    : m_InitialGenerator(create_initial_generator(container, std::move(valueAdapter)))
{
}

template<class T, class Traits>
template<class Container>
inline generic_span<T, Traits>& generic_span<T, Traits>::operator=(Container& container) noexcept
{
    *this = generic_span(container);
    return *this;
}

template<class T, class Traits>
inline bool generic_span<T, Traits>::empty() const noexcept
{
    return !static_cast<bool>(m_InitialGenerator);
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

template<class T, class Traits>
template<class Container, class Adapter>
inline typename generic_span<T, Traits>::generator_type generic_span<T, Traits>::create_initial_generator(
    Container&& container,
    Adapter     adapter) noexcept
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