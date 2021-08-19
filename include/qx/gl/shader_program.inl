/**

    @file      shader_program.inl
    @brief     Contains qx::base_shader_program class implementation
    @author    Khrapov
    @date      16.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_shader_program::~base_shader_program(void)
{
    if (m_nProgram != std::numeric_limits<GLuint>::max())
        glDeleteProgram(m_nProgram);
}

inline void base_shader_program::Init(void)
{
    m_nProgram = glCreateProgram();
}

template<GLenum ShaderType>
inline void base_shader_program::AttachShader(shader_base<ShaderType>* pShader)
{
    glAttachShader(m_nProgram, pShader->GetID());
}

inline bool base_shader_program::Link(void)
{
    glLinkProgram(m_nProgram);
    const GLint bSuccess = GetParameter(GL_LINK_STATUS);

    if (bSuccess != GL_TRUE)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_nProgram, 512, nullptr, infoLog);
        QX_ASSERT_MSG(0, "Shader linking failed: \n%s", infoLog);
    }

    return bSuccess == GL_TRUE;
}

inline void base_shader_program::Use(void) const
{
    glUseProgram(m_nProgram);
}

inline void base_shader_program::Unuse(void) const
{
    glUseProgram(0);
}

inline GLint base_shader_program::GetParameter(GLenum eParameter) const
{
    GLint nRet = -1;
    glGetProgramiv(m_nProgram, eParameter, &nRet);
    return nRet;
}

inline GLuint base_shader_program::GetBufferName(void) const
{
    return m_nProgram;
}

template<typename T>
inline void base_shader_program::SetUniform(
    GLint    nUniformLocation,
    const T* pValue,
    GLsizei  nCount)
{
    if constexpr (std::is_same_v<T, GLfloat>)
    {
        glUniform1fv(nUniformLocation, nCount, pValue);
    }
    else if constexpr (std::is_same_v<T, glm::vec2>)
    {
        glUniform2fv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::vec3>)
    {
        glUniform3fv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::vec4>)
    {
        glUniform4fv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, GLint>)
    {
        glUniform1iv(nUniformLocation, nCount, pValue);
    }
    else if constexpr (std::is_same_v<T, glm::ivec2>)
    {
        glUniform2iv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::ivec3>)
    {
        glUniform3iv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::ivec4>)
    {
        glUniform4iv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, GLuint>)
    {
        glUniform1uiv(nUniformLocation, nCount, pValue);
    }
    else if constexpr (std::is_same_v<T, glm::uvec2>)
    {
        glUniform2uiv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::uvec3>)
    {
        glUniform3uiv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::uvec4>)
    {
        glUniform4uiv(nUniformLocation, nCount, glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat2>)
    {
        glUniformMatrix2fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat3>)
    {
        glUniformMatrix3fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat4>)
    {
        glUniformMatrix4fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat2x3>)
    {
        glUniformMatrix2x3fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat3x2>)
    {
        glUniformMatrix3x2fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat2x4>)
    {
        glUniformMatrix2x4fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat4x2>)
    {
        glUniformMatrix4x2fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat3x4>)
    {
        glUniformMatrix3x4fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else if constexpr (std::is_same_v<T, glm::mat4x3>)
    {
        glUniformMatrix4x3fv(
            nUniformLocation,
            nCount,
            GL_FALSE,
            glm::value_ptr(*pValue));
    }
    else
    {
        []<bool flag = false>()
        {
            static_assert(flag, "Uniform type is not supported");
        }
        ();
    }
}

template<typename T>
inline void base_shader_program::SetUniform(
    const GLchar* pszName,
    const T*      pValue,
    GLsizei       nCount)
{
    SetUniform(GetUniformLocation(pszName), pValue, nCount);
}

template<typename T>
inline void base_shader_program::SetUniform(
    GLint    nUniformLocation,
    const T& value)
{
    using type = std::remove_cvref_t<T>;
    if constexpr (std::is_same_v<T, GLfloat>)
        glUniform1f(nUniformLocation, value);
    else if constexpr (std::is_same_v<T, glm::vec2>)
        glUniform2f(nUniformLocation, value.x, value.y);
    else if constexpr (std::is_same_v<T, glm::vec3>)
        glUniform3f(nUniformLocation, value.x, value.y, value.z);
    else if constexpr (std::is_same_v<T, glm::vec4>)
        glUniform4f(nUniformLocation, value.x, value.y, value.z, value.w);
    else if constexpr (std::is_same_v<T, GLint>)
        glUniform1i(nUniformLocation, value);
    else if constexpr (std::is_same_v<T, glm::ivec2>)
        glUniform2i(nUniformLocation, value.x, value.y);
    else if constexpr (std::is_same_v<T, glm::ivec3>)
        glUniform3i(nUniformLocation, value.x, value.y, value.z);
    else if constexpr (std::is_same_v<T, glm::ivec4>)
        glUniform4i(nUniformLocation, value.x, value.y, value.z, value.w);
    else if constexpr (std::is_same_v<T, bool>)
        glUniform1i(nUniformLocation, value ? GL_TRUE : GL_FALSE);
    else
        SetUniform(nUniformLocation, &value, 1);
}

template<typename T>
inline void base_shader_program::SetUniform(
    const GLchar* pszName,
    const T&      value)
{
    SetUniform(GetUniformLocation(pszName), value);
}

inline GLint base_shader_program::GetUniformLocation(
    const GLchar* pszName,
    string*       pError) const
{
    const GLint nLocation = glGetUniformLocation(m_nProgram, pszName);

    if (nLocation < 0 && pError)
        pError->sprintf("Cant find uniform \"%s\"", pszName);

    return nLocation;
}

inline void base_shader_program::AddInclude(
    const char* pszName,
    GLint       nNameLength,
    const char* pszText,
    GLint       nTextLength)
{
    const bool bGlslIncludeSupported = GLEW_ARB_shading_language_include != 0;
    QX_CHECK(bGlslIncludeSupported);
    glNamedStringARB(
        GL_SHADER_INCLUDE_ARB,
        nNameLength,
        pszName,
        nTextLength,
        pszText);
}

inline void base_shader_program::DispatchCompute(
    GLuint nGroupsX,
    GLuint nGroupsY,
    GLuint nGroupsZ)
{
    glDispatchCompute(nGroupsX, nGroupsY, nGroupsZ);
}

inline bool base_shader_program::operator==(
    const base_shader_program& other) const
{
    return m_nProgram == other.m_nProgram;
}


} // namespace qx
