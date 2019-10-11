#ifndef BANDOLIER_RENDERER_HH
#define BANDOLIER_RENDERER_HH

#include <memory>
#include "vertex_array.hh"
#include "renderer_api.hh"

namespace Bandolier{

class Renderer
{
public:
  static void
  BeginScene();

  static void
  EndScene();

  static void
  Submit(std::shared_ptr<VertexArray> VAO);

  inline static
  RendererAPI::API GetAPI()
  {
    return RendererAPI::GetAPI();
  }
};

}

#endif //BANDOLIER_RENDERER_HH
