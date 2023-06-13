/**

    @file      shaders.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<GLenum ShaderType>
inline shader_base<ShaderType>::~shader_base()
{
    glDeleteShader(m_nShader);
}

template<GLenum ShaderType>
inline string shader_base<ShaderType>::Init(const GLchar* pszShaderCode)
{
    cstring sError;

    if (pszShaderCode)
    {
        // Compile
        m_nShader = glCreateShader(ShaderType);
        glShaderSource(m_nShader, 1, &pszShaderCode, nullptr);
        glCompileShader(m_nShader);

        // Print compile errors if any
        if (const GLint bSuccess = GetParameter(GL_COMPILE_STATUS); !bSuccess)
        {
            GLsizei nErrorStringLength = 0;
            glGetShaderiv(m_nShader, GL_INFO_LOG_LENGTH, &nErrorStringLength);

            if (nErrorStringLength > 0)
            {
                sError.assign(nErrorStringLength, '\0');
                glGetShaderInfoLog(m_nShader, nErrorStringLength, nullptr, sError.data());
            }
        }
    }
    else
    {
        sError = "Nullptr passed as shader text pointer";
    }

    return qx::to_string(sError);
}


template<GLenum ShaderType>
inline GLuint shader_base<ShaderType>::GetID() const
{
    return m_nShader;
}

template<GLenum ShaderType>
inline GLint shader_base<ShaderType>::GetParameter(GLenum eParameter) const
{
    GLint nRet = -1;
    glGetShaderiv(m_nShader, eParameter, &nRet);
    return nRet;
}

} // namespace qx
