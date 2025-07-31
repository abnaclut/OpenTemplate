#pragma once
#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include <iostream>
#include <cstring>   // For memcpy, memmove
#include <algorithm> // For std::copy
#include <type_traits> // For std::is_trivially_copyable
#endif //TOOLS_H

namespace tools
{
    void initLog(const std::string& Function, bool initializedSuccessfully);
    void glfwSpecifyVersion(int major, int minor);
    void localMachineLog();
    //
    template<typename T>
    T* AssignArray(T* dest, T* src, size_t size, bool canOverlap);
}