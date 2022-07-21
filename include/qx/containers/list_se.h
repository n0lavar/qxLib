/**

    @file      list_se.h
    @brief     Contains qx::list class
    @author    Khrapov
    @date      4.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <initializer_list>
#include <iterator>
#include <utility>

namespace qx
{

/**

    @class   list_se
    @brief   Single ended list class
    @details ~
    @tparam  T - list element type
    @author  Khrapov
    @date    4.02.2020

**/
template<class T>
class list_se
{
    /**
        @struct list_se_node
        @date   9.08.2021
    **/
    struct list_se_node
    {
        list_se_node() = default;

        /**
            @brief  list_se_node object constructor
            @tparam Args - type of variadic args for T construction
            @param  args - variadic args for T construction
        **/
        template<class... Args>
        list_se_node(Args&&... args);

        T             value = T();
        list_se_node* pNext = nullptr;
    };

public:
    class const_iterator;

    /**

        @class   iterator
        @brief   Non-const iterator for list
        @details ~
        @author  Khrapov
        @date    9.08.2021

    **/
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

    public:
        iterator() = default;

        /**
            @brief iterator object constructor
            @param pNode - list node pointer
        **/
        iterator(list_se_node* pNode);

        /**
            @brief  operator*
            @retval - object reference
        **/
        reference operator*();

        /**
            @brief  operator->
            @retval - object pointer
        **/
        pointer operator->();

        /**
            @brief  operator!=
            @param  r - other iterator
            @retval   - true, if objects are not equal
        **/
        bool operator!=(const iterator& r) const;

        /**
            @brief  operator==
            @param  r - other iterator
            @retval   - true, if objects are equal
        **/
        bool operator==(const iterator& r) const;

        /**
            @brief  operator++
            @retval - reference to incremented value
        **/
        iterator& operator++();

        /**
            @brief  operator++
            @param   - stub param
            @retval  - iterator to not incremented value
        **/
        iterator operator++(int);

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

    public:
        const_iterator() = default;

        /**
            @brief const_iterator object constructor
            @param pNode - list node pointer
        **/
        const_iterator(const list_se_node* pNode);

        /**
            @brief const_iterator object constructor
            @param it - non-const iterator
        **/
        const_iterator(const iterator& it);

        /**
            @brief  operator*
            @retval - object reference
        **/
        reference operator*();

        /**
            @brief  operator->
            @retval - object pointer
        **/
        pointer operator->();

        /**
            @brief  operator!=
            @param  r - other iterator
            @retval   - true, if objects are not equal
        **/
        bool operator!=(const const_iterator& r) const;

        /**
            @brief  operator==
            @param  r - other iterator
            @retval   - true, if objects are equal
        **/
        bool operator==(const const_iterator& r) const;

        /**
            @brief  operator++
            @retval reference to incremented value
        **/
        const_iterator& operator++();

        /**
            @brief  operator++
            @param   - stub param
            @retval  - iterator to not incremented value
        **/
        const_iterator operator++(int);

    private:
        const list_se_node* m_pNode = nullptr;
    };

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using size_type       = std::size_t;
    using init_list       = const std::initializer_list<T>&;

