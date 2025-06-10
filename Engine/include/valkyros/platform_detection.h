#pragma once

#ifndef VK_PLATFORM_WINDOWS
    #if defined(_WIN32) || defined(_WIN64)
        #define VK_PLATFORM_WINDOWS
    #elif defined(__linux__)
        #define VK_PLATFORM_LINUX
    #elif defined(__APPLE__) && defined(__MACH__)
        #define VK_PLATFORM_MACOS
    #else
        #error "Unknown platform!"
    #endif
#endif

// Platform-specific exports
#ifdef VK_PLATFORM_WINDOWS
    #ifdef VK_BUILD_DLL
        #define VK_API __declspec(dllexport)
    #else
        #define VK_API __declspec(dllimport)
    #endif
#else
    #define VK_API
#endif

// Forward declarations
namespace Valkyros {
    struct WindowProps;
    class Window;
}

// Forward declare the factory function with C linkage
extern "C" {
VK_API Valkyros::Window* CreatePlatformWindow(const Valkyros::WindowProps& props);
}
