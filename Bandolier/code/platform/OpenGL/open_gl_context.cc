#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "open_gl_context.hh"

namespace Bandolier {

OpenGLContext::OpenGLContext(GLFWwindow* window)
  : mWindow(window)
{
  glfwMakeContextCurrent(mWindow);//! @TODO validate mWindow
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);//! @TODO validLoading
}

OpenGLContext::~OpenGLContext()
{}

void OpenGLContext::SwapBuffers()
{
  glfwSwapBuffers(mWindow);
}

}
