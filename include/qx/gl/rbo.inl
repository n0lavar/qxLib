//============================================================================
//
//!\file                           rbo.inl
//
//!\brief       Contains rbo class
//!\details     ~
//
//!\author      Khrapov
//!\date        20.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================

namespace qx::gl
{

//============================================================================
//!\fn                            rbo::Init
//
//!\brief  Init RBO with width and height
//!\param  nWidth  - width
//!\param  nHeight - height
//!\author Khrapov
//!\date   20.01.2020
//============================================================================
inline void rbo::Init(GLsizei nWidth, GLsizei nHeight)
{
    // create a renderbuffer object for depth and stencil attachment
    Generate();
    Bind();

    // use a single renderbuffer object for both a depth AND stencil buffer.
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, nWidth, nHeight);
}

//============================================================================
//!\fn                          rbo::Generate
//
//!\brief  Generate buffer
//!\author Khrapov
//!\date   20.01.2020
//============================================================================
inline void rbo::Generate(void)
{
    glGenRenderbuffers(1, &m_nBuffer);
}

//============================================================================
//!\fn                           rbo::Delete
//
//!\brief  Delete buffer
//!\author Khrapov
//!\date   20.01.2020
//============================================================================
inline void rbo::Delete(void)
{
    glDeleteRenderbuffers(1, &m_nBuffer);
}

//============================================================================
//!\fn                            rbo::Bind
//
//!\brief  Bind buffer
//!\author Khrapov
//!\date   20.01.2020
//============================================================================
inline void rbo::Bind(void) const
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_nBuffer);
}

//============================================================================
//!\fn                           rbo::Unbind
//
//!\brief  Unbind buffer
//!\author Khrapov
//!\date   20.01.2020
//============================================================================
inline void rbo::Unbind(void) const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

}