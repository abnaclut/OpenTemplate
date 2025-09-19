#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <array>
#include "../Tools/tools.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <glm/vec2.hpp>
#endif //SPRITE_H

namespace RenderEngine
{
    class Texture2D;
    class ShaderProgram;

    class Sprite
    {
    public:
        struct FrameDescription {
            FrameDescription(const glm::vec2 _leftBottomUV, const glm::vec2 _rightTopUV, const double _duration)
                : leftBottomUV(_leftBottomUV)
                , rightTopUV(_rightTopUV)
                , duration(_duration)
            {}
            glm::vec2 leftBottomUV;
            glm::vec2 rightTopUV;
            double duration;
        };
        Sprite(std::shared_ptr<Texture2D> pTexture,
               const std::string& initialSubTexture,
               std::shared_ptr<ShaderProgram> pShaderProgram);
        ~Sprite();
        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        void render(const glm::vec2& position,
                    const glm::vec2& size,
                    float rotation,
                    float layer = 0.f,
                    size_t frameId = 0) const;
        void setTexture(std::shared_ptr<Texture2D> pTexture);
        void setShaderProgram(std::shared_ptr<ShaderProgram> pShaderProgram);
        void setPosition(const glm::vec2& position);
        void setSize(const glm::vec2& size);
        void setRotation(float rotation);
        void setVAO(GLuint VAO);
        void setNVertex(GLsizei nVertex);
        void setNVertexBuffers(GLsizei nVertexBuffers);
        void setNTextureBuffers(GLsizei nTextureBuffers);
        void setVertexCoords(const std::array<GLfloat, 12>& vertexCoords);
        void setTextureCoords(const std::array<GLfloat, 12>& textureCoords);
        void insertFrames(std::vector<FrameDescription> framesDescriptions);
        double getFrameDuration(const size_t frameId) const;
        size_t getFramesCount() const;

    protected:
        //*NOTE* constructor overrides {}-Initialization (safety measure)
        std::shared_ptr<Texture2D>      m_pTexture            ; //init to nullptr
        std::shared_ptr<ShaderProgram>  m_pShaderProgram      ; //init to nullptr
        glm::vec2                       m_position{}          ; //init to 0
        glm::vec2                       m_size{}              ; //init to 0
        float                           m_rotation          {}; //init to 0
        GLuint                          m_VAO               {}; //init to empty
        GLuint                          m_vertexCoordsVBO   {}; //init to empty
        GLuint                          m_textureCoordsVBO  {}; //init to empty
        GLsizei                         m_nVertex           {}; //n - number (of vertex arrays)
        GLsizei                         m_nVertexBuffers    {}; //n - number (of vertex buffers) *NUMBERS(of something) ARE GENERALLY CONSTANT, but not always.
        GLsizei                         m_nTextureBuffers   {}; //n - number (of texture buffers)
        std::array<GLfloat, 12>         m_vertexCoords        ; //12 cuz 2 * 3 vertexes in 2D is 12 coordinates
        std::array<GLfloat, 12>         m_textureCoords       ; //same
        VertexArray                     m_vertexArray;
        VertexBuffer                    m_vertexCoordsBuffer;
        VertexBuffer                    m_textureCoordsBuffer;
        IndexBuffer                     m_indexBuffer;
        std::vector<FrameDescription> m_framesDescriptions;
        mutable size_t m_lastFrameId;
        //DEFAULT VALUES
        static constexpr GLsizei m_nVertexCoordsVertexesDefault = 6;  //number of vertexes by default (2D) in vertexCoords
        static constexpr GLsizei m_nTextureCoordsVertexesDefault = 6; //number of vertexes by default (2D) in textureCoords
        const std::array<GLfloat, m_nVertexCoordsVertexesDefault * 2> m_defaultVertexCoords =
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
        const std::array<GLfloat, m_nTextureCoordsVertexesDefault * 2> m_defaultTextureCoords =
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