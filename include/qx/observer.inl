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

//----------------------------- qx::subject::token -----------------------------

//==============================================================================
//!\fn                     qx::subject::token::token
//
//!\brief  token object constructor
//!\param  pSubject  - corresponding subject pointer
//!\param  pObserver - corresponding observer pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline subject::token::token(subject* pSubject, observer* pObserver) noexcept
    : m_pSubject (pSubject)
    , m_pObserver(pObserver)
{
}

//==============================================================================
//!\fn                     qx::subject::token::reset
//
//!\brief  Reset token. Token won't unsubscribe observer from subject in destructor
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline void subject::token::reset(void) noexcept
{
    m_pSubject  = nullptr;
    m_pObserver = nullptr;
}

//==============================================================================
//!\fn                     qx::subject::token::token
//
//!\brief  token object constructor
//!\param  other - other token object
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline subject::token::token(token&& other) noexcept
{
    std::swap(m_pSubject,  other.m_pSubject);
    std::swap(m_pObserver, other.m_pObserver);
}

//==============================================================================
//!\fn                   qx::subject::token::operator=
//
//!\brief  Assign by other token object
//!\param  other - other token object
//!\retval       - this reference
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline subject::token& subject::token::operator=(token&& other) noexcept
{
    std::swap(m_pSubject,  other.m_pSubject);
    std::swap(m_pObserver, other.m_pObserver);
    return *this;
}

//==============================================================================
//!\fn                     qx::subject::token::~token
//
//!\brief  token object destructor
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline subject::token::~token() noexcept
{
    if (m_pSubject && m_pObserver)
        m_pSubject->detach(m_pObserver);
}

//==============================================================================
//!\fn                   qx::subject::token::operator<
//
//!\brief  operator<
//!\param  other - other token object
//!\retval       - true if this less then other
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline bool subject::token::operator<(const token& other) const noexcept
{
    return m_pSubject < other.m_pSubject;
}



//--------------------------------- qx::subject --------------------------------

//==============================================================================
//!\fn                        qx::subject::attach
//
//!\brief  Attach observer to this subject
//!\param  pObserver - observer pointer
//!\retval           - token for autodetaching observer from this subject
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline subject::token subject::attach(observer * pObserver)
{
    m_Observers.insert(pObserver);
    return token(this, pObserver);
}

//==============================================================================
//!\fn                        qx::subject::detach
//
//!\brief  Detach observer from this subject
//!\param  pObserver - observer pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline void subject::detach(observer * pObserver) noexcept
{
    m_Observers.erase(pObserver);
}

//==============================================================================
//!\fn                   qx::subject::get_num_observers
//
//!\brief  Get number of observers attached to this subject
//!\retval  - number of observers attached to this subject
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline size_t subject::get_num_observers(void) const noexcept
{
    return m_Observers.size();
}

//==============================================================================
//!\fn                   qx::subject::notify<TObserver>
//
//!\brief  Notify all observers of type TObserver
//!\param  func - function for notifying
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
template<class TObserver>
inline void subject::notify(const notify_func<TObserver>& func)
{
    for (auto pAnyTypeObserver : m_Observers)
        if (auto pRequiredType = rtti_cast<TObserver>(pAnyTypeObserver))
             func(pRequiredType);
}



//-------------------------------- qx::observer --------------------------------

//==============================================================================
//!\fn                      qx::observer::attach_to
//
//!\brief  Attach this observer to subject
//!\param  pSubject - subject pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline void observer::attach_to(subject * pSubject)
{
    auto _token = std::move(pSubject->attach(this));
    const auto ret = m_Tokens.insert(std::move(_token));

    // reattachment protection
    if (!ret.second)
        _token.reset();
}

//==============================================================================
//!\fn                     qx::observer::detach_from
//
//!\brief  Detach this observer from subject
//!\param  pSubject - subject pointer
//!\author Khrapov
//!\date   6.03.2021
//==============================================================================
inline void observer::detach_from(subject * pSubject)
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

}
