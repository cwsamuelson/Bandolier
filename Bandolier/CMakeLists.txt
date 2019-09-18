cmake_minimum_required(VERSION 3.14)
project(Bandolier)

set(CMAKE_CXX_STANDARD 17)

add_library(Bandolier INTERFACE)

target_include_directories(Bandolier INTERFACE include/)

