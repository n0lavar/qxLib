/**

    @file      observer.h
    @brief     Contains qx::subject and qx::observer classes
    @author    Khrapov
    @date      6.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/useful_macros.h>

#include <algorithm>
#include <vector>

namespace qx
{

class observer;
class base_subject;

/**

    @class   qx::observer_token
    @brief   Tokens are used to automatically detach observer when the observer
             object is destroyed
    @details ~

    @author  Khrapov
    @date    10.03.2021

**/
class observer_token
{
    friend base_subject;
    friend observer;

    QX_NONCOPYABLE(observer_token);

private:
    /**
        @brief observer_token object constructor
        @param pSubject  - corresponding subject pointer 
        @param pObserver - corresponding observer pointer 
    **/
    observer_token(base_subject* pSubject, observer* pObserver) noexcept;

    /**
        @brief   Reset observer_token
        @details Token won't unsubscribe observer from subject in destructor
    **/
    void reset(void) noexcept;

public:
    /**
        @brief observer_token object constructor
        @param other - other observer_token object rvalue ref
    **/
    observer_token(observer_token&& other) noexcept;
    /**
        @brief  operator=
        @param  other - other observer_token object rvalue ref
        @retval       - this object reference
    **/
    observer_token& operator=(observer_token&& other) noexcept;

    /**
        @brief observer_token object constructor
    **/
    observer_token(void) noexcept = default;

    /**
        @brief observer_token object destructor
    **/
    ~observer_token(void) noexcept;

    /**
        @brief  operator==
        @param  other - other observer_token object
        @retval       - true, if objects are equal
    **/
    bool operator==(const observer_token& other) const noexcept;

    /**
        @brief  operator bool
        @retval - true if observer_token is valid
    **/
    operator bool(void) const noexcept;

private:
    base_subject* m_pSubject  = nullptr;
    observer*     m_pObserver = nullptr;
};

/**

    @class   qx::base_subject
    @brief   Base subject class
    @details Allows to avoid template parameter for base logic

    @author  Khrapov
    @date    10.03.2021

**/
class base_subject
{
public:
    using observers_container = std::vector<observer*>;

    template<typename TObserver>
    friend class subject;
    friend observer_token;
    friend observer;

public:
    QX_NONCOPYABLE(base_subject);
    QX_MOVABLE(base_subject);

    /**
        @brief base_subject object constructor
    **/
    base_subject(void) = default;

    /**
        @brief base_subject object destructor
    **/
    virtual ~base_subject(void) noexcept = 0;

    /**
        @brief  Get number of observers attached to this subject
        @retval - number of observers attached to this subject
    **/
    size_t get_num_observers(void) const noexcept;

private:
    /**
        @brief  Attach observer to this subject
        @param  pObserver - observer pointer 
        @retval           - observer_token for autodetaching observer from this subject 
    **/
    [[nodiscard]] observer_token attach(observer* pObserver);

    /**
        @brief Detach observer from this subject
        @param pObserver - observer pointer
    **/
    void detach(observer* pObserver) noexcept;

    /**
        @brief Iterator destructing event handler
    **/
    void on_iterator_destructed(void) noexcept;

    /**
        @brief Iterator constructing event handler
    **/
    void on_iterator_constructed(void) noexcept;

private:
    observers_container m_Observers;
    size_t              m_nIterators = 0;
};

/**

    @class   qx::subject
    @brief   Class maintains a list of its dependents, called observers,
             and notifies them automatically of any state changes
    @details ~
    @tparam  TObserver - observer type
    @author  Khrapov
    @date    6.03.2021

**/
template<class TObserver>
class subject : public base_subject
{
    template<class TBaseIterator>
    class base_iterator : public TBaseIterator
    {
    public:
        /**
            @brief base_iterator object constructor
        **/
        base_iterator(void) noexcept;

        /**
            @brief base_iterator object constructor
            @param other    - base class iterator object 
            @param pSubject - subject class pointer 
        **/
        base_iterator(const TBaseIterator& other, subject* pSubject) noexcept;

        /**
            @brief base_iterator object constructor
            @param other - other object
        **/
        base_iterator(const base_iterator& other) noexcept;

        /**
            @brief base_iterator object constructor
            @param  - other base_iterator object rvalue ref
        **/
        base_iterator(base_iterator&&) noexcept = default;

