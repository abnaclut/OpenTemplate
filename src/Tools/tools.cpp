#include "tools.h"

namespace tools
{
    void glfwSpecifyVersion(const int major, const int minor)
    {
        //TODO: OpenGL version specifications will probably be extended in the future.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    void localMachineLog()
    {
        //TODO: add more info only if essential.
        std::cout << "LOCAL MACHINE INFO: " << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    };
    void fastInitLog(const std::string& func, bool initSuccess)
    {
        if (initSuccess)
        {
            //TODO: conditions might be added in future if required.
            std::cout << func.c_str() << " Initialized correctly!" << std::endl;
            return;
        }
        //TODO: conditions or options might be added in future.
        std::cerr << func.c_str() << " Could not initialize!\n";
    }
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
            //TODO: error logs (change if other errors are expected)
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
            //TODO: error logs (change if other errors are expected)
            std::cout << "EMPTY ARGUMENT passed to initLog()!\n";
        }
        //noone is going to pass nullptr into this, right? hope so.
    };
    template<typename T>
    T AssignArray(T* dest, T* src, size_t size, bool canOverlap = false)
    {
        //size = number of values of type T * size of T in bytes // size_t size == nT*sizeof(T)
        //nullptr check
        if (!dest || !src || size == 0) { return dest; }
        //for trivial types do memmove/memcpy
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            if (canOverlap)
                { std::memmove(dest, src, size * sizeof(T)); }
            else
                { std::memcpy(dest, src, size * sizeof(T)); }
        }
        else
        {
            if (canOverlap && (dest >= src && dest < src + size)) {
                // Handle overlap manually (rare for non-POD types)
                for (size_t i = size; i-- > 0; ) {
                    dest[i] = src[i];
                }
            } else {
                //for non-trivial types like std::string
                std::copy(src, src + size, dest);
            }
        }

        return dest;
        //and then hope no memory is leaked...
    }
}