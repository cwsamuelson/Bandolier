cmake_minimum_required(VERSION 3.14)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Bandolier ${CMAKE_CURRENT_BINARY_DIR}/Bandolier)

add_executable(Sandbox source/sandbox.cc)
target_include_directories(Sandbox PRIVATE include/)
target_link_libraries(Sandbox Bandolier)

