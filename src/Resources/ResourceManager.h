#pragma once

#include <memory>
#include <string>
#include <map>

namespace Renderer
{
    class ShaderProgram;
}

class ResourceManager
    {
public:
    ResourceManager(const std::string& executablePath);
        ~ResourceManager() = default;
        //NOT ALLOWING COPY or ASSIGMENT, this class should actually be a singleton class
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ResourceManager& operator=(ResourceManager&&) = delete;
        ResourceManager(ResourceManager&&) = delete;

        std::shared_ptr<Renderer::ShaderProgram> loadShaders ( const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath );
        std::shared_ptr<Renderer::ShaderProgram> getShader (const std::string& shaderName);
    private:
        std::string getFileString(const std::string& relativeFilePath) const;

        typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap m_shaderPrograms;

        std::string m_path;
    };