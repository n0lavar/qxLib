//==============================================================================
//
//!\file                          ssbo.inl
//
//!\brief       Shader storage buffer object classes: ssbo and copyble_ssbo
//!\details     ~
//
//!\author      Khrapov
//!\date        18.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                      base_ssbo<COPYBLE>::Init
//
//!\brief  Init SSBO
//!\param  nBindingPoint - shader binding point
//!\param  nSize         - data size
//!\param  pData         - data pointer
//!\author Khrapov
//!\date   18.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_ssbo<COPYBLE>::Init(GLuint nBindingPoint, GLsizeiptr nSize, const void * pData)
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
