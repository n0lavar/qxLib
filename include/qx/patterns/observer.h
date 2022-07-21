/**

    @file      observer.h
    @brief     Contains qx::subject and qx::observer_token classes
    @author    Khrapov
    @date      6.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/useful_macros.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace qx
{

class base_subject;

template<class TObserver>
class subject;

/**

    @class   observer_token_data
    @brief   Tokens are used to automatically detach observer when the observer
             object is destroyed
    @details ~
    @author  Khrapov
    @date    10.03.2021

**/
class observer_token_data
{
    QX_NONCOPYABLE(observer_token_data);

    template<class>
    friend class subject;

public:
    /**
        @brief observer_token object constructor
    **/
    observer_token_data() noexcept = default;

    /**
        @brief observer_token object constructor
        @param pSubject  - corresponding subject pointer 
        @param pObserver - corresponding observer pointer 
    **/
    observer_token_data(base_subject* pSubject, void* pObserver) noexcept;

    /**
        @brief observer_token object constructor
        @param other - other observer_token object rvalue ref
    **/
    observer_token_data(observer_token_data&& other) noexcept;

    /**
        @brief observer_token object destructor
    **/
    ~observer_token_data() noexcept;

    /**
        @brief   Reset observer_token
        @details Token won't unsubscribe observer from subject in destructor
    **/
    void reset() noexcept;

    /**
        @brief  operator=
        @param  other - other observer_token object rvalue ref
        @retval       - this object reference
    **/
    observer_token_data& operator=(observer_token_data&& other) noexcept;

    /**
        @brief  operator==
        @param  other - other observer_token object
        @retval       - true, if objects are equal
    **/
    bool operator==(const observer_token_data& other) const noexcept;

    /**
        @brief  operator bool
        @retval - true if observer_token is valid
    **/
    operator bool() const noexcept;

private:
    base_subject* m_pSubject  = nullptr;
    void*         m_pObserver = nullptr;
};

using observer_token = std::unique_ptr<observer_token_data>;

/**

    @class   base_subject
    @brief   Base subject class
    @details Allows to avoid template parameter for base logic
    @details ~
    @author  Khrapov
    @date    17.11.2021

**/
class base_subject
{
    friend observer_token_data;

protected:
    /**
        @brief base_subject object destructor
    **/
    virtual ~base_subject() noexcept = default;

    /**
        @brief Detach observer from subject
        @param pObserver - observer pointer
    **/
    virtual void detach(void* pObserver) noexcept = 0;
};

/**

    @class   subject
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
        base_iterator() noexcept = default;

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
        ~base_iterator() noexcept;

        /**
            @brief  operator=
            @param  other - other object
            @retval       - this object reference
        **/
        base_iterator& operator=(const base_iterator& other) noexcept;

        /**
            @brief  operator->
            @retval - observer object pointer
        **/
        TObserver* operator->() noexcept;

        /**
            @brief  operator*
            @retval - observer object ref
        **/
        TObserver& operator*() noexcept;

    private:
        /**
            @brief Init iterator by calling subject callback
        **/
        void init() noexcept;

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
        const_base_iterator() noexcept = default;

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
        const TObserver* operator->() const noexcept;

        /**
            @brief  operator*
            @retval - observer object const ref
        **/
        const TObserver& operator*() const noexcept;
    };

public:
    using observers_container = std::vector<TObserver*>;

    using iterator = base_iterator<typename observers_container::iterator>;

    using const_iterator = const_base_iterator<typename observers_container::const_iterator>;

    using reverse_iterator = base_iterator<typename observers_container::reverse_iterator>;

    using const_reverse_iterator = const_base_iterator<typename observers_container::const_reverse_iterator>;

    using notify_func = std::function<void(TObserver*)>;

public:
    QX_NONCOPYABLE(subject);
    QX_MOVABLE(subject);

    /**
        @brief base_subject object constructor
    **/
    subject() = default;

    /**
        @brief subject object destructor
    **/
    virtual ~subject() override;

    /**
        @brief  Attach observer to this subject
        @param  pObserver - observer pointer 
        @retval           - observer_token for auto detaching observer from this subject 
    **/
    [[nodiscard]] observer_token attach(TObserver* pObserver) noexcept;

    /**
        @brief Notify all observers
        @param notifyFunc - callback
    **/
    void notify(const notify_func& notifyFunc) const noexcept;

    /**
        @brief  Return iterator to beginning
        @retval - iterator to beginning
    **/
    iterator begin();

    /**
        @brief  Return iterator to beginning
        @retval - iterator to beginning
    **/
    const_iterator begin() const;

    /**
        @brief  Return const iterator to beginning
        @retval - const iterator to beginning
    **/
    const_iterator cbegin() const;

    /**
        @brief  Return iterator to end
        @retval - iterator to end
    **/
    iterator end();

    /**
        @brief  Return iterator to end
        @retval - iterator to end
    **/
    const_iterator end() const;

    /**
        @brief  Return const iterator to end
        @retval - const iterator to end
    **/
    const_iterator cend() const;

    /**
        @brief  Return reverse iterator to reverse beginning
        @retval - reverse iterator to reverse beginning
    **/
    reverse_iterator rbegin();

    /**
        @brief  Return reverse iterator to reverse beginning
        @retval - reverse iterator to reverse beginning
    **/
    const_reverse_iterator rbegin() const;

    /**
        @brief  Return const reverse iterator to reverse beginning
        @retval - const reverse iterator to reverse beginning
    **/
    const_reverse_iterator crbegin() const;

    /**
        @brief  Return reverse iterator to reverse end
        @retval - reverse iterator to reverse end
    **/
    reverse_iterator rend();

    /**
        @brief  Return reverse iterator to reverse end
        @retval - reverse iterator to reverse end
    **/
    const_reverse_iterator rend() const;

    /**
        @brief  Return const reverse iterator to reverse end
        @retval - const reverse iterator to reverse end
    **/
    const_reverse_iterator crend() const;

    /**
        @brief  Get number of observers attached to this subject
        @retval - number of observers attached to this subject
    **/
    size_t get_num_observers() const noexcept;

private:
    /**
        @brief Detach observer from this subject
        @param pObserver - observer pointer
    **/
    virtual void detach(void* pObserver) noexcept override;

    /**
        @brief Iterator destructing event handler
    **/
    void on_iterator_destructed() noexcept;

    /**
        @brief Iterator constructing event handler
    **/
    void on_iterator_constructed() noexcept;

private:
    observers_container               m_Observers;
    std::vector<observer_token_data*> m_Tokens;
    size_t                            m_nIterators = 0;
};

} // namespace qx

#include <qx/patterns/observer.inl>
