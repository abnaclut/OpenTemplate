#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

ResourceManager::ResourceManager(const std::string& executablePath)
{
    size_t lastSlash = executablePath.find_last_of("/\\");
    ResourceManager::m_path = executablePath.substr(0, lastSlash);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
    std::filesystem::path fullPath = std::filesystem::path(m_path) / relativeFilePath;
    std::ifstream f(fullPath, std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Error: failed to open path: " << fullPath << std::endl;
        return std::string();
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
    ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
    if (it != m_shaderPrograms.end())
    {
        return it->second;
    }
        std::cerr << "Shader not found: " << shaderName << std::endl;
        return nullptr;
}