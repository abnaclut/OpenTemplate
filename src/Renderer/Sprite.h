#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../Tools/tools.h"
#endif //SPRITE_H


namespace Renderer
{
    class Texture2D;
    class ShaderProgram;
    class Sprite
    {
    public:
        Sprite( std::shared_ptr<Texture2D>      pTexture,                                       //
                std::shared_ptr<ShaderProgram>  pShaderProgram,                                 //
                const glm::vec2&                position        = glm::vec2(0.0f, 0.0f),    //0-vector2
                const glm::vec2&                size            = glm::vec2(1.0f, 1.0f),    //0-vector2
                float                           rotation        = 0.0f,                         //no rotation
                GLuint                          VAO             = 0,                            //empty
                GLsizei                         nVertex         = 12,                           //twice the number of vertices as rect is 2 triangles.
                GLsizei                         nVertexBuffers  = 1,                            //1 buffer
                GLsizei                         nTextureBuffers = 1                             //1 buffer
               );
        ~Sprite();

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        [[nodiscard]] bool render() const;
        //nodiscard is a temporary measure to stop warning from popping up until I implement the render method.
        bool setPosition(const glm::vec2& position);
        bool setSize(const glm::vec2& size);
        bool setTexture(std::shared_ptr<Texture2D> pTexture);
        bool setShaderProgram(std::shared_ptr<ShaderProgram> pShaderProgram);
        bool setRotation(float rotation);
        static bool setTextureCoords(const GLfloat textureCoords[]);


    private:
        std::shared_ptr<Texture2D>      m_pTexture;
        std::shared_ptr<ShaderProgram>  m_pShaderProgram;
        glm::vec2                       m_position;
        glm::vec2                       m_size;
        float                           m_rotation;
        GLuint                          m_VAO;
        GLuint                          m_vertexCoordsVBO;
        GLuint                          m_textureCoordsVBO;
        GLsizei                         m_nVertex;            //n - number (of vertex arrays)
        GLsizei                         m_nVertexBuffers;     //n - number (of vertex buffers) *NUMBERS(of something) ARE GENERALLY CONSTANT, but not always.
        GLsizei                         m_nTextureBuffers;    //n - number (of texture buffers)
        GLfloat                         m_vertexCoords[];
        static GLfloat                  m_textureCoords[];
        //DEFAULT VALUE
        const GLfloat m_defaultVertexCoords[] =
            {
            // 2--3-  -1
            // | /   / |
            // 1-  -3--2
            // ^^^   ^^^
            //  X     Y
            // X+Y Becomes
            // 2--3--1 <--
            // |  /  |
            // 1--3--2

            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
            };
        const GLfloat m_defaultTextureCoords[] =
        {
            // U  V

            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
            };
    };
}