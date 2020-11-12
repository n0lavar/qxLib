//==============================================================================
//
//!\file                     shader_program.inl
//
//!\brief       Contains shader_program class
//!\details     ~
//
//!\author      Khrapov
//!\date        16.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn              qx::shader_program::~shader_program
//
//!\brief  shader_program object destructor
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
inline shader_program::~shader_program(void)
{
    if (m_nProgram != std::numeric_limits<GLuint>::max())
        glDeleteProgram(m_nProgram);
}

//==============================================================================
//!\fn                   qx::shader_program::Init
//
//!\brief  Init shader program
//!\author Khrapov
//!\date   18.04.2020
//==============================================================================
inline void shader_program::Init(void)
{
    m_nProgram = glCreateProgram();
}

//==============================================================================
//!\fn                qx::shader_program::AttachShader
//
//!\brief  Attach shader to the program
//!\param  pShader - shader object pointer
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
template <GLenum ShaderType>
inline void shader_program::AttachShader(shader_base<ShaderType>* pShader)
{
    glAttachShader(m_nProgram, pShader->GetID());
}

//==============================================================================
//!\fn                qx::shader_program::Link
//
//!\brief  Link attached shaders
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
inline bool shader_program::Link(void)
{
    glLinkProgram(m_nProgram);
    GLint bSuccess = GetParameter(GL_LINK_STATUS);

    if (!bSuccess)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_nProgram, 512, NULL, infoLog);
        QX_ASSERT_MSG(0, "Shader linking failed: %s", infoLog);
    }

    return bSuccess;
}

//==============================================================================
//!\fn                     qx::shader_program::Use
//
//!\brief  Use shader program
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
inline void shader_program::Use(void)
{
    glUseProgram(m_nProgram);
}

//==============================================================================
//!\fn                     qx::shader_program::Use
//
//!\brief  Drop current shader
//!\author Khrapov
//!\date   16.01.2020
//==============================================================================
inline void shader_program::Unuse(void)
{
    glUseProgram(0);
}

