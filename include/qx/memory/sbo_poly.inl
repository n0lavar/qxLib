/**

    @file      sbo_poly.inl
    @author    Khrapov
    @date      20.12.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
template<sbo_poly_assignable_c<base_t> derived_t>
sbo_poly<base_t, nSBOSize_>::sbo_poly(derived_t object) noexcept
{
    assign(std::move(object));
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
sbo_poly<base_t, nSBOSize_>::sbo_poly(sbo_poly&& other) noexcept
{
    *this = std::move(other);
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
sbo_poly<base_t, nSBOSize_>::~sbo_poly() noexcept
{
    // may be empty if an object was moved
    if (m_Deleter)
        m_Deleter(m_Data);
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
template<sbo_poly_assignable_c<base_t> derived_t>
sbo_poly<base_t, nSBOSize_>& sbo_poly<base_t, nSBOSize_>::operator=(derived_t object) noexcept
{
    assign(std::move(object));
    return *this;
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
sbo_poly<base_t, nSBOSize_>& sbo_poly<base_t, nSBOSize_>::operator=(sbo_poly&& other) noexcept
{
    if (this == &other)
        return *this;

    if (m_Deleter)
        m_Deleter(m_Data);

    if (other.m_Data.is_small())
    {
        other.m_Assigner(other.m_Data, m_Data);
        other.m_Deleter(other.m_Data);
    }
    else
    {
        // Heap-backed objects can transfer ownership without moving the object itself.
        m_Data = std::move(other.m_Data);
    }

    m_Assigner       = other.m_Assigner;
    m_Deleter        = other.m_Deleter;
    other.m_Assigner = nullptr;
    other.m_Deleter  = nullptr;

    return *this;
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
template<sbo_poly_assignable_c<base_t> derived_t>
void sbo_poly<base_t, nSBOSize_>::assign(derived_t object) noexcept
{
    if (m_Data.size() > 0)
        get().~base_t();

    m_Data.resize(sizeof(derived_t));
    new (m_Data.data()) derived_t(std::move(object));

    m_Assigner = [](sbo_bytes_type& from, sbo_bytes_type& to)
    {
        to.resize(sizeof(derived_t));
        new (to.data()) derived_t(std::move(*reinterpret_cast<derived_t*>(from.data())));
    };

    m_Deleter = [](sbo_bytes_type& object)
    {
        reinterpret_cast<derived_t*>(object.data())->~derived_t();
    };
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
base_t* sbo_poly<base_t, nSBOSize_>::operator->() noexcept
{
    return &get();
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
const base_t* sbo_poly<base_t, nSBOSize_>::operator->() const noexcept
{
    return &get();
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
base_t& sbo_poly<base_t, nSBOSize_>::get() noexcept
{
    return *reinterpret_cast<base_t*>(m_Data.data());
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > 2 * sizeof(void*))
const base_t& sbo_poly<base_t, nSBOSize_>::get() const noexcept
{
    return QX_CONST_CAST_THIS()->get();
}

} // namespace qx
