#include "valkyros/application.h"
#include <iostream>

namespace Valkyros {

Application::Application() {
    m_Window = Window::Create();
    if (!m_Window) {
        std::cerr << "Failed to create application window!\n";
    }
}

Application::~Application() {
    // Window will be automatically destroyed by m_Window unique_ptr
}

void Application::Run() {
    if (!m_Window) {
        std::cerr << "Cannot run application: Window not initialized!\n";
        return;
    }

    while (!m_Window->ShouldClose()) {
        m_Window->OnUpdate();
    }
}

} // namespace Valkyros
