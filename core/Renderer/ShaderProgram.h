#pragma once
#ifndef OT_SHADERPROGRAM_H
#define OT_SHADERPROGRAM_H

#include "../Includes/includes.h"

namespace RenderEngine
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderProgram() = delete;
        ShaderProgram(ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
        ~ShaderProgram();
        void setInt(const std::string& name, GLint value) const;
        void setFloat(const std::string& name, GLfloat value) const;
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
#endif // OT_SHADERPROGRAM_H