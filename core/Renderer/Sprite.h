#pragma once
#include <memory>

#ifndef GLAD_INCLUDED
#include "../../external/glad/include/glad/glad.h"
#define GLAD_INCLUDED
#endif

#include "../../external/glm/glm/glm.hpp"
#include "../../external/glm/glm/vec2.hpp"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "../TemplateGenerator/Tools/tools.h"

namespace RenderEngine
{
    class Texture2D;
    class ShaderProgram;

    class Sprite
    {
    public:
        struct FrameDescription
        {
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
        void insertFrames(std::vector<FrameDescription> framesDescriptions); //FIXME implement
        double getFrameDuration(const size_t frameId) const; //FIXME implement
        size_t getFramesCount() const; //FIXME implement

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
        VertexArray                     m_vertexArray;
        VertexBuffer                    m_vertexCoordsBuffer;
        VertexBuffer                    m_textureCoordsBuffer;
        IndexBuffer                     m_indexBuffer;
        std::vector<FrameDescription>   m_framesDescriptions;
        mutable size_t                  m_lastFrameId;
    };
}