#include "valkyros/application.h"
#include <iostream>

namespace Valkyros {

    Application::Application()
    {
        std::cout << "Valkyros Application Created\n";

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW\n";
            // Consider throwing or setting error state here
            return;
        }

        m_Window = glfwCreateWindow(800, 600, "Valkyros Window", nullptr, nullptr);
        if (!m_Window)
        {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            // Consider throwing or setting error state here
            return;
        }

        glfwMakeContextCurrent(m_Window);

        // Set clear color to dark gray
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    }

    Application::~Application()
    {
        if (m_Window)
            glfwDestroyWindow(m_Window);

        glfwTerminate();

        std::cout << "Valkyros Application Destroyed\n";
    }

    void Application::Run()
    {
        if (!m_Window)
        {
            std::cerr << "No GLFW window to run.\n";
            return;
        }

        while (!glfwWindowShouldClose(m_Window))
        {
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap front and back buffers
            glfwSwapBuffers(m_Window);

            // Poll for and process events
            glfwPollEvents();
        }
    }

} // namespace Valkyros
