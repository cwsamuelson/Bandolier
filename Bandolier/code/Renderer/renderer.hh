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
  Submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> VAO);

  inline static
  RendererAPI::API GetAPI()
  {
    return RendererAPI::GetAPI();
  }
};

}

#endif //BANDOLIER_RENDERER_HH
