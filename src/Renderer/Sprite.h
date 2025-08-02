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
        explicit Sprite( std::shared_ptr<Texture2D>      pTexture        = nullptr,                      //null texture
                         std::shared_ptr<ShaderProgram>  pShaderProgram  = nullptr,                      //null shader
                         const glm::vec2&                position        = glm::vec2(0.0f, 0.0f),    //corner
                         const glm::vec2&                size            = glm::vec2(1.0f, 1.0f),    //1-vector2
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
        bool setTexture(std::shared_ptr<Texture2D> pTexture);
        bool setShaderProgram(std::shared_ptr<ShaderProgram> pShaderProgram);
        bool setPosition(const glm::vec2& position);
        bool setSize(const glm::vec2& size);
        bool setRotation(float rotation);
        bool setVAO(GLuint VAO);
        bool setNVertex(GLsizei nVertex);
        bool setNVertexBuffers(GLsizei nVertexBuffers);
        bool setNTextureBuffers(GLsizei nTextureBuffers);
        bool setVertexCoords(const GLfloat vertexCoords[]);
        static bool setTextureCoords(const GLfloat textureCoords[]);

    private:
        //*NOTE* initialization before setters is done here
        std::shared_ptr<Texture2D>      m_pTexture          {}; //init to nullptr
        std::shared_ptr<ShaderProgram>  m_pShaderProgram    {}; //init to nullptr
        glm::vec2                       m_position          {}; //init to 0
        glm::vec2                       m_size              {}; //init to 0
        float                           m_rotation          {}; //init to 0
        GLuint                          m_VAO               {}; //init to empty
        GLuint                          m_vertexCoordsVBO   {}; //init to empty
        GLuint                          m_textureCoordsVBO  {}; //init to empty
        GLsizei                         m_nVertex           {}; //n - number (of vertex arrays)
        GLsizei                         m_nVertexBuffers    {}; //n - number (of vertex buffers) *NUMBERS(of something) ARE GENERALLY CONSTANT, but not always.
        GLsizei                         m_nTextureBuffers   {}; //n - number (of texture buffers)
        GLfloat                         m_vertexCoords[];
        GLfloat                         m_textureCoords[];
        //DEFAULT VALUES
        static constexpr GLsizei m_nVertexCoordsVertexesDefault = 6;  //number of vertexes by default (2D) in vertexCoords
        static constexpr GLsizei m_nTextureCoordsVertexesDefault = 6; //number of vertexes by default (2D) in textureCoords
        const GLfloat m_defaultVertexCoords[m_nVertexCoordsVertexesDefault * 2] =
            {
            // 2--3-  -1
            // | /   / |
            // 1-  -3--2
            // ^^^   ^^^
            //  X     Y 
            // X+Y Becomes
            // 2-----3 <-- 3 and 1 become one point
            // |  /  |
            // 3-----2 <-- 3 and 1 become one point

            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
            };
        const GLfloat m_defaultTextureCoords[m_nTextureCoordsVertexesDefault * 2] =
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