//============================================================================
//
//!\file                      ÒShaderProgramm.h
//
//!\brief       Contains shader_program class
//!\details     ~
//
//!\author      Khrapov
//!\date        16.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <glew.h>
#include <gtc/type_ptr.hpp>
#include <vector>

#include <qx/other/noncopyble.h>
#include <qx/other/useful_macros.h>
#include <qx/gl/shaders.h>

namespace qx::gl
{

class shader_base;

//============================================================================
//
//!\class                      shader_program
//
//!\brief   Shader programm class
//!\details ~
//
//!\author  Khrapov
//!\date    16.01.2020
//
//============================================================================
class shader_program : noncopyble
{
public:
            shader_program  (void);
           ~shader_program  (void);

    void    AttachShader    (shader_base      * pShader);
    void    Link            (void);
    void    Use             (void);
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
    GLuint              m_nProgram          = -1;
    std::vector<GLuint> m_AttachedShaders;
};

}

using TPtrShaderProgram = std::shared_ptr<qx::gl::shader_program>;

#include <qx/gl/shader_program.inl>
