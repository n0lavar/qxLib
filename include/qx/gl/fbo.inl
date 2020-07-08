//==============================================================================
//
//!\file                           fbo.inl
//
//!\brief       Contains fbo class
//!\details     ~
//
//!\author      Khrapov
//!\date        20.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx::gl
{

//==============================================================================
//!\fn                           fbo::~fbo
//
//!\brief  fbo object destructor
//!\author Khrapov
//!\date   19.01.2020
//==============================================================================
inline fbo::~fbo(void)
{
    Delete();
}

//==============================================================================
//!\fn                          fbo::Generate
//
//!\brief  Generate buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::Generate(void)
{
    glGenFramebuffers(1, &m_nBuffer);
}

//==============================================================================
//!\fn                           fbo::Delete
//
//!\brief  Delete buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::Delete(void)
{
    if (m_nBuffer != UINT_EMPTY_VALUE)
    {
        glDeleteFramebuffers(1, &m_nBuffer);
        m_nBuffer = UINT_EMPTY_VALUE;
    }
}

//==============================================================================
//!\fn                            fbo::Bind
//
//!\brief  Bind buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::Bind(void) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_nBuffer);
}

//==============================================================================
//!\fn                           fbo::Unbind
//
//!\brief  Unbind buffer
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::Unbind(void) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//==============================================================================
//!\fn                            fbo::Bind
//
//!\brief  Bind buffer with target
//!\param  target - Target
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::Bind(GLenum target)
{
    glBindFramebuffer(target, m_nBuffer);
}

//==============================================================================
//!\fn                         fbo::AttachRBO
//
//!\brief  Attach RBO th FRO
//!\param  rbo - render buffer object
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::AttachRBO(const rbo& rbo)
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
                              GL_DEPTH_STENCIL_ATTACHMENT, 
                              GL_RENDERBUFFER, 
                              rbo.GetBufferName());
}

//==============================================================================
//!\fn                         fbo::AttachTexture
//
//!\brief  Attach texture th FRO
//!\param  attachment - attachment point of the framebuffer
//!\param  texTarget  - type of texture is expected in the texture parameter
//!\param  texture    - fbo texture
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::AttachTexture(GLenum          attachment,
                               GLenum          texTarget,
                               const texture & texture)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, 
                           attachment,
                           texTarget,
                           texture.GetBufferName(), 
                           0);
}

//==============================================================================
//!\fn                          fbo::CheckStatus
//
//!\brief  Check framebuffer status
//!\author Khrapov
//!\date   26.06.2020
//==============================================================================
inline void fbo::CheckStatus(void) const
{
    if (auto eStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER); eStatus != GL_FRAMEBUFFER_COMPLETE)
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

