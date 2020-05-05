//============================================================================
//
//!\file                         shaders.inl
//
//!\brief       Contains shaders classes
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================

namespace qx::gl
{

//============================================================================
//!\fn                         shader_base::shader_base
//
//!\brief  shader_base object constructor
//!\param  pszShaderCode - string with shader code
//!\author Khrapov
//!\date   16.01.2020
//============================================================================
inline shader_base::shader_base(const GLchar* pszShaderCode,  GLenum eShaderType)
{
    Init(pszShaderCode, eShaderType);
}

//============================================================================
//!\fn                        shader_base::~shader_base
//
//!\brief  shader_base object destructor
//!\author Khrapov
//!\date   17.06.2019
//============================================================================
inline shader_base::~shader_base()
{
    // shader deleted in shader_program::Link
    if (m_nShader != UINT_EMPTY_VALUE && GetParameter(GL_DELETE_STATUS) != GL_TRUE)
    {
        ASSERT_MSG(0, "Shader memory is being freed in destructor. "
                      "Shader has been compiled, but has not been attached to "
                      "the program or program has not been linked.");

        glDeleteShader(m_nShader);
    }
}

//============================================================================
//!\fn                          shader_base::Init
//
//!\brief  Init (compile) shader
//!\param  pszShaderCode - string with shader code
//!\author Khrapov
//!\date   16.01.2020
//============================================================================
inline void shader_base::Init(const GLchar* pszShaderCode, GLenum eShaderType)
{
    // Compile
    m_nShader = glCreateShader(eShaderType);
    glShaderSource(m_nShader, 1, &pszShaderCode, NULL);
    glCompileShader(m_nShader);

    // Print compile errors if any
    if (GLint bSuccess = GetParameter(GL_COMPILE_STATUS); !bSuccess)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(m_nShader, 512, NULL, infoLog);
        ASSERT_MSG(0, "Shader %d compilation failed: %s", m_nShader, infoLog);
    }
}

//============================================================================
//!\fn                      shader_base::GetParameter
//
//!\brief  Get shader parameter
//!\param  eParameter - shader parameter.
//         \see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
//!\author Khrapov
//!\date   16.01.2020
//============================================================================
inline GLint shader_base::GetParameter(GLenum eParameter) const
{
    GLint nRet = UINT_EMPTY_VALUE;
    glGetShaderiv(m_nShader, eParameter, &nRet);
    return nRet;
}

}
