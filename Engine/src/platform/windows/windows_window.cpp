#define VK_BUILD_DLL

#include "valkyros/platform/windows/windows_window.h"
#include "valkyros/platform_detection.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <dxgi1_2.h>
#include <wrl/client.h>

#pragma comment(lib, "dxgi.lib")

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
    
    // Print OpenGL version and renderer info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    
    // Store the GPU name for the window title
    m_GPUNames.clear();
    m_GPUNames.push_back(reinterpret_cast<const char*>(renderer));
    
    // List all available GPUs using DXGI
    std::cout << "[WindowsWindow::Init] Enumerating all available GPUs..." << std::endl;
    
    // First show the active OpenGL GPU
    std::cout << "  - " << vendor << " " << renderer << " (Active - OpenGL)" << std::endl;
    
    // Store GPU information for potential future use (GPU switching, settings, etc.)
    m_GPUNames.clear();
    m_GPUNames.push_back(reinterpret_cast<const char*>(renderer));
    
    // TODO: Replace with proper GPU info structure when implementing settings
    // struct GPUInfo {
    //     std::string name;
    //     size_t vramMB;
    //     uint32_t vendorID;
    //     bool isActive;
    // };
    // std::vector<GPUInfo> gpuList;
    
    // Enumerate all adapters using DXGI
    Microsoft::WRL::ComPtr<IDXGIFactory1> pFactory;
    if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&pFactory)))) {
        IDXGIAdapter1* pAdapter = nullptr;
        for (UINT i = 0; pFactory->EnumAdapters1(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
            DXGI_ADAPTER_DESC1 desc;
            if (SUCCEEDED(pAdapter->GetDesc1(&desc))) {
                // Skip software adapter
                if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
                    pAdapter->Release();
                    continue;
                }
                
                // Convert wchar_t to char for console output
                char gpuName[256];
                wcstombs_s(nullptr, gpuName, desc.Description, 256);
                
                // Get dedicated video memory in MB
                double videoMemoryMB = static_cast<double>(desc.DedicatedVideoMemory) / (1024.0 * 1024.0);
                
                // Output GPU info to console
                std::cout << "  - " << gpuName 
                          << " (VRAM: " << static_cast<int>(videoMemoryMB) << " MB, "
                          << "VendorID: 0x" << std::hex << desc.VendorId << std::dec << ")" << std::endl;
                          
                // TODO: Store this information when implementing GPU switching
                // GPUInfo gpuInfo;
                // gpuInfo.name = gpuName;
                // gpuInfo.vramMB = static_cast<size_t>(videoMemoryMB);
                // gpuInfo.vendorID = desc.VendorId;
                // gpuInfo.isActive = (m_GPUNames[0].find(gpuName) != std::string::npos);
                // gpuList.push_back(gpuInfo);
            }
            pAdapter->Release();
        }
    }
    
    // Print OpenGL version
    std::cout << "[WindowsWindow::Init] OpenGL Version: " << version << std::endl;
    
    // Update window title with GPU info
    UpdateWindowTitle();
}

void WindowsWindow::UpdateWindowTitle() {
    if (!m_GPUNames.empty() && m_Window) {
        std::string title = m_Title + " | " + m_GPUNames[0] + " | FPS: 0";
        glfwSetWindowTitle(m_Window, title.c_str());
    }
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
        static double lastFPSTime = lastTime;
        
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
        
        // Calculate and update FPS in window title
        frameCount++;
        double currentTime = glfwGetTime();
        
        // Update FPS counter every 0.1 seconds for smoother display
        if (currentTime - lastFPSTime >= 0.1) {
            double fps = frameCount / (currentTime - lastFPSTime);
            if (!m_GPUNames.empty() && m_Window) {
                std::string title = m_Title + " | " + m_GPUNames[0] + " | FPS: " + std::to_string(static_cast<int>(fps));
                glfwSetWindowTitle(m_Window, title.c_str());
            }
            lastFPSTime = currentTime;
            frameCount = 0;
        }
    } else {
        std::cerr << "[WindowsWindow::OnUpdate] No valid window!" << std::endl;
    }
}

bool WindowsWindow::ShouldClose() const {
    return m_Window ? glfwWindowShouldClose(m_Window) : true;
}

} // namespace Valkyros
