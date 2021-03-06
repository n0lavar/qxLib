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
//!\fn                       qx::shader_base::shader_base
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
//!\fn                      qx::shader_base::~shader_base
//
//!\brief  shader_base object destructor
//!\author Khrapov
//!\date   17.06.2019
//==============================================================================
template <GLenum ShaderType>
inline shader_base<ShaderType>::~shader_base()
{
    glDeleteShader(m_nShader);
}

//==============================================================================
//!\fn                        qx::shader_base::Init
//
//!\brief  Init (compile) shader
//!\param  pszShaderCode - string with shader code
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
template <GLenum ShaderType>
inline void shader_base<ShaderType>::Init(const GLchar* pszShaderCode)
{
    if (pszShaderCode)
    {
        // Compile
        m_nShader = glCreateShader(ShaderType);
        glShaderSource(m_nShader, 1, &pszShaderCode, NULL);
        glCompileShader(m_nShader);

        // Print compile errors if any
        if (GLint bSuccess = GetParameter(GL_COMPILE_STATUS); !bSuccess)
        {
            GLchar infoLog[QX_SHADER_INFO_LOG_SIZE];
            glGetShaderInfoLog(m_nShader, QX_SHADER_INFO_LOG_SIZE, NULL, infoLog);
            ASSERT_MSG(0, "Shader %d compilation failed:\n%s", m_nShader, infoLog);
        }
    }
    else
        ASSERT_MSG(0, "Nullptr passed as shader text pointer");
}

//==============================================================================
//!\fn                    qx::shader_base::GetParameter
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
    GLint nRet = -1;
    glGetShaderiv(m_nShader, eParameter, &nRet);
    return nRet;
}

}
