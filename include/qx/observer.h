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

#include <qx/rtti.h>

#include <functional>
#include <vector>

namespace qx
{

class observer;

template<class TObserver>
using notify_func = std::function<void(TObserver*)>;

//==============================================================================
//
//!\class                           qx::subject
//
//!\brief   Class maintains a list of its dependents, called observers,
//          and notifies them automatically of any state changes
//          by calling notify<T>
//!\details Tokens are used to automatically detach when the observer
//          object is destroyed
//
//!\author  Khrapov
//!\date    6.03.2021
//
//==============================================================================
class subject
{
public:

    class token
    {
        friend subject;
        friend observer;

    private:

                token       (subject  * pSubject,
                             observer * pObserver) noexcept;

        void    reset       (void)          noexcept;

    public:

                token       (token&& other) noexcept;
        token & operator=   (token&& other) noexcept;
                token       (const token&)  noexcept = delete;
        token & operator=   (const token&)  noexcept = delete;

                token       (void)          noexcept = default;
                ~token      (void)          noexcept;

        bool    operator<   (const token& other) const noexcept;

    private:

        subject   * m_pSubject  = nullptr;
        observer  * m_pObserver = nullptr;
    };

    friend token;
    friend observer;

private:

    token   attach  (observer * pObserver);
    void    detach  (observer * pObserver) noexcept;

public:

    virtual ~subject(void) noexcept = default;

    template<class TObserver>
    void    notify  (const notify_func<TObserver>& func);

    size_t  get_num_observers   (void) const noexcept;

private:

    std::vector<observer*> m_Observers;
};

//==============================================================================
//
//!\class                           qx::observer
//
//!\brief   qx::subject class event observers
//!\details The lifetime of objects of this class must be less than the lifetime
//          of the corresponding qx::subject object
//
//!\author  Khrapov
//!\date    6.03.2021
//
//==============================================================================
class observer : public rtti_base
{
    QX_RTTI_CLASS(observer, rtti_base)

public:

    virtual ~observer   (void) = 0 {}

    void attach_to      (subject* pSubject);
    void detach_from    (subject* pSubject);

private:

    std::vector<subject::token> m_Tokens;
};

}

#include <qx/observer.inl>
