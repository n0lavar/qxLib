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

#include <glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

#include <qx/gl/shaders.h>

namespace qx
{

//==============================================================================
//
//!\class                      shader_program
//
//!\brief   Shader programm class
//!\details ~
//
//!\author  Khrapov
//!\date    16.01.2020
//
//==============================================================================
class shader_program
{
public:

    QX_NONCOPYBLE(shader_program)

                shader_program      (void) = default;
               ~shader_program      (void);

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

protected:

    GLint       GetUniformLocation  (const GLchar             * pszName)    const;

private:

    GLuint              m_nProgram          = UINT_EMPTY_VALUE;
    std::vector<GLuint> m_AttachedShaders;
};

}

using TPtrShaderProgram = std::shared_ptr<qx::shader_program>;

#include <qx/gl/shader_program.inl>
