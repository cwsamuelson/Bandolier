CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Sandbox)

ADD_EXECUTABLE(Sandbox source/sandbox.cc
               source/example_layer.cc
               include/example_layer.hh source/sandbox_2_d.cc include/sandbox_2_d.hh)
TARGET_INCLUDE_DIRECTORIES(Sandbox PRIVATE include/)
TARGET_LINK_LIBRARIES(Sandbox Bandolier)

SET_TARGET_PROPERTIES(imgui PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)

CONFIGURE_FILE(assets/shaders/FlatColor.glsl assets/shaders/FlatColor.glsl COPYONLY)
CONFIGURE_FILE(assets/shaders/MagicColor.glsl assets/shaders/MagicColor.glsl COPYONLY)
CONFIGURE_FILE(assets/shaders/Texture.glsl assets/shaders/Texture.glsl COPYONLY)

CONFIGURE_FILE(assets/textures/Alpha.png assets/textures/Alpha.png COPYONLY)
CONFIGURE_FILE(assets/textures/Checkerboard.png assets/textures/Checkerboard.png COPYONLY)

