# Module Roadmap

## Current Status (June 2025)

### Completed
- ✅ Basic window management with GLFW
- ✅ Cross-platform build system setup
- ✅ GPU detection and monitoring
- ✅ Basic OpenGL rendering context
- ✅ Real-time FPS display

## Phase 1: Foundation (In Progress)

### 1.1 Core Systems
- [ ] Abstract rendering interface
- [ ] Resource management system
- [ ] Basic math library
- [ ] Logging and error handling

### 1.2 Vulkan Integration
- [ ] Vulkan instance and device setup
- [ ] Swapchain implementation
- [ ] Basic pipeline setup
- [ ] Memory management
- [ ] Shader loading and compilation

### 1.3 Basic Rendering
- [ ] Simple mesh rendering
- [ ] Basic material system
- [ ] Camera and viewport controls
- [ ] Basic lighting

## Phase 2: Core Features (Planned)

### 2.1 Advanced Rendering
- [ ] Deferred rendering pipeline
- [ ] PBR materials
- [ ] Post-processing effects
- [ ] Shadow mapping

### 2.2 Scene Management
- [ ] Entity Component System (ECS)
- [ ] Scene serialization
- [ ] Level loading

### 2.3 Tooling
- [ ] Basic editor interface
- [ ] Scene inspector
- [ ] Resource browser

## Phase 3: Advanced Features (Future)

### 3.1 Rendering
- [ ] Ray tracing support
- [ ] Global illumination
- [ ] Advanced particle systems

### 3.2 Physics
- [ ] Physics engine integration
- [ ] Collision detection
- [ ] Ragdoll physics

### 3.3 Scripting
- [ ] Lua/Python scripting
- [ ] Visual scripting

## Technical Notes

### GPU Support
- Current implementation supports multi-GPU detection
- Future-proofed for GPU switching
- Vulkan will be the primary rendering backend
- Legacy OpenGL support for compatibility

### Platform Support
- Primary: Windows 10/11 (x64)
- Future: Linux, macOS
- Console support planned for later phases

---

*Last Updated: June 2025*
*This is a living document that will evolve with the project.*