#==============================================================================
# OpenTemplate - CMakeLists.txt
#==============================================================================

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME OpenTemplate)

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

#==============================================================================
# Project Options
#==============================================================================

include(GNUInstallDirs)

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

#==============================================================================
# C++ Standard Configuration
#==============================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#==============================================================================
# Build Type Configuration
#==============================================================================

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX- /utf-8 /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto=auto")
endif()

#==============================================================================
# Project Structure
#==============================================================================

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(EXTERNAL_DIR ${PROJECT_ROOT}/external)
set(CORE_DIR ${PROJECT_ROOT}/core)

include_directories(${PROJECT_ROOT})
include_directories(${EXTERNAL_DIR})

#==============================================================================
# External Dependencies
#==============================================================================

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(${EXTERNAL_DIR}/glfw)
add_subdirectory(${EXTERNAL_DIR}/glad)
add_subdirectory(${EXTERNAL_DIR}/glm)

#==============================================================================
# ImGui Integration
#==============================================================================

include(FetchContent)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.3
        GIT_SHALLOW TRUE
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
)

target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PRIVATE glfw)

set_target_properties(imgui PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

#==============================================================================
# Core Application Library
#==============================================================================

add_library(core_app STATIC
        ${CORE_DIR}/Application/application.cpp
        ${CORE_DIR}/Application/application.h
        ${CORE_DIR}/masterInclude/masterInclude.h
)

target_include_directories(core_app PUBLIC
        ${CORE_DIR}
        ${PROJECT_ROOT}
)

target_link_libraries(core_app PRIVATE
        imgui
        glfw
        glad
        glm
)

#==============================================================================
# Template Generator Module
#==============================================================================

add_library(template_generator_lib STATIC
        ${CORE_DIR}/TemplateGenerator/Tools/tools.cpp
        ${CORE_DIR}/TemplateGenerator/Tools/tools.h
        ${CORE_DIR}/TemplateGenerator/Generator/TemplateGenerator.cpp
        ${CORE_DIR}/TemplateGenerator/Generator/TemplateGenerator.h
)

target_include_directories(template_generator_lib PUBLIC
        ${CORE_DIR}
        ${PROJECT_ROOT}
)

target_link_libraries(template_generator_lib PRIVATE
        core_app
)

#==============================================================================
# Renderer Module
#==============================================================================

add_library(renderer STATIC
        ${CORE_DIR}/Modules/Renderer/ShaderProgram.cpp
        ${CORE_DIR}/Modules/Renderer/ShaderProgram.h
        ${CORE_DIR}/Modules/Renderer/Texture2D.cpp
        ${CORE_DIR}/Modules/Renderer/Texture2D.h
        ${CORE_DIR}/Modules/Renderer/Sprite.cpp
        ${CORE_DIR}/Modules/Renderer/Sprite.h
        ${CORE_DIR}/Modules/Renderer/Renderer.cpp
        ${CORE_DIR}/Modules/Renderer/Renderer.h
        ${CORE_DIR}/Modules/Renderer/IndexBuffer.cpp
        ${CORE_DIR}/Modules/Renderer/IndexBuffer.h
        ${CORE_DIR}/Modules/Renderer/VertexBufferLayout.cpp
        ${CORE_DIR}/Modules/Renderer/VertexBufferLayout.h
        ${CORE_DIR}/Modules/Renderer/VertexBuffer.cpp
        ${CORE_DIR}/Modules/Renderer/VertexBuffer.h
        ${CORE_DIR}/Modules/Renderer/VertexArray.cpp
        ${CORE_DIR}/Modules/Renderer/VertexArray.h
)

target_include_directories(renderer PUBLIC
        ${CORE_DIR}
        ${PROJECT_ROOT}
)

target_link_libraries(renderer PRIVATE
        glad
        glm
)

#==============================================================================
# Resource Manager Module
#==============================================================================

add_library(resource_manager STATIC
        ${CORE_DIR}/Modules/ResourceManager/ResourceManager.cpp
        ${CORE_DIR}/Modules/ResourceManager/ResourceManager.h
        ${CORE_DIR}/Modules/ResourceManager/stb_image.h
)

target_include_directories(resource_manager PUBLIC
        ${CORE_DIR}
        ${PROJECT_ROOT}
)

target_link_libraries(resource_manager PRIVATE
        renderer
)

#==============================================================================
# GUI Module
#==============================================================================

add_library(gui_module STATIC
        ${CORE_DIR}/Modules/GUI/gui.cpp
        ${CORE_DIR}/Modules/GUI/gui.h
)

target_include_directories(gui_module PUBLIC
        ${CORE_DIR}
        ${PROJECT_ROOT}
)

target_link_libraries(gui_module PRIVATE
        imgui
        core_app
)

#==============================================================================
# UI Module
#==============================================================================

add_library(ui_module STATIC
        ${CORE_DIR}/UI/ui.cpp
        ${CORE_DIR}/UI/ui.h
)

target_include_directories(ui_module PUBLIC
        ${CORE_DIR}
        ${PROJECT_ROOT}
)

target_link_libraries(ui_module PRIVATE
        gui_module
        renderer
        core_app
)

#==============================================================================
# Main Executable
#==============================================================================

add_executable(${PROJECT_NAME}
        ${CORE_DIR}/TemplateGenerator/main/main.cpp
        ${CORE_DIR}/TemplateGenerator/main/main.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        template_generator_lib
        renderer
        resource_manager
        gui_module
        ui_module
        core_app
        imgui
        glfw
        glad
        glm
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        IMGUI_IMPL_OPENGL_LOADER_GLAD
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

#==============================================================================
# Resource Copy
#==============================================================================

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/resources")
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/resources")
    message(STATUS "Created resources directory: ${CMAKE_SOURCE_DIR}/resources")
endif()

# resource copy post build (if dir exists & not empty)
file(GLOB RESOURCE_FILES "${CMAKE_SOURCE_DIR}/resources/*")
if(RESOURCE_FILES)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
            COMMENT "Copying resources to output directory"
            VERBATIM
    )
else()
    message(STATUS "No resources found, skipping copy")
endif()

#==============================================================================
# Installation
#==============================================================================

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}
)

#==============================================================================
# Testing (optional, "cmake -DBUILD_TESTS=ON .." to build tests)
#==============================================================================

option(BUILD_TESTS "Build unit tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

#==============================================================================
# Output Summary
#==============================================================================

message(STATUS "========================================")
message(STATUS "${PROJECT_NAME} Configuration")
message(STATUS "========================================")
message(STATUS "Version:        ${PROJECT_VERSION}")
message(STATUS "Build type:     ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard:   ${CMAKE_CXX_STANDARD}")
message(STATUS "Build tests:    ${BUILD_TESTS}")
message(STATUS "Output dir:     ${CMAKE_BINARY_DIR}/bin")
message(STATUS "========================================")
