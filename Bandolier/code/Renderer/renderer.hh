#ifndef BANDOLIER_RENDERER_HH
#define BANDOLIER_RENDERER_HH

#include <memory>
#include "vertex_array.hh"
#include "renderer_api.hh"
#include "orthographic_camera.hh"
#include "shader.hh"

namespace Bandolier{

class Renderer
{
private:
  struct SceneData
  {
    glm::mat4 ViewProjectionMatrix;
  };

  inline static std::unique_ptr<SceneData> sSceneData = std::make_unique<SceneData>();

public:
  static void
  BeginScene(OrthographicCamera& camera);

  static void
  EndScene();

  static void
  Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO, const glm::mat4& transform = glm::mat4(1.0f));

  static void
  SetViewport(uint32_t width, uint32_t height);

  inline static
  RendererAPI::API GetAPI()
  {
    return RendererAPI::GetAPI();
  }
};

}

#endif //BANDOLIER_RENDERER_HH
