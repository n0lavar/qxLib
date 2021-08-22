/**

    @file      shader_program.h
    @brief     Contains qx::base_shader_program class
    @author    Khrapov
    @date      16.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/shaders.h>

#include <glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace qx
{

/**

    @class   base_shader_program
    @brief   Shader program class
    @details ~
    @author  Khrapov
    @date    16.01.2020

**/
class base_shader_program
{
public:
    QX_NONCOPYABLE(base_shader_program)
    QX_MOVABLE(base_shader_program)

    /**
        @brief base_shader_program object constructor
    **/
    base_shader_program(void) = default;

    /**
        @brief base_shader_program object destructor
    **/
    ~base_shader_program(void);

    /**
        @brief Init shader program
    **/
    void Init(void);

    /**
        @brief  Attach shader to the program
        @tparam ShaderType - shader type
        @param  pShader    - shader object pointer
    **/
    template<GLenum ShaderType>
    void AttachShader(shader_base<ShaderType>* pShader);

    /**
        @brief  Link attached shaders
        @retval - true if success
    **/
    bool Link(void);

    /**
        @brief Use shader program
    **/
    void Use(void) const;

    /**
        @brief Drop current shader
    **/
    void Unuse(void) const;

    /**
        @brief  Get shader program parameter
        @param  eParameter - shader program parameter
                \see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
        @retval            - shader program parameter
    **/
    GLint GetParameter(GLenum eParameter) const;

    /**
        @brief  Get shader buffer name
        @retval - shader buffer name
    **/
    GLuint GetBufferName(void) const;

    /**
        @brief  Specify the value of a uniform variable
        @tparam T                - parameter type
        @param  nUniformLocation - the location of the uniform variable to be modified
        @param  pValue           - a pointer to an array of count values that will be
                                   used to update the specified uniform variable.
        @param  nCount           - number of values that are to be modified.
    **/
    template<typename T>
    void SetUniform(GLint nUniformLocation, const T* pValue, GLsizei nCount);

    /**
        @brief  Specify the value of a uniform variable
        @tparam T       - parameter type
        @param  pszName - the name of the uniform variable to be modified.
        @param  pValue  - a pointer to an array of count values that will be
                          used to update the specified uniform variable.
        @param  nCount  - number of values that are to be modified.
    **/
    template<typename T>
    void SetUniform(const GLchar* pszName, const T* pValue, GLsizei nCount);

    /**
        @brief  Specify the value of a uniform variable
        @tparam T                - parameter type
        @param  nUniformLocation - the location of the uniform variable to be modified
        @param  value            - the value of a uniform variable
    **/
    template<typename T>
    void SetUniform(GLint nUniformLocation, const T& value);

    /**
        @brief  Specify the value of a uniform variable
        @tparam T       - parameter type
        @param  pszName - the name of the uniform variable to be modified 
        @param  value   - the value of a uniform variable. 
    **/
    template<typename T>
    void SetUniform(const GLchar* pszName, const T& value);

    /**
        @brief  Get uniform location based on it's name
        @param  pszName - uniform string name
        @param  pError  - error string pointer
        @retval         - location number
    **/
    GLint GetUniformLocation(const GLchar* pszName, string* pError = nullptr)
        const;

    /**
        @brief   Add include string
        @details ARB_shading_language_include is required for this function
                 calling of this function must be before shader's compilation
                 usage example:
                 #version 440 core
                 #extension GL_ARB_shading_language_include : require
                 #include "/header.h"
        @param pszName      - name that you will #include in shader (should be with leading '/') 
        @param nNameLength  - name length 
        @param pszText      - text that will be placed in shader instead of #include 
        @param nTextLength  - text length 
    **/
    static void AddInclude(
        const char* pszName,
        GLint       nNameLength,
        const char* pszText,
        GLint       nTextLength);

    /**
        @brief Dispatch program compute
        @param nGroupsX - The number of work groups to be launched in the X dimension 
        @param nGroupsY - The number of work groups to be launched in the Y dimension 
        @param nGroupsZ - The number of work groups to be launched in the Z dimension 
    **/
    static void DispatchCompute(
        GLuint nGroupsX,
        GLuint nGroupsY,
        GLuint nGroupsZ);

    /**
        @brief  operator==
        @param  other - other shader program
        @retval       - true, if objects are equal
    **/
    bool operator==(const base_shader_program& other) const;

private:
    GLuint m_nProgram = std::numeric_limits<GLuint>::max();
};

using shader_program = base_shader_program;

} // namespace qx

#include <qx/gl/shader_program.inl>
