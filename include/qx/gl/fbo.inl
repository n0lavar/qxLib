/**

    @file      fbo.inl
    @author    Khrapov
    @date      19.08.2021
    @copyright � Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_fbo::~base_fbo()
{
    if (m_nBuffer != std::numeric_limits<GLuint>::max())
    {
        glDeleteFramebuffers(1, &m_nBuffer);
        m_nBuffer = std::numeric_limits<GLuint>::max();
    }
}

inline void base_fbo::Generate()
{
    glGenFramebuffers(1, &m_nBuffer);
}

inline void base_fbo::Bind() const
{
    glBindFramebuffer(m_nTarget, m_nBuffer);
}

inline void base_fbo::Unbind() const
{
    glBindFramebuffer(m_nTarget, 0);
}

inline GLuint base_fbo::GetBufferName() const
{
    return m_nBuffer;
}

inline bool base_fbo::IsGenerated() const
{
    return m_nBuffer != std::numeric_limits<GLuint>::max();
}

inline void base_fbo::SetTarget(GLenum target)
{
    m_nTarget = target;
}

inline void base_fbo::AttachRBO(const base_rbo& rbo)
{
    glFramebufferRenderbuffer(m_nTarget, rbo.GetAttachmentType(), GL_RENDERBUFFER, rbo.GetBufferName());
}

inline void base_fbo::AttachTexture2D(GLenum attachment, const base_texture& texture, GLint nMipmapLevel)
{
    glFramebufferTexture2D(m_nTarget, attachment, texture.GetTarget(), texture.GetBufferName(), nMipmapLevel);
}

inline void base_fbo::AttachTexture(GLenum attachment, const base_texture& texture, GLint nMipmapLevel)
{
    glFramebufferTexture(m_nTarget, attachment, texture.GetBufferName(), nMipmapLevel);
}

inline qx::string_view base_fbo::CheckStatus() const
{
    qx::string_view svErrorMsg;
    if (const auto eStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER); eStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        switch (eStatus)
        {
        case GL_FRAMEBUFFER_UNDEFINED:
            svErrorMsg = QX_TEXT(
                "The specified framebuffer is the default read or draw"
                "framebuffer, but the default framebuffer does not exist.");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            svErrorMsg = QX_TEXT(
                "Any of the framebuffer attachment points "
                "are framebuffer incomplete.");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            svErrorMsg = QX_TEXT(
                "The framebuffer does not have at least one "
                "image attached to it.");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            svErrorMsg = QX_TEXT(
                "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE "
                "for any color attachment point(s) named by GL_DRAW_BUFFERi.");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            svErrorMsg = QX_TEXT(
                "GL_READ_BUFFER is not GL_NONE and the value of "
                "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE "
                "for the color attachment point named by GL_READ_BUFFER.");
            break;

        case GL_FRAMEBUFFER_UNSUPPORTED:
            svErrorMsg = QX_TEXT(
                "The combination of internal formats of the attached "
                "images violates an implementation - dependent set of "
                "restrictions.");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            svErrorMsg = QX_TEXT(
                "The value of GL_RENDERBUFFER_SAMPLES is not the "
                "same for all attached renderbuffers; if the value of "
                "GL_TEXTURE_SAMPLES is the not same for all attached textures; "
                "or , if the attached images are a mix of renderbuffersand "
                "textures, "
                "the value of GL_RENDERBUFFER_SAMPLES does not match the value "
                "of GL_TEXTURE_SAMPLES. Also returned if the value "
                "of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all "
                "attached textures; or , if the attached images are a mix "
                "of renderbuffersand textures, the value of "
                "GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all "
                "attached textures.");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            svErrorMsg = QX_TEXT(
                "Any framebuffer attachment is layered, and any "
                "populated attachment is not layered, or if all populated "
                "color attachments are not from textures of the same target.");
            break;

        default:
            svErrorMsg = QX_TEXT("Unknown error");
            break;
        }
    }

    return svErrorMsg;
}

} // namespace qx
