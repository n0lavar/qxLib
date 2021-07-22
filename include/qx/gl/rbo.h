//==============================================================================
//
//!\file                            rbo.h
//
//!\brief       Render buffer object classes: rbo and copyble_rbo
//!\details     ~
//
//!\author      Khrapov
//!\date        20.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/typedefs.h>
#include <qx/gl/buffer_classes.h>
#include <qx/gl/ibuffer.h>

namespace qx
{

//==============================================================================
//
//!\class                    qx::base_rbo<COPYBLE>
//
//!\brief   Base RBO class. Use rbo or copyble_rbo
//!\details ~
//
//!\author  Khrapov
//!\date    10.07.2020
//
//==============================================================================
template<bool COPYBLE>
class base_rbo : IBuffer
{
public:

    friend class base_rbo;

            void    Init                (size_t     nWidth,
                                         size_t     nHeight,
                                         GLenum     eInternalFormat,
                                         GLenum     eAttachment,
                                         size_t     nMultisamples = 0);

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

protected:

    template<class Derived>
            void    Assign          (const Derived& other);

private:

    GLuint m_nBuffer            = std::numeric_limits<GLuint>::max();
    GLenum m_eInternalFormat    = 0;
    GLenum m_eAttachmentType    = 0;
    size_t m_nWidth             = 0;
    size_t m_nHeight            = 0;
};

template<bool COPYBLE>
inline GLuint base_rbo<COPYBLE>::GetBufferName(void) const
{
    return m_nBuffer;
}
template<bool COPYBLE>
inline bool base_rbo<COPYBLE>::IsGenerated(void) const
{
    return m_nBuffer != std::numeric_limits<GLuint>::max();
}
template<bool COPYBLE>
template<class Derived>
inline void base_rbo<COPYBLE>::Assign(const Derived& other)
{
    m_nBuffer = other.m_nBuffer;
}
template<bool COPYBLE>
inline size_t base_rbo<COPYBLE>::GetWidth(void) const
{
    return m_nWidth;
}
template<bool COPYBLE>
inline size_t base_rbo<COPYBLE>::GetHeight(void) const
{
    return m_nHeight;
}
template<bool COPYBLE>
inline GLenum base_rbo<COPYBLE>::GetInternalFormat(void) const
{
    return m_eInternalFormat;
}

template<bool COPYBLE>
inline GLenum base_rbo<COPYBLE>::GetAttachmentType(void) const
{
    return m_eAttachmentType;
}

QX_DEFINE_BUFFER_CLASSES(rbo)

}

#include <qx/gl/rbo.inl>
