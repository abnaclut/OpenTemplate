#include "ShaderProgram.h"

namespace RenderEngine
{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        //CREATE VERTEX SHADER
        GLuint vertexShaderID;
        //FIXME add a typedef for GlVertexShader_type = GL_VERTEX_SHADER
        if (createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID) == false)
        {
            std::cerr << "Vertex Shader compilation FAILED!\n";
            return;
        }

        //CREATE FRAGMENT SHADER
        GLuint fragmentShaderID;
        //FIXME add a typedef for GlFragmentShader_type = GL_FRAGMENT_SHADER
        if (createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID) == false)
        {
            std::cerr << "Fragment Shader compilation FAILED!\n";
            glDeleteShader(vertexShaderID);
            return;
        }

        //TODO move to a separate function! void linkShaders()
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
            std::cerr << "Shader Program LINKING FAILED! Info: \n" << infoLog << "\n";
            glDeleteProgram(m_ID);
            glDeleteShader(vertexShaderID);
        } else { m_isCompiled = true; }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
    ShaderProgram::~ShaderProgram() { glDeleteProgram(m_ID); }

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

    bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
    {
        //FIXME!!! Has to be remade properly. Remove hardcoding, add error-checks, ....
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
            std::cout << "Error! Shader compilation failed! Info: \n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    void ShaderProgram::use() const { glUseProgram(m_ID); }
    void ShaderProgram::unuse()     { glUseProgram(0); }
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
        //FIXME add a bool transpose param
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
