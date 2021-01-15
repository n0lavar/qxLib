//==============================================================================
//
//!\file                          shaders.h
//
//!\brief       Contains shaders classes
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/useful_macros.h>

#include <glew.h>

#if !defined(QX_SHADER_INFO_LOG_SIZE)
    #define QX_SHADER_INFO_LOG_SIZE 512
#endif

namespace qx
{

enum class shader_type
{
    vert,   //!< vertex
    tesc,   //!< tessellation control
    tese,   //!< tessellation evaluation
    geom,   //!< geometry
    frag,   //!< fragment
    comp    //!< compute
};

//==============================================================================
//
//!\class                        qx::shader_base
//
//!\brief   OpenGL base shader
//
//!\author  Khrapov
//!\date    17.06.2019
//
//==============================================================================
template <GLenum ShaderType>
class shader_base
{
public:

    QX_NONCOPYBLE(shader_base)

            shader_base     (void) = default;
            shader_base     (const GLchar * pszShaderCode);
            ~shader_base    (void);

    void    Init            (const GLchar * pszShaderCode);
    GLuint  GetID           (void)                          const;
    GLint   GetParameter    (GLenum         eParameter)     const;

private:

    GLuint m_nShader = std::numeric_limits<GLuint>::max();
};

template <GLenum ShaderType>
inline GLuint shader_base<ShaderType>::GetID(void) const { return m_nShader; }

using shader_vert = shader_base<GL_VERTEX_SHADER>;
using shader_tesc = shader_base<GL_TESS_CONTROL_SHADER>;
using shader_tese = shader_base<GL_TESS_EVALUATION_SHADER>;
using shader_geom = shader_base<GL_GEOMETRY_SHADER>;
using shader_frag = shader_base<GL_FRAGMENT_SHADER>;
using shader_comp = shader_base<GL_COMPUTE_SHADER>;

}

#include <qx/gl/shaders.inl>
