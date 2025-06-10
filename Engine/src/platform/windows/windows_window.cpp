#define VK_BUILD_DLL

#include "valkyros/platform/windows/windows_window.h"
#include "valkyros/platform_detection.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>

namespace Valkyros {

// Platform-specific window factory implementation
extern "C" VK_API Window* CreatePlatformWindow(const WindowProps& props) {
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props) 
    : m_Window(nullptr), m_Width(0), m_Height(0) {
    std::cout << "[WindowsWindow] Creating window with title: " << props.title << 
                 ", size: " << props.width << "x" << props.height << std::endl;
    Init(props);
}

WindowsWindow::~WindowsWindow() {
    Shutdown();
}

void WindowsWindow::Init(const WindowProps& props) {
    m_Title = props.title;
    m_Width = props.width;
    m_Height = props.height;

    std::cout << "[WindowsWindow::Init] Initializing GLFW..." << std::endl;
    if (!glfwInit()) {
        const char* error = nullptr;
        glfwGetError(&error);
        std::cerr << "[WindowsWindow::Init] Failed to initialize GLFW: " << (error ? error : "Unknown error") << std::endl;
        return;
    }
    std::cout << "[WindowsWindow::Init] GLFW initialized successfully" << std::endl;

    std::cout << "[WindowsWindow::Init] Creating GLFW window..." << std::endl;
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        const char* error = nullptr;
        glfwGetError(&error);
        std::cerr << "[WindowsWindow::Init] Failed to create GLFW window: " << (error ? error : "Unknown error") << std::endl;
        glfwTerminate();
        return;
    }
    std::cout << "[WindowsWindow::Init] GLFW window created successfully" << std::endl;
    
    // Set user pointer to this window instance
    glfwSetWindowUserPointer(m_Window, this);

    std::cout << "[WindowsWindow::Init] Setting up OpenGL context..." << std::endl;
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1); // Enable V-Sync
    
    // Print OpenGL version
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "[WindowsWindow::Init] OpenGL Renderer: " << renderer << std::endl;
    std::cout << "[WindowsWindow::Init] OpenGL Version: " << version << std::endl;
}

void WindowsWindow::Shutdown() {
    if (m_Window) {
        std::cout << "[WindowsWindow::Shutdown] Destroying window..." << std::endl;
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
        glfwTerminate();
        std::cout << "[WindowsWindow::Shutdown] GLFW terminated" << std::endl;
    } else {
        std::cerr << "[WindowsWindow::Shutdown] No window to destroy!" << std::endl;
    }
}

void WindowsWindow::OnUpdate() {
    if (m_Window) {
        static int frameCount = 0;
        static double lastTime = glfwGetTime();
        
        glfwPollEvents();
        
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw a simple colored triangle
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-0.5f, -0.5f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f(0.5f, -0.5f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex2f(0.0f, 0.5f);
        glEnd();
        
        glfwSwapBuffers(m_Window);
        
        // Print FPS every second
        frameCount++;
        double currentTime = glfwGetTime();
        if (currentTime - lastTime >= 1.0) {
            std::cout << "[WindowsWindow::OnUpdate] FPS: " << frameCount << std::endl;
            frameCount = 0;
            lastTime = currentTime;
        }
    } else {
        std::cerr << "[WindowsWindow::OnUpdate] No valid window!" << std::endl;
    }
}

bool WindowsWindow::ShouldClose() const {
    return m_Window ? glfwWindowShouldClose(m_Window) : true;
}

} // namespace Valkyros
