#include "valkyros/core/window.h"
#include "valkyros/platform_detection.h"

namespace Valkyros {

WindowPtr Window::Create(const WindowProps& props) {
    return WindowPtr(::CreatePlatformWindow(props));
}

} // namespace Valkyros
