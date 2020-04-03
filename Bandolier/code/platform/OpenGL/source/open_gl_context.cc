#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <errors.hh>

#include "logger.hh"

#include "open_gl_context.hh"

namespace Bandolier {

OpenGLContext::OpenGLContext(GLFWwindow* window)
        : mWindow(window) {
  glfwMakeContextCurrent(mWindow);//! @TODO validate mWindow
  BNDLR_ASSERT(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to initialize GLAD");

  logging::core()->info("OpenGL info:\n\tVendor: {0}\n\tRenderer: {1}\n\tVersion: {2}",
                        glGetString(GL_VENDOR),
                        glGetString(GL_RENDERER),
                        glGetString(GL_VERSION));

#ifdef BNDLR_ENABLE_ASSERTS
  int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		BNDLR_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Bandolier requires at least OpenGL version 4.5");
#endif
}

OpenGLContext::~OpenGLContext() {
}

void OpenGLContext::SwapBuffers() {
  glfwSwapBuffers(mWindow);
}

}
