//==============================================================================
//
//!\file                          ssbo.inl
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        18.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx::gl
{

//==============================================================================
//!\fn                           ssbo::ssbo
//
//!\brief  ssbo object constructor
//!\param  nBindingPoint - shader binding point
//!\param  nSize         - data size
//!\param  pData         - data pointer
//!\author Khrapov
//!\date   18.01.2020
//==============================================================================
inline ssbo::ssbo(GLuint nBindingPoint, GLsizeiptr nSize, const void * pData)
{
    Init(nBindingPoint, nSize, pData);
}

//==============================================================================
//!\fn                           ssbo::Init
//
//!\brief  Init SSBO
//!\param  nBindingPoint - shader binding point
//!\param  nSize         - data size
//!\param  pData         - data pointer
//!\author Khrapov
//!\date   18.01.2020
//==============================================================================
inline void ssbo::Init(GLuint nBindingPoint, GLsizeiptr nSize, const void * pData)
{
    // minimum possible size to allocate
    CHECK(nSize >= GL_BUFFER_DATA_SIZE)
    {
        Delete();

        Generate();
        Bind();
        Update(nSize, pData, GL_STATIC_DRAW);
        BindBase(nBindingPoint);
    }
}

}