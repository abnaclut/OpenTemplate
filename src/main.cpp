//----------------------------------------------------//some info
//  main.cpp
//  Read LICENSE file (LGPL v2.1).
//  Major sections are marked with //---//<name> and end with //---//end
//  In case some file grows too large, this might help.
//
//  VARIABLE NAMES EXPLANATION:
//  <f>_<t><NAME>
//     f == flag; g == global, m == member of a class, s == static member(of a class).
//     t == type prefix; It is an abbreviation of a type, ONLY IF NECESSARY to prevent wrong type usage.
//     Hungarian notation is ONLY used for global variables or in case of necessity.
//        g_iv2NAME means "global 2D vector of ints NAME". This is only used with pointers, matrices, vectors.
//----------------------------------------------------//end

//----------------------------------------------------//include
//INCLUDE
//standart
#include <iostream>
//external
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
//local
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Tools/tools.h"
#include "Renderer/Sprite.h"
//INCLUDE
//----------------------------------------------------//end

//----------------------------------------------------//global variables
//GLOBAL VARIABLES
//TODO: encapsulate this in a class, especially the title= 640;
auto g_iv2WindowSize = glm::ivec2(640, 480);
GLFWmonitor* g_pMonitor = nullptr;
GLFWwindow* g_pShare = nullptr;
const char* g_pszTitle = "OpenTemplate";
bool g_bSUCCESS = true;
bool g_bFAILURE = false;
//GLOBAL VARIABLES
//----------------------------------------------------//end

//----------------------------------------------------//callbacks
//CALLBACK FUNCTIONS
//TODO: this will be modified a lot in the future to support GLFW alternatives.

//window resizing
// ReSharper disable once CppParameterMayBeConstPtrOrRef
//GLFWwindow* cannot be a pointer to const due to a conversion error!!!
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    //null window check
    if (pWindow == nullptr)
    {
        tools::initLog("glfwWindowSizeCallback", g_bFAILURE);
    }

    g_iv2WindowSize.x = width;
    g_iv2WindowSize.y = height;
    glViewport(0, 0, width, height);
}
//key processing
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    //TODO: REMOvE THIS IN FUTURE! (create an exit button)
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
    //
}
//CALLBACK FUNCTIONS
//----------------------------------------------------//end

//----------------------------------------------------//main
//MAIN
int main(int argc, char** argv)
{
    // Initialize the GLFW library
    if (!glfwInit())
    {
        tools::initLog("glfwInit", g_bFAILURE);
        return -1;
    }
    tools::initLog("glfwInit", g_bSUCCESS);

    //VERSION SPECIFICATION, *opengl core profile is forced, change glSpecifyVersion if that is a problem.
    tools::glfwSpecifyVersion(4, 6);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* pWindow = glfwCreateWindow(g_iv2WindowSize.x, g_iv2WindowSize.y, g_pszTitle, g_pMonitor, g_pShare);
    if (!pWindow)
    {
        tools::initLog("glfwCreateWindow", g_bFAILURE);
        glfwTerminate();
        return -1;
    }
    tools::initLog("glfwCreateWindow", g_bSUCCESS);

    //set callbacks
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    // Make the window's context current
    glfwMakeContextCurrent(pWindow);
    if (!gladLoadGL())
    {
        tools::initLog("gladLoadGL", g_bFAILURE);
        return -1;
    }
    tools::initLog("gladLoadGL", g_bSUCCESS);
    tools::localMachineLog();
    constexpr float red = 1;
    constexpr float green = 1;
    constexpr float blue = 0;
    constexpr float alpha = 1;
    glClearColor(red, green, blue, alpha);
    //ADDED SCOPE SO THAT GL CONTEXT IS DESTROYED PROPERLY
    {
        //initialize ResourceManager, TODO: do logging in ResourceManager.cpp
        ResourceManager ResourceManager(argv[0]);
        //create the shader program
        const std::string& defaultShaderName            = "Default shader";
        const std::string& defaultVertexShaderPath      = "res/shaders/vertex.txt";
        const std::string& defaultFragmentShaderPath    = "res/shaders/fragment.txt";
        const auto pDefaultShaderProgram = ResourceManager.loadShaders(defaultShaderName, defaultVertexShaderPath, defaultFragmentShaderPath);
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Cannot create shader program!\n";
            return -1;
        }
        const std::string& defaultTextureName = "Default texture";
        const std::string& defaultTexturePath = "res/textures/textureSample.png";
        auto tex = ResourceManager.loadTexture(defaultTextureName, defaultTexturePath);
        if (!tex) {
        std::cerr << "Could not load texture!\n";
        return -1;
    }
        //generate stuff
        Renderer::Sprite sprite();


        //use the default shader program
        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);
        //MODEL MATRIX
        auto modeMatrix = glm::mat4(1.f);
        modeMatrix = glm::translate(modeMatrix, glm::vec3(100.0f, 200.0f, 0.0f));
        //NO VIEW MATRIX DUE TO 2D
        ////PROJECTION MATRIX
        const auto right = static_cast<float>(g_iv2WindowSize.x);
        const auto bottom = static_cast<float>(g_iv2WindowSize.y);
        constexpr float left = 0.0f;
        constexpr float top = 0.0f;
        constexpr float zNear = 0.0f;
        constexpr float zFar = 100.0f;
        // ReSharper disable once CppLocalVariableMayBeConst
        glm::mat4 projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);
        // ReSharper disable once CppTooWideScope
        constexpr int mode = GL_TRIANGLES;
        // ReSharper disable once CppTooWideScope
        constexpr int count = 3;
        /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        pDefaultShaderProgram->use();
        tex->bind();
        //draws a triangle
        pDefaultShaderProgram->setMatrix4("modelMat", modeMatrix);
        glDrawArrays(mode, 0, count);
        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);
        /* Poll for and process events */
        glfwPollEvents();
    }
}
    //END PROGRAM (check for memory leaks here if detected)
    glfwTerminate();
    return 0;
}