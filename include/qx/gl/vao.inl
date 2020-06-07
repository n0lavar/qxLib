//==============================================================================
//
//!\file                           vao.inl
//
//!\brief       Contains vao class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx::gl
{

//==============================================================================
//!\fn                           vao::~vao
//
//!\brief  vao object destructor
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline vao::~vao(void)
{
    Delete();
}

//==============================================================================
//!\fn                          vao::Generate
//
//!\brief  Generate VAO. Expensive operation.
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void vao::Generate(void)
{
    glGenVertexArrays(1, &m_nVAO);
}

//==============================================================================
//!\fn                           vao::Delete
//
//!\brief  Delete VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void vao::Delete(void)
{
    if (m_nVAO != UINT_EMPTY_VALUE)
        glDeleteVertexArrays(1, &m_nVAO);
}

//==============================================================================
//!\fn                            vao::Bind
//
//!\brief  Bind VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void vao::Bind(void) const
{
    glBindVertexArray(m_nVAO);
}

//==============================================================================
//!\fn                           vao::Unbind
//
//!\brief  Unbind VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void vao::Unbind(void) const
{
    glBindVertexArray(0);
}

//==============================================================================
//!\fn                  vao::EnableVertexArrtibArray
//
//!\brief  Enable a generic vertex attribute array
//!\param  nIndex - array index in VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void vao::EnableVertexArrtibArray(GLuint nIndex)
{
    glEnableVertexAttribArray(nIndex);
}

//==============================================================================
//!\fn                  vao::DisableVertexArrtibArray
//
//!\brief  Disable a generic vertex attribute array
//!\param  nIndex - array index in VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void vao::DisableVertexArrtibArray(GLuint nIndex)
{
    glDisableVertexAttribArray(nIndex);
}

//==============================================================================
//!\fn                    vao::VertexAttribPointer
//
//!\brief  Define an array of generic vertex attribute data
//!\param  nIndex      - index of the generic vertex attribute to be modified
//!\param  nSize       - number of components per generic vertex attribute. 
//                       Must be 1, 2, 3, 4
//!\param  eType       - data type of each component in the array
//!\param  bNormalized - specifies whether fixed-point data values should be 
//                       normalized or converted directly as fixed-point values
//!\param  nStride     - byte offset between consecutive generic vertex attributes
//!\param  pData       - a offset of the first component of the first generic 
//                       vertex attribute in the array in the data store of 
//                       the buffer currently bound to the GL_ARRAY_BUFFER target
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline void vao::VertexAttribPointer(GLuint       nIndex,
                                     GLint        nSize, 
                                     GLenum       eType, 
                                     GLboolean    bNormalized, 
                                     GLsizei      nStride, 
                                     size_t       nOffset)
{
    glVertexAttribPointer(nIndex, nSize, eType, bNormalized, nStride, (GLvoid*)(nOffset));
}

}