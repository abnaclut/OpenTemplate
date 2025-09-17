//  main.cpp
//  Read LICENSE.
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Tools/tools.h"
#include "Renderer/Sprite.h"
//TODO: encapsulate this in a class, especially the title and default resolution;
auto g_WindowSize = glm::ivec2(640, 480);
auto g_Title = "OpenTemplate";

//TODO: this will be modified a lot in the future to support GLFW alternatives.

//TODO: add proper logging

//GLFWwindow* cannot be a pointer to const due to a conversion error!
// ReSharper disable once CppParameterMayBeConstPtrOrRef
void glfwWindowSizeCallback(GLFWwindow* pWindow, const int width, const int height)
{
    //null window check
    // false = failure & true = success (temporary measures)
    if (pWindow == nullptr) { tools::initLog("glfwWindowSizeCallback", false); }

    g_WindowSize.x = width;
    g_WindowSize.y = height;
    glViewport(0, 0, width, height);
}
//key processing
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    //TODO: REMOvE THIS IN FUTURE! (create an exit button)
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}
int main([[maybe_unused]] int argc, char** argv)
{
    ResourceManager resource_manager(argv[0]);
    GLFWmonitor* pMonitor = nullptr;
    GLFWwindow* pShare = nullptr;

    // Initialize the GLFW library
    if (!glfwInit()) { tools::initLog("glfwInit", false); return -1; }
    tools::initLog("glfwInit", true);

    //VERSION SPECIFICATION, *opengl core profile is forced, change glSpecifyVersion if that is a problem.
    tools::glfwSpecifyVersion(4, 6);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* pWindow = glfwCreateWindow(g_WindowSize.x, g_WindowSize.y, g_Title, pMonitor, pShare);
    if (!pWindow)
    {
        tools::initLog("glfwCreateWindow", false);
        glfwTerminate();
        return -1;
    }
    tools::initLog("glfwCreateWindow", true);

    //set callbacks
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    // Make the window's context current
    glfwMakeContextCurrent(pWindow);
    if (!gladLoadGL()) { tools::initLog("gladLoadGL", false); return -1; }
    //all new logs to be finished and done before main loop
    std::cout  << "Renderer: " << RenderEngine::Renderer::getRendererStr() << "\n";
    std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionStr() << "\n";

    RenderEngine::Renderer::setClearColor(0, 0, 0, 1);
    RenderEngine::Renderer::setDepthTest(true);

    {
    //FIXME: program->init();

        //TODO: remove this (remake properly)
    //All logging will be remade using special tools or by means of all-at-once big log here to simplify debug.
    tools::initLog("gladLoadGL", true);
    tools::localMachineLog();
    /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            // poll for and process events
            glfwPollEvents();

            //TODO: add timer here

            // render

            RenderEngine::Renderer::clear();
            //FIXME: program->render();

            // swap front and back buffers (only 2 for now, more will be supported later)
            glfwSwapBuffers(pWindow);
        }
    }
    //END PROGRAM (check for memory leaks here if symptoms are detected)
    glfwTerminate();
    return 0;
}