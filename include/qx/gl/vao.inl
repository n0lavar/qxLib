/**

    @file      vao.inl
    @brief     Contains qx::base_vao class implementation
    @author    Khrapov
    @date      19.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_vao::~base_vao(void)
{
    if (m_nVAO != std::numeric_limits<GLuint>::max())
    {
        glDeleteVertexArrays(1, &m_nVAO);
        m_nVAO = std::numeric_limits<GLuint>::max();
    }
}

inline void base_vao::Generate(void)
{
    glGenVertexArrays(1, &m_nVAO);
}

inline void base_vao::Bind(void) const
{
    glBindVertexArray(m_nVAO);
}

inline void base_vao::Unbind(void) const
{
    glBindVertexArray(0);
}

inline GLuint base_vao::GetBufferName(void) const
{
    return m_nVAO;
}

inline bool base_vao::IsGenerated(void) const
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
