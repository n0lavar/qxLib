/**

    @file      ubo.inl
    @author    Khrapov
    @date      9.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline GLint base_ubo::GetMaxSize() const
{
    GLint ret;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &ret);
    return ret;
}

inline GLenum base_ubo::GetBufferType() const
{
    return GL_UNIFORM_BUFFER;
}

inline GLbitfield base_ubo::GetBarrierBit() const
{
    return GL_UNIFORM_BARRIER_BIT;
}

} // namespace qx
