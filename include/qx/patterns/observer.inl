//==============================================================================
//
//!\file                          observer.inl
//
//!\brief       Contains qx::subject and qx::observer classes
//!\details     ~
//
//!\author      Khrapov
//!\date        6.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//------------------------- qx::subject::observer_token ------------------------

//==============================================================================
//!\fn                    qx::observer_token::observer_token
//
//!\brief  observer_token object constructor
//!\param  pSubject  - corresponding subject pointer
//!\param  pObserver - corresponding observer pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline observer_token::observer_token(
    base_subject* pSubject,
    observer    * pObserver) noexcept
    : m_pSubject (pSubject)
    , m_pObserver(pObserver)
{
}

//==============================================================================
//!\fn                    qx::observer_token::reset
//
//!\brief   Reset observer_token
//!\details Token won't unsubscribe observer from subject in destructor
//!\author  Khrapov
//!\date    6.03.2021
//==============================================================================
inline void observer_token::reset(void) noexcept
{
    m_pSubject  = nullptr;
    m_pObserver = nullptr;
}

//==============================================================================
//!\fn                   qx::observer_token::observer_token
//
//!\brief  observer_token object constructor
//!\param  other - other observer_token object
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline observer_token::observer_token(observer_token&& other) noexcept
{
    std::swap(m_pSubject,  other.m_pSubject);
    std::swap(m_pObserver, other.m_pObserver);
}

//==============================================================================
//!\fn                  qx::observer_token::operator=
//
//!\brief  Assign by other observer_token object
//!\param  other - other observer_token object
//!\retval       - this reference
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline observer_token& observer_token::operator=(
    observer_token&& other) noexcept
{
    std::swap(m_pSubject,  other.m_pSubject);
    std::swap(m_pObserver, other.m_pObserver);
    return *this;
}

//==============================================================================
//!\fn                    qx::observer_token::~observer_token
//
//!\brief  observer_token object destructor
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline observer_token::~observer_token() noexcept
{
    if (m_pSubject && m_pObserver)
        m_pSubject->detach(m_pObserver);
}

//==============================================================================
//!\fn                  qx::observer_token::operator==
//
//!\brief  operator==
//!\param  other - other observer_token object
//!\retval       - true tokens are equal
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline bool observer_token::operator==(
    const observer_token& other) const noexcept
{
    return m_pSubject == other.m_pSubject && m_pObserver == other.m_pObserver;
}

//==============================================================================
//!\fn                 qx::observer_token::operator bool
//
//!\brief  operator bool
//!\retval  - true if observer_token is valid
//!\author Khrapov
//!\date   31.07.2021
//==============================================================================
inline observer_token::operator bool(void) const noexcept
{
    return m_pSubject && m_pObserver;
}



//--------------------------------- qx::subject --------------------------------

//==============================================================================
//!\fn                        qx::subject::attach
//
//!\brief  Attach observer to this subject
//!\param  pObserver - observer pointer
//!\retval           - observer_token for autodetaching observer from this subject
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline observer_token base_subject::attach(observer * pObserver)
{
    if (std::find(
        m_Observers.begin(),
        m_Observers.end(),
        pObserver) == m_Observers.end())
    {
        m_Observers.push_back(pObserver);
        return observer_token(this, pObserver);
    }
    else
    {
        return observer_token();
    }
}

