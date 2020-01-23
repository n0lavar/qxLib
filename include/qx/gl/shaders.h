//============================================================================
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
//============================================================================
#pragma once

#include <glew.h>
#include <noncopyble.h>
#include <typedefs.h>
#include <useful_macros.h>

namespace qx::gl
{

//============================================================================
//
//!\class                          shader_base
//
//!\brief   OpenGL base shader
//
//!\author  Khrapov
//!\date    17.06.2019
//
//============================================================================
class shader_base : noncopyble
{
public:
                    shader_base     (const GLchar * pszShaderCode,
                                     GLenum         eShaderType);
    virtual        ~shader_base     (void);

            void    Init            (const GLchar * pszShaderCode,
                                     GLenum         eShaderType);
            GLuint  GetID           (void)                          const;
            GLint   GetParameter    (GLenum         eParameter)     const;

    virtual GLenum  GetShaderType   (void)                          const = 0;
    
private:
    GLuint m_nShader = UINT_EMPTY_VALUE;
};

inline GLuint shader_base::GetID(void) const { return m_nShader; }

//============================================================================
//
//!\class                        shader_vert
//
//!\brief   Vertex shader class
//!\details ~
//
//!\author  Khrapov
//!\date    17.01.2020
//
//============================================================================
class shader_vert : public shader_base
{
public:
    shader_vert(const GLchar* pszShaderText) : shader_base(pszShaderText, GetShaderType()) { }
    virtual GLenum GetShaderType(void) const override { return GL_VERTEX_SHADER; };
};

//============================================================================
//
//!\class                        shader_frag
//
//!\brief   Fragment shader class
//!\details ~
//
//!\author  Khrapov
//!\date    17.01.2020
//
//============================================================================
class shader_frag : public shader_base
{
public:
    shader_frag(const GLchar* pszShaderText) : shader_base(pszShaderText, GetShaderType()) { }
    virtual GLenum GetShaderType(void) const override { return GL_FRAGMENT_SHADER; };
};

//============================================================================
//
//!\class                        shader_comp
//
//!\brief   Compute shader class
//!\details ~
//
//!\author  Khrapov
//!\date    17.01.2020
//
//============================================================================
class shader_comp : public shader_base
{
public:
    shader_comp(const GLchar* pszShaderText) : shader_base(pszShaderText, GetShaderType()) { }
    virtual GLenum GetShaderType(void) const override { return GL_COMPUTE_SHADER; };
};

}

#include <shaders.inl>
