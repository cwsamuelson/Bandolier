cmake_minimum_required(VERSION 3.14)
project(Bandolier)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/datastructures/event_handler)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)

add_library(Bandolier source/logger.cc source/Application.cc include/windows_window.cc)

target_include_directories(Bandolier PUBLIC include/)

target_link_libraries(Bandolier spdlog_header_only event_handler glfw opengl32)

