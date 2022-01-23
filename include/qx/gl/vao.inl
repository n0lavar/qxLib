/**

    @file      vao.inl
    @author    Khrapov
    @date      19.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_vao::~base_vao()
{
    if (m_nVAO != std::numeric_limits<GLuint>::max())
    {
        glDeleteVertexArrays(1, &m_nVAO);
        m_nVAO = std::numeric_limits<GLuint>::max();
    }
}

inline void base_vao::Generate()
{
    glGenVertexArrays(1, &m_nVAO);
}

inline void base_vao::Bind() const
{
    glBindVertexArray(m_nVAO);
}

inline void base_vao::Unbind() const
{
    glBindVertexArray(0);
}

inline GLuint base_vao::GetBufferName() const
{
    return m_nVAO;
}

inline bool base_vao::IsGenerated() const
{
    return m_nVAO != std::numeric_limits<GLuint>::max();
};

inline void base_vao::EnableVertexArrtibArray(size_t nIndex)
{
    glEnableVertexAttribArray(static_cast<GLuint>(nIndex));
}

inline void base_vao::DisableVertexArrtibArray(size_t nIndex)
{
    glDisableVertexAttribArray(static_cast<GLuint>(nIndex));
}

inline void base_vao::VertexAttribPointer(
    size_t    nIndex,
    GLint     nSize,
    GLenum    eType,
    GLboolean bNormalized,
    GLsizei   nStride,
    size_t    nOffset)
{
    glVertexAttribPointer(
        static_cast<GLuint>(nIndex),
        nSize,
        eType,
        bNormalized,
        nStride,
        reinterpret_cast<GLvoid*>(nOffset));
}

} // namespace qx
