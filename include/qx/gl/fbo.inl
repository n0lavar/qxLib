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
//!\param  pszVertShaderCode - vertex shader code
//!\param  pszFragShaderCode - fragment shader code
//!\param  nWidth            - FBO width
//!\param  nHeight           - FBO height
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::Init(const GLchar*   pszVertShaderCode,
                      const GLchar*   pszFragShaderCode, 
                      GLsizei         nWidth, 
                      GLsizei         nHeight)
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

    shader_vert shaderVertFramebuffer(pszVertShaderCode);
    shader_frag shaderFragFramebuffer(pszFragShaderCode);

    m_FBOShaderProgram.Init();
    m_FBOShaderProgram.AttachShader(&shaderVertFramebuffer);
    m_FBOShaderProgram.AttachShader(&shaderFragFramebuffer);
    m_FBOShaderProgram.Link();

    m_FBOShaderProgram.Use();
    m_FBOShaderProgram.SetUniform("screenTexture", 0);

    // generate framebuffer
    Generate();
    Bind();

    // create a color attachment texture
    m_TextureColorbuffer.Generate();
    m_TextureColorbuffer.Bind();
    m_TextureColorbuffer.Specify2DTexImage(0, GL_RGB, nWidth, nHeight, GL_RGB, GL_UNSIGNED_BYTE);
    m_TextureColorbuffer.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_TextureColorbuffer.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    AttachTexture(m_TextureColorbuffer);

    m_RBO.Init(nWidth, nHeight);
    AttachRBO(m_RBO);

    // check framebuffer status
    ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

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
//!\fn                         fbo::StartFrame
//
//!\brief  Start frame rendering
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::StartFrame(void)
{
    Bind();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//==============================================================================
//!\fn                          fbo::EndFrame
//
//!\brief  End frame rendering
//!\author Khrapov
//!\date   20.01.2020
//==============================================================================
inline void fbo::EndFrame(void)
{
    glDisable(GL_DEPTH_TEST);
    Unbind();

    m_FBOShaderProgram.Use();
    m_QuadVAO.Bind();

    glActiveTexture(GL_TEXTURE0);
    m_TextureColorbuffer.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo.GetBufferName());
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetBufferName(), 0);
}

}

