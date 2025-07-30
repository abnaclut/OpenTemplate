#pragma once
#ifndef TOOLS_H
#define TOOLS_H
#endif //TOOLS_H

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tools
{
    void initLog(const std::string& Function, bool initializedSuccessfully);
    void glfwSpecifyVersion(int major, int minor);
    void localMachineLog();
}