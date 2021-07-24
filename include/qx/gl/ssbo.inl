//==============================================================================
//
//!\file                          ssbo.inl
//
//!\brief       Contains qx::base_ssbo class
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
//!\fn                      qx::base_ssbo::GetMaxSize
//
//!\brief  Get max SSBO size
//!\retval max SSBO size
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
inline GLint base_ssbo::GetMaxSize(void) const
{
    GLint ret;
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &ret);
    return ret;
}

}
