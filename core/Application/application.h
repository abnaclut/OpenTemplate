//
// Created by abnaclut on 18.01.2026.
//
// This is supposed to be a coordinating class.
//
#pragma once
#ifndef OPENTEMPLATE_APPLICATION_H
#define OPENTEMPLATE_APPLICATION_H

#include <string>
#include <memory>
#include <GLFW/glfw3.h>
#include "../ResourceManager/ResourceManager.h"
#include "../glm/vec2.hpp"
#include "../glm/gtc/matrix_transform.hpp"

namespace OT
{
  class Application
  {
  public:
    Application(int argc, char** argv);
    ~Application();

    int run();

    // configs
    void setWindowTitle(const std::string& title);
    void setWindowSize(const glm::ivec2& size);
    void setOpenGLVersion(int major, int minor);

    // getters
    [[nodiscard]] GLFWwindow* getWindow() const { return m_pWindow; }
    [[nodiscard]] glm::ivec2 getWindowSize() const { return m_windowSize; }
    [[nodiscard]] std::string getTitle() const { return m_title; }

  private:

    // init
    bool initializeGLFW();
    bool createWindow();
    bool initializeOpenGL();
    bool initializeCallbacks();

    // cleanup
    void cleanup();

    // event handling
    void processEvents();
    void render();

    // callbacks
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // vars
    GLFWwindow* m_pWindow = nullptr;
    glm::ivec2 m_windowSize;
    std::string m_title;
    int m_glMajorVersion = 4; //TODO: add support for other versions
    int m_glMinorVersion = 6;

    std::unique_ptr<ResourceManager> m_resourceManager;
    bool m_isRunning = false;

    // timer
    double m_deltaTime = 0.0;
    double m_lastFrameTime = 0.0;

    // To access instance from static callbacks
    static Application* s_instance;
  };
}
#endif //OPENTEMPLATE_APPLICATION_H