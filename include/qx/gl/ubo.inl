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
//!\fn                 qx::base_ubo<COPYBLE>::GetMaxSize
//
//!\brief  Get max UBO size
//!\retval max UBO size
//!\author Khrapov
//!\date   9.01.2020
//==============================================================================
template<bool COPYBLE>
inline GLint base_ubo<COPYBLE>::GetMaxSize(void) const
{
    GLint ret;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &ret);
    return ret;
}

}
