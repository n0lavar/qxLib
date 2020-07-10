//==============================================================================
//
//!\file                           vao.inl
//
//!\brief       Vertex array object classes: vao and copyble_vao
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
//!\fn                    base_vao<COPYBLE>::~base_vao
//
//!\brief  vao object destructor
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline base_vao<COPYBLE>::~base_vao(void)
{
    Delete();
}

//==============================================================================
//!\fn                    base_vao<COPYBLE>::Generate
//
//!\brief  Generate VAO. Expensive operation.
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_vao<COPYBLE>::Generate(void)
{
    glGenVertexArrays(1, &m_nVAO);
}

//==============================================================================
//!\fn                     base_vao<COPYBLE>::Delete
//
//!\brief  Delete VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_vao<COPYBLE>::Delete(void)
{
    if constexpr (!COPYBLE)
    {
        if (m_nVAO != UINT_EMPTY_VALUE)
        {
            glDeleteVertexArrays(1, &m_nVAO);
            m_nVAO = UINT_EMPTY_VALUE;
        }
    }
}

//==============================================================================
//!\fn                      base_vao<COPYBLE>::Bind
//
//!\brief  Bind VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_vao<COPYBLE>::Bind(void) const
{
    glBindVertexArray(m_nVAO);
}

//==============================================================================
//!\fn                     base_vao<COPYBLE>::Unbind
//
//!\brief  Unbind VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_vao<COPYBLE>::Unbind(void) const
{
    glBindVertexArray(0);
}

//==============================================================================
//!\fn             base_vao<COPYBLE>::EnableVertexArrtibArray
//
//!\brief  Enable a generic vertex attribute array
//!\param  nIndex - array index in VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_vao<COPYBLE>::EnableVertexArrtibArray(GLuint nIndex)
{
    glEnableVertexAttribArray(nIndex);
}

//==============================================================================
//!\fn            base_vao<COPYBLE>::DisableVertexArrtibArray
//
//!\brief  Disable a generic vertex attribute array
//!\param  nIndex - array index in VAO
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_vao<COPYBLE>::DisableVertexArrtibArray(GLuint nIndex)
{
    glDisableVertexAttribArray(nIndex);
}

//==============================================================================
//!\fn               base_vao<COPYBLE>::VertexAttribPointer
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
//!\param  nOffset     - offset of the first component of the first generic 
//                       vertex attribute in the array in the data store of 
//                       the buffer currently bound to the GL_ARRAY_BUFFER target
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_vao<COPYBLE>::VertexAttribPointer(
    GLuint       nIndex,
    GLint        nSize, 
    GLenum       eType, 
    GLboolean    bNormalized, 
    GLsizei      nStride, 
    size_t       nOffset)
{
    glVertexAttribPointer(nIndex, nSize, eType, bNormalized, nStride, (GLvoid*)(nOffset));
}

}