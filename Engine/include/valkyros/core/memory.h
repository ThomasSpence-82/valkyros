#pragma once

#include <memory>

// This file is kept for backward compatibility
// Prefer using std::unique_ptr and std::make_unique directly

namespace Valkyros {

// Alias for std::unique_ptr
template<typename T>
using Scope = std::unique_ptr<T>;

// Helper function to create unique_ptr
// Prefer using std::make_unique in C++14 and above
template<typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

} // namespace Valkyros
