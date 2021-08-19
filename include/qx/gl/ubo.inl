//==============================================================================
//
//!\file                        ubo.inl
//
//!\brief       Contains qx::base_ubo class implementation
//!\details     ~
//
//!\author      Khrapov
//!\date        9.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

inline GLint base_ubo::GetMaxSize(void) const
{
    GLint ret;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &ret);
    return ret;
}

inline GLenum base_ubo::GetBufferType(void) const
{
    return GL_UNIFORM_BUFFER;
}

inline GLbitfield base_ubo::GetBarrierBit(void) const
{
    return GL_UNIFORM_BARRIER_BIT;
}

} // namespace qx
