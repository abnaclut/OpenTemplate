#include "tools.h"

namespace tools
{
    void glfwSpecifyVersion(const int major, const int minor)
    {
        //OpenGL version specifications will probably be extended in the future.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    void localMachineLog()
    {
        //add more info only if essential.
        std::cout << "LOCAL MACHINE INFO: " << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    };

    void initLog(const std::string& Function, bool initializedSuccessfully)
    {
        //
        if (Function == "glfwInit")
        {
            if (initializedSuccessfully)
            {
                //debug logs
                std::cout << "GLFW initialized successfully!\n";
                return;
            }
            //error logs
            std::cout << "Cannot initialize GLFW!\n";
            std::cout << "glfwInit() failed!\n";
            return;
        }
        //
        if (Function == "glfwCreateWindow")
        {
            if (initializedSuccessfully)
            {
                //debug logs
                std::cout << "GLFW window created successfully!\n";
                return;
            }
            //error logs
            std::cout << "Cannot create GLFW window!\n";
            std::cout << "glfwCreateWindow() failed!\n";
            return;
        }
        //
        if (Function == "glfwWindowSizeCallback")
        {
            if (initializedSuccessfully)
            {
                return;
            }
            //error logs (change if other errors are expected)
            std::cout << "NULL WINDOW POINTER IN glfwWindowSizeCallback()!\n";
            return;
        }
        //
        if (Function == "gladLoadGL")
        {
            if (initializedSuccessfully)
            {
                //debug logs
                std::cout << "GLAD loaded successfully!\n";
                return;
            }
            //error logs
            std::cout << "Cannot load GLAD!\n";
        }
        //
        if (Function.empty())
        {
            if (initializedSuccessfully)
            {
                return;
            }
            //error logs (change if other errors are expected)
            std::cout << "EMPTY ARGUMENT passed to initLog()!\n";
        }
        //noone is going to pass nullptr into this, right? hope so.
    };
}