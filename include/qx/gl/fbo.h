//==============================================================================
//
//!\file                            fbo.h
//
//!\brief       Contains fbo class
//!\details     ~
//
//!\author      Khrapov
//!\date        20.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/gl/shader_program.h>
#include <qx/gl/vao.h>
#include <qx/gl/vbo.h>
#include <qx/gl/rbo.h>
#include <qx/gl/texture.h>
#include <qx/gl/shaders.h>

namespace qx::gl
{

//==============================================================================
//
//!\class                            fbo
//
//!\brief   
//!\details ~
//
//!\author  Khrapov
//!\date    20.01.2020
//
//==============================================================================
class fbo : IBuffer
{
public:

    QX_NONCOPYBLE(fbo)

                    fbo             (void) = default;
                    ~fbo            (void);

            void    Init            (GLsizei            nWidth,
                                     GLsizei            nHeight,
                                     const GLchar     * pszVertShaderCode   = nullptr,
                                     const GLchar     * pszFragShaderCode   = nullptr,
                                     size_t             nMultisamples       = 0);

    virtual void    Generate        (void)          override;
    virtual void    Delete          (void)          override;
    virtual void    Bind            (void) const    override;
    virtual void    Unbind          (void) const    override;
    virtual GLuint  GetBufferName   (void) const    override;

            void    DrawFboQuad     (void);

            void    Bind            (GLenum target);

private:
            void    AttachRBO       (const rbo    & rbo);
            void    AttachTexture   (const texture& texture);

private:

    shader_program  m_FBOShaderProgram;
    vao             m_QuadVAO;
    vbo             m_QuadVBO;
    rbo             m_RBO;
    texture         m_TextureColorbuffer;
    size_t          m_nMultisamples         = 0;    // 0 - no multisampling

    GLuint          m_nBuffer               = UINT_EMPTY_VALUE;
};

inline GLuint fbo::GetBufferName(void) const { return m_nBuffer; }

}

#include <qx/gl/fbo.inl>
