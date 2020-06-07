//==============================================================================
//
//!\file                          list_se.h
//
//!\brief       Single ended list
//!\details     ~
//
//!\author      Khrapov
//!\date        4.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <initializer_list>
#include <utility>
#include <iterator>

namespace qx
{

//==============================================================================
//
//!\class                         list_se<T>
//
//!\brief   Single ended list class
//!\details ~
//
//!\author  Khrapov
//!\date    4.02.2020
//
//==============================================================================
template<class T>
class list_se
{
    struct list_se_node
    {
        list_se_node() { }

        template<class ...Args>
        list_se_node(Args&& ...args) : value(std::forward<Args>(args)...) { }

        T             value = T();
        list_se_node* pNext = nullptr;
    };

public:

    class const_iterator;

    class iterator
    {
        friend class list_se;
        friend class const_iterator;

    public:

        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
        using difference_type   = std::ptrdiff_t;
        using size_type         = std::size_t;
        using iterator_category = std::forward_iterator_tag;

        iterator        (void) = default;
        iterator        (list_se_node* pNode) : m_pNode(pNode) { }

        reference operator*   (void)                     { return m_pNode->value;                   }
        pointer   operator->  (void)                     { return &m_pNode->value;                  }
        bool      operator!=  (const iterator & r) const { return m_pNode != r.m_pNode;             }
        bool      operator==  (const iterator & r) const { return m_pNode == r.m_pNode;             }
        iterator& operator++  (void)    { m_pNode = m_pNode->pNext; return *this;                   }
        iterator  operator++  (int)     { iterator i(m_pNode); m_pNode = m_pNode->pNext; return i;  }

    private:
        list_se_node* m_pNode = nullptr;
    };

    class const_iterator
    {
        friend class list_se;

    public:
        using value_type        = const T;
        using pointer           = const T*;
        using reference         = const T&;
        using difference_type   = std::ptrdiff_t;
        using size_type         = std::size_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator  (void) = default;
        const_iterator  (const list_se_node* pNode) : m_pNode(pNode) { }
        const_iterator  (const iterator& it) : m_pNode(it.m_pNote)   { }

        reference       operator*   (void)                          { return m_pNode->value;                  }
        pointer         operator->  (void)                          { return &m_pNode->value;                 }
        bool            operator!=  (const const_iterator& r) const { return m_pNode != r.m_pNode;            }
        bool            operator==  (const const_iterator& r) const { return m_pNode == r.m_pNode;            }
        const_iterator& operator++  (void)  { m_pNode = m_pNode->pNext; return *this;                         }
        const_iterator  operator++  (int)   { const_iterator i(m_pNode); m_pNode = m_pNode->pNext; return i;  }

    private:
        const list_se_node* m_pNode = nullptr;
    };

    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using size_type         = std::size_t;
    using init_list         = const std::initializer_list<T>&;

public:

                        list_se         (void) = default;
                        list_se         (const list_se&     list)   { assign(list);                     }
                        list_se         (list_se&&          list) noexcept { assign(std::move(list));   }
                        list_se         (init_list          init)   { assign(init);                     }
                        list_se         (size_type          count,
                                         const_reference    value)  { assign(count, value);             }
                        ~list_se        (void)                      { clear();                          }

    const list_se&      operator=       (const list_se&     list)   { assign(list); return *this;       }
    const list_se&      operator=       (list_se&&          list) noexcept { assign(std::move(list)); return *this; }
    const list_se&      operator=       (init_list          init)   { assign(init); return *this;       }

    void                assign          (const list_se&     list);
    void                assign          (list_se&&          list) noexcept;
    void                assign          (init_list          init);
    void                assign          (size_type          count,
                                         const_reference    value);

    void                insert          (iterator           where,
                                         const_reference    what);
    void                insert          (iterator           where,
                                         const_pointer      what,
                                         size_type          number = 1);
    void                insert_after    (iterator           where,
                                         const_reference    what);
    void                insert_after    (iterator           where,
                                         const_pointer      what,
                                         size_type          number = 1);
    void                erase           (iterator           where,
                                         size_type          number = 1);
    void                erase_after     (iterator           where,
                                         size_type          number = 1);

    template<class ... Args>
    void                emplace_front   (Args&&...          args);
    template<class ... Args>
    void                emplace         (iterator           where, 
                                         Args&&...          args);
    template<class ... Args>
    void                emplace_after   (iterator           where, 
                                         Args&&...          args);
    template<class ... Args>
    void                emplace_back    (Args&&...          args);
    void                push_back       (const_reference    what);
    void                push_front      (const_reference    what);
    void                pop_back        (void);
    void                pop_front       (void);

    void                clear           (void);

    size_type           size            (void)  const   { return m_nSize;                       }
    bool                empty           (void)  const   { return size() == 0;                   }
    iterator            begin           (void)          { return iterator(m_pFirstNode);        }
    const_iterator      begin           (void)  const   { return const_iterator(m_pFirstNode);  }
    iterator            end             (void)          { return iterator(nullptr);             }
    const_iterator      end             (void)  const   { return const_iterator(nullptr);       }
    const_iterator      cbegin          (void)  const   { return const_iterator(m_pFirstNode);  }
    const_iterator      cend            (void)  const   { return const_iterator(nullptr);       }
    reference           front           (void)          { return m_pFirstNode->value;           }
    reference           back            (void)          { return m_pLastNode->value;            }
    const_reference     front           (void)  const   { return m_pFirstNode->value;           }
    const_reference     back            (void)  const   { return m_pLastNode->value;            }

private:
    list_se_node*       m_pFirstNode    = nullptr;
    list_se_node*       m_pLastNode     = nullptr;
    size_type           m_nSize         = 0;
};

template<class T>
using list = list_se<T>;

}

#include <qx/containers/list_se.inl>
