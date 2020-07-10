//==============================================================================
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
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                         shader_base::shader_base
//
//!\brief  shader_base object constructor
//!\param  pszShaderCode - string with shader code
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
template <GLenum ShaderType>
inline shader_base<ShaderType>::shader_base(const GLchar* pszShaderCode)
{
    Init(pszShaderCode);
}

//==============================================================================
//!\fn                        shader_base::~shader_base
//
//!\brief  shader_base object destructor
//!\author Khrapov
//!\date   17.06.2019
//==============================================================================
template <GLenum ShaderType>
inline shader_base<ShaderType>::~shader_base()
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

//==============================================================================
//!\fn                          shader_base::Init
//
//!\brief  Init (compile) shader
//!\param  pszShaderCode - string with shader code
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
template <GLenum ShaderType>
inline void shader_base<ShaderType>::Init(const GLchar* pszShaderCode)
{
    // Compile
    m_nShader = glCreateShader(ShaderType);
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

//==============================================================================
//!\fn                      shader_base::GetParameter
//
//!\brief  Get shader parameter
//!\param  eParameter - shader parameter.
//         \see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
template <GLenum ShaderType>
inline GLint shader_base<ShaderType>::GetParameter(GLenum eParameter) const
{
    GLint nRet = UINT_EMPTY_VALUE;
    glGetShaderiv(m_nShader, eParameter, &nRet);
    return nRet;
}

}
