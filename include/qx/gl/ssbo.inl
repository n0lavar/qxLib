/**

    @file      ssbo.inl
    @author    Khrapov
    @date      18.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline GLint base_ssbo::GetMaxSize(void) const
{
    GLint ret;
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &ret);
    return ret;
}

inline GLenum base_ssbo::GetBufferType(void) const
{
    return GL_SHADER_STORAGE_BUFFER;
}
inline GLbitfield base_ssbo::GetBarrierBit(void) const
{
    return GL_SHADER_STORAGE_BARRIER_BIT;
}

} // namespace qx
