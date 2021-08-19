/**

    @file      vbo.inl
    @brief     Contains qx::base_vbo class implementation
    @author    Khrapov
    @date      19.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline GLenum base_vbo::GetBufferType(void) const
{
    return GL_ARRAY_BUFFER;
}

inline GLbitfield base_vbo::GetBarrierBit(void) const
{
    return GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT;
}


} // namespace qx
