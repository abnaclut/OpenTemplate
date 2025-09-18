#include "ShaderProgram.h"

#include <iostream>
#include <ostream>
#include <glm/gtc/type_ptr.hpp>

namespace RenderEngine
{
    //CONSTRUCTORS
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        //CREATE VERTEX SHADER
        GLuint vertexShaderID;
        if (createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID) == false)
        {
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
            return;
        }

        //CREATE FRAGMENT SHADER
        GLuint fragmentShaderID;
        if (createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID) == false)
        {
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
            glDeleteShader(vertexShaderID);
            return;
        }

        //LINK SHADERS
        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        //ERROR HANDLING
        GLint result;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            glDeleteProgram(m_ID);
            glDeleteShader(vertexShaderID);
        }
        else
        {
            m_isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
    //OPERATORS
    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;
        //SET VALUES TO DEFAULT
        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;
        //SET VALUES TO DEFAULT
        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
    }

    //SHADER CREATION IMPLEMENTATION
    bool ShaderProgram::createShader(const std::string& source, GLenum shaderType, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        //SHADER COMPILATION
        glCompileShader(shaderID);

        GLint result;
        //ERROR HANDLING
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    //DESTRUCTOR
    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }

    void ShaderProgram::use() const { glUseProgram(m_ID); }
    void ShaderProgram::unuse() { glUseProgram(0); }

    void ShaderProgram::setInt(const std::string& name, const GLint value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void ShaderProgram::setFloat(const std::string& name, const GLfloat value) const
    {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
