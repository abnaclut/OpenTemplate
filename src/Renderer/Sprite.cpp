#include "Sprite.h"

#include <utility>
#include <iostream>
#include "gtx/quaternion.hpp"

namespace Renderer
{
    Sprite::Sprite(std::shared_ptr<Texture2D>       pTexture,
                   std::shared_ptr<ShaderProgram>   pShaderProgram,
                   const glm::vec2&                 position,
                   const glm::vec2&                 size,
                   float                            rotation,
                   GLuint                           VAO,
                   GLsizei                          nVertex,          //n - number (of vertex arrays)
                   GLsizei                          nVertexBuffers,   //n - number (of vertex buffers)
                   GLsizei                          nTextureBuffers
                   )
    {
        //INITIALIZE FIELDS
        setTexture(std::move(pTexture)); //move the texture to the sprite, so it can be deleted when the sprite is deleted, prevents unnecessary copying.
        setShaderProgram(std::move(pShaderProgram)); //move the shader program to the sprite, so it can be deleted when the sprite is deleted, prevents unnecessary copying.
        setPosition(position);
        setSize(size);
        setRotation(rotation);
        m_VAO = VAO;
        m_nVertex = nVertex;
        m_nVertexBuffers = nVertexBuffers;
        m_nTextureBuffers = nTextureBuffers;

        //GENERATE STUFF
        glGenVertexArrays(nVertex, &m_VAO);
        glBindVertexArray(m_VAO);
        //
        int index = 0;
        int vectorSize = 2;
        //TODO: pass everything by a variable(or &)
        glGenBuffers(nVertexBuffers, &m_vertexCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_defaultVertexCoords), m_defaultVertexCoords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(0, vectorSize, GL_FLOAT, GL_FALSE, 0, nullptr);
        index++; // increment index for the next buffer.
        glGenBuffers(m_nTextureBuffers, &m_textureCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_defaultTextureCoords), m_defaultTextureCoords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(1, vectorSize, GL_FLOAT, GL_FALSE, 0, nullptr);
        //
        glBindBuffer(GL_ARRAY_BUFFER, 0); //bind default buffer upon ending generating.
        glBindVertexArray(0); //bind default VAO upon ending generating.
    }

    Sprite::~Sprite()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(m_nVertexBuffers, &m_vertexCoordsVBO);
        glDeleteBuffers(m_nTextureBuffers, &m_textureCoordsVBO);
    }

    bool Sprite::render() const
    {

    }

    bool Sprite::setPosition(const glm::vec2& position)
    {
        //FIXME: add out of bounds checks.
        m_position = position;
        //hope your machine executes a = b properly
        return true;
    }

    bool Sprite::setSize(const glm::vec2& size)
    {
        if (size.x == 0 || size.y == 0)
        {
            std::cerr << "WARNING: zero sized sprite!\n";
            return false;
        }
        m_size = size;
        //hope your machine executes a = b properly
        return true;
    }

    bool Sprite::setTexture(std::shared_ptr<Texture2D> pTexture)
    {
        //move the texture to the sprite, so it can be deleted when the sprite is deleted, prevents unnecessary copying.
        if (pTexture == nullptr)
        {
            std::cerr << "ERROR: null texture pointer!\n";
            return false;
        }
        m_pTexture = std::move(pTexture);
        if (m_pTexture == pTexture) { return true; } // Better safe than teeny tiny little performance optimization.
        std::cout << "WARNING: Texture was not assigned, expect issues!\n";
        return false;
    }

    bool Sprite::setShaderProgram(std::shared_ptr<ShaderProgram> pShaderProgram)
    {
        if (pShaderProgram == nullptr)
        {
            std::cerr << "ERROR: null shader pointer!\n";
            return false;
        }
        m_pShaderProgram = std::move(pShaderProgram);
        if (m_pShaderProgram == pShaderProgram) { return true; } // Better safe than teeny tiny little performance optimization.
        std::cout << "WARNING: Shader program was not assigned, expect issues!\n";
        return false;
    }

    bool Sprite::setRotation(const float rotation)
    {
        if (rotation == 0)
        {
            std::cerr << "WARNING: zero rotation!\n"; //Why would anyone do this anyway, and yet, someone will?
            return false;
        }
        m_rotation = rotation;
        //hope your machine executes a = b properly
        return true;
    }
    //TODO: 12 is the number of values in texture coords, this will be changed when I add 3D.
    bool Sprite::setTextureCoords(const GLfloat textureCoords[])
    {
        if (!textureCoords) { /*error*/ return false; }
        else
        {
            // ReSharper disable once CppDFAUnreadVariable      <-- why human programmers will not be replaced by AI
            // ReSharper disable once CppDFAUnusedValue         <-- why human programmers will not be replaced by AI
            constexpr size_t sizeOfArray = 12;
            std::memmove(m_textureCoords, textureCoords, sizeOfArray * sizeof(GLfloat));
        }
        return true;
    }

}
