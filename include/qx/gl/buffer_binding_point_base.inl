/**

    @file      buffer_binding_point_base.inl
    @brief     Contains qx::buffer_binding_point_base class implementation
    @author    Khrapov
    @date      10.07.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void buffer_binding_point_base::BindBase(GLuint nIndex)
{
    glBindBufferBase(this->GetBufferType(), nIndex, this->GetBufferName());
}

} // namespace qx
