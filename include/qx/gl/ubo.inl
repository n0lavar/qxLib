//==============================================================================
//
//!\file                        ubo.inl
//
//!\brief       Contains qx::base_ubo class
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
//!\fn                      qx::base_ubo::GetMaxSize
//
//!\brief  Get max UBO size
//!\retval max UBO size
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
inline GLint base_ubo::GetMaxSize(void) const
{
    GLint ret;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &ret);
    return ret;
}

}
