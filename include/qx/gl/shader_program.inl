//============================================================================
//
//!\file                     ñShaderProgramm.inl
//
//!\brief       Contains shader_program class
//!\details     ~
//
//!\author      Khrapov
//!\date        16.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================

namespace qx::gl
{

//============================================================================
//!\fn                 shader_program::shader_program
//
//!\brief  shader_program object constructor
//!\author Khrapov
//!\date   16.01.2020
//============================================================================
inline shader_program::shader_program()
{
    m_nProgram = glCreateProgram();
}

//============================================================================
//!\fn                shader_program::~shader_program
//
//!\brief  shader_program object destructor
//!\author Khrapov
//!\date   16.01.2020
//============================================================================
inline shader_program::~shader_program(void)
{
    glDeleteProgram(m_nProgram);
}

//============================================================================
//!\fn                  shader_program::AttachShader
//
//!\brief  Attach shader to the program
//!\param  pShader - shader object pointer
//!\author Khrapov
//!\date   16.01.2020
//============================================================================
inline void shader_program::AttachShader(shader_base* pShader)
{
    glAttachShader(m_nProgram, pShader->GetID());
    m_AttachedShaders.push_back(pShader->GetID());
}

//============================================================================
//!\fn                  shader_program::Link
//
//!\brief  Link attached shaders
//!\author Khrapov
//!\date   16.01.2020
//============================================================================
inline void shader_program::Link(void)
{
    glLinkProgram(m_nProgram);

    if (GLint bSuccess = GetParameter(GL_LINK_STATUS); !bSuccess)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_nProgram, 512, NULL, infoLog);
        ASSERT_MSG(0, "Shader linking failed: %s", infoLog);
    }
    else
    {
        for(GLuint nShader : m_AttachedShaders)
            glDeleteShader(nShader);

        m_AttachedShaders.clear();
    }
}

//============================================================================
//!\fn                       shader_program::Use
//
//!\brief  Use shader program
//!\author Khrapov
//!\date   16.01.2020
//============================================================================
inline void shader_program::Use(void)
{
    glUseProgram(m_nProgram);
}

//============================================================================
//!\fn                 shader_program::DispatchCompute
//
//!\brief  Dispatch program compute
//!\param  nGroupsX - The number of work groups to be launched in the X dimension
//!\param  nGroupsY - The number of work groups to be launched in the Y dimension
//!\param  nGroupsZ - The number of work groups to be launched in the Z dimension
//!\author Khrapov
//!\date   17.01.2020
//============================================================================
inline void shader_program::DispatchCompute(GLuint nGroupsX, GLuint nGroupsY, GLuint nGroupsZ)
{
    glDispatchCompute(nGroupsX, nGroupsY, nGroupsZ);
}

//============================================================================
//!\fn                   shader_program::GetParameter
//
//!\brief  Get shader program parameter
//!\param  eParameter - shader program parameter.
//         \see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
//!\author Khrapov
//!\date   17.01.2020
//============================================================================
inline GLint shader_program::GetParameter(GLenum eParameter)
{
    GLint nRet = -1;
    glGetProgramiv(m_nProgram, eParameter, &nRet);
    return nRet;
}


template<typename T>
inline void shader_program::SetUniform(const GLchar * name, const T & value)
{
    SetUniform(glGetUniformLocation(m_nProgram, name), value);
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
inline void shader_program::SetUniform(GLint nUniformLocation, const glm::mat4 & value)
{
    glUniformMatrix4fv(nUniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

}