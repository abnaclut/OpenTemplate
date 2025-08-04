//when released, this will be:

A **template generator** for desktop **C++** applications, everything from simple utils to large easy-to-scale project templates with different graphics options.
(will include a feature list once released)

GRAPHICS OPTIONS:

 - **OpenGL** (with loaders)
   - GLAD (for modern OpenGL) — Auto-generated loader for OpenGL functions.
   - GLFW (window/context management) — Lightweight, cross-platform, works well with GLAD.
   - SDL (glfw alternative) — Includes input/audio/networking support.
   - // I might add GLEW as a legacy GLAD alternative if someone asks for it
 - **Vulkan** //Once I finish OpenGL
   - Vulkan SDK + GLFW/SDL — High-performance, explicit API. Include validation layers for debugging.
   - Volk — Optional meta-loader for Vulkan. Reduces driver overhead.
 - **Direct3d** // Once I finish Vulkan
   - Direct3d 11/12 — Via microsoft's d3d11/d3d12 libraries.
 - **Software Rendering**
   - Dear ImGui (immediate-mode UI) — Solid option for most cases, exceptions will be explained further.
   - stb_image — Lightweight image/font rendering.
  
BUILD OPTIONS:

 - **CMake Presets**(CLion/VS code/etc) -- Generates a CMake project for your IDE or a clean project if no IDE is used.

PLATFORM OPTIONS:

 - **Cross-Platform** (Priority)
 - **Specified platform**
   - Windows
   - MacOS
   - Linux
   - Android
   - IOS

DEBUG OPTIONS:

 - **OpenGL Debug Context**
 - **Vulkan Validation Layers**
 - **RenderDoc integration**

OTHER FEATURES:

 - **Logging**
   - spdlog (fast, header-only)
   - Custom (if necessary)
 - **Profiling**
   - Tracy
   - Google Benchmark
 - **Serialization**
   - nlohmann/json
 - **Unit Testing**
   - Catch2
   - Google Test

PROJECT STRUCTURE EXAMPLES:

(to be added upon finishing corresponding options)

HOW TO USE:

(to be added after the first release)

 - ***NOTE***
Some features might not be included in the first releases or might be removed in future ones, therefore, reading docs is a good idea.
I will try to prevent such situations once everything is finished. And if I fail to, read LICENSE.
:)
