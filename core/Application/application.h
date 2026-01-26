//
// Created by abnaclut on 18.01.2026.
//
// This is supposed to be a coordinating class.
//
#pragma once
#ifndef OT_APPLICATION_H
#define OT_APPLICATION_H
#include "../Includes/includes.h"

#include "../ResourceManager/ResourceManager.h"
#include "../Renderer/Renderer.h"
#include "../TemplateGenerator/Tools/tools.h"

namespace OT
{
  class Application
  {
  public:
    Application(int argc, char** argv);
    //Application(const Application&);
    ~Application();
    int running();
    static void init(Application& a); //FIXME ADD PARAMETERS
    // configs
    void setWindowTitle(const std::string& title);
    void setWindowSize(const glm::ivec2& size);
    void setOpenGLVersion(int major, int minor);

    // getters
    [[nodiscard]] GLFWwindow* getWindow() const { return m_pWindow; }
    [[nodiscard]] glm::ivec2 getWindowSize() const { return m_windowSize; }
    [[nodiscard]] std::string getTitle() const { return m_title; }

  private:

    static bool initializeGLFW();
    bool createWindow();
    [[nodiscard]] bool initializeOpenGL() const;
    bool initializeCallbacks();
    void cleanup();
    static void processEvents();
    void render() const;

    // callbacks
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    // vars
    GLFWwindow* m_pWindow = nullptr;
    glm::ivec2 m_windowSize{};
    glm::ivec2 m_defaultWindowSize = glm::ivec2(640, 480);
    std::string m_title;
    std::string m_defaultTitle = "OpenTemplate";
    int m_glMajorVersion = 4; //TODO: add support for other versions
    int m_glMinorVersion = 6;

    std::unique_ptr<ResourceManager> m_resourceManager;
    bool m_isRunning = false;

    // To access instance from static callbacks
    static Application* s_instance;
  };
}
#endif //OT_APPLICATION_H