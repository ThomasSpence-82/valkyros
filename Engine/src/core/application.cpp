#include "valkyros/application.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Valkyros {

    Application::Application()
    {
        std::cout << "Valkyros Application Created\n";

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW\n";
            std::exit(EXIT_FAILURE);
        }

        // Set OpenGL version (3.3 Core)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac OS
        #endif

        m_Window = glfwCreateWindow(800, 600, "Valkyros Window", nullptr, nullptr);
        if (!m_Window)
        {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            std::exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(m_Window);

        // Initialize GLAD before calling any OpenGL function
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            std::exit(EXIT_FAILURE);
        }

        // Enable V-Sync
        glfwSwapInterval(1);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init(m_GlslVersion);
    }

    Application::~Application()
    {
        // Cleanup ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (m_Window)
            glfwDestroyWindow(m_Window);

        glfwTerminate();

        std::cout << "Valkyros Application Destroyed\n";
    }

    void Application::Run()
    {
        while (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();

            // Start ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // ImGui demo window or your UI here
            ImGui::Begin("Hello, Valkyros!");
            ImGui::Text("Welcome to the Valkyros engine!");
            ImGui::End();

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(m_Window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(m_Window);
        }
    }

} // namespace Valkyros
