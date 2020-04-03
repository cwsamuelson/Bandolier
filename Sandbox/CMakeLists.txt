CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Sandbox)

SET(CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(Sandbox source/sandbox.cc
               source/example_layer.cc
               include/example_layer.hh)
TARGET_INCLUDE_DIRECTORIES(Sandbox PRIVATE include/)
TARGET_LINK_LIBRARIES(Sandbox Bandolier)

CONFIGURE_FILE(assets/shaders/FlatColor.glsl assets/shaders/FlatColor.glsl COPYONLY)
CONFIGURE_FILE(assets/shaders/MagicColor.glsl assets/shaders/MagicColor.glsl COPYONLY)
CONFIGURE_FILE(assets/shaders/Texture.glsl assets/shaders/Texture.glsl COPYONLY)

CONFIGURE_FILE(assets/textures/Alpha.png assets/textures/Alpha.png COPYONLY)
CONFIGURE_FILE(assets/textures/Checkerboard.png assets/textures/Checkerboard.png COPYONLY)

