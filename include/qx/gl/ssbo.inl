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
//!\fn                    qx::base_ssbo<COPYBLE>::Init
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
    this->Delete();

    this->Generate();
    this->Bind();
    this->Update(nSize, pData, GL_DYNAMIC_DRAW);
    this->BindBase(nBindingPoint);
    this->Unbind();
}

}
