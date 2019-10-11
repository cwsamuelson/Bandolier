#ifndef BANDOLIER_OPEN_GL_RENDERER_API_HH
#define BANDOLIER_OPEN_GL_RENDERER_API_HH

#include <Renderer/renderer_api.hh>

namespace Bandolier {

class OpenGlRendererAPI : public RendererAPI
{
public:
  virtual void
  SetClearColor(const glm::vec4& color) override;

  virtual void
  Clear() override;

  virtual void
  DrawIndexed(std::shared_ptr<VertexArray> VAO) override;
};

}

#endif //BANDOLIER_OPEN_GL_RENDERER_API_HH
