//==============================================================================
//
//!\file                      shader_program.h
//
//!\brief       Contains qx::base_shader_program class
//!\details     ~
//
//!\author      Khrapov
//!\date        16.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <qx/gl/shaders.h>

namespace qx
{

//==============================================================================
//
//!\class                 qx::base_shader_program
//
//!\brief   Shader program class
//!\details ~
//
//!\author  Khrapov
//!\date    16.01.2020
//
//==============================================================================
class base_shader_program
{
public:

    QX_NONCOPYABLE(base_shader_program)
    QX_MOVABLE(base_shader_program)

                base_shader_program (void) = default;
               ~base_shader_program (void);

    void        Init                (void);

    template <GLenum ShaderType>
    void        AttachShader        (shader_base<ShaderType>  * pShader);
    bool        Link                (void);
    void        Use                 (void)                                  const;
    void        Unuse               (void)                                  const;
    GLint       GetParameter        (GLenum                     eParameter) const;
    GLuint      GetBufferName       (void)                                  const;

    template<typename T>
    void        SetUniform          (GLint                      nUniformLocation,
                                     const T                  * pValue,
                                     GLsizei                    nCount);
    template<typename T>
    void        SetUniform          (const GLchar             * pszName,
                                     const T                  * pValue,
                                     GLsizei                    nCount);
    template<typename T>
    void        SetUniform          (GLint                      nUniformLocation,
                                     const T                  & value);
    template<typename T>
    void        SetUniform          (const GLchar             * pszName,
                                     const T                  & value);

    static void AddInclude          (const char               * pszName,
                                     GLint                      nNameLength,
                                     const char               * pszText,
                                     GLint                      nTextLength);
    static void DispatchCompute     (GLuint                     nGroupsX,
                                     GLuint                     nGroupsY,
                                     GLuint                     nGroupsZ);
    GLint       GetUniformLocation  (const GLchar             * pszName,
                                     string                   * pError = nullptr) const;

    bool        operator==          (const base_shader_program& other) const { return m_nProgram == other.m_nProgram;  }

private:

    GLuint m_nProgram = std::numeric_limits<GLuint>::max();
};

inline GLuint base_shader_program::GetBufferName(void) const
{
    return m_nProgram;
}

using shader_program = base_shader_program;

}

#include <qx/gl/shader_program.inl>
