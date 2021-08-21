/**

    @file      observer.inl
    @author    Khrapov
    @date      6.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

//------------------------- qx::subject::observer_token ------------------------

inline observer_token::observer_token(
    base_subject* pSubject,
    observer*     pObserver) noexcept
    : m_pSubject(pSubject)
    , m_pObserver(pObserver)
{
}

inline void observer_token::reset(void) noexcept
{
    m_pSubject  = nullptr;
    m_pObserver = nullptr;
}

inline observer_token::observer_token(observer_token&& other) noexcept
{
    std::swap(m_pSubject, other.m_pSubject);
    std::swap(m_pObserver, other.m_pObserver);
}

inline observer_token& observer_token::operator=(
    observer_token&& other) noexcept
{
    std::swap(m_pSubject, other.m_pSubject);
    std::swap(m_pObserver, other.m_pObserver);
    return *this;
}

inline observer_token::~observer_token() noexcept
{
    if (m_pSubject && m_pObserver)
        m_pSubject->detach(m_pObserver);
}

inline bool observer_token::operator==(
    const observer_token& other) const noexcept
{
    return m_pSubject == other.m_pSubject && m_pObserver == other.m_pObserver;
}

inline observer_token::operator bool(void) const noexcept
{
    return m_pSubject && m_pObserver;
}



//--------------------------------- qx::subject --------------------------------

inline base_subject::~base_subject(void) noexcept
{
    while (!m_Observers.empty())
        m_Observers.back()->detach_from(this);
}

inline size_t base_subject::get_num_observers(void) const noexcept
{
    return m_Observers.size();
}

inline observer_token base_subject::attach(observer* pObserver)
{
    if (std::find(m_Observers.begin(), m_Observers.end(), pObserver)
        == m_Observers.end())
    {
        m_Observers.push_back(pObserver);
        return observer_token(this, pObserver);
    }
    else
    {
        return observer_token();
    }
}

inline void base_subject::detach(observer* pObserver) noexcept
{
    if (m_nIterators == 0)
    {
        m_Observers.erase(
            std::remove(m_Observers.begin(), m_Observers.end(), pObserver),
            m_Observers.end());
    }
    else
    {
        std::replace(
            m_Observers.begin(),
            m_Observers.end(),
            pObserver,
            static_cast<observer*>(nullptr));
    }
}

inline void base_subject::on_iterator_destructed(void) noexcept
{
    m_nIterators--;
    if (m_nIterators == 0)
    {
        m_Observers.erase(
            std::remove(m_Observers.begin(), m_Observers.end(), nullptr),
            m_Observers.end());
    }
}

inline void base_subject::on_iterator_constructed(void) noexcept
{
    m_nIterators++;
}



// --------------------------- subject::base_iterator --------------------------

template<class TObserver>
template<class TBaseIterator>
subject<TObserver>::base_iterator<TBaseIterator>::base_iterator(void) noexcept
    : TBaseIterator()
{
}

template<class TObserver>
template<class TBaseIterator>
subject<TObserver>::base_iterator<TBaseIterator>::base_iterator(
    const TBaseIterator& other,
    subject*             pSubject) noexcept
    : TBaseIterator(other)
    , m_pSubject(pSubject)
{
    init();
}

template<class TObserver>
template<class TBaseIterator>
subject<TObserver>::base_iterator<TBaseIterator>::base_iterator(
    const base_iterator& other) noexcept
    : TBaseIterator(other)
    , m_pSubject(other.m_pSubject)
{
    init();
}

template<class TObserver>
template<class TBaseIterator>
subject<TObserver>::base_iterator<TBaseIterator>::~base_iterator(void) noexcept
{
    m_pSubject->on_iterator_destructed();
}

template<class TObserver>
template<class TBaseIterator>
TObserver* subject<TObserver>::base_iterator<TBaseIterator>::operator->(
    void) noexcept
{
    return static_cast<TObserver*>(*TBaseIterator::operator->());
}

template<class TObserver>
template<class TBaseIterator>
TObserver& subject<TObserver>::base_iterator<TBaseIterator>::operator*(
    void) noexcept
{
    return static_cast<TObserver&>(*TBaseIterator::operator*());
}

template<class TObserver>
template<class TBaseIterator>
void subject<TObserver>::base_iterator<TBaseIterator>::init(void) noexcept
{
    m_pSubject->on_iterator_constructed();
}



// ------------------------ subject::const_base_iterator -----------------------

template<class TObserver>
template<class TBaseIterator>
inline subject<TObserver>::const_base_iterator<
    TBaseIterator>::const_base_iterator(const TBaseIterator& other) noexcept
    : TBaseIterator(other)
{
}

template<class TObserver>
template<class TBaseIterator>
const TObserver*    subject<TObserver>::const_base_iterator<
    TBaseIterator>::operator->(void) const noexcept
{
    return static_cast<const TObserver*>(*TBaseIterator::operator->());
}

template<class TObserver>
template<class TBaseIterator>
const TObserver&    subject<TObserver>::const_base_iterator<
    TBaseIterator>::operator*(void) const noexcept
{
    return static_cast<const TObserver&>(*TBaseIterator::operator*());
}



// ---------------------------------- subject ----------------------------------

template<class TObserver>
inline typename subject<TObserver>::iterator subject<TObserver>::begin(void)
{
    return iterator(m_Observers.begin(), this);
}

template<class TObserver>
inline typename subject<TObserver>::const_iterator subject<TObserver>::begin(
    void) const
{
    return const_iterator(m_Observers.cbegin());
}

template<class TObserver>
inline typename subject<TObserver>::const_iterator subject<TObserver>::cbegin(
    void) const
{
    return const_iterator(m_Observers.cbegin());
}

template<class TObserver>
inline typename subject<TObserver>::iterator subject<TObserver>::end(void)
{
    return iterator(m_Observers.end(), this);
}

template<class TObserver>
inline typename subject<TObserver>::const_iterator subject<TObserver>::end(
    void) const
{
    return const_iterator(m_Observers.cend());
}

template<class TObserver>
inline typename subject<TObserver>::const_iterator subject<TObserver>::cend(
    void) const
{
    return const_iterator(m_Observers.cend());
}

template<class TObserver>
inline typename subject<TObserver>::reverse_iterator subject<TObserver>::rbegin(
    void)
{
    return reverse_iterator(m_Observers.rbegin(), this);
}

template<class TObserver>
inline typename subject<TObserver>::const_reverse_iterator subject<
    TObserver>::rbegin(void) const
{
    return const_reverse_iterator(m_Observers.crbegin());
}

template<class TObserver>
inline typename subject<TObserver>::const_reverse_iterator subject<
    TObserver>::crbegin(void) const
{
    return const_reverse_iterator(m_Observers.crbegin());
}

template<class TObserver>
inline typename subject<TObserver>::reverse_iterator subject<TObserver>::rend(
    void)
{
    return reverse_iterator(m_Observers.rend(), this);
}

template<class TObserver>
inline typename subject<TObserver>::const_reverse_iterator subject<
    TObserver>::rend(void) const
{
    return const_reverse_iterator(m_Observers.crend());
}

template<class TObserver>
inline typename subject<TObserver>::const_reverse_iterator subject<
    TObserver>::crend(void) const
{
    return const_reverse_iterator(m_Observers.crend());
}



//-------------------------------- qx::observer --------------------------------

inline observer::~observer(void) = default;

inline void observer::attach_to(base_subject* pSubject)
{
    if (auto subjectToken = pSubject->attach(this))
    {
        if (std::find(m_Tokens.begin(), m_Tokens.end(), subjectToken)
            == m_Tokens.end())
        {
            m_Tokens.push_back(std::move(subjectToken));
        }
        else
        {
            subjectToken.reset();
        }
    }
}

inline void observer::detach_from(base_subject* pSubject)
{
    auto get_token_it = [this, pSubject]()
    {
        return std::find_if(
            m_Tokens.begin(),
            m_Tokens.end(),
            [pSubject](auto& _token)
            {
                return _token.m_pSubject == pSubject;
            });
    };

    auto it = get_token_it();
    while (it != m_Tokens.end())
    {
        m_Tokens.erase(it);
        it = get_token_it();
    }
}

inline void observer::detach_from_all(void)
{
    m_Tokens.clear();
}

inline size_t observer::get_num_subjects_attached_to(void) const
{
    return m_Tokens.size();
}

} // namespace qx
