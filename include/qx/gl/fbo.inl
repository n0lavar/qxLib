//==============================================================================
//
//!\file                           fbo.inl
//
//!\brief       Contains qx::base_fbo class
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
//!\fn                       qx::base_fbo::~base_fbo
//
//!\brief  base_fbo object destructor
//!\author Khrapov
//!\date   10.07.2020
//==============================================================================
inline base_fbo::~base_fbo(void)
{
    Delete();
}

//==============================================================================
//!\fn                       qx::base_fbo::Generate
//
//!\brief  Generate buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void base_fbo::Generate(void)
{
    glGenFramebuffers(1, &m_nBuffer);
}

//==============================================================================
//!\fn                        qx::base_fbo::Delete
//
//!\brief  Delete buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void base_fbo::Delete(void)
{
    if (m_nBuffer != std::numeric_limits<GLuint>::max())
    {
        glDeleteFramebuffers(1, &m_nBuffer);
        m_nBuffer = std::numeric_limits<GLuint>::max();
    }
}

//==============================================================================
//!\fn                         qx::base_fbo::Bind
//
//!\brief  Bind buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void base_fbo::Bind(void) const
{
    glBindFramebuffer(m_nTarget, m_nBuffer);
}

//==============================================================================
//!\fn                        qx::base_fbo::Unbind
//
//!\brief  Unbind buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void base_fbo::Unbind(void) const
{
    glBindFramebuffer(m_nTarget, 0);
}

//==============================================================================
//!\fn                       qx::base_fbo::SetTarget
//
//!\brief  Set target type
//!\param  target - GL_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER or GL_READ_FRAMEBUFFER
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void base_fbo::SetTarget(GLenum target)
{
    m_nTarget = target;
}

//==============================================================================
//!\fn                     qx::base_fbo::AttachRBO
//
//!\brief  Attach RBO th FRO
//!\param  rbo - render buffer object
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void base_fbo::AttachRBO(const base_rbo& rbo)
{
    glFramebufferRenderbuffer(
        m_nTarget,
        rbo.GetAttachmentType(),
        GL_RENDERBUFFER,
        rbo.GetBufferName());
}

//==============================================================================
//!\fn                     qx::base_fbo::AttachTexture2D
//
//!\brief  Attache a single face of a specific MIP level to FBO
//!\param  attachment   - attachment point of the framebuffer
//!\param  texture      - fbo texture
//!\param  nMipmapLevel - mipmap level of texture
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void base_fbo::AttachTexture2D(
    GLenum              attachment,
    const base_texture& texture,
    GLint               nMipmapLevel)
{
    glFramebufferTexture2D(
        m_nTarget,
        attachment,
        texture.GetTarget(),
        texture.GetBufferName(),
        nMipmapLevel);
}

//==============================================================================
//!\fn                  qx::base_fbo::AttachTexture2D
//
//!\brief  Attache all cube map faces of a specific MIP level
//         as an array of images (layered framebuffer)
//!\param  attachment   - attachment point of the framebuffer
//!\param  texture      - fbo texture
//!\param  nMipmapLevel - mipmap level of texture
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void base_fbo::AttachTexture(
    GLenum              attachment,
    const base_texture& texture,
    GLint               nMipmapLevel)
{
    glFramebufferTexture(
        m_nTarget,
        attachment,
        texture.GetBufferName(),
        nMipmapLevel);
}

//==============================================================================
//!\fn                      qx::base_fbo::CheckStatus
//
//!\brief  check framebuffer status
//!\author Khrapov
//!\date   26.06.2020
//==============================================================================
inline void base_fbo::CheckStatus(void) const
{
    if (const auto eStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        eStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        char const * pszErrorMsg = nullptr;
        switch (eStatus)
        {
        case GL_FRAMEBUFFER_UNDEFINED:
            pszErrorMsg =
                "The specified framebuffer is the default read or draw"
                "framebuffer, but the default framebuffer does not exist.";
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            pszErrorMsg =
                "Any of the framebuffer attachment points "
                "are framebuffer incomplete.";
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            pszErrorMsg =
                "The framebuffer does not have at least one "
                "image attached to it.";
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            pszErrorMsg =
                "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE "
                "for any color attachment point(s) named by GL_DRAW_BUFFERi.";
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            pszErrorMsg =
                "GL_READ_BUFFER is not GL_NONE and the value of "
                "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE "
                "for the color attachment point named by GL_READ_BUFFER.";
            break;

        case GL_FRAMEBUFFER_UNSUPPORTED:
            pszErrorMsg =
                "The combination of internal formats of the attached "
                "images violates an implementation - dependent set of restrictions.";
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            pszErrorMsg =
                "The value of GL_RENDERBUFFER_SAMPLES is not the "
                "same for all attached renderbuffers; if the value of "
                "GL_TEXTURE_SAMPLES is the not same for all attached textures; "
                "or , if the attached images are a mix of renderbuffersand textures, "
                "the value of GL_RENDERBUFFER_SAMPLES does not match the value "
                "of GL_TEXTURE_SAMPLES. Also returned if the value "
                "of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all "
                "attached textures; or , if the attached images are a mix "
                "of renderbuffersand textures, the value of "
                "GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures.";
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            pszErrorMsg =
                "Any framebuffer attachment is layered, and any "
                "populated attachment is not layered, or if all populated "
                "color attachments are not from textures of the same target.";
            break;

        default:
            pszErrorMsg = "Unknown error";
            break;
        }

        ASSERT_MSG(0,
                   "Framebuffer status is not complete: Status: %d, Error: %s",
                   eStatus,
                   pszErrorMsg);
    }
}

}
