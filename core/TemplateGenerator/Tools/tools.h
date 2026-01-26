#pragma once
#ifndef TOOLS_H
#define TOOLS_H
#include "../../Includes/includes.h"
namespace tools
{
    void initLog(const std::string& Function, bool initializedSuccessfully);
    void glfwSpecifyVersion(int major, int minor);
    void localMachineLog();
    template<typename T>
    T AssignArray(T* dest, T* src, size_t size, bool canOverlap);
}
#endif //TOOLS_H