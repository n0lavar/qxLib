/**

    @file      sbo_poly.inl
    @author    Khrapov
    @date      20.12.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
template<sbo_poly_assignable_c<base_t> derived_t>
sbo_poly<base_t, nSBOSize_>::sbo_poly(derived_t object)
{
    assign(std::move(object));
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
sbo_poly<base_t, nSBOSize_>::sbo_poly(sbo_poly&& other) noexcept
{
    *this = std::move(other);
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
sbo_poly<base_t, nSBOSize_>::~sbo_poly() noexcept
{
    // may be empty if an object was moved
    if (m_Operations)
        m_Operations->Destroy(m_Data);
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
template<sbo_poly_assignable_c<base_t> derived_t>
sbo_poly<base_t, nSBOSize_>& sbo_poly<base_t, nSBOSize_>::operator=(derived_t object)
{
    assign(std::move(object));
    return *this;
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
sbo_poly<base_t, nSBOSize_>& sbo_poly<base_t, nSBOSize_>::operator=(sbo_poly&& other) noexcept
{
    if (this == &other)
        return *this;

    // destroy the current object

    if (m_Operations)
        m_Operations->Destroy(m_Data);

    // required for exception safety if the move operation throws an exception
    m_Operations = nullptr;

    // move the other object to this one

    if (!other.m_Operations)
        return *this;

    if (other.m_Data.is_small())
    {
        other.m_Operations->Move(other.m_Data, m_Data);
        other.m_Operations->Destroy(other.m_Data);
    }
    else
    {
        // Heap-backed objects can transfer ownership without moving the object itself.
        m_Data = std::move(other.m_Data);
    }

    m_Operations       = other.m_Operations;
    other.m_Operations = nullptr;

    return *this;
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
template<sbo_poly_assignable_c<base_t> derived_t>
void sbo_poly<base_t, nSBOSize_>::assign(derived_t object)
{
    if (m_Operations)
        m_Operations->Destroy(m_Data);

    m_Operations = nullptr;

    if (!m_Data.resize(sizeof(derived_t)))
        throw std::bad_alloc();

    new (m_Data.data()) derived_t(std::move(object));
    m_Operations = &get_operations<derived_t>();
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
template<sbo_poly_assignable_c<base_t> derived_t>
const typename sbo_poly<base_t, nSBOSize_>::operations& sbo_poly<base_t, nSBOSize_>::get_operations() noexcept
{
    static constexpr operations table { [](sbo_bytes_type& object) noexcept -> base_t*
                                        {
                                            return static_cast<base_t*>(reinterpret_cast<derived_t*>(object.data()));
                                        },
                                        [](sbo_bytes_type& from, sbo_bytes_type& to) noexcept
                                        {
                                            if (!to.resize(sizeof(derived_t)))
                                                std::terminate();

                                            new (to.data())
                                                derived_t(std::move(*reinterpret_cast<derived_t*>(from.data())));
                                        },
                                        [](sbo_bytes_type& object) noexcept
                                        {
                                            reinterpret_cast<derived_t*>(object.data())->~derived_t();
                                        } };

    return table;
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
base_t* sbo_poly<base_t, nSBOSize_>::operator->() noexcept
{
    return &get();
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
const base_t* sbo_poly<base_t, nSBOSize_>::operator->() const noexcept
{
    return &get();
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
base_t& sbo_poly<base_t, nSBOSize_>::get() noexcept
{
    return *m_Operations->Get(m_Data);
}

template<class base_t, size_t nSBOSize_>
    requires(nSBOSize_ > sizeof(void*))
const base_t& sbo_poly<base_t, nSBOSize_>::get() const noexcept
{
    return QX_CONST_CAST_THIS()->get();
}

} // namespace qx
