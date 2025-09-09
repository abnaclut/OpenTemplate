#include "ResourceManager.h"

//Dont move those defs + include
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h" //has to be in the .cpp file

ResourceManager::ResourceManager(const std::string& executablePath)
{
    if (executablePath.empty()) { std::cerr << "Error empty executable path!" << std::endl; }
    const size_t lastSlash = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, lastSlash);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
    if (relativeFilePath.empty()) { std::cerr << "Error empty relative path!" << std::endl; }
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
    //error checks
    if (shaderName.empty())   { std::cerr << "Error empty shader name!" << std::endl; }
    if (vertexPath.empty())   { std::cerr << "Error empty vertex path!" << std::endl; }
    if (fragmentPath.empty()) { std::cerr << "Error empty fragment path!" << std::endl; }
    //checks for empty shader
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
    //NOTE: implementation
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
}
std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShader(const std::string& shaderName)
{
    if (shaderName.empty()) { std::cerr << "Error empty shader name, cannot get Shader!" << std::endl; }
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

    //nullified to remove trash.
    int channels = 0;
    int width = 0;
    int height = 0;

    stbi_set_flip_vertically_on_load(true);
    auto fullPath = std::filesystem::path(texturePath);
    //FIXME: probably undefined behaviour, fix me pls.
    auto pixels = reinterpret_cast<char*>(stbi_load(texturePath.c_str(), &width, &height, &channels, 0));
    if (pixels == nullptr)
    {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return nullptr;
    };
    //move filter, wrapMode to vars.
    std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName,std::make_shared<Renderer::Texture2D>(width,
                                                                                                                             height,
                                                                                                                             pixels,
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
        std::cerr << "Texture not found: " << textureName << "\n";
        return nullptr;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::loadSprite (const std::string& spriteName,
                                                 const std::string& textureName,
                                                 const std::string& shaderName,
                                                 unsigned int spriteWidth,
                                                 unsigned int spriteHeight)
{
    //Error-checks
    if (spriteName.empty() || textureName.empty() || shaderName.empty())
    {
        std::cerr << "Sprite, texture or shader name is empty!" << "\n";
        return nullptr;
    }
    if (spriteWidth == 0 || spriteHeight == 0)
    {
        std::cerr << "Sprite width or height is zero!" << "\n";
        return nullptr;
    }
//FIXME finish this tomorrow
    std::shared_ptr<Renderer::Texture2D> pTexture = getTexture(textureName);
    //Error-check
    if (pTexture == nullptr)
    {
        std::cerr << "Texture not found: " << textureName << "for sprite: " << spriteName << "\n";
        return nullptr;
    }
    std::shared_ptr<Renderer::ShaderProgram> pShader = getShader(shaderName);
    //Error-check
    if (pShader == nullptr)
    {
        std::cerr << "Shader not found: " << shaderName << "\n";
    }
    return nullptr;
}
std::shared_ptr<Renderer::Sprite> ResourceManager::getSprite (const std::string& spriteName)
{
    if (const auto it = m_sprites.find(spriteName); it != m_sprites.end())
    {
        return it->second;
    }
    std::cerr << "Sprite not found: " << spriteName << "\n";
    return nullptr;
}

void ResourceManager::setExecutablePath(const std::string& executablePath)
{
    m_path = executablePath;
}

std::string ResourceManager::getExecutablePath() { return m_path; }

//Could be used for delegation but cmon, only 3 resources so far.
// ReSharper disable once CppMemberFunctionMayBeStatic
void ResourceManager::unloadResource(const std::string& resourceName)
{
    //FIXME: implement me
}

void ResourceManager::unloadAllResources()
{
    //FIXME: IMPLEMENT DELEGATION IF REQUIRED!
    m_shaderPrograms.clear();
    m_textures.clear();
    m_sprites.clear();
}
