//==============================================================================
//
//!\file                         list_se.inl
//
//!\brief       Single ended list
//!\details     ~
//
//!\author      Khrapov
//!\date        5.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                      qx::list_se<T>::assign
//
//!\brief    Assign by copying all nodes from another list
//!\property O(list.size())
//!\param    list - another list
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::assign(const list_se& list)
{
    if (list.cbegin() != cbegin())
    {
        clear();
        for (auto& elem : list)
            push_back(elem);
    }
}

//==============================================================================
//!\fn                      qx::list_se<T>::assign
//
//!\brief    Assign by moving from other list
//!\property O(1)
//!\param    list - other list
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::assign(list_se&& list) noexcept
{
    std::swap(m_pFirstNode, list.m_pFirstNode);
    std::swap(m_pLastNode,  list.m_pLastNode);
    std::swap(m_nSize,      list.m_nSize);
}

//==============================================================================
//!\fn                      qx::list_se<T>::assign
//
//!\brief    Assign by copying from std::initializer_list
//!\property O(init.size())
//!\param    init - std::initializer_list
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::assign(init_list init)
{
    clear();
    for (auto& elem : init)
        push_back(elem);
}

//==============================================================================
//!\fn                      qx::list_se<T>::assign
//
//!\brief    Assign by filling with 'count' elemtnts of 'value'
//!\property O(count)
//!\param    count - number of elements
//!\param    value - element to fill
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::assign(size_type count, const_reference value)
{
    clear();
    for (size_type i = 0; i < count; i++)
        push_back(value);
}

//==============================================================================
//!\fn                      qx::list_se<T>::insert
//
//!\brief    Insert element in list
//!\property O(size())
//!\param    where - iterator, where new elem will be placed
//!\param    what  - element
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::insert(iterator where, const_reference what)
{
    emplace(where, what);
}

//==============================================================================
//!\fn                      qx::list_se<T>::insert
//
//!\brief    Insert number of elements in list
//!\property O(size() + number)
//!\param    where  - iterator, where new elems will be placed
//!\param    what   - pointer to first element
//!\param    number - number of elements
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::insert(iterator where, const_pointer what, size_type number)
{
    if (where != begin())
    {
        iterator it = begin();
        while (it != end() && it.m_pNode->pNext != where.m_pNode)
            ++it;

        if (it != end())
            insert_after(it, what, number);
    }
    else
    {
        for (size_type i = 0; i < number; i++)
            push_front(what);
    }
}

//==============================================================================
//!\fn                   qx::list_se<T>::insert_after
//
//!\brief    Insert elemtnt after 'where' iterator
//!\property O(1)
//!\param    where - iterator after which a new element will be inserted
//!\param    what  - new element
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::insert_after(iterator where, const_reference what)
{
    emplace_after(where, what);
}

//==============================================================================
//!\fn                   qx::list_se<T>::insert_after
//
//!\brief    Insert elemtnts after 'where' iterator
//!\property O(number)
//!\param    where  - iterator after which a new elements will be inserted
//!\param    what   - new element
//!\param    number - number of elements
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::insert_after(iterator where, const_pointer what, size_type number)
{
    for (size_type i = 0; i < number; i++)
    {
        insert_after(where, *(what + i));
        ++where;
    }
}

//==============================================================================
//!\fn                      qx::list_se<T>::erase
//
//!\brief    Erase elements from list
//!\property O(size() + number)
//!\param    where  - iterator, where erasing starts
//                    using "where" after erasing is UB
//!\param    number - number of elements to erase
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::erase(iterator where, size_type number)
{
    if (where != begin())
    {
        iterator it = begin();
        while (it != end() && it.m_pNode->pNext != where.m_pNode)
            ++it;

        if (it != end())
            erase_after(it, number);
    }
    else
    {
        for (size_type i = 0; i < number; i++)
            pop_front();
    }
}

//==============================================================================
//!\fn                   qx::list_se<T>::erase_after
//
//!\brief    Erase elements from list
//!\property O(number)
//!\param    where  - iterator, after witch erasing starts
//                    using "where" after erasing is ok
//!\param    number - number of elements to erase
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::erase_after(iterator where, size_type number)
{
    iterator current = where;
    ++current;

    iterator temp;
    for (size_type i = 0; i < number && current != end(); i++)
    {
        temp = current;
        ++temp;
        delete current.m_pNode;
        current = temp;
        m_nSize--;
    }

    where.m_pNode->pNext = current.m_pNode;

    if (current.m_pNode == nullptr)
        m_pLastNode = where.m_pNode;
}

