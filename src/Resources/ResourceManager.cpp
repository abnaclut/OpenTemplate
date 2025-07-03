#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
   #include "stb_image.h"


ResourceManager::ResourceManager(const std::string& executablePath)
{
    const size_t lastSlash = executablePath.find_last_of("/\\");
    ResourceManager::m_path = executablePath.substr(0, lastSlash);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
    std::filesystem::path fullPath = std::filesystem::path(m_path) / relativeFilePath;
    std::ifstream f(fullPath, std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Error: failed to open path: " << fullPath << std::endl;
        return {};
    }

    std::string content((std::istreambuf_iterator<char>(f)),
                        std::istreambuf_iterator<char>());
    f.close();
    return content;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexString = getFileString(vertexPath);
    if (vertexString.empty())
    {
        std::cerr << "No Vertex Shader!" << std::endl;
        return nullptr;
    }
    std::string fragmentString = getFileString(fragmentPath);
    if (fragmentString.empty())
    {
        std::cerr << "No Fragment Shader!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(
        shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
    if (newShader->isCompiled())
    {
        return newShader;
    }
        std::cerr << "Can't load shader program:\n"
            << "Vertex: " << vertexPath << "\n"
            << "Fragment: " << fragmentPath << "\n";
        return nullptr;
};

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShader(const std::string& shaderName)
{
    if (const auto it = m_shaderPrograms.find(shaderName); it != m_shaderPrograms.end())
    {
        return it->second;
    }
        std::cerr << "Shader not found: " << shaderName << std::endl;
        return nullptr;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
    if (textureName.empty() || texturePath.empty()) {
        std::cerr << "Texture name or path is empty" << std::endl;
        return nullptr;
    }

    int channels = 0;
    int width = 0;
    int height = 0;

    stbi_set_flip_vertically_on_load(true);
    auto fullPath = std::filesystem::path(texturePath);
    unsigned char* pixels = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
    if (pixels == nullptr)
    {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return nullptr;
    };

    std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName,std::make_shared<Renderer::Texture2D>(width,
                                                                                                                             height,
                                                                                                                             reinterpret_cast<const char*>(pixels),
                                                                                                                             channels,
                                                                                                                             GL_NEAREST,
                                                                                                                             GL_CLAMP_TO_EDGE)).first->second;
    stbi_image_free(pixels);
    return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
    if (const auto it = m_textures.find(textureName); it != m_textures.end())
    {
        return it->second;
    }
        std::cerr << "Texture not found: " << textureName << std::endl;
        return nullptr;
};
