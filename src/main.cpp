//----------------------------------------------------//some info
//  main.cpp
//  Read LICENSE file (LGPL v2.1).
//  Major sections are marked with //---//<name> and end with //---//end
//  In case some file grows too large, this might help.
//
//  VARIABLE NAMES EXPLANATION:
//  <f>_<t><NAME>
//     f == flag; g == global, m == member of a class, s == static member(of a class).
//     t == type prefix; It is the first letter of the type, Hungarian notation is used, unfortunately.
//        g_iv2NAME means "global 2D vector of ints NAME", this was necessary due to long type names that can be replaced with auto.
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
//INCLUDE
//----------------------------------------------------//end

//----------------------------------------------------//global variables
//GLOBAL VARIABLES
//TODO: encapsulate this in a class, especially the title
auto g_iv2WindowSize = glm::ivec2(640, 480);
GLFWmonitor* g_pMonitor = nullptr;
GLFWwindow* g_pShare = nullptr;
const char* g_pszTitle = "OpenTemplate";
bool g_bSUCCESS = true;
bool g_bFAILURE = false;
//TODO: REMOVE THE ONES BENEATH FOR RELEASE
//triangle vertex coords
GLfloat point[] = {
    0.0f, -150.0f, 0.0f,
    50.0f, -50.0f, 0.0f,
    -50.0f, -50.0f, 0.0f
};
//colors
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};
//texture coords
GLfloat texCoord[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};
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
    //local machine info
    tools::localMachineLog();
    //set color
    glClearColor(1, 1, 0, 1);
    //ADDED SCOPE SO THAT GL CONTEXT IS DESTROYED PROPERLY
{
    //initialize ResourceManager, TODO: do logging in ResourceManager.cpp
    ResourceManager ResourceManager(argv[0]);
    //create the shader program
    const auto pDefaultShaderProgram = ResourceManager.loadShaders("Default shader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
    if (!pDefaultShaderProgram)
    {
        std::cerr << "Cannot create shader program!\n";
        return -1;
    }

    auto tex = ResourceManager.loadTexture("DefaultTexture", "res/textures/textureSample.png");
    if (!tex) {
    std::cerr << "Could not load texture!\n";
    return -1;
}

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCoord_vbo = 0;
        glGenBuffers(1, &texCoord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexArrayAttrib(vao, 0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexArrayAttrib(vao, 1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexArrayAttrib(vao, 2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        //MODEL MATRIX
    auto modeMatrix = glm::mat4(1.f);
    modeMatrix = glm::translate(modeMatrix, glm::vec3(100.0f, 200.0f, 0.0f));
    //NO VIEW MATRIX DUE TO 2D
    ////PROJECTION MATRIX
    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(g_iv2WindowSize.x), static_cast<float>(g_iv2WindowSize.y), 0.0f, -100.0f, 100.0f);
    pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        pDefaultShaderProgram->use();
        glBindVertexArray(vao);
        tex->bind();
        //draws a triangle
        pDefaultShaderProgram->setMatrix4("modelMat", modeMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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