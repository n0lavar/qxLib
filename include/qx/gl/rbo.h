//==============================================================================
//
//!\file                            rbo.h
//
//!\brief       Contains qx::base_rbo class
//!\details     ~
//
//!\author      Khrapov
//!\date        20.01.2020
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
//!\class                    qx::base_rbo
//
//!\brief   Base RBO class
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
class base_rbo : IBuffer
{
public:

            void    Init                (size_t     nWidth,
                                         size_t     nHeight,
                                         GLenum     eInternalFormat,
                                         GLenum     eAttachment,
                                         size_t     nMultisamples = 0);

    virtual         ~base_rbo           (void);

    virtual void    Generate            (void)          override;
    virtual void    Delete              (void)          override;
    virtual void    Bind                (void) const    override;
    virtual void    Unbind              (void) const    override;
    virtual GLuint  GetBufferName       (void) const    override;
    virtual bool    IsGenerated         (void) const    override;

    size_t          GetWidth            (void) const;
    size_t          GetHeight           (void) const;
    GLenum          GetInternalFormat   (void) const;
    GLenum          GetAttachmentType   (void) const;

private:

    GLuint m_nBuffer            = std::numeric_limits<GLuint>::max();
    GLenum m_eInternalFormat    = 0;
    GLenum m_eAttachmentType    = 0;
    size_t m_nWidth             = 0;
    size_t m_nHeight            = 0;
};

inline GLuint base_rbo::GetBufferName(void) const
{
    return m_nBuffer;
}
inline bool base_rbo::IsGenerated(void) const
{
    return m_nBuffer != std::numeric_limits<GLuint>::max();
}
inline size_t base_rbo::GetWidth(void) const
{
    return m_nWidth;
}
inline size_t base_rbo::GetHeight(void) const
{
    return m_nHeight;
}
inline GLenum base_rbo::GetInternalFormat(void) const
{
    return m_eInternalFormat;
}
inline GLenum base_rbo::GetAttachmentType(void) const
{
    return m_eAttachmentType;
}

using rbo = base_rbo;

}

#include <qx/gl/rbo.inl>
