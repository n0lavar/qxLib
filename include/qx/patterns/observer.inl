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

template<class TObserver>
template<class TBaseIterator>
inline subject<TObserver>::base_iterator<TBaseIterator>::base_iterator(
    const TBaseIterator& other,
    subject*             pSubject) noexcept
    : TBaseIterator(other)
    , m_pSubject(pSubject)
{
    init();
}

template<class TObserver>
template<class TBaseIterator>
inline subject<TObserver>::base_iterator<TBaseIterator>::base_iterator(const base_iterator& other) noexcept
    : TBaseIterator(other)
    , m_pSubject(other.m_pSubject)
{
    init();
}

template<class TObserver>
template<class TBaseIterator>
inline subject<TObserver>::base_iterator<TBaseIterator>::~base_iterator() noexcept
{
    m_pSubject->on_iterator_destructed();
}

template<class TObserver>
template<class TBaseIterator>
inline typename subject<TObserver>::template base_iterator<TBaseIterator>& subject<TObserver>::base_iterator<
    TBaseIterator>::operator=(const base_iterator& other) noexcept
{
    *this = std::move(base_iterator(other));
    return *this;
}

template<class TObserver>
template<class TBaseIterator>
inline TObserver* subject<TObserver>::base_iterator<TBaseIterator>::operator->(void) noexcept
{
    return static_cast<TObserver*>(*TBaseIterator::operator->());
}

template<class TObserver>
template<class TBaseIterator>
inline TObserver& subject<TObserver>::base_iterator<TBaseIterator>::operator*(void) noexcept
{
    return static_cast<TObserver&>(*TBaseIterator::operator*());
}

template<class TObserver>
template<class TBaseIterator>
inline void subject<TObserver>::base_iterator<TBaseIterator>::init() noexcept
{
    m_pSubject->on_iterator_constructed();
}



// ------------------------ subject::const_base_iterator -----------------------

template<class TObserver>
template<class TBaseIterator>
inline subject<TObserver>::const_base_iterator<TBaseIterator>::const_base_iterator(const TBaseIterator& other) noexcept
    : TBaseIterator(other)
{
}

template<class TObserver>
template<class TBaseIterator>
const TObserver* subject<TObserver>::const_base_iterator<TBaseIterator>::operator->() const noexcept
{
    return static_cast<const TObserver*>(*TBaseIterator::operator->());
}

template<class TObserver>
template<class TBaseIterator>
const TObserver& subject<TObserver>::const_base_iterator<TBaseIterator>::operator*() const noexcept
{
    return static_cast<const TObserver&>(*TBaseIterator::operator*());
}



// ---------------------------------- subject ----------------------------------

template<class TObserver>
inline subject<TObserver>::~subject()
{
    // temp vector because reset will erase elements from m_Tokens
    const auto tokens = m_Tokens;
    for (const auto pToken : tokens)
        pToken->reset();
}

template<class TObserver>
inline observer_token subject<TObserver>::attach(TObserver* pObserver) noexcept
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

template<class TObserver>
inline void subject<TObserver>::notify(const notify_func& notifyFunc) const noexcept
{
    for (auto pObserver : m_Observers)
        notifyFunc(pObserver);
}

template<class TObserver>
inline typename subject<TObserver>::iterator subject<TObserver>::begin()
{
    return iterator(m_Observers.begin(), this);
}

template<class TObserver>
inline typename subject<TObserver>::const_iterator subject<TObserver>::begin(void) const
{
    return const_iterator(m_Observers.cbegin());
}

template<class TObserver>
inline typename subject<TObserver>::const_iterator subject<TObserver>::cbegin(void) const
{
    return const_iterator(m_Observers.cbegin());
}

template<class TObserver>
inline typename subject<TObserver>::iterator subject<TObserver>::end()
{
    return iterator(m_Observers.end(), this);
}

template<class TObserver>
inline typename subject<TObserver>::const_iterator subject<TObserver>::end(void) const
{
    return const_iterator(m_Observers.cend());
}

template<class TObserver>
inline typename subject<TObserver>::const_iterator subject<TObserver>::cend(void) const
{
    return const_iterator(m_Observers.cend());
}

template<class TObserver>
inline typename subject<TObserver>::reverse_iterator subject<TObserver>::rbegin(void)
{
    return reverse_iterator(m_Observers.rbegin(), this);
}

template<class TObserver>
inline typename subject<TObserver>::const_reverse_iterator subject<TObserver>::rbegin() const
{
    return const_reverse_iterator(m_Observers.crbegin());
}

template<class TObserver>
inline typename subject<TObserver>::const_reverse_iterator subject<TObserver>::crbegin() const
{
    return const_reverse_iterator(m_Observers.crbegin());
}

template<class TObserver>
inline typename subject<TObserver>::reverse_iterator subject<TObserver>::rend(void)
{
    return reverse_iterator(m_Observers.rend(), this);
}

template<class TObserver>
inline typename subject<TObserver>::const_reverse_iterator subject<TObserver>::rend() const
{
    return const_reverse_iterator(m_Observers.crend());
}

template<class TObserver>
inline typename subject<TObserver>::const_reverse_iterator subject<TObserver>::crend() const
{
    return const_reverse_iterator(m_Observers.crend());
}

template<class TObserver>
inline size_t subject<TObserver>::get_num_observers() const noexcept
{
    return m_Observers.size();
}

template<class TObserver>
inline void subject<TObserver>::detach(void* pObserver) noexcept
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
            static_cast<TObserver*>(pObserver),
            static_cast<TObserver*>(nullptr));
    }
}

template<class TObserver>
inline void subject<TObserver>::on_iterator_destructed() noexcept
{
    m_nIterators--;
    if (m_nIterators == 0)
    {
        m_Tokens.erase(std::remove(m_Tokens.begin(), m_Tokens.end(), nullptr), m_Tokens.end());

        m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), nullptr), m_Observers.end());
    }
}

template<class TObserver>
inline void subject<TObserver>::on_iterator_constructed() noexcept
{
    m_nIterators++;
}

} // namespace qx
