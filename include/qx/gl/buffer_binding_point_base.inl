//==============================================================================
//
//!\file                 buffer_binding_point_base.inl
//
//!\brief       Contains buffer_binding_point_base class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.02.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn            qx::buffer_binding_point_base<COPYBLE>::BindBase
//
//!\brief  Bind a buffer object to an indexed buffer target from shader
//!\param  nIndex - index
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void buffer_binding_point_base<COPYBLE>::BindBase(GLuint nIndex)
{
    glBindBufferBase(
        this->GetBufferType(),
        nIndex,
        this->GetBufferName());
}

}
