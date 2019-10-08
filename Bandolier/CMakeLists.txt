cmake_minimum_required(VERSION 3.14)
project(Bandolier)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/datastructures/event_handler)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

add_library(imgui vendor/imgui/imgui.cpp
                  vendor/imgui/imgui_demo.cpp
                  vendor/imgui/imgui_draw.cpp
                  vendor/imgui/imgui_widgets.cpp
                  vendor/imgui/examples/imgui_impl_opengl3.cpp
                  vendor/imgui/examples/imgui_impl_opengl3.h
                  vendor/imgui/examples/imgui_impl_glfw.h
                  vendor/imgui/examples/imgui_impl_glfw.cpp)
target_include_directories(imgui PUBLIC vendor/imgui/)
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(imgui glfw glad)

add_library(Bandolier code/source/logger.cc
                      code/source/Application.cc
                      code/platform/Windows/windows_window.cc
                      code/source/layer_stack.cc
                      code/imgui/imgui_layer.cc
                      code/imgui/imgui_layer.hh
                      code/platform/Windows/windows_input.cc
                      code/platform/Windows/windows_input.hh
                      code/include/Input.hh
                      code/include/Window.hh
                      code/include/mouse_button_codes.hh
                      code/include/key_codes.hh
                      code/Renderer/GraphicsContext.hh
                      code/platform/OpenGL/open_gl_context.cc
                      code/platform/OpenGL/open_gl_context.hh
                      code/Renderer/shader.cc
                      code/Renderer/shader.hh
                      code/Renderer/buffer.cc
                      code/Renderer/buffer.hh
                      code/Renderer/renderer.hh
                      code/platform/OpenGL/open_gl_buffer.cc
                      code/platform/OpenGL/open_gl_buffer.hh)

target_include_directories(Bandolier PUBLIC code/include code/)

target_link_libraries(Bandolier spdlog_header_only event_handler glfw opengl32 glad imgui)

