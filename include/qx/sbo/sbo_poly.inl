/**

    @file      sbo_poly.inl
    @author    Khrapov
    @date      20.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<class base_t, size_t nSBOSize_>
template<sbo_poly_assignable_c<base_t> derived_t>
sbo_poly<base_t, nSBOSize_>::sbo_poly(derived_t object) noexcept
{
    assign(std::move(object));
}

template<class base_t, size_t nSBOSize_>
sbo_poly<base_t, nSBOSize_>::sbo_poly(sbo_poly&& other) noexcept
{
    *this = std::move(other);
}

template<class base_t, size_t nSBOSize_>
sbo_poly<base_t, nSBOSize_>::~sbo_poly() noexcept
{
    get().~base_t();
}

template<class base_t, size_t nSBOSize_>
template<sbo_poly_assignable_c<base_t> derived_t>
sbo_poly<base_t, nSBOSize_>& sbo_poly<base_t, nSBOSize_>::operator=(derived_t object) noexcept
{
    assign(std::move(object));
    return *this;
}

template<class base_t, size_t nSBOSize_>
sbo_poly<base_t, nSBOSize_>& sbo_poly<base_t, nSBOSize_>::operator=(sbo_poly&& other) noexcept
{
    if (!m_Data.is_small() && !other.m_Data.is_small())
    {
        // both objects are big, it's safe to simply swap pointers
        std::swap(m_Data, other.m_Data);
    }
    else
    {
        // one or both objects is small, we should call move constructors for them,
        // because it isn't safe to use memmove for them.
        // do it that way that we avoid allocations.

        sbo_bytes<sbo_poly_traits> temp;

        if (m_Data.is_small() && other.m_Data.is_small())
        {
            m_Assigner(m_Data, temp);
            other.m_Assigner(other.m_Data, m_Data);
            m_Assigner(temp, other.m_Data);
        }
        else if (m_Data.is_small())
        {
            m_Assigner(m_Data, temp);
            other.m_Data = std::move(m_Data);
            m_Assigner(temp, other.m_Data);
        }
        else
        {
            other.m_Assigner(other.m_Data, temp);
            m_Data = std::move(other.m_Data);
            other.m_Assigner(temp, m_Data);
        }
    }

    std::swap(m_Assigner, other.m_Assigner);

    return *this;
}

template<class base_t, size_t nSBOSize_>
template<sbo_poly_assignable_c<base_t> derived_t>
void sbo_poly<base_t, nSBOSize_>::assign(derived_t object) noexcept
{
    if (m_Data.size() > 0)
        get().~base_t();

    m_Data.resize(sizeof(derived_t), std::alignment_of_v<derived_t>, sbo_resize_type::common, false);
    new (m_Data.data()) derived_t(std::move(object));

    m_Assigner = [](sbo_bytes_type& from, sbo_bytes_type& to)
    {
        to.resize(sizeof(derived_t), std::alignment_of_v<derived_t>, sbo_resize_type::common, false);
        new (to.data()) derived_t(std::move(*reinterpret_cast<derived_t*>(from.data())));
    };
}

template<class base_t, size_t nSBOSize_>
base_t* sbo_poly<base_t, nSBOSize_>::operator->() noexcept
{
    return &get();
}

template<class base_t, size_t nSBOSize_>
const base_t* sbo_poly<base_t, nSBOSize_>::operator->() const noexcept
{
    return &get();
}

template<class base_t, size_t nSBOSize_>
base_t& sbo_poly<base_t, nSBOSize_>::get() noexcept
{
    return *reinterpret_cast<base_t*>(m_Data.data());
}

template<class base_t, size_t nSBOSize_>
const base_t& sbo_poly<base_t, nSBOSize_>::get() const noexcept
{
    return QX_CONST_CAST_THIS()->get();
}

} // namespace qx
