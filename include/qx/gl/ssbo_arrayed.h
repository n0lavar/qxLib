//============================================================================
//
//!\file                       ssbo_arrayed.h
//
//!\brief       Contains ssbo_arrayed class
//!\details     ~
//
//!\author      Khrapov
//!\date        18.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <qx/gl/ssbo.h>

namespace qx::gl
{

//============================================================================
//
//!\class                      ssbo_arrayed<T>
//
//!\brief   SSBO with array of T 
//!\details expacted shader struct:
//
//          layout(std430, binding = N) buffer BufferName
//          {
//              // header is 32 bytes
//              uint	index;
//              float   _padding[7];
//          
//              T        modelData[];
//          };
//
//!\author  Khrapov
//!\date    18.01.2020
//
//============================================================================
template<typename T>
class ssbo_arrayed : protected ssbo
{
public:
            ssbo_arrayed    (void) = default;
            ssbo_arrayed    (GLuint             nBindingPoint,
                             size_t             nMaxObjects);

    void    Init            (GLuint             nBindingPoint,
                             size_t             nMaxObjects);
    size_t  AddElement      (const T          * pData);
    void    UpdateElem      (size_t             nIndex,
                             const T          * pData);
    void    RemoveElem      (size_t             nIndex);
    void    SetIndex        (size_t             nIndex);
    size_t  GetUsedSize     (void)                                  const;

private:
    size_t m_ArrayFirstFree = 0;
    std::vector<GLuint> m_Indexes;
};

template<typename T> inline size_t ssbo_arrayed<T>::GetUsedSize(void) const { return m_ArrayFirstFree; }

}

#include <qx/gl/ssbo_arrayed.inl>
