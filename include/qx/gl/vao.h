//==============================================================================
//
//!\file                            vao.h
//
//!\brief       Vertex array object classes: vao and copyble_vao
//!\details     ~
//
//!\author      Khrapov
//!\date        19.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/typedefs.h>
#include <qx/gl/ibuffer.h>

namespace qx
{

//==============================================================================
//
//!\class                      base_vao<COPYBLE>
//
//!\brief   Base VAO class. Use vao or copyble_vao
//!\details ~
//
//!\author  Khrapov
//!\date    19.01.2020
//
//==============================================================================
template<bool COPYBLE>
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

            void    EnableVertexArrtibArray (GLuint         nIndex);
            void    DisableVertexArrtibArray(GLuint         nIndex);
                    
            void    VertexAttribPointer     (GLuint         nIndex,
                                             GLint          nSize,
                                             GLenum         eType,
                                             GLboolean      bNormalized,
                                             GLsizei        nStride,
                                             size_t         nOffset);

            template<class Derived>
            void    Assign                  (const Derived& other) { m_nVAO = other.m_nVAO; }

private:

    GLuint m_nVAO = UINT_EMPTY_VALUE;
};

template<bool COPYBLE>
inline GLuint base_vao<COPYBLE>::GetBufferName (void) const { return m_nVAO; }
template<bool COPYBLE>
inline bool   base_vao<COPYBLE>::IsGenerated   (void) const { return m_nVAO != UINT_EMPTY_VALUE; };

QX_DEFINE_BUFFER_CLASSES(vao)

}

#include <qx/gl/vao.inl>
