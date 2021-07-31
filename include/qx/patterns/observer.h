//==============================================================================
//
//!\file                           observer.h
//
//!\brief       Contains qx::subject and qx::observer classes
//!\details     ~
//
//!\author      Khrapov
//!\date        6.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/useful_macros.h>

#include <algorithm>
#include <vector>

namespace qx
{

class observer;
class base_subject;

//==============================================================================
//
//!\class                     qx::observer_token
//
//!\details Tokens are used to automatically detach observer when the observer
//          object is destroyed
//!\details ~
//
//!\author  Khrapov
//!\date    10.03.2021
//
//==============================================================================
class observer_token
{
    friend base_subject;
    friend observer;

private:

                    observer_token  (base_subject * pSubject,
                                     observer     * pObserver)              noexcept;

    void            reset           (void)                                  noexcept;

public:

                    observer_token  (observer_token&&        other)         noexcept;
    observer_token& operator=       (observer_token&&        other)         noexcept;
                    observer_token  (const observer_token&)                 noexcept = delete;
    observer_token& operator=       (const observer_token&)                 noexcept = delete;

                    observer_token  (void)                                  noexcept = default;
                    ~observer_token (void)                                  noexcept;

    bool            operator==      (const observer_token  & other) const   noexcept;
    operator bool                   (void)                          const   noexcept;

private:

    base_subject    * m_pSubject  = nullptr;
    observer        * m_pObserver = nullptr;
};

//==============================================================================
//
//!\class                      qx::base_subject
//
//!\brief   Base subject class
//!\details Allows to avoid template parameter for base logic
//
//!\author  Khrapov
//!\date    10.03.2021
//
//==============================================================================
class base_subject
{
public:

    using observers_container = std::vector<observer*>;

    template<typename TObserver>
    friend class subject;
    friend observer_token;
    friend observer;

private:

    [[nodiscard]] observer_token attach                  (observer * pObserver);
    void                detach                  (observer * pObserver) noexcept;
    void                on_iterator_destructed  (void)  noexcept;
    void                on_iterator_constructed (void)  noexcept;

public:

    QX_NONCOPYABLE(base_subject)
    QX_MOVABLE(base_subject)

            base_subject        (void)                  = default;
    virtual ~base_subject       (void)      noexcept    = 0;

    size_t  get_num_observers   (void) const noexcept;

private:

    observers_container m_Observers;
    size_t              m_nIterators = 0;
};

//==============================================================================
//
//!\class                    qx::subject<TObserver>
//
//!\brief   Class maintains a list of its dependents, called observers,
//          and notifies them automatically of any state changes
//!\details ~
//
//!\author  Khrapov
//!\date    6.03.2021
//
//==============================================================================
template<class TObserver>
class subject : public base_subject
{
    template<class TBaseIterator>
    class base_iterator : public TBaseIterator
    {
    public:

        base_iterator   (void) noexcept;
        base_iterator   (const TBaseIterator  & other,
                         subject              * pSubject)   noexcept;
        base_iterator   (const base_iterator  & other)      noexcept;
        base_iterator   (base_iterator&&)                   noexcept = default;
        ~base_iterator  (void)                              noexcept;

        TObserver * operator->  (void)  noexcept;
        TObserver & operator*   (void)  noexcept;

    private:

        void        init        (void)  noexcept;

    private:

        subject* m_pSubject = nullptr;
    };

    template<class TBaseIterator>
    class const_base_iterator : public TBaseIterator
    {
    public:

        const_base_iterator(void)                               noexcept = default;
        const_base_iterator(const const_base_iterator & other)  noexcept = default;
        const_base_iterator(const_base_iterator&&)              noexcept = default;
        const_base_iterator(const TBaseIterator       & other)  noexcept;

        const TObserver* operator-> (void) const noexcept;
        const TObserver& operator*  (void) const noexcept;
    };

public:

    using iterator               = base_iterator<observers_container::iterator>;
    using const_iterator         = const_base_iterator<observers_container::const_iterator>;
    using reverse_iterator       = base_iterator<observers_container::reverse_iterator>;
    using const_reverse_iterator = const_base_iterator<observers_container::const_reverse_iterator>;

public:

    auto begin   (void)       { return iterator(m_Observers.begin(), this); }
    auto begin   (void) const { return const_iterator(m_Observers.cbegin()); }
    auto cbegin  (void) const { return const_iterator(m_Observers.cbegin()); }
    auto end     (void)       { return iterator(m_Observers.end(), this); }
    auto end     (void) const { return const_iterator(m_Observers.cend()); }
    auto cend    (void) const { return const_iterator(m_Observers.cend()); }
    auto rbegin  (void)       { return reverse_iterator(m_Observers.rbegin(), this); }
    auto rbegin  (void) const { return const_reverse_iterator(m_Observers.crbegin()); }
    auto crbegin (void) const { return const_reverse_iterator(m_Observers.crbegin()); }
    auto rend    (void)       { return reverse_iterator(m_Observers.rend(), this); }
    auto rend    (void) const { return const_reverse_iterator(m_Observers.crend()); }
    auto crend   (void) const { return const_reverse_iterator(m_Observers.crend()); }
};

//==============================================================================
//
//!\class                           qx::observer
//
//!\brief   qx::subject class event observers
//!\details ~
//
//!\author  Khrapov
//!\date    6.03.2021
//
//==============================================================================
class observer
{
public:

    virtual ~observer                       (void) = 0;

    void    attach_to                       (base_subject * pSubject);
    void    detach_from                     (base_subject * pSubject);
    void    detach_from_all                 (void);
    size_t  get_num_subjects_attached_to    (void) const;

private:

    std::vector<observer_token> m_Tokens;
};

}

#include <qx/patterns/observer.inl>
