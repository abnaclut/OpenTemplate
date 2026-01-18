cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

#FIXME redo properly
#TODO fixme

set(PROJECT_NAME OpenTemplate)
project(${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.3
)
FetchContent_MakeAvailable(imgui)
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        core/Application/application.cpp
        core/Application/application.h
)
target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
)

add_executable(${PROJECT_NAME}
        core/TemplateGenerator/main/main.cpp
        core/Renderer/ShaderProgram.cpp
        core/Renderer/ShaderProgram.h
        core/ResourceManager/ResourceManager.cpp
        core/ResourceManager/ResourceManager.h
        core/ResourceManager/stb_image.h
        core/Renderer/Texture2D.cpp
        core/Renderer/Texture2D.h
        core/TemplateGenerator/Tools/tools.cpp
        core/TemplateGenerator/Tools/tools.h
        core/Renderer/Sprite.cpp
        core/Renderer/Sprite.h
        core/Renderer/Renderer.h
        core/Renderer/Renderer.cpp
        core/Renderer/IndexBuffer.cpp
        core/Renderer/IndexBuffer.h
        core/Renderer/VertexBufferLayout.cpp
        core/Renderer/VertexBufferLayout.h
        core/Renderer/VertexBuffer.cpp
        core/Renderer/VertexBuffer.h
        core/Renderer/VertexArray.cpp
        core/Renderer/VertexArray.h
        core/TemplateGenerator/Generator/TemplateGenerator.cpp
        core/TemplateGenerator/Generator/TemplateGenerator.h
        core/UI/GUI/gui.cpp
        core/UI/GUI/gui.h
        core/UI/ui.cpp
        core/UI/ui.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)


target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(imgui glfw)
target_link_libraries(${PROJECT_NAME} imgui glad)

include_directories(external/glm/glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)