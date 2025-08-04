#pragma once
#ifndef TOOLS_H
#define TOOLS_H
#include <string>
// ReSharper disable once CppUnusedIncludeDirective
#include <iostream>
// ReSharper disable once CppUnusedIncludeDirective //USED
#include <cstring>   // For memcpy, memmove
// ReSharper disable once CppUnusedIncludeDirective //USED
#include <algorithm> // For std::copy
// ReSharper disable once CppUnusedIncludeDirective //USED
#include <type_traits> // For std::is_trivially_copyable
// ReSharper disable once CppUnusedIncludeDirective //USED
// FIXME: DO NOT CHANGE THE INCLUDE ORDER!!!!!!
#include "glad/glad.h"
#include "../glfw/include/GLFW/glfw3.h"
#endif //TOOLS_H

namespace tools
{
    void initLog(const std::string& Function, bool initializedSuccessfully);
    void glfwSpecifyVersion(int major, int minor);
    void localMachineLog();
    //
    template<typename T>
    T AssignArray(T* dest, T* src, size_t size, bool canOverlap);
}