#include "Sprite.h"
#include <utility>
#include <iostream>
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Renderer
{
    Sprite::Sprite(std::shared_ptr<Texture2D>       pTexture,
                   std::shared_ptr<ShaderProgram>   pShaderProgram,
                   const glm::vec2&                 position,
                   const glm::vec2&                 size,
                   const float                      rotation,
                   const GLuint                     VAO,
                   const GLsizei                    nVertex,          //n - number (of vertex arrays)
                   const GLsizei                    nVertexBuffers,   //n - number (of vertex buffers)
                   const GLsizei                    nTextureBuffers   //n - number (of texture buffers)
                   )
    {
        //INITIALIZE FIELDS
        setTexture(std::move(pTexture)); //move the texture to the sprite, so it can be deleted when the sprite is deleted, prevents unnecessary copying.
        setShaderProgram(std::move(pShaderProgram)); //move the shader program to the sprite, so it can be deleted when the sprite is deleted, prevents unnecessary copying.
        setPosition(position);
        setSize(size);
        setRotation(rotation);
        setVAO(VAO);
        setNVertex(nVertex);
        setNVertexBuffers(nVertexBuffers);
        setNTextureBuffers(nTextureBuffers);
        //TEMP
        int index = 0;
        int vectorSize = 2;
        //GENERATE STUFF
        glGenVertexArrays(nVertex, &m_VAO);
        glBindVertexArray(m_VAO);
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
    // ReSharper disable once CppMemberFunctionMayBeStatic
    bool Sprite::render() const // NOLINT(*-convert-member-functions-to-static)
    {
        m_pShaderProgram->use();

        auto model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(m_position, 0.0f));
        model = glm::translate(model, glm::vec3(0.5f * m_size.x,0.5f * m_size.y, 0.0f));
        model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y ,0.0f));
        model = glm::scale(model, glm::vec3(m_size, 1.0f));

        glBindVertexArray(m_VAO);
        m_pShaderProgram->setMatrix4("model", model);

        glActiveTexture(GL_TEXTURE0);
        m_pTexture->bind();

        glDrawArrays(GL_TRIANGLES, 0, m_nVertex);
        glBindVertexArray(0);

        return true;
    }

    //SETTERS
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
    bool Sprite::setRotation(const float rotation)
    {
        if (rotation == 0)
        {
            std::cerr << "WARNING: zero rotation!\n"; //Why would anyone do this anyway, and yet, someone will?
            return false;  // Well, it is technically correct with rot==0, make it return true if you want it to.
        }
        m_rotation = rotation;
        //hope your machine executes a = b properly
        return true;
    }
    bool Sprite::setVAO(const GLuint VAO)
    {
        if (VAO == 0)
        {
            std::cerr << "ERROR: null VAO!\n";
            return false;
        }
        m_VAO = VAO;
        //hope your machine executes a = b properly
        return true;
    }
    bool Sprite::setNVertex(const GLsizei nVertex)
    {
        if (nVertex == 0)
        {
            std::cerr << "ERROR: null nVertex!\n";
            return false;
        }
        m_nVertex = nVertex;
        //hope your machine executes a = b properly
        return true;
    }
    bool Sprite::setNVertexBuffers(const GLsizei nVertexBuffers)
    {
        if (nVertexBuffers == 0)
        {
            std::cerr << "ERROR: null nVertexBuffers!\n";
            return false;
        }
        m_nVertexBuffers = nVertexBuffers;
        //hope your machine executes a = b properly
        return true;
    }
    bool Sprite::setNTextureBuffers(const GLsizei nTextureBuffers)
    {
        if (nTextureBuffers == 0)
        {
            std::cerr << "ERROR: null nTextureBuffers!\n";
            return false;
        }
        m_nTextureBuffers = nTextureBuffers;
        //hope your machine executes a = b properly
        return true;
    }
    bool Sprite::setTextureCoords(const GLfloat textureCoords[])
    {
        if (!textureCoords)
        {
            std::cerr << "ERROR: null texture coords!\n";
            return false;
        }
        if (std::memmove(m_textureCoords, textureCoords, (m_nTextureCoordsVertexesDefault * sizeof(GLfloat))))
        { return true; }
        //if memmove failed
        std::cout << "WARNING: texture coords were not assigned, expect issues!\n";
        return false;
    }
    bool Sprite::setVertexCoords(const GLfloat vertexCoords[]) // NOLINT(*-convert-member-functions-to-static) //no it cannot be static.
    {
        if (vertexCoords == nullptr)
        {
            std::cerr << "ERROR: null vertex coords!\n";
            return false;
        }
        else
        {
            if (std::memmove(m_vertexCoords, vertexCoords, (m_nVertexCoordsVertexesDefault * sizeof(GLfloat)))) { return true; }
            // in this case a non-null pointer evaluates to true, nullptr == false
        }
        std::cout << "WARNING: vertex coords were not assigned, expect issues!\n";
        return false;
    }

}
