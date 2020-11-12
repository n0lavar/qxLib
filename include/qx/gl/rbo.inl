//==============================================================================
//
//!\file                           rbo.inl
//
//!\brief       Render buffer object classes: rbo and copyble_rbo
//!\details     ~
//
//!\author      Khrapov
//!\date        20.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                    qx::base_rbo<COPYBLE>::Init
//
//!\brief  Init RBO with width and height
//!\param  nWidth        - width
//!\param  nHeight       - height
//!\param  nMultisamples - samples number, 0 - disable
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_rbo<COPYBLE>::Init(GLsizei nWidth, GLsizei nHeight, GLsizei nMultisamples)
{
    // create a renderbuffer object for depth and stencil attachment
    Generate();
    Bind();

    // use a single renderbuffer object for both a depth and stencil buffer.
    if (nMultisamples > 0)
    {
        glRenderbufferStorageMultisample(
            GL_RENDERBUFFER,
            nMultisamples,
            GL_DEPTH24_STENCIL8,
            nWidth,
            nHeight);
    }
    else
    {
        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH24_STENCIL8,
            nWidth,
            nHeight);
    }

    Unbind();
}

//==============================================================================
//!\fn                  qx::base_rbo<COPYBLE>::Generate
//
//!\brief  Generate buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_rbo<COPYBLE>::Generate(void)
{
    glGenRenderbuffers(1, &m_nBuffer);
}

//==============================================================================
//!\fn                   qx::base_rbo<COPYBLE>::Delete
//
//!\brief  Delete buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_rbo<COPYBLE>::Delete(void)
{
    if constexpr (!COPYBLE)
    {
        if (m_nBuffer != std::numeric_limits<GLuint>::max())
        {
            glDeleteRenderbuffers(1, &m_nBuffer);
            m_nBuffer = std::numeric_limits<GLuint>::max();
        }
    }
}

//==============================================================================
//!\fn                    qx::base_rbo<COPYBLE>::Bind
//
//!\brief  Bind buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_rbo<COPYBLE>::Bind(void) const
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_nBuffer);
}

//==============================================================================
//!\fn                   qx::base_rbo<COPYBLE>::Unbind
//
//!\brief  Unbind buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
template<bool COPYBLE>
inline void base_rbo<COPYBLE>::Unbind(void) const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

}