//==============================================================================
//!\fn                        qx::subject::detach
//
//!\brief  Detach observer from this subject
//!\param  pObserver - observer pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline void base_subject::detach(observer * pObserver) noexcept
{
    if (m_nIterators == 0)
    {
        m_Observers.erase(std::remove(
            m_Observers.begin(),
            m_Observers.end(),
            pObserver), m_Observers.end());
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

//==============================================================================
//!\fn              qx::base_subject::on_iterator_destructed
//
//!\brief  Iterator destructing event handler
//!\author Khrapov
//!\date   11.03.2021
//==============================================================================
inline void base_subject::on_iterator_destructed(void) noexcept
{
    m_nIterators--;
    if (m_nIterators == 0)
    {
        m_Observers.erase(std::remove(
            m_Observers.begin(),
            m_Observers.end(),
            nullptr), m_Observers.end());
    }
}

//==============================================================================
//!\fn             qx::base_subject::on_iterator_constructed
//
//!\brief  Iterator constructing event handler
//!\author Khrapov
//!\date   11.03.2021
//==============================================================================
inline void base_subject::on_iterator_constructed(void) noexcept
{
    m_nIterators++;
}

//==============================================================================
//!\fn                    base_subject::~base_subject
//
//!\brief  base_subject object destructor
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
inline base_subject::~base_subject(void) noexcept
{
    while (!m_Observers.empty())
        m_Observers.back()->detach_from(this);
}

//==============================================================================
//!\fn                   qx::subject::get_num_observers
//
//!\brief  Get number of observers attached to this subject
//!\retval  - number of observers attached to this subject
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline size_t base_subject::get_num_observers(void) const noexcept
{
    return m_Observers.size();
}



//------------------------------ subject iterators -----------------------------

//==============================================================================
//!\fn  qx::subject<TObserver>::base_iterator<TBaseIterator>::base_iterator
//
//!\brief  base_iterator object constructor
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
subject<TObserver>::base_iterator<TBaseIterator>::base_iterator(void) noexcept
    : TBaseIterator()
{
}

//==============================================================================
//!\fn  qx::subject<TObserver>::base_iterator<TBaseIterator>::base_iterator
//
//!\brief  base_iterator object constructor
//!\param  other    - base class iterator object
//!\param  pSubject - subject class pointer
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
subject<TObserver>::base_iterator<TBaseIterator>::base_iterator(
    const TBaseIterator   & other,
    subject               * pSubject) noexcept
    : TBaseIterator (other)
    , m_pSubject    (pSubject)
{
    init();
}

//==============================================================================
//!\fn  qx::subject<TObserver>::base_iterator<TBaseIterator>::base_iterator
//
//!\brief  base_iterator object constructor
//!\param  other - other object
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
subject<TObserver>::base_iterator<TBaseIterator>::base_iterator(
    const base_iterator& other) noexcept
    : TBaseIterator (other)
    , m_pSubject    (other.m_pSubject)
{
    init();
}

//==============================================================================
//!\fn  qx::subject<TObserver>::base_iterator<TBaseIterator>::~base_iterator
//
//!\brief  base_iterator object destructor
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
subject<TObserver>::base_iterator<TBaseIterator>::~base_iterator(
    void) noexcept
{
    m_pSubject->on_iterator_destructed();
}

//==============================================================================
//!\fn    qx::subject<TObserver>::base_iterator<TBaseIterator>::operator->
//
//!\brief  operator->
//!\retval  - observer object pointer
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
TObserver* subject<TObserver>::base_iterator<TBaseIterator>::operator->(
    void) noexcept
{
    return static_cast<TObserver*>(*TBaseIterator::operator->());
}

//==============================================================================
//!\fn    qx::subject<TObserver>::base_iterator<TBaseIterator>::operator*
//
//!\brief  operator*
//!\retval  - observer object reference
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
TObserver& subject<TObserver>::base_iterator<TBaseIterator>::operator*(
    void) noexcept
{
    return static_cast<TObserver&>(*TBaseIterator::operator*());
}

//==============================================================================
//!\fn       qx::subject<TObserver>::base_iterator<TBaseIterator>::init
//
//!\brief  Init iterator by calling subject callback
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
void subject<TObserver>::base_iterator<TBaseIterator>::init(
    void) noexcept
{
    m_pSubject->on_iterator_constructed();
}

//==============================================================================
//!\fn subject<TObserver>::const_base_iterator<TBaseIterator>::const_base_iterator
//
//!\brief  const_base_iterator object constructor
//!\param  other - other iterator
//!\author Khrapov
//!\date   21.05.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
inline subject<TObserver>::const_base_iterator<TBaseIterator>::const_base_iterator(
    const TBaseIterator& other) noexcept
    : TBaseIterator(other)
{
}

//==============================================================================
//!\fn qx::subject<TObserver>::const_base_iterator<TBaseIterator>::operator->
//
//!\brief  operator->
//!\retval  - observer object const pointer
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
const TObserver* subject<TObserver>::const_base_iterator<TBaseIterator>::operator->(
    void) const noexcept
{
    return static_cast<const TObserver*>(*TBaseIterator::operator->());
}

//==============================================================================
//!\fn qx::subject<TObserver>::const_base_iterator<TBaseIterator>::operator*
//
//!\brief  operator*
//!\retval  - observer object const reference
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
template<class TObserver>
template<class TBaseIterator>
const TObserver& subject<TObserver>::const_base_iterator<TBaseIterator>::operator*(
    void) const noexcept
{
    return static_cast<const TObserver&>(*TBaseIterator::operator*());
}



//-------------------------------- qx::observer --------------------------------

inline observer::~observer(void) = default;

//==============================================================================
//!\fn                      qx::observer::attach_to
//
//!\brief  Attach this observer to subject
//!\param  pSubject - subject pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline void observer::attach_to(base_subject * pSubject)
{
    if (auto subjectToken = pSubject->attach(this))
    {
        if (std::find(
            m_Tokens.begin(),
            m_Tokens.end(),
            subjectToken) == m_Tokens.end())
        {
            m_Tokens.push_back(std::move(subjectToken));
        }
        else
        {
            subjectToken.reset();
        }
    }
}

//==============================================================================
//!\fn                     qx::observer::detach_from
//
//!\brief  Detach this observer from subject
//!\param  pSubject - subject pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline void observer::detach_from(base_subject * pSubject)
{
    auto get_token_it = [this, pSubject]()
    {
        return std::find_if(
            m_Tokens.begin(),
            m_Tokens.end(),
            [pSubject](auto& _token){ return _token.m_pSubject == pSubject; });
    };

    auto it = get_token_it();
    while (it != m_Tokens.end())
    {
        m_Tokens.erase(it);
        it = get_token_it();
    }
}

//==============================================================================
//!\fn                     observer::detach_from_all
//
//!\brief  Detach observer from all subjects
//!\author Khrapov
//!\date   11.03.2021
//==============================================================================
inline void observer::detach_from_all(void)
{
    m_Tokens.clear();
}

//==============================================================================
//!\fn             qx::observer::get_num_subjects_attached_to
//
//!\brief  Get number of subjects this observer is attached to
//!\retval  - number of subjects this observer is attached to
//!\author Khrapov
//!\date   12.03.2021
//==============================================================================
inline size_t observer::get_num_subjects_attached_to(void) const
{
    return m_Tokens.size();
}

}
