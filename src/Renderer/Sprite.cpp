#include "Sprite.h"
#include <utility>
#include <iostream>
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"

namespace RenderEngine
{
    Sprite::Sprite(std::shared_ptr<Texture2D> pTexture,
                   const std::string& initialSubTexture,
                   std::shared_ptr<ShaderProgram> pShaderProgram)
        : m_pTexture(std::move(pTexture))
        , m_pShaderProgram(std::move(pShaderProgram))
        , m_lastFrameId(0)
    {
        constexpr GLfloat vertexCoords[] = {
            // 1---2
            // | / |
            // 0  -3

            // X  Y
            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f
        };

        auto subTexture = Texture2D::getSubTexture(initialSubTexture);

        const GLfloat textureCoords[] = {
            // U  V
            subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
            subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
            subTexture.rightTopUV.x,   subTexture.rightTopUV.y,
            subTexture.rightTopUV.x,   subTexture.leftBottomUV.y,
        };

        const GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout vertexCoordsLayout;
        vertexCoordsLayout.addElementLayoutFloat(2, false);
        m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

        m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout textureCoordsLayout;
        textureCoordsLayout.addElementLayoutFloat(2, false);
        m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

        m_indexBuffer.init(indices, 6);

        VertexArray::unbind();
        IndexBuffer::unbind();
    }

    Sprite::~Sprite()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(m_nVertexBuffers, &m_vertexCoordsVBO);
        glDeleteBuffers(m_nTextureBuffers, &m_textureCoordsVBO);
    }
    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Sprite::render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer, const size_t frameId) const
    {
        if (m_lastFrameId != frameId)
        {
            m_lastFrameId = frameId;
            const FrameDescription& currentFrameDescription = m_framesDescriptions[frameId];

            const GLfloat textureCoords[] = {
                // U  V
                currentFrameDescription.leftBottomUV.x, currentFrameDescription.leftBottomUV.y,
                currentFrameDescription.leftBottomUV.x, currentFrameDescription.rightTopUV.y,
                currentFrameDescription.rightTopUV.x,   currentFrameDescription.rightTopUV.y,
                currentFrameDescription.rightTopUV.x,   currentFrameDescription.leftBottomUV.y,
            };

            m_textureCoordsBuffer.update(textureCoords, 2 * 4 * sizeof(GLfloat));
        }

        m_pShaderProgram->use();

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(position, 0.f));
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
        model = glm::scale(model, glm::vec3(size, 1.f));

        m_pShaderProgram->setMatrix4("modelMat", model);
        m_pShaderProgram->setFloat("layer", layer);

        glActiveTexture(GL_TEXTURE0);
        m_pTexture->bind();

        Renderer::draw(m_vertexArray, m_indexBuffer, *m_pShaderProgram);
    }

    //SETTERS
    void Sprite::setTexture(std::shared_ptr<Texture2D> pTexture)
    {
        //move the texture to the sprite, so it can be deleted when the sprite is deleted, prevents unnecessary copying.
        if (pTexture == nullptr) { std::cerr << "ERROR: null texture pointer!\n"; }
        m_pTexture = std::move(pTexture);
    }
    void Sprite::setShaderProgram(std::shared_ptr<ShaderProgram> pShaderProgram)
    {
        if (pShaderProgram == nullptr) { std::cerr << "ERROR: null shader pointer!\n"; }
        m_pShaderProgram = std::move(pShaderProgram);
    }
    void Sprite::setPosition(const glm::vec2& position)
    {
        //FIXME: add out of bounds checks.
        m_position = position;
    }
    void Sprite::setSize(const glm::vec2& size)
    {
        if (size.x == 0) { std::cerr << "WARNING: zero size (x) sprite!\n"; }
        if (size.y == 0) { std::cerr << "WARNING: zero size (y) sprite!\n"; }
        m_size = size;
    }

    void Sprite::setRotation(const float rotation)
    {
        if (rotation == 0) { std::cout << "WARNING? : zero rotation! (Might be unintended, ignore otherwise)\n"; }
        m_rotation = rotation;
    }

    void Sprite::setVAO(const GLuint VAO)
    {
        if (VAO == 0) { std::cerr << "Warning: null VAO!\n"; }
        m_VAO = VAO;
    }

    void Sprite::setNVertex(const GLsizei nVertex)
    {
        if (nVertex == 0) { std::cerr << "Warning: 0 Vertexes!\n"; }
        m_nVertex = nVertex;
    }

    void Sprite::setNVertexBuffers(const GLsizei nVertexBuffers)
    {
        if (nVertexBuffers == 0)
        { std::cerr << "Warning: 0 Vertex Buffers!\n"; }
        m_nVertexBuffers = nVertexBuffers;
    }

    void Sprite::setNTextureBuffers(const GLsizei nTextureBuffers)
    {
        if (nTextureBuffers == 0) { std::cerr << "Warning: 0 Texture Buffers!\n"; }
        m_nTextureBuffers = nTextureBuffers;
    }

    void Sprite::setTextureCoords(const std::array<GLfloat, 12>& textureCoords)
    {
        if (textureCoords.data() == nullptr) { std::cerr << "Warning: null texture coords!\n"; }
        m_textureCoords = textureCoords;
    }

    void Sprite::setVertexCoords(const std::array<GLfloat, 12>& vertexCoords) // NOLINT(*-convert-member-functions-to-static) //no it cannot be static.
    {
        if (vertexCoords.data() == nullptr){ std::cerr << "Warning: null vertex coords!\n"; }
        m_vertexCoords = vertexCoords;
    }
}
