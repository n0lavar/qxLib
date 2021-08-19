/**

    @file      ebo.inl
    @brief     Contains qx::base_ebo class implementation
    @author    Khrapov
    @date      19.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline GLenum base_ebo::GetBufferType(void) const
{
    return GL_ELEMENT_ARRAY_BUFFER;
}
inline GLbitfield base_ebo::GetBarrierBit(void) const
{
    return GL_ELEMENT_ARRAY_BARRIER_BIT;
}

} // namespace qx
