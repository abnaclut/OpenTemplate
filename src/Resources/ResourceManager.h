#pragma once

#include <memory>
#include <string>
#include <map>

namespace Renderer
{
    class ShaderProgram;
    class Texture2D;
    class Sprite;
}

class ResourceManager
    {
public:
        explicit ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;
    //NOT ALLOWING COPY or ASSIGMENT, this class should actually be a singleton class
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> loadShaders ( const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath );
    std::shared_ptr<Renderer::ShaderProgram> getShader (const std::string& shaderName);
    std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<Renderer::Texture2D> getTexture (const std::string& textureName);
    std::shared_ptr<Renderer::Sprite> loadSprite (const std::string& spriteName,
                                                 const std::string& textureName,
                                                 const std::string& shaderName,
                                                 unsigned int spriteWidth,
                                                 unsigned int spriteHeight);
    std::shared_ptr<Renderer::Sprite> getSprite (const std::string& spriteName);

    private:
        [[nodiscard]] std::string getFileString(const std::string& relativeFilePath) const;

        typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap m_shaderPrograms;

        typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
        TexturesMap m_textures;

        typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
        SpritesMap m_sprites;

        std::string m_path;
    };