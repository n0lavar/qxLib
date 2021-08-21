/**

    @file      list_se.inl
    @author    Khrapov
    @date      5.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class T>
template<class... Args>
inline list_se<T>::list_se_node::list_se_node(Args&&... args)
    : value(std::forward<Args>(args)...)
{
}

template<class T>
inline list_se<T>::iterator::iterator(list_se_node* pNode) : m_pNode(pNode)
{
}

template<class T>
inline typename list_se<T>::iterator::reference list_se<T>::iterator::operator*(
    void)
{
    return m_pNode->value;
}

template<class T>
inline typename list_se<T>::iterator::pointer list_se<T>::iterator::operator->(
    void)
{
    return &m_pNode->value;
}

template<class T>
inline bool list_se<T>::iterator::operator!=(const iterator& r) const
{
    return m_pNode != r.m_pNode;
}

template<class T>
inline bool list_se<T>::iterator::operator==(const iterator& r) const
{
    return m_pNode == r.m_pNode;
}

template<class T>
inline typename list_se<T>::iterator::iterator& list_se<
    T>::iterator::operator++(void)
{
    m_pNode = m_pNode->pNext;
    return *this;
}

template<class T>
inline typename list_se<T>::iterator::iterator list_se<T>::iterator::operator++(
    int)
{
    iterator i(m_pNode);
    m_pNode = m_pNode->pNext;
    return i;
}

template<class T>
list_se<T>::const_iterator::const_iterator(const list_se_node* pNode)
    : m_pNode(pNode)
{
}

template<class T>
list_se<T>::const_iterator::const_iterator(const iterator& it)
    : m_pNode(it.m_pNote)
{
}

template<class T>
inline typename list_se<T>::const_iterator::reference list_se<
    T>::const_iterator::operator*(void)
{
    return m_pNode->value;
}

template<class T>
inline typename list_se<T>::const_iterator::pointer list_se<
    T>::const_iterator::operator->(void)
{
    return &m_pNode->value;
}

template<class T>
inline bool list_se<T>::const_iterator::operator!=(
    const const_iterator& r) const
{
    return m_pNode != r.m_pNode;
}

template<class T>
bool list_se<T>::const_iterator::operator==(const const_iterator& r) const
{
    return m_pNode == r.m_pNode;
}

template<class T>
inline typename list_se<T>::const_iterator::const_iterator& list_se<
    T>::const_iterator::operator++(void)
{
    m_pNode = m_pNode->pNext;
    return *this;
}

template<class T>
inline typename list_se<T>::const_iterator::const_iterator list_se<
    T>::const_iterator::operator++(int)
{
    const_iterator i(m_pNode);
    m_pNode = m_pNode->pNext;
    return i;
}

template<class T>
inline list_se<T>::list_se(const list_se& list)
{
    assign(list);
}

template<class T>
inline list_se<T>::list_se(list_se&& list) noexcept
{
    assign(std::move(list));
}

template<class T>
inline list_se<T>::list_se(init_list init)
{
    assign(init);
}

template<class T>
inline list_se<T>::list_se(size_type nElements, const_reference value)
{
    assign(nElements, value);
}

template<class T>
inline list_se<T>::~list_se(void)
{
    clear();
}

template<class T>
inline const list_se<T>& list_se<T>::operator=(const list_se& list)
{
    assign(list);
    return *this;
}

template<class T>
inline const list_se<T>& list_se<T>::operator=(list_se&& list) noexcept
{
    assign(std::move(list));
    return *this;
}

template<class T>
inline const list_se<T>& list_se<T>::operator=(init_list init)
{
    assign(init);
    return *this;
}

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

template<class T>
inline void list_se<T>::assign(list_se&& list) noexcept
{
    std::swap(m_pFirstNode, list.m_pFirstNode);
    std::swap(m_pLastNode, list.m_pLastNode);
    std::swap(m_nSize, list.m_nSize);
}

template<class T>
inline void list_se<T>::assign(init_list init)
{
    clear();
    for (auto& elem : init)
        push_back(elem);
}

template<class T>
inline void list_se<T>::assign(size_type nElements, const_reference value)
{
    clear();
    for (size_type i = 0; i < nElements; i++)
        push_back(value);
}

template<class T>
inline void list_se<T>::insert(iterator where, const_reference what)
{
    emplace(where, what);
}

template<class T>
inline void list_se<T>::insert(
    iterator      itWhere,
    const_pointer pWhat,
    size_type     nElements)
{
    if (itWhere != begin())
    {
        iterator it = begin();
        while (it != end() && it.m_pNode->pNext != itWhere.m_pNode)
            ++it;

        if (it != end())
            insert_after(it, pWhat, nElements);
    }
    else
    {
        for (size_type i = 0; i < nElements; i++)
            push_front(pWhat);
    }
}

template<class T>
inline void list_se<T>::insert_after(iterator itWhere, const_reference what)
{
    emplace_after(itWhere, what);
}

template<class T>
inline void list_se<T>::insert_after(
    iterator      itWhere,
    const_pointer pWhat,
    size_type     nElements)
{
    for (size_type i = 0; i < nElements; i++)
    {
        insert_after(itWhere, *(pWhat + i));
        ++itWhere;
    }
}

template<class T>
inline void list_se<T>::erase(iterator itWhere, size_type nElements)
{
    if (itWhere != begin())
    {
        iterator it = begin();
        while (it != end() && it.m_pNode->pNext != itWhere.m_pNode)
            ++it;

        if (it != end())
            erase_after(it, nElements);
    }
    else
    {
        for (size_type i = 0; i < nElements; i++)
            pop_front();
    }
}

template<class T>
inline void list_se<T>::erase_after(iterator itWhere, size_type nElements)
{
    iterator current = itWhere;
    ++current;

    iterator temp;
    for (size_type i = 0; i < nElements && current != end(); i++)
    {
        temp = current;
        ++temp;
        delete current.m_pNode;
        current = temp;
        m_nSize--;
    }

    itWhere.m_pNode->pNext = current.m_pNode;

    if (current.m_pNode == nullptr)
        m_pLastNode = itWhere.m_pNode;
}

template<class T>
template<class... Args>
inline void list_se<T>::emplace_front(Args&&... args)
{
    list_se_node* pNode = new list_se_node(std::forward<Args>(args)...);
    pNode->pNext        = m_pFirstNode;
    m_pFirstNode        = pNode;
    if (!m_pLastNode)
        m_pLastNode = pNode;

    m_nSize++;
}

template<class T>
template<class... Args>
inline void list_se<T>::emplace(iterator where, Args&&... args)
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

template<class T>
template<class... Args>
inline void list_se<T>::emplace_after(iterator where, Args&&... args)
{
    list_se_node* pNode  = new list_se_node(std::forward<Args>(args)...);
    pNode->pNext         = where.m_pNode->pNext;
    where.m_pNode->pNext = pNode;
    m_nSize++;

    if (pNode->pNext == nullptr)
        m_pLastNode = pNode;
}

template<class T>
template<class... Args>
inline void list_se<T>::emplace_back(Args&&... args)
{
    list_se_node* pNode = new list_se_node(std::forward<Args>(args)...);

    if (m_pLastNode)
        m_pLastNode->pNext = pNode;
    else
        m_pFirstNode = pNode;

    m_pLastNode = pNode;
    m_nSize++;
}

template<class T>
inline void list_se<T>::push_back(const_reference what)
{
    emplace_back(what);
}

template<class T>
inline void list_se<T>::push_front(const_reference what)
{
    emplace_front(what);
}

template<class T>
inline void list_se<T>::pop_back(void)
{
    erase(m_pLastNode);
}

template<class T>
inline void list_se<T>::pop_front(void)
{
    list_se_node* temp = m_pFirstNode;
    m_pFirstNode       = m_pFirstNode->pNext;
    delete temp;
    m_nSize--;

    if (m_pFirstNode == nullptr)
        m_pLastNode = nullptr;
}

template<class T>
inline void list_se<T>::clear(void)
{
    list_se_node* pCurrent = nullptr;
    list_se_node* pNext    = m_pFirstNode;

    while (pNext)
    {
        pCurrent = pNext;
        pNext    = pCurrent->pNext;
        delete pCurrent;
    }

    m_pFirstNode = nullptr;
    m_pLastNode  = nullptr;
    m_nSize      = 0;
}

template<class T>
inline typename list_se<T>::size_type list_se<T>::size(void) const
{
    return m_nSize;
}

template<class T>
inline bool list_se<T>::empty(void) const
{
    return size() == 0;
}

template<class T>
inline typename list_se<T>::iterator list_se<T>::begin(void)
{
    return iterator(m_pFirstNode);
}

template<class T>
inline typename list_se<T>::const_iterator list_se<T>::begin(void) const
{
    return const_iterator(m_pFirstNode);
}

template<class T>
inline typename list_se<T>::iterator list_se<T>::end(void)
{
    return iterator(nullptr);
}

template<class T>
inline typename list_se<T>::const_iterator list_se<T>::end(void) const
{
    return const_iterator(nullptr);
}

template<class T>
inline typename list_se<T>::const_iterator list_se<T>::cbegin(void) const
{
    return const_iterator(m_pFirstNode);
}

template<class T>
inline typename list_se<T>::const_iterator list_se<T>::cend(void) const
{
    return const_iterator(nullptr);
}

template<class T>
inline typename list_se<T>::reference list_se<T>::front(void)
{
    return m_pFirstNode->value;
}

template<class T>
inline typename list_se<T>::reference list_se<T>::back(void)
{
    return m_pLastNode->value;
}

template<class T>
inline typename list_se<T>::const_reference list_se<T>::front(void) const
{
    return m_pFirstNode->value;
}

template<class T>
inline typename list_se<T>::const_reference list_se<T>::back(void) const
{
    return m_pLastNode->value;
}

} // namespace qx
