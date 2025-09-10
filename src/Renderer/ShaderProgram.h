#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#endif //SHADER_PROGRAM_H


namespace RenderEngine
{
    class ShaderProgram
    {
    public:
        //CONSTRUCTORS
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        //NOT ALLOWING EMPTY SHADER
        ShaderProgram() = delete;
        //NOT ALLOWING SHADER-COPY / SAME IDs
        ShaderProgram(ShaderProgram&) = delete;
        //NOT ALLOWING SHADER ASSIGMENT / SAME IDs
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        //moving operators
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

        //DESTRUCTORS
        ~ShaderProgram();

        void setInt(const std::string& name, GLint value) const;
        [[nodiscard]] bool isCompiled() const { return m_isCompiled; };
        void use() const;
        static void unuse();

        void setMatrix4(const std::string& name, const glm::mat4& matrix) const;

    private:
        static bool createShader(const std::string& source, GLenum shaderType, GLuint& shaderID);
        bool m_isCompiled = false;
        GLuint m_ID = 0;
    };



}
