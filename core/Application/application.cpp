//
// Created by abnaclut on 18.01.2026.
//
#include "application.h"
namespace OT
{
Application* Application::s_instance = nullptr;

Application::Application(int argc, char** argv)
{
    m_windowSize = m_defaultWindowSize;
    m_title = m_defaultTitle;
    m_resourceManager = std::make_unique<ResourceManager>(argv[0]);
    s_instance = this;
}

Application::~Application() { cleanup(); }

void Application::init(Application& a)
{
    initializeGLFW();
    if (a.initializeOpenGL()) { std::cout << "OpenGL initialized." << std::endl; }
    a.initializeCallbacks();
    a.createWindow();
}

bool Application::initializeGLFW()
{
    if (!glfwInit()) { tools::initLog("glfwInit", false); return false; }
    tools::initLog("glfwInit", true);
    tools::glfwSpecifyVersion(4, 6); //FIXME fix
    return true;
}

bool Application::createWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_glMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_glMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //GLFWmonitor* pMonitor = nullptr;
    //GLFWwindow* pShare = nullptr;
    m_pWindow = glfwCreateWindow(m_windowSize.x, m_windowSize.y, m_title.c_str(), nullptr, nullptr);
    //window creation error check
    if (!m_pWindow) { tools::initLog("glfwCreateWindow", false); return false; }
    tools::initLog("glfwCreateWindow", true); return true;
}

bool Application::initializeOpenGL() const
{
    glfwMakeContextCurrent(m_pWindow);
    if (!gladLoadGL()) { tools::initLog("gladLoadGL", false); return false; }

    RenderEngine::Renderer::setClearColor(1, 0, 0, 1);
    RenderEngine::Renderer::setDepthTest(true);

    tools::initLog("gladLoadGL", true);
    tools::localMachineLog();
    //FIXME RETURN FALSE IF ERROR OCCURS
    return true;
}

bool Application::initializeCallbacks()
{
    glfwSetKeyCallback(m_pWindow, keyCallback);
    // Store window pointer to access instance
    glfwSetWindowUserPointer(m_pWindow, this);
    return true;
}

void Application::setWindowTitle(const std::string& title)
{
    m_title = title;
    if (m_pWindow) { glfwSetWindowTitle(m_pWindow, m_title.c_str()); }
}

void Application::setWindowSize(const glm::ivec2& size)
{
    m_windowSize = size;
    if (m_pWindow) { glfwSetWindowSize(m_pWindow, size.x, size.y); }
}

void Application::setOpenGLVersion(const int major, const int minor)
{
    m_glMajorVersion = major;
    m_glMinorVersion = minor;
}

void Application::processEvents() { glfwPollEvents(); }

void Application::render() const
{
    RenderEngine::Renderer::clear();
    //TODO rendering logic goes here
    glfwSwapBuffers(m_pWindow);
}

int Application::running()
{
    if (!initializeGLFW()) return -1;
    if (!createWindow()) return -1;
    if (!initializeOpenGL()) return -1;
    //if (!initializeCallbacks()) return -1;

    m_isRunning = true;

    // Main loop
    while (m_isRunning && !glfwWindowShouldClose(m_pWindow))
    {
        processEvents();
        render();
    }
    return 0;
}

void Application::cleanup()
{
    if (m_pWindow)
    {
        glfwDestroyWindow(m_pWindow);
        m_pWindow = nullptr;
    }
    glfwTerminate();
    m_isRunning = false;
}

void Application::keyCallback(GLFWwindow* window, const int key, int scancode, const int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GLFW_TRUE); }
    // Additional key handling can be added here
}
}