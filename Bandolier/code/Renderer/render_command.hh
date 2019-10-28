#ifndef BANDOLIER_RENDER_COMMAND_HH
#define BANDOLIER_RENDER_COMMAND_HH

#include <memory>

#include "Renderer/renderer_api.hh"
#include "platform/OpenGL/open_gl_renderer_api.hh"

namespace Bandolier {

class RenderCommand
{
public:
  inline static void
  Init()
  {
    sRendererAPI->Init();
  }

  inline static void
  SetClearColor(const glm::vec4& color)
  {
    sRendererAPI->SetClearColor(color);
  }

  inline static void
  Clear()
  {
    sRendererAPI->Clear();
  }

  inline static void
  DrawIndexed(const std::shared_ptr<VertexArray>& VAO)
  {
    sRendererAPI->DrawIndexed(VAO);
  }

private:
  inline static std::unique_ptr<RendererAPI> sRendererAPI = std::make_unique<OpenGlRendererAPI>();
};

}

#endif //BANDOLIER_RENDER_COMMAND_HH
