//==============================================================================
//
//!\file                        ubo.inl
//
//!\brief       Uniform buffer object classes: ubo and copyble_ubo
//!\details     ~
//
//!\author      Khrapov
//!\date        9.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                      base_ubo<COPYBLE>::Init
//
//!\brief  Init UBO
//!\param  nBindingPoint - buffer binding point from the shader
//!\param  szUBO         - buffer size
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_ubo<COPYBLE>::Init(GLuint nBindingPoint, GLsizeiptr szUBO)
{
    Generate();
    Bind();
    Update(szUBO, NULL, GL_STREAM_DRAW);
    BindBase(nBindingPoint);
}

//==============================================================================
//!\fn                   base_ubo<COPYBLE>::GetMaxSize
//
//!\brief  Get max UBO size with current GPU
//!\retval max UBO size with current GPU
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
template<bool COPYBLE>
inline GLint base_ubo<COPYBLE>::GetMaxSize(void)
{
    GLint ret;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &ret);
    return ret;
}

}
