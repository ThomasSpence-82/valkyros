#pragma once

#include <memory>
#include <string>
#include <cstdint>

namespace Valkyros {

    // Forward declarations
    class Window;
    
    // Smart pointer type for Window
    using WindowPtr = std::unique_ptr<Window>;

    struct WindowProps {
        std::string title = "Valkyros Engine";
        uint32_t width = 1280;
        uint32_t height = 720;

        WindowProps(const std::string& t = "Valkyros Engine", uint32_t w = 1280, uint32_t h = 720)
            : title(t), width(w), height(h) {
        }
    };

    class Window {
    public:
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;
        virtual bool ShouldClose() const = 0;

        static WindowPtr Create(const WindowProps& props = WindowProps());
    };

} // namespace Valkyros
