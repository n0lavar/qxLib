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

namespace qx::gl
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

            shader_program  (void) = default;
           ~shader_program  (void);

    void    Init            (void);

    template <GLenum ShaderType>
    void    AttachShader    (shader_base<ShaderType>* pShader);
    bool    Link            (void);
    void    Use             (void);
    void    Unuse           (void);
    void    DispatchCompute (GLuint             nGroupsX,
                             GLuint             nGroupsY,
                             GLuint             nGroupsZ);
    GLint   GetParameter    (GLenum             eParameter);

    template<typename T>
    void    SetUniform      (const GLchar     * name,
                             const T          & value);

    template<typename T>
    void    SetUniform      (GLint              nUniformLocation,
                             const T          & value);

private:
    GLuint              m_nProgram          = UINT_EMPTY_VALUE;
    std::vector<GLuint> m_AttachedShaders;
};

}

using TPtrShaderProgram = std::shared_ptr<qx::gl::shader_program>;

#include <qx/gl/shader_program.inl>
