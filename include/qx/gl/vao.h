//==============================================================================
//
//!\file                            vao.h
//
//!\brief       Contains vao class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/typedefs.h>
#include <qx/gl/iBuffer.h>

namespace qx::gl
{

//==============================================================================
//
//!\class                            vao
//
//!\brief   Vertex arrays object class
//!\details ~
//
//!\author  Khrapov
//!\date    19.01.2020
//
//==============================================================================
class vao : IBuffer
{
public:

    QX_NONCOPYBLE(vao)

                    vao                     (void) = default;
                    ~vao                    (void);

    virtual void    Generate                (void)          override;
    virtual void    Delete                  (void)          override;
    virtual void    Bind                    (void) const    override;
    virtual void    Unbind                  (void) const    override;
    virtual GLuint  GetBufferName           (void) const    override;

    void            EnableVertexArrtibArray (GLuint         nIndex);
    void            DisableVertexArrtibArray(GLuint         nIndex);

    void            VertexAttribPointer     (GLuint         nIndex,
                                             GLint          nSize,
                                             GLenum         eType,
                                             GLboolean      bNormalized,
                                             GLsizei        nStride,
                                             size_t         nOffset);

private:
    GLuint m_nVAO = UINT_EMPTY_VALUE;
};

inline GLuint vao::GetBufferName(void) const { return m_nVAO; }

}

#include <qx/gl/vao.inl>
