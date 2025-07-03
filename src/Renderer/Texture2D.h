#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer
{
    class Texture2D
    {
    public:
        Texture2D(
            const GLuint width,
            const GLuint height,
            const char* data,
            const unsigned int channels = 4,
            const GLenum filter = GL_LINEAR,
            const GLenum wrapMode = GL_CLAMP_TO_EDGE);
        Texture2D() = delete;
        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;
        Texture2D& operator=(Texture2D&&) noexcept;
        Texture2D(Texture2D&& texture2d);

        static void bind(const GLuint slot = 0);


        ~Texture2D();
    private:
        GLuint m_textureID = 0;
        GLuint m_width = 0;
        GLuint m_height = 0;
        GLenum m_mode;
        GLenum m_filter = GL_NEAREST;
        GLenum m_wrapMode = GL_CLAMP_TO_EDGE;
    };
}