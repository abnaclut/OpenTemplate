#pragma once
#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H
#endif //TEXTURE_2D_H
#include <glad/glad.h>

namespace Renderer
{
    class Texture2D
    {
    public:
        Texture2D(
            GLuint width,
            GLuint height,
            const char* data,
            unsigned int channels = 4,
            const GLenum filter = GL_LINEAR,
            const GLenum wrapMode = GL_CLAMP_TO_EDGE);
        Texture2D() = delete;
        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;
        Texture2D& operator=(Texture2D&&) noexcept;
        Texture2D(Texture2D&& texture2d) noexcept;

        void bind(GLuint slot = 0) const;


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