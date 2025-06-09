#pragma once

#include <GLFW/glfw3.h>

namespace Valkyros {

    class Application {
    public:
        Application();
        ~Application();

        void Run();

    private:
        GLFWwindow* m_Window = nullptr;
    };

} // namespace Valkyros