//==============================================================================
//!\fn                 qx::shader_program::GetParameter
//
//!\brief  Get shader program parameter
//!\param  eParameter - shader program parameter.
//         \see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
//!\author Khrapov
//!\date   17.01.2020
//==============================================================================
inline GLint shader_program::GetParameter(GLenum eParameter) const
{
    GLint nRet = -1;
    glGetProgramiv(m_nProgram, eParameter, &nRet);
    return nRet;
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const GLfloat* pValue, GLsizei nCount)
{
    glUniform1fv(nUniformLocation, nCount, pValue);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::vec2* pValue, GLsizei nCount)
{
    glUniform2fv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::vec3* pValue, GLsizei nCount)
{
    glUniform3fv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::vec4* pValue, GLsizei nCount)
{
    glUniform4fv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const GLint* pValue, GLsizei nCount)
{
    glUniform1iv(nUniformLocation, nCount, pValue);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::ivec2* pValue, GLsizei nCount)
{
    glUniform2iv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::ivec3* pValue, GLsizei nCount)
{
    glUniform3iv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::ivec4* pValue, GLsizei nCount)
{
    glUniform4iv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const GLuint* pValue, GLsizei nCount)
{
    glUniform1uiv(nUniformLocation, nCount, pValue);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::uvec2* pValue, GLsizei nCount)
{
    glUniform2uiv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::uvec3* pValue, GLsizei nCount)
{
    glUniform3uiv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::uvec4* pValue, GLsizei nCount)
{
    glUniform4uiv(nUniformLocation, nCount, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat2* pValue, GLsizei nCount)
{
    glUniformMatrix2fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat3* pValue, GLsizei nCount)
{
    glUniformMatrix3fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat4* pValue, GLsizei nCount)
{
    glUniformMatrix4fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat2x3* pValue, GLsizei nCount)
{
    glUniformMatrix2x3fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat3x2* pValue, GLsizei nCount)
{
    glUniformMatrix3x2fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat2x4* pValue, GLsizei nCount)
{
    glUniformMatrix2x4fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat4x2* pValue, GLsizei nCount)
{
    glUniformMatrix4x2fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat3x4* pValue, GLsizei nCount)
{
    glUniformMatrix3x4fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat4x3* pValue, GLsizei nCount)
{
    glUniformMatrix4x3fv(nUniformLocation, nCount, GL_FALSE, glm::value_ptr(*pValue));
}

template<typename T>
inline void shader_program::SetUniform(const GLchar* pszName, const T* pValue, GLsizei nCount)
{
    SetUniform(GetUniformLocation(pszName), pValue, nCount);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const GLfloat & value)
{
    glUniform1f(nUniformLocation, value);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::vec2 & value)
{
    glUniform2f(nUniformLocation, value.x, value.y);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::vec3 & value)
{
    glUniform3f(nUniformLocation, value.x, value.y, value.z);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::vec4 & value)
{
    glUniform4f(nUniformLocation, value.x, value.y, value.z, value.w);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const GLint & value)
{
    glUniform1i(nUniformLocation, value);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::ivec2 & value)
{
    glUniform2i(nUniformLocation, value.x, value.y);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::ivec3 & value)
{
    glUniform3i(nUniformLocation, value.x, value.y, value.z);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::ivec4 & value)
{
    glUniform4i(nUniformLocation, value.x, value.y, value.z, value.w);
}

template<>
inline void shader_program::SetUniform(GLint nUniformLocation, const bool& value)
{
    SetUniform(nUniformLocation, value ? GL_TRUE : GL_FALSE);
}

template<typename T>
inline void shader_program::SetUniform(GLint nUniformLocation, const T& value)
{
    SetUniform(nUniformLocation, &value, 1);
}

template<typename T>
inline void shader_program::SetUniform(const GLchar* pszName, const T& value)
{
    SetUniform(GetUniformLocation(pszName), value);
}

//==============================================================================
//!\fn              qx::shader_program::GetUniformLocation
//
//!\brief   Get uniform location based on it's name
//!\param   name - uniform string name
//!\retval       - location number
//!\author Khrapov
//!\date   05.08.2020
//==============================================================================
inline GLint shader_program::GetUniformLocation(const GLchar* pszName) const
{
    GLint nLocation = glGetUniformLocation(m_nProgram, pszName);

#if !QX_DISABLE_UNKNOWN_UNIFORM_ASSERT
    QX_ASSERT_MSG(nLocation >= 0, "Cant find uniform \"%s\" in program %u", pszName, m_nProgram);
#endif

    return nLocation;
}

//==============================================================================
//!\fn                qx::shader_program::AddInclude
//
//!\brief   Add include string
//!\details ARB_shading_language_include is required for this function
//          calling of this function must be before shader's compilation
//          usage example:
//
//          #version 440 core
//          #extension GL_ARB_shading_language_include : require
//          #include "/header.h"
//
//!\param   pszName      - name that you will #include in shader (should be with leading '/')
//!\param   nNameLength  - name length
//!\param   pszText      - text that will be placed in shader instead of #include
//!\param   nTextLength  - text length
//!\author  Khrapov
//!\date    06.08.2020
//==============================================================================
inline void shader_program::AddInclude(const char* pszName,
                                       GLint       nNameLength,
                                       const char* pszText,
                                       GLint       nTextLength)
{
    bool bGlslIncludeSupported = GLEW_ARB_shading_language_include;
    QX_CHECK(bGlslIncludeSupported)
        glNamedStringARB(GL_SHADER_INCLUDE_ARB, nNameLength, pszName, nTextLength, pszText);
}

//==============================================================================
//!\fn               qx::shader_program::DispatchCompute
//
//!\brief  Dispatch program compute
//!\param  nGroupsX - The number of work groups to be launched in the X dimension
//!\param  nGroupsY - The number of work groups to be launched in the Y dimension
//!\param  nGroupsZ - The number of work groups to be launched in the Z dimension
//!\author Khrapov
//!\date   17.01.2020
//==============================================================================
inline void shader_program::DispatchCompute(GLuint nGroupsX, GLuint nGroupsY, GLuint nGroupsZ)
{
    glDispatchCompute(nGroupsX, nGroupsY, nGroupsZ);
}

}
