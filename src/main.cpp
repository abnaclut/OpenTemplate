
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//global variables
int g_windowSizeX = 640;
int g_windowSizeY = 480;
//global variables

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, width, height);
}

int main()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        //debug info
        std::cout << "Cannot initialize GLFW!\n";
        std::cout << "glfwInit() failed!\n";
        //debug info

        return -1;
    }

    //VERSION SPECIFICATION
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //VERSION SPECIFICATION

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "babka", nullptr, nullptr);
    if (!pWindow)
    {
        //debug info
        std::cout << "Cannot create GLFW window!\n";
        std::cout << "glfwCreateWindow() failed!\n";
        //debug info
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
    	std::cout << "Cannot load GLAD!\n";
		return -1;
    }


    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 1, 0, 1);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
