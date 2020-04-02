CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Sandbox)

SET(CMAKE_CXX_STANDARD 17)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/../Bandolier ${CMAKE_CURRENT_BINARY_DIR}/Bandolier)

ADD_EXECUTABLE(Sandbox source/sandbox.cc
               source/example_layer.cc
               include/example_layer.hh)
TARGET_INCLUDE_DIRECTORIES(Sandbox PRIVATE include/)
TARGET_LINK_LIBRARIES(Sandbox Bandolier)

