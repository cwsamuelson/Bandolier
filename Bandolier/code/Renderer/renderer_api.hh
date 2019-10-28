#ifndef BANDOLIER_RENDERER_API_HH
#define BANDOLIER_RENDERER_API_HH

#include <memory>

//! @TODO fix this include path!
#include "../../vendor/glm/glm/glm.hpp"
#include "vertex_array.hh"

namespace Bandolier {

class RendererAPI
{
public:
  enum class API{
    None = 0,
    OpenGL,
    Direct3D,
    Vulkan,
    DirectX = int(Direct3D),
  };

  virtual void
  Init() = 0;

  virtual void
  SetClearColor(const glm::vec4& color) = 0;

  virtual void
  Clear() = 0;

  virtual void
  DrawIndexed(const std::shared_ptr<VertexArray>& VAO) = 0;

  inline static API
  GetAPI(){ return sRendererAPI; }

private:
  inline static API sRendererAPI = API::OpenGL;
};

}

#endif //BANDOLIER_RENDERER_API_HH
