/**

    @file      shaders.h
    @brief     Contains shaders classes
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_converters.h>
#include <qx/macros/copyable_movable.h>

#include <glew.h>

namespace qx
{

enum class shader_type
{
    vert, //!< vertex
    tesc, //!< tessellation control
    tese, //!< tessellation evaluation
    geom, //!< geometry
    frag, //!< fragment
    comp  //!< compute
};

/**

    @class   shader_base
    @brief   OpenGL base shader
    @details ~
    @tparam  ShaderType - GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER,
                          GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER,
                          GL_FRAGMENT_SHADER, GL_COMPUTE_SHADER
    @author  Khrapov
    @date    17.06.2019

**/
template<GLenum ShaderType>
class shader_base
{
public:
    QX_NONCOPYABLE(shader_base);
    QX_MOVABLE(shader_base);

    /**
        @brief shader_base object constructor
    **/
    shader_base() = default;

    /**
        @brief shader_base object destructor
    **/
    ~shader_base();

    /**
        @brief  Init (compile) shader
        @param  pszShaderCode - string with shader code
        @retval               - error or empty string if init was successful
    **/
    string Init(const GLchar* pszShaderCode);

    /**
        @brief  Get shader name
        @retval - shader name
    **/
    GLuint GetID() const;

    /**
        @brief  Get shader parameter
        @param  eParameter - shader parameter
        \see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
        @retval            - shader parameter value
    **/
    GLint GetParameter(GLenum eParameter) const;

private:
    GLuint m_nShader = std::numeric_limits<GLuint>::max();
};

using shader_vert = shader_base<GL_VERTEX_SHADER>;
using shader_tesc = shader_base<GL_TESS_CONTROL_SHADER>;
using shader_tese = shader_base<GL_TESS_EVALUATION_SHADER>;
using shader_geom = shader_base<GL_GEOMETRY_SHADER>;
using shader_frag = shader_base<GL_FRAGMENT_SHADER>;
using shader_comp = shader_base<GL_COMPUTE_SHADER>;

} // namespace qx

#include <qx/gl/shaders.inl>
