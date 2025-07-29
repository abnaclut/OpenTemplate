//----------------------------------------------------//some info
//  main.cpp
//  Read LICENSE file (LGPL v2.1).
//  Logging is done between "debug logs" comments for better readability. (read docs)
//  Major sections are marked with //---//<name> and end with //---//end
//  In case some file grows too large, this might help.
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
//INCLUDE
//----------------------------------------------------//end

//----------------------------------------------------//global variables
//GLOBAL VARIABLES
auto g_windowSize = glm::ivec2(640, 480);
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
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    //nullptr check
    if (pWindow == nullptr)
    {
        //debug logs
        std::cerr << "NULL WINDOW POINTER IN glfwWindowSizeCallback()!\n";
        //debug logs
    }

    g_windowSize.x = width;
    g_windowSize.y = height;
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
//other stuff, TODO: move this to a separate cpp/header files
void glfwSpecifyVersion(const int major, const int minor)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
//temporarily here, I will TODO: create a separate logger.cpp+.h hater
void logLocalMachineInfo()
{
    std::cout << "LOCAL MACHINE INFO: " << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
};
//CALLBACK FUNCTIONS
//----------------------------------------------------//end

//----------------------------------------------------//main
//MAIN
int main(int argc, char** argv)
{
    // Initialize the GLFW library
    if (!glfwInit())
    {
        //debug logs
        std::cout << "Cannot initialize GLFW!\n";
        std::cout << "glfwInit() failed!\n";
        //debug logs
        return -1;
    }
    //debug logs
    std::cout << "GLFW initialized successfully!\n";
    //debug logs
    //VERSION SPECIFICATION, *opengl core profile is forced, change glSpecifyVersion if that is a problem.
    glfwSpecifyVersion(4, 6);
    // Create a windowed mode window and its OpenGL context
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "openTemplate", nullptr, nullptr);
    if (!pWindow)
    {
        //debug logs
        std::cout << "Cannot create GLFW window!\n";
        std::cout << "glfwCreateWindow() failed!\n";
        //debug logs
        glfwTerminate();
        return -1;
    }
    //debug logs
    std::cout << "GLFW window created successfully!\n";
    //debug logs
    //CALLBACKS
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    // Make the window's context current
    glfwMakeContextCurrent(pWindow);
    if (!gladLoadGL())
    {
        //debug logs
        std::cout << "Cannot load GLAD!\n";
        //debug logs
        return -1;
    }
    //debug logs
    std::cout << "GLAD loaded successfully!\n";
    //debug logs
    //local machine info
    logLocalMachineInfo();
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
    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(g_windowSize.x), static_cast<float>(g_windowSize.y), 0.0f, -100.0f, 100.0f);
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