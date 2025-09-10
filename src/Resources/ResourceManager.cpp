#include "ResourceManager.h"

//Dont move those defs + include
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h" //has to be in the .cpp file

ResourceManager::ResourceManager(const std::string& executablePath)
{
    if (executablePath.empty()) { std::cerr << "Error empty executable path!" << "\n"; return; }
    const size_t lastSlash = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, lastSlash);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
    //error check
    if (relativeFilePath.empty()) { std::cerr << "Error empty relative path!" << "\n"; return {}; }

    std::filesystem::path fullPath = std::filesystem::path(m_path) / relativeFilePath;
    std::ifstream f(fullPath, std::ios::in | std::ios::binary);

    //error check
    if (!f.is_open()) { std::cerr << "Error: failed to open path: " << fullPath << std::endl; return {}; }

    std::string content((std::istreambuf_iterator(f)), std::istreambuf_iterator<char>());
    f.close();
    return content;
}

//CHECK RETURN VALUE FOR NULLPTR! ERRORS or MISUSE RETURNS NULLPTR! (supposed to return)
std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName,
                                                                      const std::string& vertexPath,
                                                                      const std::string& fragmentPath)
{
    //error checks
    if (shaderName.empty())   { std::cerr << "Error empty shader name!" << std::endl; return nullptr; }
    if (vertexPath.empty())   { std::cerr << "Error empty vertex path!" << std::endl; return nullptr; }
    if (fragmentPath.empty()) { std::cerr << "Error empty fragment path!" << std::endl; return nullptr; }

    //Getting fragment shader as a string
    std::string vertexString = getFileString(vertexPath);
    if (vertexString.empty()) { std::cerr << "No Vertex Shader!" << std::endl; return nullptr; }
    //Getting fragment shader as a string
    std::string fragmentString = getFileString(fragmentPath);
    if (fragmentString.empty()) { std::cerr << "No Fragment Shader!" << "\n"; return nullptr; }

    //NOTE: implementation
    std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(
        shaderName,
        std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
    //SUCCESS CHECK
    if (newShader->isCompiled()) { return newShader; }
    //else
        std::cerr << "Can't load shader program:\n"
                  << "Vertex: "   << vertexPath << "\n"
                  << "Fragment: " << fragmentPath << "\n";
        return nullptr;
    //NOTE: ADD ELSE BRACKETS IF EXPANDING
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShader(const std::string& shaderName)
{
    //error check
    if (shaderName.empty()) { std::cerr << "Error empty shader name, cannot get Shader!" << "\n"; return nullptr; }
    //success check
    if (const auto it = m_shaderPrograms.find(shaderName); it != m_shaderPrograms.end()) { return it->second; }
    //else
    std::cerr << "Shader not found: " << shaderName << "\n";
    return nullptr;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture(const std::string& textureName,
                                                                  const std::string& texturePath)
{
    if (textureName.empty()) { std::cerr << "Texture name is empty" << "\n"; return nullptr; }
    if (texturePath.empty()) { std::cerr << "Texture path is empty" << "\n"; return nullptr; }

    //nullified to remove trash.
    int channels = 0;
    int width    = 0;
    int height   = 0;

    //flipped since gl draws from bottom left
    stbi_set_flip_vertically_on_load(true);

    auto fullPath = std::filesystem::path(texturePath);

    //FIXME: probably undefined behaviour, fix me pls.
    auto pixels = reinterpret_cast<char*>(stbi_load(texturePath.c_str(),
                                                    &width,
                                                    &height,
                                                    &channels,
                                                    0));
    if (pixels == nullptr) { std::cerr << "Failed to load texture: " << texturePath << "\n"; return nullptr; }
    //TODO: move filter, wrapMode vars somewhere.
    auto filter = GL_NEAREST;
    auto wrapMode = GL_CLAMP_TO_EDGE;
    std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName,std::make_shared<Renderer::Texture2D>(width,
                                                                                                                             height,
                                                                                                                             pixels,
                                                                                                                             channels,
                                                                                                                             filter,
                                                                                                                             wrapMode)).first->second;
    stbi_image_free(pixels);
    return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
    //success check
    if (const auto it = m_textures.find(textureName); it != m_textures.end()) { return it->second; }
    //else
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
    if (spriteName.empty())  { std::cerr << "Sprite name is empty!"  << "\n"; return nullptr; }
    if (textureName.empty()) { std::cerr << "Texture name is empty!" << "\n"; return nullptr; }
    if (shaderName.empty())  { std::cerr << "Shader name is empty!"  << "\n"; return nullptr; }
    if (spriteWidth == 0)    { std::cerr << "Zero sprite Width!"     << "\n"; return nullptr; }
    if (spriteHeight == 0)   { std::cerr << "Zero sprite Height!"    << "\n"; return nullptr; }
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
