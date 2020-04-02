#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.hh"

#include "open_gl_context.hh"

namespace Bandolier {

OpenGLContext::OpenGLContext(GLFWwindow* window)
        : mWindow(window) {
  glfwMakeContextCurrent(mWindow);//! @TODO validate mWindow
  int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);//! @TODO validLoading

  logging::core()->info("OpenGL info:\n\tVendor: {0}\n\tRenderer: {1}\n\tVersion: {2}",
                        glGetString(GL_VENDOR),
                        glGetString(GL_RENDERER),
                        glGetString(GL_VERSION));
}

OpenGLContext::~OpenGLContext() {
}

void OpenGLContext::SwapBuffers() {
  glfwSwapBuffers(mWindow);
}

}
