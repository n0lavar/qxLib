//==============================================================================
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
//==============================================================================

namespace qx::gl
{

//==============================================================================
//!\fn                          ubo::ubo
//
//!\brief  ubo object constructor
//!\param  nBindingPoint - buffer binding point from the shader
//!\param  szUBO         - buffer size
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
inline ubo::ubo(GLuint nBindingPoint, GLsizeiptr szUBO)
{
    Init(szUBO, nBindingPoint);
}

//==============================================================================
//!\fn                          ubo::Init
//
//!\brief  Init UBO
//!\param  nBindingPoint - buffer binding point from the shader
//!\param  szUBO         - buffer size
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
inline void ubo::Init(GLuint nBindingPoint, GLsizeiptr szUBO)
{
    Generate();
    Bind();
    Update(szUBO, NULL, GL_STREAM_DRAW);
    BindBase(nBindingPoint);
}

//==============================================================================
//!\fn                       ubo::GetMaxSize
//
//!\brief  Get max UBO size with current GPU
//!\retval max UBO size with current GPU
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
inline GLint ubo::GetMaxSize(void)
{
    GLint ret;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &ret);
    return ret;
}

}