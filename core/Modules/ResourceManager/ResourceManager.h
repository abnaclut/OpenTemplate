#pragma once
#ifndef OT_RESOURCEMANAGER_H
#define OT_RESOURCEMANAGER_H

#include "../Includes/includes.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG //FIXME support other options

namespace RenderEngine
{
    class ShaderProgram;
    class Texture2D;
    class Sprite;
}

class ResourceManager
{
public:
    void setExecutablePath(const std::string& executablePath);
    std::string getExecutablePath();
    void unloadAllResources();
    void unloadResource(const std::string& resourceName);

    explicit ResourceManager(const std::string& executablePath);

    //NOT ALLOWING COPY & ASSIGMENT, this class should actually be a singleton class

    ResourceManager() = delete;
    ~ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::shared_ptr<RenderEngine::ShaderProgram> loadShaders ( const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath );
    std::shared_ptr<RenderEngine::ShaderProgram> getShader (const std::string& shaderName);
    std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<RenderEngine::Texture2D> getTexture (const std::string& textureName);

    std::shared_ptr<RenderEngine::Sprite> loadSprite (const std::string& spriteName,
                                                 const std::string& textureName,
                                                 const std::string& shaderName,
                                                 const std::string& subTextureName);
    std::shared_ptr<RenderEngine::Sprite> getSprite (const std::string& spriteName);
//FIXME: finish
    std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(std::string textureName,
                                                                 std::string texturePath,
                                                                 std::vector<std::string> subTextures,
                                                                 unsigned int subTextureWidth,
                                                                 unsigned int subTextureHeight);

    //TODO: add textureAtlas + JSONs!!!
    private:
        [[nodiscard]] std::string getFileString(const std::string& relativeFilePath) const;

        typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap m_shaderPrograms;
        typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
        TexturesMap m_textures;
        typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;
        SpritesMap m_sprites;

        std::string m_path;
    };
#endif // OT_RESOURCEMANAGER_H