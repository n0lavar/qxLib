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
//!\fn                 qx::base_ssbo<COPYBLE>::GetMaxSize
//
//!\brief  Get max SSBO size
//!\retval max SSBO size
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
template <bool COPYBLE> inline GLint base_ssbo<COPYBLE>::GetMaxSize(void) const
{
    GLint ret;
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &ret);
    return ret;
}

}
