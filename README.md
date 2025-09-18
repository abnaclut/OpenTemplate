<div style="text-align: center">

   #  Desktop Application Template Generator

</div>

---

### A template generator for desktop C++ projects, ranging from simple utilities to large, scalable project templates. 
#### Only C++ projects are currently supported, tool-list will expand in future releases.
*Note: This project is under active development. Some features will/may be added in future releases.*

---

<div style="text-align: center">

   # Features



   ##  Graphics Options:

</div>

### OpenGL (with loaders)
- **GLAD** - Auto-generated loader for modern OpenGL functions
- **GLFW** - Window and context management (lightweight, cross-platform)
- **SDL** - GLFW alternative with input/audio/network support
- *GLEW* - Potential addition as legacy alternative to GLAD

### Vulkan *(planned)*
- **Vulkan SDK** + GLFW/SDL - High-performance explicit API
- **Validation layers** for debugging
- **Volk** - Meta-loader to reduce driver overhead

### Direct3D *(planned)*
- **Direct3D** 11/12 via Microsoft's libraries

### Software Rendering
- `Dear ImGui` - Immediate-mode UI
- `stb_image` - Lightweight image/font rendering

---

<div style="text-align: center">

   ## Build Options

</div>

- **CMake Presets** - Project generation for CLion, VS Code, or other IDEs (full list in docs)
- **Clean** build without IDE-specifications
- **Custom build**

---

<div style="text-align: center">

## Platforms Supported

</div>

- ## Cross-Platform (*priority*)
- ## Specific platforms:
   - ### Windows
   - ### macOS
   - ### Linux
   - ### *Android (future)*
   - ### *iOS (future)*

---

<div style="text-align: center">

   ## Debug Options

</div>

- ### OpenGL Debug Context
- ### Vulkan Validation Layers
- ### RenderDoc integration

---

<div style="text-align: center">

   ## Additional Features

</div>

### Logging
- `spdlog` (fast, header-only library)
- **Custom logger** (only when necessary)

### Profiling
- `Tracy`
- `Google Benchmark`

### Serialization
- `nlohmann/json`

### Unit Testing
- `Catch2`
- `Google Test`

---

<div style="text-align: center">

   ## Project Structure

</div>

*Project structure examples will be added upon first release.*

---

<div style="text-align: center">

   ## How to use

</div>

*A short manual will be added upon release, mostly in docs.*

---

<div style="text-align: center">

# Important Information

</div>

### *Some features might not be included in initial releases or may be removed in future versions. It is recommended to*:
- ### Read documentation for each release
- ### Read LICENSE

---

<div style="text-align: center">

   ## What to expect in future

</div>

### Future releases may/will include:
- #### Other programming languages, framework templates and their mixes.
- #### Web applications templates.
- #### Mobile applications templates.
- #### Additional graphics APIs and libraries.

*Those are not under development and are considered future prospects. (This will change over time)*

<div style="text-align: center">

## License

### See the [LICENSE](LICENSE) file for license.

</div>
