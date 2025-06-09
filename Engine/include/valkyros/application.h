#pragma once

struct GLFWwindow;  // Forward declaration instead of #include <GLFW/glfw3.h>

namespace Valkyros {

    class Application
    {
    public:
        Application();
        ~Application();

        void Run();

    private:
        GLFWwindow* m_Window = nullptr;
        const char* m_GlslVersion = "#version 330";
    };

}
