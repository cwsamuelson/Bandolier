#include "renderer.hh"
#include "render_command.hh"

namespace Bandolier{

void
Renderer::BeginScene(OrthographicCamera& camera)
{
  sSceneData->ViewProjectionMatrix = camera.GetViewProjection();
}

void
Renderer::EndScene()
{
}

void
Renderer::Submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> VAO, const glm::mat4& transform)
{
  shader->Bind();
  shader->UploaduniformMat4("u_ViewProjection", sSceneData->ViewProjectionMatrix);
  shader->UploaduniformMat4("u_Transform", transform);

  VAO->Bind();
  RenderCommand::DrawIndexed(VAO);
}

}

