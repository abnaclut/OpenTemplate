//COMMENT FOR RELEASE
//UNCOMMENT FOR DEBUG
#define DEBUG

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//NULL = nullptr because of GLFWindow*
#define NULL nullptr


int main()
{
    /* Initialize the library */
    if (!glfwInit())
    {

#ifdef DEBUG
        std::cout << "Cannot initialize GLFW!\n";
        std::cout << "line 17: glfwInit() failed!\n";
#endif

        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!pWindow)
    {
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

    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

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
