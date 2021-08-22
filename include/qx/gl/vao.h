/**

    @file      vao.h
    @brief     Contains qx::base_vao class
    @author    Khrapov
    @date      19.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/ibuffer.h>
#include <qx/typedefs.h>

namespace qx
{

/**

    @class   base_vao
    @brief   Base VAO class
    @details ~

    @author  Khrapov
    @date    19.01.2020

**/
class base_vao : IBuffer
{
public:
    /**
        @brief base_vao object constructor
    **/
    base_vao(void) = default;

    /**
        @brief base_vao object destructor
    **/
    virtual ~base_vao(void);

    QX_DECL_IBUFFER

    /**
        @brief Enable a generic vertex attribute array
        @param nIndex - array index in VAO
    **/
    void EnableVertexArrtibArray(size_t nIndex);

    /**
        @brief Disable a generic vertex attribute array
        @param nIndex - array index in VAO
    **/
    void DisableVertexArrtibArray(size_t nIndex);

    /**
        @brief Define an array of generic vertex attribute data
        @param nIndex      - index of the generic vertex attribute to be modified 
        @param nSize       - number of components per generic vertex attribute.
                             Must be 1, 2, 3, 4
        @param eType       - data type of each component in the array 
        @param bNormalized - specifies whether fixed-point data values should be
                             normalized or converted directly as fixed-point values
        @param nStride     - byte offset between consecutive generic vertex attributes 
        @param nOffset     - offset of the first component of the first generic
                             vertex attribute in the array in the data store of
                             the buffer currently bound to the GL_ARRAY_BUFFER target
    **/
    void VertexAttribPointer(
        size_t    nIndex,
        GLint     nSize,
        GLenum    eType,
        GLboolean bNormalized,
        GLsizei   nStride,
        size_t    nOffset);

private:
    GLuint m_nVAO = std::numeric_limits<GLuint>::max();
};

using vao = base_vao;

} // namespace qx

#include <qx/gl/vao.inl>
