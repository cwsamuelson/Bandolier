cmake_minimum_required(VERSION 3.14)
project(Bandolier)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/datastructures/event_handler)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

add_library(imgui vendor/imgui/imgui.cpp vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC vendor/imgui/)

add_library(Bandolier code/source/logger.cc code/source/Application.cc code/platform/Windows/windows_window.cc code/source/layer_stack.cc)

target_include_directories(Bandolier PUBLIC code/include code/)

target_link_libraries(Bandolier spdlog_header_only event_handler glfw opengl32 glad imgui)

