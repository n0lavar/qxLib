//==============================================================================
//
//!\file                            vao.h
//
//!\brief       Contains qx::base_vao class
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/typedefs.h>
#include <qx/gl/ibuffer.h>

namespace qx
{

//==============================================================================
//
//!\class                    qx::base_vao
//
//!\brief   Base VAO class
//!\details ~
//
//!\author  Khrapov
//!\date    19.01.2020
//
//==============================================================================
class base_vao : IBuffer
{
public:

    friend class base_vao;

                    base_vao                (void) = default;
    virtual         ~base_vao               (void);

    virtual void    Generate                (void)          override;
    virtual void    Delete                  (void)          override;
    virtual void    Bind                    (void) const    override;
    virtual void    Unbind                  (void) const    override;
    virtual GLuint  GetBufferName           (void) const    override;
    virtual bool    IsGenerated             (void) const    override;

            void    EnableVertexArrtibArray (size_t         nIndex);
            void    DisableVertexArrtibArray(size_t         nIndex);
            void    VertexAttribPointer     (size_t         nIndex,
                                             GLint          nSize,
                                             GLenum         eType,
                                             GLboolean      bNormalized,
                                             GLsizei        nStride,
                                             size_t         nOffset);

private:

    GLuint m_nVAO = std::numeric_limits<GLuint>::max();
};

inline GLuint base_vao::GetBufferName(void) const
{
    return m_nVAO;
}
inline bool base_vao::IsGenerated(void) const
{
    return m_nVAO != std::numeric_limits<GLuint>::max();
};

using vao = base_vao;

}

#include <qx/gl/vao.inl>
