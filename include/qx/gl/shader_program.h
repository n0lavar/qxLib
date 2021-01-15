//==============================================================================
//
//!\file                      shader_program.h
//
//!\brief       Contains shader_program class
//!\details     ~
//
//!\author      Khrapov
//!\date        16.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/gl/shaders.h>
#include <qx/gl/buffer_classes.h>

#include <glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace qx
{

//==============================================================================
//
//!\class                    qx::shader_program
//
//!\brief   Shader programm class
//!\details ~
//
//!\author  Khrapov
//!\date    16.01.2020
//
//==============================================================================
template<bool COPYBLE>
class base_shader_program
{
public:

    friend class base_shader_program;

    QX_NONCOPYBLE(base_shader_program)

                base_shader_program (void) = default;
               ~base_shader_program (void);

    void        Init                (void);

    template <GLenum ShaderType>
    void        AttachShader        (shader_base<ShaderType>  * pShader);
    bool        Link                (void);
    void        Use                 (void);
    void        Unuse               (void);
    GLint       GetParameter        (GLenum                     eParameter) const;

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
    GLint       GetUniformLocation  (const GLchar             * pszName)    const;

protected:

    template<class Derived>
    void        Assign              (const Derived& other) { m_nProgram = other.m_nProgram; }

private:

    GLuint m_nProgram = std::numeric_limits<GLuint>::max();
};

QX_DEFINE_BUFFER_CLASSES(shader_program)

}

#include <qx/gl/shader_program.inl>