//==============================================================================
//!\fn                    qx::list_se<T>::push_back
//
//!\brief    Push back element
//!\property O(size())
//!\param    what - new element
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::push_back(const_reference what)
{
    emplace_back(what);
}

//==============================================================================
//!\fn                    qx::list_se<T>::push_front
//
//!\brief    Push front element
//!\property O(1)
//!\param    what - new element
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::push_front(const_reference what)
{
    emplace_front(what);
}

//==============================================================================
//!\fn                     qx::list_se<T>::pop_back
//
//!\brief    Pop back element
//!\property O(size())
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::pop_back(void)
{
    erase(m_pLastNode);
}

//==============================================================================
//!\fn                    qx::list_se<T>::pop_front
//
//!\brief    Pop front element
//!\property O(1)
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::pop_front(void)
{
    list_se_node* temp = m_pFirstNode;
    m_pFirstNode = m_pFirstNode->pNext;
    delete temp;
    m_nSize--;

    if (m_pFirstNode == nullptr)
        m_pLastNode = nullptr;
}

//==============================================================================
//!\fn              qx::list_se<T>::emplace_front<...Args>
//
//!\brief    Construct and insert element at the front
//!\property O(1)
//!\param    ...args - arguments to construct T
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
template<class ...Args>
inline void list_se<T>::emplace_front(Args&& ...args)
{
    list_se_node* pNode = new list_se_node(std::forward<Args>(args)...);
    pNode->pNext = m_pFirstNode;
    m_pFirstNode = pNode;
    if (!m_pLastNode)
        m_pLastNode = pNode;

    m_nSize++;
}

//==============================================================================
//!\fn                 qx::list_se<T>::emplace<...Args>
//
//!\brief    Construct and insert element
//!\property O(size())
//!\param    where   - iterator, where to insert
//!\param    ...args - arguments to construct T
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
template<class ...Args>
inline void list_se<T>::emplace(iterator where, Args&& ...args)
{
    if (where != begin())
    {
        iterator it = begin();
        while (it != end() && it.m_pNode->pNext != where.m_pNode)
            ++it;

        if (it != end())
            emplace_after(it, std::forward<Args>(args)...);
    }
    else
    {
        emplace_front(std::forward<Args>(args)...);
    }
}

//==============================================================================
//!\fn              qx::list_se<T>::emplace_after<...Args>
//
//!\brief    Construct and insert element
//!\property O(1)
//!\param    where   - iterator, after witch inserting starts
//!\param    ...args - arguments to construct T
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
template<class ...Args>
inline void list_se<T>::emplace_after(iterator where, Args&& ...args)
{
    list_se_node* pNode = new list_se_node(std::forward<Args>(args)...);
    pNode->pNext = where.m_pNode->pNext;
    where.m_pNode->pNext = pNode;
    m_nSize++;

    if (pNode->pNext == nullptr)
        m_pLastNode = pNode;
}

//==============================================================================
//!\fn              qx::list_se<T>::emplace_back<...Args>
//
//!\brief    Construct and insert element at the end
//!\property O(size())
//!\param    ...args - arguments to construct T
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
template<class ...Args>
inline void list_se<T>::emplace_back(Args&& ...args)
{
    list_se_node* pNode = new list_se_node(std::forward<Args>(args)...);

    if (m_pLastNode)
        m_pLastNode->pNext = pNode;
    else
        m_pFirstNode = pNode;

    m_pLastNode = pNode;
    m_nSize++;
}

//==============================================================================
//!\fn                      qx::list_se<T>::clear
//
//!\brief    Clear list
//!\property O(size())
//!\author   Khrapov
//!\date     8.02.2020
//==============================================================================
template<class T>
inline void list_se<T>::clear(void)
{
    list_se_node* pCurrent = nullptr;
    list_se_node* pNext = m_pFirstNode;

    while (pNext)
    {
        pCurrent = pNext;
        pNext = pCurrent->pNext;
        delete pCurrent;
    }

    m_pFirstNode = nullptr;
    m_pLastNode  = nullptr;
    m_nSize      = 0;
}

}
