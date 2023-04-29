/**

    @file      observer.inl
    @author    Khrapov
    @date      6.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

// -------------------------- qx::observer_token_data --------------------------

inline observer_token_data::observer_token_data(base_subject* pSubject, void* pObserver) noexcept
    : m_pSubject(pSubject)
    , m_pObserver(pObserver)
{
}

inline void observer_token_data::reset() noexcept
{
    if (m_pSubject && m_pObserver)
        m_pSubject->detach(m_pObserver);

    m_pSubject  = nullptr;
    m_pObserver = nullptr;
}

inline observer_token_data::observer_token_data(observer_token_data&& other) noexcept
{
    std::swap(m_pSubject, other.m_pSubject);
    std::swap(m_pObserver, other.m_pObserver);
}

inline observer_token_data& observer_token_data::operator=(observer_token_data&& other) noexcept
{
    std::swap(m_pSubject, other.m_pSubject);
    std::swap(m_pObserver, other.m_pObserver);
    return *this;
}

inline observer_token_data::~observer_token_data() noexcept
{
    reset();
}

inline bool observer_token_data::operator==(const observer_token_data& other) const noexcept
{
    return m_pSubject == other.m_pSubject && m_pObserver == other.m_pObserver;
}

inline observer_token_data::operator bool() const noexcept
{
    return m_pSubject && m_pObserver;
}



// --------------------------- subject::base_iterator --------------------------

template<class observer_t>
template<class base_iterator_t>
inline subject<observer_t>::base_iterator<base_iterator_t>::base_iterator(
    const base_iterator_t& other,
    subject*               pSubject) noexcept
    : base_iterator_t(other)
    , m_pSubject(pSubject)
{
    init();
}

template<class observer_t>
template<class base_iterator_t>
inline subject<observer_t>::base_iterator<base_iterator_t>::base_iterator(const base_iterator& other) noexcept
    : base_iterator_t(other)
    , m_pSubject(other.m_pSubject)
{
    init();
}

template<class observer_t>
template<class base_iterator_t>
inline subject<observer_t>::base_iterator<base_iterator_t>::~base_iterator() noexcept
{
    m_pSubject->on_iterator_destructed();
}

template<class observer_t>
template<class base_iterator_t>
inline typename subject<observer_t>::template base_iterator<base_iterator_t>& subject<observer_t>::base_iterator<
    base_iterator_t>::operator=(const base_iterator& other) noexcept
{
    *this = std::move(base_iterator(other));
    return *this;
}

template<class observer_t>
template<class base_iterator_t>
inline observer_t* subject<observer_t>::base_iterator<base_iterator_t>::operator->(void) noexcept
{
    return static_cast<observer_t*>(*base_iterator_t::operator->());
}

template<class observer_t>
template<class base_iterator_t>
inline observer_t& subject<observer_t>::base_iterator<base_iterator_t>::operator*(void) noexcept
{
    return static_cast<observer_t&>(*base_iterator_t::operator*());
}

template<class observer_t>
template<class base_iterator_t>
inline void subject<observer_t>::base_iterator<base_iterator_t>::init() noexcept
{
    m_pSubject->on_iterator_constructed();
}



// ------------------------ subject::const_base_iterator -----------------------

template<class observer_t>
template<class base_iterator_t>
inline subject<observer_t>::const_base_iterator<base_iterator_t>::const_base_iterator(
    const base_iterator_t& other) noexcept
    : base_iterator_t(other)
{
}

template<class observer_t>
template<class base_iterator_t>
const observer_t* subject<observer_t>::const_base_iterator<base_iterator_t>::operator->() const noexcept
{
    return static_cast<const observer_t*>(*base_iterator_t::operator->());
}

template<class observer_t>
template<class base_iterator_t>
const observer_t& subject<observer_t>::const_base_iterator<base_iterator_t>::operator*() const noexcept
{
    return static_cast<const observer_t&>(*base_iterator_t::operator*());
}



// ---------------------------------- subject ----------------------------------

template<class observer_t>
inline subject<observer_t>::~subject()
{
    // temp vector because reset will erase elements from m_Tokens
    const auto tokens = m_Tokens;
    for (const auto pToken : tokens)
        pToken->reset();
}

template<class observer_t>
inline observer_token subject<observer_t>::attach(observer_t* pObserver) noexcept
{
    if (std::find(m_Observers.begin(), m_Observers.end(), pObserver) == m_Observers.end())
    {
        m_Observers.push_back(pObserver);
        auto token = std::make_unique<observer_token_data>(this, pObserver);
        m_Tokens.push_back(token.get());
        return token;
    }
    else
    {
        return observer_token();
    }
}

template<class observer_t>
inline void subject<observer_t>::notify(const notify_func& notifyFunc) const noexcept
{
    for (auto pObserver : m_Observers)
        notifyFunc(pObserver);
}

template<class observer_t>
inline typename subject<observer_t>::iterator subject<observer_t>::begin()
{
    return iterator(m_Observers.begin(), this);
}

template<class observer_t>
inline typename subject<observer_t>::const_iterator subject<observer_t>::begin(void) const
{
    return const_iterator(m_Observers.cbegin());
}

template<class observer_t>
inline typename subject<observer_t>::const_iterator subject<observer_t>::cbegin(void) const
{
    return const_iterator(m_Observers.cbegin());
}

template<class observer_t>
inline typename subject<observer_t>::iterator subject<observer_t>::end()
{
    return iterator(m_Observers.end(), this);
}

template<class observer_t>
inline typename subject<observer_t>::const_iterator subject<observer_t>::end(void) const
{
    return const_iterator(m_Observers.cend());
}

template<class observer_t>
inline typename subject<observer_t>::const_iterator subject<observer_t>::cend(void) const
{
    return const_iterator(m_Observers.cend());
}

template<class observer_t>
inline typename subject<observer_t>::reverse_iterator subject<observer_t>::rbegin(void)
{
    return reverse_iterator(m_Observers.rbegin(), this);
}

template<class observer_t>
inline typename subject<observer_t>::const_reverse_iterator subject<observer_t>::rbegin() const
{
    return const_reverse_iterator(m_Observers.crbegin());
}

template<class observer_t>
inline typename subject<observer_t>::const_reverse_iterator subject<observer_t>::crbegin() const
{
    return const_reverse_iterator(m_Observers.crbegin());
}

template<class observer_t>
inline typename subject<observer_t>::reverse_iterator subject<observer_t>::rend(void)
{
    return reverse_iterator(m_Observers.rend(), this);
}

template<class observer_t>
inline typename subject<observer_t>::const_reverse_iterator subject<observer_t>::rend() const
{
    return const_reverse_iterator(m_Observers.crend());
}

template<class observer_t>
inline typename subject<observer_t>::const_reverse_iterator subject<observer_t>::crend() const
{
    return const_reverse_iterator(m_Observers.crend());
}

template<class observer_t>
inline size_t subject<observer_t>::get_num_observers() const noexcept
{
    return m_Observers.size();
}

template<class observer_t>
inline void subject<observer_t>::detach(void* pObserver) noexcept
{
    if (m_nIterators == 0)
    {
        std::erase_if(
            m_Tokens,
            [pObserver](const observer_token_data* pToken)
            {
                return pToken->m_pObserver == pObserver;
            });

        m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), pObserver), m_Observers.end());
    }
    else
    {
        std::replace_if(
            m_Tokens.begin(),
            m_Tokens.end(),
            [pObserver](const observer_token_data* pToken)
            {
                return pToken && pToken->m_pObserver == pObserver;
            },
            static_cast<observer_token_data*>(nullptr));

        std::replace(
            m_Observers.begin(),
            m_Observers.end(),
            static_cast<observer_t*>(pObserver),
            static_cast<observer_t*>(nullptr));
    }
}

template<class observer_t>
inline void subject<observer_t>::on_iterator_destructed() noexcept
{
    m_nIterators--;
    if (m_nIterators == 0)
    {
        m_Tokens.erase(std::remove(m_Tokens.begin(), m_Tokens.end(), nullptr), m_Tokens.end());

        m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), nullptr), m_Observers.end());
    }
}

template<class observer_t>
inline void subject<observer_t>::on_iterator_constructed() noexcept
{
    m_nIterators++;
}

} // namespace qx
