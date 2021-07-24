//==============================================================================
//
//!\file                           vao.inl
//
//!\brief       Contains qx::base_vao class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                       qx::base_vao::~base_vao
//
//!\brief  vao object destructor
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline base_vao::~base_vao(void)
{
    Delete();
}

//==============================================================================
//!\fn                       qx::base_vao::Generate
//
//!\brief  Generate VAO. Expensive operation.
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void base_vao::Generate(void)
{
    glGenVertexArrays(1, &m_nVAO);
}

//==============================================================================
//!\fn                        qx::base_vao::Delete
//
//!\brief  Delete VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void base_vao::Delete(void)
{
    if (m_nVAO != std::numeric_limits<GLuint>::max())
    {
        glDeleteVertexArrays(1, &m_nVAO);
        m_nVAO = std::numeric_limits<GLuint>::max();
    }
}

//==============================================================================
//!\fn                         qx::base_vao::Bind
//
//!\brief  Bind VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void base_vao::Bind(void) const
{
    glBindVertexArray(m_nVAO);
}

//==============================================================================
//!\fn                        qx::base_vao::Unbind
//
//!\brief  Unbind VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void base_vao::Unbind(void) const
{
    glBindVertexArray(0);
}

//==============================================================================
//!\fn                qx::base_vao::EnableVertexArrtibArray
//
//!\brief  Enable a generic vertex attribute array
//!\param  nIndex - array index in VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void base_vao::EnableVertexArrtibArray(size_t nIndex)
{
    glEnableVertexAttribArray(static_cast<GLuint>(nIndex));
}

//==============================================================================
//!\fn               qx::base_vao::DisableVertexArrtibArray
//
//!\brief  Disable a generic vertex attribute array
//!\param  nIndex - array index in VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void base_vao::DisableVertexArrtibArray(size_t nIndex)
{
    glDisableVertexAttribArray(static_cast<GLuint>(nIndex));
}

//==============================================================================
//!\fn                  qx::base_vao::VertexAttribPointer
//
//!\brief  Define an array of generic vertex attribute data
//!\param  nIndex      - index of the generic vertex attribute to be modified
//!\param  nSize       - number of components per generic vertex attribute.
//                       Must be 1, 2, 3, 4
//!\param  eType       - data type of each component in the array
//!\param  bNormalized - specifies whether fixed-point data values should be
//                       normalized or converted directly as fixed-point values
//!\param  nStride     - byte offset between consecutive generic vertex attributes
//!\param  nOffset     - offset of the first component of the first generic
//                       vertex attribute in the array in the data store of
//                       the buffer currently bound to the GL_ARRAY_BUFFER target
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void base_vao::VertexAttribPointer(
    size_t       nIndex,
    GLint        nSize,
    GLenum       eType,
    GLboolean    bNormalized,
    GLsizei      nStride,
    size_t       nOffset)
{
    glVertexAttribPointer(
        static_cast<GLuint>(nIndex),
        nSize,
        eType,
        bNormalized,
        nStride,
        reinterpret_cast<GLvoid*>(nOffset));
}

}
