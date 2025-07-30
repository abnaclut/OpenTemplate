#include "tools.h"

namespace tools
{
    void glfwSpecifyVersion(const int major, const int minor)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    void localMachineLog()
    {
        std::cout << "LOCAL MACHINE INFO: " << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    };

    void initLog(const std::string& Function, bool initializedSuccessfully)
    {
        switch (Function)
        {
        case "glfwInit":
            {
                if (initializedSuccessfully)
                {
                    //debug logs
                    std::cout << "GLFW initialized successfully!\n";
                    break;
                }
                //error logs
                std::cout << "Cannot initialize GLFW!\n";
                std::cout << "glfwInit() failed!\n";
                break;
            }
        case "glfwCreateWindow":
            {
                if (initializedSuccessfully)
                {
                    //debug logs
                    std::cout << "GLFW window created successfully!\n";
                }
                //error logs
                std::cout << "Cannot create GLFW window!\n";
                std::cout << "glfwCreateWindow() failed!\n";
                break;
            }
        case "glfwWindowSizeCallback":
            {
                if (initializedSuccessfully)
                {
                    //debug logs
                    std::cout << "GLFW window size callback initialized successfully!\n";
                }
                //error logs
                std::cerr << "NULL WINDOW POINTER IN glfwWindowSizeCallback()!\n";
                break;
            }
        default:
            std::cout << "Incorrect initLog parameter!\n";
        }
    };
}