/**

    @file      utils.inl
    @author    Khrapov
    @date      1.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class iterator_t>
inline void destruct(iterator_t itStart, iterator_t itEnd)
{
    using T = typename iterator_t::value_type;
    if constexpr (std::is_compound_v<T>)
    {
        for (auto it = itStart; it != itEnd; ++it)
            it->~T();
    }
}

template<size_t N, class T>
constexpr auto make_array(T init_val)
{
    std::array<T, N> ret;
    ret.fill(init_val);
    return ret;
}

template<class T, std::size_t LeftLength, std::size_t RightLength>
constexpr std::array<T, LeftLength + RightLength> join_arrays(
    std::array<T, LeftLength>  rhs,
    std::array<T, RightLength> lhs)
{
    std::array<T, LeftLength + RightLength> res;
    auto                                    current = std::copy(rhs.begin(), rhs.end(), res.begin());
    std::copy(lhs.begin(), lhs.end(), current);
    return res;
}

template<class result_container_t, class container_t>
result_container_t make_container(const container_t& from)
{
    result_container_t container;

    for (const auto& item : from)
        container.insert(container.end(), typename result_container_t::value_type(item));

    return container;
}

template<class container_t>
constexpr size_t bytes_size(const container_t& container)
{
    return container.size() * sizeof(typename container_t::value_type);
}

} // namespace qx
