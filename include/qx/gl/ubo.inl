//============================================================================
//
//!\file                        ubo.inl
//
//!\brief       Uniform buffer object class
//!\details     ~
//
//!\author      Khrapov
//!\date        9.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================

namespace qx::gl
{

//============================================================================
//!\fn                          ubo::ubo
//
//!\brief  ubo object constructor
//!\param  szUBO         - buffer size
//!\param  nBindingPoint - buffer binding point from the shader
//!\author Khrapov
//!\date   9.01.2020
//============================================================================
inline ubo::ubo(GLsizeiptr szUBO, GLuint nBindingPoint)
{
    Init(szUBO, nBindingPoint);
}

//============================================================================
//!\fn                          ubo::Init
//
//!\brief  Init UBO
//!\param  szUBO         - buffer size
//!\param  nBindingPoint - buffer binding point from the shader
//!\author Khrapov
//!\date   9.01.2020
//============================================================================
inline void ubo::Init(GLsizeiptr szUBO, GLuint nBindingPoint)
{
    Generate();
    Update(szUBO, NULL, GL_STREAM_DRAW);
    BindBase(nBindingPoint);
}

}