        /**
            @brief base_iterator object destructor
        **/
        ~base_iterator(void) noexcept;

        /**
            @brief  operator->
            @retval - observer object pointer
        **/
        TObserver* operator->(void) noexcept;

        /**
            @brief  operator*
            @retval - observer object ref
        **/
        TObserver& operator*(void) noexcept;

    private:
        /**
            @brief Init iterator by calling subject callback
        **/
        void init(void) noexcept;

    private:
        subject* m_pSubject = nullptr;
    };

    template<class TBaseIterator>
    class const_base_iterator : public TBaseIterator
    {
    public:
        /**
            @brief const_base_iterator object constructor
        **/
        const_base_iterator(void) noexcept = default;

        /**
            @brief const_base_iterator object constructor
            @param - other const_base_iterator object ref
        **/
        const_base_iterator(const const_base_iterator&) noexcept = default;

        /**
            @brief const_base_iterator object constructor
            @param  - other const_base_iterator object rvalue ref
        **/
        const_base_iterator(const_base_iterator&&) noexcept = default;

        /**
            @brief const_base_iterator object constructor
            @param other - other const_base_iterator object ref
        **/
        const_base_iterator(const TBaseIterator& other) noexcept;

        /**
            @brief  operator->
            @retval - observer object const pointer
        **/
        const TObserver* operator->(void) const noexcept;

        /**
            @brief  operator*
            @retval - observer object const ref
        **/
        const TObserver& operator*(void) const noexcept;
    };

public:
    using iterator = base_iterator<observers_container::iterator>;

    using const_iterator =
        const_base_iterator<observers_container::const_iterator>;

    using reverse_iterator =
        base_iterator<observers_container::reverse_iterator>;

    using const_reverse_iterator =
        const_base_iterator<observers_container::const_reverse_iterator>;

public:
    /**
        @brief  Return iterator to beginning
        @retval - iterator to beginning
    **/
    iterator begin(void);

    /**
        @brief  Return iterator to beginning
        @retval - iterator to beginning
    **/
    const_iterator begin(void) const;

    /**
        @brief  Return const iterator to beginning
        @retval - const iterator to beginning
    **/
    const_iterator cbegin(void) const;

    /**
        @brief  Return iterator to end
        @retval - iterator to end
    **/
    iterator end(void);

    /**
        @brief  Return iterator to end
        @retval - iterator to end
    **/
    const_iterator end(void) const;

    /**
        @brief  Return const iterator to end
        @retval - const iterator to end
    **/
    const_iterator cend(void) const;

    /**
        @brief  Return reverse iterator to reverse beginning
        @retval - reverse iterator to reverse beginning
    **/
    reverse_iterator rbegin(void);

    /**
        @brief  Return reverse iterator to reverse beginning
        @retval - reverse iterator to reverse beginning
    **/
    const_reverse_iterator rbegin(void) const;

    /**
        @brief  Return const reverse iterator to reverse beginning
        @retval - const reverse iterator to reverse beginning
    **/
    const_reverse_iterator crbegin(void) const;

    /**
        @brief  Return reverse iterator to reverse end
        @retval - reverse iterator to reverse end
    **/
    reverse_iterator rend(void);

    /**
        @brief  Return reverse iterator to reverse end
        @retval - reverse iterator to reverse end
    **/
    const_reverse_iterator rend(void) const;

    /**
        @brief  Return const reverse iterator to reverse end
        @retval - const reverse iterator to reverse end
    **/
    const_reverse_iterator crend(void) const;
};

/**

    @class   qx::observer
    @brief   qx::subject class event observers
    @details ~

    @author  Khrapov
    @date    6.03.2021

**/
class observer
{
public:
    /**
        @brief observer object destructor
    **/
    virtual ~observer(void) = 0;

    /**
        @brief Attach this observer to subject
        @param pSubject - subject pointer
    **/
    void attach_to(base_subject* pSubject);

    /**
        @brief Detach this observer from subject
        @param pSubject - subject pointer
    **/
    void detach_from(base_subject* pSubject);

    /**
        @brief Detach observer from all subjects
    **/
    void detach_from_all(void);

    /**
        @brief  Get number of subjects this observer is attached to
        @retval - number of subjects this observer is attached to
    **/
    size_t get_num_subjects_attached_to(void) const;

private:
    std::vector<observer_token> m_Tokens;
};

} // namespace qx

#include <qx/patterns/observer.inl>
