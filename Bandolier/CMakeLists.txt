cmake_minimum_required(VERSION 3.14)
project(Bandolier)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/spdlog)
#target_compile_definitions(spdlog PRIVATE _WIN32)

add_library(Bandolier source/logger.cc include/logger.hh)

target_include_directories(Bandolier PUBLIC include/)

target_link_libraries(Bandolier spdlog_header_only)

