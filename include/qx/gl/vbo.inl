/**

    @file      vbo.inl
    @author    Khrapov
    @date      19.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline GLenum base_vbo::GetBufferType() const
{
    return GL_ARRAY_BUFFER;
}

inline GLbitfield base_vbo::GetBarrierBit() const
{
    return GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT;
}


} // namespace qx
