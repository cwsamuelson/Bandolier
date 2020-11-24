CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Bandolier CXX)

ADD_SUBDIRECTORY(vendor/datastructures/event_handler)
ADD_SUBDIRECTORY(vendor/datastructures/error)
ADD_SUBDIRECTORY(vendor/spdlog)
ADD_SUBDIRECTORY(vendor/glfw)
ADD_SUBDIRECTORY(vendor/glad)
ADD_SUBDIRECTORY(vendor/glm)
ADD_SUBDIRECTORY(vendor/fmt)

ADD_LIBRARY(imgui vendor/imgui/imgui.cpp
            vendor/imgui/imgui_demo.cpp
            vendor/imgui/imgui_draw.cpp
            vendor/imgui/imgui_widgets.cpp
            vendor/imgui/backends/imgui_impl_opengl3.cpp
            vendor/imgui/backends/imgui_impl_opengl3.h
            vendor/imgui/backends/imgui_impl_glfw.h
            vendor/imgui/backends/imgui_impl_glfw.cpp)
TARGET_INCLUDE_DIRECTORIES(imgui PUBLIC vendor/imgui/)
TARGET_COMPILE_DEFINITIONS(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)
TARGET_LINK_LIBRARIES(imgui glfw glad)
SET_TARGET_PROPERTIES(imgui PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)

ADD_LIBRARY(stbi vendor/stbi/stb_image.h vendor/stbi/stb_image.cc)
TARGET_INCLUDE_DIRECTORIES(stbi PUBLIC vendor/stbi)

ADD_LIBRARY(Bandolier
            code/core/source/logger.cc
            code/core/include/logger.hh
            code/core/source/Application.cc
            code/core/include/Application.hh
            code/platform/Windows/source/windows_window.cc
            code/platform/Windows/include/windows_window.hh
            code/core/source/layer_stack.cc
            code/core/include/layer_stack.hh
            code/imgui/source/imgui_layer.cc
            code/imgui/include/imgui_layer.hh
            code/platform/Windows/source/windows_input.cc
            code/platform/Windows/include/windows_input.hh
            code/core/include/Input.hh
            code/core/include/Window.hh
            code/core/include/mouse_button_codes.hh
            code/core/include/key_codes.hh
            code/Renderer/include/GraphicsContext.hh
            code/platform/OpenGL/source/open_gl_context.cc
            code/platform/OpenGL/include/open_gl_context.hh
            code/Renderer/source/shader.cc
            code/Renderer/include/shader.hh
            code/Renderer/source/buffer.cc
            code/Renderer/include/buffer.hh
            code/Renderer/include/renderer.hh
            code/platform/OpenGL/source/open_gl_buffer.cc
            code/platform/OpenGL/include/open_gl_buffer.hh
            code/platform/OpenGL/source/open_gl_vertex_array.cc
            code/platform/OpenGL/include/open_gl_vertex_array.hh
            code/Renderer/source/vertex_array.cc
            code/Renderer/include/vertex_array.hh
            code/Renderer/include/render_command.hh
            code/Renderer/include/renderer_api.hh
            code/platform/OpenGL/source/open_gl_renderer_api.cc
            code/platform/OpenGL/include/open_gl_renderer_api.hh
            code/Renderer/source/renderer.cc
            code/Renderer/include/renderer.hh
            code/Renderer/source/orthographic_camera.cc
            code/Renderer/include/orthographic_camera.hh
            code/platform/OpenGL/source/open_gl_shader.cc
            code/platform/OpenGL/include/open_gl_shader.hh
            code/core/include/errors.hh
            code/Renderer/source/texture.cc
            code/Renderer/include/texture.hh
            code/platform/OpenGL/source/open_gl_texture_2_d.cc
            code/platform/OpenGL/include/open_gl_texture_2_d.hh
            code/Renderer/source/orthographic_camera_controller.cc
            code/Renderer/include/orthographic_camera_controller.hh)

TARGET_INCLUDE_DIRECTORIES(Bandolier
                           PUBLIC code/core/include
                           PUBLIC code/events
                           PUBLIC code/imgui/include
                           PUBLIC code/platform/OpenGL/include
                           PUBLIC code/platform/Windows/include
                           PUBLIC code/Renderer/include)

TARGET_LINK_LIBRARIES(Bandolier stbi spdlog event_handler error glfw glad imgui glm)

SET_TARGET_PROPERTIES(Bandolier PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
