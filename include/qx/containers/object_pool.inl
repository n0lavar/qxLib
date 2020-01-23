//============================================================================
//
//!\file                       object_pool.inl
//
//!\brief       Contains object_pool class
//!\details     ~
//
//!\author      Khrapov
//!\date        27.07.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================

namespace qx
{

//============================================================================
//!\fn                   object_pool<T>::object_pool
//
//!\brief  object_pool object constructor
//!\param  startSize - start pool size
//!\param  incSize   - increasing pool size step
//!\author Khrapov
//!\date   27.07.2019
//============================================================================
template<class T>
object_pool<T>::object_pool(size_t startSize, size_t incSize)
              : m_nIncreaceSizeStep(incSize)
{
    m_Pool      .resize(startSize);
    m_Indexes   .resize(startSize, UINT_EMPTY_VALUE);
    m_Ids       .reserve(startSize);
}

//============================================================================
//!\fn              object_pool<T>::Emplace<...Args>
//
//!\brief    Add element to the pool
//!\details  due to the fact that OGL calls occur in the RenderComponent
//           object's destructor, we need to avoid this call by simply
//           replacing all arguments into the object.
//           new(&m_Pool[m_nFirstFreeObjInd]) T(args...)    // no destructor call
//           m_Pool[m_nFirstFreeObjInd] = T(args...);       // destructor call
//
//!\param  ...args - arguments to init the element
//!\retval         - element index in the pool
//!\author Khrapov
//!\date   29.07.2019
//============================================================================
template<class T>
template<class ... Args>
size_t object_pool<T>::Emplace(Args&&... args)
{
    size_t nFreeInd = UINT_EMPTY_VALUE;

    // checks pool border
    if (m_nFirstFreeObjInd < m_Pool.size())
    {
        // find free index
        auto itFreeInd = std::find_if(m_Indexes.begin(),
                                      m_Indexes.end(),
                                      [] (size_t val) { return val == UINT_EMPTY_VALUE; });

        DCHECK (itFreeInd != m_Indexes.end())
        {
            // add elem in the pool
            new(&m_Pool[m_nFirstFreeObjInd]) T(args...);
            nFreeInd = std::distance(m_Indexes.begin(), itFreeInd);
            m_Indexes[nFreeInd] = m_nFirstFreeObjInd;

            m_nFirstFreeObjInd++;
        }
    }
    else
    {
        // resize pool
        m_Pool.resize(m_Pool.size() + m_nIncreaceSizeStep);
        m_Indexes.resize(m_Indexes.size() + m_nIncreaceSizeStep, UINT_EMPTY_VALUE);

        new(&m_Pool[m_nFirstFreeObjInd]) T(args...);

        nFreeInd = m_nFirstFreeObjInd;
        m_Indexes[nFreeInd] = m_nFirstFreeObjInd;

        m_nFirstFreeObjInd++;
    }

    m_Ids.push_back(nFreeInd);
    return nFreeInd;
}

//============================================================================
//!\fn                     object_pool<T>::Get
//
//!\brief  Get object by given id
//!\param  id - object's id
//!\author Khrapov
//!\date   7.08.2019
//============================================================================
template<class T>
T & object_pool<T>::Get(size_t id)
{
    return m_Pool[m_Indexes[id]];
}

//============================================================================
//!\fn                      object_pool<T>::Delete
//
//!\brief  Delete element by given id
//!\author Khrapov
//!\date   27.07.2019
//============================================================================
template<class T>
void object_pool<T>::Delete(size_t id)
{
    DCHECK(id < m_Indexes.size() && m_Indexes[id] != UINT_EMPTY_VALUE)
    {
        if (m_nFirstFreeObjInd > 1 && m_nFirstFreeObjInd - 1 != m_Indexes[id])
        {
            m_Pool[m_Indexes[id]] = m_Pool[m_nFirstFreeObjInd - 1];
            m_Indexes[GetId(m_nFirstFreeObjInd - 1)] = m_Indexes[id];
        }
        else
            m_Pool[m_Indexes[id]].~T();

        m_Indexes[id] = UINT_EMPTY_VALUE;
        m_nFirstFreeObjInd--;

        if (auto it = std::find(m_Ids.begin(), m_Ids.end(), id); it != m_Ids.end())
            m_Ids.erase(it);
        else
            ASSERT(0);
    }
}

//============================================================================
//!\fn                   object_pool<T>::GetIdsArray
//
//!\brief  Get array of existing id's
//!\author Khrapov
//!\date   25.08.2019
//============================================================================
template<class T>
const std::vector<size_t>& object_pool<T>::GetIdsArray(void)
{
    return m_Ids;
}

//============================================================================
//!\fn                      object_pool<T>::clear
//
//!\brief  Clear pool
//!\author Khrapov
//!\date   27.07.2019
//============================================================================
template<class T>
void object_pool<T>::clear(void)
{
    m_Pool      .clear();
    m_Indexes   .clear();
    m_Ids       .clear();
    m_nFirstFreeObjInd = 0;
}

//============================================================================
//!\fn                     object_pool<T>::size
//
//!\brief  Get number of filled cells (not allocated)
//!\author Khrapov
//!\date   27.07.2019
//============================================================================
template<class T>
size_t object_pool<T>::size(void)
{
    return m_nFirstFreeObjInd;
}

//============================================================================
//!\fn                      object_pool<T>::begin
//
//!\brief  Get begin iterator
//!\author Khrapov
//!\date   27.07.2019
//============================================================================
template <class T>
object_pool<T>::iterator<T> object_pool<T>::begin()
{
    return iterator<T>(&m_Pool, 0);
}

//============================================================================
//!\fn                       object_pool<T>::end
//
//!\brief  Get end iterator
//!\author Khrapov
//!\date   27.07.2019
//============================================================================
template <class T>
object_pool<T>::iterator<T> object_pool<T>::end()
{
    return iterator<T>(&m_Pool, size());
}

//============================================================================
//!\fn                      object_pool<T>::GetId
//
//!\brief  Get object id by index in the pool
//!\author Khrapov
//!\date   11.08.2019
//============================================================================
template<class T>
size_t object_pool<T>::GetId(size_t ind)
{
    for (size_t i = 0; i < m_Indexes.size(); i++)
    {
        if (m_Indexes[i] == ind)
        {
            return i;
        }
    }
    ASSERT(0);
    return -1;
}

}