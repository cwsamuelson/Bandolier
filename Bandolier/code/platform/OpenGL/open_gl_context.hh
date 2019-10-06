#ifndef BANDOLIER_OPEN_GL_CONTEXT_HH
#define BANDOLIER_OPEN_GL_CONTEXT_HH

#include "Renderer/GraphicsContext.hh"

struct GLFWwindow;

namespace Bandolier {

class OpenGLContext : public GraphicsContext
{
public:
  OpenGLContext(GLFWwindow* window);
  ~OpenGLContext();

  virtual void
  SwapBuffers() override;

private:
  GLFWwindow* mWindow;
};

}

#endif //BANDOLIER_OPEN_GL_CONTEXT_HH