public:
    list_se() = default;

    /**
        @brief list_se object constructor
        @param list - other list ref
    **/
    list_se(const list_se& list);

    /**
        @brief  list_se object constructor
        @param  list - other list
    **/
    list_se(list_se&& list) noexcept;

    /**
        @brief list_se object constructor
        @param init - initializer list
    **/
    list_se(init_list init);

    /**
        @brief list_se object constructor
        @param nElements - number of objects
        @param value     - value
    **/
    list_se(size_type nElements, const_reference value);

    /**
        @brief list_se object destructor
    **/
    ~list_se();

    /**
        @brief  operator=
        @param  list - other list ref
        @retval      - this object reference
    **/
    const list_se& operator=(const list_se& list);

    /**
        @brief  operator=
        @param  list - other list
        @retval      - this object reference
    **/
    const list_se& operator=(list_se&& list) noexcept;

    /**
        @brief  operator=
        @param  init - initializer list
        @retval      - this object reference
    **/
    const list_se& operator=(init_list init);

    /**
        @brief      Assign by copying all nodes from another list
        @complexity O(list.size())
        @param      list - other list ref
    **/
    void assign(const list_se& list);

    /**
        @brief      Assign by moving from other list
        @complexity O(1)
        @param      list - other list
    **/
    void assign(list_se&& list) noexcept;

    /**
        @brief      Assign by copying from std::initializer_list
        @complexity O(init.size())
        @param      init - initializer list
    **/
    void assign(init_list init);

    /**
        @brief      Assign by filling with 'count' elements of 'value'
        @complexity O(nElements)
        @param      nElements - number of objects
        @param      value     - value
    **/
    void assign(size_type nElements, const_reference value);

    /**
        @brief      Insert element in list
        @complexity O(size())
        @param      itWhere - iterator, where new elem will be placed
        @param      what    - element
    **/
    void insert(iterator itWhere, const_reference what);

    /**
        @brief      Insert number of elements in list
        @complexity O(size() + nElements)
        @param      itWhere   - iterator, where new elems will be placed
        @param      pWhat     - pointer to first element
        @param      nElements - number of elements
    **/
    void insert(iterator itWhere, const_pointer pWhat, size_type nElements = 1);

    /**
        @brief      Insert element after 'where' iterator
        @complexity O(1)
        @param      itWhere - iterator after which a new element will be inserted
        @param      what    - new element
    **/
    void insert_after(iterator itWhere, const_reference what);

    /**
        @brief      Insert elements after 'where' iterator
        @complexity O(nElements)
        @param      itWhere   - iterator after which a new elements will be inserted
        @param      pWhat     - new element pointer
        @param      nElements - number of elements
    **/
    void insert_after(iterator itWhere, const_pointer pWhat, size_type nElements = 1);

    /**
        @brief      Erase elements from list
        @complexity O(size() + nElements)
        @param      itWhere   - iterator, where erasing starts
                                using "where" after erasing is UB
        @param      nElements - number of elements to erase
    **/
    void erase(iterator itWhere, size_type nElements = 1);

    /**
        @brief      Erase elements from list
        @complexity O(nElements)
        @param      itWhere   - iterator, where erasing starts
                                using "where" after erasing is UB
        @param      nElements - number of elements to erase
    **/
    void erase_after(iterator itWhere, size_type nElements = 1);

    /**
        @brief      Construct and insert element at the front
        @complexity O(1)
        @tparam     Args - type of variadic args for T construction
        @param      args - arguments to construct T
    **/
    template<class... Args>
    void emplace_front(Args&&... args);

    /**
        @brief      Construct and insert element
        @complexity O(size())
        @tparam     Args    - type of variadic args for T construction
        @param      itWhere - iterator, where to insert
        @param      args    - arguments to construct T
    **/
    template<class... Args>
    void emplace(iterator itWhere, Args&&... args);

    /**
        @brief      Construct and insert element
        @complexity O(1)
        @tparam     Args    - type of variadic args for T construction
        @param      itWhere - iterator, after witch inserting starts
        @param      args    - arguments to construct T
    **/
    template<class... Args>
    void emplace_after(iterator itWhere, Args&&... args);

    /**
        @brief      Construct and insert element at the end
        @complexity O(size())
        @tparam     Args - type of variadic args for T construction
        @param      args - arguments to construct T
    **/
    template<class... Args>
    void emplace_back(Args&&... args);

    /**
        @brief      Push back element
        @complexity O(size())
        @param      what - new element
    **/
    void push_back(const_reference what);

    /**
        @brief      Push front element
        @complexity O(1)
        @param      what - new element
    **/
    void push_front(const_reference what);

    /**
        @brief      Pop back element
        @complexity O(size())
    **/
    void pop_back();

    /**
        @brief      Pop front element
        @complexity O(1)
    **/
    void pop_front();

    /**
        @brief      Clear list
        @complexity O(size())
    **/
    void clear();

    /**
        @brief      Get number of elements in list
        @complexity O(1)
        @retval     - number of elements in list
    **/
    size_type size() const;

    /**
        @brief      If list empty
        @complexity O(1)
        @retval     - true, if list is empty
    **/
    bool empty() const;

    /**
        @brief      Return iterator to beginning
        @complexity O(1)
        @retval     - iterator to beginning
    **/
    iterator begin();

    /**
        @brief      Return iterator to beginning
        @complexity O(1)
        @retval     - iterator to beginning
    **/
    const_iterator begin() const;

    /**
        @brief      Return iterator to end
        @complexity O(1)
        @retval     - iterator to end
    **/
    iterator end();

    /**
        @brief      Return iterator to end
        @complexity O(1)
        @retval     - iterator to end
    **/
    const_iterator end() const;

    /**
        @brief      Return const iterator to beginning
        @complexity O(1)
        @retval     - const iterator to beginning
    **/
    const_iterator cbegin() const;

    /**
        @brief      Return const iterator to end
        @complexity O(1)
        @retval     - const iterator to end
    **/
    const_iterator cend() const;

    /**
        @brief      Get first element reference
        @complexity O(1)
        @retval     - first element reference
    **/
    reference front();

    /**
        @brief      Get last element reference
        @complexity O(1)
        @retval     - last element reference
    **/
    reference back();

    /**
        @brief      Get first element const reference
        @complexity O(1)
        @retval     - first element const reference
    **/
    const_reference front() const;

    /**
        @brief      Get last element const reference
        @complexity O(1)
        @retval     - last element const reference
    **/
    const_reference back() const;


private:
    list_se_node* m_pFirstNode = nullptr;
    list_se_node* m_pLastNode  = nullptr;
    size_type     m_nSize      = 0;
};

template<class T>
using list = list_se<T>;

} // namespace qx

#include <qx/containers/list_se.inl>
