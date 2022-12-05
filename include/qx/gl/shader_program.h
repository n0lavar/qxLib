/**

    @file      shader_program.h
    @brief     Contains qx::base_shader_program class
    @author    Khrapov
    @date      16.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/shaders.h>
#include <qx/lib_config/lib_asserts.h>

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
    QX_NONCOPYABLE(base_shader_program);

    /**
        @brief base_shader_program object constructor
    **/
    base_shader_program() = default;

    /**
        @brief base_shader_program object constructor
        @param baseShaderProgram - shader program rvalue ref
    **/
    base_shader_program(base_shader_program&& baseShaderProgram) noexcept;

    /**
        @brief base_shader_program object destructor
    **/
    ~base_shader_program() noexcept;

    /**
        @brief Init shader program
    **/
    void Init() noexcept;

    /**
        @brief  Attach shader to the program
        @tparam ShaderType - shader type
        @param  pShader    - shader object pointer
    **/
    template<GLenum ShaderType>
    void AttachShader(shader_base<ShaderType>* pShader) noexcept;

    /**
        @brief  Link attached shaders
        @retval - true if success
    **/
    bool Link() noexcept;

    /**
        @brief Use shader program
    **/
    void Use() const noexcept;

    /**
        @brief Drop current shader
    **/
    void Unuse() const noexcept;

    /**
        @brief  Get shader program parameter
        @param  eParameter - shader program parameter
                \see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
        @retval            - shader program parameter
    **/
    GLint GetParameter(GLenum eParameter) const noexcept;

    /**
        @brief  Get shader buffer name
        @retval - shader buffer name
    **/
    GLuint GetBufferName() const noexcept;

    /**
        @brief  Specify the value of a uniform variable
        @tparam T                - parameter type
        @param  nUniformLocation - the location of the uniform variable to be modified
        @param  pValue           - a pointer to an array of count values that will be
                                   used to update the specified uniform variable.
        @param  nCount           - number of values that are to be modified.
    **/
    template<typename T>
    void SetUniform(GLint nUniformLocation, const T* pValue, GLsizei nCount) noexcept;

    /**
        @brief  Specify the value of a uniform variable
        @tparam T       - parameter type
        @param  pszName - the name of the uniform variable to be modified.
        @param  pValue  - a pointer to an array of count values that will be
                          used to update the specified uniform variable.
        @param  nCount  - number of values that are to be modified.
    **/
    template<typename T>
    void SetUniform(const GLchar* pszName, const T* pValue, GLsizei nCount) noexcept;

    /**
        @brief  Specify the value of a uniform variable
        @tparam T                - parameter type
        @param  nUniformLocation - the location of the uniform variable to be modified
        @param  value            - the value of a uniform variable
    **/
    template<typename T>
    void SetUniform(GLint nUniformLocation, const T& value) noexcept;

    /**
        @brief  Specify the value of a uniform variable
        @tparam T       - parameter type
        @param  pszName - the name of the uniform variable to be modified 
        @param  value   - the value of a uniform variable. 
    **/
    template<typename T>
    void SetUniform(const GLchar* pszName, const T& value) noexcept;

    /**
        @brief  Get uniform location based on it's name
        @param  pszName - uniform string name
        @retval         - location number
    **/
    GLint GetUniformLocation(const GLchar* pszName) const noexcept;

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
        @retval             - true if include extension is supported and successfully added
    **/
    static bool AddInclude(const char* pszName, GLint nNameLength, const char* pszText, GLint nTextLength) noexcept;

    /**
        @brief Dispatch program compute
        @param nGroupsX - The number of work groups to be launched in the X dimension 
        @param nGroupsY - The number of work groups to be launched in the Y dimension 
        @param nGroupsZ - The number of work groups to be launched in the Z dimension 
    **/
    static void DispatchCompute(GLuint nGroupsX, GLuint nGroupsY, GLuint nGroupsZ) noexcept;

    /**
        @brief  operator==
        @param  other - other shader program
        @retval       - true, if objects are equal
    **/
    bool operator==(const base_shader_program& other) const noexcept;

    /**
        @brief  operator=
        @param  baseShaderProgram - shader program rvalue ref
        @retval                   - this object reference
    **/
    base_shader_program& operator=(base_shader_program&& baseShaderProgram) noexcept;



private:
    GLuint m_nProgram = std::numeric_limits<GLuint>::max();
};

using shader_program = base_shader_program;

} // namespace qx

#include <qx/gl/shader_program.inl>
