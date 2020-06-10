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

// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
constexpr float quadVertices[] =
{
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

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
//!\fn                            fbo::Init
//
//!\brief  Init FBO
//!\param  nWidth            - FBO width
//!\param  nHeight           - FBO height
//!\param  pszVertShaderCode - vertex shader code
//!\param  pszFragShaderCode - fragment shader code
//!\param  nMultisamples     - samples number, 0 - disable
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::Init(GLsizei       nWidth, 
                      GLsizei       nHeight,
                      const GLchar* pszVertShaderCode,
                      const GLchar* pszFragShaderCode,
                      size_t        nMultisamples)
{
    m_nMultisamples = nMultisamples;

    if (pszVertShaderCode && pszFragShaderCode)
    {
        // screen quad VAO
        m_QuadVAO.Generate();
        m_QuadVBO.Generate();

        m_QuadVAO.Bind();

        m_QuadVBO.Update(sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

        m_QuadVAO.EnableVertexArrtibArray(0);
        m_QuadVAO.VertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

        m_QuadVAO.EnableVertexArrtibArray(1);
        m_QuadVAO.VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 2 * sizeof(float));

        m_FBOShaderProgram.Init();

        shader_vert shaderVertFramebuffer;
        shader_frag shaderFragFramebuffer;

        shaderVertFramebuffer.Init(pszVertShaderCode);
        shaderFragFramebuffer.Init(pszFragShaderCode);

        m_FBOShaderProgram.AttachShader(&shaderVertFramebuffer);
        m_FBOShaderProgram.AttachShader(&shaderFragFramebuffer);

        m_FBOShaderProgram.Link();

        m_FBOShaderProgram.Use();
        m_FBOShaderProgram.SetUniform("screenTexture", 0);
        m_FBOShaderProgram.Unuse();
    }

    // generate framebuffer
    Generate();
    Bind();

    // create a color attachment texture
    m_TextureColorbuffer.Generate();
    m_TextureColorbuffer.SetTarget(m_nMultisamples ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D);
    m_TextureColorbuffer.Bind();

    if (!m_nMultisamples || m_nMultisamples % 2 != 0)
    {
        m_TextureColorbuffer.Specify2DTexImage(0, GL_RGB, nWidth, nHeight, GL_RGB, GL_UNSIGNED_BYTE);
        m_TextureColorbuffer.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        m_TextureColorbuffer.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        m_TextureColorbuffer.Specify2DMultisample(m_nMultisamples, GL_RGB, nWidth, nHeight, true);
    }
    m_TextureColorbuffer.Unbind();

    AttachTexture(m_TextureColorbuffer);

    m_RBO.Init(nWidth, nHeight, nMultisamples);
    AttachRBO(m_RBO);

    // check framebuffer status
    if (auto eStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER); eStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        char const * pszErrorMsg = nullptr;
        switch (eStatus)
        {
        case GL_FRAMEBUFFER_UNDEFINED:                      
            pszErrorMsg = "The specified framebuffer is the default read or draw"
                "framebuffer, but the default framebuffer does not exist."; 
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:          
            pszErrorMsg = "Any of the framebuffer attachment points "
                "are framebuffer incomplete."; 
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:  
            pszErrorMsg = "The framebuffer does not have at least one "
                "image attached to it."; 
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:         
            pszErrorMsg = "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE "
                "for any color attachment point(s) named by GL_DRAW_BUFFERi."; 
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:         
            pszErrorMsg = "GL_READ_BUFFER is not GL_NONE and the value of "
                "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE "
                "for the color attachment point named by GL_READ_BUFFER."; 
            break;

        case GL_FRAMEBUFFER_UNSUPPORTED:                    
            pszErrorMsg = "The combination of internal formats of the attached "
                "images violates an implementation - dependent set of restrictions."; 
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:         
            pszErrorMsg = "The value of GL_RENDERBUFFER_SAMPLES is not the "
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
            pszErrorMsg = "Any framebuffer attachment is layered, and any "
                "populated attachment is not layered, or if all populated "
                "color attachments are not from textures of the same target."; 
            break;

        default:
            pszErrorMsg = "Unknown error";
            break;
        }

        ASSERT_MSG(0, "Framebuffer status is not complete: Status: %d, Error: %s", 
                   eStatus, pszErrorMsg);
    }

    // drop framebuffer
    Unbind();
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
    glDeleteFramebuffers(1, &m_nBuffer);
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
//!\fn                        fbo::DrawFboQuad
//
//!\brief  End frame rendering
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::DrawFboQuad(void)
{
    m_FBOShaderProgram.Use();
    m_QuadVAO.Bind();

    glActiveTexture(GL_TEXTURE0);
    m_TextureColorbuffer.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_FBOShaderProgram.Unuse();
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
//!\param  texture - fbo texture
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::AttachTexture(const texture& texture)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, 
                           GL_COLOR_ATTACHMENT0, 
                           m_nMultisamples ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D,
                           texture.GetBufferName(), 
                           0);
}

}

