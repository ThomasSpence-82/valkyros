#pragma once

#include "valkyros/core/window.h"
#include <string>
#include <cstdint>
#include <vector>

// Forward declarations
struct GLFWwindow;

namespace Valkyros {

// Forward declarations
struct WindowProps;

class WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProps& props);
    ~WindowsWindow() override;

    // Window interface
    void OnUpdate() override;
    bool ShouldClose() const override;

private:
    void Init(const WindowProps& props);
    void Shutdown();
    void UpdateWindowTitle();

    std::vector<std::string> m_GPUNames;
    GLFWwindow* m_Window = nullptr;
    std::string m_Title;
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
};

} // namespace Valkyros
